#pragma once
#include<string>
#include<iostream>
#include<stack>

// REQUIRED HEADER
#include"error_handling.h"

// EASIER SHORTCUTS
#define str std::string
#define stackint std::stack<int>
#define stackbool std::stack<bool>
#define byte uint8_t
#define unit unsigned short int

#define get std::cin
#define print std::cout

#define PRIME_NUM_A 2707
#define PRIME_NUM_B 7013
#define LIMIT_INDEX 1048575

// COMPONENTS CLASSIFICATION
#define KEYWORDS				0x10000000		//	TOKEN	0XFFF00000
#define OPERATORS				0x20000000		//	TOKEN	0XFFF00000
#define LITERALS				0x30000000		//	TOKEN	0XFFFFFFFF
#define IDENTIFIER				0x40000000		//	TOKEN	0XFFFFFFFF
#define ERROR					0x50000000		//	TOKEN	0XFFF00000

#define DELIMITER_UPCODE		0xF0000000		//	COMPONENT DELIMITER
#define DELIMITER_MIDCODE		0x0FF00000		//	TYPE / SUBCODE DELIMITER
#define DELIMITER_DOWNCODE		0x000FFFFF		//	ID DELIMITER

#define DELIMITER_MIDCODE_LEFT	0x0F000000		//	ARR
#define DELIMITER_MIDCODE_RIGHT	0x00F00000		//	TYPE

// TYPES CLASSIFICATION
#define NOT						0x00000000		//	NOT OR UNDEFIEND
#define ARR						0x01000000
#define NUM						0x00100000 
#define STR						0x00200000
#define BOOL					0x00300000
#define OBJ						0x00400000
#define FUNC					0x00500000

// OPERATORS CLASSIFICATION						LESS PRIORITY ~ LESS NUMBER
#define NON_OPERATORS			0x00000000
#define ASSIGNMENT_OPERATORS	0x01000000
#define SEPRATOR_OPERATORS		0x02000000
#define LOGICAL_OPERATORS		0x03000000
#define ARITHMETIC_OPERATORS	0x04000000
#define OTHER_OPERATORS			0x05000000

// SUB OPERATORS CLASSIFICATION					LESS PRIORITY ~ LESS NUMBER
#define OTH_TYPE				0x00100000		// ?
#define OTH_L_REF				0x00200000		// [
#define OTH_R_REF				0x00300000		// ]

#define ARI_ADD					0x00100000		// +
#define ARI_SUB					0x00200000		// -
#define ARI_MOD					0x00300000		// %
#define ARI_DIV					0x00400000		// /
#define ARI_MUL					0x00500000		// *
#define ARI_POW					0x00600000		// ^

#define LOG_OR					0x00100000		// |
#define LOG_AND					0x00200000		// &
#define LOG_GT					0x00300000		// >
#define LOG_LT					0x00400000		// <
#define LOG_LTEQU				0x00500000		// <=
#define LOG_GTEQU				0x00600000		// >=
#define LOG_NOTEQU				0x00700000		// !=
#define LOG_EQU					0x00800000		// ==
#define LOG_NOT					0x00900000		// !

#define SEP_L_BRAC				0x00100000		// (
#define SEP_R_BRAC				0x00200000		// )
#define SEP_DOT					0x00300000		// .
#define SEP_COMMA				0x00400000		// ,
#define SEP_COLON				0x00500000		// :
#define SEP_DUBL_QUOTE			0x00600000		// "
#define SEP_QUOTE				0x00700000		// '

#define ASSI_ASSI				0x00100000		//  =
#define ASSI_POWASSI			0x00200000		// ^=
#define ASSI_MULASSI			0x00300000		// *=
#define ASSI_DIVASSI			0x00400000		// /=
#define ASSI_MODASSI			0x00500000		// %=
#define ASSI_SUBASSI			0x00600000		// -=
#define ASSI_ADDASSI			0x00700000		// +=
#define ASSI_ARR				0x00800000		// +=

// KEYWORDS CLASSIFICATION
#define LOOP					0x00100000
#define IF						0x00200000
#define ELF						0x00300000
#define ELSE					0x00400000
#define TRUE					0x00500000
#define FALSE					0x00600000
#define TO						0x00700000
#define BY						0x00800000
#define RUTIN					0x00900000
#define RET						0x00A00000
#define STOP					0x00B00000
#define NEXT					0x00C00000
#define INPUT					0x00D00000
#define OUTPUT					0x00E00000

// ERROR MESSAGES
#define ERR_UNKOWN				0x00100000
#define ERR_TYPE				0x00200000
#define ERR_REFERENCE			0x00300000
#define ERR_LEXICAL				0x00400000
#define ERR_SYNTAX				0x00500000
#define ERR_RANGE				0x00600000
#define ERR_CASTING				0x00700000
#define ERR_WRONGVAR			0x00800000

// REQUIRED CLASS
class OBJECT {
	OBJECT* _next;
	int _id, _type;
	void* _value;
	bool _is_temp;

public:
	OBJECT() {
		_id = 0;
		_type = NOT;
		_next = nullptr;
		_value = nullptr;
		_is_temp = true;
	}
	bool push(int id, int type, void* address, bool is_temp = true);
	bool pop(int id);
	OBJECT* is_exist(int id);
	void* get_address(int id);
	int get_type(int id);
	void assign_val(int id, int type, void* address, bool is_temp);
	void purify_duplications();
	void display();
};

class TOKEN {
	TOKEN* _next;
	int _code;

public:
	TOKEN() {
		_next = nullptr;
		_code = 0;
	}
	bool push(int code);
	bool pop(int step);
	int get_code(int step, char up_mid_down = 'n');
	int get_self_code(char up_mid_down = 'n');
	TOKEN* go_next();
	void purify();
	void display();
};

class EXPRESSION {
	EXPRESSION* _left, * _right;
	int _code;
	short unsigned int _priority;
	bool _is_tree;

public:
	EXPRESSION() {
		_left = nullptr;
		_right = nullptr;
		_priority = 0;
		_code = 0;
		_is_tree = false;
	}
	bool push(int code);
	int get_code();
	bool is_tree();
	void purify(EXPRESSION* root, int level);
	EXPRESSION* get_childs(bool is_right);
	EXPRESSION* copy();
};

class KEYWORD {
	int _keyword_code;

public:
	KEYWORD() {
		_keyword_code = 0;
	}
	void reset();
	bool is_loop();
};

// REQUIRED GLOBAL VARIABLE
extern unit _last_level,_current_level, _code_line_size, _current_line,
_objects_size, _tokens_size, _paran;

extern bool _ref, _compile_mod;
extern OBJECT _objects;
extern TOKEN _tokens;
extern EXPRESSION _exp;
extern str _code_line , _program;
extern stackbool _condition_state;


// REQUIRED FUNCTIONS
//unit utl_len_char(cstr cmd);
//bool utl_cmp_2str(cstr string, cstr string_2);

float utl_to_num(void* var, int type);
char* utl_to_str(void* var, int type);
char* utl_set_string(str string);
bool utl_to_bool(void* var, int type);


//char* utl_cpy_substr(cstr string, unit start, unit end);
//char* utl_reset_string(char* string, cstr nstring);
//void utl_unset_string(char* string);

void* utl_generate_address();
void utl_neutralization();
void display_tree(EXPRESSION* root, int level);