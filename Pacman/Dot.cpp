#include "Dot.h"
#include "Sprite.h"

Dot::Dot(Sprite* spr, v2& pos, bool activate)
{
	m_Active = activate;
	m_Pos = pos;
	Init(spr);
}

Dot::~Dot()
{
	if (!m_Terminated)
		Terminate();
}


int Dot::Terminate()
{

	m_Terminated = true;
	return retCode;
}
