#pragma once
#include"utility.h"
#include"object.h"
#include"expression.h"
#include"error_handling.h"

class SYNTACTIC_M {
	VEC<EXPRESSION*> _exp;
	int _keyword,_paren_counter,_brac_counter;
	bool is_args;

	// SYNTAX SECTION
	void parse(MAP<int,int>* token);
	int syntaxer(int* code, int index, int token_size);
	int parse_priority(int code);
	int parse_mode(int code);

public:
	VEC<EXPRESSION*>* run(MAP<int,int>* tokens);
};



							