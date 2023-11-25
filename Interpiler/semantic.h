#pragma once
#include"utility.h"
#include"object.h"
#include"expression.h"
#include"error_handling.h"
#include"bytecode_handling.h"

class SEMANTIC_M {
	bool is_args;
	bool stack_mode = false;

	// SYNTAX SECTION
	void parse(MAP<int, int>* tokens, VEC<EXPRESSION*>* exp);
	void parse_unary();
	void parse_binary(int op_code,int left_code,int right_code);
	void parse_arr();
	void parse_funs();
	void parse_args();
	void parse_keyword();

public:
	void run(MAP<int, int>* tokens, VEC<EXPRESSION*>* exp);
};