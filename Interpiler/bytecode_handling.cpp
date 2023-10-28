#include"bytecode_handling.h"

void BYTECODE_H::write_bytecode_handler(int coded) {

	fs file_out(_file_name, ios::out | ios::app | ios::binary);

	if (coded == INS_TMT) {
		file_out << "\n";
		file_out << _write_line << " ";
		_write_line++;
	}
	else
		file_out << coded << " ";

	file_out.close();
}

void BYTECODE_H::display_bytecode_handler() {

	fs file_in(_file_name, ios::in | ios::binary);

	std::filebuf* temp;

	while (true) {
		temp = file_in.rdbuf();
		print << temp <<'\n';
		if (temp == nullptr)
			break;
	}

	file_in.close();
}

int BYTECODE_H::get_write_line() {
	return _write_line - 1;
}