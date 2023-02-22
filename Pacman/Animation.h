#pragma once
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "DataStructures.h"

/*
	An animation class for 2D sprite animations
*/

class Animation
{
public:
	Animation(Sprite* spr, float& rate, bool& loop);
	~Animation();

	int Init(float& rate, bool& loop);
	int Update(float& elapsedTime);
	int Terminate();

	std::vector<RECTF>* GetAnimationFrames();

	int DefineAnimationFrames(SpriteData* sprData);
	int AddAnimationFrame(RECTF& frame);
	int PlayAnimation();
	int StopAnimation();
	int RestartAnimation();

private:

	Sprite* m_Sprite;
	std::vector<RECTF> m_AnimFrames;

	// Animation data
	bool m_PlayAnim;
	bool m_LoopAnim;
	float m_RateSec;			// play back speed
	float m_ElapsedSec;			// the duration the curent frame has been on the screen
	int	m_FrameId;				// the Id of the current frame
	int	m_StartFrame;			// the Id of the first frame
	int	m_EndFrame;				// the Id of the last frame

	// Terminations checks
	bool m_Terminated = false;
};


#endif // !__ANIMATION_H__