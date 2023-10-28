#include"utility.h"
#include"expression.h"
#include"error_handling.h"

// REQUIRED FUNCTIONS IMPLEMENTATION

char* utl_set_string(str string) {

	//CREATE NEW ADDRESS FOR STRING AND COPY IT
	unit length = string.length() + 1;
	char* nstring = (char*)malloc(sizeof(char) * length);
	memcpy(nstring, &string[0], length);
	return nstring;
}

void* utl_generate_address() {
	return (void*)malloc(sizeof(void*));
}

float utl_to_num(void* var, int type) {
	if (type == NUM)
		return *(float*)var;
	else if (type == BOOL)
		return (float)*(bool*)var;

	str temp = (*(str*)var);
	unit is_invalid = 0, len = temp.length();
	char cur_ch = temp.at(0);


	for (unit itr = 1; itr < len; itr++) {
		if (cur_ch == '.')
			is_invalid++;
		if (is_invalid > 1) {
			__errors_handler.set_token(temp);
			__errors_handler.rise_err(ERR_TYPE);
		}
			
		cur_ch = temp.at(itr);
	}

	return atof(&temp[0]);
}

char* utl_to_str(void* var, int type) {
	if (type == STR)
		return *(char**)var;
	else if (type == BOOL)
		return &std::to_string(*(bool*)var)[0];
	return &std::to_string(*(float*)var)[0];
}

bool utl_to_bool(void* var, int type) {
	if (type == BOOL)
		return *(bool*)var;
	else if (type == NUM)
		return (bool)*(float*)var;
	return !(*(str*)var == "");
}

int object_encoder_id(str token) {

	// HASH FUNCTION FOR CREATE UNIQUE ID FROM STRING
	unit index = 0;
	unsigned int code = 0;
	while (token[index] != '\0') {
		code = (code * PRIME_NUM_A) ^ (token[index] * PRIME_NUM_B);
		index++;
	}
	return code % LIMIT_INDEX;
}