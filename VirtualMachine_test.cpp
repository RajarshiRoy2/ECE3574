#include "catch.hpp"

#include "VirtualMachine.hpp"
#include "lexer.hpp"
#include <string>
#include <map>
#include <iomanip>
#include<iostream>
using namespace std;

TEST_CASE("first test", "[VirtualMachine]") 
{
	{
		string text = " .data\n.space 8\nvar1: .word 2\nvar2: .word -2,2\n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var1"] == 8);// << endl;
		REQUIRE(first.index_intrs["var2"] == 12);
		REQUIRE(first.memory.size() == 512);// << endl;
	}
	{
		string text = " .data\nvar2: .space 8\nvar1: .word 1\nvar3: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var3"] == 12);// << endl;
		REQUIRE(first.memory.size() == 512);
	}
	{
		string text = " .data\nvar3: .space 8,5,2,3\nvar1: .word 1\nvar2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var2"] == 22);// << endl;
		
	}
	{
		string text = R"(        .data
			VALUE = 2
			var1: .word 1
			var2: .word 12
			var3: .word -1)";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE( first.index_intrs["var1"] ==0);
		REQUIRE(first.index_intrs["var2"] == 4);
		REQUIRE(first.index_intrs["var3"] == 8);
		REQUIRE(first.memory.at(0) == 0x1);
		REQUIRE(first.memory.at(1) == 0x0);
		REQUIRE(first.memory.at(2) == 0x0);
		REQUIRE(first.memory.at(3) == 0x0);
		REQUIRE(first.memory.at(4) == 0xC);
		REQUIRE(first.memory.at(5) == 0x0);
		REQUIRE(first.memory.at(6) == 0x0);
		REQUIRE(first.memory.at(7) == 0x0);
		REQUIRE(first.memory.at(8) == 0xFF);
	}
	{
		string text = " .data\n .byte 1\nvar2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var2"] == 1);// << endl;
		
	}
	{
		string text = " .data\n gh: .byte 1,2\nvar2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["gh"] == 0);// << endl;
		REQUIRE(first.memory.size() == 512);// << endl;
	}
	{
		string text = " .data\n .byte 1,2\nvar2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
	}
	{
		string text = " .data\n .half 1,2\nvar2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var2"] == 4);// << endl;
		
	}
	{
		string text = " .data\n damm: .half 1,2\nvar2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["damm"] == 0);// << endl;
		
	}

	{
		
		string text = " .data\n .ascii ""Who am I"" \n var2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var2"] == 6);
		REQUIRE(first.memory.at(7) == 0xff);
	}
	{

		string text = " .data\n .asciiz ""Who am I"" \n var2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var2"] == 14);
		REQUIRE(first.memory.at(7) =='W');
	}
	{

		string text = " .data\nvar1: .asciiz ""Who am I"" \n var2: .word -2";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["var2"] == 14);
		REQUIRE(first.memory.at(7) == 'W');
	}
	{
		string text = " .data\n my: .ascii ""Who am I"" \n var2: .word -2 \n desi: .ascii ""lallu"" \n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs["desi"] == 10);
		REQUIRE(first.memory.at(0) == 'W'); 
		REQUIRE(first.datapart.size() == 3);
		REQUIRE(first.datapart.at(0).type == 4);
	}

	{
	
		string text = " .data\nVALUE = -1\nvar:.word 1\n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		
	}
	{
	
		string text = ".data\nvar1: .word 2\nvar2 : .word -2\n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.memory.at(4) ==(unsigned char) -2);

	}
	{

		string text = "        .data\nA = 0\nB = 1\nC = 2\nD = 4\n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.constants["D"] == 4); 

	}
	{
	
		string text = "         .data\nVALUE = 3\nvar1:.word 12\nvar2 : .word 10\n .space 3,5,3\n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE( first.constants["VALUE"]==3);

	}
	{

		string text = ".data\nvar2: \n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE(first.index_intrs.size() == 1); 

	}
	{

		string text = ".data\nr1: .space 4\n r2: .space 12\nr3: .space 4\nvar: .word 7\n";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.setting_data_values(tokens);
		REQUIRE( (int)first.memory.at(20)==7);
	}
	{

		string text = R"(.main:
			
			ble $v1,0,check1
check1:
or $zero,$at,$v0
divu $0,$1
mthi $4
mtlo $5
lb $a0,$s3
lb $a0,($s3)
lb $a0,(3)
sh $sp,$s2
divu $sp,$s2
sb $gp,$s5)";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.saving_instr(tokens);
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
		first.executing_instr();
	}
{
		string text = R"(.main:
			
			bge $a1,0,check1
check1:
or $a2,$a3,$s4
qweqwe $a2,$a3,$s3)";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.saving_instr(tokens);
		first.executing_instr();

	}
	{

		string text = R"(.main:
			
			beq $t0, 0, check1
			beq $t0, $t0, check1
			nop
			check1:
		bne $t0, 0, check2
			bne $t0, 0, check2
			nop
			check2:
		bgt $t0, $t0, check3
			bgt $t3, $t1, check3
			nop
			check3:
		bge $t0, $t1, check4
			bge $t3, $t2, check4
			nop
			check4:
		blt $t3, $t1, check5
			blt $t1, $t3, check5
			nop
			check5:
		ble $t3, $t1, check6
			ble $t3, $t3, check6
			nop
			check6:
		nop
			j check6)";
		istringstream i(text);
		TokenList tokens = tokenize(i);
		VirtualMachine first;
		first.saving_instr(tokens);
		REQUIRE(first.labels["check6"] ==18);
		first.executing_instr();
		first.executing_instr();
	}
{
		string h = "j check5\n beq $0,5,check5\nbne $0,$t0,check5\n and $s0,$s1,5\n div $t0, $t2, 5\n lw $0,6($2)\nlh $0,$3\n";
		VirtualMachine first;
		istringstream i(h);
		TokenList tokens = tokenize(i);
		first.saving_instr(tokens);
		REQUIRE(first.instructions.at(0).label == "check5");

		REQUIRE(first.instructions.at(1).label == "check5");
		REQUIRE(first.instructions.at(1).line == 2);
		REQUIRE(first.instructions.at(1).myoffset.offset == 0);
		REQUIRE(first.instructions.at(1).immediate==5);

		REQUIRE(first.instructions.at(2).myregister2 == "$8");

		REQUIRE(first.instructions.at(3).myregister2 == "$17");

		REQUIRE(first.instructions.at(4).myregister == "$8");
		REQUIRE(first.instructions.at(4).myregister2 == "$10");
		REQUIRE(first.instructions.at(4).immediate == 5);

		REQUIRE(first.instructions.at(5).myregister == "$0");
		REQUIRE(first.instructions.at(5).myoffset.myregisster == "$2");
		REQUIRE(first.instructions.at(6).myregister == "$0");
		REQUIRE(first.instructions.at(6).myoffset.myregisster == "$3");
	}
	{
		string h = "mfhi $0\n mflo $2\n move $7, $t0\n li $t2, 5\n not $s0, $10\n,not $s1, 5\n and $30, $0, 5\n or $4, $17,5\n";
		VirtualMachine first;
		
		istringstream i(h);
		TokenList tokens = tokenize(i);
		first.hi = 1;
		first.lo = 2;
		first.registers["$8"] = 3;
		first.saving_instr(tokens);
		first.executing_instr();
		REQUIRE(first.registers["$0"] == 1);
		first.executing_instr();//need to do this every turn
		REQUIRE(first.registers["$2"] == 2);
		first.executing_instr();
		REQUIRE(first.registers["$7"] == 3);
		first.executing_instr();
		REQUIRE(first.registers["$10"] == 5);
		first.executing_instr();
		REQUIRE(first.registers["$16"] == (signed)-6);
		first.executing_instr();
		REQUIRE(first.registers["$17"] == (signed)-6);
		first.executing_instr();
		REQUIRE(first.registers["$30"] == 1);
		first.executing_instr();
		REQUIRE(first.registers["$4"] == -1);
	}
	
		{
			string h = "add $0, $5,5\n add $1,$6, 21364123\n";
			VirtualMachine first;
			istringstream i(h);
			TokenList tokens = tokenize(i);
			first.saving_instr(tokens);
			first.registers["$5"] = 5;
			first.registers["$6"] = 1;
			first.executing_instr();
			REQUIRE(first.registers["$0"] == 10);
			first.executing_instr();
			REQUIRE(first.status == "");
			REQUIRE(first.registers["$1"] == 21364124);
			
			
		}

		{
			string h = R"(
multu $0,$6
bne $0,$6, check4
check2:
  mfhi $1 
  j check5 
check3:
  li $30, 6
check4:
  not $0, $10
  j check2
check5:
  li $2, 5
  j check3)";
			VirtualMachine first;
			istringstream i(h);
			TokenList tokens = tokenize(i);
			first.saving_instr(tokens);
			first.registers["$0"] = 5;
			first.registers["$10"] = 5;
			//cout << "3rd" << endl;
			first.executing_instr();
			first.executing_instr();
			first.executing_instr();

			REQUIRE(first.registers["$10"] == 5);
			REQUIRE(first.registers["$0"] == -6);
		}
		{
			string h = R"(
blt $0,5, check4
check2:
  mfhi $1 
  j check5 
check3:
  li $30, 6
check4:
  not $0, $10
  j check2
check5:
  li $2, 5
  j check3)";
			VirtualMachine first;
			istringstream i(h);
			TokenList tokens = tokenize(i);
			first.saving_instr(tokens);
			first.registers["$0"] = 5;
			first.registers["$10"] = 5;
			first.hi = 1;
			//cout << "3rd" << endl;
			first.executing_instr();
			first.executing_instr();
			REQUIRE(first.registers["$1"] == 1);
			REQUIRE(first.registers["$10"] == 5);
			REQUIRE(first.registers["$0"] == 5);
		}
			{
			string h = "sub $0, $5,5\n sub $1,$6, 21363\n";
			VirtualMachine first;
			istringstream i(h);
			TokenList tokens = tokenize(i);
			first.saving_instr(tokens);
			first.registers["$5"] = 5;
			first.registers["$6"] = 1;
			first.executing_instr();
			REQUIRE(first.registers["$0"] == 0);
			first.executing_instr();
			REQUIRE(first.registers["$1"] == -21362);

		}
		
		{
			string h = "div $5,$6\n div $4, $21\n";
			VirtualMachine first;
			istringstream i(h);
			TokenList tokens = tokenize(i);
			first.saving_instr(tokens);
			first.registers["$4"] = 4;
			first.registers["$5"] = 5;
			first.registers["$6"] = -2;
			first.registers["$21"] = 3;
			first.executing_instr();
			REQUIRE(first.lo == -2);
			REQUIRE(first.hi == 1);
			first.executing_instr();
			REQUIRE(first.lo == 1);
			REQUIRE(first.hi == 1);

		}
		{
			string h = "div $5,$6\n div $4, $21\n";
			VirtualMachine first;
			istringstream i(h);
			TokenList tokens = tokenize(i);
			first.saving_instr(tokens);
			first.registers["$4"] = 4;
			first.registers["$5"] = 5;
			first.registers["$6"] = 0;
			first.registers["$21"] = 3;

			
		}
		{
			

				string text = " .data\nA = 5\nB = 5\nC = 2\nD = 4\n";
				string text2 = "lw $4, A\n addu $5,$6, B\n";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["D"] == 4);

				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				
				REQUIRE(first.registers["$4"] == 5);
				first.executing_instr();
				REQUIRE(first.registers["$5"] == 5);
		}
		//cout << "==========================================================================" << endl;
			{//test00.asm
			string text = R"(
            .data

)";
			string text2 = R"(
