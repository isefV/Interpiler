#include"lexical.h"


//bool is_func = false;
//STRING func_name = "";

// LEXICAL SECTION
// PRIVATE : LEXICAL MACHIN MEMBER FUNCTION
int LEXICAL_M::line_level_detector() {
	int level = 0, index = 0;
	char current_ch = _command->at(0);

	// SPECIFIC INDENTATION / LEVEL
	while (current_ch == 32 || current_ch == 9) {
		level += current_ch == 9 ? 4 : 1;
		index++;
		current_ch = _command->at(index);
	}

	return index;
}

void LEXICAL_M::purification() {
	int index = 0, len = _command->length();
	bool isnt_punc = false, is_text = false;
	char current_ch = '\0', next_ch = 0;
	STRING token = "";

	index = line_level_detector();
	current_ch = _command->at(index);
	index++;

	// READ COMMAND LINE CHARACTER BY CHARACTER
	// SPLIT EACH COMPONENT AND IGNORE SPACES
	while (index <= len) {

		// IF SEEN ; DON'T READ COMMENTS
		if (current_ch == 59)
			break;

		//	IF CHAR IS ' | " SET TRUE IS TEXT FLAG
		if ((token[0] == current_ch) || token.length() == 0 && (current_ch == 34 || current_ch == 39)) {
			is_text = !is_text;
			token += "'";
			current_ch = index < len ? _command->at(index) : '\0';
			if(current_ch == '\0')
				_decomposed_command.push_back(token);
			index++;
			continue;
		}

		if (is_text) {
			token += current_ch;
			current_ch = index < len ? _command->at(index) : '\0';
			index++;
			continue;
		}

		// IF A-Z | a-z | 0-9 | _
		if ((is_text && current_ch != 39 && current_ch != 34) || (current_ch > 64 && current_ch < 91)
			|| (current_ch > 96 && current_ch < 123)
			|| (current_ch > 47 && current_ch < 58)
			|| current_ch == 46 || current_ch == 95) {

			// LOWERCASE LANG
			token += tolower(current_ch);

			// SET ISN'T PUNCTUATION FLAG TRUE FOR DELIMITER 
			isnt_punc = true;
		}
		// IF !%&()*+,-./ :<=>? []^ |#
		else if ((current_ch > 32 && current_ch < 48 && current_ch != 36)
			|| ((current_ch > 57 && current_ch < 64))
			|| current_ch == 91 || current_ch == 93 || current_ch == 94
			|| current_ch == 124) {

			//	IF DELIMITER FLAG TRUE THAT MEANS 
			//	TOKEN READY TO DELIMITER THEN SET
			//	FLAG TO FALSE
			if (isnt_punc) {
				_decomposed_command.push_back(token);
				token = "";
			}

			isnt_punc = false;

			//	CHECK NEXT CHAR TO CREATE TOKEN ONE OP | TWO OP
			next_ch = index < len ? _command->at(index) : '\0';

			// IF !*+-/<=>^#
			//	THIS OPERATOR HAS TWO PART
			if (next_ch == 61 && (current_ch == 33 || current_ch == 42
				|| current_ch == 43 || current_ch == 45 || current_ch == 47
				|| current_ch == 60 || current_ch == 61 || current_ch == 62
				|| current_ch == 94 || current_ch == 35)) {
				token += current_ch;
				token += next_ch;
				index++;
			}
			else {
				token += current_ch;
			}

			if(!is_text){
				_decomposed_command.push_back(token);
				token = "";
			}
		}

		// IF SPACES | TAB AND LAST CHAR ISN'T PUNCTUATION SET DELIMITER
		else if (isnt_punc && (current_ch == 32 || current_ch == 9)) {
			_decomposed_command.push_back(token);
			token = "";
			isnt_punc = false;
		}

		current_ch = index < len ? _command->at(index) : '\0';
		index++;
	}

	if (isnt_punc) {
		_decomposed_command.push_back(token);
		token = "";
	}

	// @Debug : test line
	for (auto iter = _decomposed_command.begin(); iter != _decomposed_command.end(); iter++) {
		PRINT << *iter << "  ";
	}

}

