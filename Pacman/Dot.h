#pragma once
#ifndef __DOT_H__
#define __DOT_H__

#include "GameObject.h"

class Dot : public GameObject
{
public:
	Dot(Sprite* spr, v2& pos, bool activate);
	~Dot() override;

	int Terminate() override;


protected:

private:


	bool m_Terminated = false;
};

#endif // !__DOT_H__