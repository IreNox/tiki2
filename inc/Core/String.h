#pragma once

#include "Core/TypeDef.h"
#include "Core/List.h"
#include <crtdefs.h>

extern "C"
{
	_CRT_INSECURE_DEPRECATE_MEMORY(memcpy_s) void *  __cdecl memcpy(_Out_opt_bytecapcount_(_Size) void * _Dst, _In_opt_bytecount_(_Size) const void * _Src, _In_ size_t _Size);
}

namespace TikiEngine
{
	#pragma region TikiStringData
	template<typename TChar>
	struct TikiStringData
	{
		TChar* StringData;
		UInt32 StringDataLength;

		UInt32 StringLength;

		Int32 RefCount;

		TikiStringData()
			: StringData(0), StringLength(0), StringDataLength(0), RefCount(1)
		{
		}

		TikiStringData(UInt32 strLen, UInt32 dataLen)
			: StringLength(strLen), StringDataLength(dataLen), RefCount(1)
		{
			StringData = TIKI_NEW TChar[dataLen];
			StringData[strLen] = 0;
		}

		TikiStringData(UInt32 strLen, UInt32 dataLen, const TChar* baseData, Int32 baseDataLen = -1)
			: StringLength(strLen), StringDataLength(dataLen), RefCount(1)
		{
			StringData = TIKI_NEW TChar[dataLen];
			memcpy(
				StringData,
				baseData,
				sizeof(TChar) * (baseDataLen == -1 ? strLen : baseDataLen)
			);
			StringData[strLen] = 0;
		}

		~TikiStringData()
		{
			if (StringData) delete[](StringData);
		}

		inline Int32 AddRef() { RefCount++; return RefCount; }
		inline Int32 Release()
		{
			if (this == &TikiBasicString<TChar>::emptyData) return 0;

			RefCount--;

			if (RefCount < 1)
			{
				delete(this);
				return 0;
			}

			return RefCount;
		}
	};
	#pragma endregion

	template<typename TChar>
	class TikiBasicString
	{
		friend class ParseString;
		friend class StringConvert;
		friend struct TikiStringData<TChar>;

	public:

		#pragma region Class
		TikiBasicString()
		{
			data = &emptyData;
		}

		TikiBasicString(TChar c)
		{
			data = TIKI_NEW TikiStringData<TChar>(1, 2, &c, 1);
		}

		TikiBasicString(const TChar* string, Int32 length = -1)
		{
			if (string == 0)
			{
				data = &emptyData;
			}
			else
			{
				UInt32 len = (length == -1 ? stringLength(string) : length);

				data = TIKI_NEW TikiStringData<TChar>(
					len,
					calcLength(len + 1),
					string
				);
			}
		}

		TikiBasicString(const TikiBasicString<TChar>& copy)
			: data(copy.data)
		{
			data->AddRef();
		}

		~TikiBasicString()
		{
			data->Release();
		}
		#pragma endregion

		#pragma region Member - Get
		inline UInt32 Length() const
		{
			return data->StringLength;
		}

		inline bool Empty() const
		{
			return data->StringLength == 0;
		}

		inline const TChar* CStr() const
		{
			return data->StringData;
		}
		#pragma endregion

		#pragma region Member - Split
		inline List<TikiBasicString<TChar>> Split(const TikiBasicString<TChar>& seperator)
		{
			List<TikiBasicString<TChar>> list;

			UInt32 i = 0;
			UInt32 lastIndex = 0;
			UInt32 count = this->CountSubstring(seperator);
			while (i < count)
			{
				UInt32 index = this->IndexOf(seperator, lastIndex + seperator.data->StringLength);

				list.Add(
					this->Substring(lastIndex, index - lastIndex)
				);

				lastIndex = index + seperator.data->StringLength;
				i++;
			}

			if (data->StringLength - lastIndex > 0)
			{
				list.Add(
					this->Substring(lastIndex, data->StringLength - lastIndex)
				);
			}

			return list;
		}
		#pragma endregion

		#pragma region Member - Replace
		inline TikiBasicString<TChar> Replace(TChar oldValue, TChar TIKI_NEWValue) const
		{
			TikiBasicString str = *this;

			UInt32 i = 0;
			while (i < data->StringLength)
			{
				if (str[i] == oldValue) str[i] = TIKI_NEWValue;
				i++;
			}

			return str;
		}

