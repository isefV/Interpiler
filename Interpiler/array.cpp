#include"array.h"

// ARRAY_T MEMBER FUNC

int ARRAY_T::push(int parent_id) {
	ARRAY_T* current = this->is_exist(parent_id);
	if (current == nullptr) {
		current = this;

		if (current->_id == 0) {
			current->_id = parent_id;
			return _end_index;
		}

		while (current->_next != nullptr ) {
			current = current->_next;
		}

		ARRAY_T* new_node = new ARRAY_T;
		new_node->_id = parent_id;
		current->_next = new_node;
		return _end_index;
	}
	
	current->_end_index++;
	__objects_table.push(parent_id + current->_end_index, NOT, utl_generate_address(), false);
	return _end_index;
}

ARRAY_T* ARRAY_T::is_exist(int parent_id) {
	ARRAY_T* current = this;

	while (current != nullptr) {
		if (parent_id == current->_id)
			return current;
		current = current->_next;
	}
	return nullptr;
}