#include"arguments.h"

// ARGUMENTS MEMBER FUNC


int ARGUMENT_T::push(int arg_id) {
	ARGUMENT_T* current = this;

	if (current->_index == -1) {
		current->_id = arg_id;
		current->_index++;
		return arg_id;
	}

	while (current->_next != nullptr) {
		current = current->_next;
	}

	ARGUMENT_T* new_node = new ARGUMENT_T;
	new_node->_id = arg_id;
	new_node->_index = current->_index + 1;
	current->_next = new_node;
	return new_node->_index;
}

int ARGUMENT_T::get_id(int arg_index) {
	ARGUMENT_T* current = this->is_exist(arg_index);

	if (current == nullptr)
		return 0;
	
	return current->_id;
}

ARGUMENT_T* ARGUMENT_T::is_exist(int arg_index) {
	ARGUMENT_T* current = this;
	while (current != nullptr) {
		if (arg_index == current->_index)
			return current;
		current = current->_next;
	}
	return nullptr;
	
}

void ARGUMENT_T::purify() {
	ARGUMENT_T* current = this->_next;

	while (current != nullptr && current->_next != nullptr) {
		ARGUMENT_T* temp = current;
		current = current->_next;
		delete temp;
	}

	this->_id = 0;
	this->_index = -1;
	this->_next = nullptr;
}