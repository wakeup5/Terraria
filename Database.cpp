#include "stdafx.h"
#include "Database.h"


Database::Database()
{
}


Database::~Database()
{
}

HRESULT Database::initialize(void)
{
	loadDatabase();

	return S_OK;
}

void Database::release(void)
{

}

void Database::loadDatabase(void)
{
	//데이터 읽는다
	vector<string> vTemp;
	vTemp = TXTMANAGER->txtLoad("database.txt");

	string str;
	
	for (int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			Elements vElement;
			str = vTemp[i + 1];
			_database.insert(make_pair(str, vElement));
			continue;
		}
		DatabaseMapIter mIter = _database.find(str);
		mIter->second.push_back(vTemp[i]);
	}
	
	vTemp.clear();
}


void Database::saveDatabase()
{
	
}

void Database::add(std::string dbname, DataObject* obj)
{
	DatabaseMapIter dbIter = _database.find(dbname);

	if (dbIter == _database.end())
	{
		Elements elements;
		_database.insert(make_pair(dbname, elements));
	}
	vector<string> temp;
	int size = obj->toString(temp);

	string objInfo = myUtil::vectorArrayCombine(temp, size);

	_database.find(dbname)->second.push_back(objInfo);
}

void Database::addDB(std::string dbname, DataObject* obj)
{
	DatabaseMapIter dbIter = _database.find(dbname);

	if (dbIter == _database.end())
	{
		Elements elements;
		_database.insert(make_pair(dbname, elements));
	}
	vector<string> temp;
	int size = obj->toString(temp);

	string objInfo = myUtil::vectorArrayCombine(temp, size);

	_database.find(dbname)->second.clear();
	_database.find(dbname)->second.push_back(objInfo);
}