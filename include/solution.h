#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Solution
{
public:
  inline Solution(const std::vector<std::string>& lines);
  virtual ~Solution() = default;
  virtual void run();
  inline const std::vector<std::string>& getLines() const { return m_Lines; }
  inline std::uint32_t getPartOneSolution() const { return m_PartOneSolution; }
  inline std::uint32_t getPartTwoSolution() const { return m_PartTwoSolution; }
protected:
  void setPartOneSolution(std::uint32_t soln) { m_PartOneSolution = soln; }
  void setPartTwoSolution(std::uint32_t soln) { m_PartTwoSolution = soln; }
private:
  std::uint32_t m_PartOneSolution;
  std::uint32_t m_PartTwoSolution;
  std::vector<std::string> m_Lines;
};

Solution::Solution(const std::vector<std::string>& lines)
  : m_Lines(lines)
{
}
