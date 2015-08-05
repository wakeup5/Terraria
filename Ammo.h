#pragma once
#include "TerrariaNode.h"
#include "Physical.h"
#include <list>

namespace Terraria
{
	typedef std::list<Object*> lAmmo;
	typedef lAmmo::iterator liAmmo;

	class Arrow : public Physical
	{
	private:
		Image* _image;
	public:
		HRESULT initialize();
		void release();
		void update();
		void render(HDC hdc);

		Arrow(){}
		virtual ~Arrow(){}
	};

	class Bullet : public Physical
	{
	private:
		Image* _image;
	public:
		HRESULT initialize();
		void release();
		void update();
		void render(HDC hdc);

		Bullet(){}
		virtual ~Bullet(){}
	};

	class Ammo : public Node
	{
	private:
		lAmmo _lAmmo;
		int _max;
	public:
		HRESULT initialize(int max);
		void release();
		void update();
		void render(HDC hdc);

		void fireArrow(float x, float y, float angle, float speed);
		void fireBullet(float x, float y, float angle, float speed);

		void removeFirst();

		lAmmo* getAmmo(){ return &_lAmmo; }

		Ammo(){}
		virtual ~Ammo(){}
	};
}