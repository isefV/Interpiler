#pragma once

struct EXPRESSION {
	int _id ;
	short int _priority , _mode ;

	EXPRESSION() : _id(0), _priority(0), _mode(0) {}
};


inline bool priority_compare(const EXPRESSION*exp_1, const EXPRESSION* exp_2) {
	return exp_1->_priority > exp_2->_priority;
}