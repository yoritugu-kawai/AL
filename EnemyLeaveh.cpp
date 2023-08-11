#include "EnemyLeaveh.h"

void EnemySttatLeave::Update(Enemy* enemy) {
	enemy->SteTransfor(Add(enemy->GetWorldTransfom().translation_, versti));

	//worldTransform_.translation_.x -= 0.1f;
	//worldTransform_.translation_.y += 0.1f;

	/*tim++;
	if (tim >= 60) {
		Fire();
		tim = 0;
	}*/
}