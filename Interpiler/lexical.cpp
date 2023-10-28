#include"lexical.h"

bool is_func = false;
str func_name = "";

// LEXICAL SECTION
// PRIVATE : LEXICAL MACHIN MEMBER FUNCTION
int LEXICAL_M::line_level_detector() {
	unit level = 0, index = 0, len = _cmd_string->length();
	char current_ch = _cmd_string->at(0), next_ch = 0;

	// SPECIFIC INDENTATION / LEVEL
	while (current_ch == 32 || current_ch == 9) {
		level += current_ch == 9 ? 4 : 1;
		index++;
		current_ch = _cmd_string->at(index);
	}

	__state_control_machine.set_level(level % 3);

	return index;
}

void LEXICAL_M::purification() {
	unit index = 0, len = _cmd_string->length();
	bool isnt_punc = false, is_text = false;
	char current_ch = '\0', next_ch = 0;
	str cmd_tp = "";

	index = line_level_detector();
	current_ch = _cmd_string->at(index);
	index++;

	// READ COMMAND LINE CHARACTER BY CHARACTER
	// SPLIT EACH COMPONENT AND IGNORE SPACES
	while (index <= len) {

		// IF SEEN ; DON'T READ COMMENTS
		if (current_ch == 59)
			break;

		// IF A-Z | a-z | 0-9 | _
		if ((is_text && current_ch != 39 && current_ch != 34) || (current_ch > 64 && current_ch < 91)
			|| (current_ch > 96 && current_ch < 123)
			|| (current_ch > 47 && current_ch < 58)
			|| current_ch == 46 || current_ch == 95) {

			// LOWERCASE LANG
			if (is_text)
				cmd_tp += current_ch;
			else
				cmd_tp += tolower(current_ch);

			// SET ISN'T PUNCTUATION FLAG TRUE FOR DELIMITER 
			isnt_punc = true;
		}

		// IF !"%&'()*+,-./ :<=>? []^ |#
		else if ((current_ch > 32 && current_ch < 48 && current_ch != 36)
			|| ((current_ch > 57 && current_ch < 64))
			|| current_ch == 91 || current_ch == 93 || current_ch == 94
			|| current_ch == 124) {

			//	IF DELIMITER FLAG TRUE THAT MEANS 
			//	TOKEN READY TO DELIMITER THEN SET
			//	FLAG TO FALSE
			if (isnt_punc)
				cmd_tp += ";";
			isnt_punc = false;

			//	IF CHAR IS ' | " SET TRUE IS TEXT FLAG
			if (current_ch == 34 || current_ch == 39)
				is_text = !is_text;

			//	CHECK NEXT CHAR TO CREATE TOKEN ONE OP | TWO OP
			next_ch = index < len ? _cmd_string->at(index) : '\0';

			// IF !*+-/<=>^#
			//	THIS OPERATOR HAS TWO PART
			if (next_ch == 61 && (current_ch == 33 || current_ch == 42
				|| current_ch == 43 || current_ch == 45 || current_ch == 47
				|| current_ch == 60 || current_ch == 61 || current_ch == 62
				|| current_ch == 94 || current_ch == 35)) {
				cmd_tp += current_ch;
				cmd_tp += next_ch;
				index++;
			}
			else {
				cmd_tp += current_ch;
			}
			cmd_tp += ';';
		}

		// IF SPACES | TAB AND LAST CHAR ISN'T PUNCTUATION SET DELIMITER
		else if (isnt_punc && (current_ch == 32 || current_ch == 9)) {
			cmd_tp += ';';
			isnt_punc = false;
		}

		current_ch = index < len ? _cmd_string->at(index) : '\0';
		index++;
	}

	if (isnt_punc)
		cmd_tp += ";";

	// @Debug : test line
	print << cmd_tp << '\n';

	*_cmd_string = cmd_tp;
}

