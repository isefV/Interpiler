#include"state_control_machine.h"

void SCM::set_level(int level_number) {
	if (_current_level == _last_level)
		return;
	else if (!(_current_level - _last_level == 1
		|| _current_level - _last_level == -1)) {
		__errors_handler.set_token("");
		__errors_handler.rise_err(ERR_INDENT);
	}

	_last_level = _current_level;
	_current_level = level_number;

	if (_current_level - _last_level == -1) {
		__state_control_machine.block_end();
	}
}

void SCM::loop_jump_control_exp() {
	int loop_line = __bytecode_handler.get_write_line();
	_loop_label_id.push(__jump_table.push(loop_line));
	_block_component.push(LOOP);
}

void SCM::loop_jump_control(int result_exp) {
	_condition_out_label_id.push(__jump_table.push(NO_JUMP));

	__bytecode_handler.write_bytecode_handler(INS_JIF);
	__bytecode_handler.write_bytecode_handler(_condition_out_label_id.top());
	__bytecode_handler.write_bytecode_handler(result_exp);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
}

void SCM::if_jump_control(int result_exp) {
	int if_line = __bytecode_handler.get_write_line();
	_condition_out_label_id.push(__jump_table.push(NO_JUMP));
	int if_line_id = __jump_table.push(NO_JUMP);
	__bytecode_handler.write_bytecode_handler(INS_JIF);
	__bytecode_handler.write_bytecode_handler(if_line_id);
	__bytecode_handler.write_bytecode_handler(result_exp);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
	_block_component.push(IF);
	_last_condition_label_id = if_line_id;
}

void SCM::elf_jump_control(int result_exp) {
	int elf_line = __bytecode_handler.get_write_line();
	__jump_table.set_line_pos(_last_condition_label_id, elf_line);
	int elf_line_id = __jump_table.push(NO_JUMP);
	__bytecode_handler.write_bytecode_handler(INS_JIF);
	__bytecode_handler.write_bytecode_handler(elf_line_id);
	__bytecode_handler.write_bytecode_handler(result_exp);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
	_block_component.push(ELF);
	_last_condition_label_id = elf_line_id;
}

void SCM::else_jump_control(int result_exp) {
	int else_line = __bytecode_handler.get_write_line();
	__jump_table.set_line_pos(_last_condition_label_id, else_line);
	int else_line_id = __jump_table.push(NO_JUMP);
	__bytecode_handler.write_bytecode_handler(INS_JIF);
	__bytecode_handler.write_bytecode_handler(else_line_id);
	__bytecode_handler.write_bytecode_handler(result_exp);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
	_block_component.push(ELSE);
	_last_condition_label_id = else_line_id;
}

void SCM::next_jump_control() {
	__bytecode_handler.write_bytecode_handler(INS_JUMP);
	__bytecode_handler.write_bytecode_handler(_loop_label_id.top());
	__bytecode_handler.write_bytecode_handler(INS_TMT);
}

void SCM::stop_jump_control() {
	__bytecode_handler.write_bytecode_handler(INS_JUMP);
	__bytecode_handler.write_bytecode_handler(_condition_out_label_id.top());
	__bytecode_handler.write_bytecode_handler(INS_TMT);
}

void SCM::block_end() {
	int block_comp = _block_component.top();

	if (block_comp == IF || block_comp == ELF) {
		__bytecode_handler.write_bytecode_handler(INS_JUMP);
		__bytecode_handler.write_bytecode_handler(_condition_out_label_id.top());
		__bytecode_handler.write_bytecode_handler(INS_TMT);
		int out_label_line = __bytecode_handler.get_write_line();
		__jump_table.set_line_pos(_condition_out_label_id.top(), out_label_line);
	}
	else if (block_comp == ELSE) {
		int out_label_line = __bytecode_handler.get_write_line();
		__jump_table.set_line_pos(_condition_out_label_id.top(), out_label_line);
	}
	else if (block_comp == LOOP) {
		__bytecode_handler.write_bytecode_handler(INS_JUMP);
		__bytecode_handler.write_bytecode_handler(_loop_label_id.top());
		__bytecode_handler.write_bytecode_handler(INS_TMT);
		int out_label_line = __bytecode_handler.get_write_line();
		__jump_table.set_line_pos(_condition_out_label_id.top(), out_label_line);
	}

	_condition_out_label_id.pop();
	_block_component.pop();
}

void SCM::ret_jump_control() {
	int ret_line = __func_table.ret(_func_id.top());
	__bytecode_handler.write_bytecode_handler(INS_JUMP);
	__bytecode_handler.write_bytecode_handler(ret_line);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
	_func_id.pop();
}

void SCM::rutin_jump_control(int func_id) {
	int rutin_line = __bytecode_handler.get_write_line();
	__func_table.push(func_id, rutin_line);
	__bytecode_handler.write_bytecode_handler(INS_INVOKE);
	__bytecode_handler.write_bytecode_handler(func_id);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
}

void SCM::rutin_args_control( int args_count) {
	__func_table.set_args_count(_func_id.top(), args_count);
}