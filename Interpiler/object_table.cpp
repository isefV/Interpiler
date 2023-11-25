#include"object_table.h"

int _object_size = 0;

// REQUIRED CLASS IMPLEMENTATION
// OBJECT_T MEMBER FUNC
void OBJECT_T::inc_size() {
	_object_size++;
}

void OBJECT_T::dec_size() {
	_object_size -= _object_size - 1 >= 0 ? 1 : 0;
}

int OBJECT_T::get_size() {
	return _object_size;
}

bool OBJECT_T::push(int id, int type, void* address, bool is_temp) {
	OBJECT_T* object = this;
	inc_size();

	if (object->_id == 0) {
		object->_id = id;
		object->_value = address;
		object->_type = type;
		return true;
	}


	while (object->_next != nullptr)
		object = object->_next;

	OBJECT_T* new_obj = new OBJECT_T;
	new_obj->_id = id;
	new_obj->_value = address;
	new_obj->_type = type;
	new_obj->_is_temp = is_temp;
	object->_next = new_obj;
	return true;
}

bool OBJECT_T::pop(int id) {
	OBJECT_T* object = this, * last = nullptr;
	dec_size();

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
		OBJECT_T* next = object->_next;
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
	object->_type = TYPE_NONT;
	return false;
}

bool OBJECT_T::edit(int id, int new_id) {
	OBJECT_T* object = is_exist(id);

	if (object != nullptr) {
		object->_id = new_id;
		return true;
	}

	return false;
}

void OBJECT_T::assign_val(int id, int type, void* address, bool is_temp) {
	this->pop(id);
	this->push(id, type, address, is_temp);
}

void OBJECT_T::purify_duplications() {
	OBJECT_T* object = this, * last = nullptr;

	while (object->_next != nullptr) {

		// IF OBJECTS HAS TEMP AND NOT BE ROOT NODE
		if (object->_is_temp && last) {
			OBJECT_T* current = object;
			last->_next = object->_next;
			object = object->_next;
			delete current;
			dec_size();
			continue;
		}

		// IF OBJECTS HAS TEMP AND BE ROOT NODE
		else if (object->_is_temp && !last) {
			OBJECT_T* next = object->_next;
			object->_id = next->_id;
			object->_value = next->_value;
			object->_type = next->_type;
			object->_is_temp = next->_is_temp;
			object->_next = next->_next;
			delete next;
			dec_size();
			continue;
		}
		last = object;
		object = object->_next;

	}
}

OBJECT_T* OBJECT_T::is_exist(int id) {
	OBJECT_T* object = this;
	while (object->_next != nullptr && object->_id != id)
		object = object->_next;

	if (object->_id != id)
		return nullptr;
	return object;
}

void* OBJECT_T::get_address(int id) {
	OBJECT_T* object = this->is_exist(id);

	if (object == nullptr)
		return nullptr;

	return object->_value;
}

int OBJECT_T::get_type(int id) {
	OBJECT_T* object = this->is_exist(id);

	if (object == nullptr)
		return TYPE_NONT;

	return object->_type;
}

void OBJECT_T::display() {
	OBJECT_T* object = this;

	PRINT << "Objects :" << '\n';
	while (object != nullptr) {
		PRINT << '\t' << std::hex << object->_id << '\t' << std::hex << object->_value << '\n';//<< object->_type << '\n';
		object = object->_next;
	}
}