#define _CRT_SECURE_NO_WARNINGS
#define GLFW_EXPOSE_NATIVE_WIN32
#include "include.h"


__forceinline void u_cache() {
	ccounter++;
	//mutex_->shared->lock();

	if (cache::local_player) {		
		if (local_3d.Length() != 0) {
			cache::eyes = cache::local_player->get_eyes();
			if (cache::eyes) {
				if (ccounter >= 5 || (!cache::movement && cache::local_player && !cache::input && !cache::modelstate && !cache::skinnable && !cache::tod_sky)) {
					cache::movement = cache::local_player->get_movement();
					cache::input = cache::local_player->get_input();
					cache::modelstate = cache::local_player->get_modelstate();
					cache::skinnable = cache::game_assembly->get_skinnable();
					cache::tod_sky = cache::game_assembly->get_tod_sky();
				}
			}
		
		}
	}

	 GameMode = memory.read_chain<uintptr_t>(GameAssembly, client_entities);
	if (!GameMode)return;
	 objectList = memory.read<uintptr_t>(GameMode + 0x18);	
	if (!objectList)return;
	std::vector<std::tuple<Vector3, std::string, Vector3>> t_others{ };
	std::vector < std::tuple < c_player*, espObject > > t_players{ };
	bool foundLocalPlayer{};
	auto txScientist = e("scientist").decrypt();
	auto isBasePlayer = e("BasePlayer").decrypt();
	auto isItem = e(" (world)").decrypt();
	
	
	for (std::uint32_t i = 0; i < memory.read<std::uint32_t>(GameMode + 0x10); i++)
	{
		auto curObject = memory.read<uintptr_t>(objectList + (0x20 + (i * 8)));
		if (!curObject)continue;
		auto baseObject = memory.read<uintptr_t>(curObject + 0x10);
		if (!baseObject)continue;
		const auto object_class = memory.read<uintptr_t>(baseObject + 0x30);
		if (!object_class)continue;
		const auto tag = memory.read<WORD>(object_class + 0x54);
		std::string element_name = get_class_name(curObject);
		std::tuple<Vector3, std::string, Vector3> element{ };
		const auto name = memory.read_chain<unity_str>(object_class, { 0x60, 0x0 }).buffer;
	



			//tag is invalid for entities that arent corpses, players.

			if (tag == 6) {
				const auto player = memory.read<c_player*>(baseObject + 0x28);
				if (!player)continue;
				if (!player->is_valid(settings->moving_esp.sleeper_esp))continue;
				if (i == 0) // local player
				{

					foundLocalPlayer = true;
					if (ccounter >= 5) {
						
						Camera = get_camera_object();
						cache::local_player = player;
						std::cout << "found local player" << std::endl;
						std::cout << Camera << std::endl;
						cache::team = player->get_current_team();
					}
				}
				else {

					if (settings->esp_styles.cham) {
						bool cc = true;
						for (int i = 0; i < skinned_pointers.size(); i++)
						{
							if (skinned_pointers.at(i) == reinterpret_cast<uintptr_t>(player)) {
								cc = false;
							}
						}
						if (cc) {

							chams(player, cache::tod_sky, cache::skinnable);
							player->set_needs_clothes_rebuild(true);
							skinned_pointers.emplace_back(reinterpret_cast<uintptr_t>(player));
						}
					}
					if (element_name == isBasePlayer) {


						
						
						wstring wow = player->get_name();
						if (wow.size() != 0) {//wstr -> string
							std::string result;
							for (char x : wow) {
								result += x;
							}
							espObject entity;
							if (settings->esp_styles.weapon_nametag) {
								std::string result2;
								for (char xx : player->get_projectile()->get_item_definition()->get_shortname()) {
									result2 += xx;
								}
								entity.weapon_name = result2;
							}
							entity.name = result;
							
								entity.sleeper = player->has_flag(16);
						
							
							entity.scientist = false;
							if (cache::local_player && settings->features.aim_team) {

								if (cache::team != 0) {
									int oTeam = player->get_current_team();
									if (oTeam == cache::team && oTeam != 0) {
										entity.team = true;
									}
								}
								
								
							}
							if (settings->esp_styles.health) {
								entity.health = player->get_health();
							}

							entity.model = player->get_model();
							t_players.push_back({ player, entity });
							
						}
					}
					else {
						if (settings->moving_esp.npc) {
						
							espObject entity;
							entity.health = player->get_health();
							entity.name = txScientist;
							entity.scientist = true;
							entity.sleeper = false;
							std::string result2;
							for (char xx : player->get_projectile()->get_item_definition()->get_shortname()) {
								result2 += xx;
							}
							entity.weapon_name = result2;
							t_players.push_back({ player, entity });
						
						}
					}
				}
			}
			if (tag == 0 && settings->resources.animals) {

				if (settings->resources.bear) {
					if (element_name.find(e("Bear")) != string::npos && element_name.find(e("trap")) == string::npos) {
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Bear")) , settings->colors.bear });
						goto end;
					}
				}
				if (settings->resources.deer) {
					if (element_name.find(e("Deer")) != string::npos) {
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Deer")) , settings->colors.deer });
						goto end;
					}
				}
				if (settings->resources.stag) {
					if (element_name.find(e("Stag")) != string::npos) {
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Stag")) , settings->colors.stag });
						goto end;
					}
				}
				if (settings->resources.chicken) {
					if (element_name.find(e("Chicken")) != string::npos) {
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Chicken")) , settings->colors.chicken });
						goto end;
					}
				}
				if (settings->resources.boar) {
					if (element_name.find(e("Boar")) != string::npos) {
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Boar")) , settings->colors.boar });
						goto end;
					}
				}
				if (settings->resources.horse) {
					if (element_name.find(e("Horse")) != string::npos) {
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Horse")) , settings->colors.horse });
						goto end;
					}
				}
			}
			if (settings->resources.world && settings->resources.dropped_items && element_name.find(e("DroppedItem")) != string::npos) {
				uintptr_t pObjName = memory.read<uintptr_t>(object_class + 0x60);
				std::string object_name = memory.ReadASCII(pObjName, 128);
				if (object_name.find(e("arrow")) == string::npos && object_name.find(e("ammo.nailgun")) == string::npos && object_name.find(e("backpack.prefab")) == string::npos) {

					std::string_view str1 = isItem;
					std::string::size_type i = object_name.find(str1);
					if (i != std::string::npos)
						object_name.erase(i, str1.length());
					Vector3 position = memory.read_chain<Vector3>(object_class, entity_chain);

					element = std::tuple<Vector3, std::string, Vector3>({ position, object_name , settings->colors.dropped_items });
					goto end;
				}
			}
			if (ccounter >= 30 || g_overlay_visible) {
					if (settings->resources.hemp && settings->resources.collectables && strstr(name, e("hemp-collectable.prefab")))
					{
						element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("hemp")) , settings->colors.hemp_collectables });
						goto end;
					}
					else {
						if (settings->resources.ores) {
							if (settings->resources.stone && strstr(name, e("stone-ore.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("stone")),  settings->colors.stone_ore });
								goto end;
							}
							else if (settings->resources.sulfur && strstr(name, e("sulfur-ore.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("sulfur")) ,  settings->colors.sulfur_ore });
								goto end;
							}
							else if (settings->resources.metal && strstr(name, e("metal-ore.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("metal")) ,  settings->colors.metal_ore });
								goto end;
							}
						}
						if (settings->resources.collectables) {

							if (settings->resources.wood_collectables && strstr(name, e("wood-collectable.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("wood_c")) , settings->colors.wood_collectables });
								goto end;
							}
							else if (settings->resources.metal_collectables && strstr(name, e("metal-collectable.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("metal_c")), settings->colors.metal_collectables });
								goto end;
							}
							else if (settings->resources.stone_collectables && strstr(name, e("stone-collectable.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("stone_c")) ,  settings->colors.stone_collectables });
								goto end;
							}
							else if (settings->resources.sulfur_collectables && (strstr(name, e("sulfur-collectable.prefab")) || strstr(name, e("halloween-sulfur-collectible.prefab")))) //lol they misspelled collectable
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("stone_c")) ,  settings->colors.stone_collectables });
								goto end;
							}
							else if (settings->resources.mushroom && strstr(name, e("mushroom-cluster")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("mushroom")),  settings->colors.mushroom });
								goto end;
							}
							else if (settings->resources.pumpkin && strstr(name, e("pumpkin-collectable.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("pumpkin")),  settings->colors.pumpkin });
								goto end;
							}
							else if (settings->resources.potato && strstr(name, e("potato-collectable.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("potato")),  settings->colors.potato });
								goto end;
							}
						}
						if (settings->resources.world) {
							if (settings->resources.stash && strstr(name, e("small_stash_deployed.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("stash")),  settings->colors.stash });
								goto end;
							}
							else if (settings->resources.corpse && strstr(name, e("player_corpse.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("corpse")),  settings->colors.corpse });
								goto end;
							}
							else if (settings->resources.backpack && strstr(name, e("item_drop_backpack.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("backpack")),  settings->colors.backpack });
								goto end;
							}
							else if (settings->resources.locked_crate && strstr(name, e("codelockedhackablecrate.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("locked crate")),  settings->colors.locked_crate });
								goto end;
							}
							else if (settings->resources.supply_drop && strstr(name, e("supply_drop.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("supply drop")),  settings->colors.supply_drop });
								goto end;
							}
						}

						if (settings->resources.radtown && element_name.find("LootContainer") != string::npos) {

							//doesnt return correct positions on floating junk
							Vector3 position = memory.read_chain<Vector3>(object_class, entity_chain);
						




							if (position.distance(local_3d) < 400.f) {

								if (settings->resources.oil_barrel) {
									if (strstr(name, e("oil_barrel.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("oil barrel")),  settings->colors.oil_barrel });
										goto end;
									}
								}
								if (settings->resources.radtown_barrel) {
									if (strstr(name, e("loot_barrel_1.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("barrel")),  settings->colors.radtown_barrel });
										goto end;
									}

									else if (strstr(name, e("loot_barrel_2.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("barrel")),  settings->colors.radtown_barrel });

										goto end;
									}
									else if (strstr(name, e("loot-barrel-1.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("barrel")),  settings->colors.radtown_barrel });
										goto end;
									}
									else if (strstr(name, e("loot-barrel-2.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("barrel")),  settings->colors.radtown_barrel });
										goto end;
									}
								}
								if (settings->resources.radtown_crate) {
									if (strstr(name, e("crate_normal_2.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("radtown crate")),  settings->colors.radtown_crate });
										goto end;
									}
								}
								if (settings->resources.elite_crate) {
									if (strstr(name, e("crate_elite.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("elite crate")),  settings->colors.elite_crate });
										goto end;
									}
								}
								if (settings->resources.mil_crate) {
									if (strstr(name, e("crate_normal.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("mil crate")),  settings->colors.mil_crate });
										goto end;
									}
								}
								if (settings->resources.med_crate) {
									if (strstr(name, e("crate_normal_2_medical.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("medical crate")),  settings->colors.med_crate });
										goto end;
									}
								}
								if (settings->resources.food_crate) {
									if (strstr(name, e("crate_normal_2_food.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("food crate")),  settings->colors.food_crate });
										goto end;
									}
								}
								if (settings->resources.minecart_crate) {
									if (strstr(name, e("minecart.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("mine cart")),  settings->colors.minecart_crate });
										goto end;
									}
								}
								if (settings->resources.toolbox_crate) {
									if (strstr(name, e("crate_tools.prefab")))
									{
										element = std::tuple<Vector3, std::string, Vector3>({ position, std::string(e("toolbox crate")),  settings->colors.toolbox_crate });
										goto end;
									}
								}
							}
						}
						if (settings->resources.traps) {
							if (settings->resources.autoturret && strstr(name, e("autoturret_deployed.prefab")))
							{
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("auto turret")),  settings->colors.autoturret });
								goto end;
							}
							else if (settings->resources.flame_turret && strstr(name, e("flameturret.deployed.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("flame turret")),  settings->colors.flame_turret });
								goto end;
							}
							else if (settings->resources.shotgun_trap && strstr(name, e("guntrap.deployed"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("shotgun trap")),  settings->colors.shotgun_trap });
								goto end;
							}
							else if (settings->resources.bear_trap && strstr(name, e("beartrap.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("bear trap")),  settings->colors.bear_trap });
								goto end;
							}
							else if (settings->resources.landmine && strstr(name, e("trap.landmine.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("land mine")),  settings->colors.bear_trap });
								goto end;
							}
							else if (settings->resources.sam_site && strstr(name, e("sam_site_turret_deployed.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("SAM SITE")),  settings->colors.sam_site });
								goto end;
							}
						}
						if (settings->resources.vehicles) {
							if (settings->resources.modular_cars && ((strstr(name, e("modularcar")) || strstr(name, e("2module_camper")) && !(strstr(name, e("lift")))))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("modular car")),  settings->colors.modular_cars });
								goto end;
							}
							else if (settings->resources.minicopter && strstr(name, e("minicopter.entity.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("minicopter")),  settings->colors.minicopter });
								goto end;
							}
							else if (settings->resources.scrappy && strstr(name, e("scraptransporthelicopter.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("scrap heli")),  settings->colors.scrappy });
								goto end;
							}
							else if (settings->resources.patrol_heli && strstr(name, e("patrolhelicopter.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("patrol heli")),  settings->colors.patrol_heli });
								goto end;
							}
							else if (settings->resources.boat && strstr(name, e("rowboat.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("boat")),  settings->colors.boat });
								goto end;
							}
							else if (settings->resources.rhib && strstr(name, e("rhib.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("rhib")),  settings->colors.rhib });
								goto end;
							}
							else if (settings->resources.bradley_apc && strstr(name, e("bradleyapc.prefab"))) {
								element = std::tuple<Vector3, std::string, Vector3>({ memory.read_chain<Vector3>(object_class, entity_chain), std::string(e("Bradley APC")),  settings->colors.bradley_apc });
								goto end;
							}
						}
					}
				}
			end:
				t_others.emplace_back(element);
			}
			


	if (!foundLocalPlayer) {
		cache::local_player = NULL;
		localPlayerAlive = false;
	}
	else {
		localPlayerAlive = true;
	}
	cache::players = t_players;
//	if (ccounter >= 5 || g_overlay_visible) {
			cache::others = t_others;
		//	ccounter = 0;
	//	}
	//mutex_->shared->unlock();
}
__forceinline void capturePositions() {

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
	CloseHandle(GetCurrentThread());
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(35));

		if (cache::local_player) {
		//	mutex_->shared->lock();
			local_3d = memory.read<Vector3>(Camera + 0x42C);

			std::vector < std::tuple<two_box, c_player* > > t_ESP_Boxes;
				
			if (cache::movement && Camera) {
			
				if (settings->features.spider) {
					if (cache::movement->get_ground_new_angl() != 0.f) {
						cache::movement->set_ground_new_angl(0.f);
					}
				}
				if (settings->features.shoot_anywhere && cache::modelstate) {
					cache::modelstate->setFlag(Flags::OnGround);
				}
			}
		
				for (auto player : cache::players)
				{
					const auto play = std::get<0>(player);
					Vector3 head_3d = (play->get_transform< c_transform*>(48)->position() + Vector3(0, 0.3f, 0));
					if (head_3d.Length() == 0.f)continue;
					if (world_to_screen(head_3d).Zero())continue;
					auto feet_3d = Vector3(play->get_transform< c_transform*>(3)->position() + play->get_transform< c_transform*>(15)->position()) * 0.5f;
					feet_3d.y -= 0.2f;
					if (feet_3d.Length() == 0.f)continue;
					two_box espObject_;

					espObject_.Feet = feet_3d;
					espObject_.Head = head_3d;
					espObject object = std::get<1>(player);
					espObject_.name = object.name;
					espObject_.weapon_name = object.weapon_name;
					espObject_.sleeper = object.sleeper;
					espObject_.team = object.team;
					espObject_.health = object.health;
					espObject_.scientist = object.scientist;
					std::tuple<two_box, c_player*> element{ };
					element = { espObject_, play };
					t_ESP_Boxes.emplace_back(element);
				}
			//	mutex_->shared->unlock();
				cache::ESP_Boxes = t_ESP_Boxes;
			
		}
		else {
			Sleep(1000);
		}
	}
}

int scounter = 0;
void slow() {
	int counter{};
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
	CloseHandle(GetCurrentThread());

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if ( ( cache::local_player && cache::movement  ) && (settings->features.aimbot || settings->features.insta_compound || settings->features.spider || settings->features.melee_range || settings->features.melee_sprint || settings->features.fakelag || settings->features.always_eoka || settings->features.always_automatic || settings->features.mounted_shoot || settings->features.norecoil || settings->features.nospread || settings->features.readyBow || settings->features.recoil_modifier))
		{
			if (settings->features.fakelag) {
				float lag = (float)(rand() % 150) / 1000.f;
				if (lag < 0.1f) {
					lag = 0.1f;
				}
				if (cache::local_player->get_client_tick_interval() != lag) {
					cache::local_player->set_client_tick_interval(lag);
				}
			}
			else {
				if (wasFakeLagOn) {
					if (cache::local_player->get_client_tick_interval() != 0.03125f) {
						cache::local_player->set_client_tick_interval(0.03125f);
					}
					wasFakeLagOn = false;
				}
			}
			if (settings->features.spider && cache::movement) {
				if (cache::movement->get_max_walking_angle() != 100.f) {
					cache::movement->set_max_walking_angle(100.f);
				}
			
			
			}


			cache::projectile = cache::local_player->get_projectile();
			if (cache::projectile) {
				cache::held = cache::projectile->get_held();
			}
			
			if (cache::projectile && cache::held) {
				c_primary_magazine* ourMagazine = cache::held->get_primary_magazin();
				if (ourMagazine != NULL) {
					if (ourMagazine->get_item_definition() && cache::held && cache::projectile) {
						cache::c_recoil = cache::held->get_recoil_propreties()->get_new_recoil_overrid();
						std::string weapon_nam = cache::projectile->get_item_definition()->get_shortnameS();
						if (weapon_nam.length() != 0 && cache::held && cache::projectile) {
							std::string bullet_nam = cache::held->get_primary_magazin()->get_item_definition()->get_shortnameS();
							const char* bullet_name = bullet_nam.c_str();
							const char* weapon_name = weapon_nam.c_str();
							weapon_stats.weapon_name = weapon_nam;
							hasEoka = (_stricmp(weapon_stats.weapon_name.c_str(), _("pistol.eoka")) == NULL);

							if (settings->features.aimbot && cache::held && cache::projectile) {
								float flVelo = get_bullet_velocity(weapon_name, bullet_name);
								float pvs = cache::held->get_pvs();
							
								weapon_stats.gravity = bullet_gravity(bullet_name);
								uintptr_t childrenList = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(cache::held) + 0x40);
								int childrenCount = memory.read<int>(childrenList + 0x18);
								childrenList = memory.read<uintptr_t>(childrenList + 0x10);
								for (int h = 0; h < childrenCount; h++)
								{
									uintptr_t childEntity = memory.read<uintptr_t>(childrenList + 0x20 + h * 0x8);
									if (!childEntity)
										continue;
									if (!cache::projectile)
										continue;
									if (!cache::held)
										continue;
									if (!bullet_name)
										continue;
									if (!has_gun_out(weapon_stats.weapon_name.c_str()))
										continue;
									uintptr_t childEntityName = memory.read<uintptr_t>(childEntity);
									childEntityName = memory.read<uintptr_t>(childEntityName + 0x10);
									std::string entityType = memory.ReadASCII(childEntityName, 24);
									if (strcmp(entityType.c_str(), _("ProjectileWeaponMod")) == 0)
									{
										ProjectileWeaponModModifier projVelModif = memory.read<ProjectileWeaponModModifier>(childEntity + 0x180);
										if (projVelModif.enabled)
										{
											flVelo *= projVelModif.scalar;
											break;
										}
									}

								}
								weapon_stats.m_flVelocity = flVelo;
							}

						}
					}
				}
			}
			
			//	
			if (cache::held && settings->features.insta_compound && _stricmp(weapon_stats.weapon_name.c_str(), _("bow.compound")) == NULL) {

				if (cache::held->get_string_max_duration() != 0.15f) {
					cache::held->set_string_max_duration(0.15f);
				}
				if (cache::held->get_string_movement_penalty() != 0.f) {
					cache::held->set_string_movement_penalty(0.f);
				}
			}

			




		
			if (cache::held && !has_gun_out(weapon_stats.weapon_name.c_str())) {
				if (settings->features.melee_sprint) {

					if (cache::held->get_block_sprint_on_attack()) {


						cache::held->set_block_sprint_on_attack(false);
					}

				}

				if (settings->features.melee_range) {
					if (cache::held->get_attack_distance() != 2.75F) {
						cache::held->set_attack_distance(2.75f);
					}
				}
			}





		
		
			if (cache::held && has_gun_out(weapon_stats.weapon_name.c_str())) {
				if (settings->features.always_automatic) {
					if (cache::held->get_automatic() == false) {
						cache::held->set_automatic(true);
					}
				}

				if (settings->features.mounted_shoot)
				{
					const auto mounted = cache::local_player->get_mounted();
					if (mounted)
					{
						if (!mounted->get_can_wield_items()) {
							mounted->set_can_wield_items(true);
						}
					}
				}




				if (settings->features.readyBow && strstr(weapon_stats.weapon_name.c_str(), _("bow.hunting"))) {
					if (!cache::held->get_attack_ready()) {
						cache::held->set_attack_ready(true);
					}
				}
				if (settings->features.always_eoka && hasEoka) {
					if (cache::held->get_success_fraction() != 1.f) {
						cache::held->set_success_fraction(1.f);
					}
				}

				c_new_recoil_override* c_recoil = cache::c_recoil;
				vec4_t recoil = c_recoil->get_recoil();
				if (!strstr(weapon_stats.weapon_name.c_str(), _("bow")) && m_vecRecoilProperties.find(weapon_stats.weapon_name) == m_vecRecoilProperties.end()) {

					m_vecRecoilProperties.emplace(weapon_stats.weapon_name, recoil);
				}

				if (settings->features.recoil_modifier && !settings->features.norecoil && !strstr(weapon_stats.weapon_name.c_str(), _("bow")) && !strstr(weapon_stats.weapon_name.c_str(), _("eoka")) && !strstr(weapon_stats.weapon_name.c_str(), _("shotgun"))){
					const vec4_t m_vecDefault = m_vecRecoilProperties[weapon_stats.weapon_name];
					c_recoil->set_recoil_vector({ m_vecDefault.x / xf(100.f) * settings->features.recoil, m_vecDefault.y / xf(100.f) * settings->features.recoil, m_vecDefault.z / xf(100.f) * settings->features.recoil, m_vecDefault.w / xf(100.f) * settings->features.recoil });
				}
				if (settings->features.norecoil && c_recoil && !strstr(weapon_stats.weapon_name.c_str(), _("bow")) && !strstr(weapon_stats.weapon_name.c_str(), _("python"))) {
					if (c_recoil->get_time_to_take_max() != 0.f) {
						c_recoil->set_recoil_vector({ 0.f,0.f,0.f,0.f });
						c_recoil->set_time_to_take_max(0.f);
					}
				}
				if (settings->features.nospread && c_recoil) {
					c_held* held = cache::held;
					if (cache::held->get_aimcone() != 0.f) {
						c_recoil->set_aimcone_curve_scal(0.f);
						held->set_sight_aimcone_scal(0.f);
						held->set_sight_aimcone_offset(0.f);
						held->set_aimcon(0.f);
						held->set_aimcone_penalty_max(0.f);
						held->set_aimcone_penalty(0.f);
						held->set_hip_aimcon(0.f);
						held->set_stance_penalty(0.f);
						held->set_hip_aimcone_scal(0.f);
						held->set_hip_aimcone_offset(0.f);
						held->set_aimcone_penalty_recover_tim(0.f);
						held->set_aimcone_penalty_recover_delay(0.f);
						held->set_aimcone_penalty_per_shot(0.f);
					}



				}
			
			}
		
		}
	else {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}
		}
}




void perfect_silent_thread() { //this shit is a fucking mess due to the soul fact i cant set projectile variables without a extremely fast while loop
	CloseHandle(GetCurrentThread());
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
	uint64_t maxxx = 0x0;
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		if (cache::local_player && settings->features.aimbot ) {
			bool updatedThis{};
			while (GetAsyncKeyState(settings->features.i_aimKey) ) {
				if (!updatedThis) {
					if (cache::local_player) {
						cache::projectile = cache::local_player->get_projectile();
						if (cache::projectile) {
							cache::held = cache::projectile->get_held();
						}
						if (cache::projectile && cache::held) {
							c_primary_magazine* ourMagazine = cache::held->get_primary_magazin();
							if (ourMagazine != NULL) {
								if (ourMagazine->get_item_definition()) {
									cache::c_recoil = cache::held->get_recoil_propreties()->get_new_recoil_overrid();
									std::string weapon_nam = cache::projectile->get_item_definition()->get_shortnameS();
									if (weapon_nam.length() != 0 && cache::held) {
										std::string bullet_nam = cache::held->get_primary_magazin()->get_item_definition()->get_shortnameS();
										const char* bullet_name = bullet_nam.c_str();
										const char* weapon_name = weapon_nam.c_str();
										weapon_stats.weapon_name = weapon_nam;
										hasEoka = (_stricmp(weapon_stats.weapon_name.c_str(), _("pistol.eoka")) == NULL);

										if (settings->features.aimbot && cache::held && cache::projectile) {
											float flVelo = get_bullet_velocity(weapon_name, bullet_name);
											float pvs = cache::held->get_pvs();
											
											weapon_stats.gravity = bullet_gravity(bullet_name);
											uintptr_t childrenList = memory.read<uintptr_t>(reinterpret_cast<uintptr_t>(cache::held) + 0x40);
											int childrenCount = memory.read<int>(childrenList + 0x18);
											childrenList = memory.read<uintptr_t>(childrenList + 0x10);
											for (int h = 0; h < childrenCount; h++)
											{
												uintptr_t childEntity = memory.read<uintptr_t>(childrenList + 0x20 + h * 0x8);
												if (!childEntity)
													continue;
												if (!cache::projectile)
													continue;
												if (!cache::held)
													continue;
												if (!bullet_name)
													continue;
												if (!has_gun_out(weapon_stats.weapon_name.c_str()))
													continue;

												uintptr_t childEntityName = memory.read<uintptr_t>(childEntity);
												childEntityName = memory.read<uintptr_t>(childEntityName + 0x10);
												std::string entityType = memory.ReadASCII(childEntityName, 24);
												if (strcmp(entityType.c_str(), _("ProjectileWeaponMod")) == 0)
												{
													ProjectileWeaponModModifier projVelModif = memory.read<ProjectileWeaponModModifier>(childEntity + 0x180);
													if (projVelModif.enabled)
													{
														flVelo *= projVelModif.scalar;
														break;
													}
												}

											}
											weapon_stats.m_flVelocity = flVelo;
										}

									}
								}
							}
						}
					}
				}
				if ( ( !settings->features.thick_bullet && !settings->features.shotgun_nospread && !wasThickBulletOn) || !has_gun_out(weapon_stats.weapon_name.c_str())) {
					if (!settings->features.silent) {
						if (settings->features.aim_smooth) {
							std::this_thread::sleep_for(std::chrono::milliseconds(15));
						}
						else {
							std::this_thread::sleep_for(std::chrono::milliseconds(3));
						}
					}
					else {
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
				}
				else {
					if (has_gun_out(weapon_stats.weapon_name.c_str())) {
						
							if (settings->features.shotgun_nospread && ((strstr(weapon_stats.weapon_name.c_str(), _("shotgun")) || strstr(weapon_stats.weapon_name.c_str(), _("eoka"))))) {
								shotgun_nospread(cache::projectile, cache::held);
							}


							if (wasThickBulletOn && !settings->features.thick_bullet) {
								disable_fat_bullet(cache::held);
							}
							if (settings->features.thick_bullet) {
								fat_bullet(cache::held);
							}
						}
					
					
					
				}
				Vector2 screen_m = { g_width * xf(0.5f), xf(g_height * 0.5f) };
				float lowest_screen_dist = (settings->features.fov);
				two_box aim_targ;
				c_player* t_selected_player{};
				
				for (auto player : cache::ESP_Boxes)
				{
					aim_targ = std::get<0>(player);
					if (aim_targ.sleeper)continue;
					if (aim_targ.team && !settings->features.aim_team)continue;
					if (aim_targ.scientist && !settings->features.aim_npc)continue;

					c_player* selected_player = std::get<1>(player);
					Vector2 two_dimension = world_to_screen(std::get<0>(player).Head);
					if (two_dimension.Distance({ 0.f,0.f }) == 0.f)continue;
					float dist = screen_m.Distance(two_dimension);
					if (dist > lowest_screen_dist)continue;
					if (dist < lowest_screen_dist)  {
						lowest_screen_dist = dist;
						t_selected_player = selected_player;
					}
				}
				
				if (lowest_screen_dist != settings->features.fov) {
					local_3d = memory.read<Vector3>(Camera + 0x42C);
					if (local_3d.Length() != 0.f) {
						int boneIndex = settings->features.chest ? 7 : 46;
						
						Vector3 target_pos_3d = t_selected_player->get_transform< c_transform*>(boneIndex)->position();
						if (target_pos_3d.Length() != 0.f) {
							auto angles = CalcAngle(local_3d, target_pos_3d);

						
							

							if (valid_angle(angles))
							
								if (settings->features.silent) {
		
									clamp(angles.x, angles.y);
									if (valid_angle(angles)) {
										vec4_t to_quat = to_quaternion(angles);
										if (cache::eyes->get_body_rotation().distance(to_quat) != 0.f) {
											cache::eyes->set_body_rotation(to_quat);
										}
									
									}
								}
								else {
									

								
									Vector2 aim_angle = angles;



									if (settings->features.aim_smooth) {
									
										srand(time(0));
										Vector2 diff = body_angles - aim_angle;
										clamp(diff.x, diff.y);
										float randomNumber = (float)(rand() % 100001) / 100000;

										diff = body_angles - diff / (settings->features.smoothing_x + (float(rand() % ((int)settings->features.smoothing_x) + (float)(rand() % 5) + randomNumber)));
										aim_angle = diff;
									
									}

									
								
									normalize(aim_angle.x, aim_angle.y);
									clamp(aim_angle.x, aim_angle.y);
									if (valid_angle(aim_angle))
									{
										if (body_angles.x != aim_angle.x && body_angles.y != aim_angle.y && body_angles.Distance({ 0,0 }) != 0 && aim_angle.Distance({0,0}) != 0) { //anti-snap + check for empty angles
											cache::input->set_body_angles({ aim_angle.x , aim_angle.y });
										}
									}
								}
						}
					}
					
				}
				else {

					std::this_thread::sleep_for(std::chrono::milliseconds(17));
				}
				
				
				
			}
			if (!settings->features.tpbullet && !wasThickBulletOn && !settings->features.thick_bullet && !settings->features.shotgun_nospread) {
				std::this_thread::sleep_for(std::chrono::milliseconds(3));
			}

		}
		else {
			if (cache::local_player) {
			
				
				if (has_gun_out(weapon_stats.weapon_name.c_str()) && !settings->features.aimbot && (wasThickBulletOn || settings->features.shotgun_nospread || settings->features.tpbullet)) { //aimbot also controls projectile vars
					while (GetAsyncKeyState(VK_LBUTTON) && has_gun_out(weapon_stats.weapon_name.c_str())) {

						if (settings->features.tpbullet) {
							initialDistanceExploit = xf(12.f);
			
						}
						if (settings->features.thick_bullet) {
							fat_bullet(cache::held);
						}
						else {
							if (wasThickBulletOn) {
								disable_fat_bullet(cache::held);
							}
						}
						if (settings->features.shotgun_nospread && ((strstr(weapon_stats.weapon_name.c_str(), _("shotgun")) || strstr(weapon_stats.weapon_name.c_str(), _("eoka"))))) {
							shotgun_nospread(cache::projectile, cache::held);
						}
					}
						
					
				}
				else {
					Sleep(100);
				}
			}
			else {
				Sleep(1000);
			}
		}
	}
}

__forceinline void runRenderTick() {
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	const auto	draw_list = ImGui::GetBackgroundDrawList();

	if (g_overlay_visible) {
		if (ImGui::Begin(e("Immortal"), &p_open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollWithMouse)) {
			float cursorposx = ImGui::GetCursorPosX(), cursorposy = ImGui::GetCursorPosY();
			ImGui::PushFont(fonts.font1);
			if (ImGui::BeginChild(e("child0"), { 251,  200 }, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize)) {
				if (ImGui::Button(e("Aimbot"), { 75, 14 })) { selectedMenu = 0; }; ImGui::SameLine();
				if (ImGui::Button(e("Movement"), { 75, 14 })) { selectedMenu = 1; };	ImGui::SameLine();
				if (ImGui::Button(e("Miscellaneous"), { 70, 14 })) { selectedMenu = 2; }; ImGui::Separator();
				if (selectedMenu == 0) {
					ImGui::Checkbox(e("enabled"), &settings->features.aimbot);
					ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 2);
					if (ImGui::Checkbox(e("silent"), &settings->features.silent)) {
						settings->features.aim_smooth = false;
					}
					ImGui::SameLine();
					/*
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 2);
					if (ImGui::Checkbox(e("smooth"), &settings->features.aim_smooth)) {
						settings->features.silent = false;
					}
					*/
					ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 2);
					ImGui::Checkbox(e("chest"), &settings->features.chest);
					ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 2);
					ImGui::Checkbox(e("npc"), &settings->features.aim_npc);
					ImGui::SameLine();
					ImGui::Checkbox(e("team"), &settings->features.aim_team);

					ImGui::Checkbox(e("fov"), &settings->features.aim_fov);
					ImGui::SameLine();
					


					ImGui::PushItemWidth(xf(130.f));
					set_cursor(ImGui::GetCursorPosX() - 10, ImGui::GetCursorPosY() - 2);
					if (ImGui::SliderInt(e(" "), &temp.fov_t, 1, 1000)) {
						settings->features.fov = static_cast<float>(temp.fov_t);
					}
					ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - xf(15.f));
					const char* key = settings->features.aimkey.c_str();
					if (ImGui::Button(key, { xf(70.f), xf(14.f) })) {
						VIRTUALKEY choice = get_async_key_state();
						settings->features.i_aimKey = choice.uiKey;
						settings->features.aimkey = choice.szKey;
					}
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 2);
					if (ImGui::Checkbox(e("smooth"), &settings->features.aim_smooth)) {
						settings->features.silent = false;
					}
					
					if (settings->features.aim_smooth) {
						ImGui::PushItemWidth(xf(227.f));
						ImGui::Text(e("Strength"));
						ImGui::SameLine();

						if (ImGui::SliderInt(e("  "), &temp.smooth_t, 1, xf(250.f))) {
							settings->features.smoothing_x = static_cast<float>(temp.smooth_t);
						}

					}
					
					
				}
				if (selectedMenu == 2) {
					if (ImGui::Checkbox(e("fat.bullet"), &settings->features.thick_bullet)) {
						if (!settings->features.thick_bullet) {
							wasThickBulletOn = true;
						}
					}
					ImGui::SameLine();
					ImGui::Checkbox(e("fast.bullet"), &settings->features.fast_bullet);
					ImGui::SameLine();
					ImGui::Checkbox(e("0.recoil"), &settings->features.norecoil);
					ImGui::SameLine();
					ImGui::Checkbox(e("0.spread"), &settings->features.nospread);
					ImGui::Text(e("recoil"));
					ImGui::SameLine();
					ImGui::PushItemWidth(xf(207.f));
					if (ImGui::SliderFloat(e("   "), &settings->features.recoil, xf(1.f), xf(100.f))) {
						settings->features.recoil_modifier = true;
					}


					set_cursor(ImGui::GetCursorPosX() + xf(3.f), ImGui::GetCursorPosY() + xf(3.f));
					float oggg = ImGui::GetCursorPosX();
					ImGui::Checkbox(e("eoka.tap"), &settings->features.insta_eoka);
					ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - xf(2.f));
					float oggg_1 = ImGui::GetCursorPosX();
					ImGui::Checkbox(e("shotgun.nospread"), &settings->features.shotgun_nospread);
					ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() - xf(9.f));
					float oggg_2 = ImGui::GetCursorPosX();
					ImGui::Checkbox(e("mounted.shoot"), &settings->features.mounted_shoot);
					ImGui::SetCursorPosX(oggg);
					ImGui::Checkbox(e("automatic"), &settings->features.always_automatic);
					ImGui::SameLine();
					ImGui::SetCursorPosX(oggg_1);
					ImGui::Checkbox(e("insta.compound"), &settings->features.insta_compound);
					ImGui::SameLine();
					ImGui::SetCursorPosX(oggg_2);
					ImGui::Checkbox(e("always.eoka"), &settings->features.always_eoka);
					
					
					ImGui::SetCursorPosX(oggg);
				
					ImGui::SameLine();
					ImGui::SetCursorPosX(oggg_1);
					ImGui::Checkbox(e("melee range"), &settings->features.melee_range);
				
					ImGui::SameLine();
					ImGui::SetCursorPosX(oggg_2);
					ImGui::Checkbox(e("melee sprint"), &settings->features.melee_sprint);
					
					ImGui::SetCursorPosX(oggg);
					ImGui::Checkbox(e("fast.bow"), &settings->features.readyBow);
					ImGui::SameLine();
					if (ImGui::IsItemHovered()) {
						ImGui::BeginTooltip();
						ImGui::Text("Gives you a small advantage with the bow. will cause cerberus ban if misused. Causes invalid shots");
						ImGui::EndTooltip();
					}

					ImGui::SetCursorPosX(oggg_1);
					ImGui::Checkbox(e("rapidfire"), &settings->features.readyBow);
					ImGui::SameLine();
					ImGui::SetCursorPosX(oggg_2);
					ImGui::Checkbox(e("tp.bullet"), &settings->features.tpbullet);
				}
				if (selectedMenu == 1) {
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(20));
					ImGui::Checkbox(e("spider"), &settings->features.spider);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(2.f));

					ImGui::SameLine();
				//	ImGui::Checkbox(e("frog"), &settings->features.superjump);
			//		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(2.f));


					ImGui::SameLine();
			//		ImGui::Checkbox(e("fly"), &settings->features.flyhack);
			//		ImGui::SameLine();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(2.f));

					if (ImGui::Checkbox(e("fakelag"), &settings->features.fakelag)) {
						wasFakeLagOn = true;
					}
					ImGui::SameLine();
					ImGui::Checkbox(e("jumpshot"), &settings->features.shoot_anywhere);


				}
				ImGui::EndChild();
			}
			set_cursor(260, cursorposy);

			if (ImGui::BeginChild(e("child3"), { 176,  279 }, true, ImGuiWindowFlags_NoScrollbar)) { //esp panel
				float og;
				float og2 = ImGui::GetCursorPosX();
				ImGui::Checkbox(e("Players"), &settings->moving_esp.players);
				if (settings->moving_esp.players) {
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("rectangles"), &settings->esp_styles.rectangle);

					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("health"), &settings->esp_styles.health);

					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("name"), &settings->esp_styles.nametags);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("weapon"), &settings->esp_styles.weapon_nametag);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("cham"), &settings->esp_styles.cham);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("sleeper"), &settings->moving_esp.sleeper_esp);
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("scientists"), &settings->moving_esp.npc);
				
				
				}
				og = og2 + 50.f;
				ImGui::Checkbox(e("Ore"), &settings->resources.ores);
				if (settings->resources.ores) {
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("stone"), &settings->resources.stone);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("cStone"), (float*)&settings->colors.stone_ore, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("metal"), &settings->resources.metal);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("cMetal"), (float*)&settings->colors.metal_ore, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("sulfur"), &settings->resources.sulfur);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("cSulfur"), (float*)&settings->colors.sulfur_ore, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
				}
				ImGui::Checkbox(e("Collectable"), &settings->resources.collectables);
				if (settings->resources.collectables) {
					og += 50.f;
				
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("hemp_collectable"), &settings->resources.hemp);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccHemp"), (float*)&settings->colors.hemp_collectables, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("stone_collectable"), &settings->resources.stone_collectables);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccStone"), (float*)&settings->colors.stone_collectables, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("metal_collectable"), &settings->resources.metal_collectables);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccMetal"), (float*)&settings->colors.metal_collectables, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("sulfur_collectable"), &settings->resources.sulfur_collectables);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccSulfur"), (float*)&settings->colors.sulfur_collectables, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("wood_collectable"), &settings->resources.wood_collectables);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccWood"), (float*)&settings->colors.wood_collectables, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("mushroom"), &settings->resources.mushroom);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccMush"), (float*)&settings->colors.mushroom, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("corn"), &settings->resources.corn);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccCorn"), (float*)&settings->colors.corn, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("pumpkin"), &settings->resources.pumpkin);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccPumpkin"), (float*)&settings->colors.pumpkin, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("potato"), &settings->resources.potato);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccPotato"), (float*)&settings->colors.potato, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();

				}
				ImGui::Checkbox(e("World"), &settings->resources.world);
				if (settings->resources.world) {
					og = 100.f;
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("dropped_items"), &settings->resources.dropped_items);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccItems"), (float*)&settings->colors.dropped_items, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("player_corpse"), &settings->resources.corpse);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccCorpse"), (float*)&settings->colors.corpse, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("player_backpack"), &settings->resources.backpack);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccBackpack"), (float*)&settings->colors.backpack, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("supply_drop"), &settings->resources.supply_drop);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccSupplies"), (float*)&settings->colors.supply_drop, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("locked_crate"), &settings->resources.locked_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccLockedCrate"), (float*)&settings->colors.locked_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("hidden_stash"), &settings->resources.stash);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccStash"), (float*)&settings->colors.stash, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
				}
				ImGui::Checkbox(e("Radtown"), &settings->resources.radtown);
				if (settings->resources.radtown) {
					og = 100.f;
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));

					ImGui::Checkbox(e("food_crate"), &settings->resources.food_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccFood_crate"), (float*)&settings->colors.food_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("tool_box"), &settings->resources.toolbox_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccTool_crate"), (float*)&settings->colors.toolbox_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("med_crate"), &settings->resources.med_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccMedCrate"), (float*)&settings->colors.med_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("mil_crate"), &settings->resources.mil_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccMilitary"), (float*)&settings->colors.mil_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("basic_crate"), &settings->resources.radtown_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccRadtownBox"), (float*)&settings->colors.radtown_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("minecart"), &settings->resources.minecart_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccMinecart"), (float*)&settings->colors.minecart_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("elite_crate"), &settings->resources.elite_crate);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccElite"), (float*)&settings->colors.elite_crate, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("radtown_barrel"), &settings->resources.radtown_barrel);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccRadtown_Barrel"), (float*)&settings->colors.radtown_barrel, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("oil_barrel"), &settings->resources.oil_barrel);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccoil_Barrel"), (float*)&settings->colors.oil_barrel, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();

				}
				ImGui::Checkbox(e("Animals"), &settings->resources.animals);
				if (settings->resources.animals) {
					og = 100.f;
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Boar"), &settings->resources.boar);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccBoar"), (float*)&settings->colors.boar, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Bear"), &settings->resources.bear);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccBear"), (float*)&settings->colors.bear, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Stag"), &settings->resources.stag);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccStag"), (float*)&settings->colors.stag, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Deer"), &settings->resources.deer);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccDeer"), (float*)&settings->colors.deer, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Horse"), &settings->resources.horse);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccHorse"), (float*)&settings->colors.horse, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Chicken"), &settings->resources.chicken);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccChicken"), (float*)&settings->colors.chicken, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
				}

				ImGui::Checkbox(e("Vehicles"), &settings->resources.vehicles);

				if (settings->resources.vehicles) {
					og = 100.f;
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Cars"), &settings->resources.modular_cars);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccModules"), (float*)&settings->colors.modular_cars, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Minicopter"), &settings->resources.minicopter);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccMinicopter"), (float*)&settings->colors.minicopter, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Scrap Heli"), &settings->resources.scrappy);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccScrappy"), (float*)&settings->colors.scrappy, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Patrol Heli"), &settings->resources.patrol_heli);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccPatrol"), (float*)&settings->colors.patrol_heli, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Bradley APC"), &settings->resources.bradley_apc);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccBradley"), (float*)&settings->colors.bradley_apc, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Boat"), &settings->resources.boat);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccBoat"), (float*)&settings->colors.boat, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Rhib"), &settings->resources.rhib);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccRhib"), (float*)&settings->colors.rhib, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
				}
				ImGui::Checkbox(e("Traps"), &settings->resources.traps);
				if (settings->resources.traps) {
					og = 100.f;
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Auto-turret"), &settings->resources.autoturret);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccAutoTurret"), (float*)&settings->colors.autoturret, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Shotgun"), &settings->resources.shotgun_trap);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccShotgunTrap"), (float*)&settings->colors.shotgun_trap, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Landmine"), &settings->resources.landmine);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccLandmine"), (float*)&settings->colors.landmine, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Flame-turret"), &settings->resources.flame_turret);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccFlameTurret"), (float*)&settings->colors.flame_turret, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("Bear-trap"), &settings->resources.bear_trap);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccBearTrap"), (float*)&settings->colors.bear_trap, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
					ImGui::Checkbox(e("SAM-Site"), &settings->resources.sam_site);
					setup_colorbox(og);
					ImGui::ColorEdit4(e("ccSamSite"), (float*)&settings->colors.sam_site, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions);
					ImGui::PopStyleVar();
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xf(5.f));
				}
				ImGui::EndChild();
			}
			set_cursor(cursorposx, 226);
			if (ImGui::BeginChild(e("child2"), { xf(251.f),  xf(78) }, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {
				ImGui::SetNextItemWidth(236);
				ImGui::InputText(e("##user"), buf, sizeof(buf));
				ImGui::Button(e("save"), ImVec2{ xf(236.f),xf(18.f) });
				ImGui::Button(e("load"), ImVec2{ xf(236.f),xf(18.f) });
				ImGui::EndChild();
			}
			ImGui::PopFont();
		}
		ImGui::End();
		if (!p_open) { exit(0); };
	} // draw menu
	if (settings->features.aim_fov) {
		ImVec2 center{ g_width * xf(0.5f), g_height * xf(0.5f) };
		draw_list->AddCircle(center, (settings->features.fov), g_color_white, 100, 1.f);
	}
	ImGui::PushFont(fonts.font2);
	matrix = memory.read<mat4x4_t>(Camera + 0x2E4);
	for (auto other : cache::others)//static... non moving entities
	{
		Vector3 world_position = std::get<0>(other);
		if (world_position.Length() == 0)continue;
		auto pos = world_to_screen(world_position);
		if (pos.Zero())continue;
		Vector3 color = std::get<2>(other);
		int Dist = static_cast<int>(world_position.distance(local_3d));
		//Dist = round(Dist * 0.5) * 2;
		auto conv = (std::string(std::get<1>(other)).append(apend).append(std::to_string(Dist)));
		draw_list->AddText(ImVec2(pos.x + 1, pos.y - 1), g_color_black, conv.c_str());
		draw_list->AddText(ImVec2(pos.x, pos.y), ImGui::ColorConvertFloat4ToU32(ImVec4(color.x, color.y, color.z, 1.0f)), conv.c_str());
	}
	if (hasEoka && settings->features.insta_eoka && cache::held && cache::projectile) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (cache::held->get_shots_fired() != 1) { //THIS OFFSET NEEDS TO BE PUT IN AUTO UPDATER
				cache::held->set_success_fraction(1.f);
				cache::held->set_striking(1);
				cache::held->set_did_spark_this_frame(1);
				std::this_thread::sleep_for(std::chrono::milliseconds(17));
				cache::held->set_striking(0);
			}
			
		}

	}
	if (settings->moving_esp.players) {

		for (auto Box : cache::ESP_Boxes)
		{
			{
				two_box tbox = std::get<0>(Box);
				Vector2  Feet = world_to_screen(tbox.Feet);
				if (Feet.Zero())continue;
				if (!settings->esp_styles.rectangle && !settings->esp_styles.health && !settings->esp_styles.nametags && !settings->esp_styles.weapon_nametag)continue;
				Vector3 world_position = tbox.Head;
				const Vector2 Head = world_to_screen(world_position);
				if (Head.Zero())continue;
				auto  h = (Head.y - Feet.y);
				auto w = h * xf(0.5f);
				const auto x = Feet.x - (w * xf(0.5f));
				auto y = Feet.y;
				if (settings->esp_styles.rectangle) {


					draw_list->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), g_color_white);

				}
				ImVec2 calc;
				if (settings->esp_styles.nametags) {
					const auto caption = tbox.name.c_str();
					calc = ImGui::CalcTextSize(caption);
					draw_list->AddText(ImVec2(Feet.x - (calc.x * xf(0.5f)) - xf(1.f), Head.y - xf(12.f)), g_color_black, caption);
					draw_list->AddText(ImVec2(Feet.x - (calc.x * xf(0.5f)), Head.y - xf(13.f)), g_color_white, caption);
				}
				if (settings->esp_styles.weapon_nametag) {
					const auto caption = tbox.weapon_name.c_str();
					calc = ImGui::CalcTextSize(caption);
					draw_list->AddText(ImVec2(Feet.x - (calc.x * xf(0.5f)) - xf(1.f), Feet.y + xf(2.f)), g_color_black, caption);
					draw_list->AddText(ImVec2(Feet.x - (calc.x * xf(0.5f)), Feet.y + (1.f)), g_color_white, caption);
				}
				if (settings->esp_styles.health) {

					float max_health = tbox.scientist ? xf(150.f) : xf(100.f);
					float BoxHeight = h;
					float HealthPosVal = (tbox.health / max_health);
					//	w *= 0.25f;
					//	w -= 1.f;

					draw_list->AddRectFilled({ x + w - 2.f ,  Feet.y + h }, { x + w - 2.f + 1.f, Feet.y }, ImColor(0, 0, 0), 100.f);
					draw_list->AddRectFilled({ x + w - 2.f,  Feet.y + (h * HealthPosVal) }, { x + w - 2.f + 1.f, Feet.y }, ImColor(0, 255, 0), 100.f);


				}
			}

		}
	}

		ImGui::PopFont();

		ImGui::Render();
		glViewport(0, 0, g_width, g_height);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(g_window);
	
}


