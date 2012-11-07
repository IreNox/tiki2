#pragma once

#include "Core/TypeDef.h"
#include "Core/HelperThreading.h"

#include <functional>

namespace TikiEngine
{
	using namespace std;

	/*! @brief Buffered Variable */
	template<typename T>
	class BVar
	{
	public:

		BVar()
		{
			val[0] = T();

#ifdef TIKI_MULTITHREADING
			val[1] = T();
#endif
		}

		BVar(T initVal)
		{
			val[0] = initVal;

#ifdef TIKI_MULTITHREADING
			val[1] = initVal;
#endif
		}

		BVar(function<T(void)> ctor)
		{
			val[0] = ctor();

#ifdef TIKI_MULTITHREADING
			val[1] = ctor();
#endif
		}

		virtual ~BVar()
		{
		}

		inline void ToAll(function<void(T&)> func)
		{
			func(val[0]);

#ifdef TIKI_MULTITHREADING
			func(val[1]);
#endif
		}

		inline void operator=(const T& nVal)
		{
			val[getCurrentIndex()] = nVal;
		}

		inline void operator=(const BVar<T>& other)
		{
			val[0] = other.val[0];

#ifdef TIKI_MULTITHREADING
			val[1] = other.val[1];
#endif
		}

		inline operator T&()
		{
			return val[getCurrentIndex()];
		}

		inline T* operator->()
		{
			return &val[getCurrentIndex()];
		}

	protected:

#ifdef TIKI_MULTITHREADING
		T val[2];
#else
		T val[1];
#endif


		inline Byte getCurrentIndex()
		{
#ifdef TIKI_MULTITHREADING
			return HelperThreading::GIndex();
#else
			return 0;
#endif
		}

	};

	/*! @brief Buffered Pointer */
	template<typename T>
	class BPoint : public BVar<T*>
	{
	public:

		BPoint()
			: BVar(0)
		{
			dtor = [](T* t){};
		}

		BPoint(function<T*(void)> ctor)
			: BVar(0)
		{
			SafeAddRef(ctor(), &val[0]);

#ifdef TIKI_MULTITHREADING
			SafeAddRef(ctor(), &val[1]);
#endif

			dtor = [](T* t){ SafeRelease(&t); };
		}

		BPoint(function<T*(void)> ctor, function<void(T*)> dtor)
			: BVar(0), dtor(dtor)
		{
			SafeAddRef(ctor(), &val[0]);

#ifdef TIKI_MULTITHREADING
			SafeAddRef(ctor(), &val[1]);
#endif
		}

		BPoint(BPoint<T>& other)
		{
			SafeAddRef(other.val[0], val[0]);

#ifdef TIKI_MULTITHREADING
			SafeAddRef(other.val[1], val[1]);
#endif
		}

		~BPoint()
		{
			if (val[0] != 0) dtor(val[0]);

#ifdef TIKI_MULTITHREADING
			if (val[1] != 0) dtor(val[1]);
#endif
		}

		inline void operator=(const BPoint<T>& other)
		{
			SafeAddRef(other.val[0], &val[0]);

#ifdef TIKI_MULTITHREADING
			SafeAddRef(other.val[1], &val[1]);
#endif
		}

		inline T* operator->()
		{
			return val[getCurrentIndex()];
		}

	protected:

		function<void(T*)> dtor;

	};
}