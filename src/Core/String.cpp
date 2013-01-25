
#include "Core/String.h"

namespace TikiEngine
{
	const char TikiBasicString<char>::letterBigA = 'A';
	const char TikiBasicString<char>::letterBigZ = 'Z';
	const char TikiBasicString<char>::letterLittleA = 'a';
	const char TikiBasicString<char>::letterLittleZ = 'z';
	const char TikiBasicString<char>::numberDot = L'.';
	const char TikiBasicString<char>::numberZero = L'0';
	const char TikiBasicString<char>::numberNine = L'9';
	const char TikiBasicString<char>::numberPlus = L'+';
	const char TikiBasicString<char>::numberMinus = L'-';
	TikiStringData<char> TikiBasicString<char>::emptyData = TikiStringData<char>();

	const wchar_t TikiBasicString<wchar_t>::letterBigA = L'A';
	const wchar_t TikiBasicString<wchar_t>::letterBigZ = L'Z';
	const wchar_t TikiBasicString<wchar_t>::letterLittleA = L'a';
	const wchar_t TikiBasicString<wchar_t>::letterLittleZ = L'z';
	const wchar_t TikiBasicString<wchar_t>::numberDot = L'.';
	const wchar_t TikiBasicString<wchar_t>::numberZero = L'0';
	const wchar_t TikiBasicString<wchar_t>::numberNine = L'9';
	const wchar_t TikiBasicString<wchar_t>::numberPlus = L'+';
	const wchar_t TikiBasicString<wchar_t>::numberMinus = L'-';
	TikiStringData<wchar_t> TikiBasicString<wchar_t>::emptyData = TikiStringData<wchar_t>();
}
