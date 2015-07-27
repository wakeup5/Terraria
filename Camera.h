#pragma once
#include "TerrariaNode.h"
namespace Terraria
{
	class Camera
	{
	private:
		float _x;
		float _y;

	public:
		void setX(float x){ _x = x; }
		void setY(float y){ _y = y; }

		float getX(){ return _x; }
		float getY(){ return _y; }

		Camera();
		virtual ~Camera();
	};
}