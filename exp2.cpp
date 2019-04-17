#include "WordTokenlizer.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const char* USAGE = "exp2 inputfile outputfile";

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        puts(USAGE);
        return 0;
    }
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    std::string line;
    int linenum = 0;
    std::vector<std::pair<std::string, std::string>> words;
    while (std::getline(fin, line))
    {
        ++linenum;
        std::transform(line.begin(), line.end(), line.begin(), [](int c) { return tolower(c); });
        WordTokenlizer tokenlizer(line);
        std::string type, token;
        try
        {
            while (tokenlizer.nextToken(type, token)) words.emplace_back(type, token);
        }
        catch (const std::exception& e)
        {
            fout << e.what() << " on line" << linenum << '.' << std::endl;
        }
    }
    for (auto&& [type, token] : words)
    {
        fout << '(';
        fout << std::setiosflags(std::ios::left) << std::setw(10);
        fout << type << ',';
        fout << token << ')' << std::endl;
    }
}
