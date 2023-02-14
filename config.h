class config
{
public:
	struct {
		bool always_eoka;
		bool shotgun_nospread;
		bool recoil_modifier;
		float recoil = 100.f;
		std::string aimkey = "right mouse";
		int i_aimKey = 2;
		bool silent;
		bool aim_npc;
		bool aim_smooth;
		bool spider;
		bool chest;
		float smoothing_x;
		float smoothing_y;
		bool aimbot;
		bool aim_fov = true;
		bool thick_bullet = false;
		bool fast_bullet;
		float thickness = 1.0f;
		bool nospread;
		bool norecoil;
		bool super_eoka;
		bool superjump;
		bool omnisprint;
		bool shoot_anywhere;
		bool flyhack;
		bool fakelag;
		bool instant_eoka;
		bool always_automatic;
		bool mounted_shoot;
		bool tpbullet;
		bool insta_eoka;
		bool readyBow;
		bool aim_team = true;
		bool insta_compound = false;
		bool melee_sprint;
		bool melee_range;

		float fov = 100.f;
	}features;
	struct {
		float draw_distance = false;
		bool players = false;
		bool npc = false;
		bool animals = false;
		bool sleeper_esp = false;
	}moving_esp;

	struct {
		bool weapon_nametag;
		bool health;
		bool rectangle;
		bool cham;
		bool culling;
		bool nametags;
	}esp_styles;

	struct
	{
		float draw_distance;
		bool corpse;
		bool mil_crate;
		bool radtown_crate;
		bool toolbox_crate;
		bool radtown_barrel;
		bool oil_barrel;
		bool minecart_crate;
		bool elite_crate;
		bool backpack;
		bool minicopter;
		bool supply_drop;
		bool locked_crate;
		bool dropped_items;
		bool ores = false;
		bool vehicles = false;
		bool radtown = false;
		bool barrels = false;
		bool collectables = false;
		bool stash;
		bool world;
		bool modular_cars;
		bool animals;
		bool bear;
		bool patrol_heli;
		bool bradley_apc;
		bool boat;
		bool rhib;
		bool autoturret;
		bool stag;
		bool scrappy;
		bool chicken;
		bool horse;
		bool deer;
		bool boar;
		bool traps = false;
		bool hemp;
		bool stone;
		bool sulfur;
		bool metal;
		bool stone_collectables;
		bool metal_collectables;
		bool sulfur_collectables;
		bool wood_collectables;
		bool med_crate;
		bool sam_site;
		bool landmine;
		bool shotgun_trap;
		bool bear_trap;
		bool corn;
		bool mushroom;
		bool potato;
		bool pumpkin;
		bool flame_turret;
		bool food_crate;
	}resources;


	struct {
		Vector3 pumpkin = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 potato = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 corn = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 mushroom = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };


		Vector3 modular_cars = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };

		Vector3 minicopter = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 scrappy = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 patrol_heli = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 bradley_apc = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 boat = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 rhib = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 autoturret = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 shotgun_trap = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 sam_site = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 landmine = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 flame_turret = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 bear_trap = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };

		Vector3 bear = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 deer = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 stag = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 chicken = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 boar = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 horse = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 radtown_barrel = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 oil_barrel = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 radtown_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 toolbox_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 minecart_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 med_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 food_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 mil_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 elite_crate = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 stone_ore = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 sulfur_ore = { 255.f / 255.f,128.f / 255.f,0.f };
		Vector3 metal_ore = { 128.f / 255.f, 128.f / 255.f, 128.f / 255.f };
		Vector3 hemp_collectables = {0.f,200.f / 255.f,0.f};
		Vector3 stone_collectables = { 160.f / 255.f, 160.f / 255.f, 160.f / 255.f };
		Vector3 wood_collectables = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 stash = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 corpse = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 dropped_items = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 backpack = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 locked_crate = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 supply_drop = { 102.f / 255.f, 51.f / 255.f, 0.f };
		Vector3 sulfur_collectables = { 255.f / 255.f,128.f / 255.f,0.f };
		Vector3 metal_collectables = { 128.f / 255.f, 128.f / 255.f, 128.f / 255.f };
	}colors;

};

static config* settings = new config();