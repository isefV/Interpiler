#pragma once
#include"utility_info.h"

// OBJECT TABLE OBJECT
class OBJECT_T {
	OBJECT_T* _next;
	int _id, _type;
	void* _value;
	bool _is_temp;
	void inc_size();
	void dec_size();

public:
	OBJECT_T() {
		_id = 0;
		_type = TYPE_NONT;
		_next = nullptr;
		_value = nullptr;
		_is_temp = true;
	}
	bool push(int id, int type, void* address, bool is_temp = true);
	bool pop(int id);
	bool edit(int id, int new_id);
	int get_type(int id);
	int get_size();
	void* get_address(int id);
	void assign_val(int id, int type, void* address, bool is_temp);
	void purify_duplications();
	void display();
	OBJECT_T* is_exist(int id);

};

extern OBJECT_T __objects_table;