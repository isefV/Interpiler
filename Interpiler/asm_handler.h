#pragma once

#include <fstream>
#include <iostream>
#include"utility.h"

#define FS std::fstream

#define ASM_DATA "asm_data.txt"
#define ASM_CODE "asm_code.txt"



#define _ASM_PRINT "MOV\t%ah,9\nINT\t0x21\n"

#define _ASM_END "MOV\t%ah,0x4c\nINT\t0x21\n"


bool asm_create_files();
bool asm_write_data(str string);
bool asm_write_code(str string);