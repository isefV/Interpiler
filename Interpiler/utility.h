#pragma once
#include<string>
#include<iostream>
#include<stack>

// REQUIRED HEADER
//#include"error_handling.h"

// EASIER SHORTCUTS
#define str std::string
#define stackint std::stack<int>
#define stackbool std::stack<bool>
#define byte uint8_t
#define unit unsigned short int
#define fs std::fstream
#define ios std::ios

#define get std::cin
#define print std::cout

#define PRIME_NUM_A 2707
#define PRIME_NUM_B 7013
#define LIMIT_INDEX 1048575
											
// COMPONENTS CLASSIFICATION
#define KEYWORDS						0x10000000			//	TOKEN_L	0XFFF00000
#define OPERATORS						0x20000000			//	TOKEN_L	0XFFF00000
#define LITERALS						0x30000000			//	TOKEN_L	0XFFFFFFFF
#define IDENTIFIER						0x40000000			//	TOKEN_L	0XFFFFFFFF
#define STACK							0x50000000
#define ERROR							0x60000000			//	TOKEN_L	0XFFF00000

#define DELIMITER_UPCODE				0xF0000000			//	COMPONENT DELIMITER
#define DELIMITER_MIDCODE				0x0FF00000			//	TYPE / SUBCODE DELIMITER
#define DELIMITER_DOWNCODE				0x000FFFFF			//	ID DELIMITER

#define DELIMITER_MIDCODE_LEFT			0x0F000000			//	ARR
#define DELIMITER_MIDCODE_RIGHT			0x00F00000			//	TYPE

// TYPES CLASSIFICATION
#define NOT								0x00000000			//	NOT OR UNDEFIEND
#define ARR								0x01000000
#define TMP								0x02000000
#define NUM								0x00100000 
#define STR								0x00200000
#define BOOL							0x00300000
#define OBJ								0x00400000
#define FUNC							0x00500000

// OPERATORS CLASSIFICATION									LESS PRIORITY ~ LESS NUMBER
#define NON_OPERATORS					0x00000000
#define ASSIGNMENT_OPERATORS			0x01000000
#define SEPRATOR_OPERATORS				0x02000000
#define LOGICAL_OPERATORS				0x03000000
#define ARITHMETIC_OPERATORS			0x04000000
#define OTHER_OPERATORS					0x05000000

// SUB OPERATORS CLASSIFICATION								LESS PRIORITY ~ LESS NUMBER
#define ASSI_ASSI						0x00100000			//  =
#define ASSI_POWASSI					0x00200000			// ^=
#define ASSI_MULASSI					0x00300000			// *=
#define ASSI_DIVASSI					0x00400000			// /=
#define ASSI_MODASSI					0x00500000			// %=
#define ASSI_SUBASSI					0x00600000			// -=
#define ASSI_ADDASSI					0x00700000			// +=
#define ASSI_ARR						0x00800000			// +=

#define SEP_L_BRAC						0x00100000			// (
#define SEP_R_BRAC						0x00200000			// )
#define SEP_DOT							0x00300000			// .
#define SEP_COMMA						0x00400000			// ,
#define SEP_COLON						0x00500000			// :
#define SEP_DUBL_QUOTE					0x00600000			// "
#define SEP_QUOTE						0x00700000			// '

#define LOG_OR							0x00100000			// |
#define LOG_AND							0x00200000			// &
#define LOG_GT							0x00300000			// >
#define LOG_LT							0x00400000			// <
#define LOG_LTEQU						0x00500000			// <=
#define LOG_GTEQU						0x00600000			// >=
#define LOG_NOTEQU						0x00700000			// !=
#define LOG_EQU							0x00800000			// ==
#define LOG_NOT							0x00900000			// !

#define ARI_ADD							0x00100000			// +
#define ARI_SUB							0x00200000			// -
#define ARI_MOD							0x00300000			// %
#define ARI_DIV							0x00400000			// /
#define ARI_MUL							0x00500000			// *
#define ARI_POW							0x00600000			// ^

#define OTH_TYPE						0x00100000			// ?
#define OTH_L_REF						0x00200000			// [
#define OTH_R_REF						0x00300000			// ]

// KEYWORDS CLASSIFICATION
#define LOOP							0x00100000
#define IF								0x00200000
#define ELF								0x00300000
#define ELSE							0x00400000
#define TRUE							0x00500000
#define FALSE							0x00600000
#define TO								0x00700000
#define BY								0x00800000
#define RUTIN							0x00900000
#define RET								0x00A00000
#define STOP							0x00B00000
#define NEXT							0x00C00000
#define INPUT							0x00D00000
#define OUTPUT							0x00E00000

// ERROR MESSAGES CLASSIFICATION
#define ERR_UNKOWN						0x00100000
#define ERR_TYPE						0x00200000
#define ERR_REFERENCE					0x00300000
#define ERR_LEXICAL						0x00400000
#define ERR_SYNTAX						0x00500000
#define ERR_RANGE						0x00600000
#define ERR_CASTING						0x00700000
#define ERR_WRONGVAR					0x00800000
#define ERR_INDENT						0x00900000

// BYTECODE INSTRUCTIONS CLASSIFICATION
#define INS_SET_VAR						0x101
#define INS_GET_ARR						0x102
#define INS_PUSH						0x103
#define INS_POP							0x104
#define INS_JIF							0x105
#define INS_JUMP						0x106
#define INS_INVOKE 						0x107
#define INS_CALL						0x108
#define INS_INPUT						0x109
#define INS_OUTPUT						0x10A
#define INS_CTYP						0x10B

#define INS_STK_1						0x10C
#define INS_STK_2						0x10D

#define INS_ADD							0x201
#define INS_SUB							0x202
#define INS_MUL							0x203
#define INS_DIV							0x204
#define INS_MOD							0x205
#define INS_POW							0x206

#define INS_OR							0x301
#define INS_AND							0x302
#define INS_EQ							0x303
#define INS_GT							0x304
#define INS_GE							0x305
#define INS_LT							0x306
#define INS_LE							0x307
#define INS_NOT							0x308

#define INS_WTP							0x401

#define INS_TMT							0x000

#define NO_JUMP							0x000

// REQUIRED FUNCTIONS
float utl_to_num(void* var, int type);
char* utl_to_str(void* var, int type);
char* utl_set_string(str string);
bool utl_to_bool(void* var, int type);
void* utl_generate_address();
void utl_neutralization();
int object_encoder_id(str token);