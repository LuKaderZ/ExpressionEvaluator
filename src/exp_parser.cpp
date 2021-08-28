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

Expression::node* Expression::to_tree(Exp_Cells* cells)
{
	if (cells->empty())
		return nullptr;

	node* ROOT = new node;
	ROOT->data = "ROOT";
	ROOT->father = ROOT;
	ROOT->parameter_count = 1;

	auto get_priority = [](const string& str) {return operators.find(str)->second.priority; };
	auto get_operator_position = [](const string& str) {return operators.find(str)->second.operator_position; };
	auto get_parameter_count = [](const string& str) {return operators.find(str)->second.parameter_count; };

	node* current_father = ROOT;
	for (Exp_Cells::const_iterator iter = cells->begin(); iter != cells->end(); iter++)
	{
		node* temp = new node;
		if (**iter == "SKIP")
			continue;
		if ('0' <= (**iter)[0] && (**iter)[0] <= '9')
		{
			temp->is_operator = false;
			temp->data = **iter;

			temp->father = current_father;
			current_father->children.push_back(temp);
		}
		else if (**iter == "(")
		{
			delete temp;
			iter++;
			Exp_Cells* new_tokens = new Exp_Cells;
			int Left_bracket = 0;
			while (true)
			{
				if (**iter == "(")
					Left_bracket++;
				else if (**iter == ")")
					Left_bracket--;
				if (Left_bracket == -1)
				{
					temp = to_tree(new_tokens);
					delete new_tokens;
					for (auto i : temp->children)
					{
						current_father->children.push_back(i);
						i->father = current_father;
					}
					delete temp;
					break;
				}
				else
					new_tokens->push_back(*iter);
				iter++;
			}
			continue;
		}
		else if (get_priority(**iter) == 3 || get_priority(**iter) == 5)
		{
			temp->father = current_father;
			current_father->children.push_back(temp);
			temp->data = **iter;
			temp->parameter_count = get_parameter_count(**iter);
			current_father = temp;
		}
		else
		{
			if ((current_father->data == "ROOT") && current_father->children.size() == 0)
			{
				temp->father = current_father;
				temp->data = **iter;
				temp->parameter_count = get_parameter_count(**iter);
				current_father->children.push_back(temp);
			}
			else
			{
				if (get_priority(**iter) > get_priority(current_father->data))
				{
					temp->father = current_father;
					temp->data = **iter;
					temp->parameter_count = get_parameter_count(**iter);
					switch (get_operator_position(**iter))
					{
					case 2:
					case 3:
						temp->children.push_back(current_father->children.back());
						current_father->children.back()->father = temp;
						current_father->children.pop_back();
						current_father->children.push_back(temp);
						break;
					}
				}
				else
				{
					temp->father = current_father->father;
					temp->data = **iter;
					temp->parameter_count = get_parameter_count(**iter);
					temp->children.push_back(current_father);
					current_father->father->children.pop_back();
					current_father->father->children.push_back(temp);
					current_father->father = temp;
				}
			}
			current_father = temp;
		}

		if (current_father->children.size() == current_father->parameter_count)
			current_father = current_father->father;
	}

	return ROOT;
}

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

	ROOT = to_tree(cells);
}