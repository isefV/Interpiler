#include"function.h"

// FUNCTION MEMBER FUNC

int FUNCTION_T::push(int func_id,int invoke_line) {
	FUNCTION_T* current = this->is_exist(func_id);

	if (current == nullptr) {
		current = this;

		if (current->_id == 0) {
			this->_id = func_id;
			this->_invoke_line = invoke_line;
			return this->_id;
		}

		while (current->_next != nullptr) {
			current = current->_next;
		}

		FUNCTION_T* new_node = new FUNCTION_T;
		new_node->_id = func_id;
		current->_invoke_line = invoke_line;
		current->_next = new_node;
		return new_node->_id;
	}

	return current->_id;
}

FUNCTION_T* FUNCTION_T::is_exist(int func_id) {
	FUNCTION_T* current = this;

	while (current != nullptr) {
		if (func_id == current->_id)
			return current;
		current = current->_next;
	}
	return nullptr;
}

void FUNCTION_T::set_args_count(int func_id,int args_count) {
	FUNCTION_T* current = this->is_exist(func_id);

	if (current == nullptr) {
		return;
	}

	current->_args_count = args_count;
}

void FUNCTION_T::call(int func_id,int call_line) {
	FUNCTION_T* current = this->is_exist(func_id);

	if (current == nullptr)
		return;

	current->_call_line.push(call_line);
}

int FUNCTION_T::ret(int func_id) {
	FUNCTION_T* current = this->is_exist(func_id);

	if (current == nullptr)
		return -1;


	int line = current->_call_line.top();
	current->_call_line.pop();
	return line;
}