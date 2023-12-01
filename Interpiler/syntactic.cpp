#include"syntactic.h"

// SYNTAX SECTION
// PRIVATE : SYNTAX MACHIN MEMBER FUNCTION
void SYNTACTIC_M::parse(VEC<TOKEN*>* token) {

	VEC<int> reomve_id;
	_size = token->size();
	auto iter = token->begin();
	while ( iter != token->end() ) {

		int token_upcode = (*iter)->get_token_code(DEL_UPPER_CODE);
		int token_upmidcode = (*iter)->get_token_code(DEL_UPPER_MIDDLE_CODE);
		int token_lowmidcode = (*iter)->get_token_code(DEL_LOWER_MIDDLE_CODE);

		int is_syntax = syntaxer(&token_upcode, &token_upmidcode, &token_lowmidcode);

		if (is_syntax == REFUSE) {
			if (token_upcode == KYW_IF
				|| token_upcode == KYW_ELF
				|| token_upcode == KYW_LOOP
				|| token_upcode == KYW_RUTIN)
				__errors_handler.set_token("if | elf | loop | rutin");
			else if (token_upcode == KYW_INPUT
				|| token_upcode == KYW_OUTPUT)
				__errors_handler.set_token("input | output");
			else if (token_upcode == KYW_ELSE)
				__errors_handler.set_token("else");
			else if (token_upcode == KYW_STOP
				|| token_upcode == KYW_NEXT)
				__errors_handler.set_token("stop | next | ret");
			__errors_handler.rise_err(ERR_SYNTAX);
		}
		else if (is_syntax == ACCEPT_NO_ACTION) {
			iter = token->erase(iter);
			continue;
		}
		EXPRESSION* temp = new EXPRESSION;

		temp->_id = token_lowmidcode;
		temp->_priority = parse_priority(&token_upcode, &token_upmidcode) ;
		temp->_mode = parse_mode(&token_upcode, &token_upmidcode);

		if (token_upmidcode == OP_SEPRATOR + OP_SEP_LEFT_PARENTHESE
			|| token_upmidcode ==  OP_SEPRATOR + OP_SEP_RIGHT_PARENTHESE
			|| token_upmidcode ==  OP_OTHER + OP_SEP_LEFT_BRACKET
			|| token_upmidcode ==  OP_OTHER + OP_SEP_RIGHT_BREACKET) {
			iter = token->erase(iter);
			//reomve_id.push_back(token_id);
			continue;
		}

		if (temp->_priority != PRIO_NO) {
			temp->_priority += _paren_counter + _brac_counter;
			_exp.push_back(temp);
		}

		iter++;
	}

	SORT(_exp.begin(), _exp.end(), priority_compare);

	// @Debug: test line
	if (debug_mode) {
		PRINT << "\nTokens:\n";
		for (auto item = token->begin(); item != token->end(); item++)
			PRINT << '\t' << std::hex << (*item)->get_token() << '\n';
		PRINT << "\nExpression:\n";
		for (auto item = _exp.begin(); item != _exp.end(); item++)
			PRINT << '\t' << std::dec << (*item)->_id << '\t' << (*item)->_priority << '\t' << (*item)->_mode << '\t' << '\n';
		PRINT << '\n';
	}
}

