#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>
#include "Animation.h"
#include "system/Log.h"

class Animation;
struct Frame;

struct AnimationData {
	AnimationData() : currentFrame(0), playTime(0.0f), playing(false), looping(false), interruptible(true) {}
	int currentFrame;
	float playTime;
	bool playing;
	bool looping;
	bool interruptible;
};

class Animator {
	
public:
	Animator();
	// Copy
	Animator& operator=(const Animator& other);
	Animator(const Animator& other);
	// Move
	Animator(Animator&& other) noexcept;
	Animator& operator=(Animator&& other) noexcept;

	~Animator() {};

	void AddAnimation(const std::string &name, Animation* animation);
	void Update(float dt);
	void PlayAnimation(const std::string& animation, bool looping, bool interruptible);
	// Plays the animation only if it's not already playing
	// The preffered method to call
	void PlayOnce(const std::string& animation, bool looping, bool interruptible); // TODO: the worst name ever pls change API
	bool PlayingAnimation() { return playingAnimation; }
	// Invoked at end of animation
	void AnimEndCallback();
	const Frame& GetCurrentFrame();

private:
	AnimationData animationData;
	// Map of animations to their name
	std::unordered_map<std::string, Animation*> animMap;
	// Stores animations on deck to be played. If one animation is not interruptable, the next will play when it's finished.
	// TODO: you're gonna have to add animationdata for each animation
	std::queue<std::string> animQueue;
	Animation* currentAnimation;

	bool playingAnimation;
	// TODO: delete
	bool interruptible;

	void ActivateAnimation(Animation* animation, bool interruptible);
};
