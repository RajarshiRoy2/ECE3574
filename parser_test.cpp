#include "catch.hpp"

#include "parser.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
//better way of tests as well
TEST_CASE("whole_parser", "[parser]")
{
	{
		string s = "345";
		string s1 = "A122343289";
		Parser w;

		REQUIRE(w.tokens(s1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.integer() == false);
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.integer() == true);

	}

	{
		string s = "\"absdsfsfc\"";
		string s1 = "UUUEEQWEQWSAD";
		Parser w;
		REQUIRE(w.tokens(s1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.string_check() == false);
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.string_check() == true);
	}

	{
		Parser w;
		string s = ".asciiz";
		string s1 = "123asdqw.asciiz";
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.layout() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.layout() == true);
	}
	
	{
		string s = ".word";
		string s1 = "1239awo";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.intlayout() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.intlayout() == true);
		//cout << "gine" << endl;
	}
	{
		string s = "2ufhsrd=122933";
		string s1 = "AAA123ord 1254123987";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.constant() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.constant() == false);
	}
	{

		string s = "iajhd:";
		string s1 = "A2dq1";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.label() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.label() == true);


	}
	{
		string s = "2ufhsrd=122933";
		string s1 = "AAA123ord 1254123987";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.constant() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.constant() == false);
	}
	{
		string s = ".half 22210";
		string s1 = ".byte ";
		string tru = ".byte 100,200";
		string tru1 = ".ascii \"hasd12awd\"";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.layout2() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(tru) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(tru1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
	}
	{
		string s = "2ufhsrd=122933";
		string s1 = "AAA123ord 1254123987";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.constant() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.constant() == false);
	}
	{
		string s = ".half 2272";
		string s1 = ".word ";
		string tru = ".byte 25,69,79";
		string tru1 = ".ascii\"hasiudho\"";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == false);
		REQUIRE(w.tokens(tru) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(tru1) == true);
		REQUIRE(w.layout2() == true);
	}


	{
		string s = ".half 2382";
		string s1 = ".word 1937489273648";
		string tru = ".byte 256";
		string tru1 = ".ascii \"384732fd\"";
		Parser w;

		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == false);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(tru) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == false);
		REQUIRE(w.tokens(tru1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
	}
	{
		string s = ".half 2500,60";
		string s1 = ".word  -25,-2500 ";
		string t2 = ".half -127,-120000,+128";
	
		Parser w;

		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.layout2() == true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s1) == true);
		REQUIRE(w.layout2() ==true);
		//cout << "gine" << endl;
		REQUIRE(w.tokens(t2) == true);
		REQUIRE(w.layout2() == false);
		//cout << "gine" << endl;
	}

	{
		string s = ".half 2230";
		string s1 = ".word ";
		string tru = ".byte -17,-10,+127";
		//cout << "gine" << endl;
		string tru1 = ".ascii 1212";
		Parser w;
		//cout << "gine" << endl;
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.layout2() == true);
		REQUIRE(w.tokens(s1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == false);
		REQUIRE(w.tokens(tru) == true);
		//cout << "gine" << endl;
		REQUIRE(w.layout2() == true);
		REQUIRE(w.tokens(tru1) == true);
		REQUIRE(w.layout2() == false);
		//cout << "gine" << endl;
	}



	{
		string s = "value = 123";
		string s1 = ".half ";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "gine" << endl;
		REQUIRE(w.decleration() == true);
		REQUIRE(w.tokens(s1) == true);
		//cout << "gine" << endl;
		REQUIRE(w.decleration() == false);
	}
	//test section as same part here
	{
		string wq = "$asjdh";
		Parser w;
		REQUIRE(w.tokens(wq) == true);
		//cout << "euyg" << endl;
		REQUIRE(w.register_check() == false);
		//cout << "gine" << endl;
		string trus = "li $5, 123";
		Parser w1;
		REQUIRE(w1.tokens(trus) == true);
		//cout << "gine" << endl;
		REQUIRE(w1.li() == true);
	}
	{
		Parser w;
		string wq = "mult $zero,$zero";
		string yu = "mult $11,$2is";
		REQUIRE(w.tokens(wq) == true);
		//cout << "g123" << endl;
		REQUIRE(w.opst() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(yu) == true);
		//cout << "g123" << endl;
		REQUIRE(w.opst() == false);
		//cout << "g123" << endl;
	}

	{
		
		string y = "mult";
		string t1 = "$2";
		Parser w;
		string t2 = "87(erpo)";
		REQUIRE(w.tokens(y) == true);
		//cout << "g123" << endl;
		REQUIRE(w.mememorycheck() == true);
		REQUIRE(w.tokens(t1) == true);
		//cout << "g123" << endl;
		REQUIRE(w.mememorycheck() == true);
		REQUIRE(w.tokens(t2) == true);
		//cout << "g123" << endl;
		REQUIRE(w.mememorycheck() == true);
	} 
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}

	{
		Parser w;
		string t = "add $1,$2,12123123";
		string f = "a1d $2,$t6,123232";
		REQUIRE(w.tokens(f) == true);
		//cout << "g123" << endl;
		REQUIRE(w.srss() == false);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(t) == true);
		//cout << "g123" << endl;
		REQUIRE(w.srss() == true);

	}
	
	{
		Parser w;
		string trus = "$7";
		string falsestr = "$";
		REQUIRE(w.tokens(trus) == true);
		//cout << "g123" << endl;
		REQUIRE(w.register_check() == true);
		REQUIRE(w.tokens(falsestr) == true);
		//cout << "g123" << endl;
		REQUIRE(w.register_check() == false);
	}
	//cout << "g123" << endl;
	{

		string tr = "beq $3, $t4,mult:";
		string tr2 = "bne $qwe,11237y,mult";
		Parser w;
		//cout << "g123" << endl;
		string tr1 = "bne $11,13434,mult";
		REQUIRE(w.tokens(tr) == true);
		REQUIRE(w.open() == false);
		REQUIRE(w.tokens(tr1) == true);
		//cout << "g123" << endl;
		REQUIRE(w.open() == true);
		REQUIRE(w.tokens(tr2) == true);
		REQUIRE(w.open() == false);
		//cout << "g123" << endl;
	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	{
		Parser w;
		
		string t2 = "bne $zero,12a34,mult";
		string tr = "beq $1, $t0,mult";
		string t1 = "bne $1,1234,mult";
		REQUIRE(w.tokens(tr) == true);
		//cout << "g123" << endl;
		REQUIRE(w.open() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(t1) == true);
		//cout << "g123" << endl;
		REQUIRE(w.open() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(t2) == true);
		//cout << "g123" << endl;
		REQUIRE(w.open() == false);
	}

	{
		Parser w;
		string tr = "mult: beq $12, $s2,mult";
		string tr1 = "bne $1,1234,mult";
		//cout << "g123" << endl;
		string tr2 = "mult:";
		string tr3 = ".text \n \n";
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr) == true);
		REQUIRE(w.text() == true);
		REQUIRE(w.tokens(tr1) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		REQUIRE(w.tokens(tr2) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr3) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);

	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	{
		Parser w;
		string tr = "mfhi $1";
		//cout << "g123" << endl;
		string tr1 = "not $1,1234";
		string tr2 = "mult:";
		//cout << "g123" << endl;
		string tr3 = ".text \n \n";
		REQUIRE(w.tokens(tr) == true);
		REQUIRE(w.opress() == true);
		//cout << "g123" << endl;
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr1) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr2) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr3) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}

	{
		//cout << "g123" << endl;
		string s = ".data \n n: .word 10 \n 	sumOfSquares: .word 0 \n	.text \n main: \n lw $t0, n \n li $t1, 1 \n li $t2, 0 \n \n sumLoop: \n 	mul $t3, $t1, $t1 \n add $t2, $t2, $32	# parse error \n add $t1, $t1, 1 \n	ble $t1, $t0, sumLoop \n	sw  $t2, sumOfSquares \n \n 	end: \n j end";
		Parser w;
		//cout << "g123" << endl;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
	}

	
	{
		Parser w;
		string tr = ".data\nvar1: .word 1024 var1 = 1024\n var2: .half 12  var2 = 12\nvar3: .byte 0                # char var3 = 0\nvar4: .byte 1, 2, 3, 4, 5, 6, 7, # PARSE ERROR\nvar5: .space 512  \nvar6: .ascii \"hello\"\nvar7: .asciiz \"goodbye\"\n.text\n";
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);


	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	{
		Parser w;
		string tr = "mfhi $1";
		//cout << "g123" << endl;
		string tr1 = "not $1,1234";
		string tr2 = "mult:";
		//cout << "g123" << endl;
		string tr3 = ".text \n \n";
		REQUIRE(w.tokens(tr) == true);
		REQUIRE(w.opress() == true);
		//cout << "g123" << endl;
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr1) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr2) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr3) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}


	{
		Parser w;
		string tr = "div $1,$t2,$30";

		string tr2 = "divu $1,$t4,$16";
		string tr3 = "divu $1,$1";
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr) == true);
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr2) == true);
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr3) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);


	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		s = ".text asdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == true);
	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	{
		Parser w;
		string tr = "j asdy";
		string tr2 = "mult:";
		string tr3 = "j asdjh:";
		REQUIRE(w.tokens(tr) == true);
		//cout << "g123" << endl;
		REQUIRE(w.opii() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr2) == true);
		//cout << "g123" << endl;
		REQUIRE(w.text() == true);
		//cout << "g123" << endl;
		REQUIRE(w.tokens(tr3) == true);
		//cout << "g123" << endl;
		REQUIRE(w.opii() == false);
	}
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	//cout << "g123" << endl;
	{
		Parser w; //use same file as tests order
		ofstream test01;
		test01.open("test.txt");
		test01 <<
			R"(		# A test file of data declarations only
	.data
var1:	.word 1024             # int var1 = 1024

var2:	.half 12               # short var2 = 12
	
var3:	.byte 0                # char var3 = 0

var4:	.byte 1, 2, 3, 4, 5, 6, 7, 8  # var4 = {1,2,3,4,5,6,7,8}

var5:	.space 512             # reserve 512 bytes

var6:	.ascii "hello"

var7:	.asciiz "goodbye"

	.text
	
	)";
		test01.close();
		REQUIRE(w.file("test.txt"));
	}

	{
		Parser w;
		string tr = "\nashdjdsgh";
		REQUIRE(w.tokens(tr) == true);
		REQUIRE(w.my_error() == "Error:2:  ashdjdsgh\n");

	}
	//cout << "g123" << endl;
	{
		string s = "asiduh";
		Parser w;
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data asdsdlo";
		REQUIRE(w.tokens(s) == true);
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".text asasdawe";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == false);
		//cout << "g123" << endl;
		s = ".data \n\n";
		REQUIRE(w.tokens(s) == true);
		//cout << "g123" << endl;
		REQUIRE(w.file() == true);
	}
	//cout << "g123" << endl;
	{
		Parser w;
		ofstream test08;
		test08.open("test.txt");
		test08 <<
			R"(	# a test of address modes
	.data
str:	.ascii	"hello"

	.text
main:
	lb $t8, str
	la $t0, str
	lb $t1, ($t0)
	lb $t2, 1($t0)
	lb $t3, 2($t0)
	lb $t4, 3($t0)
	lb $t5, 4($t0)
	
end:	nop
	j end
	

	)";
		test08.close();
		REQUIRE(!w.file("test.txt"));
	}
	//cout << "g123" << endl;
}

