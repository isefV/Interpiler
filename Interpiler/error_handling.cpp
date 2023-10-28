#include"error_handling.h"
#include"utility.h"

void rise_err(int err_type, int line, str token) {
	str err_msg = "";

	switch (err_type)
	{
	case ERR_TYPE:
		err_msg = "[\t- THERE IS AN #ERR_TYPE IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THIS ERROR MAY BE RELATED TO YOUR VARIABLES!\t]";
		break;
	case ERR_REFERENCE:
		err_msg = "[\t- THERE IS AN #ERR_REFERENCE IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THIS ERROR MAY BE CAUSED BY ACCESSING THE WRONG VARIABLE OR INDEX!\t]";
		break;
	case ERR_LEXICAL:
		err_msg = "[\t- THERE IS AN #ERR_LEXICAL IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THIS ERROR MAY BE RELATED TO YOUR UNDEFINED CHARACTER!\t]";
		break;
	case ERR_SYNTAX:
		err_msg = "[\t- THERE IS AN #ERR_SYNTAX IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THIS ERROR MAY BE YOUR TYPO!\t]";
		break;
	case ERR_RANGE:
		err_msg = "[\t- THERE IS AN #ERR_RANGE IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THIS ERROR MAY BE FROM WRONG RANGE OF NUMBERS!\t]";
		break;
	case ERR_CASTING:
		err_msg = "[\t- THERE IS AN #ERR_CASTING IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THE AUTO CASTING NOT ACCEPTED BY COMPILER!(YOUR DATA NOT SAME TYPE)\t]";
		break;
	case ERR_WRONGVAR:
		err_msg = "[\t- THERE IS AN #ERR_WRONGVAR IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , YOU ATTEMPT TO WORK ON 'NOT','OBJ' OR 'FUNC' TYPE LIKE OTHER TYPE.\t]";
		break;
	default:
		err_msg = "[\t- THERE IS AN #ERR_UNKOWN IN YOUR CODE AT LINE [" + std::to_string(line) + "] AND TOKEN : [" + token + "] , THIS ERROR IS VERY RARE! (!! I DON'T KNOW EITHER !!)\t]";
		break;
	}

	print << '\n' << err_msg << '\n';
	stop_program_err();
}

void stop_program_err() {
	while (true) {}
}