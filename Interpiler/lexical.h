#pragma once
#include"utility.h"
#include"token.h"
#include"keyword.h"
#include"object.h"
#include"error_handling.h"
#include"state_control_machine.h"

class LEXICAL_M {
	str* _cmd_string;
	TOKEN_L _tokens;

	// LEXICAL SECTION
	int line_level_detector();
	void purification();
	void tokenization();
	int token_detector(str* token, bool is_text);
	int keyword_detector(str* token);
	int operator_detector(str* token);
	int object_detector(str* token, bool is_text);
	int set_object(str* token, int type, bool is_temp = true);

public:
	TOKEN_L* run(str* cmd);
	void refresh();
};