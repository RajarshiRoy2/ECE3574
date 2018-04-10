#include "lexer.hpp"
#include <iostream>

using namespace std;
TokenList tokenize(istream & ins)
{
	TokenList tokens;
	char c;
	bool myerror = false;
	string temp;//string the thing
	size_t l = 1;
	int cou = 0;

	while (ins.get(c))
	{
		switch (c) 
		{
		case '\t':
			if (temp.empty() == false)
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			break;
		case '#':
			if (tokens.empty() == false)
			{
				if (tokens.back().type() == EOL)
				{
					while (c != '\n')
					{
						//cout <<"GH" <<c << endl;
						ins.get(c);
						if (ins.eof())
						{
							break;
						}
					}
					break;
				}
				else
				{
					tokens.emplace_back(EOL, l);
					while (c != '\n')
					{
					//	cout << "GH!!" << c << endl;
						ins.get(c);
						if (ins.eof())
							break;
					}
					break;
				}
			}
			else
			{
				while (c != '\n')
				{
					//cout << "GH@@" << c << endl;
					ins.get(c);

				}
				break;
			}
		case '\r'://empty line
			if (temp.empty() == false)
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			break;
		case ' ':
			if (temp.empty() == false)
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			break;
		case '\n':
			if (cou > 0)
			{
				myerror = true;
				break;
			}
			if (temp.empty() == false)
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}

			if (tokens.size() > 0)
			{
				tokens.emplace_back(EOL, l);
			}
			l++;
			break;
		case ',':
			if (temp.empty()==false) 
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			tokens.emplace_back(SEP, l);
			break;
		
		case '=':
			if (!temp.empty())
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			tokens.emplace_back(EQUAL, l);
			break;
		case '\"':
			if (!temp.empty())
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			tokens.emplace_back(STRING_DELIM, l);
			ins.get(c);
			while (c != '\"')
			{
				if (c == '\n')
				{
					myerror = true;
					break;
				}
				temp.push_back(c);
				ins.get(c);
			}
			if (myerror==false)
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
				tokens.emplace_back(STRING_DELIM, l);
			}
			break;
		case '(':
			if (temp.empty() == false)
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			cou++;
			tokens.emplace_back(OPEN_PAREN, l);
			break;
		case ')':
			if (temp.empty()==false) 
			{
				tokens.emplace_back(STRING, l, temp);
				temp.clear();
			}
			cou--;
			tokens.emplace_back(CLOSE_PAREN, l);
			break;
		default:
			temp.push_back(c);
			break;
		}
		if (cou < 0)
			myerror = true;
		if (myerror)		
			break;
	}
	//this order is important 
	if (cou > 0)
	{
		myerror = true;
	}
	if (temp.empty()==false && myerror==false)
	{
		tokens.emplace_back(STRING, l, temp);
		temp.clear();
		tokens.emplace_back(EOL, l);
	}
	if (tokens.size() != 0 && tokens.back().type() != EOL)
		tokens.emplace_back(EOL, l);

	if (myerror==true)
		tokens.emplace_back(ERROR, l, "Error: Check the file...");
	return tokens;
}