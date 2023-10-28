#pragma once
#include"utility.h"
#include"bytecode_handling.h"
#include"object.h"
#include"jump.h"
#include"array.h"
#include"arguments.h"
#include"function.h"
#include"error_handling.h"

// STATE CONTROL MACHINE OBJECT
class SCM {
	int _current_level, _last_level,
		_current_line, _last_condition_label_id;
	stackint _block_component, _condition_out_label_id,
		_loop_label_id, _func_id;

public:
	SCM() {
		_current_level = 0;
		_last_level = 0;
		_current_line = 0;
		_last_condition_label_id = 0;
	}
	void set_level(int level_number);
	void if_jump_control(int result_exp);
	void elf_jump_control(int result_exp);
	void else_jump_control(int result_exp);
	void loop_jump_control_exp();
	void loop_jump_control(int result_exp);
	void rutin_jump_control(int result_exp);
	void rutin_args_control( int args_count);
	void ret_jump_control();
	void next_jump_control();
	void stop_jump_control();
	void block_end();
};

extern SCM __state_control_machine;