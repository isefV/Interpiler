#include "lexical.h"

bool is_func = false, _ref = false;
str func_name = "";

int lex_detect_level_line(str* cmd) {
	unit level = 0, index = 0, len = cmd->length();
	char current_ch = cmd->at(0), next_ch = 0;
	// SPECIFIC INDENTATION / LEVEL
	while (current_ch == 32 || current_ch == 9) {
		level += current_ch == 9 ? 4 : 1;
		current_ch = cmd->at(index);
		index++;
	}

	_current_level = level % 3;
	return index;
}

void lex_purification(str* cmd) {
	unit index = 0, len = cmd->length();
	bool isnt_punc = false, is_text = false;
	char current_ch = '\0', next_ch = 0;
	str cmd_tp = "";

	index = lex_detect_level_line(cmd);
	current_ch = cmd->at(index);
	index++;

	// PURGING USELESS SPACES
	while (index <= len) {

		// IF SEEN ; DON'T READ COMMENTS
		if (current_ch == 59)
			break;

		//// IF SEEN # SAVE VAR_NAME TO INDEXES
		//if (current_ch == 35) {
		//	cmd_tp += "#";
		//}

		// IF A-Z | a-z | 0-9 | _
		if ((is_text && current_ch != 39 && current_ch != 34) || (current_ch > 64 && current_ch < 91)
			|| (current_ch > 96 && current_ch < 123)
			|| (current_ch > 47 && current_ch < 58)
			|| current_ch == 46 || current_ch == 95) {

			// LOWERCASE LANG
			if(is_text)
				cmd_tp += current_ch;
			else
				cmd_tp += tolower(current_ch);

			// SET ISN'T PUNCTUATION FLAG TRUE FOR DELIMITER 
			isnt_punc = true;
		}

		// IF !"%&'()*+,-./ :<=>? []^ |#
		else if ((current_ch > 32 && current_ch < 48 && current_ch != 36 )
			|| ((current_ch > 57 && current_ch < 64))
			|| current_ch == 91 || current_ch == 93 || current_ch == 94
			|| current_ch == 124) {

			////	IF SEEN [ ADD @ | ] ADD ; TO VAR LIKE : VAR#INDEX;
			//if (isnt_punc && (current_ch == 91 || current_ch == 93)) {
			//	cmd_tp += current_ch == 91 ? "#;" : "";
			//	current_ch = cmd->at(index);
			//	index++;
			//	continue;
			//}

			//	IF DELIMITER FLAG TRUE THAT MEANS TOKEN READY TO DELIMITER THEN SET FLAG TO FALSE
			if (isnt_punc)
				cmd_tp += ";";
			isnt_punc = false;

			//	IF CHAR IS ' | " SET TRUE IS TEXT FLAG
			if (current_ch == 34 || current_ch == 39)
				is_text = !is_text;

			//	CHECK NEXT CHAR TO CREATE TOKEN ONE OP | TWO OP
			next_ch = index < len ? cmd->at(index) : '\0';

			// IF !*+-/<=>^#
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

		current_ch = index < len ? cmd->at(index) : '\0';
		index++;
	}

	if (isnt_punc)
		cmd_tp += ";";

	// @Debug : test line
	print << cmd_tp << '\n';

	// CREATE A NEW ADDRESS FOR REFINED CODE
	*cmd = cmd_tp;
}

void lex_tokenization(str* cmd) {

	lex_purification(cmd);

	int index = 1, len = cmd->length();
	char current_ch = cmd->at(0), last_ch = '\0', text_ch = '\0';
	str token = "";

	while (index <= len) {

		// IF CHAR IS DELIMITER CREATE TOKEN CODE 
		if (current_ch == ';' && token != "") {
			//	0x00000000
			int code = 0;
			bool is_text = false;
			// CHECK TOKEN HAVE " | ' OP BEFORE AND AFTER IT
			if (text_ch != '\0')
				is_text = cmd->at(index) == text_ch;

			//	IF FUNCTION MODE TRUE THAT SAVE FUNCTION NAME	
			if (is_func) {
				func_name = token;
				is_func = false;
			}

			//	GET TOKEN CODE BASE ON COMMAND
			code = lex_token_code_detector(token, is_text);

			// CHECK FUNCTION COMMAND FOR LABEL VARIABLE FUNCTION
			if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + RUTIN)
				is_func = true;

			//	XTRCT KEYWORD TELL THAT FUNCTION END AND VARIABLE BE GLOBAL
			if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + RET)
				func_name = "";

			//	IF CODE ZERO RISE ERROR FOR SYNTAX
			if (code == NOT)
				rise_err(ERR_LEXICAL, _current_line, token);

			_tokens.push(code);
			text_ch = '\0';
			token = "";
			_ref = false;
		}
		else if (current_ch != ';') {
			// SET TEXT_CH TO CHECK STRING STARTED OR NOT
			if (text_ch == '\0' && (current_ch == 34 || current_ch == 39))
				text_ch = current_ch;
			else {
				token += current_ch;

				// IF # THAT SHOW ARR TYPE
				if (current_ch == 35)
					_ref = true;

			}
		}

		last_ch = current_ch;
		current_ch = index < len ? cmd->at(index) : '\0';
		index++;
	}


	// @Debug : test line
	_tokens.display();
	print << "\n";
	_objects.display();
	print << std::dec << "\nToken size : " << _tokens_size
		<< "\t\tObject size : " << _objects_size << '\n';

}

