#pragma once
#include"utility.h"
#include"keyword.h"
#include"translator_machine.h"
#include"state_control_machine.h"

str _code_line;

// MACHINE OBJECTS
SCM __state_control_machine;
TM __trans_machine;

// HANDLER OBJECTS
BYTECODE_H __bytecode_handler;
ERROR_H __errors_handler;

// TABLE OBJECTS
OBJECT_T __objects_table;
JUMP_T __jump_table;
ARRAY_T __array_table;
FUNCTION_T __func_table;
ARGUMENT_T __args_table;

KEYWORD_ _keyword;
