#ifndef CHERRY_H
#define CHERRY_H

#include "StaticGameEntity.h"
#include "Vector2f.h"

class oCherry : public StaticGameEntity
{
public:
	oCherry(Vector2f aPosition);
	~oCherry(void);
};

#endif // CHERRY_H