#include "VirtualMachine.hpp"
#include <sstream>
#include<iostream>


VirtualMachine::VirtualMachine()
{
	vector<unsigned char> memory;
	map <string, int> index_intrs;
	status = "";
	map <string, int> constants;
	map<string, int> labels;
	line2=0;
}

VirtualMachine::~VirtualMachine()
{
	
	memory.clear();
	vector<unsigned char>().swap(memory);
	index_intrs.clear();
	constants.clear();
	labels.clear();
	status.clear();

}

void VirtualMachine::setting_data_values(TokenList tokens)
{
	
	auto it = tokens.begin();
	if (it->value() == ".data")
	{
		it++;
		if (it->type() == EOL)
		{
			it++;
		}
	}
	bool constant = false;
	while (it != tokens.end())
	{
		////cout << "IOP" << endl;
		while (it->type() != EOL)
		{
			it++;
			if (it->type() == EQUAL)
			{
				////cout << "yui" << endl;
				constant = true;
				it--;
			}
			else
			{
			//	//cout << "yui2" << endl;
				constant = false;
				it--;
			}
			if (constant == false)
			{
				string variable = "";
			//	//cout << "yui22!!" << endl;
				if (it->value() != ".word"&&it->value() != ".byte"&&it->value() != ".half"&&it->value() != ".space"&&it->value() != ".ascii"&&it->value() != ".asciiz")
				{
					variable = it->value();
					it++;
					if (it->type() == EOL)
					{
						index_intrs.insert(pair<string, int>(variable, address));
						datainfo first;
						first.index_intrs1 = index_intrs;
						first.type = 7;//only variable as in var: \n
						datapart.push_back(first);
					}
					it--;
				}
				else if (it->value() == ".space")
				{
					if (it->value() == ".space")
					{
						it++;
					}
					it--;
					it--;


					variable = it->value();
					it++;
					it++;
					
					
					if (variable.empty())
					{

						stringstream geek(it->value());
						int x = 0;
						geek >> x;

						address = address + x;

						for (int i = address; i < address + x; i++)
						{
							memory.push_back(0);
						}
						//	//cout << address << endl;
					}
					else
					{
						////cout << variable << endl;
					//	//cout << address << endl;
						variable.pop_back();
						index_intrs.insert(pair<string, int>(variable, address));
						stringstream geek(it->value());
						int x = 0;
						geek >> x;
						
						for (int i = address; i < address + x; i++)
						{
							memory.push_back(0);
						}
						address = address + x;
					}

					////cout << address << endl;
					it++;
					if (it->type() == SEP)
					{
						if (it == tokens.end())
						{
							break;
						}
						it++;
						while (it->type() != EOL)
						{
							stringstream geek(it->value());
							int x = 0;
							geek >> x;
							if (variable.empty())
							{
								//memory.assign(address, 0);
								for (int i = address; i < address + x; i++)
								{
									memory.push_back(0);
								}
								it++;
							}
							else
							{

								//memory.assign(address, 0);
								for (int i = address; i < address + x; i++)
								{
									memory.push_back(0);
								}
								it++;
							}
							address = address + x;
						}
					}
				}
				else if (it->value() == ".word")
				{
					it--;
					variable = it->value();
					it++;
					if (it->value() == ".word")
						it++;
					stringstream geek(it->value());
					int x = 0;
					geek >> x;
					unsigned char *p = (unsigned char*)&x;

					//	//cout << "!!" << x << endl;
					if (!variable.empty())
					{
						
						variable.pop_back();
						index_intrs.insert(pair<string, int>(variable, address));
						datainfo first;
						first.index_intrs1 = index_intrs;
						first.type = 1;
						datapart.push_back(first);
						
					}

					memory.push_back(p[0]);
					memory.push_back(p[1]);
					memory.push_back(p[2]);
					memory.push_back(p[3]);
					////cout << "hey4" << endl;
					////cout << hex << (int)p[0] << (int)p[1] << (int)p[2] << (int)p[3] << endl;
					p = NULL;
					delete p;
					address = address + 4;
					it++;
					if (it->type() == SEP)
					{
						if (it == tokens.end())
							break;
						it++;
						while (it->type() != EOL)
						{
							stringstream geek(it->value());
							int x = 0;
							geek >> x;
							unsigned char *p = (unsigned char*)&x;
								memory.push_back(p[0]);
								memory.push_back(p[1]);
								memory.push_back(p[2]);
								memory.push_back(p[3]);
								////cout << "hey1" << memory.size() << endl;
								////cout << hex << (int)p[0] << endl; //<< (int)p[1] << (int)p[2] << (int)p[3] << endl;
								it++;
							
							p = NULL;
							delete p;
							address = address + 4;
						}
					}
				}
				else if (it->value() == ".byte")
				{
					it--;
					variable = it->value();
					it++;
					if (it->value() == ".byte")
					{
						it++;
					}
					stringstream geek(it->value());
					int x = 0;
					geek >> x;
					unsigned char *p = (unsigned char*)&x;
					//	//cout << "!!" << x << endl;
					if (!variable.empty())
					{


						variable.pop_back();
						index_intrs.insert(pair<string, int>(variable, address));
						datainfo first;
						first.index_intrs1 = index_intrs;
						first.type = 2;
						datapart.push_back(first);
						

						////cout << hex << (int)p[0] << endl; //<< (int)p[1] << (int)p[2] << (int)p[3] << endl;
					}
					memory.push_back(p[0]);
					p = NULL;
					delete p;
					address = address + 1;
					it++;
					if (it->type() == SEP)
					{
						if (it == tokens.end())
						{
							break;
						}
						it++;
						while (it->type() != EOL)
						{
							stringstream geek(it->value());
							int x = 0;
							geek >> x;
							unsigned char *p = (unsigned char*)&x;
								memory.push_back(p[0]);
								it++;
							p = NULL;
							delete p;
							address = address + 1;
						}
					}
				}
				else if (it->value() == ".half")
				{
					it--;
					variable = it->value();
					it++;
					if (it->value() == ".half")
					{
						it++;
					}
					stringstream geek(it->value());
					int x = 0;
					geek >> x;
					unsigned char *p = (unsigned char*)&x;
					//	//cout << "!!" << x << endl;
					if (!variable.empty())
					{
						variable.pop_back();
						index_intrs.insert(pair<string, int>(variable, address));
						datainfo first;
						first.index_intrs1 = index_intrs;
						first.type = 3;
						datapart.push_back(first);

					}
					memory.push_back(p[0]);
					memory.push_back(p[1]);
					p = NULL;
					delete p;
					address = address + 2;
					it++;
					if (it->type() == SEP)
					{
						if (it == tokens.end())
						{
							break;
						}
						it++;
						while (it->type() != EOL)
						{
							stringstream geek(it->value());
							int x = 0;
							geek >> x;
							unsigned char *p = (unsigned char*)&x;
							////cout <<"!!" <<x << endl;
								memory.push_back(p[0]);
								memory.push_back(p[1]);
								////cout << "hey2" << memory.size() << endl;
								////cout << hex << (int)p[0] << endl; //<< (int)p[1] << (int)p[2] << (int)p[3] << endl;
								it++;
							p = NULL;
							delete p;
							address = address + 2;
						}
					}
				}
				else if (it->value() == ".ascii")
				{
					it--;
					variable = it->value();
					it++;
					if (it->value() == ".ascii")
					{
						it++;
					}
					if (variable.empty())
					{
						string h = "";
						//it++;//skip delimiter
						while (it->type() != STRING_DELIM)
						{
							h = h + it->value();

							if (it != tokens.end() && it->type() != EOL)
								it++;
							else
								break;
						}
						for (unsigned int i = 0; i < h.length(); i++)
						{
							////cout << h[i] << endl;
							memory.push_back(h[i]);
							address = address + 1;
						}
					}
					else
					{
						//it++;//skip delimiter
						variable.pop_back();
						index_intrs.insert(pair<string, int>(variable, address));
						string h = "";
						datainfo first;
						first.index_intrs1 = index_intrs;
						first.type = 4;
						datapart.push_back(first);
						while (it->type() != STRING_DELIM)
						{
							h = h + it->value();

							if (it != tokens.end() && it->type() != EOL)
								it++;
							else
								break;
						}
						for (unsigned int i = 0; i < h.length(); i++)
						{
							////cout << h[i] << endl;
							memory.push_back(h[i]);
							address = address + 1;
						}
					}

				}
				else if (it->value() == ".asciiz")
				{
					it--;
					variable = it->value();
					it++;
					if (it->value() == ".ascii")
					{
						it++;
					}
					if (variable.empty())
					{
						string h = "";
						//it++;//skip delimiter
						while (it->type() != STRING_DELIM)
						{
							h = h + it->value();

							if (it != tokens.end() && it->type() != EOL)
								it++;
							else
								break;
						}
						for (unsigned int i = 0; i < h.length(); i++)
						{
							////cout << h[i] << endl;
							memory.push_back(h[i]);
							address = address + 1;
						}
						memory.push_back(0);
						address = address + 1;
					}
					else
					{
						//it++;//skip delimiter
						variable.pop_back();
						index_intrs.insert(pair<string, int>(variable, address));
						datainfo first;
						first.index_intrs1 = index_intrs;
						first.type = 5;
						datapart.push_back(first);
						string h = "";
						//it++;//skip delimiter
						while (it->type() != STRING_DELIM)
						{
							h = h + it->value();

							if (it != tokens.end() && it->type() != EOL)
								it++;
							else
								break;
						}
						for (unsigned int i = 0; i < h.length(); i++)
						{
							////cout << h[i] << endl;
							memory.push_back(h[i]);
							address = address + 1;
						}
						memory.push_back(0);
						address = address + 1;
					}
				}

				if (it == tokens.end() || it->type() == EOL)
				{
					break;
				}
				else
				{

					it++;
					//	////cout << "h3" << endl;
				}
			}
			else //for constants and values
			{
			//	////cout << "cons" << endl;
				string name = it->value();
				it++;
				it++;
				stringstream geek(it->value());
				int value = 0;
				geek >> value;
				constants.insert(pair<string, int>(name, value));
				//////cout << "it++" << endl;;
				
			}
		}
		if (it == tokens.end())
			break;
		else 
			it++;
	}
	for (int i = address; i < 512; i++)
		memory.push_back(0x00);
}
bool VirtualMachine::islabel(string str)
{
	if(str.length()>0)
	{ 
	if (str.at(str.length() - 1) == ':')
		return true;
	else
		return false;
	}
	else
		return false;
}

