#pragma once

#include <stdio.h>
#include "Core/Console.h"

class ErrorStream : public NxUserOutputStream
{
public:
	/*
	 * this should be routed to the application specific error handling. If this gets hit then you are in most cases using the SDK
     * wrong and you need to debug your code! however, code may just be a warning or information.
	*/
	void reportError(NxErrorCode e, const char* message, const char* file, int line)
	{
		//printf("%s (%d) :", file, line);
		

		switch(e)
		{
		case NXE_INVALID_PARAMETER:
			Console::Write( "invalid parameter");
			break;
		case NXE_INVALID_OPERATION:
			Console::Write( "invalid operation");
			break;
		case NXE_OUT_OF_MEMORY:
			Console::Write( "out of memory");
			break;
		case NXE_DB_INFO:
			Console::Write( "info");
			break;
		case NXE_DB_WARNING:
			Console::Write( "warning");
			break;
		default:
			Console::Write("unknown error");
		}

		std::string error(message);
		Console::Write(error);
		Console::Write("\n");

	}

	NxAssertResponse reportAssertViolation(const char* message, const char* file, int line)
	{
		printf("access violation : %s (%s line %d)\n", message, file, line);

		switch (MessageBox(0, (LPCWSTR)message, L"AssertViolations.", MB_ABORTRETRYIGNORE))
		{
		case IDRETRY:
			return NX_AR_CONTINUE;
		case IDIGNORE:
			return NX_AR_IGNORE;
		case IDABORT:
		default:
			return NX_AR_BREAKPOINT;
		}

	}

	void print(const char* message)
	{
		Console::Write(message);
	}

	string GetNxSDKCreateError(const NxSDKCreateError& errorCode) 
	{
		switch(errorCode) 
		{
			case NXCE_NO_ERROR:				return "NXCE_NO_ERROR";
			case NXCE_PHYSX_NOT_FOUND:		return "NXCE_PHYSX_NOT_FOUND";
			case NXCE_WRONG_VERSION:		return "NXCE_WRONG_VERSION";
			case NXCE_DESCRIPTOR_INVALID:	return "NXCE_DESCRIPTOR_INVALID";
			case NXCE_CONNECTION_ERROR:		return "NXCE_CONNECTION_ERROR";
			case NXCE_RESET_ERROR:			return "NXCE_RESET_ERROR";
			case NXCE_IN_USE_ERROR:			return "NXCE_IN_USE_ERROR";
			default:					    return "Unknown error";
		}
	}

};