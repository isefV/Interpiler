#include"token.h"

int _token_size = 0;
TOKEN_L* _last_token_node, *_first_token_node;

// TOKEN_L MEMBER FUNC
int TOKEN_L::get_size() {
	return _token_size;
}

void TOKEN_L::push(int code) {
	inc_tk(_token_size);

	if (this->_code == 0) {
		this->_code = code;
		this->_id = _token_size;
		_last_token_node = this;
		_first_token_node = this;
		return;
	}


	TOKEN_L* token = new TOKEN_L;
	token->_code = code;
	token->_id = _token_size;
	_last_token_node->_next = token;
	token->_last = _last_token_node;
	_last_token_node = token;
}

void TOKEN_L::set_code(int code) {
	if (this != nullptr)
		this->_code = code;
}

void TOKEN_L::pop(int id) {
	TOKEN_L* token = is_exist(id);

	if (token == nullptr)
		return;

	dec_tk(_token_size);

	if (token == _first_token_node) {

		this->_code = 0;
		this->_id = NO_ID;
		this->_last = nullptr;
		_last_token_node = this;
		return;
	}

	if (_last_token_node == token) {
		_last_token_node = token->_last;
		_last_token_node->_next = nullptr;
	}

	token->_last = token->_next;
	delete token;
}

void TOKEN_L::purify() {
	int size = _token_size;

	for (int index = 0; index < size; index++)
		pop(index);
	return;

}

TOKEN_L* TOKEN_L::is_exist(int id){
	TOKEN_L* token = _first_token_node;

	while (token->_next != nullptr && token->_id != id)
		token = token->_next;

	if (token->_id != id)
		return nullptr;

	return token;
}

TOKEN_L* TOKEN_L::remove(){
	if (_first_token_node == this) {
		TOKEN_L* next = this->_next;
		if(next != nullptr){
			this->_code = next->_code;
			this->_id = next->_id;
			this->_next = next->_next;
			if (next->_next != nullptr)
				next->_next->_last = this;
			this->_last = nullptr;
			_first_token_node = this;
			delete next;
			return this;
		}
		this->_code = 0;
		this->_id = -1;
		this->_next = nullptr;
		_last_token_node = this;
		return nullptr;
	}

	if (_last_token_node == this ) {
		TOKEN_L* token = this;
		_last_token_node = token->_last;
		_last_token_node->_next = nullptr;
		delete token;
		return nullptr;
	}

	TOKEN_L* token = this,*next = this->_next;

	token->_next->_last = this->_last;
	token->_last->_next = token->_next;
	delete token;

	return next;
}

int TOKEN_L::get_code(int id, char up_mid_down) {
	TOKEN_L* token = is_exist(id);;

	if (token == nullptr)
		return NOT;

	if (up_mid_down == 'u')
		return (token->_code & DELIMITER_UPCODE);
	else if (up_mid_down == 'm')
		return (token->_code & DELIMITER_MIDCODE);
	else if (up_mid_down == 'd')
		return (token->_code & DELIMITER_DOWNCODE);

	return (token->_code);
}

int TOKEN_L::get_self_code() {
	return this == nullptr ? 0 : this->_code;
}

int TOKEN_L::get_id() {
	return this->_id;
}

TOKEN_L* TOKEN_L::go_next() {
	return this != nullptr ? this->_next : nullptr;
}

TOKEN_L* TOKEN_L::go_last() {
	return this != nullptr ? this->_last : nullptr;
}

void TOKEN_L::display() {
	TOKEN_L* token = _first_token_node;

	print << "\nTokens\t\tID\n";
	print << "--------\t-----\n";
	while (token != nullptr) {
		print << std::hex << token->_code << '\t' << token->_id << '\n';
		token = token->_next;
	}
}
