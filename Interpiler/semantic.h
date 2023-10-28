#pragma once
#include"utility.h"
#include"token.h"
#include"keyword.h"
#include"object.h"
#include"expression.h"
#include"error_handling.h"
#include"bytecode_handling.h"
#include"state_control_machine.h"

class SEMANTIC_M {
	EXPRESSION_L* _exp;
	TOKEN_L* _tokens;

	//// SEMENTIC SECTION
	//int parse_code();
	//int parse_tree(EXPRESSION_L* root, str level);
	//int parse_loop_to_tree(EXPRESSION_L* root);
	//int parse_ret_tree(EXPRESSION_L* root, int index);
	//int parse_invoke_func_tree(EXPRESSION_L* root, bool is_root, int index);
	//int parse_call_func_tree(EXPRESSION_L* root, bool is_root, int index);
	//int parse_arr_tree(EXPRESSION_L* root, int arr_root, int index);
	//int parse_three_address(int op, int code_1, int code_2, str level, bool is_one);
	//void parser();

	void parse();
	void unray_parser(int op,int ident);
	void binray_parser(int op,int ident_1,int ident_2);
	void arr_parser(int arr,int index);
	void func_parser(int code);
	void args_parser(int code);
	void keyw_parser(int code, int ident);

	bool type_control(int code,int type_1, int type_2, bool is_unary);

public:
	void run(EXPRESSION_L* exp, TOKEN_L* token);
	/*void refresh();*/
};