.text
main:	j main)";
			istringstream i(text);
			TokenList tokens = tokenize(i);
			VirtualMachine first;
			first.setting_data_values(tokens);
			istringstream i1(text2);
			TokenList token = tokenize(i1);
			first.saving_instr(token);
			first.executing_instr();
			first.executing_instr();
			first.executing_instr();
			first.executing_instr();
			first.executing_instr();
			first.executing_instr();
			first.executing_instr(); 
			first.executing_instr();
			first.executing_instr();
			first.executing_instr();
		}
		//cout << "==========================================================================" << endl;
				{//test01.asm
			string text = R"(
            .data
        .space 8
var1:   .word 1
var2:   .word -2
)";
			string text2 = R"(
			 .text
main:
     	la $t0, var1

	lw $t1, 0
	lw $t2, $t0
	lw $t3, 4($t0)
	lw $t4, 4(var1)
	lw $t5, var2)";
			istringstream i(text);
			TokenList tokens = tokenize(i);
			VirtualMachine first;
			first.setting_data_values(tokens);
			istringstream i1(text2);
			TokenList token = tokenize(i1);
			first.saving_instr(token);
			first.executing_instr();
			REQUIRE(first.memory.at(12) == 0xfe);
			REQUIRE(first.registers["$8"] == 8);
			first.executing_instr();
			REQUIRE(first.registers["$9"] == 0);
			first.executing_instr();
			REQUIRE(first.registers["$10"] == 1);
			first.executing_instr();
			REQUIRE(first.registers["$11"] == -2);
			first.executing_instr();

			REQUIRE(first.registers["$12"] == -2);
			first.executing_instr();
			REQUIRE(first.registers["$13"] == -2);
		}
				{//test02.asm
			string text = R"(
            .data
r1:     .space 4
r2:     .space 12
r3:     .space 4
var:    .word 7
)";
			string text2 = R"(
			 .text
