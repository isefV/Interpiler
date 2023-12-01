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
	if (debug_mode) {
		for (auto iter = _decomposed_command.begin(); iter != _decomposed_command.end(); iter++) {
			PRINT << *iter << "  ";
		}
	}

}

void LEXICAL_M::tokenization() {

	purification();

	// CODEED TOKEN COMPONENT
	for (int index = 0; index < _decomposed_command.size(); index++) {

		TOKEN* token_code = new TOKEN;
		STRING temp = _decomposed_command.at(index);
		if (!token_detector(&temp, token_code))
			PRINT << "ERROR";
			//errors

		token_code->set_token_id(index);
		_tokens.push_back(token_code);
		//if(code == COMPONENTS_NON)
			//__errors_handler.rise_err(ERR_TYPE);

	}

	// @Debug : test line
	if (debug_mode) {
		PRINT << "\nTokens:\n";
		for (auto item = _tokens.begin(); item != _tokens.end(); item++)
			PRINT << '\t' << std::hex << (*item)->get_token() << '\n';
		PRINT << '\n';

		PRINT << "\Objects:\n";
		for (auto item = __objects_table.begin(); item != __objects_table.end(); item++)
			PRINT << '\t' << std::hex << item->first << '\t' << item->second->_value << '\t' << item->second->_is_temp << '\n';
		PRINT << '\n';

		PRINT << std::dec << "\nToken size : " << _tokens.size()
			<< "\t\tObject size : " << __objects_table.size() << '\n';
	}

}

bool LEXICAL_M::token_detector(STRING* token, TOKEN* token_code) {
	int code;
	// IF TOKEN IS KEYWORD_ RETURN 0xZZZ00000 KEYWORD_ CODE
	if ((code = keyword_detector(token, token_code)) != TYPE_NONT) {
		if (code == KYW_TRUE || code == KYW_FALSE) {
			token_code->set_token_type(COMPONENTS_LITERALS);
			token_code->set_token_section(TYPE_BOOL);
			set_object(token, (COMPONENTS_LITERALS + TYPE_BOOL), token_code);
			return true;
		}

		token_code->set_token_type(COMPONENTS_KEYWORDS);
		return true;
	}
	// IF TOKEN IS OPERATORS RETURN 0xZZZ00000 OPERATOR CODE
	else if (operator_detector(token, token_code)) {
		token_code->set_token_type(COMPONENTS_OPERATORS);
		return true;
	}
	// IF TOKEN IS OBJECT_T RETURN 0x4ZZAAAAA IDENTIFIER CODE | 0x3ZZAAAAA LITERALS CODE
	else if (object_detector(token, token_code))
		return true;

	// ELSE ITS WRONG SYNTAX
	return false;
}

int LEXICAL_M::keyword_detector(STRING* token, TOKEN* token_code) {
	if (*token == "loop") {
		token_code->set_token_section(KYW_LOOP);
		return KYW_LOOP;
	}
	else if (*token == "if") {
		token_code->set_token_section(KYW_IF);
		return KYW_IF;
	}
	else if (*token == "elf") {

		token_code->set_token_section(KYW_ELF);
		return KYW_ELF;
	}
	else if (*token == "else") {

		token_code->set_token_section(KYW_ELSE);
		return KYW_ELSE;
	}
	else if (*token == "to") {
		token_code->set_token_section(KYW_TO);
		return KYW_TO;
	}
	else if (*token == "by") {
		token_code->set_token_section(KYW_BY);
		return KYW_BY;
	}
	else if (*token == "rutin"){
		token_code->set_token_section(KYW_RUTIN);
		return KYW_RUTIN;
	}
	else if (*token == "ret"){
		token_code->set_token_section(KYW_RET);
		return KYW_RET;
	}
	else if (*token == "stop"){
		token_code->set_token_section(KYW_STOP);
		return KYW_STOP;
	}
	else if (*token == "next"){
		token_code->set_token_section(KYW_NEXT);
		return KYW_NEXT;
	}
	else if (*token == "input"){
		token_code->set_token_section(KYW_INPUT);
		return KYW_INPUT;
	}
	else if (*token == "output"){
		token_code->set_token_section(KYW_OUTPUT);
		return KYW_OUTPUT;
	}
	else if (*token == "true") {
		token_code->set_token_section(KYW_TRUE);
		return KYW_TRUE;
	}
	else if (*token == "false"){
		token_code->set_token_section(KYW_FALSE);
		return KYW_FALSE;
	}

	// ELSE ITS WRONG SYNTAX
	return TYPE_NONT;
}

