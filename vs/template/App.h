#pragma once
#include "Actor_Manager.h"

class App
{
public:
	App();
	virtual ~App();

	static App& GetInstance() { return *s_pApp; }

	void OnStart();
	void OnUpdate();
	void OnExit();
	void OnRender(int pass);

	static void MyPixelShader(cpu_ps_io& io);

	XMFLOAT2 AngleToPos(float angle);

	//float GetPlayerAngle();

	XMFLOAT2 GetRandPos();

	void EndGame();

	cpu_fsm<App>* GetFSM() { return m_appFSM; }

	Actor_Manager actor_manager;
	int m_totalScore;

	bool m_endGame;
private:
	inline static App* s_pApp = nullptr;

	cpu_mesh m_meshPlayer;
	cpu_font m_font;

	//float m_playerAngle;


	cpu_entity* m_pEntity;
	cpu_fsm<App>* m_appFSM;
};

struct StateAppInGame
{
	void OnEnter(App& cur, int from);
	void OnExecute(App& cur);
	void OnExit(App& cur, int to);

	float m_cooldown = 0.f;
	float playerAngle = 0.f;
};

struct StateAppPause
{
	void OnEnter(App& cur, int from);
	void OnExecute(App& cur);
	void OnExit(App& cur, int to);
};

struct StateAppEnd
{
	void OnEnter(App& cur, int from);
	void OnExecute(App& cur);
	void OnExit(App& cur, int to);
};
