#pragma once
#include"utility_info.h"

struct OBJECT {
	int _type ;
	void* _value ;
	bool _is_temp ;

	OBJECT() :_type(TYPE_NONT), _value(nullptr), _is_temp(true) {};
};

extern MAP<int, OBJECT*> __objects_table;
