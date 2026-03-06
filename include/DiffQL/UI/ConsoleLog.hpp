#pragma once
#include <mutex>
#include <streambuf>
#include <string>
#include <vector>

class ConsoleLog
{
public:
  void                     append(const std::string &line);
  std::vector<std::string> snapshot() const;

private:
  mutable std::mutex       m_mutex;
  std::vector<std::string> m_lines;
};

// std::streambuf adapter — routes any ostream writes into a ConsoleLog.
class ConsoleLogBuf : public std::streambuf
{
public:
  explicit ConsoleLogBuf(ConsoleLog &log);

protected:
  // Called by the streambuf machinery for single-char writes.
  int             overflow(int c) override;
  // Called by the streambuf machinery for bulk string writes.
  std::streamsize xsputn(const char *s, std::streamsize n) override;

private:
  ConsoleLog &m_log;
  std::string m_current; // accumulates until '\n'

  void flush_line();
};
