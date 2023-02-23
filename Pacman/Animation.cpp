#include "Animation.h"
#include "Sprite.h"

Animation::Animation(Sprite* spr, float& rate, bool& loop)
	: m_Sprite(spr)
{
	Init(rate, loop);
}

Animation::~Animation()
{
	if (!m_Terminated)
	{
		Terminate();
	}

}

int Animation::Init(float& rate, bool& loop)
{
	// Get the animation frames of a sprite
	DefineAnimationFrames(m_Sprite->GetSpriteData());

	// Animation data 
	m_LoopAnim = loop;					// loop the animation
	m_PlayAnim = true;					// False, unless explicitly changed
	m_FrameId = 0;						// the Id of the current frame
	m_ElapsedSec = 0;					// the duration the curent frame has been on the 
	m_RateSec = rate;					// play back speed
	m_StartFrame = 0;					// the Id of the first frame is always zero
	m_EndFrame = m_AnimFrames.size();	// the Id of the last frame is the size of the animation

	// Define the sprite rect
	m_Sprite->DefineTextureRect(&m_AnimFrames.at(m_FrameId));

	return retCode;
}

int Animation::Update(float& elapsedTime)
{
	if (!m_PlayAnim)
		return retCode;

	m_ElapsedSec += elapsedTime;

	if (m_Sprite->GetSpriteData()->Animated)
	{
		if (m_ElapsedSec > (1.f / m_RateSec))
		{
			m_ElapsedSec = 0;
			++m_FrameId;
			if (m_FrameId >= m_EndFrame)
			{
				if (m_LoopAnim)
					m_FrameId = m_StartFrame;
				else
				{
					m_FrameId = 0;
					m_Sprite->m_Active = false;
				}
			}
			m_Sprite->DefineTextureRect(&m_AnimFrames.at(m_FrameId));
		}
	}

	return retCode;
}

int Animation::Terminate()
{
	delete m_Sprite;
	m_AnimFrames.clear();

	m_Terminated = true;

	return retCode;
}

std::vector<RECTF>* Animation::GetAnimationFrames()
{
	return &m_AnimFrames;
}

int Animation::DefineAnimationFrames(SpriteData* sprData)
{
	// v2 (individual frame width, individual frame height) - individual size for animated sprite frame rects
	v2 iSize((sprData->Size.myX), (sprData->Size.myY));

	RECTF iRect;	// single Frame rect

	// For Every row in the grid
	for (size_t j = 0; j < sprData->Grid.myY; ++j)
	{
		iRect.y = sprData->TexRect.y + (iSize.myY * j);
		iRect.h = iSize.myY;

		// Set column grid rect as an animation frame
		for (size_t i = 0; i < sprData->Grid.myX; ++i)
		{
			iRect.x = sprData->TexRect.x + (iSize.myX * i);
			iRect.w = iSize.myX;

			// Add rect to the animations frame storage
			m_AnimFrames.emplace_back(iRect);
		}
	}

	return retCode;
}

int Animation::AddAnimationFrame(RECTF& frame)
{
	m_AnimFrames.emplace_back(frame);

	return retCode;
}

int Animation::PlayAnimation()
{
	m_PlayAnim = true;
	return retCode;
}

int Animation::StopAnimation()
{
	m_PlayAnim = false;
	return retCode;
}

int Animation::RestartAnimation()
{
	m_FrameId = 0;
	m_PlayAnim = true;

	return retCode;
}