int SYNTACTIC_M::syntaxer(const int* upcode, const int* upmidcode, const int* lowmidcode) {

	if (*upcode == COMPONENTS_KEYWORDS) {
		if ((*upmidcode == KYW_IF
			|| *upmidcode == KYW_ELF
			|| *upmidcode == KYW_ELSE
			|| *upmidcode == KYW_RUTIN
			|| *upmidcode == KYW_RET
			|| *upmidcode == KYW_STOP
			|| *upmidcode == KYW_NEXT
			|| *upmidcode == KYW_LOOP
			|| *upmidcode == KYW_OUTPUT)
			&& (*lowmidcode == 0)) {
			if (*upmidcode == KYW_LOOP)
				_syntax_flag[0] = true;
			_keyword = *upmidcode;
			return ACCEPT_ACTION;
		}
		else if (_keyword == KYW_LOOP
			&& *upmidcode == KYW_TO
			&& (*lowmidcode == 5 || *lowmidcode == 3)) {
			_syntax_flag[1] = true;
			return ACCEPT_ACTION;
		}
		else if (_keyword == KYW_LOOP
			&& *upmidcode == KYW_BY
			&& (*lowmidcode == 7 || *lowmidcode == 5)){
			_syntax_flag[2] = true;
			return ACCEPT_ACTION;
		}
		else if (_keyword == KYW_LOOP
			&& (*lowmidcode == 2))
			return ACCEPT_ACTION;
	}
	else if (*upcode == COMPONENTS_OPERATORS) {
		if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_SEPRATOR) {
			if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_PARENTHESE)
				&& ( _keyword == KYW_IF
					|| _keyword == KYW_ELF
					|| _keyword == KYW_ELSE
					|| _keyword == KYW_LOOP
					|| _keyword == KYW_OUTPUT)
				&& ( *lowmidcode == 1))
				return ACCEPT_NO_ACTION;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_PARENTHESE
				&& _keyword == KYW_RUTIN
				&& (*lowmidcode == 2))
				return ACCEPT_NO_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_PARENTHESE)
				&& (_keyword == KYW_IF
					|| _keyword == KYW_ELF
					|| _keyword == KYW_ELSE
					|| _keyword == KYW_LOOP
					|| _keyword == KYW_OUTPUT)
				&& (*lowmidcode > 1 && *lowmidcode < _size - 2))
				return ACCEPT_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_PARENTHESE)
				&& (*lowmidcode > 1 && *lowmidcode < _size))
				return ACCEPT_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_PARENTHESE)
				&& (_keyword == KYW_IF
					|| _keyword == KYW_ELF
					|| _keyword == KYW_RUTIN
					|| _keyword == KYW_LOOP)
				&& (*lowmidcode == _size - 2))
				return ACCEPT_NO_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_PARENTHESE)
				&& (_keyword == KYW_OUTPUT
					|| _keyword == KYW_ELSE)
				&& (*lowmidcode == _size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_PARENTHESE)
				&& (_keyword == KYW_IF
					|| _keyword == KYW_ELF
					|| _keyword == KYW_ELSE
					|| _keyword == KYW_LOOP
					|| _keyword == KYW_OUTPUT)
				&& (*lowmidcode > 1 && *lowmidcode < _size - 2))
				return ACCEPT_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_PARENTHESE)
				&& (*lowmidcode > 1 && *lowmidcode < _size))
				return ACCEPT_ACTION;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_COLON
				&& (_keyword == KYW_IF
					|| _keyword == KYW_ELF
					|| _keyword == KYW_ELSE
					|| _keyword == KYW_RUTIN
					|| _keyword == KYW_LOOP)
				&& (*lowmidcode == _size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_COLON)
				&& _keyword == KYW_LOOP
				&& (*lowmidcode == 3))
				return ACCEPT_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_COMMA)
				&& _keyword == KYW_RUTIN
				&& (*lowmidcode > 3 && *lowmidcode < _size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_COMMA)
				&& (*lowmidcode > 2 && *lowmidcode < _size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_BRACKET
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_BREACKET))
				return ACCEPT_ACTION;
		}
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_ASSIGNMENT) {
			if (*lowmidcode == 1)
				return ACCEPT_ACTION;
		}
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_LOGICAL
			|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_ARITHMETIC) {
			if ((_keyword == KYW_IF
				|| _keyword == KYW_ELF
				|| _keyword == KYW_LOOP)
				&& (*lowmidcode > 1 && *lowmidcode < _size - 2))
				return ACCEPT_ACTION;
			else if (_keyword == KYW_OUTPUT
				&& (*lowmidcode > 1 && *lowmidcode < _size - 1))
				return ACCEPT_ACTION;
			else if (*lowmidcode > 1 && *lowmidcode < _size - 1)
				return ACCEPT_ACTION;
		}
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_OTHER) {
				if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_OTR_TYPE
				&& (*lowmidcode > 1))
				return ACCEPT_ACTION;
		}
	}
	else if (*upcode == COMPONENTS_IDENTIFIER) {
			//&& (code & DEL_LOWER_MIDDLE_CODE) == TYPE_FUNC
		if (_keyword == KYW_RUTIN
			&& *lowmidcode == 1) {
			//__objects_table.at((*code & DEL_LOWER_CODE))->_type = (*code & (DEL_UPPER_CODE + DEL_LOWER_CODE)) + TYPE_FUNC;
			//*code = (*code & (DEL_UPPER_CODE + DEL_LOWER_CODE)) + TYPE_FUNC;
			return ACCEPT_ACTION;
		}
		else if (_keyword == KYW_RUTIN
			&& (*lowmidcode > 2 && *lowmidcode < _size - 2))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_IF
			|| _keyword == KYW_ELF
			|| _keyword == KYW_LOOP
			&& (*lowmidcode > 1 && *lowmidcode < _size - 2))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_OUTPUT
			&& (*lowmidcode > 1 && *lowmidcode < _size - 1))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_INPUT
			&& (*lowmidcode > 3 && *lowmidcode < _size - 1))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_NON)
			return ACCEPT_ACTION;
	}
	else if (*upcode == COMPONENTS_LITERALS) {
		if (_keyword == KYW_IF
			|| _keyword == KYW_ELF
			|| _keyword == KYW_LOOP
			&& (*lowmidcode > 1 && *lowmidcode < _size - 2))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_OUTPUT
			&& (*lowmidcode > 1 && *lowmidcode < _size - 1))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_INPUT
			&& (*lowmidcode > 3 && *lowmidcode < _size - 1))
			return ACCEPT_ACTION;
		else if (_keyword == KYW_NON)
			return ACCEPT_ACTION;
	}

	return REFUSE;
}

