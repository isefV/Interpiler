#include"syntactic.h"

// SYNTAX SECTION
// PRIVATE : SYNTAX MACHIN MEMBER FUNCTION
void SYNTACTIC_M::parse(MAP<int,int>* token) {

	VEC<int> reomve_id;
	int token_size = token->size();

	for (auto iter = token->begin() ; iter != token->end(); iter++) {

		int token_id = iter->first;
		int token_code = iter->second;

		int is_syntax = syntaxer(&token_code, token_id, token_size);

		if (is_syntax == REFUSE) {
			if (TOKEN_IS_KEYWORD(token_code,KYW_IF)
				|| TOKEN_IS_KEYWORD(token_code, KYW_ELF)
				|| TOKEN_IS_KEYWORD(token_code, KYW_LOOP)
				|| TOKEN_IS_KEYWORD(token_code, KYW_RUTIN))
				__errors_handler.set_token("if | elf | loop | rutin");
			else if (TOKEN_IS_KEYWORD(token_code, KYW_INPUT)
				|| TOKEN_IS_KEYWORD(token_code, KYW_OUTPUT))
				__errors_handler.set_token("input | output");
			else if (TOKEN_IS_KEYWORD(token_code, KYW_ELSE))
				__errors_handler.set_token("else");
			else if (TOKEN_IS_KEYWORD(token_code, KYW_STOP)
				|| TOKEN_IS_KEYWORD(token_code, KYW_NEXT))
				__errors_handler.set_token("stop | next | ret");
			__errors_handler.rise_err(ERR_SYNTAX);
		}
		else if (is_syntax == ACCEPT_NO_ACTION) {
			reomve_id.push_back(token_id);
			continue;
		}
		EXPRESSION* temp = new EXPRESSION;

		temp->_id = token_id;
		temp->_priority = parse_priority(token_code) ;
		temp->_mode = parse_mode(token_code);

		if (((token_code & (UPCODE + MIDCODE)) == (COMPONENTS_OPERATORS + OP_SEPRATOR + OP_SEP_LEFT_PARENTHESE))
			|| ((token_code & (UPCODE + MIDCODE)) == (COMPONENTS_OPERATORS + OP_SEPRATOR + OP_SEP_RIGHT_PARENTHESE))
			|| ((token_code & (UPCODE + MIDCODE)) == (COMPONENTS_OPERATORS + OP_OTHER + OP_OTR_LEFT_BRACKET))
			|| ((token_code & (UPCODE + MIDCODE)) == (COMPONENTS_OPERATORS + OP_OTHER + OP_OTR_RIGHT_BREACKET))) {
			reomve_id.push_back(token_id);
			continue;
		}

		if (temp->_priority != PRIO_NO) {
			temp->_priority += _paren_counter + _brac_counter;
			_exp.push_back(temp);
		}
	}

	SORT(_exp.begin(), _exp.end(), priority_compare);

	for (int index =  0; index < reomve_id.size(); index++) {
		auto itr = token->find(reomve_id.at(index));
		token->erase(itr);
	}

	// @Debug: test line
	PRINT << "\nTokens:\n";
	for (auto item = token->begin(); item != token->end(); item++)
		PRINT << '\t' << std::hex << item->first << '\t' << item->second << '\n';
	PRINT << "\nExpression:\n";
	for (auto item = _exp.begin(); item != _exp.end(); item++)
		PRINT << '\t' << std::dec << (*item)->_id << '\t' << (*item)->_priority << '\t' << (*item)->_mode << '\t' << '\n';
	PRINT << '\n';
}

