#pragma once
#include "DiffQL/CanonicalObjectModel/Hierarchy.hpp"
#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include "DiffQL/UI/ConsoleLog.hpp"
#include <functional>
#include <string>
#include <vector>

// Loader function type: receives a ConsoleLog to write progress into,
// returns the parsed schema.
using SchemaLoader = std::function<std::vector<Table>(ConsoleLog &)>;

namespace DiffQL::UI {

// Interactive rename confirmation modal (opens its own FTXUI screen).
bool ask_rename(
    const std::string &orig_name,
    const std::string &dest_name,
    float              similarity);

// Full TUI lifecycle: loading console -> rename modals -> diff viewer,
// all within a single FullscreenAlternateScreen.
// source_loader and target_loader are called on a worker thread; they
// receive a ConsoleLog to append progress lines into.
void run_tui_mode(
    SchemaLoader source_loader,
    SchemaLoader target_loader);

// Standalone split-pane diff viewer.
// log is optional — [L] toggle shows captured output.
void run_diff_viewer(
    const SchemaDiff         &diff,
    const std::vector<Table> &origin_schema,
    const std::vector<Table> &dest_schema,
    const ConsoleLog         *log = nullptr);

}
