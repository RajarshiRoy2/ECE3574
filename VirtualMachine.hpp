#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include <vector>
#include <map>
#include <string>
#include "token.hpp"

using namespace std;

enum Opcode
{
LW,LH,
LB,LI,
LA,SW,
SH,SB,
MOVE,MFHI,
MFLO,MTHI,
MTLO,

ADD,ADDU,
SUB,SUBU,
MUL,MULO,
MULOU,MULT,
MULTU,
DIVU3,DIV3,
DIV2,DIVU2,
REM,REMU,
ABS,NEG,
NEGU,

AND,NOR,
NOT,OR,
XOR,

J,BEQ,
BNE,BLT,
BGT,BGE,BLE,
NOP
};

struct Offset {
	string myregisster;
	int offset;
	string label;
	int immediate;
};

struct arguments
{
	Opcode ops;
	Offset myoffset;
	string myregister;
	string myregister2;
	string myregister3;
	int immediate;
	string label;
	int line;
	int notthere;
	int no;
};

struct datainfo
{
	map <string, int> index_intrs1;
	int type;
};
class VirtualMachine {

public:
	VirtualMachine();
	
	~VirtualMachine();

	void setting_data_values(TokenList tokens);
	void saving_instr(TokenList tokens);

	string alias(string value);

	void executing_instr();
	
	vector<unsigned char> memory;
	map <string, int> index_intrs;
	map <string, int> constants;
	vector<datainfo>datapart;
	map<string, int> labels;
	map<string, int> registers = { { pair<string,int>("$0",0) },{ pair<string,int>("$1",0) },{ pair<string,int>("$2",0) },
	{ pair<string,int>("$3",0) },{ pair<string,int>("$4",0) },{ pair<string,int>("$5",0) },{ pair<string,int>("$6",0) },
	{ pair<string,int>("$7",0) },{ pair<string,int>("$8",0) },{ pair<string,int>("$9",0) },{ pair<string,int>("$10",0) }, 
	{ pair<string,int>("$11",0) },{ pair<string,int>("$12",0) },{ pair<string,int>("$13",0) },{ pair<string,int>("$14",0) }, 
	{ pair<string,int>("$15",0) },{ pair<string,int>("$16",0) },{ pair<string,int>("$17",0) },{ pair<string,int>("$18",0) }, 
	{ pair<string,int>("$19",0) },{ pair<string,int>("$20",0) },{ pair<string,int>("$21",0) },{ pair<string,int>("$22",0) }, 
	{ pair<string,int>("$23",0) },{ pair<string,int>("$24",0) },{ pair<string,int>("$25",0) },{ pair<string,int>("$26",0) }, 
	{ pair<string,int>("$27",0) },{ pair<string,int>("$28",0) },{ pair<string,int>("$29",0) },{ pair<string,int>("$30",0) }, 
	{ pair<string,int>("$31",0) } };
	int hi=0, lo=0;
	string status;
	int line2;
	vector<arguments>instructions;
private:
	bool islabel(string str);
	int address = 0;
	int ipe = 0;
	int place = 0;
	
	
};

#endif