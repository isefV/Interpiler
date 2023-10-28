#include"main.h"

int main() {

	//_code_line = "	if ((10  + 5)%2==0) :";
	//_code_line = "if (a[3] / 3 == 0 ) :"; // a;#=;3;
	//_code_line = "a #=  3 + 1, 0, 2, 6, 8 ";
	_code_line = "rutin pow(a,b,c):";
	//_code_line = "rutin pow(a):";
	//_code_line = "pow(a,b)";
	//_code_line = "loop (!ro):";
	//_code_line = "loop (!ro != true):";
	//_code_line = "		loop (x:5 to a):";
	//_code_line = "		loop (x:5 to 10 by +1):";
	//_code_line = "		loop ( 4 + 5 > 10):";
	//_code_line = "c='hello world'";
	//_code_line = "x=6-8";
	//_code_line = "x = 8";
	//_code_line = "x =  5 * ( 7 + 2) > 12";
	//_code_line = "x =  5 * ( 7 + 2) > 12 / 2";
	//_code_line = "ret d,s";
	//_code_line = "else:";
	//_code_line = "stop";
	//_code_line = "Next";
	//_code_line = "y = true";
	//_code_line = "if(x:";
	//_code_line = "loop x:5 to b:";

	__trans_machine.run(&_code_line);
	//__bytecode_handler.display_bytecode_handler();




	return 0;
}