#include "ExpressionCalculator.h"
#include "WordTokenlizer.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::vector<std::pair<Object, std::string>> objects;
        std::transform(line.begin(), line.end(), line.begin(), [](int c) { return tolower(c); });
        WordTokenlizer tokenlizer(line);
        std::string type, token;
        try
        {
            while (tokenlizer.nextToken(type, token)) objects.emplace_back(getObject(type), token);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            continue;
        }
        objects.emplace_back(__nuil, "");
        ExpressionCalculator calculator;
        try
        {
            std::cout << calculator.calculate(objects) << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
