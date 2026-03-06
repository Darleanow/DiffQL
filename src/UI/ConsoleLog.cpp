#include "DiffQL/UI/ConsoleLog.hpp"

void ConsoleLog::append(const std::string &line)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_lines.push_back(line);
}

std::vector<std::string> ConsoleLog::snapshot() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_lines;
}

ConsoleLogBuf::ConsoleLogBuf(ConsoleLog &log) : m_log(log) {}

int ConsoleLogBuf::overflow(int c)
{
  if(c == EOF) return c;
  if(c == '\n')
    flush_line();
  else
    m_current += static_cast<char>(c);
  return c;
}

std::streamsize ConsoleLogBuf::xsputn(const char *s, std::streamsize n)
{
  for(std::streamsize i = 0; i < n; ++i)
    overflow(static_cast<unsigned char>(s[i]));
  return n;
}

void ConsoleLogBuf::flush_line()
{
  m_log.append(m_current);
  m_current.clear();
}
