#include"program.h"


str program_read_line() {
	// read / get new line
	return "";
}

void program_forward() {
	while (true) {
		str cmd = program_read_line();
		_program += cmd;
		_code_line = cmd;
		_current_line++;

		lex_detect_level_line(&cmd);
		if ((_last_level - _current_level == 0) 
			|| (_condition_state.top() && _current_level - _last_level == 1) 
			|| (_current_level - _last_level < 0)){

			if (_condition_state.top() && (_current_level - _last_level < 0))
				_condition_state.pop();

			_last_level = _current_level;
			return;
		}
		continue;
	}
}

str program_goto(int line) {
	int line_count = 0, index = 0, len = _program.length();
	str cmd = "";
	while (index < len) {

		if (line_count == line)
			cmd += _program[index];
		else if (line_count > line) {
			_current_line = line;
			return cmd;
		}
		if (_program[index] == '\n')
			line_count++;
		index++;
	}
}