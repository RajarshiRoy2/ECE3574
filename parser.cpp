#include <sstream>
#include <string>
#include <assert.h>
#include <fstream>
#include "parser.hpp"

using namespace std;

Parser::Parser(): tl(TokenList()), it(tl.begin()){}

Parser::~Parser(){}

bool Parser::tokens(istream & ins)
{
	tl = ::tokenize(ins);
	it = tl.begin();
	return tl.back().type() != ERROR;
}

bool Parser::tokens(string & str)
{
	istringstream iss(str);
	return tokens(iss);
}

bool Parser::tokens(const string& file_name)
{
	ifstream i(file_name);
	return tokens(i);
}

bool Parser::check_a(char c) { return (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (c == '_'); }
bool Parser::check_d(char c) { return (('0' <= c) && (c <= '9')) || (c == '-') || (c == '+'); }

bool Parser::type_check()
{
	if (it->type() == STRING && (it->value() == ".data" || it->value() == ".text"))
	{
		return true;
	}
	return false;
}

const string Parser::my_error()
{
	if (it == tl.end())
	{
		//cout << "error1" << endl;
		return "";
	}
	string h;
	while (it->type() != EOL)
	{
		h = h+" "+it->value() ;
		it++;
	}
	//cout << "uiui" << endl;
	return "Error:" + to_string(it->line()) +": " +h + "\n";
}

bool Parser::decleration()
{
	auto t= it;
	if (constant()==true)
	{
		if (it->type() != EOL)
		{
			it = t;
			return false;
		}
	}
	else if (label() == true)
	{
		if (layout2() == true)
		{
			if (it->type() != EOL)
			{
				it = t;
				return false;
			}
		}
		else if (it->type() != EOL)
		{
			it = t;
			return false;
		}
	}
	else if (layout2() == true)
	{
		if (it->type() != EOL)
		{
			it = t;
			return false;
		}
	}
	else
	{
		it = t;
		return false;
	}
	it++;
	return true;
}

bool Parser::label()
{
	auto begin = it;
	size_t i = 0;

	if (it->type() != STRING)
	{
		it = begin;
		return false;
	}

	if (check_a(it->value()[0])==false)
	{
		it = begin;
		return false;
	}
	for (i = 0; i < (it->value().length() - 1); ++i)
	{
		if (check_d(it->value()[i])==false && check_a(it->value()[i])==false)
		{
			it = begin;
			return false;
		}
	}

	if (it->value()[it->value().length() - 1] != ':')
	{
		it = begin;
		return false;
	}
	labels.emplace(it->value());
	++it;
	return true;
}

bool Parser::constant()
{
	auto begin = it;
	size_t i = 0;
	name.emplace(it->value());
	if (it->type() != STRING)
	{
		it = begin;
		name.erase(it->value());
		return false;
	}
	if (check_a(it->value()[0]) == false)
	{
		it = begin;
		name.erase(it->value());
		return false;
	}
	for (i = 1; i < (it->value().length()); ++i)
	{
		if (check_d(it->value()[i]) == false && check_a(it->value()[i]) == false)
		{
			it = begin;
			name.erase(it->value());
			return false;
		}
	}
	if ((++it)->type() != EQUAL)
	{
		it = begin;
		name.erase(it->value());
		return false;
	}
	++it;
	if (integer() == false)
	{
		//cout << "error14" << endl;
		it = begin;
		name.erase(it->value());
		return false;
	}
	return true;
}

bool Parser::layout2()
{
	auto begin = it;
	string temp = it->value();
	if (intlayout() == true)
	{
		if (integer() == true)
		{
			if (temp == ".space"||temp == ".word" )
			{
				it--;
				if (space_check()==false)
				{
					it = begin;
					return false;
				}
			}
			else if (temp == ".half")
			{
				it--;
				if (check16()==false)
				{
					it = begin;
					return false;
				}
			}
			else if (temp == ".byte")
			{
				it--;
				if (byte_check()==false)
				{
					it = begin;
					return false;
				}
			}
		}
		else if (name.find(it->value()) != name.end())
		{
			it++;
		}
		else
		{
			it = begin;
			return false;
		}
		if (it->type() != EOL)
		{
			while (it->type() != EOL)
			{
				if ((it)->type() != SEP)
				{
					it = begin;
					return false;
				}
				++it;
				if (integer()==true)
				{
					if (temp == ".word" || temp == ".space")
					{
						it--;
						if (!space_check())
						{
							it = begin;
							return false;
						}
					}
					else if (temp == ".half")
					{
						it--;
						if (!check16())
						{
							it = begin;
							return false;
						}
					}
					else if (temp == ".byte")
					{
						it--;
						if (!byte_check())
						{
							it = begin;
							return false;
						}
					}
				}
				else if (name.find(it->value()) != name.end())
				{
					it++;
				}
				else
				{
					it = begin;
					return false;
				}
			}
		}
	}
	else if (layout()==true)
	{
		if (string_check() == false)
		{
			it = begin;
			return false;
		}
		return true;
	}
	else 
	{
		it = begin;
		return false;
	}
	return true;
}

bool Parser::string_check()
{
	auto begin = it;
	if (it->type() != STRING_DELIM)
	{
		it = begin;
		return false;
	}
	if ((++it)->type() != STRING)
	{
		it = begin;
		return false;
	}
	if ((++it)->type() != STRING_DELIM)
	{
		it = begin;
		return false;
	}
	++it;
	return true;
}

bool Parser::integer()
{
	auto begin = it;
	size_t i = 0;
	
	if (it->type() != STRING)
	{
		it = begin;
		return false;
	}
	//cout << it->value();

	for (i = 0; i < it->value().length(); i++)
	{
		if (check_d(it->value()[i])==false)
		{
			it = begin;
			return false;
		}
	}
	++it;
	return true;
}

bool Parser::layout()
{
	auto begin = it;
	if (it->type() != STRING)
	{
		it = begin;
		return false;
	}
	if (it->value() != ".ascii" && it->value() != ".asciiz")
	{
		it = begin;
		return false;
	}
	++it;
	return true;
}

bool Parser::intlayout()
{
	auto begin = it;
	if (it->type() != STRING)
	{
		it = begin;
		return false;
	}
	if (it->value() != ".word" && it->value() != ".half" &&it->value() != ".byte" && it->value() != ".space")
	{
		it = begin;
		return false;
	}
	++it;
	return true;

}

bool Parser::oprrssmm()
{
	unordered_set<string> instrs = { "lb","la","sw","sh","sb","lw","lh" };
	auto begin = it;
	if (instrs.find(it->value()) == instrs.end())
	{
		it = begin;
		return false;
	}
	it++;
	if (register_check()==false)
	{
		it = begin;
		return false;
	}
	if (it->type() != SEP)
	{
		it = begin;
		return false;
	}
	it++;
	if (mememorycheck()==false)
	{
		it = begin;
		return false;
	}
	return true;

}

bool Parser::check16()
{
	signed long long int ull=0;
	unsigned long long int ull1=0;
	if (it->value()[0] == '-' || it->value()[0] == '+')
	{
		stringstream geek(it->value());
		geek >> ull;
		if (ull >(signed)32767 || ull < (signed)-32768)
		{
			//cout << "error35" << endl;
			return false;
		}
	}
	else 
	{
		stringstream geek1(it->value());
		geek1 >> ull1;
		if (ull > 65535)
		{

			return false;
		}
	}
	it++;
	return true;

}
bool Parser::space_check()
{
	signed long long int ull=0;
	unsigned long long int ull1=0;
	
	if (it->value()[0] == '-' || it->value()[0] == '+')
	{
		stringstream geek(it->value());
		geek >> ull;
		//cout << ull << endl;
		if (ull > (signed)2147483647 || ull <(signed) -2147483648)
		{
			//cout << ull << endl;
			//cout << "error37" << endl;
			return false;
		}
	}
	else 
	{
		stringstream geek1(it->value());
		geek1 >> ull1;
		if (ull1 > 4294967295) 
		{
			
			//cout << "error38" << endl;
			return false;
		}
	}
	it++;
	return true;
}

bool Parser::byte_check()
{
	signed long long int ull=0;
	unsigned long long int ull1=0;
	if (it->value()[0] == '-' || it->value()[0] == '+')
	{
		stringstream geek(it->value());
		geek >> ull;
		if (ull > (signed)127 || ull <(signed)-128)
		{
			//cout << "error39" << endl;
			return false;
		}
	}
	else 
	{
		stringstream geek1(it->value());
		geek1 >> ull1;
		if (ull1 > 255)
		{
			//cout << "error40" << endl;
			return false;
		}
	}
	it++;
	return true;
}

bool Parser::text()
{
	auto begin = it;
	if (it->type() == EOL)
	{
		//cout << "good" << endl;
		it++;
		return true;
	}
	else if (label() == true)
	{
		if (it->type() != EOL)
		{
			if (ops2() == false)
			{
				it = begin;
				return false;
			}
		}
	}
	else if (ops2() == false)
	{
		it = begin;
		return false;
	}
	else if (it->type() == OPEN_PAREN)//for offset
	{
		it++;
			it++;
			if (name.find(it->value()) != name.end())
			{
				it = begin;
				return false;
			}
		
		it++;
		if (it->type() != EOL)//problem here
		{
			it = begin;
			return false;
		}
		return true;

	}
 if (it->type() != EOL)//problem here
	{
	 it = begin;
	 return false;
	}
	it++;
	return true;

}

bool Parser::immediate()
{
	if (name.find(it->value()) != name.end())
	{
		//cout << "good2" << endl;
		it++;
		return true;
	}
	else if (integer() == true)
	{
		//cout << "good3" << endl;
		return true;
	}
	//cout << "error48" << endl;
	return false;
}
bool Parser::source()
{
	if (register_check() == false && immediate()==false)
	{
		//cout << "error49" << endl;
		return false;
	}
	return true;
}

bool Parser::srss()
{
	auto g = it;
	unordered_set<string> instrs = { "add","addu","sub","subu","mul","mulo","mulou","and","nor","or","xor","rem","remu","div","divu" };
	if (instrs.find(it->value()) == instrs.end())
	{
		it = g;
		return false;
	}
	it++;
	if (register_check()==false)
	{
		it = g;
		return false;
	}
	if (it->type() != SEP)
	{
		it = g;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = g;
		return false;
	}
	if (it->type() != SEP)
	{
		it = g;
		return false;
	}
	it++;
	if (source() == false)
	{
		it = g;
		return false;
	}
	return true;
}

bool Parser::opress()
{
	unordered_set<string> instrs = { "mfhi","mflo","mthi","mtlo" };
	auto begin = it;
	if (instrs.find(it->value()) == instrs.end())
	{
		it = begin;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = begin;
		return false;
	}
	return true;
}

bool Parser::opst()
{
	unordered_set<string>instrs = { "mult","multu","abs","neg","negu","move","div","divu" };
	auto begin = it;
	if (instrs.find(it->value()) == instrs.end())
	{
		it = begin;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = begin;
		return false;
	}
	if (it->type() != SEP)
	{
		it = begin;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = begin;
		return false;
	}
	return true;
}

bool Parser::oprsss()
{
	unordered_set<string> instrs = { "not" };
	auto u = it;
	if (instrs.find(it->value()) == instrs.end())
	{
		it = u;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = u;
		return false;
	}
	if (it->type() != SEP)
	{
		it = u;
		return false;
	}
	it++;
	if (source() == false)
	{
		it = u;
		return false;
	}
	return true;

}

bool Parser::opii()
{
	unordered_set<string> instrs = { "j" };
	auto e = it;
	if (instrs.find(it->value()) == instrs.end())
	{
	it = e;
	return false;
	}
	it++;
	if (label_test() == false)
	{
		it = e;
		return false;
	}

	return true;
}

bool Parser::label_test()
{

	auto d = it;
	size_t i = 0;

	if (it->type() != STRING)
	{
		it = d;
		return false;
	}

	if (check_a(it->value()[0]) == false)
	{
		it = d;
		return false;
	}
	for (i = 0; i < (it->value().length()); ++i)
	{
		if (check_d(it->value()[i]) == false && check_a(it->value()[i]) == false)
		{
			it = d;
			return false;
		}
	}
	labels.emplace(it->value());
	++it;
	return true;
}

bool Parser::open()
{
	unordered_set<string> oprsssl = { "beq","bne","blt","ble","bgt","bge" };
	auto w = it;
	if (oprsssl.find(it->value()) == oprsssl.end())
	{
		it = w;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = w;
		return false;
	}
	if (it->type() != SEP)
	{
		it = w;
		return false;
	}
	it++;
	if (source() == false)
	{
		it = w;
		return false;
	}
	if (it->type() != SEP)
	{
		//cout << "error76" << endl;
		it = w;
		return false;
	}
	it++;
	if (label_test() == false)
	{
	//	cout << "error77" << endl;
		it = w;
		return false;
	}
	return true;
	
}
bool Parser::li()
{
	auto n = it;
	if (it->value() != "li")
	{
		it = n;
		return false;
	}
	it++;
	if (register_check() == false)
	{
		it = n;
		return false;
	}
	if (it->type() != SEP)
	{
		it = n;
		return false;
	}
	it++;
	if (immediate() == false)
	{
		it = n;
		return false;
	}
	return true;
}

bool Parser::ops2()
{
	auto q = it;
	if (it->value() == "nop")
	{
		it++;
	}
	else if (li() == false && oprrssmm() == false && opress() == false && srss() == false &&
		oprsss() == false && opst() == false && opii() == false && open() == false)
	{
		it = q;
		return false;
	}
	
	return true;
}

bool Parser::register_check()
{
	unordered_set<string> k = { "$0","$1","$2","$3","$4","$5","$6","$7",
		"$8","$9","$10","$11","$12","$13","$14","$15","$16","$17","$18","$19",
		"$20","$21","$22","$23","$24","$25","$26","$27","$28","$29","$30","$31","$zero",
		"$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6",
		"$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9" ,"$k0","$k1","$gp","$sp","$fp","$ra" };
	bool ip = true;
	for (unsigned int i = 0; i < it->value().length(); i++)
	{
		if (isdigit(it->value()[i]) == false)
		{
			ip = false;
			break;
		}
	}
	if (k.find(it->value()) == k.end() && ip == false)
	{
		//cout << "alex" << it->value() << endl;
		//cout << "error83" << endl;
		return false;
	}
	it++;
	return true;
}

bool Parser::mememorycheck()
{
	auto q1 = it;
	//cout << "Rajarshi" << it->value() << endl;
	if (register_check() == true)
	{
		return true;
	}
	else
	{
		if (integer() == true)
		{
			it--;
			if (stoi(it->value()) < 0 || space_check() == false)
			{
			//	cout << "OPOP" << it->value() << endl;
			//	cout << "error79" << endl;
				it = q1;
				return false;
			}
		}
		if (label_test() == true)
		{
		//	cout << "good3" << endl;
			return true;
		}
		if (it->type() != OPEN_PAREN)
		{
		//	cout << "error80" << endl;
			it = q1;
			return false;
		}
		++it;
		if (register_check() == false)
		{
		//	cout << "OPOP!!" << it->value() << endl;
		//	cout << "error81" << endl;
			it = q1;
			return false;
		}
		if (it->type() != CLOSE_PAREN)
		{
		//	cout << "error82" << endl;
			it = q1;
			return false;
		}
		it++;
	}
	return true;
}

bool Parser::file(const string & file_name)
{
	if (tokens(file_name) == false)
	{
	//	cout << "error84" << endl;
		return false;
	}
	//auto q1 = it;
	while (it != tl.end())
	{
		if (it->value() == ".text")
		{

			if ((++it)->type() != EOL)
			{
		//		cout << "error85" << endl;
				return false;
			}
			it++;
			while (it != tl.end() && type_check() == false)
			{
				if (!text())
				{
			//		cout << "error86" <<it->value()<< endl;
					return false;
				}
			}
		}
		else if (it->value() == ".data")
		{
			it++;
			if (it->type() != EOL)
			{
			//	cout << "error87" << endl;
				return false;
			}
			it++;
			while (it != tl.end() && type_check() == false)
			{
				if (it->type() == EOL)
				{
					it++;
				}
				else if (decleration() == false)
				{
			//		cout << "error88" << endl;
					return false;
				}
			}
		}
		else
		{
		//	cout << "error89" << endl;
			return false;
		}
	}
	return true;

}

bool Parser::file()
{
	while (it != tl.end())
	{
		if (it->value() == ".text")
		{

			if ((++it)->type() != EOL)
			{
			//	cout << "error90" << endl;
				return false;
			}
			it++;
			while (it != tl.end() && type_check() == false)
			{
				if (text() == false)
				{
			//		cout << "error91" << endl;
					return false;
				}
			}
		}
		else if (it->value() == ".data")
		{
			it++;
			if (it->type() != EOL)
			{
			//	cout << "error92" << endl;
				return false;
			}
			it++;
			while (it != tl.end() && type_check() == false)
			{
				if (it->type() == EOL)
				{
					it++;
				}
				else if (!decleration())
				{
			//		cout << "error93" << endl;
					return false;
				}
			}
		}
		else
		{
		//	cout << "error94" << endl;
			return false;
		}
	}
	return true;
}
