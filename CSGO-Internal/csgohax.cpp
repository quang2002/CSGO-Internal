#include "csgohax.h"

csgo::engine csgohax::game;

uint32_t __stdcall csgohax::main(void*)
{
	while (!prepare()) Sleep(1000);
	for (game.vars->get_data();; Sleep(10)) hack();
	return uint32_t();
}

uint32_t __stdcall csgohax::prepare()
{
	return (uint32_t)GetModuleHandleA("client.dll");
}

uint32_t __stdcall csgohax::hack()
{
	csgo::engine::player_t* localPlayer = game.local_player();
	if (!localPlayer) return 0;

	// no flash
	localPlayer->flash_duration() = 0.0f;

	// glow esp
	for (size_t i = 0; i < 32; i++)
	{
		csgo::engine::player_t* target = game.get_player_by_id(i);
		if (!target) continue;

		if (target->dormant() || !target->team()) continue;

		csgo::engine::glowObject_t* glowObj = game.get_glow_object_by_id(target->glow_index());
		if (!glowObj) continue;

		if (localPlayer->team() == target->team())
		{
			// allies
			glowObj->r = 100.0f / 255.0f;
			glowObj->g = 240.0f / 255.0f;
			glowObj->b = 120.0f / 255.0f;
		}
		else
		{
			// enemies
			glowObj->r = 230.0f / 255.0f;
			glowObj->g = 70.0f / 255.0f;
			glowObj->b = 70.0f / 255.0f;
		}

		glowObj->a = 1.0f;
		glowObj->RenderWhenOccluded = true;
		glowObj->RenderWhenUnoccluded = false;
	}

	// trigger bot
	int crosshair_id = localPlayer->crosshair_id() - 1;
	csgo::engine::player_t* target = game.get_player_by_id(crosshair_id);
	if (target && !target->dormant() && target->team() != localPlayer->team())
		game.force_attack() = 6;

	// bunny hop
	if (GetAsyncKeyState(VK_SPACE) && localPlayer->flags() & 1)
		game.force_jump() = 6;
	return uint32_t();
}
