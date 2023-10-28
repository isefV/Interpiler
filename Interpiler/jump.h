#pragma once
#include"utility.h"

// JUMP TABLE OBJECT
class JUMP_T {
	int _line_pos,_label_id;
	JUMP_T* _next;
public:
	JUMP_T() {
		_line_pos = 0;
		_label_id = 0;
		_next = nullptr;
	}
	int push(int line_pos);
	void set_line_pos(int id,int line_pos);
	JUMP_T* is_exist(int id);
};

extern JUMP_T __jump_table;