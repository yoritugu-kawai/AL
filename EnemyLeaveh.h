#pragma once
#include "IEnemySetat.h"
#include "MyClass/chara/Enemy.h"
#include "Vector3.h"
class EnemySttatLeave : public IenemyState {
public:
	void Update(Enemy* enemy) override;

private:
	Vector3 versti{-1,1,-1};
};