main:
        la $t0, r2
     	lw $t1, var

	sw $t1, 0
	sw $t1, $t0
	sw $t1, 4($t0)
	sw $t1, 8(r2)
	sw $t1, r3)";
			istringstream i(text);
			TokenList tokens = tokenize(i);
			VirtualMachine first;
			first.setting_data_values(tokens);
			istringstream i1(text2);
			TokenList token = tokenize(i1);
			first.saving_instr(token);
			first.executing_instr();
			REQUIRE(first.index_intrs["r2"] == 4);
			REQUIRE(first.registers["$8"] == 4);
			first.executing_instr();
			REQUIRE(first.registers["$9"] == 7);
			first.executing_instr();
			REQUIRE(first.memory.at(0) == 7);
			first.executing_instr();
			REQUIRE(first.memory.at(4) == 7);
			first.executing_instr();
			REQUIRE(first.memory.at(8) == 7);
			first.executing_instr();
			REQUIRE(first.memory.at(20) == 7);
			first.executing_instr();
			REQUIRE(first.memory.at(20) == 7);
		}
		{//test03.asm
			string text = R"(
.data
				A = 0
				B = 1
				C = 2
				D = 4)";
			string text2 = R"(
				.text
				main :
			li $t0, 100
				li $t1, A
				li $t2, B
				li $t3, C
				li $t4, D)";
			istringstream i(text);
			TokenList tokens = tokenize(i);
			VirtualMachine first;
			first.setting_data_values(tokens);
			REQUIRE(first.constants["D"] == 4);

			istringstream i1(text2);
			TokenList token = tokenize(i1);
			first.saving_instr(token);
			first.executing_instr();
			REQUIRE(first.registers["$8"] == 100);
			first.executing_instr();
			REQUIRE(first.registers["$9"] == 0);
			first.executing_instr();
			REQUIRE(first.registers["$10"] == 1);
			first.executing_instr();
			REQUIRE(first.registers["$11"] == 2);
			first.executing_instr();
			REQUIRE(first.registers["$12"] == 4);
		}
			{//test04.asm
				string text = R"(
 .data
VALUE = -1234
)";
				string text2 = R"(
				main:
        li $t0, VALUE
        move $t1, $t0
        move $t2, $t1
        move $t3, $t2
        move $t4, $t3
        move $t5, $t4
        move $t6, $t5
        move $t7, $t6)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == -1234);

				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$10"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$11"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$12"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$13"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$14"] == -1234);
				first.executing_instr();
				REQUIRE(first.registers["$15"] == -1234);

			}

			{//test05.asm
				string text = R"(
   .data
VALUE = -1
var:    .word 1)";
				string text2 = R"(
				.text
