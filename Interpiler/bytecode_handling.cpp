#include"bytecode_handling.h"

void BYTECODE_H::write_bytecode_handler(int coded) {

	FSTREAM file_out(_file_name, IOS::out | IOS::app | IOS::binary);

	if (coded == INSTRUCTION_END) {
		file_out << "\n";
		file_out << _write_line << " ";
		_write_line++;
	}
	else
		file_out << coded << " ";

	file_out.close();
}

void BYTECODE_H::display_bytecode_handler() {

	FSTREAM file_in(_file_name, IOS::in | IOS::binary);

	std::filebuf* temp;

	while (true) {
		temp = file_in.rdbuf();
		PRINT << temp << '\n';
		if (temp == nullptr)
			break;
	}

	file_in.close();
}

int BYTECODE_H::get_write_line() {
	return _write_line - 1;
}