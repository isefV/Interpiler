#pragma once
#include"utility.h"
#include"object_table.h"
#include"expression.h"
#include"error_handling.h"

#define PRIO_NO -1
#define PRIO_LEAST 0
#define PRIO_1 1
#define PRIO_2 2
#define PRIO_3 3
#define PRIO_4 4
#define PRIO_5 5
#define PRIO_6 6
#define PRIO_7 7
#define PRIO_8 8
#define PRIO_9 9
#define PRIO_10 10
#define PRIO_11 11
#define PRIO_12 12
#define PRIO_13 13
#define PRIO_14 14
#define PRIO_15 15
#define PRIO_MOST 16

#define MODE_OFF 0
#define MODE_UNARY 1
#define MODE_BINARY 2
#define MODE_ARR 3
#define MODE_FUNC 4
#define MODE_ARGS 5
#define MODE_KEYWORD 6

#define ACCEPT_ACTION 1
#define ACCEPT_NO_ACTION 0
#define REFUSE -1

class SYNTACTIC_M {
	VEC<EXPRESSION*> _exp;
	int _keyword,_paren_counter,_brac_counter;
	bool is_args;

	// SYNTAX SECTION
	void parse(VEC<int>* token);
	int syntaxer(int code, int index, int token_size);
	int parse_priority(int code);
	int parse_mode(int code);

public:
	VEC<EXPRESSION*>* run(VEC<int>* tokens);

};