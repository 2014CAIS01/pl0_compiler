#include "IndentTokenlizer.h"

bool IndentTokenlizer::nextToken(std::string& token)
{
    while (index < s.length() && isspace(s[index])) index++;
    while (index < s.length())
    {
        if (isalpha(s[index]))
        {
            int index2 = index;
            while (index2 < s.length() && isalnum(s[index2])) index2++;
            token = s.substr(index, index2 - index);
            index = index2;
            if (!sys.count(token)) return true;
        }
        else
            index++;
    }
    return false;
}
