#include"main.h"

int main() {
	__input_controler.set_filename("TEST_FILE.txt");
	__command = __input_controler.read_line_file();
	__command = __input_controler.read_line_file();

	// @Debug : test line
	PRINT << __command <<'\n';

	__syntaxer.run(__lexer.run(&__command));
	return 0;
}