int SYNTACTIC_M::syntaxer(int* code, int index, int token_size) {

	if ((*code & UPCODE) == COMPONENTS_KEYWORDS) {
		if ((TOKEN_IS_KEYWORD(*code, KYW_IF)
			|| TOKEN_IS_KEYWORD(*code, KYW_ELF)
			|| TOKEN_IS_KEYWORD(*code, KYW_ELSE)
			|| TOKEN_IS_KEYWORD(*code, KYW_RUTIN)
			|| TOKEN_IS_KEYWORD(*code, KYW_RET)
			|| TOKEN_IS_KEYWORD(*code, KYW_STOP)
			|| TOKEN_IS_KEYWORD(*code, KYW_NEXT)
			|| TOKEN_IS_KEYWORD(*code, KYW_LOOP)
			|| TOKEN_IS_KEYWORD(*code, KYW_OUTPUT))
			&& (index == 0)) {
			_keyword = *code;
			return ACCEPT_ACTION;
		}
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
			&& TOKEN_IS_KEYWORD(*code, KYW_TO)
			&& (index == 5 || index == 3))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
			&& TOKEN_IS_KEYWORD(*code, KYW_BY)
			&& (index == 7 || index == 5))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
			&& TOKEN_IS_KEYWORD(*code, KYW_BY)
			&& (index == 7 || index == 5))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
			&& (index == 2))
			return ACCEPT_ACTION;
	}
	else if ((*code & UPCODE) == COMPONENTS_OPERATORS) {
		if ((*code & MIDCODE_LEFT) == OP_SEPRATOR) {
			if (((*code & MIDCODE_RIGHT) == OP_SEP_LEFT_PARENTHESE)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_IF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELSE)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT))
				&& (index == 1))
				return ACCEPT_NO_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_LEFT_PARENTHESE)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN)
				&& (index == 2)))
				return ACCEPT_NO_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_LEFT_PARENTHESE)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_IF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELSE)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT))
				&& (index > 1 && index < token_size - 2))
				return ACCEPT_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_LEFT_PARENTHESE)
				&& (index > 1 && index < token_size))
				return ACCEPT_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_RIGHT_PARENTHESE)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_IF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP))
				&& (index == token_size - 2))
				return ACCEPT_NO_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_RIGHT_PARENTHESE)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELSE))
				&& (index == token_size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_RIGHT_PARENTHESE)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_IF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELSE)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT))
				&& (index > 1 && index < token_size - 2))
				return ACCEPT_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_RIGHT_PARENTHESE)
				&& (index > 1 && index < token_size))
				return ACCEPT_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_COLON)
				&& (TOKEN_IS_KEYWORD(_keyword, KYW_IF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_ELSE)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN)
					|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP))
				&& (index == token_size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_COLON)
				&& TOKEN_IS_KEYWORD(_keyword, KYW_LOOP)
				&& (index == 3))
				return ACCEPT_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_COMMA)
				&& TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN)
				&& (index > 3 && index < token_size - 1))
				return ACCEPT_NO_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_SEP_COMMA)
				&& (index > 2 && index < token_size - 1))
				return ACCEPT_NO_ACTION;
		}
		else if ((*code & MIDCODE_LEFT) == OP_ASSIGNMENT) {
			if (index == 1)
				return ACCEPT_ACTION;
		}
		else if (((*code & MIDCODE_LEFT) == OP_LOGICAL)
			|| ((*code & MIDCODE_LEFT) == OP_ARITHMETIC)) {
			if ((TOKEN_IS_KEYWORD(_keyword, KYW_IF)
				|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
				|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP))
				&& (index > 1 && index < token_size - 2))
				return ACCEPT_ACTION;
			else if (TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT)
				&& (index > 1 && index < token_size - 1))
				return ACCEPT_ACTION;
			else if (index > 1 && index < token_size - 1)
				return ACCEPT_ACTION;
		}
		else if ((*code & MIDCODE_LEFT) == OP_OTHER) {
			if ((((*code & MIDCODE_RIGHT) == OP_OTR_LEFT_BRACKET)
				|| ((*code & MIDCODE_RIGHT) == OP_OTR_RIGHT_BREACKET)))
				return ACCEPT_ACTION;
			else if (((*code & MIDCODE_RIGHT) == OP_OTR_TYPE)
				&& (index > 1))
				return ACCEPT_ACTION;
		}
	}
	else if ((*code & UPCODE) == COMPONENTS_IDENTIFIER) {
			//&& (code & MIDCODE_RIGHT) == TYPE_FUNC
		if (TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN)
			&& index == 1) {
			__objects_table.edit(*code, (*code & (UPCODE + DOWNCODE)) + TYPE_FUNC);
			*code = (*code & (UPCODE + DOWNCODE)) + TYPE_FUNC;
			return ACCEPT_ACTION;
		}
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN)
			&& (index > 2 && index < token_size - 2))
			return ACCEPT_ACTION;
		else if ((TOKEN_IS_KEYWORD(_keyword, KYW_IF)
			|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
			|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP))
			&& (index > 1 && index < token_size - 2))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT)
			&& (index > 1 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_INPUT)
			&& (index > 3 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_NON))
			return ACCEPT_ACTION;
	}
	else if ((*code & UPCODE) == COMPONENTS_LITERALS) {
		if ((TOKEN_IS_KEYWORD(_keyword, KYW_IF)
			|| TOKEN_IS_KEYWORD(_keyword, KYW_ELF)
			|| TOKEN_IS_KEYWORD(_keyword, KYW_LOOP))
			&& (index > 1 && index < token_size - 2))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_OUTPUT)
			&& (index > 1 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_INPUT)
			&& (index > 3 && index < token_size - 1))
			return ACCEPT_ACTION;
		else if (TOKEN_IS_KEYWORD(_keyword, KYW_NON))
			return ACCEPT_ACTION;
	}

	return REFUSE;
}