main:
        lw $t0, var
        add $t1, $t0, VALUE
        add $t2, $t1, $t0)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == -1);

				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$10"] == 1);

			}
			{//test06.asm
				string text = R"(
         .data
VALUE = 12
var:    .word 31
					)";
				string text2 = R"(
				     .text
main:
        lw $t0, var
        addu $t1, $t0, VALUE # 31+12=43
        addu $t2, $t1, $t0 # 43+31=74)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 12);
				REQUIRE(first.memory.at(0) == 31);
				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 31);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 43);
				first.executing_instr();
				REQUIRE(first.registers["$10"] == 74);

			}
			//cout << "rta" << endl;
			{//test07.asm


				string text = R"(
  .data
VALUE = 2
var1:   .word 1
var2:   .word 12
var3:   .word -1
					)";
				string text2 = R"(
				  .text
main:
        lw $t0, var1
        lw $t1, var2
        lw $t2, var3
        sub $t3, $t0, VALUE # 1-2 = -1
        sub $t4, $t1, $t0 # 12-1 = 11
        sub $t5, $t2, VALUE # -1-2 = -3)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 2);

				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 12);
				first.executing_instr();
				REQUIRE(first.registers["$10"] == -1);
				first.executing_instr();
				REQUIRE(first.registers["$11"] == -1);
				first.executing_instr();
				REQUIRE(first.registers["$12"] == 11);
				first.executing_instr();
				REQUIRE(first.registers["$13"] == -3);


			}
			{//test08.asm
				string text = R"(
   .data
VALUE = 2
var1:   .word 1
var2:   .word 12
var3:   .word -1
					)";
				string text2 = R"(
				 .text
