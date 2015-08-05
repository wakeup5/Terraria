#pragma once
#include <vector>
#include "TerrariaNode.h"
#include "TEffect.h"

namespace Terraria
{
	typedef std::vector<TEffect*> vEffect;
	typedef vEffect::iterator viEffect;

	class TEffectManager : public SingletonBase < TEffectManager >
	{
	private:
		int _max;

		vEffect _vEffect;
	public:
		HRESULT initialize(int max);
		void release();
		void update();
		void render(HDC hdc);

		void createEffect(float x, float y, float angle, float speed, std::string imageName, int frameX, int frameY, float lifeTime, bool isTileCollision, bool isGravity);

		void createEffects(float x, float y, int amount, float playerAngle, float speed, std::string imageName, int frameX, int frameY, float lifeTime, bool isGravity);

		TEffectManager();
		virtual ~TEffectManager();
	};
}