void LEXICAL_M::tokenization() {

	purification();

	int index = 1, len = _cmd_string->length();
	char current_ch = _cmd_string->at(0), last_ch = '\0', text_ch = '\0';
	str token = "";

	// CODEED TOKEN COMPONENT
	while (index <= len) {

		// IF CHAR IS DELIMITER CREATE TOKEN CODE 
		if (current_ch == ';' && token != "") {

			int code = NOT;
			bool is_text = false;

			// CHECK TOKEN HAVE " | ' OP BEFORE AND AFTER IT
			//  " TEXT " | ' TEXT '
			if (text_ch != '\0')
				is_text = _cmd_string->at(index) == text_ch;

			//	IF FUNCTION MODE TRUE THAT SAVE FUNCTION NAME	
			if (is_func) {
				func_name = token;
				is_func = false;
			}

			//	GET TOKEN CODE BASE ON COMMAND
			code = token_detector(&token, is_text);

			// CHECK FUNCTION COMMAND FOR LABEL VARIABLE FUNCTION
			if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + RUTIN)
				is_func = true;

			//	XTRCT KEYWORD_ TELL THAT FUNCTION END AND VARIABLE BE GLOBAL
			if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + RET)
				func_name = "";

			//	IF CODE ZERO RISE ERROR FOR SYNTAX
			if (code == NOT) {
				__errors_handler.set_token(token);
				__errors_handler.rise_err(ERR_LEXICAL);
			}

			_tokens.push(code);
			text_ch = '\0';
			token = "";
		}
		else if (current_ch != ';') {

			// SET TEXT_CH TO CHECK STRING STARTED ( ' | " ) OR NOT
			if (text_ch == '\0' && (current_ch == 34 || current_ch == 39))
				text_ch = current_ch;
			else
				token += current_ch;
		}

		last_ch = current_ch;
		current_ch = index < len ? _cmd_string->at(index) : '\0';
		index++;
	}

	// @Debug : test line
	_tokens.display();
	print << "\n";
	__objects_table.display();
	print << std::dec << "\nToken size : " << _tokens.get_size()
		<< "\t\tObject size : " << __objects_table.get_size() << '\n';

}

