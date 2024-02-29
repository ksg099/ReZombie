#pragma once
#include "SpriteGo.h"

class Player;

class Item : public SpriteGo
{
public:
	enum class Types
	{
		None = -1,
		Ammo,
		Health,
		Count,
	};

	static Item* Create(Types t, int v);

protected:
	Types type = Types::None;
	int healvalue = 100;
	int ammovalue = 10;
	float duration = 5.f;
	float time = 0.f;
	Player* player = nullptr;

	Item(const std::string& name = "");

public:
	~Item() override = default;

	Types GetType() const { return type; }
	int GetAmmoValue() const { return ammovalue; }
	int GetHealValue() const { return healvalue; }


	void Reset() override;
	void FixedUpdate(float dt) override;
};

