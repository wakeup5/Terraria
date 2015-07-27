#pragma once
#include "common.h"

namespace Terraria
{
	class Node
	{
	private:
		
	public:
		virtual HRESULT initialize(){ return S_OK; }
		virtual void release(){ }
		virtual void update(){ }
		virtual void render(HDC hdc){ }

		Node(){}
		virtual ~Node(){}
	};
}
