#include"expression.h"

//int _paran = 0;
//
//// EXPRESSION_L MEMBER FUNC
//bool EXPRESSION_L::push(int code) {
//	EXPRESSION_L* _root = this;
//
//	// IF SEEN ( INCREASE _PARAN LEVEL
//	if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC)){
//		_paran++;
//		return true;
//	}
//	// IF SEEN ) DECREASE _PARAN LEVEL
//	else if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC)) {
//		_paran -= _paran - 1 < 0 ? 0 : 1;
//		return true;
//	}
//
//	// THERE IS FIRST NODE ~ ROOT
//	if (_root->_code == 0) {
//		_root->_code = code;
//		_root->_priority = _paran;
//		return true;
//	}
//
//	// IF UPCODE HAS BEEN OPERATORS | KEYWORDS (THIS UPCODE HAS MOST PRIORITY)
//	// THAT MEANS OPERATORS | KEYWORDS GO TO ROOT
//	if ((code & DELIMITER_UPCODE) < LITERALS) {
//		EXPRESSION_L* temp_last = new EXPRESSION_L;
//
//		// _ROOT == NULLPTR MEANS REACH TO LEAF TREE
//		while (_root != nullptr) {
//
//			// IF  THE ROOT (UPCODE + MIDCODE) PRIORITY HAS 
//			// LESS THAT NEW NODE (UPCODE + MIDCODE) PRIORITY 
//			// 
//			//			- NEW NODE < ROOT NODE -> ROOT GO LEFT , 
//			//				NEW NODE REPALCE ROOT NODE
//			//
//			//			- ROOT -> PRIORITY - 1 => THIS EXP HAS MOST PRIORITY THAT ROOT
//			//				LIKE : * -> 245XXXXX , + -> 241XXXXX => 245XXXXX > 241XXXXX
//			//						BUT 241XXXXX HAVE PRIORITY SO 245XXXXX -R-> 241XXXXX
//			if ((((code & (DELIMITER_UPCODE | DELIMITER_MIDCODE)) < (_root->_code & (DELIMITER_UPCODE | DELIMITER_MIDCODE)))
//				&& (_root->_priority == _paran)
//				&& ((_root->_code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) != (IDENTIFIER + FUNC)))
//				|| (_root->_priority - 1 == _paran)) {
//
//				EXPRESSION_L* _node = new EXPRESSION_L;
//				_node->_code = _root->_code;
//				_node->_priority = _root->_priority;
//				_node->_is_tree = _root->_is_tree;
//				_node->_left = _root->_left;
//				_node->_right = _root->_right;
//
//				_root->_left = _node;
//				_root->_right = nullptr;
//				_root->_code = code;
//				_root->_priority = _paran;
//				_root->_is_tree = true;
//				return true;
//			}
//
//			temp_last = _root;
//			_root = _root ->_right;
//		}
//		// ELSE THE ROOT (UPCODE + MIDCODE) PRIORITY HAS MORE
//		//  THAT NEW NODE (UPCODE + MIDCODE) PRIORITY 
//		//	(NEW NODE GO TO RIGHT SIDE OF THE ROOT)
//
//		EXPRESSION_L* _node = new EXPRESSION_L;
//		_node->_code = code;
//		_node->_priority = _paran;
//
//		temp_last->_right = _node;
//	}
//	// IF UPCODE HAS BEEN IDENTIFIER | LITERALS (THIS UPCODE HAS LESS PRIORITY)
//	// THAT MEANS IDENTIFIER | LITERALS GO TO LEAF
//	else {
//		EXPRESSION_L* _node = new EXPRESSION_L;
//		_node->_code = code;
//		_node->_priority = _paran;
//
//		while (_root != nullptr) {
//
//			// IF _ROOT HAS LEFT NODE EMPTY
//			if (_root->_left == nullptr) {
//				_root->_left = _node;
//				_root->_is_tree = true;
//				return true;
//			}
//			// IF _ROOT HAS RIGHT NODE EMPTY
//			else if (_root->_right == nullptr) {
//				_root->_right = _node;
//				_root->_is_tree = true;
//				return true;
//			}
//
//			// GO DEEP TREE FOR FIND PALCE
//			_root = _root->_right;
//		}
//	}
//	return false;
//}
//
//int EXPRESSION_L::get_code() {
//	return this != nullptr ? this->_code : 0;
//}
//
//bool EXPRESSION_L::is_tree() {
//	return this != nullptr ? this->_is_tree : false;
//}
//
//void EXPRESSION_L::purify(EXPRESSION_L* root, int level) {
//
//	// IF ROOT HAS NULLPTR REACH TO LEAF NODES
//	if (root == nullptr)
//		return;
//
//	// RECURSIVE GO TO LEAF NODES
//	root->purify(root->_left, level + 1);
//	root->purify(root->_right, level + 1);
//
//	// IF NOT ROOT DELETE NODE
//	if (level != 0) {
//		delete root;
//		return;
//	}
//
//	// SET ROOT NODE TO BE EMPTY
//	root->_left = nullptr;
//	root->_right = nullptr;
//	root->_is_tree = false;
//	root->_priority = 0;
//	root->_code = 0;
//}
//
//EXPRESSION_L* EXPRESSION_L::get_childs(bool is_right) {
//	if (this == nullptr)
//		return nullptr;
//	if (is_right)
//		return this->_right;
//	return this->_left;
//}
//
//EXPRESSION_L* EXPRESSION_L::copy() {
//
//	// CREATE NEW NODE FOR COPY DATA OF CURRENT NODE
//	EXPRESSION_L* root = this, * _new_root = new EXPRESSION_L,
//		* left = root->get_childs(false), * right = root->get_childs(true);
//
//	if (root == nullptr)
//		return nullptr;
//
//	_new_root->_code = root->_code;
//	_new_root->_is_tree = root->_is_tree;
//	_new_root->_priority = root->_priority;
//
//	// RECURSIVE COPY TREE CHILD
//	_new_root->_left = left->copy();
//	_new_root->_right = right->copy();
//
//	return _new_root;
//}