main:
        lw $t0, var1
        lw $t1, var2
        lw $t2, var3
        subu $t3, $t0, VALUE # 1-2 = -1 = 4294967295
        subu $t4, $t1, $t0 # 12-1 = 11
        subu $t5, $t2, VALUE # -1-2 = -3 = 4294967293)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 2);

				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 12);
				first.executing_instr();
				REQUIRE(first.registers["$10"] == -1);
				first.executing_instr();
				REQUIRE(first.registers["$11"] == -1);
				first.executing_instr();
				REQUIRE(first.registers["$12"] == 11);
				first.executing_instr();
				REQUIRE(first.registers["$13"] == -3);
			}
			//cout << "fowee" << endl;
			{//test 09.asm
				string text = R"(
   .data
VALUE = 4
VALUE2 = -4
var1:   .word 2
var2:   .word -2
var3:   .word 1073741824 # = 2^30
					)";
				string text2 = R"(
				 .text
main:
        lw $t0, var1
        li $t1, VALUE
        mult $t0, $t1 # 2*4 = 8
        mflo $t8
        mfhi $t9

        lw $t0, var2
        lw $t1, var1
        mult $t0, $t1 # -2*2 = -4 
        mflo $t8
        mfhi $t9

        lw $t0, var3
        li $t1, VALUE
        mult $t0, $t1 # 1073741824*4 = 4294967296 (overflow)
        mflo $t8
        mfhi $t9

        lw $t0, var3
        li $t1, VALUE2
        mult $t0, $t1 # 1073741824*-4 = -4294967296 (overflow)
        mflo $t8
        mfhi $t9)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 4);
				REQUIRE(first.memory.at(4) == 0xfe);
				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 2);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 8);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == -2);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 2);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == -4);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == -1);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1073741824);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 1);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1073741824);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == -4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == -1);
				
			}
			{//test 10.asm
				string text = R"(
     .data
VALUE = 4
var1:   .word 2
var2:   .word 1073741824 # = 2^30
					)";
				string text2 = R"(
				.text
