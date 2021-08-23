#include <iostream>
#include <string>
#include <vector>
using namespace std;

using Cells = vector<string*>;
Cells* separate(const string& expression)
{
	Cells* cells = new Cells;
	for (string::const_iterator iter = expression.begin(); iter < expression.end(); iter++)
	{
		string* temp = new string;
		if ('0' <= *iter && *iter <= '9')
		{
			do
			{
				*temp += *iter;
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
				*temp += *iter;
				iter++;
			} while ((iter != expression.end()) && ((('A' <= *iter && *iter <= 'Z') || ('a' <= *iter && *iter <= 'z'))));
			iter--;
		}
		else
			*temp = *iter;
		cells->push_back(temp);
	}
	return cells;
}

int main()
{
	while (true)
	{
		string temp;
		cin >> temp;
		Cells* cell = separate(temp);
		for (auto i = cell->begin(); i != cell->end(); i++)
		{
			cout << **i << " ";
		}
		cin.get();
	}
	return 0;
}