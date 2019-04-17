#ifndef __WORDTOKENLIZER_H__
#define __WORDTOKENLIZER_H__
#include "Tokenlizer.h"
#include <exception>
#include <unordered_map>

class WordTokenlizer : public Tokenlizer
{
private:
    static const std::unordered_map<std::string, std::string> dic;
    static int id(char c);
    static const int f[7][7];
    static const int startState;
    static const int finishState;
public:
    WordTokenlizer(const std::string& s) : Tokenlizer(s) {}
    bool nextToken(std::string& s) override;
    bool nextToken(std::string& type, std::string& token);
};

class LexicalError : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "Lexical Error";
    }
};

#endif
