#include "ExpressionAnalyzer.h"

const std::map<Object, std::map<Object, std::vector<Object>>> ExpressionAnalyzer::f = {
    {__expr,
     {{plus, {Plus, Expr}},
      {minus, {Plus, Expr}},
      {ident, {Expr}},
      {number, {Expr}},
      {lparen, {Expr}}}},
    {Expr,
     {{ident, {Term, expr}},
      {number, {Term, expr}},
      {lparen, {Term, expr}}}},
    {expr,
     {{plus, {Plus, Term, expr}},
      {minus, {Plus, Term, expr}},
      {rparen, {}},
      {__nuil, {}}}},
    {Term,
     {{ident, {Factor, term}},
      {number, {Factor, term}},
      {lparen, {Factor, term}}}},
    {term,
     {{plus, {}},
      {minus, {}},
      {times, {Multi, Factor, term}},
      {slash, {Multi, Factor, term}},
      {rparen, {}},
      {__nuil, {}}}},
    {Factor,
     {{ident, {Ident}},
      {number, {Ident}},
      {lparen, {lparen, __expr, rparen}}}},
    {Plus,
     {{plus, {plus}},
      {minus, {minus}}}},
    {Multi,
     {{times, {times}},
      {slash, {slash}}}},
    {Ident,
     {{ident, {ident}},
      {number, {number}}}}};

bool isTermial(Object obj)
{
    return obj < 9;
}

Object getObject(const std::string& s)
{
    if (s == "ident") return ident;
    if (s == "number") return number;
    if (s == "plus") return plus;
    if (s == "minus") return minus;
    if (s == "times") return times;
    if (s == "slash") return slash;
    if (s == "lparen") return lparen;
    if (s == "rparen") return rparen;
    throw NoSuchObjectException();
}

ExpressionException::ExpressionException(Object obj) { msg = (getErrorMessage(obj)); }

std::string ExpressionException::getErrorMessage(Object obj)
{
    std::string msg = "Unexpect ";
    switch (obj)
    {
    case ident:
        msg += "ident";
        break;
    case number:
        msg += "number";
        break;
    case plus:
        msg += "operator \"+\"";
        break;
    case minus:
        msg += "operator \"-\"";
        break;
    case times:
        msg += "operator \"*\"";
        break;
    case slash:
        msg += "operator \"/\"";
        break;
    case lparen:
        msg += "\"(\"";
        break;
    case rparen:
        msg += "\")\"";
        break;
    case __nuil:
        msg += "EOF";
        break;
    default:
        throw NoSuchObjectException();
        break;
    }
    msg.push_back('.');
    return msg;
}

std::vector<Object> ExpressionAnalyzer::getNext(Object current, Object type)
{
    auto t = f.find(current)->second;
    auto it = t.find(type);
    if (it == t.end()) throw ExpressionException(type);
    std::vector<Object> res = it->second;
    std::reverse(res.begin(), res.end());
    return res;
}

bool ExpressionAnalyzer::isValid(const std::vector<Object>& objects) const
{
    std::stack<Object> s;
    s.push(__nuil);
    s.push(__expr);
    int counter = 0;
    for (auto&& object : objects)
    {
        ++counter;
        while (!isTermial(s.top()))
        {
            try
            {
                auto cur = s.top();
                s.pop();
                auto t = getNext(cur, object);
                for (auto&& it : t) s.push(it);
            }
            catch (const std::exception& e)
            {
                std::cerr << counter << ':';
                std::cerr << e.what() << '\n';
                return false;
            }
        }
        if (s.top() != object)
        {
            std::cerr << counter << ':';
            std::cerr << ExpressionException::getErrorMessage(object) << '\n';
            return false;
        }
        s.pop();
    }
    return true;
}
