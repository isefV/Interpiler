#include"translator_machine.h"

// TRANSLATOR MACHIN MEMBER FUNCTION
void TM::run(str* cmd) {
	TOKEN_L* tk = _lexer.run(cmd);
	EXPRESSION_L* exp = _syntaxer.run(tk);
	//_semanticer.run(exp,tk);
}

void TM::refresh() {
	_lexer.refresh();
	_syntaxer.refresh();
}