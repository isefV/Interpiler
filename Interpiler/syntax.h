#pragma once
#include"utility.h"
#include"token.h"
#include"keyword.h"
#include"object.h"
#include"expression.h"
#include"error_handling.h"
#include"state_control_machine.h"

#define ACCEPT_ACTION 1
#define ACCEPT_NO_ACTION 0
#define REFUSE -1

class SYNTACTIC_M {
	EXPRESSION_L _exp;

	// SYNTAX SECTION
	void parse(TOKEN_L* token);
	int syntaxer(int code,int index, int token_size);
	//void display(EXPRESSION_L* root);

public:
	EXPRESSION_L* run(TOKEN_L* tokens);
	void refresh();
};