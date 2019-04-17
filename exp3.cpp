#include "ExpressionAnalyzer.h"
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
    int linenum = 0;
    std::vector<std::pair<std::string, std::string>> words;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), [](int c) { return tolower(c); });
    WordTokenlizer tokenlizer(line);
    std::string type, token;
    try
    {
        while (tokenlizer.nextToken(type, token)) words.emplace_back(type, token);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    std::vector<Object> objects;
    for (auto&& [type, token] : words)
    {
        std::cout << '(';
        std::cout << std::setiosflags(std::ios::left) << std::setw(10);
        std::cout << type << ',';
        std::cout << token << ')' << std::endl;
        objects.push_back(getObject(type));
    }
    objects.push_back(__nuil);
    ExpressionAnalyzer analyzer;
    if (analyzer.isValid(objects))
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail" << std::endl;
}