void VirtualMachine::saving_instr(TokenList tokens)
{
	int line = 0;
	//////cout << "here" << endl;
	auto it = tokens.begin();
	bool u = false;
	arguments mi;
	while (it != tokens.end())
	{
		while (it->type() != EOL)
		{
			
			u = islabel(it->value());
			if (u)
			{
				labels.insert(pair<string, int>(it->value().erase(it->value().size() - 1), line));
				//////cout << it->value().erase(it->value().size() - 1) <<line<< endl;
			}
			else
			{
				if (it->value() == "j")
				{
					line++;
					mi.ops = J;
					it++;//no seperator here
					mi.immediate = 0;
					mi.label = it->value();
					mi.myoffset.myregisster="0";
					mi.myoffset.offset = 0;
					mi.myregister = "0";
					mi.myregister2 = "0";
					mi.myregister3 = "0";
					mi.line = line;
					instructions.push_back(mi);
				}
				else if (it->value() == "bge"|| it->value() == "bgt"||it->value()=="ble"|| it->value() == "blt"|| it->value() == "bne"|| it->value() == "beq")
				{
					line++;
					if (it->value() == "bge")
					{
					//	////cout << "BGE" << endl;
						mi.ops = BGE;
					}
					else if (it->value() == "bgt")
					{
					//	////cout << "BGT" << endl;
						mi.ops = BGT;
					}
					else if (it->value() == "ble")
					{
						//////cout << "BLE" << endl;
						mi.ops = BLE;
					}
					else if (it->value() == "blt")
					{
						//////cout << "BLT" << endl;
						mi.ops = BLT;
					}
					else if (it->value() == "bne")
					{
						//////cout << "BNE" << endl;
						mi.ops = BNE;
					}
					else if (it->value() == "beq")
					{
					//	//cout << "BEQ" << endl;
						mi.ops = BEQ;
					}
					it++;
					mi.myregister = alias(it->value());
					it++;
					it++;//to skip sep
					
					bool l = it->value().find_first_not_of("0123456789") == string::npos;
					if (l == true)
					{
						stringstream geek(it->value());
						int x = 0;
						geek >> x;
						mi.immediate = x;
						mi.myregister2 = "0";
					}
					else if (constants.count(it->value()) == 1)
					{
						mi.myregister2 = "0";
						mi.immediate = constants[it->value()];
					}
					else
					{
						mi.immediate = 0;
						mi.myregister2 = alias(it->value());
					}
					it++;
					it++;//for next sep
					mi.label = it->value();
					mi.myregister3 = "0";
					mi.myoffset.myregisster = "0";
					mi.myoffset.offset = 0;
					mi.line = line;
					instructions.push_back(mi);
				}
				else if (it->value() == "xor"|| it->value() == "or"|| it->value() == "nor"|| it->value() == "and"||it->value()=="add"||it->value()=="addu"||it->value()=="sub"||it->value()=="subu"||it->value()=="mul"||it->value()=="mulo"||it->value()=="mulou"||it->value()=="rem"||it->value()=="remu")
				{
					line++;
					if (it->value() == "xor")
						mi.ops = XOR;
					else if (it->value() == "or")
						mi.ops = OR;
					else if (it->value() == "nor")
						mi.ops = NOR;
					else if (it->value() == "and")
						mi.ops = AND;
					else if (it->value() == "add")
						mi.ops = ADD;
					else if (it->value() == "addu")
						mi.ops = ADDU;
					else if (it->value() == "sub")
						mi.ops = SUB;
					else if (it->value() == "subu")
						mi.ops = SUBU;
					
					it++;
					mi.myregister = alias(it->value());
					it++;
					it++;//skip sep
					mi.myregister2 = alias(it->value());
					it++;
					it++;//skip sep
					bool l = it->value().find_first_not_of("0123456789") == string::npos;
					if (l == true)
					{
						stringstream geek(it->value());
						int x = 0;
						geek >> x;
						mi.immediate = x;
						mi.myregister3 = "0";
					}
					else if (constants.count(it->value()) == 1)
					{
						////cout << it->value() << "!!@" << endl;
						////cout<< constants[it->value()]<<endl;
						mi.immediate = constants[it->value()];
						mi.myregister3 = "0";
					}
					else
					{
					//	//cout << "yuirosd#$#@" << endl;
					//	//cout << it->value() << endl;
						mi.immediate = 0;
						mi.myregister3 = alias(it->value());
					}
					mi.label = "0";
					mi.myoffset.myregisster = "0";
					mi.myoffset.offset = 0;
					mi.line = line;
					instructions.push_back(mi);
				}
				else if (it->value() == "not")
				{
					line++;
					mi.ops = NOT;
					it++;
					mi.myregister = alias(it->value());
					it++;
					it++;
					bool l = it->value().find_first_not_of("0123456789") == string::npos;
					if (l == true)
					{
						stringstream geek(it->value());
						int x = 0;
						geek >> x;
						mi.immediate = x;
						mi.myregister2 = "0";
					}
					else if (constants.count(it->value()) == 1)
					{
					//	//cout << it->value() << endl;
					//	//cout << constants[it->value()] << endl;
						mi.immediate = constants[it->value()];
						mi.myregister2 = "0";
					}
					else
					{
						mi.immediate = 0;
						mi.myregister2 = alias(it->value());
					}
					mi.label = "0";
					mi.myregister3 = "0";
					mi.myoffset.myregisster = "0";
					mi.myoffset.offset = 0;
					mi.line = line;
					instructions.push_back(mi);
				}
				else if (it->value() == "mult" || it->value() == "multu" || it->value() == "abs" || it->value() == "neg" || it->value() == "negu"||it->value()=="move")
				{
					line++;
					if (it->value() == "mult")
						mi.ops = MULT;
					else if (it->value() == "multu")
						mi.ops = MULTU;
					else if (it->value() == "move")
						mi.ops = MOVE;
					it++;
					mi.myregister = alias(it->value());
					it++;
					it++;
					mi.myregister2 = alias(it->value());
					mi.label = "0";
					mi.myregister3 = "0";
					mi.myoffset.myregisster = "0";
					mi.myoffset.offset = 0;
					mi.line = line;
					instructions.push_back(mi);

				}
				else if (it->value()=="div"||it->value()=="divu")
				{
					line++;
					it++;
					it++;
					it++;
					it++;
					if (it->type() != SEP)
					{
						it--;
						it--;
						it--;
						it--;
						if (it->value() == "div")
							mi.ops = DIV2;
						else if (it->value() == "divu")
							mi.ops = DIVU2;
						it++;
						mi.myregister = alias(it->value());
						it++;
						it++;
						mi.myregister2 = alias(it->value());
						mi.label = "0";
						mi.myregister3 = "0";
						mi.myoffset.myregisster = "0";
						mi.myoffset.offset = 0;
						mi.line = line;
						instructions.push_back(mi);
					}
					else if (it->type() == SEP)
					{
						it--;
						it--;
						it--;
						it--;
						if (it->value() == "div")
							mi.ops = DIV3;
						else if (it->value() == "divu")
							mi.ops = DIVU3;
						it++;
						mi.myregister = alias(it->value());
						it++;
						it++;
						mi.myregister2 = alias(it->value());
						it++;
						it++;
						bool l = it->value().find_first_not_of("0123456789") == std::string::npos;
						if (l == true)
						{
							stringstream geek(it->value());
							int x = 0;
							geek >> x;
							mi.immediate = x;
							mi.myregister3 = "0";
						}
						else
						{
							mi.immediate = 0;
							mi.myregister3 = alias(it->value());
						}
						mi.myoffset.myregisster = "0";
						mi.myoffset.offset = 0;
						mi.line = line;
						instructions.push_back(mi);

					}

				}
				else if (it->value() == "mfhi" || it->value() == "mflo" || it->value() == "mthi" || it->value() == "mtlo")
				{
					line++;
					if(it->value()=="mfhi")
						mi.ops =MFHI;
					else if(it->value()=="mflo")
						mi.ops = MFLO;
					else if (it->value() == "mthi")
						mi.ops = MTHI;
					else if (it->value() == "mtlo")
						mi.ops = MTLO;
					it++;
					mi.myregister = alias(it->value());
					mi.myregister2 = "0";
					mi.myregister3 = "0";
					mi.myoffset.myregisster = "0";
					mi.myoffset.offset = 0;
					mi.line = line;
					instructions.push_back(mi);

				}
				else if (it->value() == "li")
				{
					line++;
					mi.ops = LI;
					it++;
					mi.myregister = alias(it->value());
					it++;
					it++;
				 if (constants.count(it->value()) == 1)
				{
					mi.immediate = constants[it->value()];
				}
				 else
				 {
					 stringstream geek(it->value());
					 int x = 0;
					 geek >> x;
					 mi.immediate = x;
				 }
					mi.myregister2 = "0";
					mi.label = "0";
					mi.myregister3 = "0";
					mi.myoffset.myregisster = "0";
					mi.myoffset.offset = 0;
					mi.line = line;
					instructions.push_back(mi);
				}
				else if (it->value() == "lw" || it->value() == "lh" || it->value() == "lb" || it->value() == "la" || it->value() == "sw" || it->value() == "sh" || it->value() == "sb")
				{
					line++;
					if (it->value() == "lw")
					{
						////cout << ">>>>>>>!" << endl;
						mi.ops = LW;
					}
					else if (it->value() == "lh")
						mi.ops = LH;
					else if (it->value() == "lb")
						mi.ops = LB;
					else if (it->value() == "la")
						mi.ops = LA;
					else if (it->value() == "sw")
						mi.ops = SW;
					else if (it->value() == "sh")
						mi.ops = SH;
					else if (it->value() == "sb")
						mi.ops = SB;
					it++;
					mi.myregister = alias(it->value());
					//cout << mi.myregister << endl;
					it++;
					it++;
					//bool l = it->value().find_first_not_of("0123456789") == string::npos;
					bool l1 = true;
					it++;
					if (it->type() == OPEN_PAREN)
					{
						l1 = false;
					}
					it--;
					if (it->type()==STRING&&l1==true)//no offset
					{
						//cout << it->value() << "no offset" << endl;
						mi.notthere = 1;
						mi.myoffset.offset = 0;
						if (it->value()[0] == '$')
						{
							mi.no = 0;
							mi.myoffset.myregisster = alias(it->value());
							//cout << "kajshkd!!" << mi.myoffset.myregisster << endl;
						}
						else
						{
							//cout << "k!!!!!!!!kd!!" << mi.myoffset.myregisster << endl;
							bool l = it->value().find_first_not_of("0123456789") == string::npos;
							if (l == true)
							{
								mi.notthere = 1;
								mi.no = 1;
								stringstream geek(it->value());
								int x = 0;
								geek >> x;
								mi.myoffset.immediate = x;
								//cout << x << endl;
							}
							else
							{
								mi.notthere = 1;
								mi.no = 2;
								mi.myoffset.label = it->value();
							}
						}
					}
					else if (it->type() == OPEN_PAREN)//offset but only ($0) and thats it. no offset value in front
					{
						mi.notthere = 0;
						mi.myoffset.offset = 0;
						it++;
						if (it->value()[0] == '$')
						{
							mi.no = 3;
						//	//cout << "kajshkd" << mi.myoffset.myregisster << endl;
							mi.myoffset.myregisster = alias(it->value());
						}
						else
						{
							bool l = it->value().find_first_not_of("0123456789") == string::npos;
							if (l == true)
							{
								mi.no = 4;
								stringstream geek(it->value());
								int x = 0;
								geek >> x;
								mi.myoffset.immediate = x;
							}
							else
							{
								mi.no = 5;
								mi.myoffset.label = it->value();
							}
						}
					}
					else
					{
					//	//cout << "offset here" << endl;
						mi.notthere = 0;
						stringstream geek(it->value());
						int x1 = 0;
						geek >> x1;
						mi.myoffset.offset = x1;
						//cout << x1 << endl;
						it++;
						it++;
						if (it->value()[0] == '$')
						{
							mi.no = 6;
							
							mi.myoffset.myregisster= alias(it->value());
						//	//cout << "kajshkd" << mi.myoffset.myregisster << endl;
						//	//cout << "Howdy" << it->value() << endl;
						}
						else
						{
							bool l = it->value().find_first_not_of("0123456789") == string::npos;
							if (l == true)
							{
								mi.no = 7;
								stringstream geek(it->value());
								int x = 0;
								geek >> x;
								mi.myoffset.immediate = x;
							//	//cout << x <<"Rohan"<< endl;
							}
							else
							{
								mi.myoffset.myregisster.clear();
								mi.no = 8;
							//	//cout << "Rohan2" << endl;
								
								mi.myoffset.label= it->value();
							//	//cout << mi.myoffset.label << endl;
							}
						}
					}
					mi.line = line;
					instructions.push_back(mi);
				}
				else if (it->value() == "nop")
				{
					line++;
					mi.ops = NOP;
					mi.myregister3 = "0";
					mi.immediate = 0;
					mi.line = line;
					instructions.push_back(mi);

				}
			}
			it++;
		}
		
		it++;
	}
}

