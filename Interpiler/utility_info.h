#pragma once
#include <string>
#include <iostream>
#include <fstream> 
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
// REQUIRED HEADER
//#include"error_handling.h"

// EASIER SHORTCUTS
#define STRING								std::string
#define FSTREAM								std::fstream
#define IOS									std::ios
#define GET									std::cin
#define PRINT								std::cout
#define VEC									std::vector
#define MAP									std::map
#define SORT								std::sort
//#define STK_INT std::stack<int>

#define PRIME_NUM_A							2707
#define PRIME_NUM_B							7013
#define LIMIT_INDEX							1048575

// COMPONENTS CLASSIFICATION
#define COMPONENTS_NON						0x0
#define COMPONENTS_KEYWORDS					0x10000000			//	TOKEN_L	0XFFF00000
#define COMPONENTS_OPERATORS				0x20000000			//	TOKEN_L	0XFFF00000
#define COMPONENTS_LITERALS					0x30000000			//	TOKEN_L	0XFFFFFFFF
#define COMPONENTS_IDENTIFIER				0x40000000			//	TOKEN_L	0XFFFFFFFF
#define COMPONENTS_STACK					0x50000000			
#define COMPONENTS_ERROR					0x60000000			//	TOKEN_L	0XFFF00000

#define UPCODE								0xF0000000			//	COMPONENT DELIMITER
#define MIDCODE								0x0FF00000			//	TYPE / SUBCODE DELIMITER
#define MIDCODE_LEFT						0x0F000000			
#define MIDCODE_RIGHT						0x00F00000			
#define DOWNCODE							0x000FFFFF			//	ID DELIMITER

// TYPES CLASSIFICATION
#define TYPE_NONT							0x00000000			//	NOT OR UNDEFIEND
#define TYPE_ARR							0x01000000
#define TYPE_NUM							0x00100000 
#define TYPE_STR							0x00200000
#define TYPE_BOOL							0x00300000
#define TYPE_OBJ							0x00400000
#define TYPE_FUNC							0x00500000

// OPERATORS CLASSIFICATION									LESS PRIORITY ~ LESS NUMBER
#define OP_NON								0x00000000
#define OP_ASSIGNMENT						0x01000000
#define OP_SEPRATOR							0x02000000
#define OP_LOGICAL							0x03000000
#define OP_ARITHMETIC						0x04000000
#define OP_OTHER							0x05000000

// SUB OPERATORS CLASSIFICATION								LESS PRIORITY ~ LESS NUMBER
#define OP_ASN_ASSIGNMENT					0x00100000			//  =
#define OP_ASN_POWASSI						0x00200000			// ^=
#define OP_ASN_MULASSI						0x00300000			// *=
#define OP_ASN_DIVASSI						0x00400000			// /=
#define OP_ASN_MODASSI						0x00500000			// %=
#define OP_ASN_SUBASSI						0x00600000			// -=
#define OP_ASN_ADDASSI						0x00700000			// +=
#define OP_ASN_ARRASSI						0x00800000			// +=
	
#define OP_SEP_LEFT_PARENTHESE				0x00100000			// (
#define OP_SEP_RIGHT_PARENTHESE				0x00200000			// )
#define OP_SEP_DOT							0x00300000			// .
#define OP_SEP_COMMA						0x00400000			// ,
#define OP_SEP_COLON						0x00500000			// :
#define OP_SEP_DUOBLE_QUOTE					0x00600000			// "
#define OP_SEP_QUOTE						0x00700000			// '

#define OP_LOG_OR							0x00100000			// |
#define OP_LOG_AND							0x00200000			// &
#define OP_LOG_EQUAL						0x00300000			// ==
#define OP_LOG_NOT_EQUAL					0x00400000			// !=
#define OP_LOG_GREATER_THAN					0x00500000			// >
#define OP_LOG_LESS_THAN					0x00600000			// <
#define OP_LOG_GREATER_EQUAL				0x00700000			// >=
#define OP_LOG_LESS_EQUAL					0x00800000			// <=
#define OP_LOG_OPPOSITE						0x00900000			// !

