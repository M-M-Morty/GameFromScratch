#pragma once
#include "CameraComponent.h"
#include <vector>

struct Spline
{
	// 曲线的控制点
	// 需要n+2个控制点
	std::vector<Vector3> mControlPoints;
	// Given spline segment where startIdx = P1,
	// compute position based on t value
	Vector3 Compute(size_t startIdx, float t) const;
	// Returns number of control points
	size_t GetNumPoints() const { return mControlPoints.size(); }
};

class SplineCamera :public CameraComponent
{
public:
	SplineCamera(class Actor* owner);

	void Update(float deltaTime) override;
	// Restart the spline
	void Restart();

	void SetSpeed(float speed) { mSpeed = speed; }
	void SetSpline(const Spline& spline) { mPath = spline; }
	void SetPaused(bool pause) { mPaused = pause; }
private:
	Spline mPath;

	size_t mIndex;
	float mT;

	float mSpeed;
	bool mPaused;
};
