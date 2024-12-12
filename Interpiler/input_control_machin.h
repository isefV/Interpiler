#pragma once
#include"utility_info.h"

class INCM {
	STRING _file_name;
	std::streampos _line_pos;

public:
	INCM() {
		_file_name = "";
		_line_pos = 0;
	}

	void set_filename(STRING file_name);
	STRING read_line_file();
	STRING read_line();

};