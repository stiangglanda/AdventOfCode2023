#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> strSplit(std::string s, std::string del)
{
    std::vector<std::string> result;

    int end = s.find(del);
    while (end != -1)
    {
        result.push_back(s.substr(0, end));
        s.erase(s.begin(), s.begin() + end + 1);
        end = s.find(del);
    }
    result.push_back(s.substr(0, end));
    return result;
}

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

std::vector<std::string> readFile()
{
    std::vector<std::string> engine;
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string line;
    while (std::getline(inputFile, line))
    {
        engine.push_back(line);
    }
    inputFile.close();
    return engine;
}

void printInput(std::vector<std::string> input)
{
    for (auto i = input.cbegin(); i != input.cend(); ++i)
    {
        std::cout << *i << std::endl;
    }
}

std::pair<int, int> findWholeNumber(const std::string input, int StartIndex)
{
    std::string number;

    for (int i = StartIndex; i < input.size(); i++)
    {
        if (std::isdigit(input[i]))
        {
            number.push_back(input[i]);
        }
        else
        {
            return std::make_pair(number.size(), std::stoi(number));
        }
    }
    return std::make_pair(number.size(), std::stoi(number));
}

bool CheckNumbersSurrundingArea(const std::vector<std::string> &area, int X, int Y, int length)
{
    for (int x = X - 1; x <= (X + 1); x++)
    {
        if (x >= 0 && x < area.size())
        {
            for (int y = Y - 1; y <= (Y + length); y++)
            {
                if (y >= 0 && y < area[x].size())
                {
                    if (std::isdigit(area[x][y]) || area[x][y] == '.')
                    {
                    }
                    else
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

std::vector<int> parseValidNumbers(const std::vector<std::string> &input)
{
    std::vector<int> ValidNumbers;

    for (int x = 0; x < input.size(); x++)
    {
        for (int y = 0; y < input[x].size(); y++)
        {
            if (std::isdigit(input[x][y]))
            {

                std::pair<int, int> LengthNumber = findWholeNumber(input[x], y);
                if (CheckNumbersSurrundingArea(input, x, y, LengthNumber.first))
                {
                    ValidNumbers.push_back(LengthNumber.second);
                }
                y += LengthNumber.first;
            }
        }
    }

    return ValidNumbers;
}

int AddUp(const std::vector<int> &numbers)
{
    int result = 0;

    for (auto x = numbers.cbegin(); x != numbers.cend(); ++x)
    {
        result += *x;
    }
    return result;
}

int main()
{
    std::vector<std::string> input = readFile();
    std::vector<int> ValidNumbers = parseValidNumbers(input);
    std::cout << "result: " << AddUp(ValidNumbers) << std::endl;
}