		inline TikiBasicString<TChar> Replace(const TikiBasicString<TChar>& oldValue, const TikiBasicString<TChar>& TIKI_NEWValue) const
		{
			UInt32 count = this->CountSubstring(oldValue);
			UInt32 length = data->StringLength - (count * oldValue.data->StringLength) + (count * TIKI_NEWValue.data->StringLength);

			TikiBasicString<TChar> str = TikiBasicString<TChar>(length);

			UInt32 i = 0;
			UInt32 offsetOld = 0;
			UInt32 offsetNew = 0;
			while (i < count)
			{
				UInt32 index = this->IndexOf(oldValue, offsetOld);

				memcpy(str.data->StringData + offsetNew, data->StringData + offsetOld, sizeof(TChar) * (index - offsetOld));
				offsetOld += index - offsetOld;
				offsetNew += index - offsetNew;

				memcpy(str.data->StringData + offsetNew, TIKI_NEWValue.data->StringData, sizeof(TChar) * TIKI_NEWValue.data->StringLength);
				offsetOld += oldValue.data->StringLength;
				offsetNew += oldValue.data->StringLength;

				i++;
			}

			return str;
		}
		#pragma endregion

		#pragma region Member - Substring
		inline TikiBasicString<TChar> Substring(UInt32 startIndex, Int32 length = -1) const
		{
			if (length == -1 || startIndex + length > data->StringLength) length = data->StringLength - startIndex;
			if (startIndex > data->StringLength) throw "Index > Length";

			if (length == data->StringLength && startIndex == 0)
			{
				return TikiBasicString<TChar>(*this);
			}

			return TikiBasicString<TChar>(
				data->StringData + startIndex,
				length
				);
		}

		inline UInt32 CountSubstring(const TikiBasicString<TChar>& str) const
		{
			if (str.data->StringLength > data->StringLength)
				throw "str.Length > this.Length";

			UInt32 i = 0;
			UInt32 c = 0;
			while (i < data->StringLength)
			{
				UInt32 b = 0;
				bool found = true;
				while (b < str.data->StringLength)
				{
					if (data->StringData[i + b] != str.data->StringData[b])
					{
						found = false;
						break;
					}
					b++;
				}

				if (found)
				{
					c++;
					i += str.data->StringLength;
				}
				else
				{
					i++;
				}
			}

			return c;
		}
		#pragma endregion

		#pragma region Member - Insert/Remove
		inline TikiBasicString<TChar> Insert(const TikiBasicString<TChar>& str, UInt32 index) const
		{
			TikiBasicString<TChar> oStr = TikiBasicString<TChar>(data->StringLength + str.data->StringLength);

			memcpy(oStr.data->StringData, data->StringData, sizeof(TChar) * index);
			memcpy(oStr.data->StringData + index, str.data->StringData, sizeof(TChar) * str.data->StringLength);
			memcpy(oStr.data->StringData + index + str.data->StringLength, data->StringData + index, sizeof(TChar) * (data->StringLength - index));

			return oStr;
		}

		inline TikiBasicString<TChar> Remove(UInt32 startIndex, UInt32 len) const
		{
			TikiBasicString<TChar> oStr = TikiBasicString<TChar>(data->StringLength - len);

			memcpy(oStr.data->StringData, data->StringData, sizeof(TChar) * startIndex);
			memcpy(oStr.data->StringData + startIndex, data->StringData + startIndex + len, sizeof(TChar) * (data->StringLength - startIndex - len));

			return oStr;
		}
		#pragma endregion

		#pragma region Member - ToLower/ToUpper
		inline TikiBasicString<TChar> ToLower() const
		{
			TikiBasicString<TChar> str = *this;

			UInt32 i = 0;
			while (i < data->StringLength)
			{
				if (str[i] >= letterBigA && str[i] <= letterBigZ)
					str[i] -= letterBigZ - letterLittleZ;

				i++;
			}

			return str;
		}

		inline TikiBasicString<TChar> ToUpper() const
		{
			TikiBasicString<TChar> str = *this;

			UInt32 i = 0;
			while (i < data->StringLength)
			{
				if (str[i] >= letterLittleA && str[i] <= letterLittleZ)
					str[i] -= letterLittleZ - letterBigZ;

				i++;
			}

			return str;
		}
		#pragma endregion

