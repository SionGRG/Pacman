#pragma once
#ifndef __BIGDOT_H
#define __BIGDOT_H

#include "GameObject.h"

class BigDot : public GameObject
{
public:
	BigDot(Sprite* spr, v2& pos, bool activate);
	~BigDot() override;

	int Terminate() override;


protected:

private:


	bool m_Terminated = false;
};

#endif // !__BIGDOT_H