void LEXICAL_M::tokenization() {

	purification();

	// CODEED TOKEN COMPONENT
	for (int index = 0; index < _decomposed_command.size(); index++) {

		STRING temp = _decomposed_command.at(index);
		int code = token_detector(&temp);

		_tokens[index] = code;
		//if(code == COMPONENTS_NON)
			//__errors_handler.rise_err(ERR_TYPE);

	}

	// @Debug : test line
	PRINT << "\nTokens:\n";
	for (auto item = _tokens.begin(); item != _tokens.end(); item++)
		PRINT << '\t' << std::hex << item->first << '\t' << item->second << '\n';
	PRINT << '\n';

	PRINT << "\Objects:\n";
	for (auto item = __objects_table.begin(); item != __objects_table.end(); item++)
		PRINT << '\t' << std::hex << item->first << '\t' << item->second->_value << '\t' << item->second->_is_temp << '\n';
	PRINT << '\n';

	PRINT << std::dec << "\nToken size : " << _tokens.size()
		<< "\t\tObject size : " << __objects_table.size() << '\n';

}

int LEXICAL_M::token_detector(STRING* token) {
	int code = COMPONENTS_NON;

	// IF TOKEN IS KEYWORD_ RETURN 0xZZZ00000 KEYWORD_ CODE
	if ((code = keyword_detector(token)) != COMPONENTS_NON) {
		if (code == KYW_TRUE)
			return set_object(token, (COMPONENTS_LITERALS + TYPE_BOOL));
		else if (code == KYW_FALSE)
			return set_object(token, (COMPONENTS_LITERALS + TYPE_BOOL));

		return COMPONENTS_KEYWORDS + code;
	}
	// IF TOKEN IS OPERATORS RETURN 0xZZZ00000 OPERATOR CODE
	else if ((code = operator_detector(token)) != OP_NON)
		return COMPONENTS_OPERATORS + code;

	// IF TOKEN IS OBJECT_T RETURN 0x4ZZAAAAA IDENTIFIER CODE | 0x3ZZAAAAA LITERALS CODE
	else if ((code = object_detector(token)) != TYPE_NONT)
		return code;

	// ELSE ITS WRONG SYNTAX
	return COMPONENTS_NON;
}

int LEXICAL_M::keyword_detector(STRING* token) {
	if (*token == "loop")
		return KYW_LOOP;
	else if (*token == "if")
		return KYW_IF;
	else if (*token == "elf")
		return KYW_ELF;
	else if (*token == "else")
		return KYW_ELSE;
	else if (*token == "to")
		return KYW_TO;
	else if (*token == "by")
		return KYW_BY;
	else if (*token == "rutin")
		return KYW_RUTIN;
	else if (*token == "ret")
		return KYW_RET;
	else if (*token == "stop")
		return KYW_STOP;
	else if (*token == "next")
		return KYW_NEXT;
	else if (*token == "input")
		return KYW_INPUT;
	else if (*token == "output")
		return KYW_OUTPUT;
	else if (*token == "true")
		return KYW_TRUE;
	else if (*token == "false")
		return KYW_FALSE;

	// ELSE ITS WRONG SYNTAX
	return TYPE_NONT;
}

