#include <algorithm>
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

struct Card
{
    unsigned int CardId;

    std::vector<int> YourCards;
    std::vector<int> WinningCards;
};

static std::vector<int> CastStringsToInt(const std::vector<std::string> &numbers)
{
    std::vector<int> castednumbers;
    for (auto i = numbers.cbegin(); i != numbers.cend(); ++i)
    {
        castednumbers.push_back(std::stoi(*i));
    }
    return std::move(castednumbers);
}

static std::vector<Card> readFile()
{
    std::vector<Card> cards;
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string line;
    while (std::getline(inputFile, line))
    {
        Card card;
        std::string cardId = line.substr(5, line.find(":") - 5);
        trim(cardId);
        card.CardId = std::stoi(cardId);
        std::string cardstr = line.substr(line.find(":") + 2);

        std::vector<std::string> numberslists = strSplit(cardstr, "|");

        if (numberslists.size() != 2)
        {
            std::cout << "nummber of lists isn't 2" << std::endl;
        }

        for (auto i = numberslists.begin(); i != numberslists.end(); ++i)
        {
            trim(*i);
            i->erase(std::unique(i->begin(), i->end(), [](char a, char b) { return a == ' ' && b == ' '; }),
                     i->end()); // replace "  " with " "
            std::vector<std::string> numbers = strSplit(*i, " ");

            std::vector<int> castednumbers = CastStringsToInt(numbers);

            if (i == numberslists.begin())
            {
                card.WinningCards = castednumbers;
            }
            else
            {
                card.YourCards = castednumbers;
            }
        }

        cards.push_back(card);
    }
    inputFile.close();
    return std::move(cards);
}

static unsigned int CalculatePointsFromCards(const std::vector<Card> &cards)
{
    unsigned int result = 0;

    for (auto x = cards.cbegin(); x != cards.cend(); ++x)
    {
        unsigned int CardOverlaps = 0;
        for (auto y = x->YourCards.cbegin(); y != x->YourCards.cend(); ++y)
        {
            if (std::find(x->WinningCards.cbegin(), x->WinningCards.cend(), *y) != std::end(x->WinningCards))
            {
                CardOverlaps++;
            }
        }

        if (CardOverlaps != 0)
        {
            result += std::pow(2, CardOverlaps - 1);
        }
    }
    return result;
}

int main()
{
    std::vector<Card> input = readFile();
    std::cout << "result: " << CalculatePointsFromCards(input) << std::endl;
}
