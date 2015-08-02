#include "stdafx.h"
#include "Database.h"

Database::Database()
{

}
Database::~Database()
{

}

bool Database::addTable(string tablename)
{
	DB::iterator dbIter = _db.find(tablename);

	if (dbIter == _db.end())
	{
		Table* table = new Table;
		_db.insert(make_pair(tablename, table));
		return true;
	}

	return false;
}

bool Database::removeTable(string tablename)
{
	DB::iterator dbIter = _db.find(tablename);

	if (dbIter != _db.end())
	{
		for (DB::iterator i = _db.begin(); i != _db.end(); i++)
		{
			delete i->second;
		}

		_db.erase(dbIter);
		return true;
	}

	return false;
}

bool Database::isExistTable(string tablename)
{
	return _db.find(tablename) != _db.end();
}

Table* Database::getTable(std::string tablename)
{
	Table* table;
	if (!isExistTable(tablename))
	{
		return NULL;
	}
	
	table = _db.find(tablename)->second;

	return table;
}

bool Database::add(std::string tablename, string keyValue, Row &object)
{
	Table* table = getTable(tablename);

	if (table == NULL || get(tablename, keyValue) != NULL) return false;

	Row* row = new Row(object.begin(), object.end());

	row->insert(make_pair("key", keyValue));
	table->insert(row);

	return true;
}
bool Database::modify(std::string tablename, std::string keyValue, Row &object)
{
	Row* row = get(tablename, keyValue);

	if (row == NULL)
	{
		return false;
	}

	for (Row::iterator i = object.begin(), temp; i != object.end(); i++)
	{
		temp = row->find(i->first);
		if (temp != row->end())
		{
			temp->second = i->second;
		}
		else
		{
			row->insert(make_pair(i->first, i->second));
		}
	}

	return true;
}
bool Database::remove(std::string tablename, std::string keyValue)
{
	Table* table = getTable(tablename);

	if (table == NULL) return NULL;

	Table::iterator tableIter = table->begin();

	for (; tableIter != table->end(); ++tableIter)
	{
		string key = (*tableIter)->find("key")->second;

		if (key == keyValue)
		{
			delete *tableIter;
			table->erase(tableIter);

			return true;
		}
	}

	return false;
}
Row* Database::get(std::string tablename, std::string keyValue)
{
	Row* row = NULL;
	Table* table = getTable(tablename);

	if (table == NULL) return NULL;

	Table::iterator tableIter = table->begin();

	for (; tableIter != table->end(); ++tableIter)
	{
		string key = (*tableIter)->find("key")->second;

		if (key != keyValue)
		{
			continue;
		}

		row = *tableIter;
	}

	return row;
}

/*
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
*/