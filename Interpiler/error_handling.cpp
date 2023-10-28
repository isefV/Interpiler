#include"error_handling.h"

void ERROR_H::rise_err(int err_type) {
	str err_msg = "";

	switch (err_type)
	{
	case ERR_TYPE:
		err_msg = "[\t- THERE IS AN #ERR_TYPE IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THIS ERROR MAY BE RELATED TO YOUR VARIABLES!\t]";
		break;
	case ERR_REFERENCE:
		err_msg = "[\t- THERE IS AN #ERR_REFERENCE IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THIS ERROR MAY BE CAUSED BY ACCESSING THE WRONG VARIABLE OR INDEX!\t]";
		break;
	case ERR_LEXICAL:
		err_msg = "[\t- THERE IS AN #ERR_LEXICAL IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THIS ERROR MAY BE RELATED TO YOUR UNDEFINED CHARACTER!\t]";
		break;
	case ERR_SYNTAX:
		err_msg = "[\t- THERE IS AN #ERR_SYNTAX IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THIS ERROR MAY BE YOUR TYPO!\t]";
		break;
	case ERR_RANGE:
		err_msg = "[\t- THERE IS AN #ERR_RANGE IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THIS ERROR MAY BE FROM WRONG RANGE OF NUMBERS!\t]";
		break;
	case ERR_CASTING:
		err_msg = "[\t- THERE IS AN #ERR_CASTING IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THE AUTO CASTING NOT ACCEPTED BY COMPILER!(YOUR DATA NOT SAME TYPE)\t]";
		break;
	case ERR_WRONGVAR:
		err_msg = "[\t- THERE IS AN #ERR_WRONGVAR IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , YOU ATTEMPT TO WORK ON 'NOT','OBJ' OR 'FUNC' TYPE LIKE OTHER TYPE.\t]";
		break;
	case ERR_INDENT:
		err_msg = "[\t- THERE IS AN #ERR_INDENT IN YOUR CODE AT LINE [" + std::to_string(_line) + "], YOUR BLOCK INDENT INVALID.\t]";
		break;
	default:
		err_msg = "[\t- THERE IS AN #ERR_UNKOWN IN YOUR CODE AT LINE [" + std::to_string(_line) + "] AND TOKEN_L : [" + _token + "] , THIS ERROR IS VERY RARE! (!! I DON'T KNOW EITHER !!)\t]";
		break;
	}

	print << '\n' << err_msg << '\n';
	stop_program_err();
}

void ERROR_H::set_line(int line_number) {
	_line = line_number;
}

void ERROR_H::set_token(str token) {
	_token = token;
}

void ERROR_H::stop_program_err() {
	while (true) {}
}