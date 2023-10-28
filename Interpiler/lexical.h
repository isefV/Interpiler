#pragma once

#include "utility.h"
#include"error_handling.h"

void lex_purification(str* cmd);

void lex_tokenization(str* cmd);

int lex_token_code_detector(str token, bool is_text);
int lex_keyword_detector(str token);
int lex_operator_detector(str token);
int lex_object_detector(str token, bool is_text);
int lex_id_object_encoder(str token);
int lex_set_object(str token, int type, bool is_temp = true);
