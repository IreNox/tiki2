#pragma once

#include "Core/TypeInc.h"

enum TikiFlags
{
	TF_INSTANCE		= 0x0001,
	TF_STATIC		= 0x0002,
	TF_CONST		= 0x0004,
	TF_PUBLIC		= 0x0010,
	TF_PRIVATE		= 0x0020,
	TF_PROTECTED	= 0x0040,
	TF_VIRTUAL		= 0x0100,
	TF_VOLATILE		= 0x0200, 
	TF_TRANSIENT	= 0x0400
};

#pragma region MemberInfo
class TikiMemberInfo
{
public:
	TikiMemberInfo(const char* name) : name(name) {}
	~TikiMemberInfo() {}

	inline cstring Name() { return name; }
private:
	cstring name;
};
#pragma endregion

#pragma region TikiType
class TikiType : public TikiMemberInfo
{
public:
	TikiType(cstring name, TikiMemberInfo* info);
	~TikiType();

};
#pragma endregion

#pragma region FieldInfo
class TikiFieldInfo : public TikiMemberInfo
{
public:
	TikiFieldInfo(const char* name, UPInt offset, UPInt size, TikiType* type)
		: TikiMemberInfo(name), offset(offset), size(size), type(type) {}
	~TikiFieldInfo();

	inline UPInt Size() { return size; }
	inline UPInt Offset() { return offset; }
	inline TikiType* FieldType() { return type; }

	inline void* GetValue(void* obj) { return (void*)(((char*)obj)+offset); }
	inline void SetValue(void* obj, void* value) { memcpy((char*)obj+offset, value, size); }

private:

	UPInt size;
	UPInt offset;

	TikiType* type;

};

class TikiPointerInfo : public TikiFieldInfo
{
public:
	TikiPointerInfo(const char* name, UPInt offset, UPInt size, TikiType* type)
		: TikiFieldInfo(name, offset, size, 0), pointerType(type) {}
	~TikiPointerInfo();
	
	Tik

private:

	TikiType* pointerType;

};
#pragma endregion
