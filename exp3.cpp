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
    while (std::getline(std::cin, line))
    {
        linenum++;
        std::vector<std::pair<std::string, std::string>> words;
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
        std::vector<std::pair<Object, std::string>> objects;
        for (auto&& [type, token] : words)
        {
            std::cerr << '(';
            std::cerr << std::setiosflags(std::ios::left) << std::setw(10);
            std::cerr << type << ',';
            std::cerr << token << ')' << std::endl;
            objects.emplace_back(getObject(type), token);
        }
        objects.emplace_back(__nuil, "");
        ExpressionAnalyzer analyzer;
        std::cout << linenum << ":";
        if (analyzer.isValid(objects))
            std::cout << "OK" << std::endl;
    }
}
