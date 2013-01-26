#pragma once

#include "Core/String.h"
#include <stdio.h>

namespace TikiEngine
{
	class StringConvert
	{
	public:

		#pragma region String
		static string ToString(Int16 value)
		{
			return integerToString<char, Int16>(value);
		}

		static string ToString(Int32 value)
		{
			return integerToString<char, Int32>(value);
		}

		static string ToString(Int64 value)
		{
			return integerToString<char, Int64>(value);
		}

		static string ToString(UInt16 value)
		{
			return integerToString<char, UInt16>(value);
		}

		static string ToString(UInt32 value)
		{
			return integerToString<char, UInt32>(value);
		}

		static string ToString(UInt64 value)
		{
			return integerToString<char, UInt64>(value);
		}

		static string ToString(Single value)
		{
			return floatToString<char, Single>(value);
		}

		static string ToString(Double value)
		{
			return floatToString<char, Double>(value);
		}
		#pragma endregion

		#pragma region WString
		static wstring ToWString(Int16 value)
		{
			return integerToString<wchar_t, Int16>(value);
		}

		static wstring ToWString(Int32 value)
		{
			return integerToString<wchar_t, Int32>(value);
		}

		static wstring ToWString(Int64 value)
		{
			return integerToString<wchar_t, Int64>(value);
		}

		static wstring ToWString(UInt16 value)
		{
			return integerToString<wchar_t, UInt16>(value);
		}

		static wstring ToWString(UInt32 value)
		{
			return integerToString<wchar_t, UInt32>(value);
		}

		static wstring ToWString(UInt64 value)
		{
			return integerToString<wchar_t, UInt64>(value);
		}

		static wstring ToWString(Single value)
		{
			return floatToString<wchar_t, Single>(value);
		}

		static wstring ToWString(Double value)
		{
			return floatToString<wchar_t, Double>(value);
		}
		#pragma endregion

	private:

		#pragma region IntegerToString
		template <typename TString, typename TInt>
		static TikiBasicString<TString> integerToString(TInt value)
		{
			UInt32 len = 0;
			TInt val = (TInt)abs((Int32)value);

			if (value < 0)
				len++;

			TInt i = 1;
			TInt i2 = i;
			while (true)
			{
				if (i > val) break;

				len++;
				i2 = i;
				i *= 10;

				if (i < i2) break;
			}

			TikiBasicString<TString> str = TikiBasicString<TString>(len);

			UInt32 a = 0;
			if (value < 0)
			{
				str[0] = TikiBasicString<TString>::numberMinus;
				a++;
			}

			i = 0;
			TInt i3 = 0;
			while (a < len)
			{
				i2 = val / (TInt)pow(10.0, (double)(len - a) - 1);
				i2 -= i3;
				i3 += i2;
				i3 *= 10;

				str[a] = TikiBasicString<TString>::numberZero + (TString)i2;

				i++;
				a++;
			}

			return str;
		}
		#pragma endregion

		#pragma region FloatToString
		template <typename TString, typename TFloat>
		static TikiBasicString<TString> floatToString(TFloat value)
		{
			TString buffer[64];

			if (sizeof(TString) == 1)
			{
				_snprintf_s((char*)buffer, 64, 64, "%f", value);
			}
			else
			{
				_snwprintf_s((wchar_t*)buffer, 64, 64, L"%f", value);
			}

			return TikiBasicString<TString>(buffer);
		}
		#pragma endregion

	};
}