void entityLoop() {
	CloseHandle(GetCurrentThread());
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);
	uint64_t counter{};
    while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		u_cache();
	}
}
int main()
{


		//FreeConsole();
		CloseHandle(GetCurrentThread());
       // set_timer_resolution();//windows trick (timer resolution) (make cheat feel better overall)
	//	set_process_priority(HIGH_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
		std::cout << "press any key to continue" << std::endl;
		getchar();
		//FreeConsole();
		//process_id = memory.
		game_window = FindWindowA("UnityWndClass", NULL);
		
//		driver::process_id = process_id;
		
		//game_window = FindWindow(e("UnityWndClass"), e("Rust"));

		std::cout << std::hex << GameAssembly << std::endl;//debug
		std::cout << std::hex << UnityPlayer << std::endl;//debug
		cache::game_assembly = reinterpret_cast<c_game_assembly*>(GameAssembly);
		std::cout << "press any key to continue" << std::endl;
		getchar();
		exit(0);
		/*
	//	FreeConsole();
		mutex_ = std::make_unique<_Mutex>();
		mutex_->shared = std::make_unique<sf::contention_free_shared_mutex<>>();
		std::thread(hkp).detach();  // handle the insert (toggle menu) key without spamming asynckeystate in render thread 
		std::thread(entityLoop).detach(); // cache ents
		std::thread(capturePositions).detach(); // grab positions optimally		
		std::thread(perfect_silent_thread).detach(); // silent needs its own thread	
		std::thread(slow).detach();	// slow thread
		std::thread(view_offset_debug).detach();	// slow thread
		

		setupWindow(); //create topmost overlay	
		HWND overlay_window = glfwGetWin32Window(g_window);
		SetForegroundWindow(overlay_window);
		glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, false);

		while (true)
		{
			runRenderTick(); // render in render thread
			Sleep(1);
		};
		return 1;
		*/
}

