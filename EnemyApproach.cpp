#include "EnemyApproach.h"

void EnemySttatApproach::Update(Enemy* enemy) {

	enemy->SteTransfor(Add(enemy->GetWorldTransfom().translation_, enemy->GetVelocty()));
	if (enemy->GetWorldTransfom().translation_.z < 50.0f) {
	
		enemy->StateChnji(new EnemySttatLeave);

	}
}