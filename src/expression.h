#pragma once
#include <string>
#include <vector>

namespace LL
{
	using Exp_Cells = std::vector<std::string*>;

	class Expression
	{
	public:
		void parser(const std::string& expression);
	private:
		struct node
		{
			node* father = nullptr;

			bool is_operator = true;
			std::string data = "";
			int parameter_count = 0;

			std::vector<node*> children;
		};
		node* ROOT;

		node* to_tree(Exp_Cells* cells);
	};
}