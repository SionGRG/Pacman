#ifndef DOT_H
#define DOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class oDot : public StaticGameEntity
{
public:
	oDot(Vector2f aPosition);
	~oDot(void);
};

#endif // DOT_H