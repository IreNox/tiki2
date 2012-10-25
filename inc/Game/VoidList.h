#pragma once

namespace TikiEngine
{
	namespace AI
	{

		struct ListNode 
		{
			void*		Data;
			int			DataSize;
			ListNode*	Next;
			ListNode*	Prev;
			int			ID;
		};

		// General list class for arbitrary data
		class VoidList
		{

		public:

			VoidList();
			~VoidList();

			int Append(void *data, int size);

			int GetCount();

			void* GetLast();

			// Build a table of pointers to the node data
			void** BuildTable(int *count);

			// Create one big array with all the node data
			void* BuildLinearTable(int *count);

			void PositionAt(int id);

			void* GetCurrent();

			void Advance();

		protected:
			ListNode* First;
			ListNode* Last;
			ListNode* Iter;
			int		  ListCount;

		};

	}
}