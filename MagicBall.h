#pragma once
#include "Physical.h"
#include "TEffectManager.h"
#include "TerrariaUnit.h"
//#include "MonsterManager.h"

namespace Terraria
{
	typedef list<class MBall*> lMagic;
	typedef set<Unit*> sUnit;

	class MonsterManager;
	class MBall : public Physical
	{
	protected:
		float _effectTime;
		float _time;
		float _lifeTime;

		sUnit _unit;

		string _effectName;

		int _clearTime;
	public:
		HRESULT initialize(){ return S_OK; }
		virtual HRESULT initialize(float lifeTime, float effectTime);
		virtual void release();
		virtual void update();
		virtual void render(HDC hdc);

		bool isLive(){ return _lifeTime >= 0; }

		bool isPass(Unit* unit);

		MBall();
		virtual ~MBall();
	};

	class Water : public MBall
	{
	public:
		HRESULT initialize(float lifeTime, float effectTime);
		void update();

		Water();
		~Water();
	};

	class GreenBall : public MBall
	{
	public:
		HRESULT initialize(float lifeTime, float effectTime);
		void update();

		GreenBall(){}
		~GreenBall(){}
	};

	class MagicBullet : public MBall
	{
	private:
		enum DIRECT
		{
			L, R, D
		};
		float _x;
		float _y;

		//float _clearTime;
	public:
		HRESULT initialize(float lifeTime, float effectTime, float x, float y);
		void update();

		MagicBullet(){}
		~MagicBullet(){}
	};

	class MagicBall : public Node
	{
	private:
		lMagic _lMagic;

		int _max;
	public:
		HRESULT initialize(int max);
		void release();
		void update();
		void render(HDC hdc);

		void shoot(float x, float y, float angle, float accel, float speed);
		void shootWater(float x, float y, float angle, float accel, float speed);
		void shootGreenball(float startX, float startY, float endX, float endY, float accel, float speed);
		void shootFire(float startX, float startY, float endX, float endY, float accel, float speed);

		lMagic* getMagicBall(){ return &_lMagic; }

		bool collisionMonster(MonsterManager* mm, int damage);

		MagicBall();
		virtual ~MagicBall();
	};
}