EXPRESSION_L* _last_exp_node;
int _paran = 0 , _brac = 0;
bool is_rutin = false,is_args = false;

void EXPRESSION_L::push(int code,int id) {

	int priority = parse_priority(code);

	if (priority == PRIO_NO)
		return;

	int mode = parse_mode(code);
	priority += _paran + _brac;

	if (this->_id == PRIO_NO) {
		this->_id = id;
		this->_mode = mode;
		this->_priority = priority;
		_last_exp_node = this;
		return;
	}

	EXPRESSION_L* node = new EXPRESSION_L;
	node->_id = id;
	node->_mode = mode;
	node->_priority = priority;

	if (_last_exp_node->_priority > node->_priority) {
		_last_exp_node->_next = node;
		node->_last = _last_exp_node;
		_last_exp_node = node;
		return;
	}

	EXPRESSION_L* temp = new EXPRESSION_L;
	temp = _last_exp_node->_last == nullptr ? _last_exp_node : _last_exp_node->_last;

	while (temp->_last != nullptr && temp->_priority < node->_priority)
		temp = temp->_last;

	if (temp->_priority > node->_priority) {

		node->_next = temp->_next;
		node->_last = temp;
		if (node->_next != nullptr)
			node->_next->_last = node;
		temp->_next = node;
		return;
	}

	node->_next = temp->_next;
	node->_last = temp;
	node->_id = temp->_id;
	node->_mode = temp->_mode;
	node->_priority = temp->_priority;
	temp->_next = node;
	if (node->_next != nullptr)
		node->_next->_last = node;
	temp->_last = nullptr;
	temp->_id = id;
	temp->_mode = mode;
	temp->_priority = priority;

	if (temp == _last_exp_node)
		_last_exp_node = node;

}

