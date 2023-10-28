#pragma once
#include"utility.h"
#include"object.h"

// FUNCTION TABLE OBJECT
class FUNCTION_T {
	int _id, _args_count , _invoke_line;
	stackint _call_line;
	FUNCTION_T* _next;

public:
	FUNCTION_T() {
		_id = 0;
		_args_count = 0;
		_invoke_line = -1;
		_next = nullptr;
	}

	int push(int func_id, int invoke_line);
	void set_args_count(int func_id,int args_count);
	FUNCTION_T* is_exist(int func_id);
	void call(int func_id, int line_number);
	int ret(int func_id);
};

extern FUNCTION_T __func_table;