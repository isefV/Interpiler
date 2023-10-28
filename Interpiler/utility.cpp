#include"utility.h"

unit _objects_size = 0, _tokens_size = 0;

// REQUIRED FUNCTIONS IMPLEMENTATION

char* utl_set_string(str string) {

	//CREATE NEW ADDRESS FOR STRING AND COPY IT
	unit length = string.length() + 1;
	char* nstring = (char*)malloc(sizeof(char) * length);
	memcpy(nstring, &string[0], length);
	return nstring;
}

void* utl_generate_address() {
	return (void*)malloc(sizeof(void*));
}

float utl_to_num(void* var, int type) {
	if (type == NUM)
		return *(float*)var;
	else if (type == BOOL)
		return (float)*(bool*)var;

	str temp = (*(str*)var);
	unit is_invalid = 0, len = temp.length();
	char cur_ch = temp.at(0);


	for (unit itr = 1; itr < len; itr++) {
		if (cur_ch == '.')
			is_invalid++;
		if (is_invalid > 1)
			rise_err(ERR_TYPE, _current_line, temp);
		cur_ch = temp.at(itr);
	}

	return atof(&temp[0]);
}

char* utl_to_str(void* var, int type) {
	if (type == STR)
		return *(char**)var;
	else if (type == BOOL)
		return &std::to_string(*(bool*)var)[0];
	return &std::to_string(*(float*)var)[0];
}

bool utl_to_bool(void* var, int type) {
	if (type == BOOL)
		return *(bool*)var;
	else if (type == NUM)
		return (bool)*(float*)var;
	return !(*(str*)var == "");
}

void utl_neutralization() {

	// AFTER EVERY EXCUTE LINE THIS VARIABLES SHOULD BE PURE FOR NEXT LINE
	_objects.purify_duplications();
	_tokens.purify();
	_exp.purify(&_exp, 0);
}


// REQUIRED CLASS IMPLEMENTATION
// OBJECT MEMBER FUNC

bool OBJECT::push(int id, int type, void* address, bool is_temp) {
	OBJECT* object = this;
	_objects_size++;

	if (object->_id == 0) {
		object->_id = id;
		object->_value = address;
		object->_type = type;
		return true;
	}


	while (object->_next != nullptr)
		object = object->_next;

	OBJECT* new_obj = new OBJECT;
	new_obj->_id = id;
	new_obj->_value = address;
	new_obj->_type = type;
	new_obj->_is_temp = is_temp;
	object->_next = new_obj;
	return true;
}

bool OBJECT::pop(int id) {
	OBJECT* object = this, * last = nullptr;
	_objects_size -= _objects_size - 1 > 0 ? 1 : 0;

	while (object->_next != nullptr && object->_id != id) {
		last = object;
		object = object->_next;
	}

	if (last != nullptr) {
		last->_next = object->_next;
		delete object;
		return true;
	}


	if (object->_next != nullptr) {
		OBJECT* next = object->_next;
		object->_id = next->_id;
		object->_next = next->_next;
		object->_is_temp = next->_is_temp;
		object->_value = next->_value;
		delete next;
		return true;
	}

	object->_id = 0;
	object->_next = nullptr;
	object->_is_temp = true;
	object->_value = nullptr;
	object->_type = NOT;
	return false;
}

void OBJECT::assign_val(int id, int type, void* address, bool is_temp) {
	this->pop(id);
	this->push(id, type, address, is_temp);
}

void OBJECT::purify_duplications() {
	OBJECT* object = this, * last = nullptr;

	while (object->_next != nullptr) {

		// IF OBJECTS HAS TEMP AND NOT BE ROOT NODE
		if (object->_is_temp && last) {
			OBJECT* current = object;
			last->_next = object->_next;
			object = object->_next;
			delete current;
			_objects_size -= _objects_size - 1 > 0 ? 1 : 0;
			continue;
		}

		// IF OBJECTS HAS TEMP AND BE ROOT NODE
		else if (object->_is_temp && !last) {
			OBJECT* next = object->_next;
			object->_id = next->_id;
			object->_value = next->_value;
			object->_type = next->_type;
			object->_is_temp = next->_is_temp;
			object->_next = next->_next;
			delete next;
			_objects_size -= _objects_size - 1 > 0 ? 1 : 0;
			continue;
		}
		last = object;
		object = object->_next;

	}
}

OBJECT* OBJECT::is_exist(int id) {
	OBJECT* object = this;
	while (object->_next != nullptr && object->_id != id)
		object = object->_next;

	if (object->_id != id)
		return nullptr;
	return object;
}

