
#include <Windows.h>

#include <string>
#include <sstream>
using namespace std;

wstring getDirname(wstring name)
{
	return name.substr(0, name.find_last_of(L'\\'));
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	BOOL is64;
	IsWow64Process(GetCurrentProcess(), &is64);

	WCHAR cd[MAX_PATH];
	GetModuleFileName(0, cd, MAX_PATH);

	wstring path = getDirname(cd);

	wstring fileName = L"";
	if (is64)
	{
		fileName = L"bin64\\game64.exe";
	}
	else
	{
		fileName = L"bin32\\game32.exe";
	}

	wstring fullPath = path + L"\\" + fileName;

	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;

	ZeroMemory(&sInfo, sizeof(sInfo));
	ZeroMemory(&pInfo, sizeof(pInfo));

	memcpy(cd, fullPath.c_str(), sizeof(WCHAR) * (fullPath.size() + 1));

	if (!CreateProcess(
		NULL,
		cd,
		NULL,
		NULL,
		false,
		0,
		NULL,
		path.c_str(),
		&sInfo,
		&pInfo
	))
	{
		wostringstream s;
		s << L"Starting game failed. ErrorCode: " << GetLastError();

		MessageBox(0, s.str().c_str(), L"TikiLauncher", MB_OK | MB_ICONERROR);

		return 0;
	}

	return 0;
}