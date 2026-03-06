#include "DiffQL/UI/DiffViewer.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/terminal.hpp>

using namespace ftxui;

namespace {

enum class LineStyle
{
  NORMAL,
  ADDED,
  DROPPED,
  MODIFIED,
  EMPTY,
};

struct DiffRow
{
  std::string left;
  std::string right;
  LineStyle   left_style;
  LineStyle   right_style;
};

static std::string fmt_type(const CanonicalType &t)
{
  const char *base_name = nullptr;
  switch(t.base) {
    case CanonicalType::INTEGER:    base_name = "INT"; break;
    case CanonicalType::BIGINT:     base_name = "BIGINT"; break;
    case CanonicalType::SMALLINT:   base_name = "SMALLINT"; break;
    case CanonicalType::TINYINT:    base_name = "TINYINT"; break;
    case CanonicalType::MEDIUMINT:  base_name = "MEDIUMINT"; break;
    case CanonicalType::VARCHAR:    base_name = "VARCHAR"; break;
    case CanonicalType::TEXT:       base_name = "TEXT"; break;
    case CanonicalType::MEDIUMTEXT: base_name = "MEDIUMTEXT"; break;
    case CanonicalType::LONGTEXT:   base_name = "LONGTEXT"; break;
    case CanonicalType::CHAR:       base_name = "CHAR"; break;
    case CanonicalType::DECIMAL:    base_name = "DECIMAL"; break;
    case CanonicalType::FLOAT:      base_name = "FLOAT"; break;
    case CanonicalType::DOUBLE:     base_name = "DOUBLE"; break;
    case CanonicalType::DATE:       base_name = "DATE"; break;
    case CanonicalType::DATETIME:   base_name = "DATETIME"; break;
    case CanonicalType::TIMESTAMP:  base_name = "TIMESTAMP"; break;
    case CanonicalType::TIME:       base_name = "TIME"; break;
    case CanonicalType::BOOLEAN:    base_name = "BOOLEAN"; break;
    case CanonicalType::BLOB:       base_name = "BLOB"; break;
    case CanonicalType::JSON:       base_name = "JSON"; break;
    case CanonicalType::ENUM:       base_name = "ENUM"; break;
  }
  std::ostringstream os;
  os << base_name;
  if(t.length)    os << "(" << *t.length << ")";
  if(t.precision) {
    os << "(" << *t.precision;
    if(t.scale) os << "," << *t.scale;
    os << ")";
  }
  return os.str();
}

static std::string fmt_column(const Column &col)
{
  std::ostringstream ss;
  ss << "`" << col.name << "` " << fmt_type(col.type);
  if(!col.nullable)      ss << " NOT NULL";
  if(col.auto_increment) ss << " AUTO_INCREMENT";
  if(col.default_value)  ss << " DEFAULT " << *col.default_value;
  return ss.str();
}

static std::string join_names(const std::vector<std::string> &names)
{
  std::ostringstream ss;
  for(size_t i = 0; i < names.size(); ++i) {
    if(i > 0) ss << ", ";
    ss << "`" << names[i] << "`";
  }
  return ss.str();
}

static std::vector<std::string> render_table_lines(const Table &table)
{
  std::vector<std::string> lines;
  lines.push_back("CREATE TABLE `" + table.name + "` (");

  size_t total_items = table.columns.size() +
                       (table.primary_key ? 1 : 0) +
                       table.foreign_keys.size() +
                       table.indexes.size() +
                       table.checks.size();
  size_t idx = 0;

  for(const auto &col : table.columns) {
    bool last = (++idx == total_items);
    lines.push_back("  " + fmt_column(col) + (last ? "" : ","));
  }

  if(table.primary_key) {
    bool last = (++idx == total_items);
    lines.push_back(
        "  PRIMARY KEY (" + join_names(table.primary_key->column_names) + ")" +
        (last ? "" : ",")
    );
  }

  for(const auto &fk : table.foreign_keys) {
    bool last = (++idx == total_items);
    lines.push_back(
        "  FOREIGN KEY (" + join_names(fk.column_names) + ") REFERENCES `" +
        fk.referenced_table + "` (" + join_names(fk.referenced_columns) + ")" +
        (last ? "" : ",")
    );
  }

  for(const auto &ix : table.indexes) {
    bool last = (++idx == total_items);
    lines.push_back(
        "  " + std::string(ix.unique ? "UNIQUE " : "") + "INDEX `" + ix.name +
        "` (" + join_names(ix.column_names) + ")" + (last ? "" : ",")
    );
  }

  for(const auto &ck : table.checks) {
    bool last = (++idx == total_items);
    lines.push_back(
        "  CONSTRAINT `" + ck.name + "` CHECK (" + ck.expression + ")" +
        (last ? "" : ",")
    );
  }

  lines.push_back(");");
  return lines;
}

static void add_modified_table_rows(
    std::vector<DiffRow> &rows,
    const TableDiff      &td,
    const Table          &origin,
    const Table          &dest
)
{
  // Index column diffs by name for O(1) lookup
  std::unordered_map<std::string, const ElementDiff<Column> *> col_diff_map;
  for(const auto &cd : td.column_diffs)
    col_diff_map[cd.name] = &cd;

  // Table header (show rename if applicable)
  rows.push_back(
      {"CREATE TABLE `" + origin.name + "` (",
       "CREATE TABLE `" + dest.name + "` (",
       LineStyle::NORMAL,
       LineStyle::NORMAL}
  );

  // Walk origin columns in declaration order
  for(const auto &col : origin.columns) {
    auto it = col_diff_map.find(col.name);
    if(it == col_diff_map.end()) {
      // Unchanged — identical on both sides
      std::string line = "  " + fmt_column(col) + ",";
      rows.push_back({line, line, LineStyle::NORMAL, LineStyle::NORMAL});
    } else {
      const auto &cd = *it->second;
      if(cd.action == DiffAction::DROPPED) {
        rows.push_back(
            {"- " + fmt_column(col) + ",",
             "",
             LineStyle::DROPPED,
             LineStyle::EMPTY}
        );
      } else if(cd.action == DiffAction::MODIFIED && cd.before && cd.after) {
        rows.push_back(
            {"~ " + fmt_column(*cd.before) + ",",
             "~ " + fmt_column(*cd.after) + ",",
             LineStyle::MODIFIED,
             LineStyle::MODIFIED}
        );
      }
    }
  }

  // Appended additions (preserve dest column order)
  for(const auto &dest_col : dest.columns) {
    auto it = col_diff_map.find(dest_col.name);
    if(it != col_diff_map.end() && it->second->action == DiffAction::ADDED &&
       it->second->after) {
      rows.push_back(
          {"",
           "+ " + fmt_column(*it->second->after) + ",",
           LineStyle::EMPTY,
           LineStyle::ADDED}
      );
    }
  }

  // Primary key diff
  if(td.pk_diff) {
    const auto &pd = *td.pk_diff;
    if(pd.action == DiffAction::DROPPED && pd.before) {
      rows.push_back(
          {"- PRIMARY KEY (" + join_names(pd.before->column_names) + "),",
           "",
           LineStyle::DROPPED,
           LineStyle::EMPTY}
      );
    } else if(pd.action == DiffAction::ADDED && pd.after) {
      rows.push_back(
          {"",
           "+ PRIMARY KEY (" + join_names(pd.after->column_names) + "),",
           LineStyle::EMPTY,
           LineStyle::ADDED}
      );
    } else if(pd.action == DiffAction::MODIFIED && pd.before && pd.after) {
      rows.push_back(
          {"~ PRIMARY KEY (" + join_names(pd.before->column_names) + "),",
           "~ PRIMARY KEY (" + join_names(pd.after->column_names) + "),",
           LineStyle::MODIFIED,
           LineStyle::MODIFIED}
      );
    }
  }

  // Foreign key diffs
  for(const auto &fd : td.fk_diffs) {
    if(fd.action == DiffAction::DROPPED && fd.before) {
      rows.push_back(
          {"- FOREIGN KEY (" + join_names(fd.before->column_names) +
               ") REFERENCES `" + fd.before->referenced_table + "` (" +
               join_names(fd.before->referenced_columns) + "),",
           "",
           LineStyle::DROPPED,
           LineStyle::EMPTY}
      );
    } else if(fd.action == DiffAction::ADDED && fd.after) {
      rows.push_back(
          {"",
           "+ FOREIGN KEY (" + join_names(fd.after->column_names) +
               ") REFERENCES `" + fd.after->referenced_table + "` (" +
               join_names(fd.after->referenced_columns) + "),",
           LineStyle::EMPTY,
           LineStyle::ADDED}
      );
    }
  }

  // Index diffs
  for(const auto &id : td.index_diffs) {
    if(id.action == DiffAction::DROPPED && id.before) {
      rows.push_back(
          {"- " + std::string(id.before->unique ? "UNIQUE " : "") + "INDEX `" +
               id.before->name + "` (" + join_names(id.before->column_names) +
               "),",
           "",
           LineStyle::DROPPED,
           LineStyle::EMPTY}
      );
    } else if(id.action == DiffAction::ADDED && id.after) {
      rows.push_back(
          {"",
           "+ " + std::string(id.after->unique ? "UNIQUE " : "") + "INDEX `" +
               id.after->name + "` (" + join_names(id.after->column_names) +
               "),",
           LineStyle::EMPTY,
           LineStyle::ADDED}
      );
    }
  }

  // Check constraint diffs
  for(const auto &ck : td.check_diffs) {
    if(ck.action == DiffAction::DROPPED && ck.before) {
      rows.push_back(
          {"- CONSTRAINT `" + ck.before->name + "` CHECK (" +
               ck.before->expression + "),",
           "",
           LineStyle::DROPPED,
           LineStyle::EMPTY}
      );
    } else if(ck.action == DiffAction::ADDED && ck.after) {
      rows.push_back(
          {"",
           "+ CONSTRAINT `" + ck.after->name + "` CHECK (" +
               ck.after->expression + "),",
           LineStyle::EMPTY,
           LineStyle::ADDED}
      );
    }
  }

  rows.push_back({");", ");", LineStyle::NORMAL, LineStyle::NORMAL});
}

static std::vector<DiffRow> build_diff_rows(
    const SchemaDiff         &diff,
    const std::vector<Table> &origin_schema,
    const std::vector<Table> &dest_schema
)
{
  std::unordered_map<std::string, const Table *> origin_map, dest_map;
  for(const auto &t : origin_schema)
    origin_map[t.name] = &t;
  for(const auto &t : dest_schema)
    dest_map[t.name] = &t;

  std::vector<DiffRow> rows;

  for(const auto &td : diff.table_diffs) {
    // Blank separator between tables
    if(!rows.empty())
      rows.push_back({"", "", LineStyle::NORMAL, LineStyle::NORMAL});

    switch(td.action) {
      case DiffAction::DROPPED: {
        auto it = origin_map.find(td.table_name);
        if(it == origin_map.end())
          break;
        for(const auto &line : render_table_lines(*it->second))
          rows.push_back({line, "", LineStyle::DROPPED, LineStyle::EMPTY});
        break;
      }
      case DiffAction::ADDED: {
        auto it = dest_map.find(td.new_name.value_or(td.table_name));
        if(it == dest_map.end())
          break;
        for(const auto &line : render_table_lines(*it->second))
          rows.push_back({"", line, LineStyle::EMPTY, LineStyle::ADDED});
        break;
      }
      case DiffAction::MODIFIED: {
        auto orig_it = origin_map.find(td.table_name);
        auto dest_it = dest_map.find(td.new_name.value_or(td.table_name));
        if(orig_it == origin_map.end() || dest_it == dest_map.end())
          break;
        add_modified_table_rows(rows, td, *orig_it->second, *dest_it->second);
        break;
      }
    }
  }

  if(rows.empty())
    rows.push_back(
        {"(no differences)", "(no differences)", LineStyle::NORMAL,
         LineStyle::NORMAL}
    );

  return rows;
}

static Element styled_text(const std::string &txt, LineStyle style)
{
  auto elem = text(txt);
  switch(style) {
    case LineStyle::ADDED:    return elem | color(Color::GreenLight);
    case LineStyle::DROPPED:  return elem | color(Color::RedLight);
    case LineStyle::MODIFIED: return elem | color(Color::YellowLight);
    case LineStyle::EMPTY:    return elem | color(Color::GrayDark);
    case LineStyle::NORMAL:   return elem;
  }
  return elem;
}

static constexpr int LOG_PANEL_LINES = 8;

} // anonymous namespace

