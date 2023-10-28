#pragma once
#include"utility.h"

// KEYWORD OBJECT
class KEYWORD_ {
	int _keyword_code;

public:
	KEYWORD_() {
		_keyword_code = 0;
	}
	void reset();
	void set(int code);

	bool is_no_keyword();
	bool is_loop();
	bool is_if_elf();
	bool is_if();
	bool is_elf();
	bool is_else();
	bool is_rutin();
	bool is_ret();
	bool is_stop();
	bool is_next();
	bool is_input();
	bool is_output();
};

extern KEYWORD_ _keyword;