#include "expression.h"

using namespace LL;
using std::string;

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
}