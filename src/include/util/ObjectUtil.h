#ifndef _OBJECT_UTIL_H
#define _OBJECT_UTIL_H

#include "Object.h"

namespace ObjectUtil {

	// Cast an Object to another type
	// T - Type of the Object to cast
	// o - Object to cast
	// returns: The Object casted to the type T, or to nullptr if the cast
	//		wasn't sucessful
	template<class T>
	T* toType(Object* o) {
		return dynamic_cast<T*>(o);
	}

	// Check if an Object is another type
	// T - Type of the Object to check the cast of
	// o - Object to check the casting of
	// returns: If the Object o can be casted to the type T
	template<class T>
	bool isType(Object* o) {
		return (dynamic_cast<T*>(o) == o);
	}

	// Cast a pointer to an Object pointer
	// o - Pointer to cast
	// returns: A Object* of o
	Object* toObject(void* o);

};

#endif