main:
        lw $t0, var1
        li $t1, VALUE
        mult $t0, $t1 # 2*4 = 8
        mflo $t8
        mfhi $t9

        lw $t0, var2
        li $t1, VALUE
        mult $t0, $t1 # 1073741824*4 = 4294967296 (overflow)
        mflo $t8
        mfhi $t9
	)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 4);
				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 2);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 8);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1073741824);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 1);
				
			}
			{//test 11.asm
				string text = R"(
    .data
VALUE = 4
VALUE2 = -4
var1:   .word 2
var2:   .word -2
var3:   .word 1073741824 # = 2^30
					)";
				string text2 = R"(
				 .text
main:
        lw $t0, var1
        li $t1, VALUE
        div $t0, $t1 # 2/4 = 0 rem 2
        mflo $t8
        mfhi $t9

        lw $t0, var2
        lw $t1, var1
        div $t0, $t1 # -2/2 = -1 rem 0 
        mflo $t8
        mfhi $t9

        lw $t0, var3
        li $t1, VALUE
        div $t0, $t1 # 1073741824/4 = 268435456 rem 0
        mflo $t8
        mfhi $t9

        lw $t0, var3
        li $t1, VALUE2
        div $t0, $t1 # 1073741824/-4 = -268435456 rem 0 
        mflo $t8
        mfhi $t9

        # divide by 0
        div $t0, $0)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 4);
				REQUIRE(first.memory.at(4) == 0xfe);
				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 2);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 2);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == -2);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 2);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == -1);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1073741824);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 268435456);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 1073741824);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == -4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == -268435456);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 0);
			}
				{//test 12.asm
				string text = R"(
            .data
VALUE = 4
var1:   .word 2
var2:   .word 1073741825 # = 2^30+1
					)";
				string text2 = R"(
				  .text
main:
        lw $t0, var1
        li $t1, VALUE
        div $t0, $t1 # 2/4 = 0 rem 2
        mflo $t8
        mfhi $t9

        lw $t0, var2
        li $t1, VALUE
        div $t0, $t1 # 1073741825/4 = 268435456 rem 1
        mflo $t8
        mfhi $t9

        # divide by 0
        div $t0, $0)";
				istringstream i(text);
				TokenList tokens = tokenize(i);
				VirtualMachine first;
				first.setting_data_values(tokens);
				REQUIRE(first.constants["VALUE"] == 4);
				istringstream i1(text2);
				TokenList token = tokenize(i1);
				first.saving_instr(token);
				first.executing_instr();
				REQUIRE(first.registers["$8"] == 2);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 0);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 2);
				first.executing_instr();
				
				REQUIRE(first.registers["$8"] == 1073741825);
				first.executing_instr();
				REQUIRE(first.registers["$9"] == 4);
				first.executing_instr();
				first.executing_instr();
				REQUIRE(first.registers["$24"] == 268435456);
				first.executing_instr();
				REQUIRE(first.registers["$25"] == 1);

			}
					{//test 13.asm
					string text = R"(
           .data
VALUE = 3
var1:   .word 12
var2:   .word 10
					)";
					string text2 = R"(
				 .text
main:
        lw $t0, var1
        lw $t1, var2
        and $t2, $t0, $t1  
        and $t2, $t0, VALUE)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					REQUIRE(first.constants["VALUE"] == 3);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 12);
					first.executing_instr();
					REQUIRE(first.registers["$9"] == 10);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 8);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 0);
			}
					{//test 14.asm
					string text = R"(
            .data
VALUE = 3
var1:   .word 12
var2:   .word 10
					)";
					string text2 = R"(
				 .text
main:
        lw $t0, var1
        lw $t1, var2
        nor $t2, $t0, $t1  
        nor $t2, $t0, VALUE)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					REQUIRE(first.constants["VALUE"] == 3);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 12);
					first.executing_instr();
					REQUIRE(first.registers["$9"] == 10);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == -15);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == -16);
				}
				{//test 15.asm
					string text = R"(
             .data
VALUE = 3
var1:   .word 12
var2:   .word 10
					)";
					string text2 = R"(
				 .text
