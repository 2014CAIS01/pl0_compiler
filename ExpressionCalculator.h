#ifndef __EXPRESSIONCALCULATOR_H__
#define __EXPRESSIONCALCULATOR_H__

#include <algorithm>
#include <cassert>
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

/**
 * SLR(1):
 * S' -> S      {print(S.val)}
 * S -> APE     {S.val:=P.val(A.val,E.val)}
 * S -> A       {S.val:=A.val}
 * A -> PT      {A.val:=P.val(T.val)}
 * E -> E'PT    {E.val:=P.val(E'.val,T.val)}
 * E -> T       {E.val:=T.val}
 * T -> T'MF    {T.val:=M.val(T'.val,F.val)}
 * T -> F       {T.val:=F.val}
 * F -> (S)     {F.val:=S.val}
 * F -> n       {F.val:=n.lexval}
 * P -> +       {P.val:=+.lexval}
 * P -> -       {P.val:=-.lexval}
 * M -> *       {M.val:=*.lexval}
 * M -> /       {M.val:=/.lexval}
*/

enum Object
{
    __nuil, // #
    lparen, // (
    rparen, // )
    plus,   // +
    minus,  // -
    times,  // *
    slash,  // /
    number, // n

    __expr, // S
    AExpr,  // A
    Expr,   // E
    Term,   // T
    Factor, // F
    Ident,  // I
    Plus,   // P
    Multi   // M
};

enum Action
{
    Accept,
    Shift,
    Reduce,
    Goto
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

Object getObject(const std::string& s);

typedef int TResult;

class ExpressionCalculator
{
private:
    // Gramma
    static const std::vector<std::pair<Object, std::vector<Object>>> production;
    static const std::vector<std::map<Object, std::pair<Action, int>>> f;
    static std::pair<Action, int> getNext(int current, Object type);
    static std::pair<Object, std::vector<Object>> getReduce(int id);

    // Semantic
    static TResult getLexval(Object obj, std::string);
    static TResult calc(TResult lhs, TResult op, TResult rhs);
    static TResult calc(TResult op, TResult rhs);

public:
    TResult calculate(const std::vector<std::pair<Object, std::string>>& objects) const;
};

#endif
