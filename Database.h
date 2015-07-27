#pragma once
#include "SingletonBase.h"

#include <vector>
#include <map>

class DataObject
{
public:
	virtual int toString(vector<string>&) = 0;
	virtual int toObject(vector<string>) = 0;
	static int getStrLenByList(const vector<string>& v)
	{
		int result = 0;
		for (vector<string>::const_iterator i = v.begin(); i != v.end(); i++)
		{
			result += i->size();
		}

		return result;
	}
};

typedef DataObject Element;

typedef std::vector<std::string>			Elements;
typedef std::vector<std::string>::iterator	ElementsIter;

typedef std::map<std::string, Elements>				DatabaseMap;
typedef std::map<std::string, Elements>::iterator	DatabaseMapIter;

class Database : public SingletonBase < Database >
{
private:
public:
	DatabaseMap _database;

	HRESULT initialize();
	void release();

	void loadDatabase();
	void saveDatabase();

	template < class T >
	T* get(std::string dbname, int index, DataObject* obj = NULL)
	{
		DatabaseMapIter dbIter = _database.find(dbname);
		Elements elements;
		T* result;

		if (dbIter == _database.end() || !dynamic_cast<T>(obj)) return obj;
		elements = dbIter->second;

		if (obj == NULL) obj = new T;
		result = dynamic_cast<T*>(obj);

		vector<string> objInfo = myUtil::charArraySeparation(elements[i].c_str());

		((DataObject*)result)->toObject(objInfo);
		
		return result;
	}

	template < typename T >
	vector<T> getDB(std::string dbname)
	{
		DatabaseMapIter dbIter = _database.find(dbname);
		vector<T> resultList;

		if (dbIter == _database.end()) return resultList;

		for (ElementsIter i = dbIter->second.begin(); i != dbIter->second.end(); i++)
		{
			//if (!dynamic_cast<T*>(*i)) continue;

			vector<string> objInfo = myUtil::charArraySeparation(i->c_str());

			T elem;
			((DataObject*)&elem)->toObject(objInfo);

			resultList.push_back(elem);
		}

		return resultList;
	}

	void add(std::string dbname, DataObject* obj);
	void addDB(std::string dbname, DataObject* obj);

	Database();
	~Database();
};

