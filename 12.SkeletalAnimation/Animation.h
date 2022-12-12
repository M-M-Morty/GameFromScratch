#pragma once
#include <vector>
#include <string>

#include "BoneTransform.h"

class Animation
{
public:
	bool Load(const std::string& fileName);

	size_t GetNumBones() const { return mNumBones; }
	size_t GetNumFrames() const { return mNumFrames; }
	float GetDuration() const { return mDuration; }
	float GetFrameDuration() const { return mFrameDuration; }

	// Fills the provided vector with the global (current) pose matrices for each
	// bone at the specified time in the animation. It is expected that the time
	// is >= 0.0f and <= mDuration
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;
private:
	size_t mNumBones;
	size_t mNumFrames;
	float mDuration;
	float mFrameDuration;
	// Transform information for each frame for each bone(track)
	// Each index in the outer vector is a bone, inner vector is a frame
	std::vector<std::vector<BoneTransform>> mTracks;
};
