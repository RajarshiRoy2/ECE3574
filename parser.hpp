#pragma once
#include "lexer.hpp"
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Parser 
{
public:
	Parser();
	~Parser();
	bool tokens(istream & ins);
	bool tokens(string & str);
	bool tokens(const string & file_name);
	const string my_error();
	bool file(const string & file_name);
	bool immediate();
	bool source();
	bool open();

	bool opii();
	bool srss();
	bool opst();

	bool oprsss();
	bool opress();
	bool oprrssmm();
	bool label_test();
	bool intlayout();
	bool layout();
	bool integer();

	bool string_check();
	bool layout2();
	bool label();
	bool constant();
	bool decleration();
	bool check16();
	bool space_check();

	bool byte_check();
	bool text();
	bool ops2();
	bool li();
	bool mememorycheck();

	bool register_check();
	bool file();
private:
	bool check_a(char c);
	bool check_d(char c);
	bool type_check();
	TokenList tl;
	TokenList::iterator it;
	unordered_set<string> labels;
	unordered_set<string> name;
};
