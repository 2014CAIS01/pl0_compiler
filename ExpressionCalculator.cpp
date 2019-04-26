#include "ExpressionCalculator.h"

const std::vector<std::pair<Object, std::vector<Object>>>
    ExpressionCalculator::production = {
        {__nuil, {Expr}},
        {Expr, {Expr, Plus, Term}},
        {Expr, {Plus, Term}},
        {Expr, {Term}},
        {Term, {Term, Multi, Factor}},
        {Term, {Factor}},
        {Factor, {lparen, Expr, rparen}},
        {Factor, {ident}},
        {Factor, {number}},
        {Plus, {plus}},
        {Plus, {minus}},
        {Multi, {times}},
        {Multi, {slash}}};

const std::vector<std::map<Object, std::pair<Action, int>>> ExpressionCalculator::f = {
    // 0
    {
        {lparen, {Shift, 1}},
        {plus, {Shift, 2}},
        {minus, {Shift, 3}},
        {ident, {Shift, 8}},
        {number, {Shift, 9}},
        {Expr, {Goto, 4}},
        {Term, {Goto, 7}},
        {Factor, {Goto, 5}},
        {Plus, {Goto, 6}}},
    // 1
    {
        {lparen, {Shift, 1}},
        {plus, {Shift, 2}},
        {minus, {Shift, 3}},
        {ident, {Shift, 8}},
        {number, {Shift, 9}},
        {Expr, {Goto, 10}},
        {Term, {Goto, 7}},
        {Factor, {Goto, 5}},
        {Plus, {Goto, 6}}},
    // 2
    {
        {lparen, {Reduce, 9}},
        {ident, {Reduce, 9}},
        {number, {Reduce, 9}},
    },
    // 3
    {
        {lparen, {Reduce, 10}},
        {number, {Reduce, 10}},
        {ident, {Reduce, 10}}},
    // 4
    {
        {plus, {Shift, 2}},
        {minus, {Shift, 3}},
        {__nuil, {Accept, 0}},
        {Plus, {Goto, 11}}},
    // 5
    {
        {rparen, {Reduce, 5}},
        {plus, {Reduce, 5}},
        {minus, {Reduce, 5}},
        {times, {Reduce, 5}},
        {slash, {Reduce, 5}},
        {__nuil, {Reduce, 5}}},
    // 6
    {
        {lparen, {Shift, 1}},
        {ident, {Shift, 8}},
        {number, {Shift, 9}},
        {Term, {Goto, 12}},
        {Factor, {Goto, 5}}},
    // 7
    {
        {rparen, {Reduce, 3}},
        {plus, {Reduce, 3}},
        {minus, {Reduce, 3}},
        {times, {Shift, 13}},
        {slash, {Shift, 14}},
        {__nuil, {Reduce, 3}},
        {Multi, {Goto, 15}}},
    // 8
    {
        {rparen, {Reduce, 7}},
        {plus, {Reduce, 7}},
        {minus, {Reduce, 7}},
        {times, {Reduce, 7}},
        {slash, {Reduce, 7}},
        {__nuil, {Reduce, 7}}},
    // 9
    {
        {rparen, {Reduce, 8}},
        {plus, {Reduce, 8}},
        {minus, {Reduce, 8}},
        {times, {Reduce, 8}},
        {slash, {Reduce, 8}},
        {__nuil, {Reduce, 8}}},
    // 10
    {
        {rparen, {Shift, 16}},
        {plus, {Shift, 2}},
        {minus, {Shift, 3}},
        {Plus, {Goto, 11}}},
    // 11
    {
        {lparen, {Shift, 1}},
        {ident, {Shift, 8}},
        {number, {Shift, 9}},
        {Term, {Goto, 17}},
        {Factor, {Goto, 5}}},
    // 12
    {
        {rparen, {Reduce, 2}},
        {plus, {Reduce, 2}},
        {minus, {Reduce, 2}},
        {times, {Shift, 13}},
        {slash, {Shift, 14}},
        {__nuil, {Reduce, 2}},
        {Multi, {Goto, 15}}},
    // 13
    {
        {lparen, {Reduce, 11}},
        {ident, {Reduce, 11}},
        {number, {Reduce, 11}},
    },
    // 14
    {
        {lparen, {Reduce, 12}},
        {ident, {Reduce, 12}},
        {number, {Reduce, 12}}},
    // 15
    {
        {lparen, {Shift, 1}},
        {ident, {Shift, 8}},
        {number, {Shift, 9}},
        {Factor, {Goto, 18}}},
    // 16
    {
        {rparen, {Reduce, 6}},
        {plus, {Reduce, 6}},
        {minus, {Reduce, 6}},
        {times, {Reduce, 6}},
        {slash, {Reduce, 6}},
        {__nuil, {Reduce, 6}}},
    // 17
    {
        {rparen, {Reduce, 1}},
        {plus, {Reduce, 1}},
        {minus, {Reduce, 1}},
        {times, {Shift, 13}},
        {slash, {Shift, 14}},
        {__nuil, {Reduce, 1}},
        {Multi, {Goto, 15}}},
    // 18
    {
        {rparen, {Reduce, 4}},
        {plus, {Reduce, 4}},
        {minus, {Reduce, 4}},
        {times, {Reduce, 4}},
        {slash, {Reduce, 4}},
        {__nuil, {Reduce, 4}}}};

