#pragma once
#include"utility_info.h"
#include"utility.h"
#include"object.h"


class LEXICAL_M {
	STRING* _command;
	VEC<STRING> _decomposed_command;
	MAP<int,int> _tokens;

	// LEXICAL SECTION
	int line_level_detector();
	void purification();
	void tokenization();
	int token_detector(STRING* token);
	int keyword_detector(STRING* token);
	int operator_detector(STRING* token);
	int object_detector(STRING* token);
	int set_object(STRING* token, int type);

public:
	MAP<int,int>* run(STRING* cmd);
};