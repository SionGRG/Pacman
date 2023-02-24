#include "BigDot.h"
#include "Sprite.h"

BigDot::BigDot(Sprite* spr, v2& pos, bool activate)
{
	m_Active = activate;
	m_Pos = pos;
	Init(spr);
}

BigDot::~BigDot()
{
	if (!m_Terminated)
		Terminate();
}


int BigDot::Terminate()
{

	m_Terminated = true;
	return retCode;
}
