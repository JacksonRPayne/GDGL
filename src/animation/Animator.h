#pragma once
#include "Animation.h"
#include <map>
#include <unordered_map>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>
#include "system/Log.h"

class Animation;
struct Frame;

class Animator {
	
public:
	//TODO: Review this and animation class, document more and clean up
	Animator();
	Animator& operator=(const Animator& a);
	Animator(const Animator& other);
	~Animator() {};
	void AddAnimation(const std::string name, Animation animation);
	void Update(float dt);
	void PlayAnimation(const std::string& animation, bool looping, bool interruptible);
	// Plays the animation only if it's not already playing
	// The preffered method to call
	void PlayOnce(const std::string& animation, bool looping, bool interruptible); // TODO: the worst name ever pls change API

	bool PlayingAnimation() { return playingAnimation; }

	const Frame& GetCurrentFrame();

private:
	// Map of animations to their name
	std::unordered_map<std::string, Animation> animMap;
	// Stores animations on deck to be played
	// If one animation is not interruptable, the next
	// will play when it's finished.
	std::queue<std::string> animQueue;
	Animation* currentAnimation;
	bool playingAnimation;
	bool interruptible;
	// Invoked at end of animation
	void AnimEndCallback();
	void ActivateAnimation(Animation* animation, bool interruptible);
};
