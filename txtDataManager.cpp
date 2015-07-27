#include "StdAfx.h"
#include "txtDataManager.h"

txtDataManager::txtDataManager(void)
{
}

txtDataManager::~txtDataManager(void)
{
}

HRESULT txtDataManager::init(void)
{
	return S_OK;
}

void txtDataManager::release(void)
{

}

//세이브
void txtDataManager::txtSave(const char* saveFileName, vector<string> vStr, const int size)
{
	HANDLE file;
	char* str = new char[size];
	DWORD write;

	strncpy_s(str, size, vectorArrayCombine(vStr, size), size);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}


void txtDataManager::txtSave(const char* saveFileName, const char* contents, const int size)
{
	HANDLE file;
	char* str = new char[size];
	DWORD write;

	strncpy_s(str, size, contents, size);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}


char* txtDataManager::vectorArrayCombine(vector<string> vArray, const int size)
{
	char* str = new char[size];

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, size, vArray[i].c_str(), size);
		if (i + 1 < vArray.size()) strncat_s(str, size, ",", size);
	}

	return str;
}



//로드
vector<string> txtDataManager::txtLoad(const char* loadFileName)
{
	HANDLE file;
	char str[300];
	DWORD read;

	memset(str, 0, 300);
	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 300, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtDataManager::charArraySeparation(const char charArray[])
{
	vector<string> vArray;
	char* temp;
	char* separator = " ,/(&%#@";
	char* token;
	char* tempCharArray = new char[strlen(charArray)];

	//strlen(charArray);

	strcpy_s(tempCharArray, strlen(charArray) + 1, charArray);

	token = strtok_s(tempCharArray, separator, &temp);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	return vArray;
}