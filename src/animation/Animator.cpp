#include "Animator.h"

Animator::Animator() : animMap(), animQueue(), currentAnimation(), playingAnimation(false),
interruptible(true), animationData() {}

Animator& Animator::operator=(const Animator& other) 
{
	std::cout << "Animator assigned" << "\n";
	// Deep copies maps
	this->animMap = std::unordered_map<std::string, Animation*>(other.animMap);
	this->animQueue = std::queue<std::string>(other.animQueue);
	this->currentAnimation = nullptr;
	this->playingAnimation = false;
	this->interruptible = true;
	this->animationData = other.animationData;
	this->currentAnimation = other.currentAnimation;

	return *this;
}

Animator::Animator(const Animator& other) {
	std::cout << "Animator copied" << "\n";
	// Deep copies maps
	this->animMap = std::unordered_map<std::string, Animation*>(other.animMap);
	this->animQueue = std::queue<std::string>(other.animQueue);
	this->currentAnimation = nullptr;
	this->playingAnimation = false;
	this->interruptible = true;
	this->animationData = other.animationData;
	this->currentAnimation = other.currentAnimation;

}

Animator::Animator(Animator&& other) noexcept{
	std::cout << "Animator move constructor" << "\n";
	// Moves maps
	this->animMap = std::move(other.animMap);
	this->animQueue = std::move(other.animQueue);
	this->currentAnimation = nullptr;
	this->playingAnimation = false;
	this->interruptible = true;
	this->animationData = other.animationData;
	this->currentAnimation = other.currentAnimation;

}

Animator& Animator::operator=(Animator&& other) noexcept {
	std::cout << "Animator move constructor" << "\n";
	if (this != &other) {
		// Moves maps
		this->animMap = std::move(other.animMap);
		this->animQueue = std::move(other.animQueue);
		this->currentAnimation = nullptr;
		this->playingAnimation = false;
		this->interruptible = true;
		this->animationData = other.animationData;
		this->currentAnimation = other.currentAnimation;
	}
	
	return *this;
}

void Animator::AnimEndCallback() {
	interruptible = true;
	// No queued animations
	if (animQueue.empty()) {
		playingAnimation = false;
		return;
	}
	/* TODO: Play top member of animation queue
	Animation* queuedAnim = animMap[animQueue.front()];
	ActivateAnimation(queuedAnim, queuedAnim->Interruptible());
	animQueue.pop();*/
}


void Animator::AddAnimation(const std::string &name, Animation* animation) {
	animation->name = name;
	animMap[name] = animation;
}

void Animator::PlayOnce(const std::string& animation, bool looping, bool interruptible) {
	// Only plays if not currently playing
	if (!currentAnimation || currentAnimation->name != animation) PlayAnimation(animation, looping, interruptible);
}

void Animator::PlayAnimation(const std::string& animation, bool looping=false, bool interruptible=true) {
	if (looping && !interruptible) {
		std::stringstream msg;
		msg << "animation " << animation << " is looping and uninterruptable";
		Log::LogWarning(msg.str());
	}
	// Animation doesn't exist in the map
	if (animMap.find(animation) == animMap.end()) {
		std::stringstream msg;
		msg << "could not find animation: " << animation;
		Log::LogError(msg.str());
		return;
	}
	// Set animation properties
	Animation* anim = (animMap[animation]);
	/*anim->SetLooping(looping);
	anim->SetInterruptible(interruptible);*/
	// An uninterruptible animation is playing
	animationData.looping = looping;
	animationData.interruptible = interruptible;
	/*TODO
	if (playingAnimation && !this->interruptible) {
        animQueue.push(animation);
		return;
	}*/

	// An interuptible animation is playing -- stop it
	if (playingAnimation) currentAnimation->Stop(&animationData);

	ActivateAnimation(anim, interruptible);
}

void Animator::ActivateAnimation(Animation* animation, bool interruptible) {
	// Activate the animation
	playingAnimation = true;
	currentAnimation = animation;
	this->interruptible = interruptible;
	animation->Play(&animationData);
}


void Animator::Update(float dt) {
	currentAnimation->Update(dt, &animationData);
}

const Frame& Animator::GetCurrentFrame() { return currentAnimation->GetCurrentFrame(&animationData); }
