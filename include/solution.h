#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

class Solution {
public:
    inline Solution(const std::vector<std::string>& lines);
    virtual ~Solution() = default;
    virtual void run()  = 0;
    inline const std::vector<std::string>& getLines() const { return m_Lines; }
    inline std::variant<std::uint32_t, std::string> getPartOneSolution() const
        { return m_PartOneSolution; }
    inline std::variant<std::uint32_t, std::string> getPartTwoSolution() const
        { return m_PartTwoSolution; }
protected:
    void setPartOneSolution(std::uint32_t soln) { m_PartOneSolution = soln; }
    void setPartOneSolution(const std::string& soln) { m_PartOneSolution = soln; }

    void setPartTwoSolution(std::uint32_t soln) { m_PartTwoSolution = soln; }
    void setPartTwoSolution(const std::string& soln) { m_PartTwoSolution = soln; }
private:
    std::variant<uint32_t, std::string> m_PartOneSolution = static_cast<uint32_t>(0);
    std::variant<uint32_t, std::string> m_PartTwoSolution = static_cast<uint32_t>(0);
    std::vector<std::string> m_Lines;
};

Solution::Solution(const std::vector<std::string>& lines)
    : m_Lines(lines)
{
}

