#include "pch.h"
#include "ItemSpawner.h"

ItemSpawner::ItemSpawner(const std::string& name)
    : Spawner(name)
{
}

GameObject* ItemSpawner::Create()
{
    Item::Types itemType = (Item::Types)Utils::RandomRange(0, itemTypes.size());
    int value = 0;
    switch (itemType)
    {
    case Item::Types::Ammo:
        value = 10;
        break;
    case Item::Types::Health:
        value = 50;
        break;
    }
    return Item::Create(itemType, value);
}

void ItemSpawner::Reset()
{
    itemTypes.clear();

    itemTypes.push_back(Item::Types::Ammo);
    itemTypes.push_back(Item::Types::Health);

    Spawner::Reset();

    interval = 5.f;
    spawnCount = 1;
    radius = 500.f;
}
