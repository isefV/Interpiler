#include"semantic.h"

//// SEMANTIC PARSE TREE SECTION
//void SEMANTIC_M::parser() {
//	if (_keyword.is_loop() && _exp->get_code() != (KEYWORDS + TO))
//		__state_control_machine.loop_jump_control_exp();
//	else if (_keyword.is_next())
//		__state_control_machine.next_jump_control();
//	else if (_keyword.is_stop())
//		__state_control_machine.stop_jump_control();
//
//	int result_exp = parse_code();
//
//	if (_keyword.is_if())
//		__state_control_machine.if_jump_control(result_exp);
//	else if (_keyword.is_elf())
//		__state_control_machine.elf_jump_control(result_exp);
//	else if (_keyword.is_else())
//		__state_control_machine.elf_jump_control(result_exp);
//	else if (_keyword.is_loop() && _exp->get_code() != (KEYWORDS + TO))
//		__state_control_machine.loop_jump_control(result_exp);
//	else if (_keyword.is_ret())
//		__state_control_machine.ret_jump_control();
//}
//
//int SEMANTIC_M::parse_code() {
//	EXPRESSION_L* _root = _exp;
//	int code = _root->get_code();
//
//	// IF ROOT CODE HAS ARRAY THE PARSE MODE LIKE : VAR_ARR #= VAL_1 , ... , VAL_N
//	if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ARR) {
//		int index = 0;
//		int arr = _root->get_childs(false)->get_code() + ARR;
//		print << arr << '\n';
//		return parse_arr_tree(_root->get_childs(true), arr, 0);
//	}
//	// IF ROOT CODE HAS EXP THE PARSE MODE LIKE : VAR = EXP | EXP
//	else if (((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == OPERATORS + ASSIGNMENT_OPERATORS)
//		|| ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE_LEFT)) == OPERATORS + LOGICAL_OPERATORS)) {
//		return parse_tree(_root, "");
//	}
//	// IF ROOT CODE HAS 'TO' KEYWORD THE PARSE MODE LIKE : DEFINE VAR TO END VAR INC / DEC
//	else if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + TO) {
//		return parse_loop_to_tree(_root);
//	}
//	// IF ROOT CODE HAS FUNCTION THE PARSE MODE LIKE : RUTIN FUNC_NAME ( VAR , VAR , ... ) ~ INVOKE
//	else if (_keyword.is_rutin() && ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == IDENTIFIER + FUNC)) {
//		return parse_invoke_func_tree(_root, true, 0);
//	}
//	// IF ROOT CODE HAS FUNCTION THE PARSE MODE LIKE : FUNC_NAME ( VAR , VAR , ... ) ~ CALL
//	else if (((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == IDENTIFIER + FUNC)) {
//		return parse_call_func_tree(_root, true, 0);
//	}
//	// IF KEYWORD HAS RET
//	else if (_keyword.is_ret()) {
//		__args_table.purify();
//		return parse_ret_tree(_root,0);
//	}
//}
//
//int SEMANTIC_M::parse_ret_tree(EXPRESSION_L* root,int index){
//	// PARSE TREE OF LEFT NODE TO RIGHT NODE
//	if (root->is_tree()) {
//		int code_op = root->get_code(), code_left, code_right;
//
//		if (code_op != (OPERATORS + SEPRATOR_OPERATORS + SEP_COMMA)) {
//			return parse_tree(root, "");
//		}
//		code_left = parse_ret_tree(root->get_childs(false),index);
//		__args_table.push(code_left);
//		code_right = parse_ret_tree(root->get_childs(true), index + 1);
//		if (code_right == NOT)
//			return NOT;
//		__args_table.push(code_right);
//		return NOT;
//	}
//
//	return root->get_code();
//}
//
//int SEMANTIC_M::parse_arr_tree(EXPRESSION_L* root, int arr_root, int index) {
//
//	// PARSE TREE OF LEFT NODE TO RIGHT NODE
//	if (root->is_tree()) {
//		int code_op = root->get_code(), code_left, code_right;
//
//		if (code_op != (OPERATORS + SEPRATOR_OPERATORS + SEP_COMMA)) {
//			return parse_tree(root, "");
//		}
//
//		code_left = parse_arr_tree(root->get_childs(false), arr_root, index);
//		parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), arr_root + __array_table.push(arr_root), code_left, "", false);
//		code_right = parse_arr_tree(root->get_childs(true), arr_root, index + 1);
//		if (code_right == NOT)
//			return NOT;
//		parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), arr_root + __array_table.push(arr_root), code_right, "", false);
//		return NOT;
//	}
//
//	return root->get_code();
//}
//
//int SEMANTIC_M::parse_loop_to_tree(EXPRESSION_L* root) {
//
//	// PARSE TREE OF LEFT NODE TO RIGHT NODE
//	if (root->is_tree()) {
//		int code_op = root->get_code();
//
//		if (code_op == (OPERATORS + SEPRATOR_OPERATORS + SEP_COLON)) {
//			int var_code = parse_loop_to_tree(root->get_childs(false));
//			int init_val_code = parse_tree(root->get_childs(true), "");
//			int init = parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), var_code, init_val_code, "", false);
//			__state_control_machine.loop_jump_control_exp();
//			return init;
//		}
//
//		if (code_op == (KEYWORDS + TO)) {
//			int var_code = parse_loop_to_tree(root->get_childs(false));
//			// should be add [ BY OP STEP ] conditons
//			int end = parse_loop_to_tree(root->get_childs(true));
//			int temp_exp = parse_three_address((OPERATORS + LOGICAL_OPERATORS + LOG_LT), var_code, end, "", false);
//			__state_control_machine.loop_jump_control(temp_exp);
//			return parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ADDASSI), var_code, end, "", false);
//		}
//	}
//	return root->get_code();
//}
//
//int SEMANTIC_M::parse_invoke_func_tree(EXPRESSION_L* root, bool is_root, int index) {
//
//	// PARSE TREE OF LEFT NODE TO RIGHT NODE
//	if (root->is_tree()) {
//		int code_op = root->get_code();
//
//		if (is_root)
//			__state_control_machine.rutin_jump_control(root->get_code());
//
//		if (is_root || code_op == (OPERATORS + SEPRATOR_OPERATORS + SEP_COMMA)) {
//			int left = parse_invoke_func_tree(root->get_childs(false), false, index);
//			parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), left, __args_table.get_id(index), "", false);
//			int right = parse_invoke_func_tree(root->get_childs(true), false, index + 1);
//			if (right == NOT)
//				return NOT;
//			parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), right, __args_table.get_id(index + 1), "", false);
//			__state_control_machine.rutin_args_control(index + 1);
//			return NOT;
//		}
//		else
//			return parse_tree(root, "");
//	}
//	return root->get_code();
//}
//
//int SEMANTIC_M::parse_call_func_tree(EXPRESSION_L* root, bool is_root, int index) {
//
//	// PARSE TREE OF LEFT NODE TO RIGHT NODE
//	if (root->is_tree()) {
//		int code_op = root->get_code();
//
//		if (is_root)
//			__state_control_machine.rutin_jump_control(root->get_code());
//
//		if (is_root || code_op == (OPERATORS + SEPRATOR_OPERATORS + SEP_COMMA)) {
//			int left = parse_call_func_tree(root->get_childs(false), false, index);
//			parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), left, __args_table.get_id(index), "", false);
//			int right = parse_call_func_tree(root->get_childs(true), false, index + 1);
//			if (right == NOT)
//				return NOT;
//			parse_three_address((OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI), right, __args_table.get_id(index + 1), "", false);
//			__state_control_machine.rutin_args_control(index + 1);
//			return NOT;
//		}
//		else
//			return parse_tree(root, "");
//	}
//	return root->get_code();
//}
//
//int SEMANTIC_M::parse_tree(EXPRESSION_L* root, str level) {
//	// PARSE TREE OF LEFT NODE TO RIGHT NODE
//	if (root->is_tree()) {
//		int code_op = root->get_code(),
//			code_left = parse_tree(root->get_childs(false), level + "L"),
//			code_right = parse_tree(root->get_childs(true), level + "R"),
//			result = 0;
//		bool is_one = false;
//
//
//
//		if (code_left == 0) {
//			code_left = code_right;
//			code_right = 0;
//			is_one = true;
//		}
//		else if (code_right == 0)
//			is_one = true;
//
//		// PARSE TREE IN THREE ADDRESS (OP,VAR_1 ,VAR_2)
//		return parse_three_address(code_op, code_left, code_right, level, is_one);
//	}
//
//	return root->get_code();
//}
//
//int SEMANTIC_M::parse_three_address(int op, int code_1, int code_2, str level, bool is_one_op) {
//	int addr_1 = (code_1 & DELIMITER_DOWNCODE), addr_2 = (code_2 & DELIMITER_DOWNCODE),
//		type_1 = (code_1 & DELIMITER_MIDCODE_RIGHT), type_2 = (code_2 & DELIMITER_MIDCODE_RIGHT);
//
//	void* val_1 = __objects_table.get_address(addr_1), * val_2 = __objects_table.get_address(addr_2);
//
//	if (!is_one_op && (type_2 == NOT || type_1 == OBJ || type_1 == FUNC)) {
//		__errors_handler.set_token("");
//		__errors_handler.rise_err(ERR_WRONGVAR);
//	}
//
//	// CASTING TYPE IF TYPES DIFFERENT AND OP != ASSIGNMENT
//	if (!is_one_op && type_1 != type_2 && (op != (OPERATORS + ASSIGNMENT_OPERATORS + ASSI_ASSI))) {
//
//		__bytecode_handler.write_bytecode_handler(INS_CTYP);
//		// BOOL TO NUM | STR TO BOOL | NUM TO STR
//		if ((type_1 == NUM && type_2 == BOOL)
//			|| (type_1 == BOOL && type_2 == STR)
//			|| (type_1 == NUM && type_2 == STR)) {
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(type_1);
//		}
//		else if ((type_1 == BOOL && type_2 == NUM)
//			|| (type_1 == STR && type_2 == BOOL)
//			|| (type_1 == STR && type_2 == NUM)) {
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(type_2);
//		}
//		else {
//			__errors_handler.set_token("");
//			__errors_handler.rise_err(ERR_WRONGVAR);
//		}
//		__bytecode_handler.write_bytecode_handler(INS_TMT);
//	}
//
//	int code_id;
//
//	if ((code_1 & DELIMITER_MIDCODE_LEFT) == TMP)
//		code_id = code_1 & DELIMITER_DOWNCODE;
//	else if ((code_2 & DELIMITER_MIDCODE_LEFT) == TMP)
//		code_id = code_2 & DELIMITER_DOWNCODE;
//	else
//		code_id = object_encoder_id("%" + level + "%");
//
//	int oplc = (op & DELIMITER_MIDCODE_LEFT), oprc = (op & DELIMITER_MIDCODE_RIGHT);
//
//	if (oplc == ASSIGNMENT_OPERATORS) {
//		if (oprc == ASSI_ASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			type_1 = type_2;
//			code_id = 0;
//		}
//		else if (oprc == ASSI_POWASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_POW);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_TMT);
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == ASSI_MULASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_MUL);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_TMT);
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == ASSI_DIVASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_DIV);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_TMT);
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == ASSI_MODASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_MOD);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_TMT);
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == ASSI_SUBASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_SUB);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_TMT);
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == ASSI_ADDASSI) {
//			__bytecode_handler.write_bytecode_handler(INS_ADD);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_TMT);
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == ASSI_ARR) {
//			__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//	}
//	else if (oplc == LOGICAL_OPERATORS) {
//		if (oprc == LOG_OR) {
//			__bytecode_handler.write_bytecode_handler(INS_OR);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_AND) {
//			__bytecode_handler.write_bytecode_handler(INS_AND);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_GT) {
//			__bytecode_handler.write_bytecode_handler(INS_GT);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_LT) {
//			__bytecode_handler.write_bytecode_handler(INS_LT);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_LTEQU) {
//			__bytecode_handler.write_bytecode_handler(INS_LE);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_GTEQU) {
//			__bytecode_handler.write_bytecode_handler(INS_GE);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_NOTEQU) {
//			__bytecode_handler.write_bytecode_handler(INS_EQ);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//			__bytecode_handler.write_bytecode_handler(INS_NOT);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//		}
//		else if (oprc == LOG_EQU) {
//			__bytecode_handler.write_bytecode_handler(INS_EQ);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == LOG_NOT) {
//			__bytecode_handler.write_bytecode_handler(INS_NOT);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//		}
//	}
//	else if (oplc == ARITHMETIC_OPERATORS) {
//		if (oprc == ARI_ADD) {
//			__bytecode_handler.write_bytecode_handler(INS_ADD);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == ARI_SUB) {
//			__bytecode_handler.write_bytecode_handler(INS_SUB);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == ARI_MOD) {
//			__bytecode_handler.write_bytecode_handler(INS_MOD);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == ARI_DIV) {
//			__bytecode_handler.write_bytecode_handler(INS_DIV);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == ARI_MUL) {
//			__bytecode_handler.write_bytecode_handler(INS_MUL);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//		else if (oprc == ARI_POW) {
//			__bytecode_handler.write_bytecode_handler(INS_POW);
//			__bytecode_handler.write_bytecode_handler((IDENTIFIER + TMP + type_1 + code_id));
//			__bytecode_handler.write_bytecode_handler(code_1);
//			__bytecode_handler.write_bytecode_handler(code_2);
//		}
//	}
//	else if (oplc == OTHER_OPERATORS) {
//		if (oprc == OTH_TYPE) {
//			__bytecode_handler.write_bytecode_handler(INS_WTP);
//			__bytecode_handler.write_bytecode_handler(code_1);
//			code_id = 0;
//		}
//	}
//
//	__bytecode_handler.write_bytecode_handler(INS_TMT);
//
//	return (IDENTIFIER + TMP + type_1 + code_id);
//}

void SEMANTIC_M::parse() {
	EXPRESSION_L* current_exp = _exp;
	while (current_exp != nullptr) {

		int mode = current_exp->get_mode();
		int id = current_exp->get_id();
		TOKEN_L* token = _tokens->is_exist(id);
		int code = token->get_self_code();

		if (mode == MODE_UNARY) {
			int code_next = token->go_next()->get_self_code();
			unray_parser(code, code_next);
			token->go_next()->set_code(STACK + (code_next & (DELIMITER_MIDCODE + DELIMITER_DOWNCODE)));
			token->remove();
		}
		else if (mode == MODE_BINARY) {
			int code_next = token->go_next()->get_self_code();
			int code_last = token->go_last()->get_self_code();
			binray_parser(code,code_next, code_last);
			token->go_last()->set_code(STACK + (code_next & (DELIMITER_MIDCODE + DELIMITER_DOWNCODE)));
			token->go_next()->remove();
			token->remove();
		}
		else if (mode == MODE_ARR) {
			int code_next = token->go_next()->get_self_code();
			arr_parser(code,code_next);
			token->go_next()->remove();
			token->set_code(STACK + (code_next & (DELIMITER_MIDCODE + DELIMITER_DOWNCODE)));
		}
		else if (mode == MODE_FUNC) {
			func_parser(code);
		}
		else if (mode == MODE_ARGS) {
			func_parser(code);
		}
		else if (mode == MODE_KEYWORD) {
			int code_next = token->go_next()->get_self_code();
			keyw_parser(code, code_next);
			token->go_next()->remove();
			token->remove();
		}

		current_exp = current_exp->go_next();
	}
}

void SEMANTIC_M::unray_parser(int op, int ident) {
	if ((ident & DELIMITER_UPCODE) != STACK) {
		__bytecode_handler.write_bytecode_handler(INS_PUSH);
		__bytecode_handler.write_bytecode_handler(ident & DELIMITER_DOWNCODE);
		__bytecode_handler.write_bytecode_handler(INS_TMT);
	}

	if((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == OPERATORS + LOGICAL_OPERATORS + LOG_NOT)
		__bytecode_handler.write_bytecode_handler(INS_NOT);
	else if ((op & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == OPERATORS + OTHER_OPERATORS + OTH_TYPE)
		__bytecode_handler.write_bytecode_handler(INS_CTYP);

	__bytecode_handler.write_bytecode_handler(INS_STK_1);
	__bytecode_handler.write_bytecode_handler(INS_TMT);
}

void SEMANTIC_M::binray_parser(int op, int ident_1, int ident_2) {
	if ((ident_1 & DELIMITER_UPCODE) != STACK) {
		__bytecode_handler.write_bytecode_handler(INS_PUSH);
		__bytecode_handler.write_bytecode_handler(ident_1 & DELIMITER_DOWNCODE);
		__bytecode_handler.write_bytecode_handler(INS_TMT);
	}
	if ((ident_2 & DELIMITER_UPCODE) != STACK) {
		__bytecode_handler.write_bytecode_handler(INS_PUSH);
		__bytecode_handler.write_bytecode_handler(ident_2 & DELIMITER_DOWNCODE);
		__bytecode_handler.write_bytecode_handler(INS_TMT);
	}

	if ((op & (DELIMITER_UPCODE)) == OPERATORS) {
		if ((op & (DELIMITER_MIDCODE_LEFT)) == ASSIGNMENT_OPERATORS) {
			if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_ASSI) {
				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);
			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_POWASSI) {
				__bytecode_handler.write_bytecode_handler(INS_POW);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_PUSH);
				__bytecode_handler.write_bytecode_handler(ident_1 & DELIMITER_DOWNCODE);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_MULASSI) {
				__bytecode_handler.write_bytecode_handler(INS_MUL);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_PUSH);
				__bytecode_handler.write_bytecode_handler(ident_1 & DELIMITER_DOWNCODE);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);
			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_DIVASSI) {
				__bytecode_handler.write_bytecode_handler(INS_DIV);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_PUSH);
				__bytecode_handler.write_bytecode_handler(ident_1 & DELIMITER_DOWNCODE);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);
			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_MODASSI) {
				__bytecode_handler.write_bytecode_handler(INS_MOD);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_PUSH);
				__bytecode_handler.write_bytecode_handler(ident_1 & DELIMITER_DOWNCODE);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);
			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_SUBASSI) {
				__bytecode_handler.write_bytecode_handler(INS_SUB);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_PUSH);
				__bytecode_handler.write_bytecode_handler(ident_1 & DELIMITER_DOWNCODE);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);
			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_ADDASSI) {
				__bytecode_handler.write_bytecode_handler(INS_ADD);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_PUSH);
				__bytecode_handler.write_bytecode_handler(ident_1& DELIMITER_DOWNCODE);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

				__bytecode_handler.write_bytecode_handler(INS_SET_VAR);
				__bytecode_handler.write_bytecode_handler(INS_STK_2);
				__bytecode_handler.write_bytecode_handler(INS_STK_1);
				__bytecode_handler.write_bytecode_handler(INS_TMT);

			}
			else if ((op & (DELIMITER_MIDCODE_RIGHT)) == ASSI_ARR) {

			}
			else if ((op & (DELIMITER_MIDCODE_LEFT)) == LOGICAL_OPERATORS) {
				if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_OR) {
					__bytecode_handler.write_bytecode_handler(INS_OR);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);
				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_AND) {
					__bytecode_handler.write_bytecode_handler(INS_AND);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);
				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_EQU) {
					__bytecode_handler.write_bytecode_handler(INS_EQ);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_GT) {
					__bytecode_handler.write_bytecode_handler(INS_GT);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_GTEQU) {
					__bytecode_handler.write_bytecode_handler(INS_GE);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_LT) {
					__bytecode_handler.write_bytecode_handler(INS_LT);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_LTEQU) {
					__bytecode_handler.write_bytecode_handler(INS_LE);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

				}
				else if ((op & (DELIMITER_MIDCODE_RIGHT)) == LOG_NOTEQU) {
					__bytecode_handler.write_bytecode_handler(INS_EQ);
					__bytecode_handler.write_bytecode_handler(INS_STK_2);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

					__bytecode_handler.write_bytecode_handler(INS_NOT);
					__bytecode_handler.write_bytecode_handler(INS_STK_1);
					__bytecode_handler.write_bytecode_handler(INS_TMT);

				}
			}

		}
	}
}

void SEMANTIC_M::arr_parser(int arr, int index){

}

void SEMANTIC_M::func_parser(int code){

}

void SEMANTIC_M::args_parser(int code) {

}

void SEMANTIC_M::keyw_parser(int code, int ident){

	if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == KEYWORDS + RUTIN) {
		__bytecode_handler.write_bytecode_handler(INS_INVOKE);
		__bytecode_handler.write_bytecode_handler(ident & DELIMITER_DOWNCODE);
		__bytecode_handler.write_bytecode_handler(INS_TMT);
	}
}

bool SEMANTIC_M::type_control(int code, int type_1, int type_2,bool is_unary) {

	//if (type_1 == NOT)
	//	__errors_handler.rise_err(ERR_TYPE);

	if (type_1 != type_2) {

	}

	/*if (type == NUM) {

	}
	else if(type == STR) {

	}
	else if(type == BOOL) {

	}*/

	return true;
}

// SEMANTIC MACHIN MEMBER FUNCTION
void SEMANTIC_M::run(EXPRESSION_L* exp, TOKEN_L* token) {
	_exp = exp;
	_tokens = token;
	//parser();
}

//void SEMANTIC_M::refresh() {
//
//}