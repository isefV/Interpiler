#pragma once
#include"utility_info.h"

class TOKEN {
	char _code[11];
	STRING _int_to_32base(int code,int size);
	int _32base_to_int(char code32);

public:
	TOKEN() : _code{ '0','0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0','\0'} {};
	STRING get_token();
	int get_token_code(int delimiter);

	void set_token_type(int code);
	void set_token_section(int code);
	void set_token_id(int code);
	void set_token_address(int code);
};