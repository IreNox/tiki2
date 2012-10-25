#include "Game/VoidList.h"
#include <stdlib.h>
#include <string.h>

namespace TikiEngine
{
	namespace AI
	{

		VoidList::VoidList()
		{
			First = 0;
			Last = 0;
			Iter = 0;
			ListCount = 0;
		}


		VoidList::~VoidList()
		{
			ListNode* node = First;

			while (node != 0)
			{
				ListNode* del = node;
				node = node->Next;
				free(del);
			}
		}

		int VoidList::Append(void* data, int size)
		{
			ListNode* newNode;

			newNode = (ListNode*)malloc(sizeof(ListNode));
			if(newNode == 0)
				return 0;

			newNode->Data = malloc(size);
			if(newNode->Data == 0)
				return 0;

			memcpy(newNode->Data, data, size);
			newNode->Next = 0;
			newNode->Prev = 0;
			newNode->ID = ListCount;
			newNode->DataSize = size;

			if (Last == 0)
			{
				First = newNode;
				Last = First;
			}
			else
			{
				Last->Next = newNode;
				newNode->Prev = Last;
				Last = newNode;
			}

			ListCount++;
			return 1;
		}

		int VoidList::GetCount()
		{
			return ListCount;
		}

		void* VoidList::GetLast()
		{
			if (Last)
				return Last->Data;
			return 0;
		}

		void** VoidList::BuildTable(int *count)
		{
			ListNode* node = First;
			void** table;

			*count = ListCount;
			if (node != 0)
			{
				int i = 0;

				table = (void**)malloc(sizeof(void*) * ListCount);
				if (table == 0)
					return 0;

				while (node != 0)
				{
					table[i] = node->Data;
					node = node->Next;
					i++;
				}

				return table;
			}

			return 0;
		}

		void* VoidList::BuildLinearTable(int *count)
		{
			ListNode* node = First;
			char* table;

			*count = ListCount;
			if (node != 0)
			{
				int i = 0;

				// Assuming all data is the same size
				table = (char*)malloc(node->DataSize * ListCount);
				if (table == 0)
					return 0;

				while (node != 0)
				{
					memcpy(&table[i * node->DataSize], node->Data, node->DataSize);
					node = node->Next;
					i++;
				}

				return table;
			}

			return 0;
		}


		void VoidList::PositionAt(int id)
		{
			ListNode* node = Last;

			while (node != 0 && node->ID != id)
				node = node->Prev;

			Iter = node;
		}

		void* VoidList::GetCurrent()
		{
			if (Iter)
				return Iter->Data;

			return 0;
		}

		void VoidList::Advance()
		{
			Iter = Iter->Next;
		}
	}
}