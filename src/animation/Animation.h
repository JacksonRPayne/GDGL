#pragma once
#include <vector>
#include "graphics/Texture.h"
#include <iostream>
#include "Animator.h"
#define MIN_PLAY_SPEED  0.01f

class Animator;
struct AnimationData;

struct Frame {
	Frame(const SubTexture &subTex) : subTexture(subTex){}
	SubTexture subTexture;
};

class Animation
{
public:
	Animation();
	Animation(const std::vector<Frame> &frames, float playSpeed);
	Animation(const Animation& other);
	Animation& operator=(const Animation& other);
	~Animation(){}

	// Getters
	float GetPlaySpeed() { return playSpeed; }
	const std::vector<Frame>& GetFrames() { return frames; }
	const Frame& GetCurrentFrame(AnimationData* data);
	// Setters
	void SetPlaySpeed(float speed) { playSpeed = speed > MIN_PLAY_SPEED ? speed : MIN_PLAY_SPEED; }
	void SetFrames(const std::vector<Frame>& newFrames) { frames = newFrames; }
	void AddFrame(const Frame &frame) { frames.push_back(frame); }

	// Updates the internal clock of the animation
	void Update(float dt, AnimationData* data);
	void Play(AnimationData* data);
	void Stop(AnimationData* data);

	std::string name;

private:
	// The speed at which each frame goes by
	float playSpeed;
	std::vector<Frame> frames;
	// Called at the end of the animation, either loops it again or ends it
	void AnimationEnd(AnimationData* data);
};

