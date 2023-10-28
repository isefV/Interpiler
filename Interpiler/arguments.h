#pragma once
#include"utility.h"

// ARGUMENTS TABLE OBJECT
class ARGUMENT_T {
	int _id, _index;
	ARGUMENT_T* _next;

public:
	ARGUMENT_T() {
		_id = 0;
		_index = -1;
		_next = nullptr;
	}

	int push(int arg_id);
	int get_id(int arg_index);
	ARGUMENT_T* is_exist(int arg_index);
	void purify();
};

extern ARGUMENT_T __args_table;