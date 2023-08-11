#pragma once
class Enemy;

class IenemyState {
public:
	virtual void Update(Enemy*enemy)=0;


private:

};

