#pragma once
#include "Spawner.h"
#include "Item.h"

class ItemSpawner : public Spawner
{
protected:
	std::vector<Item::Types> itemTypes;

public:
	ItemSpawner(const std::string& name = "");
	~ItemSpawner() = default;

	GameObject* Create() override;

	void Reset() override;
};