namespace DiffQL::UI {

bool ask_rename(
    const std::string &orig_name,
    const std::string &dest_name,
    float              similarity
)
{
  bool result = false;
  auto screen = ScreenInteractive::FitComponent();

  auto pct = std::to_string(static_cast<int>(similarity * 100.0f)) + "%";

  auto dialog = Renderer([&] {
    return vbox({
               text(" Rename detected ") | bold | hcenter,
               separator(),
               hbox({text("  "), text(orig_name) | color(Color::RedLight),
                     text("  →  "), text(dest_name) | color(Color::GreenLight),
                     text("  ")}),
               text("  Similarity: " + pct) | color(Color::YellowLight),
               separator(),
               text("  Treat as rename / modification?  ") | hcenter,
               hbox({
                   text("  "),
                   text("[Y] Yes") | color(Color::GreenLight) | bold,
                   text("   "),
                   text("[N] No") | color(Color::RedLight) | bold,
                   text("  "),
               }) | hcenter,
           }) |
           border;
  });

  auto component = CatchEvent(dialog, [&](Event event) -> bool {
    if(event == Event::Character('y') || event == Event::Character('Y')) {
      result = true;
      screen.Exit();
      return true;
    }
    if(event == Event::Character('n') || event == Event::Character('N') ||
       event == Event::Return || event == Event::Escape) {
      result = false;
      screen.Exit();
      return true;
    }
    return false;
  });

  screen.Loop(component);
  return result;
}

void run_diff_viewer(
    const SchemaDiff         &diff,
    const std::vector<Table> &origin_schema,
    const std::vector<Table> &dest_schema,
    const ConsoleLog         *log
)
{
  auto rows       = build_diff_rows(diff, origin_schema, dest_schema);
  int  total_rows = static_cast<int>(rows.size());
  int  scroll     = 0;
  int  log_scroll = 0;
  bool log_open   = false;

  // Pre-compute summary counts
  int added = 0, dropped = 0, modified = 0;
  for(const auto &td : diff.table_diffs) {
    switch(td.action) {
      case DiffAction::ADDED:    ++added; break;
      case DiffAction::DROPPED:  ++dropped; break;
      case DiffAction::MODIFIED: ++modified; break;
    }
  }

  auto screen = ScreenInteractive::FullscreenAlternateScreen();

  auto renderer = Renderer([&] {
    int total_h    = Terminal::Size().dimy;
    int log_h      = (log && log_open) ? LOG_PANEL_LINES + 3 : 0; // +border
    // chrome: border(2) + header(1) + sub-sep(1) + footer(1) = 5
    int visible    = std::max(1, total_h - 5 - log_h);
    int max_scroll = std::max(0, total_rows - visible);
    scroll         = std::clamp(scroll, 0, max_scroll);

    int end = std::min(scroll + visible, total_rows);
    Elements left_lines, right_lines;
    left_lines.reserve(static_cast<size_t>(visible));
    right_lines.reserve(static_cast<size_t>(visible));

    for(int i = scroll; i < end; ++i) {
      const auto &row = rows[static_cast<size_t>(i)];
      left_lines.push_back(styled_text(row.left, row.left_style));
      right_lines.push_back(styled_text(row.right, row.right_style));
    }
    while(static_cast<int>(left_lines.size()) < visible) {
      left_lines.push_back(text(""));
      right_lines.push_back(text(""));
    }

    std::string summary =
        std::to_string(static_cast<int>(diff.table_diffs.size())) +
        " table(s)  +" + std::to_string(added) + " -" +
        std::to_string(dropped) + " ~" + std::to_string(modified);

    std::string position =
        std::to_string(scroll + 1) + "/" + std::to_string(total_rows);

    std::string log_key = log ? "  [L] Log" : "";

    Elements main_elements;

    if(log && log_open) {
      auto log_lines = log->snapshot();
      int  log_total = static_cast<int>(log_lines.size());
      int  log_max   = std::max(0, log_total - LOG_PANEL_LINES);
      log_scroll     = std::clamp(log_scroll, 0, log_max);

      Elements log_elems;
      log_elems.reserve(static_cast<size_t>(LOG_PANEL_LINES));
      int log_end = std::min(log_scroll + LOG_PANEL_LINES, log_total);
      for(int i = log_scroll; i < log_end; ++i)
        log_elems.push_back(
            text(log_lines[static_cast<size_t>(i)]) | color(Color::GrayLight)
        );
      while(static_cast<int>(log_elems.size()) < LOG_PANEL_LINES)
        log_elems.push_back(text(""));

      main_elements.push_back(
          vbox({
              text(" Console Log ") | bold,
              separatorLight(),
              vbox(std::move(log_elems)),
          }) | border | size(HEIGHT, EQUAL, LOG_PANEL_LINES + 3)
      );
    }

    main_elements.push_back(
        vbox({
            hbox({
                text(" Original Schema ") | bold | flex,
                separatorLight(),
                text(" After Migration ") | bold | flex,
            }),
            separatorLight(),
            hbox({
                vbox(std::move(left_lines)) | flex,
                separatorLight(),
                vbox(std::move(right_lines)) | flex,
            }) | flex,
        }) | border | flex
    );

    main_elements.push_back(hbox({
        text(" [↑↓/j/k] Scroll  [PgUp/PgDn] Page  [Home/End]" + log_key +
             "  [q] Quit  ") |
            color(Color::GrayLight),
        text(summary) | bold,
        filler(),
        text(position + " ") | color(Color::GrayLight),
    }));

    return vbox(std::move(main_elements));
  });

  auto component = CatchEvent(renderer, [&](Event event) -> bool {
    int total_h    = Terminal::Size().dimy;
    int log_h      = (log && log_open) ? LOG_PANEL_LINES + 3 : 0;
    int visible    = std::max(1, total_h - 5 - log_h);
    int max_scroll = std::max(0, total_rows - visible);

    if(event == Event::Character('q') || event == Event::Escape ||
       event == Event::Return) {
      screen.Exit();
      return true;
    }
    if(log && event == Event::Character('l')) {
      log_open   = !log_open;
      log_scroll = 0;
      return true;
    }
    if(event == Event::ArrowDown || event == Event::Character('j')) {
      scroll = std::min(scroll + 1, max_scroll);
      return true;
    }
    if(event == Event::ArrowUp || event == Event::Character('k')) {
      scroll = std::max(scroll - 1, 0);
      return true;
    }
    if(event == Event::PageDown) {
      scroll = std::min(scroll + visible, max_scroll);
      return true;
    }
    if(event == Event::PageUp) {
      scroll = std::max(scroll - visible, 0);
      return true;
    }
    if(event == Event::Home) {
      scroll = 0;
      return true;
    }
    if(event == Event::End) {
      scroll = max_scroll;
      return true;
    }
    return false;
  });

  screen.Loop(component);
}

void run_tui_mode(
    const std::string                                             &origin_path,
    const std::string                                             &dest_path,
    const std::function<std::vector<Table>(const std::string &)> &parse_fn
)
{
  enum class Phase
  {
    LOADING,
    RENAME,
    VIEWING
  };

  std::atomic<Phase> phase {Phase::LOADING};

  ConsoleLog log;

  std::mutex              rename_mutex;
  std::condition_variable rename_cv;
  std::string             rename_orig, rename_dest;
  float                   rename_score = 0.f;
  std::optional<bool>     rename_answer;
  bool                    has_rename = false;

  std::vector<DiffRow> diff_rows;
  int                  diff_total  = 0;
  int                  diff_scroll = 0;
  int                  added = 0, dropped = 0, modified = 0;
  bool                 log_open        = false;
  int                  log_panel_scroll = 0;
  std::string          diff_summary;

  auto screen = ScreenInteractive::FullscreenAlternateScreen();

  // IMPORTANT: never redirect std::cout/cerr here — std::cout is used by
  // FTXUI on the main thread for rendering.  Use log.append() directly.
  std::thread worker([&] {
    log.append("Parsing " + origin_path + " ...");
    auto origin_schema = parse_fn(origin_path);
    log.append("  → " + std::to_string(origin_schema.size()) + " table(s) found");
    log.append("");

    log.append("Parsing " + dest_path + " ...");
    auto dest_schema = parse_fn(dest_path);
    log.append("  → " + std::to_string(dest_schema.size()) + " table(s) found");
    log.append("");

    log.append("Computing schema diff...");

    DiffEngine engine(origin_schema, dest_schema);
    engine.set_rename_callback(
        [&](const std::string &orig, const std::string &dest,
            float              score) -> bool {
          log.append("  Rename candidate: '" + orig + "'  →  '" + dest + "'");
          {
            std::unique_lock<std::mutex> lock(rename_mutex);
            rename_orig   = orig;
            rename_dest   = dest;
            rename_score  = score;
            rename_answer = std::nullopt;
            has_rename    = true;
          }
          phase.store(Phase::RENAME);
          screen.PostEvent(Event::Custom);

          // Wait for user answer — lock is released during wait
          std::unique_lock<std::mutex> lock(rename_mutex);
          rename_cv.wait(lock, [&] { return rename_answer.has_value(); });
          bool answer = *rename_answer;
          has_rename  = false;
          lock.unlock();

          log.append(
              std::string("  → ") + (answer ? "treated as rename" : "treated as drop + add")
          );

          phase.store(Phase::LOADING);
          screen.PostEvent(Event::Custom);
          return answer;
        }
    );

    SchemaDiff diff = engine.compare_schemas();

    diff_rows  = build_diff_rows(diff, origin_schema, dest_schema);
    diff_total = static_cast<int>(diff_rows.size());
    for(const auto &td : diff.table_diffs) {
      switch(td.action) {
        case DiffAction::ADDED:    ++added; break;
        case DiffAction::DROPPED:  ++dropped; break;
        case DiffAction::MODIFIED: ++modified; break;
      }
    }

    diff_summary = std::to_string(static_cast<int>(diff.table_diffs.size())) +
                   " table(s) changed  +" + std::to_string(added) + " -" +
                   std::to_string(dropped) + " ~" + std::to_string(modified);

    log.append("Done — " + diff_summary);

    phase.store(Phase::VIEWING);
    screen.PostEvent(Event::Custom);
  });

  // ── Refresh thread (keeps loading screen live while worker runs) ───────────
  std::atomic<bool> refreshing {true};
  std::thread       refresh_thread([&] {
    using namespace std::chrono_literals;
    while(refreshing.load()) {
      std::this_thread::sleep_for(100ms);
      if(phase.load() == Phase::LOADING)
        screen.PostEvent(Event::Custom);
    }
  });

  auto renderer = Renderer([&] {
    auto p      = phase.load();
    int  term_h = Terminal::Size().dimy;

    if(p == Phase::VIEWING) {
      int log_h   = log_open ? LOG_PANEL_LINES + 3 : 0;
      int visible = std::max(1, term_h - 5 - log_h);
      diff_scroll = std::clamp(diff_scroll, 0, std::max(0, diff_total - visible));

      int      end = std::min(diff_scroll + visible, diff_total);
      Elements left_lines, right_lines;
      for(int i = diff_scroll; i < end; ++i) {
        const auto &row = diff_rows[static_cast<size_t>(i)];
        left_lines.push_back(styled_text(row.left, row.left_style));
        right_lines.push_back(styled_text(row.right, row.right_style));
      }
      while(static_cast<int>(left_lines.size()) < visible) {
        left_lines.push_back(text(""));
        right_lines.push_back(text(""));
      }

      std::string pos = std::to_string(diff_scroll + 1) + "/" +
                        std::to_string(diff_total);
      std::string log_key = "  [L] Log";

      Elements elems;

      if(log_open) {
        auto snap      = log.snapshot();
        int  log_total = static_cast<int>(snap.size());
        int  lmax      = std::max(0, log_total - LOG_PANEL_LINES);
        log_panel_scroll = std::clamp(log_panel_scroll, 0, lmax);
        int      lend = std::min(log_panel_scroll + LOG_PANEL_LINES, log_total);
        Elements le;
        for(int i = log_panel_scroll; i < lend; ++i)
          le.push_back(
              text(snap[static_cast<size_t>(i)]) | color(Color::GrayLight)
          );
        while(static_cast<int>(le.size()) < LOG_PANEL_LINES)
          le.push_back(text(""));
        elems.push_back(
            vbox({text(" Console Log ") | bold, separatorLight(),
                  vbox(std::move(le))}) | border |
            size(HEIGHT, EQUAL, LOG_PANEL_LINES + 3)
        );
      }

      elems.push_back(
          vbox({hbox({text(" Original Schema ") | bold | flex, separatorLight(),
                      text(" After Migration ") | bold | flex}),
                separatorLight(),
                hbox({vbox(std::move(left_lines)) | flex, separatorLight(),
                      vbox(std::move(right_lines)) | flex}) | flex}) |
          border | flex
      );
      elems.push_back(hbox({
          text(" [↑↓/j/k] Scroll  [PgUp/PgDn] Page  [Home/End]" + log_key +
               "  [q] Quit  ") |
              color(Color::GrayLight),
          text(diff_summary) | bold,
          filler(),
          text(pos + " ") | color(Color::GrayLight),
      }));
      return vbox(std::move(elems));
    }

    auto snap        = log.snapshot();
    int  log_total   = static_cast<int>(snap.size());
    int  log_visible = std::max(1, term_h - 5);
    // Auto-scroll to bottom so latest output is always visible
    int log_scroll_auto = std::max(0, log_total - log_visible);

    Elements log_elems;
    int      lend = std::min(log_scroll_auto + log_visible, log_total);
    for(int i = log_scroll_auto; i < lend; ++i)
      log_elems.push_back(
          text(snap[static_cast<size_t>(i)]) | color(Color::GrayLight)
      );
    while(static_cast<int>(log_elems.size()) < log_visible)
      log_elems.push_back(text(""));

    auto console_view =
        vbox({hbox({text(" DiffQL ") | bold | color(Color::CyanLight),
                    filler(),
                    text(" Loading... ") | color(Color::YellowLight) | bold}),
              separatorLight(), vbox(std::move(log_elems)) | flex}) |
        border | flex;

    auto footer = hbox({
        text(" Please wait — parsing and computing diff...") |
            color(Color::GrayLight),
    });

    if(p == Phase::RENAME) {
      std::string orig, dest, pct;
      {
        std::lock_guard<std::mutex> lock(rename_mutex);
        if(!has_rename)
          return vbox({console_view, footer});
        orig = rename_orig;
        dest = rename_dest;
        pct  = std::to_string(static_cast<int>(rename_score * 100.f)) + "%";
      }
      auto modal =
          vbox({text(" Rename detected ") | bold | hcenter, separator(),
                hbox({text("  "), text(orig) | color(Color::RedLight),
                      text("  →  "), text(dest) | color(Color::GreenLight),
                      text("  ")}),
                text("  Similarity: " + pct) | color(Color::YellowLight),
                separator(),
                text("  Treat as rename / modification?  ") | hcenter,
                hbox({text("  "),
                      text("[Y] Yes") | color(Color::GreenLight) | bold,
                      text("   "),
                      text("[N] No") | color(Color::RedLight) | bold,
                      text("  ")}) | hcenter}) |
          border | center;

      return vbox({dbox({console_view, modal}), footer});
    }

    return vbox({console_view, footer});
  });

  auto component = CatchEvent(renderer, [&](Event event) -> bool {
    auto p = phase.load();

    if(p == Phase::RENAME) {
      bool answered = false;
      bool answer   = false;
      if(event == Event::Character('y') || event == Event::Character('Y')) {
        answered = answer = true;
      } else if(
          event == Event::Character('n') || event == Event::Character('N') ||
          event == Event::Return || event == Event::Escape
      ) {
        answered = true;
        answer   = false;
      }
      if(answered) {
        {
          std::lock_guard<std::mutex> lock(rename_mutex);
          rename_answer = answer;
        }
        rename_cv.notify_one();
        return true;
      }
      return false;
    }

    if(p == Phase::VIEWING) {
      int log_h   = log_open ? LOG_PANEL_LINES + 3 : 0;
      int visible = std::max(1, Terminal::Size().dimy - 5 - log_h);
      int max_s   = std::max(0, diff_total - visible);

      if(event == Event::Character('q') || event == Event::Escape ||
         event == Event::Return) {
        screen.Exit();
        return true;
      }
      if(event == Event::Character('l')) {
        log_open        = !log_open;
        log_panel_scroll = 0;
        return true;
      }
      if(event == Event::ArrowDown || event == Event::Character('j')) {
        diff_scroll = std::min(diff_scroll + 1, max_s);
        return true;
      }
      if(event == Event::ArrowUp || event == Event::Character('k')) {
        diff_scroll = std::max(diff_scroll - 1, 0);
        return true;
      }
      if(event == Event::PageDown) {
        diff_scroll = std::min(diff_scroll + visible, max_s);
        return true;
      }
      if(event == Event::PageUp) {
        diff_scroll = std::max(diff_scroll - visible, 0);
        return true;
      }
      if(event == Event::Home) {
        diff_scroll = 0;
        return true;
      }
      if(event == Event::End) {
        diff_scroll = max_s;
        return true;
      }
    }
    return false;
  });

  screen.Loop(component);

  refreshing.store(false);
  refresh_thread.join();
  worker.join();
}

}
