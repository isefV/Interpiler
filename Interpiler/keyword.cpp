#include"keyword.h"

// KEYWORD_
bool KEYWORD_::is_loop() {
	return (_keyword_code & DELIMITER_MIDCODE) == LOOP;
}

bool KEYWORD_::is_if_elf() {
	return (_keyword_code & DELIMITER_MIDCODE) == ELF
		|| (_keyword_code & DELIMITER_MIDCODE) == IF;
}

bool KEYWORD_::is_if() {
	return (_keyword_code & DELIMITER_MIDCODE) == IF;
}

bool KEYWORD_::is_elf() {
	return (_keyword_code & DELIMITER_MIDCODE) == ELF;
}

bool KEYWORD_::is_else() {
	return (_keyword_code & DELIMITER_MIDCODE) == ELSE;
}

bool KEYWORD_::is_rutin() {
	return (_keyword_code & DELIMITER_MIDCODE) == RUTIN;
}

bool KEYWORD_::is_ret() {
	return (_keyword_code & DELIMITER_MIDCODE) == RET;
}

bool KEYWORD_::is_stop() {
	return (_keyword_code & DELIMITER_MIDCODE) == STOP;
}

bool KEYWORD_::is_next() {
	return (_keyword_code & DELIMITER_MIDCODE) == NEXT;
}

bool KEYWORD_::is_input() {
	return (_keyword_code & DELIMITER_MIDCODE) == INPUT;
}

bool KEYWORD_::is_output() {
	return (_keyword_code & DELIMITER_MIDCODE) == OUTPUT;
}

bool KEYWORD_::is_no_keyword() {
	return _keyword_code == 0;
}

void KEYWORD_::reset() {
	_keyword_code = 0;
}

void KEYWORD_::set(int code) {
	_keyword_code = code;
}