#pragma once
#include"utility.h"
#include"error_handling.h"

// EXPRESSION TREE OBJECT
//class EXPRESSION_L {
//	EXPRESSION_L* _left, * _right;
//	int _code;
//	short unsigned int _priority;
//	bool _is_tree;
//
//public:
//	EXPRESSION_L() {
//		_left = nullptr;
//		_right = nullptr;
//		_priority = 0;
//		_code = 0;
//		_is_tree = false;
//	}
//	bool push(int code);
//	int get_code();
//	bool is_tree();
//	void purify(EXPRESSION_L* root, int level);
//	EXPRESSION_L* get_childs(bool is_right);
//	EXPRESSION_L* copy();
//};

#define inc_bp(number) number += number + PRIO_MOST
#define invalid_bp(number) if (number - PRIO_MOST < 0) __errors_handler.rise_err(ERR_SYNTAX)
#define dec_bp(number) number -= PRIO_MOST


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


class EXPRESSION_L {
	EXPRESSION_L * _next, * _last;
	int _id;
	short unsigned int _priority , _mode;

public:
	EXPRESSION_L() {
		_next = nullptr;
		_last = nullptr;
		_priority = PRIO_NO;
		_id = -1;
		_mode = MODE_OFF;
	}
	int parse_priority(int code);
	int parse_mode(int code);
	void push(int code, int id);
	void purify();
	void display();

	int get_id();
	int get_mode();
	EXPRESSION_L* go_next();
};
