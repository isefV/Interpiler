#pragma once
#include"utility.h"
#include<fstream>
#include"state_control_machine.h"

// BYTECODE HANDLER OBJECT
class BYTECODE_H {
	str _file_name;
	int _write_line, _read_line;

public:
	BYTECODE_H() {
		_write_line = 0x10001;
		_read_line = 0x10000;
		_file_name = "bytecode.bin";

		fs file_out(_file_name, ios::out | ios::trunc | ios::binary);
		file_out << _write_line << " ";
		_write_line++;
		file_out.close();
	}

	void write_bytecode_handler(int coded);
	void display_bytecode_handler();
	int get_write_line();
};

extern BYTECODE_H __bytecode_handler;