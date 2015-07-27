#pragma once
#include <map>
#include <string>

namespace Terraria
{
	class Background : public SingletonBase< Terraria::Background >
	{
	private:
		typedef struct tagBgSet
		{
			Image* bg;
			Image* hear;
			Image* that;
			Image* there;
			float height;
		} BgSet;

		std::map<std::string, BgSet> _bgMap;
		std::map<std::string, BgSet>::iterator _bgMapIter;

		Image* _bgSky;
		BgSet _select;
	public:
		HRESULT initailize();
		void render(HDC hdc);

		void change(std::string key);
		void change(std::string key, float offset, float min, float max);

		Background();
		virtual ~Background();
	};
}