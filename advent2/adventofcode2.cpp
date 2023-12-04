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

enum class Color
{
    blue,
    red,
    green
};

struct Game
{
    unsigned int GameId;

    std::vector<std::pair<Color, unsigned int>> sets;
};

std::vector<Game> readFile()
{
    std::vector<Game> games;
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string line;
    while (std::getline(inputFile, line))
    {
        Game Game;
        std::vector<std::pair<Color, unsigned int>> Sets;
        std::string gameId = line.substr(5, line.find(":") - 5);
        trim(gameId);
        Game.GameId = std::stoi(gameId);
        std::string game = line.substr(line.find(":") + 2);
        std::vector<std::string> sets = strSplit(game, ";");

        for (auto x = sets.cbegin(); x != sets.cend(); ++x)
        {
            std::vector<std::string> set = strSplit(*x, ",");

            for (auto y = set.cbegin(); y != set.cend(); ++y)
            {
                std::string TrimmedSet = *y;
                trim(TrimmedSet);
                std::vector<std::string> SpecificSet = strSplit(TrimmedSet, " ");
                if (SpecificSet.size() != 2)
                {
                    std::cout << "Error" << std::endl;
                }

                trim(SpecificSet[0]);
                trim(SpecificSet[1]);

                unsigned int cubeCount = std::stoi(SpecificSet[0]);
                Color cubeColor;

                if (SpecificSet[1] == "blue")
                {
                    cubeColor = Color::blue;
                }
                else if (SpecificSet[1] == "red")
                {
                    cubeColor = Color::red;
                }
                else if (SpecificSet[1] == "green")
                {
                    cubeColor = Color::green;
                }
                else
                {
                    std::cout << "Error\n";
                }

                Sets.push_back(std::make_pair(cubeColor, cubeCount));
            }
            Game.sets = Sets;
        }

        games.push_back(Game);
    }
    inputFile.close();
    return games;
}

void printInput(std::vector<std::string> input)
{
    for (auto i = input.cbegin(); i != input.cend(); ++i)
    {
        std::cout << *i << std::endl;
    }
}

void printGameVector(std::vector<Game> games)
{
    for (auto x = games.cbegin(); x != games.cend(); ++x)
    {
        std::cout << "GameId: " << x->GameId << std::endl;

        for (auto y = x->sets.cbegin(); y != x->sets.cend(); ++y)
        {

            switch (y->first)
            {
            case Color::blue:
                std::cout << "Color: blue" << std::endl;
                break;
            case Color::red:
                std::cout << "Color: red" << std::endl;
                break;
            case Color::green:
                std::cout << "Color: green" << std::endl;
                break;
            default:
                std::cout << "Error\n";
                break;
            }

            std::cout << "CubeCount: " << y->second << std::endl;
        }
    }
}

bool isSetPossible(std::vector<std::pair<Color, unsigned int>> Sets)
{
    for (auto y = Sets.cbegin(); y != Sets.cend(); ++y)
    {
        switch (y->first)
        {
        case Color::blue:
            if (y->second > 14)
            {
                return false;
            }
            break;
        case Color::red:
            if (y->second > 12)
            {
                return false;
            }
            break;
        case Color::green:
            if (y->second > 13)
            {
                return false;
            }
            break;
        default:
            std::cout << "Error\n";
            break;
        }
    }
    return true;
}

int AddUpPossibleGameIds(std::vector<Game> games)
{
    int result = 0;

    for (auto x = games.cbegin(); x != games.cend(); ++x)
    {
        if (isSetPossible(x->sets))
        {
            result += x->GameId;
        }
    }
    return result;
}

int main()
{
    std::vector<Game> games = readFile();
    // printGameVector(games);
    std::cout << "result: " << AddUpPossibleGameIds(games) << std::endl;
}
