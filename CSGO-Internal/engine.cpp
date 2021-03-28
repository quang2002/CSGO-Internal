#include "engine.h"

void csgo::engine::variable_t::get_data()
{
	this->modules.csgo = (uint32_t)GetModuleHandle(_T("csgo.exe"));
	this->modules.client = (uint32_t)GetModuleHandle(_T("client.dll"));
	this->modules.engine = (uint32_t)GetModuleHandle(_T("engine.dll"));
}

csgo::engine::player_t* csgo::engine::local_player()
{
	return *(player_t**)(vars->modules.client + hazedumper::signatures::dwLocalPlayer);
}

csgo::engine::player_t* csgo::engine::get_player_by_id(uint32_t id)
{
	return *(player_t**)(vars->modules.client + hazedumper::signatures::dwEntityList + 0x10 * id);
}

csgo::engine::glowObject_t* csgo::engine::get_glow_object_by_id(uint32_t id)
{
	uint32_t glowManager = *(uint32_t*)(this->vars->modules.client + hazedumper::signatures::dwGlowObjectManager);
	if (!glowManager) return nullptr;
	return (glowObject_t*)(glowManager + sizeof glowObject_t * id);
}

uint32_t& csgo::engine::force_attack()
{
	return *(uint32_t*)(this->vars->modules.client + hazedumper::signatures::dwForceAttack);
}

uint32_t& csgo::engine::force_jump()
{
	return *(uint32_t*)(this->vars->modules.client + hazedumper::signatures::dwForceJump);
}