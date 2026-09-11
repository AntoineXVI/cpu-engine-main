#include "pch.h"
#include "Rail.h"

App::App()
{
	s_pApp = this;
	CPU_CALLBACK_START(OnStart);
	CPU_CALLBACK_UPDATE(OnUpdate);
	CPU_CALLBACK_EXIT(OnExit);
	CPU_CALLBACK_RENDER(OnRender);

}

App::~App()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void App::OnStart()
{	
	XMFLOAT2 posPlayerInit;
	posPlayerInit.x = 2.f;
	posPlayerInit.y = 0.f;

	XMFLOAT2 posEnemyInit = GetRandPos();
	actor_manager.AddPlayer(posPlayerInit);

	actor_manager.AddRail();

	actor_manager.AddEnemy(posEnemyInit);

	//camera 
	cpuEngine.GetCamera()->transform.pos.z = -5.0f;
	cpuEngine.GetCamera()->transform.pos.y = 1.5f;

	cpuEngine.GetCamera()->transform.SetYPR(0.f, 0.1f, 0.f);

	//font
	m_font.Create(cpuDevice.GetHeight() <= 512 ? 14 : 28);
	m_totalScore = 0;

	m_endGame = false;

	m_appFSM = cpuEngine.CreateFSM(this);
	m_appFSM->Add<StateAppInGame>("In Game");
	m_appFSM->Add<StateAppPause>("Pause");
	m_appFSM->Add<StateAppEnd>("End");

	this->GetFSM()->ToState(CPU_ID(StateAppInGame));
}

void App::OnUpdate()
{

	#ifdef _DEBUG
	if (cpuInput.IsDown())
	{
		Actor_Manager::GetInstance().ChangeEnemiesSpeed(0.05f);
	}
	if (cpuInput.IsDownReleased())
	{
		Actor_Manager::GetInstance().ResetEnemiesSpeed();
	}
	#endif
}

void App::OnExit()
{
	
}


void App::OnRender(int pass)
{
	switch (pass)
	{
		case CPU_PASS_PARTICLE_BEGIN:
		{
			// Blur particles
			//cpuEngine.SetRT(m_rts[0]);
			//cpuEngine.ClearColor();
			break;
		}
		case CPU_PASS_PARTICLE_END:
		{
			// Blur particles
			//cpuEngine.Blur(10);
			//cpuEngine.SetMainRT();
			//cpuEngine.AlphaBlend(m_rts[0]);
			break;
		}
		case CPU_PASS_UI_END:
		{
			if (m_endGame) 
			{
				EndGame();
			}
			
			#ifdef _DEBUG
			Player* m_player = actor_manager.GetPlayer();
			std::string states;
			states += "States:";
			states += "\nPlayer: ";
			states += m_player->GetFSM()->GetName(m_player->GetFSM()->state);

			states += "\nGame: ";
			states += this->GetFSM()->GetName(this->GetFSM()->state);
			states += "\nNombre d'enemies: ";
			states += CPU_STR(actor_manager.GetNumberEnemies()).c_str();


			XMFLOAT3 tintDebug = { 1.0f, 1.0f, 0.8f };
			cpuDevice.DrawText(&m_font, states.c_str(), (int)(cpuDevice.GetWidth() * 0.5f), 10, CPU_TEXT_CENTER, &tintDebug);
			#endif 

			m_totalScore = actor_manager.GetScore();
			
			std::string info;
			info += "Score: ";
			info += CPU_STR(m_totalScore).c_str();

			XMFLOAT3 tint = { 1.0f, 1.0f, 0.8f };
			cpuDevice.DrawText(&m_font, info.c_str(), 0, 10, CPU_TEXT_LEFT, &tint);


			break;
		}
	}
}

void App::MyPixelShader(cpu_ps_io& io)
{
	io.color = io.p.color;
}

XMFLOAT2 App::AngleToPos(float angle) 
{
	XMFLOAT2 pos;
	pos.x = cosf(angle) * 2.f;
	pos.y = sinf(angle) * 2.f;

	return pos;
}

XMFLOAT2 App::GetRandPos()
{
	float posEnemyDeg = rand() % 360;
	float posEnemyRad = posEnemyDeg * XM_PI / 180;
	XMFLOAT2 randEnemyPos;
	randEnemyPos.x = AngleToPos(posEnemyRad).x;
	randEnemyPos.y = AngleToPos(posEnemyRad).y;
	return randEnemyPos;
}

void App::EndGame()
{
	std::string infoEnd;
	infoEnd += "\nGAME OVER";
	m_totalScore = actor_manager.GetScore();

	if (m_totalScore > 0)
	{
		infoEnd += "\nVICTORY!";
	}
	else
	{
		infoEnd += "\nDEFEAT!";
	}

	XMFLOAT3 tintEnd = { 1.0f, 1.0f, 0.8f };
	cpuDevice.DrawText(&m_font, infoEnd.c_str(), (int)(cpuDevice.GetWidth()* 0.5), 100, CPU_TEXT_CENTER, &tintEnd);
}


void StateAppInGame::OnEnter(App& cur, int from)
{

}

void StateAppInGame::OnExecute(App& cur)
{
	// time
	float dt = cpuTime.delta;
	float time = cpuTime.total;

	XMFLOAT2 posPlayer = cur.AngleToPos(playerAngle);
	
	// move counter clockwise direction
	if (cpuInput.IsLeft())
	{
		// calculate player angle
		float angle = -XM_PI * dt;
		playerAngle += angle;
		Actor_Manager::GetInstance().UpdatePlayer(posPlayer);
	}
	// move clockwise direction
	else if (cpuInput.IsRight())
	{
		// calculate player angle
		float angle = XM_PI * dt;
		playerAngle += angle;
		Actor_Manager::GetInstance().UpdatePlayer(posPlayer);
	}
	//Actor_Manager::GetInstance().UpdateEnemyPhysics();
	Actor_Manager::GetInstance().UpdateEnemyCollision();
	Actor_Manager::GetInstance().PurgeEnemies();

	//every 2s, spawn enemy
	if ( m_cooldown >= 2.f)
	{
		m_cooldown = 0.f;
		XMFLOAT2 posEnemyInit = cur.GetRandPos();
		cur.actor_manager.AddEnemy(posEnemyInit);
	}
	m_cooldown += dt;

	int totalScore = cur.actor_manager.GetScore();

	if (totalScore >= 5 || totalScore <= -5) 
	{
		cur.GetFSM()->ToState(CPU_ID(StateAppEnd));
		return;
	}
}

void StateAppInGame::OnExit(App& cur, int to)
{

}

void StateAppPause::OnEnter(App& cur, int from)
{

}

void StateAppPause::OnExecute(App& cur)
{

}

void StateAppPause::OnExit(App& cur, int to)
{

}

void StateAppEnd::OnEnter(App& cur, int from)
{

}

void StateAppEnd::OnExecute(App& cur)
{
	cur.m_endGame = true;
	cur.actor_manager.ClearEnemies();
}

void StateAppEnd::OnExit(App& cur, int to)
{

}
