#include "DXUT.h"
#include "FireAttack.h"

#include "Bullet.h"

void FireAttack::Attack(int damage, float bulletSpeed, Vector3 start, Vector3 direction, Tag targetTag)
{
	Actor* pBullet = ACTOR.Create(TagType::Effect, 4);
	pBullet->transform->Position = start;
	pBullet->AddComponent<Bullet>()->Set(direction, bulletSpeed, targetTag, damage);
	pBullet->renderer->ChangeSprite(Sprite::Find("bullet")->Get(1));
}
