#pragma once
#include"utility.h"
#include"object.h"

// ARRAY TABLE OBJECT
class ARRAY_T {
	int _id, _end_index;
	ARRAY_T* _next;

public:
	ARRAY_T() {
		_id = 0;
		_end_index = 0;
		_next = nullptr;
	}

	int push(int parent_id);
	ARRAY_T* is_exist(int parent_id);
};

extern ARRAY_T __array_table;