		#pragma region Member - IndexOf/Contains
		inline Int32 IndexOf(TChar c, UInt32 index = 0) const
		{
			UInt32 i = index;
			while (i < data->StringLength)
			{
				if (data->StringData[i] == c) return i;
				i++;
			}
			return -1;
		}

		inline Int32 IndexOf(const TikiBasicString<TChar>& str, UInt32 index = 0) const
		{
			if (str.data->StringLength > data->StringLength) return -1;

			UInt32 i = index;
			UInt32 c = data->StringLength - str.data->StringLength;

			do
			{
				UInt32 b = 0;
				bool found = true;
				while (b < str.data->StringLength)
				{
					if (data->StringData[i + b] != str.data->StringData[b])
					{
						found = false;
						break;
					}
					b++;
				}

				if (found)
				{
					return i;
				}

				i++;
			}
			while (i <= c);

			return -1;
		}

		inline Int32 LastIndexOf(TChar c) const
		{
			Int32 i = data->StringLength - 1;
			while (i >= 0)
			{
				if (data->StringData[i] == c) return i;
				i--;
			}
			return -1;
		}

		inline Int32 LastIndexOf(const TikiBasicString<TChar>& str) const
		{
			Int32 i = (data->StringLength - str.data->StringLength);
			while (i >= 0)
			{
				UInt32 b = 0;
				bool found = true;
				while (b < str.data->StringLength)
				{
					if (data->StringData[i + b] != str.data->StringData[b])
					{
						found = false;
						break;
					}
					b++;
				}

				if (found)
				{
					return i;
				}

				i--;
			}

			return -1;
		}

		inline bool Contains(TChar c) const
		{
			return this->IndexOf(c) != -1;
		}

		inline bool Contains(const TikiBasicString<TChar>& str) const
		{
			return this->IndexOf(str) != -1;
		}
		#pragma endregion

		#pragma region Member - StartWith/EndWith
		inline bool StartsWith(TChar c) const
		{
			if (data->StringLength < 1) return false;

			return data->StringData[0] == c;
		}

		inline bool StartsWith(const TikiBasicString<TChar>& str) const
		{
			if (data->StringLength < str.data->StringLength) return false;

			UInt32 i = 0;
			while (i < str.data->StringLength)
			{
				if (data->StringData[i] != str.data->StringData[i]) return false;
				i++;
			}

			return true;
		}

		inline bool EndsWith(TChar c) const
		{
			if (data->StringLength < 1) return false;

			return data->StringData[data->StringLength - 1] == c;
		}

		inline bool EndsWith(const TikiBasicString<TChar>& str) const
		{
			if (data->StringLength < str.data->StringLength) return false;

			UInt32 b = 0;
			UInt32 i = data->StringLength - str.data->StringLength;
			while (i < data->StringLength)
			{
				if (data->StringData[i] != str.data->StringData[b]) return false;
				i++;
				b++;
			}

			return true;
		}
		#pragma endregion

		#pragma region Operators - Const - []/==/!=
		inline const TChar* operator*()
		{
			return data->StringData;
		}

		inline TChar operator[](UInt32 index) const
		{
			if (index >= data->StringLength) 
				throw "Index > Length";

			return data->StringData[index];
		}

		inline TChar& operator[](UInt32 index)
		{
			if (index >= data->StringLength)
				throw "Index > Length";

			if (data->RefCount > 1)
			{
				TikiStringData<TChar>* oldData = data;

				data = TIKI_NEW TikiStringData<TChar>(
					data->StringLength,
					data->StringDataLength,
					data->StringData
				);

				oldData->Release();
			}

			return data->StringData[index];
		}

		inline bool operator==(const TikiBasicString<TChar>& rhs) const
		{
			if (data == rhs.data) return true;
			if (data->StringLength != rhs.data->StringLength) return false;

			UInt32 i = 0;
			while (i < data->StringLength)
			{
				if (data->StringData[i] != rhs.data->StringData[i]) return false;
				i++;
			}

			return true;
		}

		inline bool operator!=(const TikiBasicString<TChar>& rhs) const
		{
			return !(*this == rhs);
		}
		#pragma endregion

		#pragma region Operators - =/+/+=
		inline void operator=(const TikiBasicString<TChar>& rhs)
		{
			TikiStringData<TChar>* oldData = data;

			data = rhs.data;
			data->AddRef();

			oldData->Release();
		}