bool LEXICAL_M::operator_detector(STRING* token, TOKEN* token_code) {
	if (*token == "=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_ASSIGNMENT);
		return true;
	}
	else if (*token == "^=")
	{
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_POWASSI);
		return true;
	}
	else if (*token == "*=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_MULASSI);
		return true;;
	}
	else if (*token == "/=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_DIVASSI);
		return true;
	}
	else if (*token == "%=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_MODASSI);
		return true;
	}
	else if (*token == "-=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_SUBASSI);
		return true;
	}
	else if (*token == "+=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_ADDASSI);
		return true;
	}
	else if (*token == "#=") {
		token_code->set_token_section(OP_ASSIGNMENT + OP_ASN_ARRASSI);
		return true;
	}

	if (*token == "(") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_LEFT_PARENTHESE);
		return true;
	}
	else if (*token == ")") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_RIGHT_PARENTHESE);
		return true;
	}
	else if (*token == "[") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_LEFT_BRACKET);
		return true;
	}
	else if (*token == "]") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_RIGHT_BREACKET);
		return true;
	}
	else if (*token == ".") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_DOT);
		return true;
	}
	else if (*token == ",") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_COMMA);
		return true;
	}
	else if (*token == ":") {
		token_code->set_token_section(OP_SEPRATOR + OP_SEP_COLON);
		return true;
	}



	if (*token == "!") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_OPPOSITE);
		return true;
	}
	else if (*token == ">") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_GREATER_THAN);
		return true;
	}
	else if (*token == "<") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_LESS_THAN);
		return true;
	}
	else if (*token == "<=") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_LESS_EQUAL);
		return true;
	}
	else if (*token == ">=") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_GREATER_EQUAL);
		return true;
	}
	else if (*token == "!=") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_NOT_EQUAL);
		return true;
	}
	else if (*token == "==") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_EQUAL);
		return true;
	}
	else if (*token == "&") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_AND);
		return true;
	}
	else if (*token == "|") {
		token_code->set_token_section(OP_LOGICAL + OP_LOG_OR);
		return true;
	}


	if (*token == "^"){
		token_code->set_token_section(OP_ARITHMETIC + OP_ARI_POW);
		return true;
	}
	else if (*token == "*") {
		token_code->set_token_section(OP_ARITHMETIC + OP_ARI_MUL);
		return true;
	}
	else if (*token == "/") {
		token_code->set_token_section(OP_ARITHMETIC + OP_ARI_DIV);
		return true;
	}
	else if (*token == "%") {
		token_code->set_token_section(OP_ARITHMETIC + OP_ARI_MOD);
		return true;
	}
	else if (*token == "-") {
		token_code->set_token_section(OP_ARITHMETIC + OP_ARI_SUB);
		return true;
	}
	else if (*token == "+") {
		token_code->set_token_section(OP_ARITHMETIC + OP_ARI_ADD);
		return true;
	}

	if (*token == "?") {
		token_code->set_token_section(OP_OTHER + OP_OTR_TYPE);
		return true;
	}

	// ELSE ITS WRONG SYNTAX
	return false;
}

bool LEXICAL_M::object_detector(STRING* token, TOKEN* token_code) {

	// IF TOKEN HAVE " | ' OP BEFORE AND AFTER IT HAS STRING TYPE
	if (token->at(0) == token->at(token->length() - 1) && token->at(0) == '\'') {
		token_code->set_token_type(COMPONENTS_IDENTIFIER);
		token_code->set_token_section(TYPE_STR);
		set_object(token, (COMPONENTS_LITERALS + TYPE_STR), token_code);
		return true;
	}

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
	if (is_digit) {
		token_code->set_token_type(COMPONENTS_LITERALS);
		token_code->set_token_section(TYPE_NUM);
		set_object(token, (COMPONENTS_LITERALS + TYPE_NUM), token_code);
		return true;
	}

	// IF TOKEN ISN'T START WITH NUMBER , ITS IDENTIFIER
	if (!((*token)[0] > 47 && (*token)[0] < 58)) {
		token_code->set_token_type(COMPONENTS_IDENTIFIER);
		token_code->set_token_section(TYPE_NONT);
		set_object(token, (COMPONENTS_IDENTIFIER + TYPE_NONT), token_code);
		return true;
	}

	// ELSE ITS WRONG SYNTAX
	return false;
}

bool LEXICAL_M::set_object(STRING* token, int type, TOKEN* token_code) {

	// FIND HASH ID OF STRING FOR SET ID
	int code_id = object_encoder_id(*token);
	token_code->set_token_address(code_id);

	// CHECK IF HAS BEEN OBJECT_T CREATE JUST RETURN CODE ID
	if (__objects_table.find(code_id) != __objects_table.end())
		return false;

	// CREATE NEW ADDRESS
	void* value = utl_generate_address();
	int var_type = TYPE_NONT;

	// FOR TYPE OF DATA SET VALUE TO ADDRESS
	if ((type & DEL_LOWER_MIDDLE_CODE) == TYPE_NUM) {
		(*(float*)value) = atof(&(*token)[0]);
		var_type = TYPE_NUM;
	}
	else if ((type & DEL_LOWER_MIDDLE_CODE) == TYPE_BOOL) {
		(*(bool*)value) = *token == "true" ? true : false;
		var_type = TYPE_BOOL;
	}
	else if ((type & DEL_LOWER_MIDDLE_CODE) == TYPE_STR) {
		*(char**)value = utl_set_string(*token);
		var_type = TYPE_STR;
	}

	// CREATE OBJECT_T 
	OBJECT* temp = new OBJECT;
	temp->_type = var_type;
	temp->_value = value;
	temp->_is_temp = true;

	__objects_table[code_id] = temp;

	return true;
}

// PUBLIC : LEXICAL MACHIN MEMBER FUNCTION
VEC<TOKEN*>* LEXICAL_M::run(STRING* cmd) {
	_command = cmd;
	tokenization();
	_decomposed_command.clear();
	return &_tokens;
}