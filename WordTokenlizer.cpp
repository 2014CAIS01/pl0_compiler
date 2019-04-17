#include "WordTokenlizer.h"
#include <cassert>

const std::unordered_map<std::string,
                         std::string>
    WordTokenlizer::dic = {
        // 基本字
        {"begin", "beginsym"},
        {"call", "callsym"},
        {"const", "constsym"},
        {"do", "dosym"},
        {"end", "endsym"},
        {"if", "ifsym"},
        {"odd", "oddsym"},
        {"procedure", "proceduresym"},
        {"read", "readsym"},
        {"then", "thensym"},
        {"var", "varsym"},
        {"while", "whilesym"},
        {"write", "writesym"},
        // 标识符 state = 1
        // 常数   state = 2
        // 运算符
        {"+", "plus"},
        {"-", "minus"},
        {"*", "times"},
        {"/", "slash"},
        {"=", "eql"},
        {"#", "neq"},
        {"<", "lss"},
        {"<=", "leq"},
        {">", "gtr"},
        {">=", "geq"},
        {":=", "becomes"},
        // 界符
        {"(", "lparen"},
        {")", "rparen"},
        {",", "comma"},
        {";", "semicolon"},
        {".", "period"}};
const int WordTokenlizer::f[7][7]
    = {{1, 2, 3, 4, 5, 6, 0},
       {1, 1, -1, -1, -1, -1, -1},
       {-2, 2, -1, -1, -1, -1, -1},
       {-1, -1, -1, -1, -1, -1, -1},
       {-1, -1, -1, -1, 5, -1, -1},
       {-1, -1, -1, -1, -1, -1, -1},
       {-1, -1, -1, -1, 5, -1, -1}};
const int WordTokenlizer::startState = 0;
const int WordTokenlizer::finishState = 0x3e; // 0111110

int WordTokenlizer::id(char c)
{
    if (isspace(c)) return 6;
    if (isalpha(c)) return 0;
    if (isdigit(c)) return 1;
    if (c == '<' || c == '>') return 3;
    if (c == '=') return 4;
    if (c == ':') return 5;
    return 2;
}

bool WordTokenlizer::nextToken(std::string& token)
{
    throw std::exception();
}

bool WordTokenlizer::nextToken(std::string& type, std::string& token)
{
    while (index < s.length() && isspace(s[index])) index++;
    int currentState = 0;
    int index2 = index;
    while (index2 < s.length())
    {
        if (currentState < 0) throw LexicalError();
        int nextState = f[currentState][id(s[index2])];
        if (~nextState)
            currentState = nextState, index2++;
        else
            break;
    }
    if (index == index2) return false;
    if ((finishState >> currentState & 1) == 0)
        throw LexicalError();
    token = s.substr(index, index2 - index);
    index = index2;
    if (dic.count(token))
        type = dic.find(token)->second;
    else if (currentState == 1)
        type = "ident";
    else if (currentState == 2)
        type = "number";
    else
        throw LexicalError();
    return true;
}
