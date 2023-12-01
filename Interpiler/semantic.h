#pragma once
#include"utility.h"
#include"token.h"
#include"object.h"
#include"expression.h"
#include"error_handling.h"
#include"bytecode_handling.h"

class SEMANTIC_M {
	bool is_args;
	bool stack_mode = false;
	bool loop_mode = false;
	int iter_code = 0;


	// SYNTAX SECTION
	void parse(VEC<TOKEN*>* tokens, VEC<EXPRESSION*>* exp);
	void parse_unary(int op_code, int right_code);
	void parse_binary(int op_code,int left_code,int right_code);
	void parse_arr(int arr_code, int index_code);
	void parse_keyword(int kyw_code);
	//void parse_funcs();
	//void parse_args();

public:
	void run(VEC<TOKEN*>* tokens, VEC<EXPRESSION*>* exp);
};