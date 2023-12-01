#pragma once
#include"utility_info.h"
#include"utility.h"
#include"object.h"
#include"token.h"


class LEXICAL_M {
	STRING* _command;
	VEC<STRING> _decomposed_command;
	VEC<TOKEN*> _tokens;

	// LEXICAL SECTION
	int line_level_detector();
	void purification();
	void tokenization();
	bool token_detector(STRING* token, TOKEN* token_code);
	int keyword_detector(STRING* token, TOKEN* token_code);
	bool operator_detector(STRING* token, TOKEN* token_code);
	bool object_detector(STRING* token, TOKEN* token_code);
	bool set_object(STRING* token, int type, TOKEN* token_code);

public:
	VEC<TOKEN*>* run(STRING* cmd);
};