#pragma once

#include "Core/TikiReflect.h"

#define TIKI_PTR(var, flags) \
	TikiFieldInfo(#var, (char*)&x-(char*)this, sizeof(var), TikiTypeOfPtr(&var))

#define TIKI_FIELD(var, flags) \
	TikiFieldInfo(#var, (char*)&x-(char*)this, sizeof(var), TikiTypeOf(var))

#define TIKI_FUNC(var, flags) \
	TikiMethodInfo(#var, TikiFuncTypeOf(&self::var))

//#define TIKI_METHOD(var, flags) \
	TikiMethodInfo(#var, TikiFuncTypeOf(&self::var))


#define TIKI_TYPE(components) \
	private: \
	static TikiType* type; \
	public: \
	TikiType* GetTikiType() { \
		if (type == 0) type = TikiType(typeid(*this).name(), components); \
		return type; \
	}

//static TikiTypeDescription* GetTikiTypeDesc() { return &TikiTypeDesc; }
