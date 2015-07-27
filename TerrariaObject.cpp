#include "stdafx.h"
#include "TerrariaObject.h"

using namespace std;

namespace Terraria
{
	Object::Object()
	{

	}

	Object::~Object()
	{

	}

	string Object::toString()
	{
		char result[9] = { '\0' };

		sprintf_s(result, "%p", this);

		return string(result);
	}
}
