#pragma once
#include"utility.h"

#define NO_ID -1

#define inc_tk(number) number += 1
#define dec_tk(number) number -= number - 1 >= 0 ? 1 : 0 ;

// TOKEN TABLE OBJECT
class TOKEN_L {
	TOKEN_L* _next ,*_last;
	int _code,_id;

public:
	TOKEN_L() {
		_next = nullptr;
		_last = nullptr;
		_code = 0;
		_id = NO_ID;
	}
	void push(int code);
	void set_code(int code);
	void pop(int id);
	void purify();
	void display();
	int get_code(int id, char up_mid_down = 'n');
	int get_self_code();
	int get_id();
	int get_size();
	TOKEN_L* remove();
	TOKEN_L* is_exist(int id);
	TOKEN_L* go_next();
	TOKEN_L* go_last();
};