#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"

class oAvatar : public MovableGameEntity
{
public:
	oAvatar(const Vector2f& aPosition);
	~oAvatar(void);

	void Update(float aTime);

private:


};

#endif //AVATAR_H