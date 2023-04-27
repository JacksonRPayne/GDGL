#pragma once
#include <vector>
#include "graphics/Texture.h"
#include <iostream>
#include "Animator.h"
#define MIN_PLAY_SPEED  0.01f

class Animator;

struct Frame {
	Frame(SubTexture subTex) : subTexture(subTex){}
	SubTexture subTexture;
};

class Animation
{
public:
	// TODO: add name member? less map accesses
	Animation();
	Animation(const std::vector<Frame> &frames, float playSpeed);

	// Getters
	float GetPlaySpeed() { return playSpeed; }
	const std::vector<Frame>& GetFrames() { return frames; }
	const Frame& GetCurrentFrame() { return frames[currentFrame]; }
	bool Playing() { return playing; }
	bool Loops() { return looping; }
	bool Interruptible()  { return interruptible; }
	// Setters
	void SetPlaySpeed(float speed) { playSpeed = speed > MIN_PLAY_SPEED ? speed : MIN_PLAY_SPEED; }
	void SetFrames(const std::vector<Frame>& newFrames) { frames = newFrames; }
	void AddFrame(const Frame &frame) { frames.push_back(frame); }
	void SetLooping(bool shouldLoop) { looping = shouldLoop; }
	void SetInterruptible(bool inter) { interruptible = inter; }
	void SetAnimEndCallback(void (Animator::*func)()) { animEndCallback = func; }
	void SetAnimator(Animator* anim) { animator = anim; }

	// Updates the internal clock of the animation
	void Update(float dt);
	void Play();
	void Stop();

private:
	// The speed at which each frame goes by
	float playSpeed;
	std::vector<Frame> frames;
	// Stores the index of the frame in the vector
	int currentFrame;
	float playTime;
	bool playing;
	bool looping;
	bool interruptible;
	// The calling animator
	Animator* animator;
	// Called at the end of the animation, either loops it again or ends it
	void AnimationEnd();
	// Function pointer to function that should be called when animation ends (set automatically by animator)
	void (Animator::*animEndCallback)();

};

