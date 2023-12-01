#include"main.h"

int main() {
	__input_controler.set_filename("TEST_FILE.txt");
	__command = __input_controler.read_line_file();
	__command = __input_controler.read_line_file();

	// @Debug : test line
	if(debug_mode)
		PRINT << __command <<'\n';

	VEC<TOKEN*>* tokens = __lexer.run(&__command);
	VEC<EXPRESSION*>* exp = __syntaxer.run(tokens);
	//__semanticer.run(tokens, exp);
	return 0;
}