int SYNTACTIC_M::parse_priority(int code) {

	if ((code & UPCODE) == COMPONENTS_LITERALS)
		return PRIO_NO;

	if ((code & UPCODE) == COMPONENTS_KEYWORDS) {
		if ((code & MIDCODE) == KYW_TO) {
			return PRIO_13;
		}
		else if ((code & MIDCODE) == KYW_BY) {
			return PRIO_12;
		}
		else if ((code & MIDCODE) == KYW_RUTIN) {
			return PRIO_MOST + PRIO_MOST;
		}
		return PRIO_LEAST;
	}
	else if ((code & UPCODE) == COMPONENTS_OPERATORS) {
		if ((code & MIDCODE_LEFT) == OP_SEPRATOR) {
			if ((code & MIDCODE_RIGHT) == OP_SEP_LEFT_PARENTHESE) {
				INC(_paren_counter, PRIO_MOST);
				if (TOKEN_IS_KEYWORD(_keyword,KYW_RUTIN))
					is_args = true;
				return PRIO_NO;
			}
			else if ((code & MIDCODE_RIGHT) == OP_SEP_RIGHT_PARENTHESE) {
				LESS_THAN_ZERO(_paren_counter, PRIO_MOST);
				DEC(_paren_counter, PRIO_MOST);
				if (TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN))
					is_args = false;
				return PRIO_NO;
			}
			else if ((code & MIDCODE_RIGHT) == OP_SEP_COMMA) {
				if (TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN))
					return PRIO_NO;
				return PRIO_1;
			}
			else if ((code & MIDCODE_RIGHT) == OP_SEP_COLON)
				return PRIO_14;

		}
		else if ((code & MIDCODE_LEFT) == OP_ARITHMETIC) {
			if ((code & MIDCODE_RIGHT) == OP_ARI_POW)
				return PRIO_10;
			else if (((code & MIDCODE_RIGHT) == OP_ARI_DIV)
				|| ((code & MIDCODE_RIGHT) == OP_ARI_MUL))
				return PRIO_9;
			else if ((code & MIDCODE_RIGHT) == OP_ARI_MOD)
				return PRIO_8;
			else if (((code & MIDCODE_RIGHT) == OP_ARI_SUB)
				|| ((code & MIDCODE_RIGHT) == OP_ARI_ADD))
				return PRIO_7;
		}
		else if ((code & MIDCODE_LEFT) == OP_LOGICAL) {
			if ((code & MIDCODE_RIGHT) == OP_LOG_OPPOSITE)
				return PRIO_11;
			else if (((code & MIDCODE_RIGHT) == OP_LOG_GREATER_THAN)
				|| ((code & MIDCODE_RIGHT) == OP_LOG_LESS_THAN)
				|| ((code & MIDCODE_RIGHT) == OP_LOG_GREATER_EQUAL)
				|| ((code & MIDCODE_RIGHT) == OP_LOG_LESS_EQUAL)
				|| ((code & MIDCODE_RIGHT) == OP_LOG_NOT_EQUAL)
				|| ((code & MIDCODE_RIGHT) == OP_LOG_EQUAL))
				return PRIO_6;
			else if ((code & MIDCODE_RIGHT) == OP_LOG_AND)
				return PRIO_5;
			else if ((code & MIDCODE_RIGHT) == OP_LOG_OR)
				return PRIO_4;
		}
		else if ((code & MIDCODE_LEFT) == OP_OTHER) {
			if ((code & MIDCODE_RIGHT) == OP_OTR_LEFT_BRACKET) {
				INC(_brac_counter,PRIO_MOST);
				return PRIO_NO;
			}
			else if ((code & MIDCODE_RIGHT) == OP_OTR_RIGHT_BREACKET) {
				LESS_THAN_ZERO(_brac_counter, PRIO_MOST);
				DEC(_brac_counter, PRIO_MOST);
				return PRIO_NO;
			}
			return PRIO_11;
		}
		else if ((code & MIDCODE_LEFT) == OP_ASSIGNMENT) {
			if ((code & MIDCODE_RIGHT) == OP_ASN_ARRASSI)
				return PRIO_3;
			return PRIO_2;
		}
	}
	else if ((code & UPCODE) == COMPONENTS_IDENTIFIER) {
		if (((code & MIDCODE_LEFT) == TYPE_ARR)
			|| (!TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN) && ((code & MIDCODE_RIGHT) == TYPE_FUNC))) {
			return PRIO_15;
		}
		else if (is_args && TOKEN_IS_KEYWORD(_keyword, KYW_RUTIN))
			return PRIO_15;
	}

	return PRIO_NO;
}

