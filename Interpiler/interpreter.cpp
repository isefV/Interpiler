#include"interpreter.h"

void interp_parse_tree() {
	EXPRESSION* _root = &_exp;
	int code = _root->get_code();

	// IF ROOT CODE HAS EXP THE PARSE MODE LIKE : VAR = EXP | EXP
	if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == OPERATORS + ASSIGNMENT_OPERATORS) {
		interp_parse_exp(_root, "");
		//int s = (d & DELIMITER_DOWNCODE);
		//print << *(float*)_objects.get_address(s);
	}
	else if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == OPERATORS + LOGICAL_OPERATORS) {
		int keyword = _tokens.get_self_code() & (DELIMITER_UPCODE + DELIMITER_MIDCODE);
		if (keyword == KEYWORDS + LOOP) {
			EXPRESSION* _new_root = _exp.copy();
			// SET CONDITION FLOW CONTROL 'WHILE' TYPE
			interp_set_loop_condition(true, _new_root);
		}
		else if ((keyword == KEYWORDS + IF) || (keyword == KEYWORDS + ELF) || (keyword == KEYWORDS + ELSE)) {
			_condition_state.push(true);
		}
	}
	
	// IF ROOT CODE HAS 'TO' KEYWORD THE PARSE MODE LIKE : DEFINE VAR TO END VAR INC / DEC
	else if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + TO) {

		EXPRESSION* left = _root->get_childs(false), * right = _root->get_childs(true);
		int lcode = left->get_code(), rcode = right->get_code();

		// CREATE CONDITION EXP FOR LOOP FLOW CONTROL
		EXPRESSION* condition = new EXPRESSION;
		condition->push(OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC);

		//	CHECK LEFT SIDE OF TREE HAS : VAR = LIT | VAR : LIT | VAR
		// SET ITERATION VARIABLE
		if (((lcode & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI)
			|| ((lcode & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == OPERATORS + SEPRATOR_OPERATORS + SEP_COLON)) {

			// ASSIGN ITERATION VARIABLE
			lcode = (OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI);
			int var = left->get_childs(false)->get_code(), lit = left->get_childs(true)->get_code();
			var = interp_parse_op(lcode, var, lit, "");
			condition->push(var);
		}
		else if (lcode & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT) == (IDENTIFIER + NUM)) {
			if ((lcode & DELIMITER_MIDCODE) == NOT)
				rise_err(ERR_WRONGVAR, _current_line, "");

			// ITERATION VARIABLE ALEARDY DEFINED
			condition->push(lcode);
		}
		else
			rise_err(ERR_REFERENCE, _current_line, "");

		// SET STEP AND END VARIABLE
		int step = lex_set_object("#step", NOT), end = lex_set_object("#end", NOT), end_id = rcode & DELIMITER_DOWNCODE;
		void* step_address = _objects.get_address(step), * end_address = _objects.get_address(end);

		*(float*)step_address = (float)1;
		*(float*)end_address = *(float*)_objects.get_address(end_id);
		_objects.assign_val(step, NUM, step_address, false);
		_objects.assign_val(end, NUM, end_address, false);

		condition->push(OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ADDASSI);
		condition->push(step);
		condition->push(OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC);
		condition->push(OPERATORS + LOGICAL_OPERATORS + LOG_LTEQU);
		condition->push(end);

		// SET CONDITION FLOW CONTROL 'FOR' TYPE
		interp_set_loop_condition(false, condition);
	}
	
	// IF ROOT CODE HAS FUNCTION THE PARSE MODE LIKE : RUTIN FUNC_NAME ( VAR , VAR , ... )
	else if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == IDENTIFIER + FUNC) {

	}
}

int interp_parse_exp(EXPRESSION* root, str level) {

	// PARSE TREE OF LEFT NODE TO RIGHT NODE
	if (root->is_tree()) {
		int code_op = root->get_code(),
			code_left = interp_parse_exp(root->get_childs(false), level + "L"),
			code_right = interp_parse_exp(root->get_childs(true), level + "R"),
			result = 0;
		bool is_one = false;

		if (code_left == 0) {
			code_left = code_right;
			code_right = 0;
			is_one = true;
		}
		else if (code_right == 0)
			is_one = true;

		// PARSE TREE IN THREE ADDRESS (OP,VAR_1 ,VAR_2)
		return interp_parse_op(code_op, code_left, code_right, level, is_one);
	}

	return root->get_code();
}