main:
        lw $t0, var1
        lw $t1, var2
        or $t2, $t0, $t1  
        or $t2, $t0, VALUE)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					REQUIRE(first.constants["VALUE"] == 3);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 12);
					first.executing_instr();
					REQUIRE(first.registers["$9"] == 10);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 14);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 15);
				}
				{//test 16.asm
					string text = R"(
              .data
VALUE = 3
var1:   .word 12
var2:   .word 10
					)";
					string text2 = R"(
				 .text
main:
        lw $t0, var1
        lw $t1, var2
        xor $t2, $t0, $t1  
        xor $t2, $t0, VALUE)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					REQUIRE(first.constants["VALUE"] == 3);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 12);
					first.executing_instr();
					REQUIRE(first.registers["$9"] == 10);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 6);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 15);
				}
				{//test 17.asm
					string text = R"(
           .data
VALUE = 3
var1:   .word 12
var2:   .word 10)";
					string text2 = R"(
				  .text
main:
        lw $t0, var1
        lw $t1, var2
        not $t2, $t0
        not $t2, $t1
        not $t2, VALUE)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					REQUIRE(first.constants["VALUE"] == 3);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					//cout << first.line2 << endl;
					REQUIRE(first.registers["$8"] == 12);
					first.executing_instr();
					//cout << first.line2 << endl;
					REQUIRE(first.registers["$9"] == 10);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == -13);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == -11);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == -4);
				}
					{//test18.asm
					string text2 = R"(
				.text
main:
        nop
        j next
        nop
next:
        nop
        j main)";

					VirtualMachine first;
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 0);
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 0);
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
				}
				//cout << "::::::::::::::::::::" << endl;
					{//test19.asm I will need to check this
					string text = R"(
           .data
var0:   .word 0
var1:   .word 1
var2:   .word 2
var3:   .word 3)";
					string text2 = R"(
				  .text
main:
        lw $t0, var0
        lw $t1, var1
        lw $t2, var2
        lw $t3, var3

        beq $t0, $t1, check1
        beq $t0, $t0, check1
        nop
check1:
        bne $t0, $t0, check2 
        bne $t0, $t1, check2
        nop
check2:
        bgt $t0, $t0, check3
        bgt $t3, $t1, check3
        nop
check3:
        bge $t0, $t1, check4
        bge $t3, $t2, check4
        nop
check4:
        blt $t3, $t1, check5
        blt $t1, $t3, check5
        nop
check5:
        ble $t3, $t1, check6
        ble $t3, $t3, check6
        nop
check6:
        nop
        j check6)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 0);
					first.executing_instr();
					REQUIRE(first.registers["$9"] == 1);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 2);
					first.executing_instr();
					REQUIRE(first.registers["$11"] == 3);
					first.executing_instr();
					first.executing_instr();
					//good so far
					first.executing_instr();
					
					first.executing_instr();

					first.executing_instr();

					first.executing_instr();

					first.executing_instr();
					//jfound
					first.executing_instr();

				}
						{//test20.asm
					string text = R"(
           .data
n:		.word 10
sumOfSquares:	.word 0
)";
					string text2 = R"(
			.text
main:
	lw $t0,n
	li $t1,1
	li $t2,0

sumLoop:
	mult $t1, $t1
    mflo $t3
	add $t2, $t2, $t3
	add $t1, $t1, 1
	sw  $t2, sumOfSquares

end:
	j end)";
					istringstream i(text);
					TokenList tokens = tokenize(i);
					VirtualMachine first;
					first.setting_data_values(tokens);
					istringstream i1(text2);
					TokenList token = tokenize(i1);
					first.saving_instr(token);
					first.executing_instr();
					REQUIRE(first.registers["$8"] == 10);
					first.executing_instr();
					REQUIRE(first.registers["$9"] == 1);
					first.executing_instr();
					REQUIRE(first.registers["$10"] == 0);
					first.executing_instr();
					first.executing_instr();
					REQUIRE(first.registers["$11"] == 1);
					first.executing_instr();
					REQUIRE(first.registers["$11"] == 1);
					first.executing_instr();
					first.executing_instr();
					REQUIRE(first.memory.at(4) == 1);
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();
					first.executing_instr();

				}	
}