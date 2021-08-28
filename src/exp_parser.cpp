#include "expression.h"
#include <map>

using namespace LL;
using std::string;
using std::map;

struct Operator_Property
{
	int priority;
	int operator_position;
	int parameter_count;
};
map<string, Operator_Property> operators
{
	{"ROOT",{-1,0,1}},
	{"+",{0,2,2}},
	{"++",{5,1,1}},
	{"-",{0,2,2}},
	{"--",{5,1,1}},
	{"*",{1,2,2}},
	{"/",{1,2,2}},
	{"%",{1,2,2}},
	{"%%",{5,3,1}},
	{"^",{2,2,2}},
	{"!",{4,3,1}},
	{"sqrt",{5,1,1}},
	{"abs",{5,1,1}},
	{"lg",{5,1,1}},
	{"ln",{5,1,1}},
	{"sin",{5,1,1}},
	{"cos",{5,1,1}},
	{"tan",{5,1,1}},
	{"arcsin",{5,1,1}},
	{"arccos",{5,1,1}},
	{"arctan",{5,1,1}},
	{"sinh",{5,1,1}},
	{"cosh",{5,1,1}},
	{"tanh",{5,1,1}},
	{"arsinh",{5,1,1}},
	{"arcosh",{5,1,1}},
	{"artanh",{5,1,1}},
	{"min",{3,1,2}},
	{"max",{3,1,2}},
	{"log",{3,1,2}}
};

void Expression::parser(const string& expression)
{
	Exp_Cells* cells = [&expression]() {
		Exp_Cells* cells_temp = new Exp_Cells;
		for (string::const_iterator iter = expression.begin(); iter < expression.end(); iter++)
		{
			string* str_temp = new string;
			if ('0' <= *iter && *iter <= '9')
			{
				do
				{
					*str_temp += *iter;
					iter++;
				} while ((iter != expression.end()) && (('0' <= *iter && *iter <= '9') || *iter == '.'));
				iter--;
			}
			else if (*iter == ',')
				continue;
			else if (('A' <= *iter && *iter <= 'Z') || ('a' <= *iter && *iter <= 'z'))
			{
				do
				{
					*str_temp += *iter;
					iter++;
				} while ((iter != expression.end()) && ((('A' <= *iter && *iter <= 'Z') || ('a' <= *iter && *iter <= 'z'))));
				iter--;
			}
			else
				*str_temp = *iter;
			cells_temp->push_back(str_temp);
		}
		return cells_temp;
	}();

	try
	{
		for (auto i : *cells)
		{
			if (('A' <= (*i)[0] && (*i)[0] <= 'Z') || ('a' <= (*i)[0] && (*i)[0] <= 'z'))
			{
				if (operators.find(*i) == operators.end())
				{
					string error = "unknown operator:" + *i;
					throw error.c_str();
				}
			}
		}
	}
	catch (const char* ERROR_INFORMATION)
	{
		throw ERROR_INFORMATION;
	}
}