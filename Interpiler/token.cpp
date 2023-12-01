#include"token.h"

STRING TOKEN::_int_to_32base(int code, int size) {
	STRING enc;

	while (code > 0) {
		int rem = code % 32;

		if (rem >= 0 && rem < 10)
			enc += char(48 + rem);
		else
			enc += char(65 + (rem - 10));

		code = int(code / 32);
	}

	std::reverse(enc.begin(), enc.end());

	while (enc.length() < size)
		enc = '0' + enc;

	return enc;
}

int TOKEN::_32base_to_int(char code32) {
	int code = int(code32);
	if (code >= 48 && code <= 57)
		return code % 48;

	return (code % 65) + 10;
}

void TOKEN::set_token_type(int code) {
	_code[UPPER_CODE_PART] = _int_to_32base(code,1)[0];
}

void TOKEN::set_token_section(int code) {
	STRING temp = _int_to_32base(code,2);
	_code[UPPER_MIDDLE_CODE_PART_1] = temp[0];
	_code[UPPER_MIDDLE_CODE_PART_2] = temp[1];
}

void TOKEN::set_token_id(int code) {
	STRING temp = _int_to_32base(code,2);
	_code[LOWER_MIDDLE_CODE_PART_1] = temp[0];
	_code[LOWER_MIDDLE_CODE_PART_2] = temp[1];
}

void TOKEN::set_token_address(int code) {
	STRING temp = _int_to_32base(code,5);
	_code[LOWER_CODE_PART_1] = temp[0];
	_code[LOWER_CODE_PART_2] = temp[1];
	_code[LOWER_CODE_PART_3] = temp[2];
	_code[LOWER_CODE_PART_4] = temp[3];
	_code[LOWER_CODE_PART_5] = temp[4];
}

STRING TOKEN::get_token() {
	return std::string(_code);
}

int TOKEN::get_token_code(int delimiter) {
	if (delimiter == DEL_UPPER_CODE) {
		return _32base_to_int(_code[UPPER_CODE_PART]);
	}
	else if(delimiter == DEL_UPPER_MIDDLE_CODE){
		return (_32base_to_int(_code[UPPER_MIDDLE_CODE_PART_1]) * 32) + _32base_to_int(_code[UPPER_MIDDLE_CODE_PART_2]);
	}
	else if (delimiter == DEL_LOWER_MIDDLE_CODE) {
		return (_32base_to_int(_code[LOWER_MIDDLE_CODE_PART_1]) * 32) + _32base_to_int(_code[LOWER_MIDDLE_CODE_PART_2]);
	}

	int code = 0;
	for (int index = 0; index < LIMIT_PART; index++)
		code += _32base_to_int(_code[9 - index]) * std::pow(32,index);
	return code;

}