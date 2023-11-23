#pragma once
#include"utility_info.h"
#include"object_table.h"
#include"error_handling.h"
#include"input_control_machin.h"
#include"lexical.h"
#include"syntactic.h"

STRING __command = "";
INCM __input_controler;

LEXICAL_M __lexer;
SYNTACTIC_M __syntaxer;

ERROR_H __errors_handler;

OBJECT_T __objects_table;