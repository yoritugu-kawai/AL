#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include <ImGuiManager.h>
#include <WorldTransform.h>
#include <cassert>
void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	if (parent_) {
		matWorld_ *= parent_->matWorld_;
	}
	TransferMatrix();
}