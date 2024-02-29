#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Item.h";
#include "UiHud.h"

Player::Player(const std::string& name)
	: SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = fireInterval;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	isFiring = false;
	fireTimer = fireInterval;

	hp = maxHp;
	sceneGame->GetHud()->SetHp(hp, maxHp);
	sceneGame->GetHud()->SetAmmo(currentAmmo, total);

	currentAmmo = maxAmmo;

	isAlive = true;
	isNoDamage = false;
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	look = mouseWorldPos - position;
	Utils::Normalize(look);

	SetRotation(Utils::Angle(look));

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;
	}

	fireTimer += dt;
	if (isFiring && fireTimer > fireInterval && currentAmmo > 0)
	{
		Fire();
		fireTimer = 0.f;
	}

	if (isNoDamage)
	{
		noDamageTimer += dt;
		if (noDamageTimer > noDamageTime)
		{
			isNoDamage = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	if (currentAmmo > 0)
	{
		Bullet* bullet = new Bullet();
		bullet->Init();
		bullet->Reset();
		bullet->SetPosition(position);
		bullet->Fire(look, bulletSpeed, bulletDamage);
		sceneGame->AddGo(bullet);

		SOUND_MGR.PlaySfx("sound/shoot.wav");
	
		currentAmmo--;
		sceneGame->GetHud()->SetAmmo(currentAmmo, total);
	}
	


}

void Player::OnDamage(int damage)
{
	if (!isAlive || isNoDamage)
		return;

	hp -= damage;
	sceneGame->GetHud()->SetHp(hp, maxHp);

	isNoDamage = true;
	noDamageTimer = 0.f;

	if (hp <= 0)
	{
		hp = 0;
		sceneGame->GetHud()->SetHp(hp, maxHp);

		OnDie();
	}
}

void Player::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
}

void Player::OnItem(Item* item)
{
	switch (item->GetType())
	{
	case Item::Types::Ammo:
		currentAmmo += item->GetAmmoValue();
		sceneGame->GetHud()->SetAmmo(currentAmmo, total);
		break;
	case Item::Types::Health:
		hp += item->GetHealValue();
		sceneGame->GetHud()->SetHp(hp, maxHp);
		break;
	}
}
