#pragma once
#include"utility.h"
#include"lexical.h"
#include"syntax.h"
#include"semantic.h"


// TRANSLATOR MACHINE OBJECT
class TM {
	LEXICAL_M _lexer;
	SYNTACTIC_M _syntaxer;
	SEMANTIC_M _semanticer;
	
public:
	void refresh();
	void run(str* cmd);
};