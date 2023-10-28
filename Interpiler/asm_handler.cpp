#include"asm_handler.h"

bool asm_create_files() {
	FS asm_data, asm_code;

	asm_data.open(ASM_DATA, FS::out);
	if (!asm_data.is_open())
		return false;
	asm_data << "section\t.data\n";

	asm_code.open(ASM_CODE, FS::out);
	if (!asm_code.is_open())
		return false;
	asm_code << "section\t.text\nglobal\t_start\n_start:\n";

	asm_data.close();
	asm_code.close();
	return true;
}

bool asm_write_data(str string) {
	FS asm_data;

	asm_data.open(ASM_DATA, FS::out | FS::app);
	if (!asm_data.is_open())
		return false;
	asm_data << string << '\n';

	asm_data.close();

	return true;
}

bool asm_write_code(str string) {
	FS asm_code;

	asm_code.open(ASM_CODE, FS::out | FS::app);
	if (!asm_code.is_open())
		return false;
	asm_code << string << '\n';

	asm_code.close();

	return true;
}