Object getObject(const std::string& s)
{
    if (s == "number") return number;
    if (s == "ident") return ident;
    if (s == "plus") return plus;
    if (s == "minus") return minus;
    if (s == "times") return times;
    if (s == "slash") return slash;
    if (s == "lparen") return lparen;
    if (s == "rparen") return rparen;
    throw NoSuchObjectException();
}
std::ostream& operator<<(std::ostream& out, const Object& obj)
{
    switch (obj)
    {
    case plus:
        out << "+";
        break;
    case minus:
        out << "-";
        break;
    case times:
        out << "*";
        break;
    case slash:
        out << "/";
        break;
    default:
        break;
    }
}
std::ostream& operator<<(std::ostream& out, const Action& act)
{
    switch (act)
    {
    case Accept:
        out << "Accept";
        break;
    case Shift:
        out << "Shift";
        break;
    case Reduce:
        out << "Reduce";
        break;
    case Goto:
        out << "Goto";
        break;
    default:
        break;
    }
    return out;
}
void __printitem(const std::pair<TResult, std::string>& item)
{
    if (item.second == "")
        std::cout << item.first;
    else
        std::cout << item.second;
}

ExpressionException::ExpressionException(Object obj) { msg = (getErrorMessage(obj)); }

std::string ExpressionException::getErrorMessage(Object obj)
{
    std::string msg = "Unexpect ";
    switch (obj)
    {
    case number:
        msg += "number";
        break;
    case ident:
        msg += "ident";
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
        msg += "delimiter \"(\"";
        break;
    case rparen:
        msg += "delimiter \")\"";
        break;
    case __nuil:
        msg += "EOF";
        break;
    default:
        msg = "Unknown Error";
        break;
    }
    msg.push_back('.');
    return msg;
}

std::pair<Action, int> ExpressionCalculator::getNext(int current, Object type)
{
    auto it = f[current].find(type);
    if (it == f[current].end()) throw ExpressionException(type);
    return it->second;
}

std::pair<Object, std::vector<Object>> ExpressionCalculator::getReduce(int id)
{
    return production[id];
}

TResult ExpressionCalculator::getLexval(Object obj, std::string token)
{
    if (obj == number) return std::stoi(token);
    if (obj < number) return static_cast<TResult>(obj);
    return 0;
}

TResult ExpressionCalculator::calc(TResult lhs, TResult op, TResult rhs)
{
    if (op == plus) return lhs + rhs;
    if (op == minus) return lhs - rhs;
    if (op == times) return lhs * rhs;
    if (op == slash) return rhs ? lhs / rhs : 0;
    // :(
    assert(false);
}

TResult ExpressionCalculator::calc(TResult op, TResult rhs)
{
    if (op == plus) return +rhs;
    if (op == minus) return -rhs;
    // :(
    assert(false);
}

void ExpressionCalculator::print(Object op,
                                 std::pair<TResult, std::string> lhs,
                                 std::pair<TResult, std::string> rhs,
                                 std::pair<TResult, std::string> res)
{
    std::cout << '(' << op << ',';
    __printitem(lhs);
    std::cout << ',';
    __printitem(rhs);
    std::cout << ',';
    __printitem(res);
    std::cout << ')' << std::endl;
}

void ExpressionCalculator::print(Object op,
                                 std::pair<TResult, std::string> rhs,
                                 std::pair<TResult, std::string> res)
{
    std::cout << '(' << op << ',';
    std::cout << ' ' << ',';
    __printitem(rhs);
    std::cout << ',';
    __printitem(res);
    std::cout << ')' << std::endl;
}

TResult ExpressionCalculator::calculate(const std::vector<std::pair<Object, std::string>>& objects) const
{
    // state, token, result, id
    int counter = 0;
    std::stack<std::tuple<int, Object, std::pair<TResult, std::string>>> s;
    s.push(std::make_tuple(0, __nuil, std::make_pair(0, "")));
    for (auto&& [object, token] : objects)
    {
        for (;;)
        {
            auto action = getNext(std::get<0>(s.top()), object);
            // std::cerr << action.first << ' ' << action.second << std::endl;
            if (action.first == Shift)
            {
                s.push(std::make_tuple(action.second, object,
                                       std::make_pair(getLexval(object, token), token)));
                break;
            }
            else if (action.first == Reduce)
            {
                auto it = getReduce(action.second);
                auto reduce = it.second;
                std::reverse(reduce.begin(), reduce.end());
                static std::pair<TResult, std::string> buffer[3];
                static int sz;
                sz = 0;
                for (auto&& r : reduce)
                {
                    assert(r == std::get<1>(s.top()));
                    buffer[sz++] = std::get<2>(s.top());
                    s.pop();
                }
                std::pair<TResult, std::string> res;
                if (sz == 1)
                    res = buffer[0];
                else if (sz == 2)
                {
                    res = std::make_pair(calc(buffer[1].first, buffer[0].first), "t" + std::to_string(++counter));
                    print(static_cast<Object>(buffer[1].first), buffer[0], res);
                }
                else if (sz == 3)
                {
                    if (buffer[2].second == "(" && buffer[0].second == ")")
                        res = buffer[1];
                    else
                    {
                        res = std::make_pair(calc(buffer[2].first, buffer[1].first, buffer[0].first), "t" + std::to_string(++counter));
                        print(static_cast<Object>(buffer[1].first), buffer[2], buffer[0], res);
                    }
                }
                else //:(
                    assert(false);
                auto go = getNext(std::get<0>(s.top()), it.first);
                assert(go.first == Goto);
                // std::cerr << go.first << ' ' << go.second << std::endl;
                s.push(std::make_tuple(go.second, it.first, res));
            }
            else if (action.first == Accept)
                return std::get<2>(s.top()).first;
            else // :(
                assert(false);
        }
    }
    // ：(
    assert(false);
}
