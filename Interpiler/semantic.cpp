#include "semantic.h"

void SEMANTIC_M::parse(MAP<int, int>* tokens, VEC<EXPRESSION*>* exp) {
	for (auto iter = exp->begin(); iter != exp->end(); iter++) {

		int id = (*iter)->_id;
		int mode = (*iter)->_mode;
		auto item = tokens->find(id);

		PRINT << mode << '\t' << std::hex << item->second << '\n';

		if (mode == MODE_UNARY) {
			auto  right = item;

			PRINT << "Right" << '\t' << std::hex << (++right)->second << '\n';
		}
		else if (mode == MODE_BINARY) {
			auto left = item , right = item;

			PRINT << "Left" << '\t' << std::hex << (--left)->second << '\n';
			PRINT << "Right" << '\t' << std::hex << (++right)->second << '\n';

			parse_binary(item->second, left->second, right->second);
		}
		else if (mode == MODE_ARR) {
			auto  right = item;

			PRINT <<  "Right" << '\t' << std::hex << (++right)->second << '\n';
		}
		else if (mode == MODE_FUNC) {
			auto  right = item;

			PRINT <<  "Right" << '\t' << std::hex << (++right)->second << '\n';
		}
		else if (mode == MODE_ARGS) {

		}
		else if (mode == MODE_KEYWORD) {

		}

		if (!stack_mode)
			stack_mode = true;
	}
}

void SEMANTIC_M::parse_binary(int op_code, int left_code, int right_code) {
	if ((op_code & UPCODE) == COMPONENTS_OPERATORS) {
		if ((op_code & MIDCODE_LEFT) == OP_SEPRATOR) {
			if ((op_code & MIDCODE_RIGHT) == OP_SEP_COLON) {
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				__bytecode_handler.write_bytecode_handler(right_code);
				if(debug_mode) PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << ' ' << right_code << '\n' ;
			}
		}
		else if ((op_code & MIDCODE_LEFT) == OP_ARITHMETIC) {
			if ((op_code & MIDCODE_RIGHT) == OP_ARI_POW) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_POW);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_POW << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ARI_DIV) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_DIV);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_DIV << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ARI_MUL) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MUL);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_MUL << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ARI_MOD) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MOD);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_MOD << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ARI_SUB) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SUB);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SUB << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ARI_ADD) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_ADD);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_ADD << ' ' << right_code << '\n';
				}
			}
		}
		else if ((op_code & MIDCODE_LEFT) == OP_LOGICAL) {
			if ((op_code & MIDCODE_RIGHT) == OP_LOG_OPPOSITE) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(right_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_NOT);
				__bytecode_handler.write_bytecode_handler(COMPONENTS_STACK);

				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_NOT << ' ' << COMPONENTS_STACK << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_GREATER_THAN) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_GT);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_GT << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_LESS_THAN) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_LT);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_LT << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_GREATER_EQUAL) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_GE);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_GE << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_LESS_EQUAL) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_LE);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_LE << ' ' << COMPONENTS_STACK << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_EQUAL) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_EQ);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_EQ << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_NOT_EQUAL) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_EQ);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_NOT);
				__bytecode_handler.write_bytecode_handler(COMPONENTS_STACK);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_EQ << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_NOT << ' ' << COMPONENTS_STACK << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_AND) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_AND);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_AND << ' ' << right_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_LOG_OR) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_OR);
				__bytecode_handler.write_bytecode_handler(right_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << left_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_OR << ' ' << right_code << '\n';
				}
			}
		}
		else if ((op_code & MIDCODE_LEFT) == OP_OTHER) {
			if ((op_code & MIDCODE_RIGHT) == OP_OTR_TYPE) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(right_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_TYPE);
				__bytecode_handler.write_bytecode_handler(COMPONENTS_STACK);
				
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_TYPE << ' ' << COMPONENTS_STACK << '\n';
				}
			}
		}
		else if ((op_code & MIDCODE_LEFT) == OP_ASSIGNMENT) {
			if ((op_code & MIDCODE_RIGHT) == OP_ASN_ASSIGNMENT) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(right_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if(!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code  << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_POWASSI) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_POW);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_POW << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_DIVASSI) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_DIV);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_DIV << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_MULASSI) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MUL);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_MUL << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_MODASSI) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_MOD);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_MOD << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_SUBASSI) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SUB);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SUB << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_ADDASSI) {
				if (!stack_mode) {
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_PUSH);
					__bytecode_handler.write_bytecode_handler(left_code);
					__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				}
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_ADD);
				__bytecode_handler.write_bytecode_handler(right_code);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
				__bytecode_handler.write_bytecode_handler(INSTRUCTION_SET_VAR);
				__bytecode_handler.write_bytecode_handler(left_code);
				if (debug_mode) {
					if (!stack_mode) PRINT << "\t\t" << INSTRUCTION_PUSH << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_ADD << ' ' << right_code << '\n';
					PRINT << "\t\t" << INSTRUCTION_SET_VAR << ' ' << left_code << '\n';
				}
			}
			else if ((op_code & MIDCODE_RIGHT) == OP_ASN_ARRASSI) {
				
			}
		}
	}

	__bytecode_handler.write_bytecode_handler(INSTRUCTION_END);
}


void SEMANTIC_M::run(MAP<int, int>* tokens, VEC<EXPRESSION*>* exp) {
	parse(tokens, exp);
}