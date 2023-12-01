//#include "semantic.h"
//
//void SEMANTIC_M::parse(VEC<TOKEN*>* tokens, VEC<EXPRESSION*>* exp) {
//
//	for (auto iter = exp->begin(); iter != exp->end(); iter++) {
//
//		int id = (*iter)->_id;
//		int mode = (*iter)->_mode;
//		auto item = tokens->find(id);
//
//		if (debug_mode) {
//			PRINT << mode << '\t' << std::hex << item->second << '\n';
//		}
//
//		if (_syntax_flag[0] && !_syntax_flag[1]) {
//			// jump label
//		}
//
//		if (mode == MODE_UNARY) {
//			auto  right = item;
//			++right;
//
//			if (debug_mode) {
//				PRINT << "Right" << '\t' << std::hex << right->second << '\n';
//			}
//		}
//		else if (mode == MODE_BINARY) {
//			auto left = item , right = item;
//			--left;
//			++right;
//
//			if (debug_mode) {
//				PRINT << "Left" << '\t' << std::hex << left->second << '\n';
//				PRINT << "Right" << '\t' << std::hex << right->second << '\n';
//			}
//
//			parse_binary(item->second, left->second, right->second);
//		}
//		else if (mode == MODE_ARR) {
//			auto  right = item;
//			++right;
//
//			if (debug_mode) {
//				PRINT << "Right" << '\t' << std::hex << right->second << '\n';
//			}
//
//			parse_arr(item->second, right->second);
//		}
//		else if (mode == MODE_KEYWORD) {
//			parse_keyword(item->second);
//		}
//
//		//else if (mode == MODE_FUNC) {
//		//	auto  right = item;
//		//	++right;
//
//		//	if (debug_mode) {
//		//		PRINT << "Right" << '\t' << std::hex << right->second << '\n';
//		//	}
//		//}
//		//else if (mode == MODE_ARGS) {
//
//		//}
//
//
//		if (!stack_mode)
//			stack_mode = true;
//	}
//}
//
//void SEMANTIC_M::parse_unary(int op_code,int right_code) {
//	if ((op_code & DEL_UPPER_CODE) == COMPONENTS_OPERATORS) {
//		if ((op_code & DEL_UPPER_MIDDLE_CODE) == OP_LOGICAL) {
//			if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_OPPOSITE) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(right_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_NOT);
//				__bytecode_handler.write_bytecode_handler(COMPONENTS_STACK);
//
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_NOT << ' ' << COMPONENTS_STACK << '\n';
//				}
//			}
//		}
//		else if ((op_code & DEL_UPPER_MIDDLE_CODE) == OP_OTHER) {
//			if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_OTR_TYPE) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(right_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_TYPE);
//				__bytecode_handler.write_bytecode_handler(COMPONENTS_STACK);
//
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_TYPE << ' ' << COMPONENTS_STACK << '\n';
//				}
//			}
//		}
//
//	}
//}
//
//void SEMANTIC_M::parse_binary(int op_code, int left_code, int right_code) {
//	if ((op_code & DEL_UPPER_CODE) == COMPONENTS_OPERATORS) {
//		if ((op_code & DEL_UPPER_MIDDLE_CODE) == OP_SEPRATOR) {
//			if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_SEP_COLON) {
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				iter_code = left_code;
//				if(debug_mode) PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << ' ' << right_code << '\n' ;
//			}
//		}
//		else if ((op_code & DEL_UPPER_MIDDLE_CODE) == OP_ARITHMETIC) {
//			if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ARI_POW) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_POW);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_POW << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ARI_DIV) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_DIV);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_DIV << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ARI_MUL) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MUL);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_MUL << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ARI_MOD) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MOD);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_MOD << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ARI_SUB) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SUB);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SUB << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ARI_ADD) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_ADD);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_ADD << ' ' << right_code << '\n';
//				}
//			}
//		}
//		else if ((op_code & DEL_UPPER_MIDDLE_CODE) == OP_LOGICAL) {
//			 if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_GREATER_THAN) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_GT);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_GT << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_LESS_THAN) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_LT);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_LT << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_GREATER_EQUAL) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_GE);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_GE << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_LESS_EQUAL) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_LE);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_LE << ' ' << COMPONENTS_STACK << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_EQUAL) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_EQ);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_EQ << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_NOT_EQUAL) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_EQ);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_NOT);
//				__bytecode_handler.write_bytecode_handler(COMPONENTS_STACK);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_EQ << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_NOT << ' ' << COMPONENTS_STACK << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_AND) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_AND);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_AND << ' ' << right_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_LOG_OR) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_OR);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_OR << ' ' << right_code << '\n';
//				}
//			}
//		}
//		else if ((op_code & DEL_UPPER_MIDDLE_CODE) == OP_ASSIGNMENT) {
//			if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_ASSIGNMENT) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(right_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if(!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code  << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_POWASSI) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_POW);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_POW << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_DIVASSI) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_DIV);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_DIV << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_MULASSI) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MUL);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_MUL << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_MODASSI) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MOD);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_MOD << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_SUBASSI) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SUB);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SUB << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_ADDASSI) {
//				if (!stack_mode) {
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//					__bytecode_handler.write_bytecode_handler(left_code);
//					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				}
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_ADD);
//				__bytecode_handler.write_bytecode_handler(right_code);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				__bytecode_handler.write_bytecode_handler(left_code);
//				if (debug_mode) {
//					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_ADD << ' ' << right_code << '\n';
//					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
//				}
//			}
//			else if ((op_code & DEL_LOWER_MIDDLE_CODE) == OP_ASN_ARRASSI) {
//				
//			}
//		}
//	}
//	else if ((op_code & DEL_UPPER_CODE) == COMPONENTS_KEYWORDS) {
//		if ((op_code & DEL_MIDCODE) == KYW_TO) {
//			// set label
//			int label = 0;
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_EQ);
//			__bytecode_handler.write_bytecode_handler(right_code);
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_JIF);
//			__bytecode_handler.write_bytecode_handler(label);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_EQ << ' ' << right_code << '\n' << "\t\t" << INSTRUCTION_JIF << ' ' << label << '\n';
//			loop_mode = true;
//		}
//		else if ((op_code & DEL_MIDCODE) == KYW_BY) {
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//			__bytecode_handler.write_bytecode_handler(iter_code);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << iter_code << '\n';
//		}
//	}
//
//	__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//}
//
//void SEMANTIC_M::parse_arr(int arr_code, int index_code) {
//	__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
//	__bytecode_handler.write_bytecode_handler(index_code);
//	__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//	__bytecode_handler.write_bytecode_handler(INSTRUCTION_GET_ARR);
//	__bytecode_handler.write_bytecode_handler(arr_code);
//	__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//	if (debug_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << index_code << '\n' << "\t\t" << INSTRUCTION_GET_ARR << ' ' << arr_code << '\n';
//}
//
//void SEMANTIC_M::parse_keyword(int kyw_code) {
//	if ((kyw_code & DEL_UPPER_CODE) == COMPONENTS_KEYWORDS) {
//		if ((kyw_code & DEL_MIDCODE) == KYW_LOOP) {
//
//			if (!loop_mode) {
//				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
//				/// 
//				if (debug_mode) PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << ' ' << ' ' << ' ' << '\n';
//			}
//			loop_mode = false;
//		}
//		else if ((kyw_code & DEL_MIDCODE) == KYW_IF) {
//			int label = 0;
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_JIF);
//			__bytecode_handler.write_bytecode_handler(label);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_JIF << ' ' << label << '\n';
//		}
//		else if ((kyw_code & DEL_MIDCODE) == KYW_ELF) {
//			int label = 0;
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_JIF);
//			__bytecode_handler.write_bytecode_handler(label);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_JIF << ' ' << label << '\n';
//		}
//		else if ((kyw_code & DEL_MIDCODE) == KYW_STOP) {
//			int label = 0;
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_JUMP);
//			__bytecode_handler.write_bytecode_handler(label);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_JUMP << ' ' << label << '\n';
//		}
//		else if ((kyw_code & DEL_MIDCODE) == KYW_NEXT) {
//			int label = 0;
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_JUMP);
//			__bytecode_handler.write_bytecode_handler(label);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_JUMP << ' ' << label << '\n';
//		}
//		else if ((kyw_code & DEL_MIDCODE) == KYW_OUTPUT) {
//			__bytecode_handler.write_bytecode_handler(INSTRUCTION_OUTPUT);
//			if (debug_mode) PRINT << "\t\t" << INSTRUCTION_OUTPUT << '\n';
//		}
//	}
//	__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
//}
//
////void SEMANTIC_M::parse_funcs() {
////
////}
////
////void SEMANTIC_M::parse_args() {
////
////}
//
//void SEMANTIC_M::run(VEC<TOKEN*>* tokens, VEC<EXPRESSION*>* exp) {
//	parse(tokens, exp);
//}