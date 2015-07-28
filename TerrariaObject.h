#pragma once
#include <string>
#include "TerrariaNode.h"

namespace Terraria
{
	/**
	테라리아의 모든 오브젝트의 기본 클래스
	*/
	class Object : public Node
	{
	private:
		float _x;
		float _y;

		int _width;
		int _height;

		RECT _rc;

	public:
		virtual HRESULT initialize() = 0;
		virtual void release() = 0;
		virtual void update() = 0;
		virtual void render(HDC hdc) = 0;

		virtual std::string toString();

		inline float getX(){ return _x; }
		inline float getY(){ return _y; }
		inline void setX(float x){ _x = x; updateRect(); }
		inline void setY(float y){ _y = y; updateRect(); }
		inline void setCenter(float x, float y){ setX(x); setY(y); }

		inline int getWidth(){ return _width; }
		inline int getHeight(){ return _height; }
		inline void setWidth(int width){ _width = width; updateRect(); }
		inline void setHeight(int height){ _height = height; updateRect(); }
		inline void setSize(int width, int height) { setWidth(width); setHeight(height); }

	protected:
		inline void updateRect(){ _rc = makeRectCenter(_x, _y, _width, _height); }

	public:
		inline RECT getRect(){ return _rc; }

		Object();
		virtual ~Object();
	};
}