int LEXICAL_M::token_detector(str* token, bool is_text) {
	int code = NOT;

	// IF TOKEN IS KEYWORD_ RETURN 0xZZZ00000 KEYWORD_ CODE
	if ((code = keyword_detector(token)) != NOT) {
		if (_keyword.is_no_keyword())
			_keyword.set(code);
		return KEYWORDS + code;
	}

	// IF TOKEN IS OPERATORS RETURN 0xZZZ00000 OPERATOR CODE
	else if ((code = operator_detector(token)) != NOT)
		return OPERATORS + code;

	// IF TOKEN IS OBJECT_T RETURN 0x4ZZAAAAA IDENTIFIER CODE | 0x3ZZAAAAA LITERALS CODE
	else if ((code = object_detector(token, is_text)) != NOT)
		return code;

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int LEXICAL_M::keyword_detector(str* token) {
	if (*token == "loop")
		return LOOP;
	else if (*token == "if")
		return IF;
	else if (*token == "elf")
		return ELF;
	else if (*token == "else")
		return ELSE;
	else if (*token == "to")
		return TO;
	else if (*token == "by")
		return BY;
	else if (*token == "rutin")
		return RUTIN;
	else if (*token == "ret")
		return RET;
	else if (*token == "stop")
		return STOP;
	else if (*token == "next")
		return NEXT;
	else if (*token == "input")
		return INPUT;
	else if (*token == "output")
		return OUTPUT;

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int LEXICAL_M::operator_detector(str* token) {
	if (*token == "=")
		return ASSIGNMENT_OPERATORS + ASSI_ASSI;
	else if (*token == "^=")
		return ASSIGNMENT_OPERATORS + ASSI_POWASSI;
	else if (*token == "*=")
		return ASSIGNMENT_OPERATORS + ASSI_MULASSI;
	else if (*token == "/=")
		return ASSIGNMENT_OPERATORS + ASSI_DIVASSI;
	else if (*token == "%=")
		return ASSIGNMENT_OPERATORS + ASSI_MODASSI;
	else if (*token == "-=")
		return ASSIGNMENT_OPERATORS + ASSI_SUBASSI;
	else if (*token == "+=")
		return ASSIGNMENT_OPERATORS + ASSI_ADDASSI;
	else if (*token == "#=")
		return ASSIGNMENT_OPERATORS + ASSI_ARR;

	if (*token == "(")
		return SEPRATOR_OPERATORS + SEP_L_BRAC;
	else if (*token == ")")
		return SEPRATOR_OPERATORS + SEP_R_BRAC;
	else if (*token == ".")
		return SEPRATOR_OPERATORS + SEP_DOT;
	else if (*token == ",")
		return SEPRATOR_OPERATORS + SEP_COMMA;
	else if (*token == ":")
		return SEPRATOR_OPERATORS + SEP_COLON;


	if (*token == "!")
		return LOGICAL_OPERATORS + LOG_NOT;
	else if (*token == ">")
		return LOGICAL_OPERATORS + LOG_GT;
	else if (*token == "<")
		return LOGICAL_OPERATORS + LOG_LT;
	else if (*token == "<=")
		return LOGICAL_OPERATORS + LOG_LTEQU;
	else if (*token == ">=")
		return LOGICAL_OPERATORS + LOG_GTEQU;
	else if (*token == "!=")
		return LOGICAL_OPERATORS + LOG_NOTEQU;
	else if (*token == "==")
		return LOGICAL_OPERATORS + LOG_EQU;
	else if (*token == "&")
		return LOGICAL_OPERATORS + LOG_AND;
	else if (*token == "|")
		return LOGICAL_OPERATORS + LOG_OR;


	if (*token == "^")
		return ARITHMETIC_OPERATORS + ARI_POW;
	else if (*token == "*")
		return ARITHMETIC_OPERATORS + ARI_MUL;
	else if (*token == "/")
		return ARITHMETIC_OPERATORS + ARI_DIV;
	else if (*token == "%")
		return ARITHMETIC_OPERATORS + ARI_MOD;
	else if (*token == "-")
		return ARITHMETIC_OPERATORS + ARI_SUB;
	else if (*token == "+")
		return ARITHMETIC_OPERATORS + ARI_ADD;


	if (*token == "[")
		return OTHER_OPERATORS + OTH_L_REF;
	else if (*token == "]")
		return OTHER_OPERATORS + OTH_R_REF;
	else
		if (*token == "?")
			return OTHER_OPERATORS + OTH_TYPE;

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int LEXICAL_M::object_detector(str* token, bool is_text) {

	// IF TOKEN HAVE " | ' OP BEFORE AND AFTER IT HAS STRING TYPE
	if (is_text)
		return set_object(token, (LITERALS + STR));

	// IF TOKEN HAS TRUE | FALSE , SO ITS BOOLEAN TYPE
	if (*token == "true" || *token == "false")
		return set_object(token, (LITERALS + BOOL));

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
		return set_object(token, (LITERALS + NUM));

	// IF TOKEN ISN'T START WITH NUMBER , ITS IDENTIFIER
	if (!((*token)[0] > 47 && (*token)[0] < 58))
	{
		//	SET FUNCTION VARIABLE LIKE FUNC_NAME@VAR_NAME 
		if (func_name != "" && func_name != *token) {
			*token = func_name + "@" + *token;
		}
		else if (func_name != "" && func_name == *token)
			return set_object(token, (IDENTIFIER + FUNC));
		return set_object(token, (IDENTIFIER + NOT));
	}

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int LEXICAL_M::set_object(str* token, int type, bool is_temp) {

	// FIND HASH ID OF STRING FOR SET ID
	int code_id = object_encoder_id(*token);

	// CHECK IF HAS BEEN OBJECT_T CREATE JUST RETURN CODE ID
	if (__objects_table.is_exist(code_id) != nullptr)
		return type + __objects_table.get_type(code_id) + code_id;

	// CREATE NEW ADDRESS
	void* value = utl_generate_address();
	int var_type = NOT;

	// FOR TYPE OF DATA SET VALUE TO ADDRESS
	if ((type & DELIMITER_MIDCODE_RIGHT) == NUM) {
		(*(float*)value) = atof(&(*token)[0]);
		var_type = NUM;
	}
	else if ((type & DELIMITER_MIDCODE_RIGHT) == BOOL) {
		(*(bool*)value) = *token == "true" ? true : false;
		var_type = BOOL;
	}
	else if ((type & DELIMITER_MIDCODE_RIGHT) == STR) {
		*(char**)value = utl_set_string(*token);
		var_type = STR;
	}

	// CREATE OBJECT_T 
	__objects_table.push(code_id, var_type, value, is_temp);

	return type + code_id;
}

// PUBLIC : LEXICAL MACHIN MEMBER FUNCTION
TOKEN_L* LEXICAL_M::run(str* cmd) {
	_cmd_string = cmd;
	tokenization();
	return &_tokens;
}

void  LEXICAL_M::refresh() {
	_tokens.purify();
}