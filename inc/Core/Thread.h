#pragma once

#include "Core/TikiObject.h"

#include <functional>
#include <Windows.h>

namespace TikiEngine
{
	using namespace std;

	enum ThreadState
	{
		TS_TIKI_NEW,
		TS_Starting,
		TS_Running,
		TS_Suspend,
		TS_Aborted,	
		TS_Terminated
	};

	template<typename TInst, typename TArgs>
	class Thread : public TikiObject
	{
	public:

		Thread(function<void(TInst*, TArgs*)> func)
			: func(func), state(TS_TIKI_NEW)
		{
		}

		~Thread()
		{
			this->Abort();
		}

		void Start(TInst* instance, TArgs* arg)
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

		void Suspend()
		{
			state = TS_Suspend;
			SuspendThread(threadHandle);
		}

		void Resume()
		{
			if (state == TS_Suspend)
			{
				ResumeThread(threadHandle);
				state = TS_Running;
			}
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

		TArgs* args;
		TInst* instance;
		function<void(TInst*, TArgs*)> func;

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