void* OBJECT::get_address(int id) {
	OBJECT* object = this->is_exist(id);

	if (object == nullptr)
		return nullptr;

	return object->_value;
}

int OBJECT::get_type(int id) {
	OBJECT* object = this->is_exist(id);

	if (object == nullptr)
		return NOT;

	return object->_type;
}

void OBJECT::display() {
	OBJECT* object = this;

	print << "Objects :" << '\n';
	while (object != nullptr) {
		print << std::hex << object->_id << '\t' << std::hex << object->_value << '\n';//<< object->_type << '\n';
		object = object->_next;
	}
}

// TOKEN MEMBER FUNC

bool TOKEN::push(int code) {
	TOKEN* object = this;
	_tokens_size++;

	if (object->_code == 0) {
		object->_code = code;
		return true;
	}

	while (object->_next != nullptr)
		object = object->_next;

	TOKEN* new_obj = new TOKEN;
	new_obj->_code = code;
	object->_next = new_obj;
	return true;
}

bool TOKEN::pop(int step) {
	TOKEN* object = this, * last = nullptr;
	int index = 0;
	_tokens_size -= _tokens_size - 1 > 0 ? 1 : 0;

	while (object->_next != nullptr && index < step) {
		last = object;
		object = object->_next;
	}

	if (last != nullptr) {
		last->_next = object->_next;
		delete object;
		return true;
	}

	if (object->_next != nullptr) {
		object->_code = object->_next->_code;
		object->_next = object->_next->_next;
		return true;
	}

	object->_code = 0;
	object->_next = nullptr;
	return false;
}

void TOKEN::purify() {
	TOKEN* object = this->_next;

	// SET ROOT NODE EMPTY
	this->_code = 0;
	this->_next = nullptr;

	_tokens_size = 0;

	// DELETE ALL NODE AFTER ROOT
	while (object != nullptr) {
		TOKEN* temp = object;
		object = object->_next;
		delete temp;
	}
}

int TOKEN::get_code(int step, char up_mid_down) {
	TOKEN* object = this;
	int index = 0;

	while (object->_next != nullptr && index < step)
		object = object->_next;

	if (up_mid_down == 'u')
		return (object->_code & DELIMITER_UPCODE);
	else if (up_mid_down == 'm')
		return (object->_code & DELIMITER_MIDCODE);
	else if (up_mid_down == 'd')
		return (object->_code & DELIMITER_DOWNCODE);

	return (object->_code);
}

int TOKEN::get_self_code(char up_mid_down) {
	if (up_mid_down == 'u')
		return (this->_code & DELIMITER_UPCODE);
	else if (up_mid_down == 'm')
		return (this->_code & DELIMITER_MIDCODE);
	else if (up_mid_down == 'd')
		return (this->_code & DELIMITER_DOWNCODE);

	return (this->_code);
}

TOKEN* TOKEN::go_next() {
	return this != nullptr ? this->_next : nullptr;
}

void TOKEN::display() {
	TOKEN* object = this;

	print << "Tokens :" << '\n';
	while (object != nullptr) {
		print << std::hex << object->_code << '\n';
		object = object->_next;
	}
}

// EXPRESSION MEMBER FUNC

