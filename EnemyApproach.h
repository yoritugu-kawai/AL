#pragma once
#include"IEnemySetat.h"
#include"MyClass/chara/Enemy.h"
#include"Vector3.h"
#include"EnemyLeaveh.h"
class EnemySttatApproach : public IenemyState {
public:
	void Update(Enemy*enemy)override;

private:
	
};

