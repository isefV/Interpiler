#include"input_control_machin.h"

STRING INCM::read_line_file() {
	FSTREAM file;
	STRING temp = "";
	file.open(_file_name, std::fstream::in);
	file.seekg(_line_pos);
	if (file.is_open()) {
		std::getline(file, temp);
		_line_pos = file.tellg();
	}
	file.close();

	return temp;
}

STRING INCM::read_line() {
	STRING temp = "";
	std::getline(GET, temp);
	return temp;
}

void INCM::set_filename(STRING file_name) {
	_file_name = file_name;
}