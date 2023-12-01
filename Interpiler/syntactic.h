#pragma once
#include"utility.h"
#include"token.h"
#include"object.h"
#include"expression.h"
#include"error_handling.h"

class SYNTACTIC_M {
	VEC<EXPRESSION*> _exp;
	int _keyword,_size, _paren_counter, _brac_counter;
	bool is_args;

	// SYNTAX SECTION
	void parse(VEC<TOKEN*>* token);
	int syntaxer(const int* upcode, const int* upmidcode, const int* lowmidcode);
	int parse_priority(const int* upcode, const int* upmidcode);
	int parse_mode(const int* upcode, const int* upmidcode);
public:
	VEC<EXPRESSION*>* run(VEC<TOKEN*>* tokens);
};



							