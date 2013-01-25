//
//#include "Core/Thread.h"
//
//namespace TikiEngine
//{
//	Thread::Thread(function<void(void*)> func)
//		: func(func), state(TS_TIKI_NEW)
//	{
//	}
//
//	Thread::~Thread()
//	{
//		this->Abort();
//	}
//
//	void Thread::Start(void* arg)
//	{
//		args = arg;
//		state = TS_Starting;
//
//		threadHandle = CreateThread(
//			0,
//			0,
//			startThread,
//			this,
//			0,
//			&threadId
//		);
//	}
//
//	void Thread::Abort(DWORD exitCode)
//	{
//		if (state == TS_Running)
//		{
//			TerminateThread(threadHandle, exitCode);
//			state = TS_Aborted;
//		}
//	}
//
//	DWORD Thread::startThread(void* voidThread)
//	{
//		Thread* thread = (Thread*)voidThread;
//		thread->state = TS_Running;
//
//		thread->func(
//			thread->args
//		);
//
//		thread->state = TS_Terminated;
//		return 0;
//	}
//}