int LEXICAL_M::operator_detector(STRING* token) {
	if (*token == "=")
		return OP_ASSIGNMENT + OP_ASN_ASSIGNMENT;
	else if (*token == "^=")
		return OP_ASSIGNMENT + OP_ASN_POWASSI;
	else if (*token == "*=")
		return OP_ASSIGNMENT + OP_ASN_MULASSI;
	else if (*token == "/=")
		return OP_ASSIGNMENT + OP_ASN_DIVASSI;
	else if (*token == "%=")
		return OP_ASSIGNMENT + OP_ASN_MODASSI;
	else if (*token == "-=")
		return OP_ASSIGNMENT + OP_ASN_SUBASSI;
	else if (*token == "+=")
		return OP_ASSIGNMENT + OP_ASN_ADDASSI;
	else if (*token == "#=")
		return OP_ASSIGNMENT + OP_ASN_ARRASSI;

	if (*token == "(")
		return OP_SEPRATOR + OP_SEP_LEFT_PARENTHESE;
	else if (*token == ")")
		return OP_SEPRATOR + OP_SEP_RIGHT_PARENTHESE;
	else if (*token == ".")
		return OP_SEPRATOR + OP_SEP_DOT;
	else if (*token == ",")
		return OP_SEPRATOR + OP_SEP_COMMA;
	else if (*token == ":")
		return OP_SEPRATOR + OP_SEP_COLON;


	if (*token == "!")
		return OP_LOGICAL + OP_LOG_OPPOSITE;
	else if (*token == ">")
		return OP_LOGICAL + OP_LOG_GREATER_THAN;
	else if (*token == "<")
		return OP_LOGICAL + OP_LOG_LESS_THAN;
	else if (*token == "<=")
		return OP_LOGICAL + OP_LOG_LESS_EQUAL;
	else if (*token == ">=")
		return OP_LOGICAL + OP_LOG_GREATER_EQUAL;
	else if (*token == "!=")
		return OP_LOGICAL + OP_LOG_NOT_EQUAL;
	else if (*token == "==")
		return OP_LOGICAL + OP_LOG_EQUAL;
	else if (*token == "&")
		return OP_LOGICAL + OP_LOG_AND;
	else if (*token == "|")
		return OP_LOGICAL + OP_LOG_OR;


	if (*token == "^")
		return OP_ARITHMETIC + OP_ARI_POW;
	else if (*token == "*")
		return OP_ARITHMETIC + OP_ARI_MUL;
	else if (*token == "/")
		return OP_ARITHMETIC + OP_ARI_DIV;
	else if (*token == "%")
		return OP_ARITHMETIC + OP_ARI_MOD;
	else if (*token == "-")
		return OP_ARITHMETIC + OP_ARI_SUB;
	else if (*token == "+")
		return OP_ARITHMETIC + OP_ARI_ADD;


	if (*token == "[")
		return OP_OTHER + OP_OTR_LEFT_BRACKET;
	else if (*token == "]")
		return OP_OTHER + OP_OTR_RIGHT_BREACKET;
	else if (*token == "?")
			return OP_OTHER + OP_OTR_TYPE;

	// ELSE ITS WRONG SYNTAX
	return OP_NON;
}

int LEXICAL_M::object_detector(STRING* token) {

	// IF TOKEN HAVE " | ' OP BEFORE AND AFTER IT HAS STRING TYPE
	if ( token->at(0) == token->at(token->length() - 1) && token->at(0) == '\'')
		return set_object(token, (COMPONENTS_LITERALS + TYPE_STR));

	bool is_digit = true;
	char* current_ch = &(*token)[0];

	while (*current_ch != '\0') {
		if (!((*current_ch > 47 && *current_ch < 58) || *current_ch == 46)) {
			is_digit = false;
			break;
		}
		current_ch++;
	}

	// IF ALL TOKEN CHAR IS DIGIT , SO ITS NUMBER TYPE
	if (is_digit)
		return set_object(token, (COMPONENTS_LITERALS + TYPE_NUM));

	// IF TOKEN ISN'T START WITH NUMBER , ITS IDENTIFIER
	if (!((*token)[0] > 47 && (*token)[0] < 58))
		return set_object(token, (COMPONENTS_IDENTIFIER + TYPE_NONT));

	// ELSE ITS WRONG SYNTAX
	return TYPE_NONT;
}

int LEXICAL_M::set_object(STRING* token, int type) {

	// FIND HASH ID OF STRING FOR SET ID
	int code_id = object_encoder_id(*token);

	// CHECK IF HAS BEEN OBJECT_T CREATE JUST RETURN CODE ID
	if (__objects_table.find(code_id) != __objects_table.end())
		return type + __objects_table.at(code_id)->_type + code_id;

	// CREATE NEW ADDRESS
	void* value = utl_generate_address();
	int var_type = TYPE_NONT;

	// FOR TYPE OF DATA SET VALUE TO ADDRESS
	if ((type & MIDCODE_RIGHT) == TYPE_NUM) {
		(*(float*)value) = atof(&(*token)[0]);
		var_type = TYPE_NUM;
	}
	else if ((type & MIDCODE_RIGHT) == TYPE_BOOL) {
		(*(bool*)value) = *token == "true" ? true : false;
		var_type = TYPE_BOOL;
	}
	else if ((type & MIDCODE_RIGHT) == TYPE_STR) {
		*(char**)value = utl_set_string(*token);
		var_type = TYPE_STR;
	}

	// CREATE OBJECT_T 
	OBJECT* temp = new OBJECT;
	temp->_type = var_type;
	temp->_value = value;
	temp->_is_temp = true;

	__objects_table[code_id] = temp;

	return type + code_id;
}

// PUBLIC : LEXICAL MACHIN MEMBER FUNCTION
MAP<int,int>* LEXICAL_M::run(STRING* cmd) {
	_command = cmd;
	tokenization();
	return &_tokens;
}