int interp_parse_op(int op, int code_1, int code_2, str level, bool is_one_op) {

	int addr_1 = (code_1 & DELIMITER_DOWNCODE), addr_2 = (code_2 & DELIMITER_DOWNCODE),
		type_1 = (code_1 & DELIMITER_MIDCODE_RIGHT), type_2 = (code_2 & DELIMITER_MIDCODE_RIGHT),
		type_op = 0, code = 0, assign_id = (addr_1 & DELIMITER_DOWNCODE);

	void* val_1 = _objects.get_address(addr_1), * val_2 = _objects.get_address(addr_2);

	if (!is_one_op && (type_2 == NOT || type_1 == OBJ || type_1 == FUNC))
		rise_err(ERR_WRONGVAR, _current_line, "");

	// CASTING TYPE IF TYPES DIFFERENT AND OP != ASSIGNMENT
	if (!is_one_op && type_1 != type_2 && (op != (OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI))) {

		// BOOL TO NUM
		if (type_1 == NUM && type_2 == BOOL) {
			*(float*)val_2 = utl_to_num(val_2, BOOL);
		}
		else if (type_1 == BOOL && type_2 == NUM) {
			*(float*)val_1 = utl_to_num(val_1, BOOL);
		}

		// STR TO BOOL
		else if (type_1 == BOOL && type_2 == STR) {
			*(bool*)val_1 = utl_to_bool(val_2, STR);
		}
		else if (type_1 == STR && type_2 == BOOL) {
			*(bool*)val_2 = utl_to_bool(val_1, STR);
		}

		// NUM TO STR
		else if (type_1 == NUM && type_2 == STR) {
			*(char**)val_1 = utl_to_str(val_1, NUM);
		}
		else if (type_1 == STR && type_2 == NUM) {
			*(char**)val_2 = utl_to_str(val_2, NUM);
		}
		else
			rise_err(ERR_WRONGVAR, _current_line, "");
	}

	void* address = utl_generate_address();
	int code_id = lex_id_object_encoder("#" + level);

	if (is_one_op) {
		code = LITERALS;
		// OP = ! -> OP VAL : ! X
		if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + LOGICAL_OPERATORS + LOG_NOT)) {
			if (type_1 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 != 0 ? false : true;

				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL) {
				code += BOOL;
				*(bool*)address = !(*(bool*)val_1);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR) {
				code += BOOL;
				*(bool*)address = (*(char**)val_1 == "");
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = ? -> VAL OP : X ?
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + OTHER_OPERATORS + OTH_TYPE)) {
			if (type_1 == NUM) {
				code += STR;
				*(str*)address = "NUM";
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
			else if (type_1 == BOOL) {
				code += STR;
				*(str*)address = "BOOL";
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
			else if (type_1 == STR) {
				code += STR;
				*(str*)address = "STR";
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
			else if (type_1 == OBJ) {
				code += STR;
				*(str*)address = "OBJ";
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
			else if (type_1 == FUNC) {
				code += STR;
				*(str*)address = "FUNC";
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
		}
	}

	if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == (OPERATORS + ASSIGNMENT_OPERATORS))
	{
		code = IDENTIFIER;
		// OP = = -> VAL OP VAL : X = X
		if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ASSI_ASSI)) {
			if (type_2 == NUM) {
				code += NUM;
				*(float*)address = *(float*)val_2;
				_objects.assign_val(assign_id, NUM, address, false);
				return code + assign_id;
			}
			else if (type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = *(bool*)val_2;
				_objects.assign_val(assign_id, BOOL, address, false);
				return code + assign_id;
			}
			else if (type_2 == STR) {
				code += STR;
				*(char**)address = *(char**)val_2;
				_objects.assign_val(assign_id, STR, address, false);
				return code + assign_id;
			}
		}
		// OP = ^= -> VAL OP VAL : X ^= X | X = X ^ X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ASSI_POWASSI)) {
			if (type_1 == NUM && type_2 == NUM) {
				float base = *(float*)val_1, pow = *(float*)val_2;
				for (int i = 1; i <= (int)pow; i++)
					base *= pow;
				*(float*)address = base;
				_objects.assign_val(assign_id, NUM, address, false);
				return code_1;
			}
		}
		// OP = *= -> VAL OP VAL : X *= X | X = X * X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ASSI_MULASSI)) {
			if (type_1 == NUM && type_2 == NUM) {
				*(float*)address = (*(float*)val_1) * (*(float*)val_2);
				_objects.assign_val(assign_id, NUM, address, false);
				return code_1;
			}
			/*else if (type_1 == STR && type_2 == NUM) {
				str temp = (*(str*)val_1);
				int copies = (int)(*(float*)val_2);
				for (int i = 0; i < copies; i++)
					temp += (*(str*)val_1);
				*(str*)val_1 = temp;
				return code_1;
			}
			else if (type_1 == NUM && type_2 == STR ) {
				str temp = (*(str*)val_2);
				int copies = (int)(*(float*)val_1);
				for (int i = 0; i < copies; i++)
					temp += (*(str*)val_2);
				*(str*)val_1 = temp;
				code_1 = (code_1 & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT + DELIMITER_DOWNCODE)) + STR;
				return code_1;
			}*/
			else if (type_1 == STR && type_2 == STR) {
				str temp_1 = (*(char**)val_1), temp_2 = (*(char**)val_2);
				int copies = temp_2.length() - 1;
				for (int i = 0; i < copies; i++)
					temp_1 += temp_1;
				*(char**)address = utl_set_string(temp_1);;
				_objects.assign_val(assign_id, STR, address, false);
				return code_1;
			}
		}
		// OP = /= -> VAL OP VAL : X /= X | X = X / X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ASSI_DIVASSI)) {
			if (type_1 == NUM && type_2 == NUM) {
				*(float*)address = (*(float*)val_1) / (*(float*)val_2);
				_objects.assign_val(assign_id, NUM, address, false);
				return code_1;
			}
		}
		// OP = %= -> VAL OP VAL : X %= X | X = X % X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ASSI_MODASSI)) {
			if (type_1 == NUM && type_2 == NUM) {
				*(float*)address = (int)(*(float*)val_1) % (int)(*(float*)val_2);
				_objects.assign_val(assign_id, NUM, address, false);
				return code_1;
			}
		}
		// OP = -= -> VAL OP VAL : X -= X | X = X - X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ASSI_SUBASSI)) {
			if (type_1 == NUM && type_2 == NUM) {
				*(float*)address = (*(float*)val_1) - (*(float*)val_2);
				_objects.assign_val(assign_id, NUM, address, false);
				return code_1;
			}
		}
		// OP = += -> VAL OP VAL : X += X | X = X + X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ADDASSI)) {
			if (type_1 == NUM && type_2 == NUM) {
				*(float*)address = (*(float*)val_1) + (*(float*)val_2);
				_objects.assign_val(assign_id, NUM, address, false);
				return code_1;
			}
			/*else if (type_1 == STR && type_2 == NUM) {
				*(str*)val_1 = (*(str*)val_1) + std::to_string((*(float*)val_2));
				return code_1;
			}
			else if (type_1 == NUM && type_2 == STR) {
				*(str*)val_1 = std::to_string((*(float*)val_1)) + (*(str*)val_2);
				code_1 = (code_1 & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT + DELIMITER_DOWNCODE)) + STR;
				return code_1;
			}*/
			else if (type_1 == STR && type_2 == STR) {
				str temp_1 = (*(char**)val_1), temp_2 = (*(char**)val_2);
				*(char**)address = utl_set_string(temp_1 + temp_2);
				_objects.assign_val(assign_id, STR, address, false);
				return code_1;
			}
		}
	}

	else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == (OPERATORS + LOGICAL_OPERATORS))
	{
		code = LITERALS;
		// OP = | -> VAL OP VAL : X | X 
		if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_OR)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = utl_to_bool(val_1, NUM) || utl_to_bool(val_2, NUM);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = *(bool*)val_1 || *(bool*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				*(bool*)address = utl_to_bool(val_1, STR) || utl_to_bool(val_2, STR);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = & -> VAL OP VAL : X & X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_AND)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = utl_to_bool(val_1, NUM) && utl_to_bool(val_2, NUM);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = *(bool*)val_1 && *(bool*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				*(bool*)address = utl_to_bool(val_1, STR) && utl_to_bool(val_2, STR);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = > -> VAL OP VAL : X > X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_GT)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 > *(float*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = utl_to_num(val_1, BOOL) > utl_to_num(val_1, BOOL);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(bool*)address = temp_1.length() > temp_2.length();
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = < -> VAL OP VAL : X < X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_LT)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 < *(float*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = utl_to_num(val_1, BOOL) < utl_to_num(val_1, BOOL);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(bool*)address = temp_1.length() < temp_2.length();
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = <= -> VAL OP VAL : X <= X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_LTEQU)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 <= *(float*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = utl_to_num(val_1, BOOL) <= utl_to_num(val_1, BOOL);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(bool*)address = temp_1.length() <= temp_2.length();
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = >= -> VAL OP VAL : X >= X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_GTEQU)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 >= *(float*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = utl_to_num(val_1, BOOL) >= utl_to_num(val_1, BOOL);
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(bool*)address = temp_1.length() >= temp_2.length();
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = != -> VAL OP VAL : X != X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_NOTEQU)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 != *(float*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = *(bool*)val_1 != *(bool*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(bool*)address = temp_1 == temp_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
		// OP = == -> VAL OP VAL : X == X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + LOG_EQU)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += BOOL;
				*(bool*)address = *(float*)val_1 == *(float*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += BOOL;
				*(bool*)address = *(bool*)val_1 == *(bool*)val_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += BOOL;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(bool*)address = temp_1 != temp_2;
				_objects.push(code_id, BOOL, address);
				return code + code_id;
			}
		}
	}

	else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == (OPERATORS + ARITHMETIC_OPERATORS))
	{
		code = LITERALS;
		// OP = + -> VAL OP VAL : X + X 
		if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ARI_ADD)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += NUM;
				*(float*)address = *(float*)val_1 + *(float*)val_2;
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
			else if (type_1 == BOOL && type_2 == BOOL) {
				code += NUM;
				*(float*)address = utl_to_num(val_1, BOOL) + utl_to_num(val_2, BOOL);
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += STR;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				*(char**)address = utl_set_string(temp_1 + temp_2);;
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
		}
		// OP = + -> VAL OP VAL : X - X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ARI_SUB)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += NUM;
				*(float*)address = *(float*)val_1 - *(float*)val_2;
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
		}
		// OP = + -> VAL OP VAL : X % X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ARI_MOD)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += NUM;
				*(float*)address = (int)*(float*)val_1 % (int)*(float*)val_2;
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
		}
		// OP = + -> VAL OP VAL : X / X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ARI_DIV)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += NUM;
				*(float*)address = *(float*)val_1 / *(float*)val_2;
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
		}
		// OP = + -> VAL OP VAL : X * X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ARI_MUL)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += NUM;
				*(float*)address = *(float*)val_1 * *(float*)val_2;
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
			else if (type_1 == STR && type_2 == STR) {
				code += STR;
				str temp_1 = *(char**)val_1, temp_2 = *(char**)val_2;
				int copies = temp_2.length();
				for (int i = 0; i < copies; i++)
					temp_1 += temp_1;
				*(char**)address = utl_set_string(temp_1);;
				_objects.push(code_id, STR, address);
				return code + code_id;
			}
		}
		// OP = + -> VAL OP VAL : X ^ X 
		else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE_RIGHT)) == (OPERATORS + ARI_POW)) {
			if (type_1 == NUM && type_2 == NUM) {
				code += NUM;
				float base = *(float*)val_1, pow = *(float*)val_2;
				for (int i = 1; i <= (int)pow; i++)
					base *= pow;
				*(float*)address = base;
				_objects.push(code_id, NUM, address);
				return code + code_id;
			}
		}
	}

	rise_err(ERR_TYPE, _current_line, "");
}

void interp_set_loop_condition(bool is_while, EXPRESSION* condition) {
	if (is_while)
		_jump_mod = J_WHILE;
	else
		_jump_mod = J_FOR;

	_condition_exp = condition;
}

bool interp_loop_condition() {
	int res = interp_parse_exp(_condition_exp, "");

	if (!*(bool*)_objects.get_address(res)) {
		_jump_mod = NOJUMP;
		_condition_exp->purify(_condition_exp, 0);
		return false;
	}
	return true;
}