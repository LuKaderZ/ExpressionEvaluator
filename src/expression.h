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

	};
}