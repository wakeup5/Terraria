#pragma once

#include <cmath>

#define DEG_TO_RAD		180 / M_PI

#define FLOAT_EPSILON	0.001f									//�÷� ���Ƿ�
#define FLOAT_TO_INT(f1) static_cast<int>(f1 * FLOAT_EPSILON)	//�Ǽ��� ���������� ��ȯ�Ѵ�
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)
//fabs�� �Ҽ��� ���� ���밪�� ��ȯ�Ѵ�

namespace myUtil
{
	/// �ΰ��� ��ǥ�� �޾� ����?�� ��ȯ
	float getAngle(float startX, float startY, float endX, float endY);

	/// �ΰ��� ��ǥ ������ �Ÿ��� ��ȯ
	float getDistance(float startX, float startY, float endX, float endY);

	/// �ΰ��� ��ǥ�� �޾� ������ ���� ������ ��ȯ
	float getGradeRadian(float x1, float y1, float x2, float y2);
	float getGradeDegree(float x1, float y1, float x2, float y2);

	//���� ������ ��׸� ������ ��ȯ
	float degFromRad(float radian);
	//��׸� ������ ���� ������ ��ȯ
	float radFromDeg(float degree);

	char* vectorArrayCombine(vector<string> vArray, const int size);
	vector<string> charArraySeparation(const char charArray[], const char* separator = " ,/(&%#@");

	POINT getRotatePoint(int x, int y, float angle);
	POINT getRotatePoint(int cx, int cy, int x, int y, float angle);

	short sign(int num);

	bool existBit(UINT variable, UINT bit);

	HANDLE AddResourceFont(LPCTSTR ResID, DWORD *Installed);


}