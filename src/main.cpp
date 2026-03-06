#include "DiffQL/Connectors/MariaDB/Connector.hpp"
#include "DiffQL/UI/DiffViewer.hpp"

#include <iostream>
#include <string>

static MariaDBConn parse_conn_block(char **argv, int start, int end)
{
  MariaDBConn conn;
  for(int i = start; i < end - 1; ++i) {
    std::string flag = argv[i];
    std::string val  = argv[i + 1];
    if     (flag == "-u") conn.user   = val;
    else if(flag == "-p") conn.passwd = val;
    else if(flag == "-d") conn.db     = val;
    else if(flag == "-h") conn.host   = val;
    else if(flag == "-P") conn.port   = std::stoi(val);
  }
  return conn;
}

static int find_flag(int argc, char **argv, const std::string &flag)
{
  for(int i = 1; i < argc; ++i)
    if(std::string(argv[i]) == flag) return i;
  return -1;
}

static void print_usage(const char *prog)
{
  std::cerr
      << "Usage:\n"
      << "  " << prog
      << " --source -u USER -p PASS -d DB [-h HOST] [-P PORT]"
         " --target -u USER -p PASS -d DB [-h HOST] [-P PORT]\n";
}

int main(int argc, char **argv)
{
  int src_pos = find_flag(argc, argv, "--source");
  int tgt_pos = find_flag(argc, argv, "--target");

  if(src_pos == -1 || tgt_pos == -1) {
    print_usage(argv[0]);
    return 1;
  }

  MariaDBConn src = parse_conn_block(argv, src_pos + 1, tgt_pos);
  MariaDBConn tgt = parse_conn_block(argv, tgt_pos + 1, argc);

  if(src.user.empty() || src.db.empty() || tgt.user.empty() || tgt.db.empty()) {
    std::cerr << "Error: -u and -d are required for both --source and --target.\n";
    print_usage(argv[0]);
    return 1;
  }

  DiffQL::UI::run_tui_mode(
      [src](ConsoleLog &log) mutable {
        log.append("Connecting to " + src.host + "/" + src.db + " ...");
        MariaDBConnector connector(src);
        return connector.get_schema(&log);
      },
      [tgt](ConsoleLog &log) mutable {
        log.append("Connecting to " + tgt.host + "/" + tgt.db + " ...");
        MariaDBConnector connector(tgt);
        return connector.get_schema(&log);
      }
  );

  return 0;
}