int SYNTACTIC_M::parse_priority(const int* upcode, const int* upmidcode) {

	if (*upcode == COMPONENTS_LITERALS)
		return PRIO_NO;

	if (*upcode == COMPONENTS_KEYWORDS) {
		if (*upmidcode == KYW_TO){
			return PRIO_13;
		}
		else if (*upmidcode == KYW_BY) {
			return PRIO_12;
		}
		else if (*upmidcode == KYW_RUTIN) {
			return PRIO_MOST + PRIO_MOST;
		}
		return PRIO_LEAST;
	}
	else if (*upcode == COMPONENTS_OPERATORS) {
		if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_SEPRATOR) {
			if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_PARENTHESE) {
				INC(_paren_counter, PRIO_MOST);
				if (_keyword == KYW_RUTIN)
					is_args = true;
				return PRIO_NO;
			}
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_PARENTHESE) {
				LESS_THAN_ZERO(_paren_counter, PRIO_MOST);
				DEC(_paren_counter, PRIO_MOST);
				if (_keyword == KYW_RUTIN)
					is_args = false;
				return PRIO_NO;
			}
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_LEFT_BRACKET) {
				INC(_brac_counter, PRIO_MOST);
				return PRIO_NO;
			}
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_RIGHT_BREACKET) {
				LESS_THAN_ZERO(_brac_counter, PRIO_MOST);
				DEC(_brac_counter, PRIO_MOST);
				return PRIO_NO;
			}
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_COMMA) {
				if (_keyword == KYW_RUTIN)
					return PRIO_NO;
				return PRIO_1;
			}
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_SEP_COLON)
				return PRIO_14;

		}
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_ARITHMETIC) {
			if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ARI_POW)
				return PRIO_10;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ARI_DIV
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ARI_MUL)
				return PRIO_9;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ARI_MOD)
				return PRIO_8;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ARI_SUB
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ARI_ADD)
				return PRIO_7;
		}
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_LOGICAL) {
			if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_OPPOSITE)
				return PRIO_11;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_GREATER_THAN
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_LESS_THAN
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_GREATER_EQUAL
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_LESS_EQUAL
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_NOT_EQUAL
				|| (*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_EQUAL)
				return PRIO_6;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_AND)
				return PRIO_5;
			else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_LOG_OR)
				return PRIO_4;
		}
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_OTHER)
			return PRIO_11;
		else if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_L) == OP_ASSIGNMENT) {
			if ((*upmidcode & DEL_UPPER_MIDDLE_CODE_R) == OP_ASN_ARRASSI)
				return PRIO_3;
			return PRIO_2;
		}
	}
	else if (*upcode == COMPONENTS_IDENTIFIER) {
		if ((*upmidcode  == TYPE_ARR
			|| _keyword != KYW_RUTIN )
			&& *upmidcode  == TYPE_FUNC) {
			return PRIO_15;
		}
		else if (is_args && _keyword == KYW_RUTIN)
			return PRIO_15;
	}

	return PRIO_NO;
}

int SYNTACTIC_M::parse_mode(const int* upcode, const int* upmidcode) {

	if (*upcode == COMPONENTS_KEYWORDS) {
		if (*upmidcode == KYW_TO) {
			return MODE_BINARY;
		}
		else if (*upmidcode == KYW_BY) {
			return MODE_BINARY;
		}
		else if (*upmidcode == KYW_RUTIN) {
			return MODE_FUNC;
		}
		return MODE_KEYWORD;
	}

	if (*upcode == COMPONENTS_IDENTIFIER) {
		if (*upmidcode == TYPE_ARR)
			return MODE_ARR;
		else if (*upmidcode == TYPE_FUNC)
			return MODE_FUNC;
		return MODE_ARGS;
	}
	else if ((*upcode == COMPONENTS_OPERATORS && *upmidcode == OP_LOGICAL + OP_LOG_OPPOSITE)
		|| (*upcode == COMPONENTS_OPERATORS && *upmidcode == OP_OTHER + OP_OTR_TYPE))
		return MODE_UNARY;
	else if (*upcode == COMPONENTS_OPERATORS && *upmidcode == OP_ASSIGNMENT + OP_ASN_ARRASSI)
		return MODE_ARR;
	return MODE_BINARY;
}

// PUBLIC : SYNTAX MACHIN MEMBER FUNCTION
VEC<EXPRESSION*>* SYNTACTIC_M::run(VEC<TOKEN*>* tokens) {
	_keyword = KYW_NON;
	_paren_counter = 0;
	_brac_counter = 0;
	is_args = false;
	parse(tokens);
	return &_exp;
}
