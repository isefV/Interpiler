#include"jump.h"

int _last_j_id = 0;

int JUMP_T::push(int line_pos) {
	JUMP_T* last = is_exist(_last_j_id);
	_last_j_id++;

	if (last != this || last->_label_id != 0) {
		JUMP_T* new_node = new JUMP_T;
		new_node->_label_id = _last_j_id;
		new_node->_line_pos = line_pos;
		last->_next = new_node;
		return new_node->_label_id;
	}
	last->_label_id = _last_j_id;
	last->_line_pos = line_pos;
	return last->_label_id;
}

JUMP_T* JUMP_T::is_exist(int id) {
	JUMP_T* current = this;
	while (current->_next != nullptr) {
		if (current->_label_id == id)
			return current;
		current = current->_next;
	}

	return current;
}

void JUMP_T::set_line_pos(int id,int line_pos) {
	JUMP_T* node = is_exist(id);
	node->_line_pos = line_pos;
}