#pragma once
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

namespace DiffQL
{

inline int lev_distance(const std::string &origin, const std::string &dest)
{
  const int m = static_cast<int>(origin.size());
  const int n = static_cast<int>(dest.size());

  if(m == 0)
    return n;
  if(n == 0)
    return m;

  std::vector<int> prev(n + 1);
  std::iota(prev.begin(), prev.end(), 0);

  std::vector<int> curr(n + 1);

  for(int i = 1; i <= m; ++i) {
    curr[0] = i;
    for(int j = 1; j <= n; ++j) {
      const int cost = (origin[i - 1] == dest[j - 1]) ? 0 : 1;
      curr[j]        = std::min({prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + cost});
    }
    std::swap(prev, curr);
  }

  return prev[n];
}

} // namespace DiffQL