#define OP_ARI_ADD							0x00100000			// +
#define OP_ARI_SUB							0x00200000			// -
#define OP_ARI_MOD							0x00300000			// %
#define OP_ARI_DIV							0x00400000			// /
#define OP_ARI_MUL							0x00500000			// *
#define OP_ARI_POW							0x00600000			// ^

#define OP_OTR_TYPE							0x00100000			// ?
#define OP_OTR_LEFT_BRACKET					0x00200000			// [
#define OP_OTR_RIGHT_BREACKET				0x00300000			// ]

// KEYWORDS CLASSIFICATION
#define KYW_NON								0x00000000
#define KYW_LOOP							0x00100000
#define KYW_IF								0x00200000
#define KYW_ELF								0x00300000
#define KYW_ELSE							0x00400000
#define KYW_TRUE							0x00500000
#define KYW_FALSE							0x00600000
#define KYW_TO								0x00700000
#define KYW_BY								0x00800000
#define KYW_RUTIN							0x00900000
#define KYW_RET								0x00A00000
#define KYW_STOP							0x00B00000
#define KYW_NEXT							0x00C00000
#define KYW_INPUT							0x00D00000
#define KYW_OUTPUT							0x00E00000

// ERROR MESSAGES CLASSIFICATION
#define ERR_UNKOWN							0x00100000
#define ERR_TYPE							0x00200000
#define ERR_REFERENCE						0x00300000
#define ERR_LEXICAL							0x00400000
#define ERR_SYNTAX							0x00500000
#define ERR_RANGE							0x00600000
#define ERR_CASTING							0x00700000
#define ERR_WRONGVAR						0x00800000
#define ERR_INDENT							0x00900000

// BYTECODE INSTRUCTIONS CLASSIFICATION
#define INSTRUCTION_SET_VAR					0x101
#define INSTRUCTION_GET_ARR					0x102	// GET ARR + INDEX
#define INSTRUCTION_PUSH					0x103	// PUSH ITEM TO TOP STACK
#define INSTRUCTION_POP						0x104	// POP TOP ITEM IN STACK INTO
#define INSTRUCTION_JIF						0x105	// JUMP IF FASLE
#define INSTRUCTION_JUMP					0x106
#define INSTRUCTION_INVOKE 					0x107
#define INSTRUCTION_CALL					0x108
#define INSTRUCTION_INPUT					0x109
#define INSTRUCTION_OUTPUT					0x10A
#define INSTRUCTION_CAST					0x10B	// CAST TYPE TO
#define INSTRUCTION_TYPE					0x10C

#define INSTRUCTION_ADD						0x201
#define INSTRUCTION_SUB						0x202
#define INSTRUCTION_MOD						0x203
#define INSTRUCTION_MUL						0x204
#define INSTRUCTION_DIV						0x205
#define INSTRUCTION_POW						0x206

#define INSTRUCTION_OR						0x301
#define INSTRUCTION_AND						0x302
#define INSTRUCTION_EQ						0x303
#define INSTRUCTION_GT						0x304
#define INSTRUCTION_LT						0x305
#define INSTRUCTION_GE						0x306
#define INSTRUCTION_LE						0x307
#define INSTRUCTION_NOT						0x308

#define INSTRUCTION_END						0x000

//SYNTAX CONSTANT
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


#define INC(number,value) number += number + value
#define DEC(number,value) number -= value
#define LESS_THAN_ZERO(number,value) if (number - value < 0) __errors_handler.rise_err(ERR_SYNTAX)
#define TOKEN_IS_KEYWORD(code,type)	(code & (UPCODE + MIDCODE)) == COMPONENTS_KEYWORDS + type

extern bool debug_mode;
extern bool _syntax_flag[];	// 0 - LOOP EXP
							// 1 - LOOP TO
							// 2 - LOOP TO BY