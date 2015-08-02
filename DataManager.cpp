#include "stdafx.h"
#include "DataManager.h"


DataManager::DataManager()
{

}


DataManager::~DataManager()
{

}

HRESULT DataManager::initialize()
{
	return S_OK;
}
void DataManager::release()
{

}

void DataManager::save(const char* saveFileName, vector<string> vString)
{
	HANDLE file;
	char str[256];
	DWORD write;

	file = CreateFile("a.save", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 256, &write, NULL);

	CloseHandle(file);
}

void DataManager::loadDatabase(std::string tablename, const char* ini)
{
	Table* table = DATABASE->getTable(tablename);
	if (table != NULL) return;

	DATABASE->addTable(tablename);

	Row row;

	char buffer[2000];
	char secBuffer[1000];
	GetPrivateProfileSectionNames(buffer, 2000, ini);

	for (LPCTSTR p = buffer; *p != 0; p += strlen(p) + 1)
	{
		GetPrivateProfileSection(p, secBuffer, 1000, ini);

		//row->insert("key", p);
		for (LPCTSTR secP = secBuffer; *secP != 0; secP += strlen(secP) + 1)
		{
			string kv(secP);

			string key = kv.substr(0, kv.find("="));
			string value = kv.substr(kv.find("=") + 1);

			row.insert(make_pair(key, value));
		}

		DATABASE->add(tablename, p, row);
		row.clear();
	}

	//GetPrivateProfileSectionNames()
}

void DataManager::saveDatabase(std::string tablename, const char* ini)
{
	Table* table = DATABASE->getTable(tablename);

	if (table == NULL) return;

	for (Table::iterator i = table->begin(); i != table->end(); i++)
	{
		for (Row::iterator rowIter = (*i)->begin(); rowIter != (*i)->end(); rowIter++)
		{
			if (rowIter->first == "key") continue;

			WritePrivateProfileString((*i)->find("key")->second.c_str(), rowIter->first.c_str(), rowIter->second.c_str(), ini);
		}
	}
}