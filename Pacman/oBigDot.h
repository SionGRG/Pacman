#ifndef BIGDOT_H
#define BIGDOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class oBigDot : public StaticGameEntity
{
public:
	oBigDot(Vector2f aPosition);
	~oBigDot(void);
};

#endif // BIGDOT_H