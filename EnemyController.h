#pragma once
#include "Component.h"

class Enemy;

class EnemyController :
	public Component
{
private:

public:

	// SoldierType:: 
	Enemy* SpawnEnemy(Vector3 position, int soldierType);


private:
	inline static EnemyController* g_pMainEnemyController = nullptr;
	inline static int g_iEnemyUnitCount = 0;

public:

	static EnemyController* GetMain() { return g_pMainEnemyController; }
	static int GetEnemyUnitCount() { return g_iEnemyUnitCount; }

	static void AddUnit() { g_iEnemyUnitCount++; }
	static void RemoveUnit() { g_iEnemyUnitCount--; }
};

