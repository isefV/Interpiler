
#include"utility.h"
#include"lexical.h"
#include"syntax.h"
#include"interpreter.h"
#include"asm_handler.h"

unit	_current_level = 0, _code_line_size = 0, _current_line = 0, _paran = 0;
str* _code_line;

stackint _loop_stk, _func_stk, _loop_end, _loop_step;
bool _compile_mod = false;

int _jump_mod = NOJUMP;

OBJECT _objects;
TOKEN _tokens;
EXPRESSION _exp, * _condition_exp;;


int main() {

	//asm_create_files();

	//str cmd = "	if ((10  + a)%2==0) :";
	//str cmd = "if (a[3] / 3 == 0 ) :"; // a#;3;
	//str cmd = "a# =  3 , 0 ";
	//str cmd = "rutin pow(a,b):";
	//str cmd = "pow(a,b)";
	//str cmd = "loop (!ro):";
	//str cmd = "loop (!ro != tru):";
	//str cmd = "		loop (x:5 to a):";
	str cmd = "		loop (x:5 to 10):";
	//str cmd = "c='hello world'";
	//str cmd = "x+=6-8";
	//str cmd = "x = 8";
	//str cmd = "x =  5 * ( 7 + 2) > 12";
	//str cmd = "ret d,s";
	//str cmd = "else:";
	//str cmd = "stop";
	//str cmd = "Next";
	//str cmd = "y = true";
	//str cmd = "if(x:";
	//str cmd = "loop x:5 to b:";


	lex_tokenization(&cmd);
	sytx_preparation();

	//utl_neutralization();

	//cmd = "x = 6";

	//lex_tokenization(&cmd);
	//sytx_preparation();

	//utl_neutralization();

	//cmd = "x*= 2 ";

	//lex_tokenization(&cmd);
	//sytx_preparation();

	return 0;
}