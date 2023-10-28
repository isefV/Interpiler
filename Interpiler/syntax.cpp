#include"syntax.h"

// SYNTAX SECTION
// PRIVATE : SYNTAX MACHIN MEMBER FUNCTION
void SYNTACTIC_M::parse(TOKEN_L* token) {
	TOKEN_L* token_item = token;
	unit index = 0;
	int token_size = token->get_size();

	while (token_item != nullptr) {

		int token_code = token_item->get_self_code(), token_id = token_item->get_id();
		int is_syntax = syntaxer(token_code, index, token_size);

		if (is_syntax == REFUSE) {
			if (_keyword.is_if_elf() || _keyword.is_loop() || _keyword.is_rutin())
				__errors_handler.set_token("if | elf | loop | rutin");
			else if (_keyword.is_input()
				|| _keyword.is_output())
				__errors_handler.set_token("input | output");
			else if (_keyword.is_else())
				__errors_handler.set_token("else");
			else if (_keyword.is_stop()
				|| _keyword.is_next())
				__errors_handler.set_token("stop | next | ret");
			__errors_handler.rise_err(ERR_SYNTAX);
		}
		else if (is_syntax == ACCEPT_NO_ACTION) {
			index++;
			token_item = token_item->remove();
			continue;
		}

		_exp.push(token_code, token_id);

		if (((token_code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC))
			|| ((token_code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC))
			|| ((token_code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + OTHER_OPERATORS + OTH_L_REF))
			|| ((token_code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + OTHER_OPERATORS + OTH_R_REF))) {
			index++;
			token_item = token_item->remove();
			continue;
		}

		index++;
		token_item = token_item->go_next();
	}

	// @Debug: test line
	//print << "\nNODE\tLEVEL\tID\t\tIS TREE?\n\nROOT\t";
	token_item->display();
	_exp.display();
}

