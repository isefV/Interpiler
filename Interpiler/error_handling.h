#pragma once
#include"utility_info.h"

// ERROR HANDLER OBJECT
class ERROR_H {
	int _line;
	STRING _token;
public:
	ERROR_H() {
		_line = 0;
		_token = "";
	}
	void rise_err(int err_type);
	void stop_program_err();
	void set_line(int line_number);
	void set_token(STRING token);
};

extern ERROR_H __errors_handler;