#include "Animation.h"
#include "Skeleton.h"

bool Animation::Load(const std::string& fileName)
{
    return false;
}

void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime) const
{
    if (outPoses.size() != mNumBones)
    {
        outPoses.resize(mNumBones);
    }

    // Figure out the current frame index and next frame
    // (This assumes inTime is bounded by [0, AnimDuration]
    size_t frame = static_cast<size_t>(inTime / mFrameDuration);
    size_t nextFrame = frame + 1;
    // Calculate fractional value between frame and next frame
    float pct = inTime / mFrameDuration - frame;

    // Setup the pose for the root
    if (mTracks[0].size() > 0)
    {
        // Interpolate between the current frame's pose and the next frame
        BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
            mTracks[0][nextFrame], pct);
        outPoses[0] = interp.ToMatrix();
    }
    else
    {
        outPoses[0] = Matrix4::Identity;
    }

    const std::vector<Skeleton::Bone>& bones = inSkeleton->GetBones();
    // Now setup the poses for the rest
    for (size_t bone = 1; bone < mNumBones; bone++)
    {
        Matrix4 localMat; // (Defaults to identity)
        if (mTracks[bone].size() > 0)
        {
            BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
                mTracks[bone][nextFrame], pct);
            localMat = interp.ToMatrix();
        }
        outPoses[bone] = localMat * outPoses[bones[bone].mParent];
    }
}
