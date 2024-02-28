#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "UiHud.h"
#include "Upgrade.h"
#include "TextGo.h"
SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{

}

void SceneGame::SetStatus(Status newStatus)
{
	currentStatus = newStatus;
	switch (currentStatus)
	{
	case SceneGame::Status::Title:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneGame::Status::Playing:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case SceneGame::Status::NextWave:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	case SceneGame::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);;
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
	return Utils::Clamp(point, rect);
}

void SceneGame::Init()
{
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ItemSpawner());

	for (auto s : spawners)
	{
		s->SetPosition({ 0.f, 0.f });
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	crosshair = new SpriteGo("Crosshair");
	crosshair->sortLayer = -1;
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->SetOrigin(Origins::MC);

	AddGo(crosshair, Scene::Layers::Ui);

	hud = new UiHud("Hud");
	AddGo(hud, Scene::Layers::Ui);

	upui = new Upgrade("UP");
	AddGo(upui, Scene::Layers::Ui);

	float textSize = 120.f;
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");

	/*overText = new TextGo("over");
	overText->Set(font, formatover, textSize, sf::Color::White);
	overText->SetPosition({ 1920 / 2.f , 1080 / 2.f });
	overText->SetOrigin(Origins::MC);
	AddGo(overText);*/


	LoadHiScore();

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition({ -1000.f, -1000.f });

	Scene::Enter();
	hud->SetScore(0);
	hud->SetHiScore(this->HiScore);
	hud->SetAmmo(20, 40);

	SetStatus(Status::Title);
	spawners[0]->SetActive(false);
	spawners[0]->Spawn(5);
	wave = 1;
	hud->SetWave(wave);
	hud->SetFps(0);
}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	hud->SetZombieCount(zombieList.size());

	Scene::Update(dt);

<<<<<<< HEAD
	timer += dt;
	++fpsCount;

	if (timer >= 1)
	{
		fps = fpsCount / timer;
		timer = 0;
		fpsCount = 0;
	}
	hud->SetFps(fps);

=======
>>>>>>> origin/Develop
	crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));

	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 2.f);
	worldView.setCenter(worldViewCenter);

	switch (currentStatus)
	{
	case SceneGame::Status::Title:
		if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
		{
			player->UpgradefireInterval(0.05f);
			upui->SetActive(false);
			SetStatus(Status::Playing);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
		{
			player->UpgradeSpeed(40.f);
			upui->SetActive(false);
			SetStatus(Status::Playing);
		}
		else if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
		{
			player->UpgradeMaxHp(25);
			upui->SetActive(false);
			SetStatus(Status::Playing);
		}
			
		break;
	case SceneGame::Status::Playing:
		if (zombieList.size() == 0)
		{
			SetStatus(Status::NextWave);
			upui->SetActive(true);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			player->OnDie();
			SetStatus(Status::GameOver);
		}
		if (player->GetHp() <= 0)
		{
			SetStatus(Status::GameOver);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Delete))
		{
			ZombieClear();
		}
		break;
	case SceneGame::Status::NextWave:
		SetStatus(Status::Title);
		hud->SetWave(++wave);
		spawners[0]->Spawn(5 * wave);
		break;
	case SceneGame::Status::GameOver:

		SCENE_MGR.ChangeScene(SceneIds::TitleScene);
		//SetStatus(Status::Title);
		
	}
}

void SceneGame::FixedUpdate(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::AddScore(int s)
{
	this->Score += s;
	hud->SetScore(this->Score);
}

void SceneGame::AddHiScore(int s)
{
	if (Score > HiScore)
	{
		this->HiScore = this->Score;
		hud->SetHiScore(this->HiScore);
		SaveHiScore();
	}
}

void SceneGame::SaveHiScore()
{
	std::ofstream file("HiScore.txt");
	if (file.is_open())
	{
		file << this->HiScore;
		file.close();
	}
}

void SceneGame::LoadHiScore()
{
	std::ifstream file("HiScore.txt");

	if (file.is_open())
	{
		file >> this->HiScore;
		file.close();
		hud->SetHiScore(this->HiScore);
	}
}

void SceneGame::ZombieClear()
{
	auto& list = GetZombieList();
	for (auto Go : list)
	{
		if (!Go->GetActive())
			continue;
		Zombie* zombie = dynamic_cast<Zombie*>(Go);
		if (zombie != nullptr)
		{
			zombie->OnDie();
		}
	}
}
