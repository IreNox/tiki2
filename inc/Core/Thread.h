#pragma once

#include "Core/TikiObject.h"

#include <functional>
#include <Windows.h>

namespace TikiEngine
{
	using namespace std;

	enum ThreadState
	{
		TS_New,
		TS_Starting,
		TS_Running,
		TS_Aborted,	
		TS_Terminated
	};

	template<typename T>
	class Thread : public TikiObject
	{
	public:

		Thread(function<void(T*, void*)> func)
			: func(func), state(TS_New)
		{
		}

		~Thread()
		{
			this->Abort();
		}

		void Start(T* instance, void* arg)
		{
			this->args = arg;
			this->instance = instance;
			state = TS_Starting;

			threadHandle = CreateThread(
				0,
				0,
				startThread,
				this,
				0,
				&threadId
			);
		}

		void Abort(DWORD exitCode = 1)
		{
			if (state == TS_Running)
			{
				TerminateThread(threadHandle, exitCode);
				state = TS_Aborted;
			}
		}

		ThreadState GThreadState()
		{
			return state;
		}

	private:

		DWORD threadId;
		HANDLE threadHandle;

		ThreadState state;

		void* args;
		T* instance;
		function<void(T*, void*)> func;

		static DWORD WINAPI startThread(void* voidThread)
		{
			Thread* thread = (Thread*)voidThread;
			thread->state = TS_Running;

			thread->func(
				thread->instance,
				thread->args
			);

			thread->state = TS_Terminated;
			return 0;
		}

	};
}