string VirtualMachine:: alias(string value)
{
	string result;
	if (value == "$zero")
		result="$0";
	else if (value == "$at")
		result = "$1";
	else if (value == "$v0")
		result ="$2";
	else if (value == "$v1")
		result ="$3";
	else if (value == "$a0")
		result ="$4";
	else if (value == "$a1")
		result ="$5";
	else if (value == "$a2")
		result ="$6";
	else if (value == "$a3")
		result ="$7";
	else if (value == "$t0")
		result ="$8";
	else if (value == "$t1")
		result ="$9";
	else if (value == "$t2")
		result ="$10";
	else if (value == "$t3")
		result ="$11";
	else if (value == "$t4")
		result ="$12";
	else if (value == "$t5")
		result ="$13";
	else if (value == "$t6")
		result ="$14";
	else if (value == "$t7")
		result ="$15";
	else if (value == "$s0")
		result ="$16";
	else if (value == "$s1")
		result ="$17";
	else if (value == "$s2")
		result ="$18";
	else if (value == "$s3")
		result ="$19";
	else if (value == "$s4")
		result ="$20";
	else if (value == "$s5")
		result ="$21";
	else if (value == "$s6")
		result ="$22";
	else if (value == "$s7")
		result ="$23";
	else if (value == "$t8")
		result ="$24";
	else if (value == "$t9")
		result ="$25";
	else if (value == "$k0")
		result ="$26";
	else if (value == "$k1")
		result ="$27";
	else if (value == "$gp")
		result ="$28";
	else if (value == "$sp")
		result ="$29";
	else if (value == "$fp")
		result ="$30";
	else if (value == "$ra")
		result ="$31";
	else
		result =value;
	return result;
}

