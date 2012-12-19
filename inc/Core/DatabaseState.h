#pragma once

#include "Core/EngineObject.h"
#include "Core/sqlite3.h"

namespace TikiEngine
{
	enum DatabaseTypes
	{
		DBT_Integer = 1,
		DBT_Float   = 2,
		DBT_Text    = 3,
		DBT_Blob    = 4,
		DBT_Null    = 5
	};

	class DatabaseState : public EngineObject
	{
	public:

		DatabaseState(Engine* engine);
		~DatabaseState();

		bool Query(const string& sql);
		template<typename T>
		bool Query(const string& table, const string& field, const T& value)
		{
			ostringstream s;
			s << "SELECT * FROM [" << table << "] WHERE [" << field << "] = '" << value << "'";

			return this->Query(
				s.str()
			);
		}

		bool ReadNextRow();

		void* GetField(const string& field)
		{
			return fieldData[field];
		}
		template<typename T>
		T* GetFieldPtr(const string& field)
		{
			return (T*)fieldData[field];
		}
		template<typename T>
		T GetFieldValue(const string& field)
		{
			return *((T*)fieldData[field]);
		}

	private:

		sqlite3_stmt* state;
		UInt32 dataLength;
		Byte* data;

		Dictionary<string, void*> fieldData;

	};
}