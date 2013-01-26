#pragma once

#include "Core/String.h"
#include <math.h>

namespace TikiEngine
{
	class ParseString
	{
	public:

		#pragma region String
		static Int16 ParseInt16(const string& string)
		{			
			return parseSigedInteger<char, UInt16>(string);
		}

		static Int32 ParseInt32(const string& string)
		{			
			return parseSigedInteger<char, UInt32>(string);
		}

		static Int64 ParseInt64(const string& string)
		{			
			return parseSigedInteger<char, UInt64>(string);
		}

		static UInt16 ParseUInt16(const string& string)
		{			
			return parseUnsigedInteger<char, UInt16>(string);
		}

		static UInt32 ParseUInt32(const string& string)
		{			
			return parseUnsigedInteger<char, UInt32>(string);
		}

		static UInt64 ParseUInt64(const string& string)
		{			
			return parseUnsigedInteger<char, UInt64>(string);
		}

		static Single ParseSingle(const string& string)
		{			
			return parseFloat<char, Single>(string);
		}

		static Double ParseDouble(const string& string)
		{			
			return parseFloat<char, Double>(string);
		}
		#pragma endregion

		#pragma region WString
		static Int16 WParseInt16(const wstring& string)
		{			
			return parseSigedInteger<wchar_t, UInt16>(string);
		}

		static Int32 WParseInt32(const wstring& string)
		{			
			return parseSigedInteger<wchar_t, UInt32>(string);
		}

		static Int64 WParseInt64(const wstring& string)
		{			
			return parseSigedInteger<wchar_t, UInt64>(string);
		}

		static UInt16 WParseUInt16(const wstring& string)
		{			
			return parseUnsigedInteger<wchar_t, UInt16>(string);
		}

		static UInt32 WParseUInt32(const wstring& string)
		{			
			return parseUnsigedInteger<wchar_t, UInt32>(string);
		}

		static UInt64 WParseUInt64(const wstring& string)
		{			
			return parseUnsigedInteger<wchar_t, UInt64>(string);
		}

		static Single WParseSingle(const wstring& string)
		{			
			return parseFloat<wchar_t, Single>(string);
		}

		static Double WParseDouble(const wstring& string)
		{			
			return parseFloat<wchar_t, Double>(string);
		}
		#pragma endregion

	private:

		#pragma region Private Member
		template <typename TString>
		static bool getSiged(TikiBasicString<TString>& string)
		{
			if (string[0] == TikiBasicString<TString>::numberPlus)
			{
				string = string.Substring(1);
			}

			if (string[0] == TikiBasicString<TString>::numberMinus)
			{
				string = string.Substring(1);
				return false;
			}

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Integer
		template<typename TString, typename TUInt>
		static TUInt parseUnsigedInteger(const TikiBasicString<TString>& string)
		{
			TUInt num = 0;

			UInt32 i = 0;
			while (i < string.data->StringLength)
			{
				if (string[i] >= TikiBasicString<TString>::numberZero && string[i] <= TikiBasicString<TString>::numberNine)
				{
					int p = string.data->StringLength - (i + 1);
					TUInt c = string[i] - TikiBasicString<TString>::numberZero;

					num += c * (TUInt)pow(10.0, p);
				}
				else
				{
					return (TUInt)-1;
				}

				i++;
			}

			return num;
		}

		template<typename TString, typename TInt>
		static TInt parseSigedInteger(const TikiBasicString<TString>& string)
		{
			TikiBasicString<TString> str = string;
			TInt mul = (getSiged(str) ? 1 : -1);

			return parseUnsigedInteger<TString, TInt>(str) * mul;
		}
		#pragma endregion

		#pragma region Private Member - Float
		template <typename TString, typename TFloat>
		static TFloat parseFloat(const TikiBasicString<TString>& string)
		{
			TikiBasicString<TString> str = string;
			TFloat mul = (TFloat)(getSiged(str) ? 1.0 : -1.0);
			TFloat num = 0;

			UInt32 i = 0;
			UInt32 dotIndex = str.IndexOf(TikiBasicString<TString>::numberDot);
			while (i < str.data->StringLength)
			{
				if (str[i] >= TikiBasicString<TString>::numberZero && str[i] <= TikiBasicString<TString>::numberNine)
				{
					int p = dotIndex - (i < dotIndex ? i + 1 : i);
					TFloat c = (TFloat)(str[i] - TikiBasicString<TString>::numberZero);

					num += c * (TFloat)pow(10.0, p);
				}
				else
				{
					return (TFloat)-1.0;
				}

				i++;

				if (i == dotIndex)
					i++;
			}

			return num * mul;
		}
		#pragma endregion
	};
}