#pragma once
#include"utility.h"
#include "lexical.h"

#define NOJUMP		0x0
#define J_WHILE		0x1
#define J_FOR		0x2
//#define J_IF		0x3
//#define J_ELSE		0x4
#define J_RUTIN		0x3
#define J_RET		0x4

void interp_parse_tree();
int interp_parse_exp(EXPRESSION* root, str level);
int interp_parse_op(int op, int code_1, int code_2, str level, bool is_one_op = false);

bool condition_flow_control();
void interp_set_loop_condition(bool is_while, EXPRESSION* condition);

extern stackint _loop_stk, _func_stk;
extern int _jump_mod;

extern EXPRESSION* _condition_exp;