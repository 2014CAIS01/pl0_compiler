#include "IndentTokenlizer.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

const char* USAGE = "exp1 inputfile outputfile";

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
    std::map<std::string, int> counter;
    while (std::getline(fin, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), [](int c) { return tolower(c); });
        IndentTokenlizer tokenlizer(line);
        std::string token;
        while (tokenlizer.nextToken(token)) counter[token]++;
    }
    for (auto&& [token, count] : counter)
        fout << '(' << token << ':' << count << ')' << std::endl;
}
