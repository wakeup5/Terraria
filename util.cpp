#include "stdafx.h"
#include "util.h"

namespace myUtil
{
	/**	getAngleByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 엇각?을 반환
	*/
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrtf(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0) angle = M_PI * 2 - angle;
		return angle;
	}

	/**	getDistanceByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 두 점사이의 거리를 반환
	*/
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float dx = endX - startX;
		float dy = endY - startY;

		return sqrt(dx * dx + dy * dy);
	}

	/**	getGradeRadianByTwoPoint
	@date	2015/06/01
	@brief	두개의 좌표를 받아 그 기울기의 라디안 각도를 반환
	*/
	float getGradeRadian(float x1, float y1, float x2, float y2)
	{
		//atan2는 시계방향 기준이므로 y축 반전이 필요하다.
		//return atan2(y1 - y2, x2 - x1);
		
		if (y1 > y2)
		{
			return atan2(y1 - y2, x2 - x1);
		}
		else
		{
			return 2 * M_PI - atan2(y2 - y1, x2 - x1);
		}
		
	}
	/**	getGradeDegreeByTwoPoint
	@date	2015/06/13
	@brief	두개의 좌표를 받아 그 기울기의 디그리 각도를 반환
	*/
	float getGradeDegree(float x1, float y1, float x2, float y2)
	{
		return degFromRad(getGradeRadian(x1, y1, x2, y2));
	}

	//라디안 각도를 디그리 각도로 변환
	float degFromRad(float radian)
	{
		return (radian / (2 * M_PI)) * 360;
	}
	//디그리 각도를 라디안 각도로 변환
	float radFromDeg(float degree)
	{
		return (degree / 360) * (2 * M_PI);
	}

	char* vectorArrayCombine(vector<string> vArray, const int size)
	{
		char* str = new char[size];

		for (int i = 0; i < vArray.size(); i++)
		{
			strncat_s(str, size, vArray[i].c_str(), size);
			if (i + 1 < vArray.size()) strncat_s(str, size, ",", size);
		}

		return str;
	}

	vector<string> charArraySeparation(const char charArray[], const char* separator)
	{
		vector<string> vArray;
		char* temp;
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

	POINT getRotatePoint(int x, int y, float angle)
	{
		POINT result;

		result.x = cos(angle) * x + sin(angle) * y;
		result.y = -sin(angle) * x + cos(angle) * y;

		return result;
	}

	POINT getRotatePoint(int cx, int cy, int x, int y, float angle)
	{
		POINT result;
		POINT temp;

		temp = getRotatePoint(x, y, angle);
		result.x = cx + temp.x;
		result.y = cy + temp.y;

		return result;
	}

	short sign(int num)
	{
		return (num > 0) - (num < 0);
	}

	bool existBit(UINT variable, UINT bit)
	{
		return (variable & bit) == bit;
	}

	HANDLE AddResourceFont(LPCTSTR ResID, DWORD *Installed)
	{
		if (Installed) *Installed = 0;

		HMODULE hMod = GetModuleHandle(NULL);
		DWORD Count, ErrorCode;

		HRSRC Resource = FindResource(hMod, ResID, RT_FONT); // or RT_FONT or whatever your actual resource type is
		if (!Resource)
		{
			ErrorCode = GetLastError();
			//...
			return NULL;
		}

		DWORD Length = SizeofResource(hMod, Resource);
		if ((Length == 0) && (GetLastError() != 0))
		{
			ErrorCode = GetLastError();
			//...
			return NULL;
		}

		HGLOBAL Address = LoadResource(hMod, Resource);
		if (!Address)
		{
			ErrorCode = GetLastError();
			//...
			return NULL;
		}

		PVOID FontData = LockResource(Address);
		if (!FontData)
		{
			ErrorCode = GetLastError();
			//...
			return NULL;
		}

		HANDLE Handle = AddFontMemResourceEx(FontData, Length, 0, &Count);
		if (!Handle)
		{
			ErrorCode = GetLastError();
			//...
			return NULL;
		}

		if (Installed) *Installed = Count;
		return Handle;
	}
}