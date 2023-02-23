#include "oAvatar.h"

oAvatar::oAvatar(const Vector2f& aPosition)
: MovableGameEntity(aPosition, "open_32.png")
{

}

oAvatar::~oAvatar(void)
{
}

void oAvatar::Update(float aTime)
{
	int tileSize = 22;

	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;

	float distanceToMove = aTime * 30.f;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
}