		inline TikiBasicString<TChar> operator+(const TikiBasicString<TChar>& rhs) const
		{
			UInt32 len = data->StringLength + rhs.data->StringLength;
			TikiBasicString<TChar> str = TikiBasicString<TChar>(len);

			memcpy(str.data->StringData, data->StringData, sizeof(TChar) * data->StringLength);
			memcpy(str.data->StringData + data->StringLength, rhs.data->StringData, sizeof(TChar) * rhs.data->StringLength);
			str.data->StringData[len] = 0;

			return str;
		}

		inline TikiBasicString<TChar>& operator+=(const TikiBasicString<TChar>& rhs)
		{
			UInt32 sl = data->StringLength;
			UInt32 len = data->StringLength + rhs.data->StringLength;

			if (data->RefCount != 1 || data->StringDataLength <= len)
			{
				TikiStringData<TChar>* oldData = data;

				data = TIKI_NEW TikiStringData<TChar>(
					len,
					calcLength(len + 1),
					oldData->StringData,
					oldData->StringLength
				);

				oldData->Release();
			}

			memcpy(data->StringData + sl, rhs.data->StringData, sizeof(TChar) * rhs.data->StringLength);
			data->StringData[len] = 0;
			data->StringLength = len;

			return *this;
		}
		#pragma endregion

		#pragma region Operators - >/>=/</<=
		inline bool operator>(const TikiBasicString<TChar>& rhs) const
		{
			if (data == rhs.data) return false;

			UInt32 i = 0;
			UInt32 c = (data->StringLength < rhs.data->StringLength ? data->StringLength : rhs.data->StringLength);
			while (i < c && data->StringData[i] == rhs.data->StringData[i])
			{
				i++;
			}

			return data->StringData[i] > rhs.data->StringData[i];
		}

		inline bool operator>=(const TikiBasicString<TChar>& rhs) const
		{
			return (*this > rhs) || (*this == rhs);
		}

		inline bool operator<(const TikiBasicString<TChar>& rhs) const
		{
			if (data == rhs.data) return false;

			UInt32 i = 0;
			UInt32 c = (data->StringLength < rhs.data->StringLength ? data->StringLength : rhs.data->StringLength);
			while (i < c && data->StringData[i] == rhs.data->StringData[i])
			{
				i++;
			}

			return data->StringData[i] < rhs.data->StringData[i];
		}

		inline bool operator<=(const TikiBasicString<TChar>& rhs) const
		{
			return (*this < rhs) || (*this == rhs);
		}
		#pragma endregion

	private:

		#pragma region Private Constructor
		TikiBasicString(UInt32 len)
		{
			data = TIKI_NEW TikiStringData<TChar>(
				len,
				calcLength(len + 1)
			);
		}
		#pragma endregion

		#pragma region Vars
		TikiStringData<TChar>* data;

		static const TChar letterBigA;
		static const TChar letterBigZ;
		static const TChar letterLittleA;
		static const TChar letterLittleZ;
		static const TChar numberDot;
		static const TChar numberZero;
		static const TChar numberNine;
		static const TChar numberPlus;
		static const TChar numberMinus;
		static TikiStringData<TChar> emptyData;
		#pragma endregion

		#pragma region Private Member
		inline UInt32 stringLength(const TChar* string) const
		{
			if (string == 0) return 0;

			UInt32 c = 0;
			const TChar* str = string;
			while (*str != 0) { str++; c++; }

			return c;
		}

		inline UInt32 calcLength(UInt32 neededLen) const
		{
			UInt32 len = 2;
			while (len < neededLen) { len *= 2; }
			return len;
		}
		#pragma endregion

	};

	inline TikiBasicString<char> operator+(const char* str1, TikiBasicString<char> str2)
	{
		return TikiBasicString<char>(str1) + str2;
	}

	inline TikiBasicString<wchar_t> operator+(const wchar_t* str1, TikiBasicString<wchar_t> str2)
	{
		return TikiBasicString<wchar_t>(str1) + str2;
	}

	typedef TikiBasicString<char> string;
	typedef TikiBasicString<wchar_t> wstring;

	//typedef TikiBasicString<char> String;
	//typedef TikiBasicString<wchar_t> WString;
}