bool EXPRESSION::push(int code) {
	EXPRESSION* _root = this;

	// IF SEEN ( INCREASE _PARAN LEVEL
	if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + SEPRATOR_OPERATORS + SEP_L_BRAC))
	{
		_paran++;
		return true;
	}
	// IF SEEN ) DECREASE _PARAN LEVEL
	else if ((code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) == (OPERATORS + SEPRATOR_OPERATORS + SEP_R_BRAC)) {
		_paran -= _paran - 1 < 0 ? 0 : 1;
		return true;
	}

	// THERE IS FIRST NODE ~ ROOT
	if (_root->_code == 0) {
		_root->_code = code;
		_root->_priority = _paran;
		return true;
	}

	// IF UPCODE HAS BEEN OPERATORS | KEYWORDS (THIS UPCODE HAS MOST PRIORITY)
	if ((code & DELIMITER_UPCODE) < LITERALS) {
		EXPRESSION* temp_last_root = new EXPRESSION;
		// _ROOT == NULLPTR MEANS REACH TO LEAF TREE
		while (_root != nullptr) {

			// IF  THE ROOT (UPCODE + MIDCODE) PRIORITY HAS LESS THAT NEW NODE (UPCODE + MIDCODE) PRIORITY 
			//			- NEW NODE < ROOT NODE -> ROOT GO LEFT , NEW NODE REPALCE ROOT NODE
			if ((((code & (DELIMITER_UPCODE | DELIMITER_MIDCODE)) < (_root->_code & (DELIMITER_UPCODE | DELIMITER_MIDCODE)))
				&& (_root->_priority == _paran)
				&& ((_root->_code & (DELIMITER_UPCODE + DELIMITER_MIDCODE)) != (IDENTIFIER + FUNC)))
				|| (_root->_priority - 1 == _paran)) {

				EXPRESSION* _node = new EXPRESSION;
				_node->_code = _root->_code;
				_node->_priority = _root->_priority;
				_node->_is_tree = _root->_is_tree;
				_node->_left = _root->_left;
				_node->_right = _root->_right;

				_root->_left = _node;
				_root->_right = nullptr;
				_root->_code = code;
				_root->_priority = _paran;
				_root->_is_tree = true;
				return true;
			}

			// ELSE THE ROOT (UPCODE + MIDCODE) PRIORITY HAS MORE THAT NEW NODE (UPCODE + MIDCODE) PRIORITY (NEW NODE GO TO RIGHT SIDE OF THE ROOT)
			temp_last_root = _root;
			_root = _root->_right;
		}

		EXPRESSION* _node = new EXPRESSION;
		_node->_code = code;
		_node->_priority = _paran;

		temp_last_root->_right = _node;
	}
	// IF UPCODE HAS BEEN IDENTIFIER | LITERALS (THIS UPCODE HAS LESS PRIORITY)
	else {
		EXPRESSION* _node = new EXPRESSION;
		_node->_code = code;
		_node->_priority = _paran;

		while (_root != nullptr) {

			// IF _ROOT HAS LEFT NODE EMPTY
			if (_root->_left == nullptr) {
				_root->_left = _node;
				_root->_is_tree = true;
				return true;
			}
			// IF _ROOT HAS RIGHT NODE EMPTY
			else if (_root->_right == nullptr) {
				_root->_right = _node;
				_root->_is_tree = true;
				return true;
			}

			// GO DEEP TREE FOR FIND PALCE
			_root = _root->_right;
		}
	}
	return false;
}

int EXPRESSION::get_code() {
	return this != nullptr ? this->_code : 0;
}

bool EXPRESSION::is_tree() {
	return this != nullptr ? this->_is_tree : false;
}

void EXPRESSION::purify(EXPRESSION* root, int level) {

	// IF ROOT HAS NULLPTR REACH TO LEAF NODES
	if (root == nullptr)
		return;

	// RECURSIVE GO TO LEAF NODES
	root->purify(root->_left, level + 1);
	root->purify(root->_right, level + 1);

	// IF NOT ROOT DELETE NODE
	if (level != 0) {
		delete root;
		return;
	}

	// SET ROOT NODE TO BE EMPTY
	root->_left = nullptr;
	root->_right = nullptr;
	root->_is_tree = false;
	root->_priority = 0;
	root->_code = 0;
}

EXPRESSION* EXPRESSION::get_childs(bool is_right) {
	if (this == nullptr)
		return nullptr;
	if (is_right)
		return this->_right;
	return this->_left;
}

EXPRESSION* EXPRESSION::copy() {

	// CREATE NEW NODE FOR COPY DATA OF CURRENT NODE
	EXPRESSION* root = this, * _new_root = new EXPRESSION,
		* left = root->get_childs(false), * right = root->get_childs(true);

	_new_root->_code = root->_code;
	_new_root->_is_tree = root->_is_tree;
	_new_root->_priority = root->_priority;

	// RECURSIVE COPY TREE CHILD
	_new_root->_left = left->copy();
	_new_root->_right = right->copy();

	return _new_root;
}

// KEYWORD

bool KEYWORD::is_loop() {
	return (_keyword_code & (DELIMITER_UPCODE & DELIMITER_MIDCODE)) == (KEYWORDS + LOOP);
}

void KEYWORD::reset() {
	_keyword_code = 0;
}

// @Debug: test func
void display_tree(EXPRESSION* root, int level) {

	print << level << '\t' << std::hex << root->get_code() << '\t' << root->is_tree() << '\n';
	if (!root->is_tree())
		return;
	level++;
	print << "L\t";
	display_tree(root->get_childs(false), level);	// left
	print << "R\t";
	display_tree(root->get_childs(true), level);		// right
}