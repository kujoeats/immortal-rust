#pragma once
#include <vector>
#include "sdk.h"
#include <shared_mutex>   
#include "safe_ptr.h"
struct _Mutex {
	std::unique_ptr<sf::contention_free_shared_mutex<>> shared;
}; std::unique_ptr<_Mutex> mutex_;

int process_id;
const std::string apend = std::string(" - ");//affix distance on esp
struct {
	int thick_t = 1;
	int fov_t = 100;
	int smooth_t = 1;
	int smooth_t_2 = 1;
}temp;
struct two_box
{
	bool sleeper;
	std::string weapon_name;
	Vector3 Feet;
	Vector3 Head;
	std::string  name;
	float health;
	bool team;
	bool scientist;
	
};

struct espObject
{
	bool sleeper;
	std::string weapon_name;
	std::string name;
	bool scientist;
	bool team;
	float health;
	
	c_model* model;
};

 static char buf[256] = "Configuration";

Vector3 local_3d;
struct {
	float m_flVelocity = 375.f;
	float m_flDrag = 0.005f;
	float pvs = 1.f;
	float gravity = 0.5f;
	std::string weapon_name;
}weapon_stats;

namespace cache
{
	int team;
	c_game_assembly* game_assembly = nullptr;
	std::vector < std::tuple<two_box, c_player*> > ESP_Boxes;
	c_player* local_player;
	c_eyes* eyes;
	c_held* held;
	c_input* input;
	c_projectile* projectile;
	c_new_recoil_override* c_recoil;
	c_movement* movement;
	c_modelstate* modelstate;
	c_skinnable* skinnable = nullptr;
	c_tod_ambient* tod_amb = nullptr;
	c_tod_sky* tod_sky = nullptr;
	std::vector < std::tuple < c_player*, espObject> > players{ };
	std::vector<std::tuple<Vector3, std::string, Vector3>> animalVehicleItem;

	std::vector<std::tuple<Vector3, std::string, Vector3>> others;
}