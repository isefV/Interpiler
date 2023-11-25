#pragma once
#include"utility_info.h"
#include"object.h"
#include"error_handling.h"
#include"input_control_machin.h"
#include"lexical.h"
#include"syntactic.h"
#include "semantic.h"

bool debug_mode = true;

STRING __command = "";
INCM __input_controler;

LEXICAL_M __lexer;
SYNTACTIC_M __syntaxer;
SEMANTIC_M __semanticer;

ERROR_H __errors_handler;
BYTECODE_H __bytecode_handler;

//OBJECT_T __objects_table;

MAP<int,OBJECT*> __objects_table;