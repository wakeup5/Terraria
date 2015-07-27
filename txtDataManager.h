#pragma once

#include "Singletonbase.h"
#include <vector>

using namespace std;

class txtDataManager : public SingletonBase <txtDataManager>
{
public:
	HRESULT init(void);
	void release(void);

	//���̺�~~
	void txtSave(const char* saveFileName, vector<string> vStr, const int size);
	void txtSave(const char* saveFileName, const char* contents, const int size);
	char* vectorArrayCombine(vector<string> vArray, const int size);

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(const char charArray[]);	

	txtDataManager(void);
	~txtDataManager(void);
};