int SYNTACTIC_M::parse_mode(int code) {

	if ((code & UPCODE) == COMPONENTS_KEYWORDS) {
		if ((code & MIDCODE) == KYW_TO) {
			return MODE_BINARY;
		}
		else if ((code & MIDCODE) == KYW_BY) {
			return MODE_BINARY;
		}
		return MODE_KEYWORD;
	}

	if ((code & UPCODE) == COMPONENTS_IDENTIFIER) {
		if ((code & MIDCODE_LEFT) == TYPE_ARR)
			return MODE_ARR;
		else if ((code & MIDCODE_RIGHT) == TYPE_FUNC)
			return MODE_FUNC;
		return MODE_ARGS;
	}
	else if (((code & (UPCODE + MIDCODE)) == (COMPONENTS_OPERATORS + OP_LOGICAL + OP_LOG_OPPOSITE))
		|| ((code & (UPCODE + MIDCODE)) == (COMPONENTS_OPERATORS + OP_OTHER + OP_OTR_TYPE)))
		return MODE_UNARY;
	return MODE_BINARY;
}

// PUBLIC : SYNTAX MACHIN MEMBER FUNCTION
VEC<EXPRESSION*>* SYNTACTIC_M::run(MAP<int,int>* tokens) {
	_keyword = COMPONENTS_KEYWORDS + KYW_NON;
	_paren_counter = 0;
	_brac_counter = 0;
	is_args = false;
	parse(tokens);
	return &_exp;
}
