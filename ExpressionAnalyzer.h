#ifndef __EXPRESSIONANALYZER_H__
#define __EXPRESSIONANALYZER_H__
#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

/**
 * BNF: 
 * expr -> [_plus] term {_plus term}
 * term -> factor {_times factor}
 * factor -> ident | number | lparen _expr rparen
 * _plus -> plus | minus
 * _times -> times | slash
*/

/*
 * LL(1):
 * e -> PE | E
 * E -> TE'
 * E' -> PTE' | #
 * T -> FT'
 * T' -> MFT' | #
 * F -> I | (e)
 * P -> + | -
 * M -> * | /
 * I -> i | n
*/

enum Object
{
    __nuil, // #
    ident,  // i
    number, // n
    plus,   // +
    minus,  // -
    times,  // *
    slash,  // /
    lparen, // (
    rparen, // )

    __expr, // e
    Expr,   // E
    expr,   // E'
    Term,   // T
    term,   // T'
    Factor, // F
    factor, // F'
    Plus,   // P
    Multi,  // M
    Ident,  // I

};

class NoSuchObjectException : public std::exception
{
public:
    const char* what() const noexcept
    {
        return "No Such Object";
    }
};

class ExpressionException : public std::exception
{
private:
    std::string msg;

public:
    ExpressionException(Object obj);
    static std::string getErrorMessage(Object object);
    const char* what() const noexcept
    {
        return msg.c_str();
    }
};

bool isTermial(Object obj);
Object getObject(const std::string& s);

class ExpressionAnalyzer
{
private:
    static const std::map<Object, std::map<Object, std::vector<Object>>> f;
    static std::vector<Object> getNext(Object current, Object type);

public:
    bool isValid(const std::vector<std::pair<Object, std::string>>& objects) const;
};

#endif
