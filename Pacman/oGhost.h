#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"

class World;
class PathmapTile;

class oGhost : public MovableGameEntity
{
public:
	oGhost(const Vector2f& aPosition);
	~oGhost(void);

	void Update(float aTime, World* aWorld);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void SetImage(const char* anImage);

	void Die(World* aWorld);

	void Draw(Drawer* aDrawer);

protected:

	int myDesiredMovementX;
	int myDesiredMovementY;

	std::list<PathmapTile*> myPath;

};

#endif // GHOST_H