int SYNTACTIC_M::syntaxer(int code, int index, int token_size) {

	if ((code & DELIMITER_UPCODE) == KEYWORDS) {
		if ((_keyword.is_if()
			|| _keyword.is_if_elf()
			|| _keyword.is_else()
			|| _keyword.is_rutin()
			|| _keyword.is_ret()
			|| _keyword.is_stop()
			|| _keyword.is_next()
			|| _keyword.is_loop()
			|| _keyword.is_output())
			&& (index == 0))
			return ACCEPT_ACTION;
		else if (_keyword.is_loop()
			&& ((code & DELIMITER_MIDCODE) == TO)
			&& (index == 5 || index == 3))
			return ACCEPT_ACTION;
		else if (_keyword.is_loop()
			&& ((code & DELIMITER_MIDCODE) == BY)
			&& (index == 7 || index == 5))
			return ACCEPT_ACTION;
		else if (_keyword.is_loop()
			&& ((code & DELIMITER_MIDCODE) == BY)
			&& (index == 7 || index == 5))
			return ACCEPT_ACTION;
		else if (_keyword.is_input()
			&& (index == 2))
			return ACCEPT_ACTION;
	}
	else if ((code & DELIMITER_UPCODE) == OPERATORS) {
		if ((code & DELIMITER_MIDCODE_LEFT) == SEPRATOR_OPERATORS) {
			if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_L_BRAC)
				&& (_keyword.is_if_elf()
					|| _keyword.is_else()
					|| _keyword.is_rutin()
					|| _keyword.is_ret()
					|| _keyword.is_stop()
					|| _keyword.is_next()
					|| _keyword.is_loop()
					|| _keyword.is_output())
				&& (index == 1))
				return ACCEPT_NO_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_L_BRAC)
				&& (_keyword.is_if_elf()
					|| _keyword.is_else()
					|| _keyword.is_rutin()
					|| _keyword.is_ret()
					|| _keyword.is_stop()
					|| _keyword.is_next()
					|| _keyword.is_loop()
					|| _keyword.is_output())
				&& (index > 1 && index < token_size - 2))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_L_BRAC)
				&& _keyword.is_no_keyword()
				&& (index > 1 && index < token_size ))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_R_BRAC)
				&& (_keyword.is_if_elf()
					|| _keyword.is_rutin()
					|| _keyword.is_loop())
				&& (index == token_size - 2))
				return ACCEPT_NO_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_R_BRAC)
				&& (_keyword.is_output()
					|| _keyword.is_else())
				&& (index == token_size - 1))
				return ACCEPT_NO_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_R_BRAC)
				&& (_keyword.is_if_elf()
					|| _keyword.is_else()
					|| _keyword.is_rutin()
					|| _keyword.is_ret()
					|| _keyword.is_stop()
					|| _keyword.is_next()
					|| _keyword.is_loop()
					|| _keyword.is_output())
				&& (index > 1 && index < token_size - 2))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_R_BRAC)
				&& _keyword.is_no_keyword()
				&& (index > 1 && index < token_size))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_COLON)
				&& (_keyword.is_if_elf()
					|| _keyword.is_else()
					|| _keyword.is_rutin()
					|| _keyword.is_loop())
				&& (index == token_size - 1))
				return ACCEPT_NO_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_COLON)
				&& _keyword.is_loop()
				&& (index == 3))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_COMMA)
				&& _keyword.is_rutin()
				&& (index > 3 && index < token_size - 1))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == SEP_COMMA)
				&& (index > 2 && index < token_size - 1))
				return ACCEPT_ACTION;
		}
		else if ((code & DELIMITER_MIDCODE_LEFT) == ASSIGNMENT_OPERATORS) {
			if (index == 1)
				return ACCEPT_ACTION;
		}
		else if (((code & DELIMITER_MIDCODE_LEFT) == LOGICAL_OPERATORS)
			|| ((code & DELIMITER_MIDCODE_LEFT) == ARITHMETIC_OPERATORS)) {
			if ((_keyword.is_if_elf()
				|| _keyword.is_loop()
				|| _keyword.is_loop())
				&& (index > 1 && index < token_size - 2))
				return ACCEPT_ACTION;
			else if (_keyword.is_output()
				&& (index > 1 && index < token_size - 1))
				return ACCEPT_ACTION;
			else if (_keyword.is_no_keyword()
				&& (index > 1 && index < token_size - 1))
				return ACCEPT_ACTION;
		}
		else if ((code & DELIMITER_MIDCODE_LEFT) == OTHER_OPERATORS) {
			if ((((code & DELIMITER_MIDCODE_RIGHT) == OTH_L_REF)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == OTH_R_REF)))
				return ACCEPT_ACTION;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == OTH_TYPE)
				&& (index > 1))
				return ACCEPT_ACTION;
		}
	}
	else if ((code & DELIMITER_UPCODE) == IDENTIFIER) {
		if (_keyword.is_rutin()
			&& (code & DELIMITER_MIDCODE_RIGHT) == FUNC
			&& (index == 1))
			return ACCEPT_ACTION;
		else if ((_keyword.is_rutin()
			&& (code & DELIMITER_MIDCODE_RIGHT) != FUNC)
			&& (index > 2 && index < token_size - 2))
			return ACCEPT_ACTION;
		else if ((_keyword.is_if_elf()
			|| _keyword.is_loop())
			&& (index > 1 && index < token_size - 2))
			return ACCEPT_ACTION;
		else if (_keyword.is_output()
			&& (index > 1 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (_keyword.is_input()
			&& (index > 3 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (_keyword.is_no_keyword())
			return ACCEPT_ACTION;
	}
	else if ((code & DELIMITER_UPCODE) == LITERALS) {
		if ((_keyword.is_if_elf()
			|| _keyword.is_loop())
			&& (index > 1 && index < token_size - 2))
			return ACCEPT_ACTION;
		else if (_keyword.is_output()
			&& (index > 1 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (_keyword.is_input()
			&& (index > 3 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (_keyword.is_no_keyword())
			return ACCEPT_ACTION;
	}

	return REFUSE;

	// LOOP, IF, ELF SYNTAX IS : KEYWORD ( EXP ) :
	//if ((_keyword.is_if_elf()
	//	|| _keyword.is_loop())
	//	&& (index == 1 || index == token_size - 2 || index == token_size - 1))
	//	return (upcode == (OPERATORS + SEPRATOR_OPERATORS))
	//	&& ((index == 1 && downcode == SEP_L_BRAC)
	//		|| (index == token_size - 2 && downcode == SEP_R_BRAC)
	//		|| (index == token_size - 1 && downcode == SEP_COLON));
	//// RUTIN SYNTAX IS : RUTIN FUNC_NAME ( EXP ) :
	//else if (_keyword.is_rutin()
	//	&& (index == 2 || index == token_size - 2 || index == token_size - 1))
	//	return (upcode == (OPERATORS + SEPRATOR_OPERATORS))
	//	&& ((index == 2 && downcode == SEP_L_BRAC)
	//		|| (index == token_size - 2 && downcode == SEP_R_BRAC)
	//		|| (index == token_size - 1 && downcode == SEP_COLON));
	//// OUTPUT SYNTAX IS : KEYWORD ( EXP )
	//else if ( _keyword.is_output()
	//	&& (index == 1 || index == token_size - 1))
	//	return (upcode == (OPERATORS + SEPRATOR_OPERATORS))
	//	&& ((index == 1 && downcode == SEP_L_BRAC)
	//		|| (index == token_size - 1 && downcode == SEP_R_BRAC));
	//// ELS SYNTAX IS : KEYWROD :
	//else if ((_keyword.is_else())
	//	&& (index == token_size - 1))
	//	//token->get_self_code() == (OPERATORS + SEPRATOR_OPERATORS + SEP_COLON)))
	//	return (upcode == (OPERATORS + SEPRATOR_OPERATORS))
	//	&& (index == 1 && downcode == SEP_COLON);
	//// STOP, NEXT SYNTAX IS : KEYWROD
	//else if ((_keyword.is_next() || _keyword.is_stop())
	//	&& (index == 1))
	//	return true;
	//// INPUT SYNTAX IS : IDENT = KEYWORD ( EXP )
	//else if (_keyword.is_input()
	//	&& (index == 1 || index == 3 || index == token_size - 1))
	//	return (upcode == (OPERATORS + SEPRATOR_OPERATORS) 
	//		|| upcode == (OPERATORS + ASSIGNMENT_OPERATORS))
	//	&& ((index == 1 && downcode == SEP_L_BRAC)
	//		|| (index == token_size - 1 && downcode == SEP_R_BRAC));
}

// @Debug: test func
//void SYNTACTIC_M::display(EXPRESSION_L* root) {
//	print << level << '\t' << std::hex << root->get_code() << '\t' << root->is_tree() << '\n';
//	if (!root->is_tree())
//		return;
//	level++;
//	print << "L\t";
//	display_tree(root->get_childs(false), level);	// left
//	print << "R\t";
//	display_tree(root->get_childs(true), level);	// right
//}

// PUBLIC : SYNTAX MACHIN MEMBER FUNCTION
EXPRESSION_L* SYNTACTIC_M::run(TOKEN_L* tokens) {
	parse(tokens);
	return &_exp;
}

void  SYNTACTIC_M::refresh() {
	_exp.purify();
}