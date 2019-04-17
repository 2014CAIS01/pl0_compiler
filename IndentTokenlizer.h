#ifndef __INDENTTOKENLIZER_H__
#define __INDENTTOKENLIZER_H__
#include "Tokenlizer.h"
#include <unordered_set>

const std::unordered_set<std::string> sys = {"begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"};

class IndentTokenlizer : public Tokenlizer
{
public:
    IndentTokenlizer(const std::string& s) : Tokenlizer(s) {}
    bool nextToken(std::string& s) override;
};

#endif
