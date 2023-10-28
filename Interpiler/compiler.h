#pragma once
#include"utility.h"
#include "lexical.h"

void comp_parse_tree();
int comp_parse_exp(EXPRESSION* root, str level);
int comp_parse_op(int op, int code_1, int code_2, str level, bool is_one_op = false);
