#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <mutex>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QApplication>
#include "VirtualMachine.hpp"
#include "virtual_machine_gui.hpp"
#include "parser.hpp"
#include "vector.hpp"
using namespace std;

bool is_file_exist(string fileName)
{
	ifstream infile(fileName);
	return infile.good();
}
OutputVector<string> vec;
VirtualMachine machine;
int n1 = 0;
void run_function()
{
	int mode = 0;


	while (machine.status.empty())
	{
		if (machine.line2>= machine.instructions.size())
			break;
		else
			machine.executing_instr();
		if (vec.size() != 0)
		{
			vec.the_vec.clear();
			break;
		}
	}
	
}

int main(int argc, char *argv[])
{
	vector<string> args;
	ifstream inFile;
	for (auto i = 0; i < argc; ++i)
		args.push_back(argv[i]);
	if (args.at(1) == "--gui")
	{
		
		QApplication app(argc, argv);
		VirtualMachineGUI GUI;
		QString qstr1 = QString::fromStdString(args.at(2));
		GUI.load(qstr1);
		GUI.showMaximized();

		return app.exec();
	}
	else
	{
		bool t = is_file_exist(args.at(1));
		if (t == false)
		{
			cerr << "Error file does not exist" << endl;
			return EXIT_FAILURE;
		}
		if (args.size() != 2)
		{
			cerr << "Please an correct format..." << endl;
			return EXIT_FAILURE;
		}
		Parser parser;
		string value, input, sum;
		inFile.open(args.at(1));
		while (getline(inFile, input))
			sum = sum + "\n" + input;
		inFile.close();
		if (!parser.tokens(sum)) //checking for error
		{
			cerr << parser.my_error() << endl;
			return EXIT_FAILURE;
		}
		//sum.clear();
		inFile.open(args.at(1));
		while (getline(inFile, input))
		{
			size_t found = input.find(".text");
			if (found > 0 && found != 4294967295)
			{
				break;
			}
			sum = sum + "\n" + input;
		}
		istringstream iss(sum);
		TokenList tl1 = tokenize(iss);

		machine.setting_data_values(tl1);
		sum.clear();
		while (getline(inFile, input))
		{
			if (input != ""&&input != " "&&input != "\t")
				sum = sum + "\n" + input;
		}
		istringstream iss1(sum);
		TokenList tl11 = tokenize(iss1);
		machine.saving_instr(tl11);
		inFile.close();

		int er = 0;

		while (true)
		{
			cerr << "simmips> ";
			getline(cin, value);
			if (value == "step"&&machine.status.empty())
			{
				
				machine.executing_instr();
				cerr << "0x" << setfill('0') << setw(8) << hex << machine.line2 << endl;
			}
			else if (value == "status")
				cerr << machine.status << endl;
			else if (value == "quit")
				break;
			else
			{

				if (value.substr(0, 6) == "print ")
				{
					value.erase(0, 6);
					if (value[0] == '&')
					{
						int ss1;
						value.erase(0, 1);
						stringstream ss;
						ss << std::hex << value;
						ss >> ss1;
						if (ss1 > (signed)machine.memory.size())
						{
							cerr << "Error out of bound memory" << endl;
						}
						else
						{
							if ((int)machine.memory.at(ss1) < 15)
							{
								cerr << "0x" // show the 0x prefix
									<< "0";// fill between the prefix and the number
								cerr << hex << (int)machine.memory.at(ss1) << endl;
							}
							else
							{
								cerr << "0x" // show the 0x prefix
									<< internal // fill between the prefix and the number
									<< setfill('0'); // fill with 0s
								cerr << hex << (int)machine.memory.at(ss1) << endl;
							}

						}
					}
					else if (value[0] == '$')
					{
						string register2 = machine.alias(value);
						if (machine.registers.count(register2) > 0)
							cerr << "0x" << setfill('0') << setw(8) << hex << machine.registers[register2] << endl;
						else if (value == "$hi")
							cerr << "0x" << setfill('0') << setw(8) << hex << machine.hi << endl;
						else if (value == "$lo")
							cerr << "0x" << setfill('0') << setw(8) << hex << machine.lo << endl;
						else if (value == "$pc")
							cerr << "0x" << setfill('0') << setw(8) << hex << machine.line2 << endl;
						else
							cerr << "Error Not a valid register..." << endl;
					}
					
					else
						cerr << "Error : unknown command.\n";
				}
				else if (value == "run"&&machine.status.empty())
				{
					er = 1;
					thread t1(&run_function);
					t1.detach();
					cout << machine.status << endl;
				}
				else if (value == "break")
				{
					if (er == 1)
					{
						vec.append("break");
					}

				}
				else
					cerr << "Error here.\n";
			}
		}
		cerr << "Success" << endl;
		return EXIT_SUCCESS;
	}
}
