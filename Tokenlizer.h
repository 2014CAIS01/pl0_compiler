#ifndef __TOKENLIZER_H__
#define __TOKENLIZER_H__
#include <string>

class Tokenlizer
{
protected:
    std::string s;
    int index;

public:
    Tokenlizer(const std::string& s) : s(s), index(0) {}
    void reset() { index = 0; }
    virtual bool nextToken(std::string& token) = 0;
};

#endif
