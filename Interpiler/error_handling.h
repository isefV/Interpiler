#pragma once
#include"utility.h"

// ERROR HANDLER OBJECT
class ERROR_H {
	int _line;
	str _token;
public:
	ERROR_H(){
		_line = 0;
		_token = "";
	}
	void rise_err(int err_type);
	void stop_program_err();
	void set_line(int line_number);
	void set_token(str token);
};

extern ERROR_H __errors_handler;