int EXPRESSION_L::parse_priority(int code) {

	if ((code & DELIMITER_UPCODE) == LITERALS)
		return PRIO_NO;

	if ((code & DELIMITER_UPCODE) == KEYWORDS) {
		if ((code & DELIMITER_MIDCODE) == TO) {
			return PRIO_13;
		}
		else if ((code & DELIMITER_MIDCODE) == BY){
			return PRIO_12;
		}
		else if ((code & DELIMITER_MIDCODE) == RUTIN) {
			is_rutin = true;
			return PRIO_MOST + PRIO_MOST;
		}
		return PRIO_LEAST;
	}
	else if ((code & DELIMITER_UPCODE) == OPERATORS) {
		if ((code & DELIMITER_MIDCODE_LEFT) == SEPRATOR_OPERATORS) {
			if ((code & DELIMITER_MIDCODE_RIGHT) == SEP_L_BRAC) {
				inc_bp(_paran);
				if (is_rutin)
					is_args = true;
				return PRIO_NO;
			}
			else if ((code & DELIMITER_MIDCODE_RIGHT) == SEP_R_BRAC) {
				invalid_bp(_paran);
				dec_bp(_paran);
				if (is_rutin)
					is_args = false;
				return PRIO_NO;
			}
			else if ((code & DELIMITER_MIDCODE_RIGHT) == SEP_COMMA) {
				if (is_rutin)
					return PRIO_NO;
				return PRIO_1;
			}
			else if ((code & DELIMITER_MIDCODE_RIGHT) == SEP_COLON) {
				if (is_rutin)
					is_rutin = false;
				return PRIO_14;
			}
		}
		else if ((code & DELIMITER_MIDCODE_LEFT) == ARITHMETIC_OPERATORS) {
			if ((code & DELIMITER_MIDCODE_RIGHT) == ARI_POW)
				return PRIO_10;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == ARI_DIV)
					|| ((code & DELIMITER_MIDCODE_RIGHT) == ARI_MUL))
				return PRIO_9;
			else if ((code & DELIMITER_MIDCODE_RIGHT) == ARI_MOD)
				return PRIO_8;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == ARI_SUB)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == ARI_ADD))
				return PRIO_7;
		}
		else if ((code & DELIMITER_MIDCODE_LEFT) == LOGICAL_OPERATORS) {
			if ((code & DELIMITER_MIDCODE_RIGHT) == LOG_NOT)
				return PRIO_11;
			else if (((code & DELIMITER_MIDCODE_RIGHT) == LOG_GT)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == LOG_LT)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == LOG_GTEQU)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == LOG_LTEQU)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == LOG_NOTEQU)
				|| ((code & DELIMITER_MIDCODE_RIGHT) == LOG_EQU))
				return PRIO_6;
			else if ((code & DELIMITER_MIDCODE_RIGHT) == LOG_AND)
				return PRIO_5;
			else if ((code & DELIMITER_MIDCODE_RIGHT) == LOG_OR)
				return PRIO_4;
		}
		else if ((code & DELIMITER_MIDCODE_LEFT) == OTHER_OPERATORS) {
			if ((code & DELIMITER_MIDCODE_RIGHT) == OTH_L_REF) {
				inc_bp(_brac);
				return PRIO_NO;
			}
			else if ((code & DELIMITER_MIDCODE_RIGHT) == OTH_R_REF) {
				invalid_bp(_brac);
				dec_bp(_brac);
				return PRIO_NO;
			}
			return PRIO_11;
		}
		else if ((code & DELIMITER_MIDCODE_LEFT) == ASSIGNMENT_OPERATORS) {
			if ((code & DELIMITER_MIDCODE_RIGHT) == ASSI_ARR)
				return PRIO_3;
			return PRIO_2;
		}
	}
	else if ((code & DELIMITER_UPCODE) == IDENTIFIER) {
		if (((code & DELIMITER_MIDCODE_LEFT) == ARR)
			|| (!is_rutin && ((code & DELIMITER_MIDCODE_RIGHT) == FUNC))) {
			return PRIO_15;
		}
		else if (is_args && is_rutin)
			return PRIO_15;
	}
	
	return PRIO_NO;
}

int EXPRESSION_L::parse_mode(int code) {

	if ((code & DELIMITER_UPCODE) == KEYWORDS){
		if((code & DELIMITER_MIDCODE) == TO) {
			return MODE_BINARY;
		}
		else if ((code & DELIMITER_MIDCODE) == BY) {
			return MODE_BINARY;
		}
		return MODE_KEYWORD;
	}

	if ((code & DELIMITER_UPCODE) == IDENTIFIER) {
		if ((code & DELIMITER_MIDCODE_LEFT) == ARR)
			return MODE_ARR;
		else if ((code & DELIMITER_MIDCODE_RIGHT) == FUNC)
			return MODE_FUNC;
		return MODE_ARGS;
	}
	else if (((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + LOGICAL_OPERATORS + LOG_NOT))
		|| ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + OTHER_OPERATORS + OTH_TYPE)))
		return MODE_UNARY;
	return MODE_BINARY;
}

int EXPRESSION_L::get_id(){
	return this->_id;
}

int EXPRESSION_L::get_mode() {
	return this->_mode;
}

void EXPRESSION_L::purify() {
	EXPRESSION_L* current = this->_next;

	this->_priority = PRIO_NO;
	this->_id = -1;
	this->_next = nullptr;
	this->_last = nullptr;

	while (current != nullptr) {
		EXPRESSION_L* temp = current;
		current = current->_next;
		delete temp;
	}
}

void EXPRESSION_L::display() {
	EXPRESSION_L* current = this;

	print << "ID\tPriority\tMode\n";
	while (current != nullptr) {
		print << current->_id << '\t' << current->_priority << "\t\t" << current->_mode << '\n';
		current = current->_next;
	}
}

EXPRESSION_L* EXPRESSION_L::go_next() {
	return this->_next;
}