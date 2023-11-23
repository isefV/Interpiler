#pragma once
#include"utility_info.h"

float utl_to_num(void* var, int type);
char* utl_to_str(void* var, int type);
char* utl_set_string(STRING string);
bool utl_to_bool(void* var, int type);
void* utl_generate_address();
void utl_neutralization();
int object_encoder_id(STRING token);