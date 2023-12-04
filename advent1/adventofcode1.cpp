#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int findFirstDigit(std::string x)
{
    for (auto y = x.cbegin(); y != x.cend(); ++y)
    {
        if (isdigit(*y))
        {
            return *y - '0';
        }
    }
    return 0;
}

int findLastDigit(std::string x)
{
    for (auto y = x.crbegin(); y != x.crend(); ++y)
    {
        if (isdigit(*y))
        {
            return *y - '0';
        }
    }
    return 0;
}

std::vector<std::string> readFile()
{
    std::vector<std::string> input;
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string line;
    while (std::getline(inputFile, line))
    {
        input.push_back(line);
    }
    inputFile.close();
    return input;
}

void printInput(std::vector<std::string> input)
{
    for (auto i = input.cbegin(); i != input.cend(); ++i)
    {
        std::cout << *i << std::endl;
    }
}

int addUpResults(std::vector<int> lineResults)
{
    int finalResult = 0;
    for (auto x = lineResults.cbegin(); x != lineResults.cend(); ++x)
    {
        finalResult += *x;
    }
    return finalResult;
}

int main()
{
    std::vector<std::string> input = readFile();
    std::vector<int> lineResults;

    printInput(input);

    for (auto x = input.cbegin(); x != input.cend(); ++x)
    {
        int firstDigit = findFirstDigit(*x);
        int lastDigit = findLastDigit(*x);

        std::string result = std::to_string(firstDigit) + std::to_string(lastDigit);
        std::cout << result << std::endl;

        lineResults.push_back(std::stoi(result));
    }

    std::cout << "result: " << addUpResults(lineResults) << std::endl;
}
