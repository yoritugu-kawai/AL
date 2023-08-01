#pragma once
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include <ImGuiManager.h>
#include "ViewProjection.h"
#include"MyClass/math/ALL.h"
class RailCmamera {
public:

	void Initialize(const Vector3& worldPos, const Vector3& position);
	void Update();

	ViewProjection& GetViewProjection() { return viewProjection_; }
	WorldTransform& GetWorldTransform() { return worldTransform_; };

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};