int lex_token_code_detector(str token, bool is_text) {
	int code = NOT;

	// IF TOKEN IS KEYWORD RETURN 0xZZZ00000 KEYWORD CODE
	if ((code = lex_keyword_detector(token)) != NOT)
		return KEYWORDS + code;

	// IF TOKEN IS OPERATORS RETURN 0xZZZ00000 OPERATOR CODE
	else if ((code = lex_operator_detector(token)) != NOT)
		return OPERATORS + code;

	// IF TOKEN IS OBJECT RETURN 0x4ZZAAAAA IDENTIFIER CODE | 0x3ZZAAAAA LITERALS CODE
	else if ((code = lex_object_detector(token, is_text)) != NOT)
		return code;

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int lex_keyword_detector(str token) {
	if (token == "loop")
		return LOOP;
	else if (token == "if")
		return IF;
	else if (token == "elf")
		return ELF;
	else if (token == "else")
		return ELSE;
	else if (token == "to")
		return TO;
	else if (token == "by")
		return BY;
	else if (token == "rutin")
		return RUTIN;
	else if (token == "ret")
		return RET;
	else if (token == "stop")
		return STOP;
	else if (token == "next")
		return NEXT;
	else if (token == "input")
		return INPUT;
	else if (token == "output")
		return OUTPUT;

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int lex_operator_detector(str token) {
	if (token == "=")
		return ASSIGNMENT_OPERATORS + ASSI_ASSI;
	else if (token == "^=")
		return ASSIGNMENT_OPERATORS + ASSI_POWASSI;
	else if (token == "*=")
		return ASSIGNMENT_OPERATORS + ASSI_MULASSI;
	else if (token == "/=")
		return ASSIGNMENT_OPERATORS + ASSI_DIVASSI;
	else if (token == "%=")
		return ASSIGNMENT_OPERATORS + ASSI_MODASSI;
	else if (token == "-=")
		return ASSIGNMENT_OPERATORS + ASSI_SUBASSI;
	else if (token == "+=")
		return ASSIGNMENT_OPERATORS + ASSI_ADDASSI;
	else if (token == "#=")
		return ASSIGNMENT_OPERATORS + ASSI_ARR;

	if (token == "(")
		return SEPRATOR_OPERATORS + SEP_L_BRAC;
	else if (token == ")")
		return SEPRATOR_OPERATORS + SEP_R_BRAC;
	else if (token == ".")
		return SEPRATOR_OPERATORS + SEP_DOT;
	else if (token == ",")
		return SEPRATOR_OPERATORS + SEP_COMMA;
	else if (token == ":")
		return SEPRATOR_OPERATORS + SEP_COLON;


	if (token == "!")
		return LOGICAL_OPERATORS + LOG_NOT;
	else if (token == ">")
		return LOGICAL_OPERATORS + LOG_GT;
	else if (token == "<")
		return LOGICAL_OPERATORS + LOG_LT;
	else if (token == "<=")
		return LOGICAL_OPERATORS + LOG_LTEQU;
	else if (token == ">=")
		return LOGICAL_OPERATORS + LOG_GTEQU;
	else if (token == "!=")
		return LOGICAL_OPERATORS + LOG_NOTEQU;
	else if (token == "==")
		return LOGICAL_OPERATORS + LOG_EQU;
	else if (token == "&")
		return LOGICAL_OPERATORS + LOG_AND;
	else if (token == "|")
		return LOGICAL_OPERATORS + LOG_OR;


	if (token == "^")
		return ARITHMETIC_OPERATORS + ARI_POW;
	else if (token == "*")
		return ARITHMETIC_OPERATORS + ARI_MUL;
	else if (token == "/")
		return ARITHMETIC_OPERATORS + ARI_DIV;
	else if (token == "%")
		return ARITHMETIC_OPERATORS + ARI_MOD;
	else if (token == "-")
		return ARITHMETIC_OPERATORS + ARI_SUB;
	else if (token == "+")
		return ARITHMETIC_OPERATORS + ARI_ADD;


	if (token == "[")
		return OTHER_OPERATORS + OTH_L_REF;
	else if (token == "]")
		return OTHER_OPERATORS + OTH_R_REF;
	else 
	if (token == "?")
		return OTHER_OPERATORS + OTH_TYPE;

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int lex_object_detector(str token, bool is_text) {

	// IF TOKEN HAVE " | ' OP BEFORE AND AFTER IT HAS STRING TYPE
	if (is_text)
		return lex_set_object(token, (LITERALS + STR));

	// IF TOKEN HAS TRU | FLS , SO ITS BOOLEAN TYPE
	if (token == "true" || token == "false")
		return lex_set_object(token, (LITERALS + BOOL));

	bool is_digit = true;
	char* current_ch = &token[0];

	while (*current_ch != '\0') {
		if (!((*current_ch > 47 && *current_ch < 58) || *current_ch == 46)) {
			is_digit = false;
			break;
		}
		current_ch++;
	}

	// IF ALL TOKEN CHAR IS DIGIT , SO ITS NUMBER TYPE
	if (is_digit)
		return lex_set_object(token, (LITERALS + NUM));

	// IF TOKEN ISN'T START WITH NUMBER , ITS IDENTIFIER
	if (!(token[0] > 47 && token[0] < 58))
	{
		//	SET FUNCTION VARIABLE LIKE FUNC_NAME@VAR_NAME 
		if (func_name != "" && func_name != token) {
			token = func_name + "@" + token;
		}
		else if (func_name != "" && func_name == token)
			return lex_set_object(token, (IDENTIFIER + FUNC));
		return lex_set_object(token, (IDENTIFIER + NOT));
	}

	// ELSE ITS WRONG SYNTAX
	return NOT;
}

int lex_id_object_encoder(str token) {

	// HASH FUNCTION FOR CREATE UNIQUE ID FROM STRING
	unit index = 0;
	unsigned int code = 0;
	while (token[index] != '\0') {
		code = (code * PRIME_NUM_A) ^ (token[index] * PRIME_NUM_B);
		index++;
	}
	return code % LIMIT_INDEX;

	//const char* allowed_ch = "!\"#$%&'()*+,./56789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ]^_`abcdefghijklmnopqrstuvwxyz{|}";
	//str token_tp = "";
	//unit dec_lvl = 0, inc_lvl = 0, token_len = token.length();;

	//// STRING WITH N LENGTH CHARACTER MAP TO 5 LENGTH CHARACTER UNIQUE
	//while (token_len != 3) {
	//	
	//	if (token_len > 3) {
	//		if(token_len%2!=0)
	//			token += '~';

	//		for (unit item = 0; item <= token_len - 1; item+=2){
	//			token_tp += allowed_ch[((int)token[item] + (int)token[item + 1]) % 84];
	//		}
	//		token = token_tp;
	//		dec_lvl++;
	//		token_len = token.length();
	//		token_tp = "";
	//		continue;
	//	}

	//	token += '~';
	//	token_len = token.length();
	//	inc_lvl++;
	//}

	//for (unit item = 0; item < 3; item ++) {
	//	token_tp += allowed_ch[(int)token[item] % 84];
	//}

	//token += allowed_ch[dec_lvl];
	//token += allowed_ch[inc_lvl];
	//token += token_tp;

	//return &token[0];

	/*	RETURN INT DYNAMIC VALUE
		unsigned int hash = 0;
		unsigned int x = 0;
		unsigned int i = 0;
		unsigned int len = token.length();

		for (i = 0; i < len; i++)
		{
			hash = (hash << 4) + (token[i]);
			if ((x = hash & 0xF0000000) != 0)
			{
				hash ^= (x >> 24);
			}
			hash &= ~x;
		}

		return hash;
	*/
}

int lex_set_object(str token, int type, bool is_temp) {

	// FIND HASH ID OF STRING FOR SET ID
	int code_id = lex_id_object_encoder(token);

	// CHECK IF HAS BEEN OBJECT CREATE JUST RETURN CODE ID
	if (_objects.is_exist(code_id) != nullptr)
		return type + _objects.get_type(code_id) + code_id;

	// CREATE NEW ADDRESS
	void* value = utl_generate_address();
	int var_type = NOT;

	// FOR TYPE OF DATA SET VALUE TO ADDRESS
	if ((type & DELIMITER_MIDCODE_RIGHT) == NUM) {
		(*(float*)value) = atof(&token[0]);
		var_type = NUM;
	}
	else if ((type & DELIMITER_MIDCODE_RIGHT) == BOOL) {
		(*(bool*)value) = token == "true" ? true : false;
		var_type = BOOL;
	}
	else if ((type & DELIMITER_MIDCODE_RIGHT) == STR) {
		*(char**)value = utl_set_string(token);
		var_type = STR;
	}

	// CREATE OBJECT 
	_objects.push(code_id, var_type, value, is_temp);


	// IF TYPE HAS ARR
	if (_ref)
		code_id += ARR;

	return type + code_id;
}