int addOvf(int result, int a, int b)
{
//	//cout << a <<","<< b << endl;
	result = a + b;
	if (a > 0 && b > 0 && result < 0)
		return -1;
	if (a < 0 && b < 0 && result > 0)
		return -1;
	return 0;
}
int i;
void VirtualMachine::executing_instr()
{
	if (status.empty())
	{
		
		arguments here;
		here = instructions.at(line2);
		////cout << line2 << endl;
		
		 if(line2==(signed)instructions.size())
		{
			status = "Error : Instructions finished...";
		}
		 line2++;
		
	
		if (here.ops == MFHI)
		{
			////cout << "jj" << hi << endl;
			registers[here.myregister] = hi;
		}
		else if (here.ops == MFLO)
		{
			registers[here.myregister] = lo;
		}
		else if (here.ops == MTHI)
		{
			hi = registers[here.myregister];
		}
		else if (here.ops == MTLO)
		{
			lo = registers[here.myregister];
		}
		else if (here.ops == MOVE)
		{
			
			registers[here.myregister] = registers[here.myregister2];
			
		}
		else if (here.ops == LI)
		{
			////cout << "yuyu" << here.immediate << endl;
			registers[here.myregister] = here.immediate;
		}
		else if (here.ops == AND)
		{
			
			if (here.myregister3 == "0")
			{
				
				
				registers[here.myregister] = registers[here.myregister2] & here.immediate;
			}
			else
			{
				
				registers[here.myregister] = registers[here.myregister2] & registers[here.myregister3];
			}
		}
		else if (here.ops == NOR)
		{
			if (here.myregister3 == "0")
			{
				registers[here.myregister] = ~(registers[here.myregister2] | here.immediate);
			}
			else
			{
				registers[here.myregister] = ~(registers[here.myregister2] | registers[here.myregister3]);
			}
		}
		else if (here.ops == NOT)
		{
			if (here.myregister2 == "0")
			{
			//	//cout << "jiji" << endl;
			//	//cout << here.immediate << endl;
				registers[here.myregister] = ~here.immediate;
			}
			else
			{
			//	//cout << "jiji" << endl;
				//	//cout << "not here1" << endl;
				registers[here.myregister] = ~registers[here.myregister2];
			}
		}
		else if (here.ops == OR)
		{
			if (here.myregister3 == "0")
			{
				registers[here.myregister] = registers[here.myregister2] | here.immediate;
			}
			else
			{
				registers[here.myregister] = registers[here.myregister2] | registers[here.myregister3];
			}
		}
		else if (here.ops == XOR)
		{
			if (here.myregister3 == "0")
			{
				registers[here.myregister] = registers[here.myregister2] ^ here.immediate;
			}
			else
			{
				registers[here.myregister] = registers[here.myregister2] ^ registers[here.myregister3];
			}
		}
		else if (here.ops == ADD)
		{
			////cout << here.immediate <<"Raj" <<endl;
			if (here.myregister3 == "0")
			{
			//	//cout << here.immediate << "Raj" << endl;
				int result = 0;
				
				int y = addOvf(result, registers[here.myregister2], here.immediate);
				if (y == -1 )
				{
				//	//cout << here.immediate << "Raj" << endl;
					status = "Error : Overflow dectected...";
				}
				else
				{
					registers[here.myregister] = registers[here.myregister2] + here.immediate;
				}
			}
			else
			{
				int result = 0;
				//int u = registers[here.myregister2] + registers[here.myregister3];
				
				int y = addOvf(result, registers[here.myregister2], registers[here.myregister3]);
				if (y == -1 )
				{
					status = "Error : Overflow dectected...";
				}
				else
				{
					////cout << "tywir" << endl;
					registers[here.myregister] = registers[here.myregister2] + registers[here.myregister3];
				}

			}

		}
		else if (here.ops == ADDU)
		{
			if (here.myregister3 == "0")
			{
				registers[here.myregister] = registers[here.myregister2] + here.immediate;
			}
			else
			{
				registers[here.myregister] = registers[here.myregister2] + registers[here.myregister3];
			}
		}
		else if (here.ops == SUB)
		{
			if (here.myregister3 == "0")
			{
				int result = 0;
				int u = registers[here.myregister2] - registers[here.myregister3];
				int y = addOvf(result, registers[here.myregister2], here.immediate);
				if (y == -1 && u == 1)
				{
					status = "Error : Overflow dectected...";
				}
				else
				{
					registers[here.myregister] = registers[here.myregister2] - here.immediate;
				}
			}
			else
			{
				int result = 0;
				int u = registers[here.myregister2] - registers[here.myregister3];
				int y = addOvf(result, registers[here.myregister2], registers[here.myregister3]);
				if (y == -1 && u == 1)
				{
					status = "Error : Overflow dectected...";
				}
				else
				{
					registers[here.myregister] = registers[here.myregister2] - registers[here.myregister3];
				}

			}

		}
		else if (here.ops == SUBU)
		{
			if (here.myregister3 == "0")
			{
				registers[here.myregister] = registers[here.myregister2] - here.immediate;
			}
			else
			{
				registers[here.myregister] = registers[here.myregister2] - registers[here.myregister3];
			}
		}
		else if (here.ops == MULT)//prob here signed ask tomorrow
		{
			int64_t verylong = static_cast<int64_t>(registers[here.myregister]) * static_cast<int64_t>(registers[here.myregister2]);
			//int64_t  l = static_cast<signed>(2077252342) * static_cast<signed>(2);
			////cout << l << endl;
			
		
				////cout<< static_cast<int64_t>(registers[here.myregister]) <<"*"<< static_cast<int64_t>(registers[here.myregister2])<<"=" <<  (verylong) << endl;
				lo = static_cast<int32_t>(verylong);
				hi = static_cast<int64_t>(verylong) >> 32;
			
			//printf("low32=%#x\nhigh32=%#x\n", lo, hi);
		}
		else if (here.ops == MULTU)//ok here but still ask
		{
			uint64_t verylong = static_cast<uint64_t>(registers[here.myregister]) * static_cast<uint64_t>(registers[here.myregister2]);
				lo = static_cast<uint32_t>(verylong);
				hi = static_cast<uint64_t>(verylong) >> 32;
			
			//printf("low32=%#x\nhigh32=%#x\n", lo, hi);
		}
		else if (here.ops == DIV2)
		{
			if (registers[here.myregister2] != 0)
			{
				signed int y = registers[here.myregister] / registers[here.myregister2];
				int u = registers[here.myregister] % registers[here.myregister2];
				hi = (signed)u;
				lo = (signed)y;
			}
			
		}
		else if (here.ops == DIVU2)
		{
			if (registers[here.myregister2] != 0)
			{
				lo = registers[here.myregister] / registers[here.myregister2];
				hi = registers[here.myregister] % registers[here.myregister2];

			}
			
		}
		else if (here.ops == J)
		{
			line2 = labels[here.label];

		}
		else if (here.ops == NOP)
		{
			//do nothing
		}
		else if (here.ops == BEQ)
		{
			////cout << "BEQ!!!!!!"  << endl;
			////cout << here.label << endl;
			if ((registers[here.myregister] == here.immediate&&here.myregister2=="0")|| (registers[here.myregister] == registers[here.myregister2] && here.myregister2 != "0"))
			{
				////cout << here.myregister << endl;
				line2 = labels[here.label];
			}

		}
		else if (here.ops == BNE)
		{
			////cout << "BNE" << endl;
			if ((registers[here.myregister] != here.immediate && here.myregister2 == "0")|| (registers[here.myregister] != registers[here.myregister2] && here.myregister2 != "0"))
			{
				line2 = labels[here.label];
			}
		}
		else if (here.ops == BLT)
		{
		//	//cout << "BLT" << endl;
			if ((registers[here.myregister] < here.immediate&&here.myregister2 == "0")|| (registers[here.myregister] < registers[here.myregister2] && here.myregister2 != "0"))
			{
				line2 = labels[here.label];
			}

		}
		else if (here.ops == BLE)
		{
		//	//cout << "BLE" << endl;
			if ((registers[here.myregister] <= here.immediate&&here.myregister2 == "0")|| (registers[here.myregister] <= registers[here.myregister2] && here.myregister2 != "0"))
			{
				line2 = labels[here.label];
			}
		}
		else if (here.ops == BGT)
		{
			////cout << "BGT" << endl;
			if ((registers[here.myregister] > here.immediate&&here.myregister2 == "0")|| (registers[here.myregister] > registers[here.myregister2] && here.myregister2 != "0"))
			{
				line2 = labels[here.label];
			}

		}
		else if (here.ops == BGE)
		{
			if ((registers[here.myregister] >= here.immediate&&here.myregister2 == "0")||( registers[here.myregister] >= registers[here.myregister2] && here.myregister2 != "0"))
			{
				line2 = labels[here.label];
			}
		}
		else if (here.ops == LW)
		{
			
			if (here.myoffset.myregisster.empty() ||here.myoffset.myregisster == "0")
			{
				////cout << "ajksdhkajsdh122222 " << here.myoffset.label << endl;
				if (constants.count(here.myoffset.label) == 1)
				{
					registers[here.myregister] = constants[here.myoffset.label];// >> here.myoffset.offset; no offset with constants
				}
				else if(here.notthere==1)//no offset or bracekts easy part
				{
					 if (here.no == 1)//immediate value no offset
					{

						// //cout << "uiwo1" << endl;
						registers[here.myregister] = int((unsigned char)(memory.at(here.myoffset.immediate + 3)) << 24 |
							(unsigned char)(memory.at(here.myoffset.immediate + 2)) << 16 |
							(unsigned char)(memory.at(here.myoffset.immediate + 1)) << 8 |
							(unsigned char)(memory.at(here.myoffset.immediate)));
						
					}
					else if (here.no == 2)//label no offset
					{
						////cout << "aj()()()() " << here.myoffset.label << endl;
						////cout << here.myoffset.label <<here.line<< endl;
						////cout << "hey1111" << endl;
						////cout << hex<<(int)(memory.at(index_intrs[here.myoffset.label] + 3)) << (int)(memory.at(index_intrs[here.myoffset.label] + 2))<< (int)(memory.at(index_intrs[here.myoffset.label] + 1)) << (int)(memory.at(index_intrs[here.myoffset.label])) <<endl;
						registers[here.myregister]  = int((unsigned char)(memory.at(index_intrs[here.myoffset.label]+3)) << 24 |
							(unsigned char)(memory.at(index_intrs[here.myoffset.label] + 2)) << 16 |
							(unsigned char)(memory.at(index_intrs[here.myoffset.label] + 1)) << 8 |
							(unsigned char)(memory.at(index_intrs[here.myoffset.label] )));
						////cout << hex << registers[here.myregister] << endl;
					}
					
					else
					{
						status = "Error here...";
					}
					// //cout << "here3749" << endl;
				}
				else if (here.notthere == 0)
				{
					if (here.no == 4|| here.no == 7)
					{
						registers[here.myregister] = int((unsigned char)(memory.at(here.myoffset.immediate + 3+here.myoffset.offset)) << 24 |
							(unsigned char)(memory.at(here.myoffset.immediate + 2+ here.myoffset.offset)) << 16 |
							(unsigned char)(memory.at(here.myoffset.immediate + 1+ here.myoffset.offset)) << 8 |
							(unsigned char)(memory.at(here.myoffset.immediate+ here.myoffset.offset)));
					//	//cout << hex << registers[here.myregister] << endl;
					}
					else if (here.no == 5|| here.no == 8)
					{
						////cout << here.myoffset.label << endl;
						////cout << "38938472 " << index_intrs[here.myoffset.label] <<endl;
						registers[here.myregister] = int((unsigned char)(memory.at(index_intrs[here.myoffset.label] + 3 + here.myoffset.offset)) << 24 |
							(unsigned char)(memory.at(index_intrs[here.myoffset.label] + 2 + here.myoffset.offset)) << 16 |
							(unsigned char)(memory.at(index_intrs[here.myoffset.label] + 1 + here.myoffset.offset)) << 8 |
							(unsigned char)(memory.at(index_intrs[here.myoffset.label] + here.myoffset.offset)));
						////cout << hex << registers[here.myregister] << endl;
					}
					else
					{
						status = "Error here...";
					}
				}
				else
				{
					status = "Error here...";
				}
			}
			else if(!here.myoffset.myregisster.empty()&& here.myoffset.myregisster!="0")
			{
				//cout << "dh1!!!! " << here.myoffset.label <<here.myoffset.offset<< endl;
				if (here.no == 6||here.no == 3|| here.no == 0)
				{
					////cout << here.myregister << endl;
					registers[here.myregister] =  int((unsigned char)(memory.at(registers[here.myoffset.myregisster] + 3 + here.myoffset.offset)) << 24 |
						(unsigned char)(memory.at(registers[here.myoffset.myregisster] + 2 + here.myoffset.offset)) << 16 |
						(unsigned char)(memory.at(registers[here.myoffset.myregisster] + 1 + here.myoffset.offset)) << 8 |
						(unsigned char)(memory.at(registers[here.myoffset.myregisster] + here.myoffset.offset)));
					//here.myoffset.myregisster.clear();
					////cout << registers[here.myregister] << endl;
					////cout <<"&*()_"<< hex << (int)memory.at(registers[here.myoffset.myregisster] + 3 + here.myoffset.offset) << (int)memory.at(registers[here.myoffset.myregisster] + 2 + here.myoffset.offset) << (int)memory.at(registers[here.myoffset.myregisster] + 1 + here.myoffset.offset) << (int)memory.at(registers[here.myoffset.myregisster]  + here.myoffset.offset) << endl;
				}
			}
		}
		else if (here.ops == LA)
		{
			if (constants.count(here.myoffset.label) == 1)
			{
				registers[here.myregister] = constants[here.myoffset.label];;// >> here.myoffset.offset; no offset with constants
			}
			else if (here.notthere == 1)//no offset or bracekts easy part
			{
				if (here.no == 1)//immediate value no offset
				{

					registers[here.myregister] = here.myoffset.immediate;
					// //cout << "uiwo1" << endl;

				}
				else if (here.no == 2)//label no offset
				{
					////cout << "tyeuro" << endl;
					////cout << here.myoffset.label << endl;
					////cout << index_intrs[here.myoffset.label] << endl;
					registers[here.myregister] = index_intrs[here.myoffset.label];

				}
				else
				{
					status = "Error here...";
				}
				// //cout << "here3749" << endl;
			}
			else if (here.notthere == 0)
			{
				if (here.no == 4 || here.no == 7)
				{
					registers[here.myregister] = here.myoffset.immediate + here.myoffset.offset;

				}
				else if (here.no == 5 || here.no == 8)
				{
					registers[here.myregister] = here.myoffset.immediate + here.myoffset.offset;

				}
				else
				{
					status = "Error here...";
				}
			}
		}
		else if (here.ops == SW)//has to do this
		{

			if (here.myoffset.myregisster.empty() || here.myoffset.myregisster == "0")
			{
				
				if (constants.count(here.myoffset.label) == 1)
				{
					registers[here.myregister] = constants[here.myoffset.label];// >> here.myoffset.offset; no offset with constants
				}
				else if (here.notthere == 1)//no offset or bracekts easy part
				{
					if (here.no == 1)//immediate value no offset
					{

						unsigned char *p = (unsigned char*)&registers[here.myregister];
						memory[here.myoffset.immediate]=p[0];
						memory[here.myoffset.immediate+1] = p[1];
						memory[here.myoffset.immediate+2] = p[2];
						memory[here.myoffset.immediate+3] = p[3];

						p = NULL;
						delete p;
						// //cout << "uiwo1" << endl;
						
					}
					else if (here.no == 2)//label no offset
					{
						////cout << "ajksdhsdh!!" << endl;
						////cout << here.myoffset.label << endl;
						////cout << index_intrs[here.myoffset.label] << endl;
						unsigned char *p = (unsigned char*)&registers[here.myregister];
						memory[index_intrs[here.myoffset.label]] = p[0];
						memory[index_intrs[here.myoffset.label] + 1] = p[1];
						memory[index_intrs[here.myoffset.label] + 2] = p[2];
						memory[index_intrs[here.myoffset.label] + 3] = p[3];

						p = NULL;
						delete p;

					}
					else
					{
						status = "Error here...";
					}
					// //cout << "here3749" << endl;
				}
				else if (here.notthere == 0)
				{
					if (here.no == 4 || here.no == 7)
					{
						unsigned char *p = (unsigned char*)&registers[here.myregister];
						memory[here.myoffset.immediate +  here.myoffset.offset] = p[0];
						memory[here.myoffset.immediate +  here.myoffset.offset + 1] = p[1];
						memory[here.myoffset.immediate +  here.myoffset.offset + 2] = p[2];
						memory[here.myoffset.immediate +  here.myoffset.offset + 3] = p[3];

						p = NULL;
						delete p;
						
					}
					else if (here.no == 5 || here.no == 8)
					{
						unsigned char *p = (unsigned char*)&registers[here.myregister];
						memory[index_intrs[here.myoffset.label] +  here.myoffset.offset] = p[0];
						memory[index_intrs[here.myoffset.label] +  here.myoffset.offset + 1] = p[1];
						memory[index_intrs[here.myoffset.label] +  here.myoffset.offset + 2] = p[2];
						memory[index_intrs[here.myoffset.label] +  here.myoffset.offset + 3] = p[3];

						p = NULL;
						delete p;
					}
					else
					{
						status = "Error here...";
					}
				}
				else
				{
					status = "Error here...";
				}
			}
			else if (!here.myoffset.myregisster.empty() && here.myoffset.myregisster != "0")
			{
				if (here.no == 6 || here.no == 3 || here.no == 0)
				{
					unsigned char *p = (unsigned char*)&registers[here.myregister];
					memory[registers[here.myoffset.myregisster] + here.myoffset.offset] = p[0];
					memory[registers[here.myoffset.myregisster] + here.myoffset.offset + 1] = p[1];
					memory[registers[here.myoffset.myregisster] + here.myoffset.offset + 2] = p[2];
					memory[registers[here.myoffset.myregisster] + here.myoffset.offset + 3] = p[3];

					p = NULL;
					delete p;
				}
			}
		}
		else
		{
			status = "Error :Invalid opcode...\n";
		}
	}
	else
	{
		status=status+"Please correct the mistake and restart the program...";
	}
}