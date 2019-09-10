#include "DXUT.h"
#include "BulletAttack.h"

#include "Bullet.h"

void BulletAttack::Attack(int damage, float bulletSpeed, Vector3 start, Vector3 direction, Tag targetTag)
{
	SoundSource::Load("gun-gunshot-01", L"Sound/gun-gunshot-01.wav")->DuplicatePlay();

	Actor* pBullet = ACTOR.Create(TagType::Effect, 4);
	pBullet->transform->Position = start;
	pBullet->AddComponent<Bullet>()->Set(direction, bulletSpeed, targetTag, damage);
}
