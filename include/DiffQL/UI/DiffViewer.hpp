#pragma once
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include "DiffQL/UI/ConsoleLog.hpp"
#include <functional>
#include <string>
#include <vector>

namespace DiffQL::UI {

// Full TUI lifecycle: loading console → rename modals → diff viewer,
// all within a single FullscreenAlternateScreen.
// parse_fn is called on a worker thread to load each SQL file.
void run_tui_mode(
    const std::string                                               &origin_path,
    const std::string                                               &dest_path,
    const std::function<std::vector<Table>(const std::string &)>   &parse_fn);

// Standalone diff viewer.
// log is optional — [L] toggle shows captured output.
void run_diff_viewer(
    const SchemaDiff         &diff,
    const std::vector<Table> &origin_schema,
    const std::vector<Table> &dest_schema,
    const ConsoleLog         *log = nullptr);

}
