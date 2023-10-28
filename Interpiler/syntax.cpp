#include"syntax.h"
#include"lexical.h"
#include "error_handling.h"

void sytx_preparation() {
	TOKEN* token = &_tokens;
	unit index = 0, syntax_movement = 0;
	int keyword_code = 0;

	while (token != nullptr) {

		// IF FIRST TOKEN IS KEYWORD
		if (index == 0 && token->get_self_code('u') == KEYWORDS) {
			keyword_code = token->get_self_code();
			index++;
			token = token->go_next();
			continue;
		}

		// IF TOKENS HAS KEYWORD + EXP
		if (keyword_code != 0) {

			// LOOP, IF, ELF SYNTAX IS : KEYWORD ( EXP ) :
			if ((keyword_code == (KEYWORDS + IF)
				|| (keyword_code == (KEYWORDS + LOOP))
				|| (keyword_code == (KEYWORDS + ELF)))
				&& ((index == 1 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC))
					|| (index == _tokens_size - 2 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC))
					|| (index == _tokens_size - 1 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_COLON))))
				syntax_movement++;

			// RUTIN SYNTAX IS : RUTIN FUNC_NAME ( EXP ) :
			else if ((keyword_code == (KEYWORDS + RUTIN))
				&& ((index == 2 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC))
					|| (index == _tokens_size - 2 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC))
					|| (index == _tokens_size - 1 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_COLON))))
				syntax_movement++;

			// INPUT, OUTPUT SYNTAX IS : KEYWORD ( EXP )
			else if ((keyword_code == (KEYWORDS + INPUT) || (keyword_code == (KEYWORDS + OUTPUT))
				&& (index == 1 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC))
				|| (index == _tokens_size - 1 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC))))
				syntax_movement++;

			// ELS SYNTAX IS : KEYWORD :
			else if (keyword_code == (KEYWORDS + ELSE)
				&& (index == _tokens_size - 1 && token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_COLON)))
				syntax_movement++;

			// STOP, NEXT SYNTAX IS : KEYWORD

			// RET SYNTAX IS : KEYWORD EXP

			else
				_exp.push(token->get_self_code());

			index++;
			token = token->go_next();
			continue;
		}

		// IF TOKENS HAS EXP
		_exp.push(token->get_self_code());
		index++;
		token = token->go_next();
	}

	// IF SYNTAX HAS MORE OR LESS THAT GRAMMER SHOW ERROR
	if (keyword_code != 0) {
		if ((keyword_code == (KEYWORDS + IF)
			|| keyword_code == (KEYWORDS + LOOP)
			|| keyword_code == (KEYWORDS + ELF)
			|| keyword_code == (KEYWORDS + RUTIN))
			&& syntax_movement % 3 != 0)
			rise_err(ERR_SYNTAX, _current_line, "if | loop | elf | rutin");
		else if ((keyword_code == (KEYWORDS + INPUT)
			|| keyword_code == (KEYWORDS + OUTPUT))
			&& syntax_movement % 2 != 0)
			rise_err(ERR_SYNTAX, _current_line, "input | output");
		else if ((keyword_code == (KEYWORDS + ELSE))
			&& syntax_movement % 1 != 0)
			rise_err(ERR_SYNTAX, _current_line, "else");
		else if ((keyword_code == (KEYWORDS + STOP)
			|| keyword_code == (KEYWORDS + NEXT)
			|| keyword_code == (KEYWORDS + RET))
			&& syntax_movement != 0)
			rise_err(ERR_SYNTAX, _current_line, "stop | next | ret");

	}

	// @Debug: test line
	print << "\nNODE\tLEVEL\tID\t\tIS TREE?\n\nROOT\t";
	display_tree(&_exp, 0);
}

