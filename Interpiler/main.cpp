
#include"utility.h"
#include"lexical.h"
#include"syntax.h"
#include"interpreter.h"
#include"compiler.h"
#include"asm_handler.h"
#include"program.h"

unit	_current_level = 0 , _last_level = 0, _code_line_size = 0, _current_line = 0, _paran = 0;
str _code_line, _program;

stackint _loop_stk, _func_stk, _loop_end, _loop_step;
stackbool _condition_state;

bool _compile_mod = false;

int _jump_mod = NOJUMP;

OBJECT _objects;
TOKEN _tokens;
EXPRESSION _exp, * _condition_exp;;


int main() {
	_condition_state.push(false);
	//asm_create_files();

	//program_forward();

	//_code_line = "	if ((10  + a)%2==0) :";
	//_code_line = "if (a[3] / 3 == 0 ) :"; // a#;3;
	//_code_line = "a #=  3 , 0 ";
	//_code_line = "rutin pow(a,b):";
	//_code_line = "pow(a,b)";
	//_code_line = "loop (!ro):";
	//_code_line = "loop (!ro != tru):";
	//_code_line = "		loop (x:5 to a):";
	//_code_line = "		loop (x:5 to 10):";
	//_code_line = "c='hello world'";
	//_code_line = "x+=6-8";
	//_code_line = "x = 8";
	_code_line = "x =  5 * ( 7 + 2) < 12";
	//_code_line = "ret d,s";
	//_code_line = "else:";
	//_code_line = "stop";
	//_code_line = "Next";
	//_code_line = "y = true";
	//_code_line = "if(x:";
	//_code_line = "loop x:5 to b:";


	lex_tokenization(&_code_line);
	sytx_preparation();

	if (_compile_mod)
		comp_parse_tree();
	else
		interp_parse_tree();

	//utl_neutralization();

	//cmd = "x = 6";

	//lex_tokenization(&_code_line);
	//sytx_preparation();

	//utl_neutralization();

	//cmd = "x*= 2 ";

	//lex_tokenization(&_code_line);
	//sytx_preparation();

	return 0;
}