#include <fstream>
#include <string>
#include <vector>
#include <iostream>


enum class tokens
{
	_return,
	int_lit,
	semi_colon
};

class tokenclass
{
public:
	tokens token;
	std::string value;
};


int main(int argc, char* argv[])
{
	std::fstream file{ argv[1], std::fstream::in };

	std::vector<char> a{};
	std::vector<std::string> b{};

	char c;

	int i = 0;
	while (file >> std::noskipws >> c)
	{
		a.push_back(c);
		i++;
	}
	file.close();

	std::string buf;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != ' ' && a[i] != ';' && a[i] != '\n')
		{
			buf.push_back(a[i]);
		}
		else if (a[i] == ';')
		{
			b.push_back(buf);
			b.push_back(";");
			buf = "";
		}
		else {
			b.push_back(buf);
			buf = "";
		}
	}

	if (buf != "") // if buffer not empty
	{
		b.push_back(buf);
	}

	for (int i = 0; i < b.size(); i++)
	{
		if (b[i] == "")
		{
			b.erase(b.begin() + i);
		}
	}

	std::vector<tokenclass> tokens{};

	tokens.resize(b.size());

	for (int i = 0; i < b.size(); i++)
	{
		if (std::isalpha(b[i][0]) && b[i] == "return")
		{
			tokens[i].token = tokens::_return;
			tokens[i].value = b[i];
		}
		else if (std::isalnum(b[i][0]))
		{
			tokens[i].token = tokens::int_lit;
			tokens[i].value = b[i];
		}
		else if (b[i] == ";")
		{
			tokens[i].token = tokens::semi_colon;
			tokens[i].value = b[i];
		}
	}

	for (int i = 0; i < b.size(); i++)
	{
		if (tokens[i].token == tokens::_return)
		{
			std::cout << "{ " << tokens[i].value << " }" << " = _RETURN" << "\n";
		}
		if (tokens[i].token == tokens::int_lit)
		{
			std::cout << "{ " << tokens[i].value << " }" << " = INT_LIT" << "\n";
		}
		if (tokens[i].token == tokens::semi_colon)
		{
			std::cout << "{ " << tokens[i].value << " }" << " = SEMI_COLON" << "\n";
		}
	}

	return 0;
}
