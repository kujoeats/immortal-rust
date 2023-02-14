#include "driver.hpp"
#include "vectors.h"//transform
#include <map>
#include "skcrypt.h"

ULONG64 UnityPlayer;
ULONG64 GameAssembly;
uintptr_t Camera;


struct unity_str
{
	char buffer[128];
};
struct ProjectileWeaponModModifier
{
	bool enabled;
	float scalar;
	float offset;
};




std::unordered_map<std::string, vec4_t> m_vecRecoilProperties;
class c_item_definition
{
public:


	auto get_shortname() -> const std::wstring
	{
		const auto shortname = memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_shortname);

		if (!shortname)
		{
			return std::wstring();
		}

		const auto buffer = std::make_unique<wchar_t[]>(64);

		memory.read(shortname + 0x14, buffer.get(), 64 * sizeof(wchar_t));

		return std::wstring(buffer.get());
	}
	auto get_shortnameS() -> const std::string
	{
		const auto shortname = memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_shortname);

		if (!shortname)
		{
			return std::string();
		}
		const auto buffer = std::make_unique<wchar_t[]>(64);
		memory.read(shortname + 0x14, buffer.get(), 64 * sizeof(wchar_t));
		std::wstring buf = (buffer.get());
		std::string result;
		for (char x : buf) {
			result += x;
		}
		return result;
	}

};
class c_primary_magazine
{
public:

	/*
	public class BaseProjectile.Magazine // TypeDefIndex: 10250
	// Fields
	public BaseProjectile.Magazine.Definition definition; // 0x10
	*/
	auto get_item_definition() -> c_item_definition*
	{
		return memory.read<c_item_definition*>(reinterpret_cast<std::uintptr_t>(this) + m_item_definition);
	}




};
class c_new_recoil_override
{
public:
	auto get_recoil() -> vec4_t
	{
		return memory.read<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min);
	}
	auto set_time_to_take_max(const float time) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_time_to_take_max, time);
	}

	auto set_aimcone_curve_scal(const float scale) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_curve_scale, scale);
	}

	auto get_time_to_take_max() -> const float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_time_to_take_max);
	}

	auto get_aimcone_curve_scal() -> const float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_curve_scale);
	}

	auto set_recoil_vector(const vec4_t vector) -> void
	{
		memory.write<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min, vector);
	}

	auto set_recoil_yaw_min(const float min) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min, min);
	}

	auto set_recoil_yaw_max(const float max) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_max, max);
	}

	auto set_recoil_pitch_min(const float min) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_pitch_min, min);
	}

	auto set_recoil_pitch_max(const float max) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_pitch_max, max);
	}
};


class c_recoil_properties
{
public:
	auto set_recoil_vector(const vec4_t vector) -> void
	{
		memory.write<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min, vector);
	}
	auto get_recoil() -> vec4_t
	{
		return memory.read<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min);
	}
	auto get_time_to_take_max() -> float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_time_to_take_max);
	}
	auto set_time_to_take_max(const float time) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_time_to_take_max, time);
	}

	auto set_aimcone_curve_scal(const float scale) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_curve_scale, scale);
	}

	auto set_recoil_yaw_min(const float min) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min, min);
	}

	auto set_recoil_yaw_max(const float max) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_max, max);
	}

	auto set_recoil_pitch_min(const float min) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_pitch_min, min);
	}

	auto set_recoil_pitch_max(const float max) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_pitch_max, max);
	}
	auto get_new_recoil_overrid() -> c_new_recoil_override*
	{
		return memory.read<c_new_recoil_override*>(reinterpret_cast<std::uintptr_t>(this) + m_new_recoil_override);
	}
};


class c_held
{
public:
	auto set_recoil_yaw_min(const float min) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_min, min);
	}

	auto set_recoil_yaw_max(const float max) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_yaw_max, max);
	}

	auto set_recoil_pitch_min(const float min) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_pitch_min, min);
	}

	auto set_recoil_pitch_max(const float max) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_recoil_pitch_max, max);
	}
	auto get_automatic() -> bool
	{
	return		memory.read<bool>(reinterpret_cast<std::uintptr_t>(this) + m_automatic);

	}
	auto set_automatic(const bool enabled) -> auto
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t>(this) + m_automatic, enabled);

	}
	auto get_b_automatic() -> bool
	{
	return	memory.read<bool>(reinterpret_cast<std::uintptr_t>(this) + m_bautomatic);

	}
	auto set_b_automatic(const bool enabled) -> auto
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t>(this) + m_bautomatic, enabled);

	}
	auto get_block_sprint_on_attack() -> bool
	{
		return memory.read<bool>(reinterpret_cast<std::uintptr_t>(this) + m_block_sprint_on_attack);
	}
	auto set_block_sprint_on_attack(const bool enabled) -> auto
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t>(this) + m_block_sprint_on_attack, enabled);
	}
	auto get_attack_distance() -> float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + m_attack_dist);
	}
	auto set_attack_distance(const float dist) -> auto
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_attack_dist, dist);
	}
	auto get_string_max_duration() -> float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + m_string_max_hold_duration);
	}
	auto set_string_max_duration(const float fraction) -> auto
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_string_max_hold_duration, fraction);
	}
	auto get_string_movement_penalty() -> float
	{
	return 	memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + m_string_movement_penalty);
	}
	auto set_string_movement_penalty(const float fraction) -> auto
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_string_max_movement_penalty, fraction);
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_string_movement_penalty, fraction);
	}
	auto get_attack_ready() {
		return 	memory.read<bool>(reinterpret_cast<std::uintptr_t>(this) + m_attack_ready);
	}
	auto set_attack_ready(const bool fraction) -> auto
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t>(this) + m_attack_ready, fraction);
	}
	auto get_success_fraction() -> bool
	{
	return	memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + m_success_fraction);
	}
	auto set_success_fraction(const float fraction) -> auto
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_success_fraction, fraction);
	}
	auto set_striking(const uint8_t fraction) -> auto
	{
		memory.write<uint8_t>(reinterpret_cast<std::uintptr_t>(this) + m_striking, fraction);
	}
	auto set_did_spark_this_frame(const uint8_t fraction) -> auto
	{
		memory.write<uint8_t>(reinterpret_cast<std::uintptr_t>(this) + m__did_spark_this_frame, fraction);
	}

	auto set_aimcon(const float aimcone) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone, aimcone);
	}
	auto get_aimcone() -> float
	{
		return	memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone);
	}


	auto set_hip_aimcon(const float aimcone) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_hip_aimcone, aimcone);
	}

	auto set_aimcone_penalty_per_shot(const float penalty) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_penalty_per_shot, penalty);
	}

	auto set_aimcone_penalty_max(const float penalty) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_penalty_max, penalty);
	}

	auto set_aimcone_penalty_recover_tim(const float penalty) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_penalty_recover_time, penalty);
	}

	auto set_aimcone_penalty_recover_delay(const float penalty) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimcone_penalty_recover_delay, penalty);
	}
	auto set_gun_burst(bool burst) -> void
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t> (this) + 0x312, burst);
	}

	auto get_shots_fired() -> int
	{
		return		memory.read<int>(reinterpret_cast<std::uintptr_t> (this) + 0x33C);

	}
	auto set_burst_int(const int sway) -> void
	{
		memory.write<int>(reinterpret_cast<std::uintptr_t> (this) + 0x388, sway);

	}
	auto get_bursts() -> int
	{
		return	memory.read<int>(reinterpret_cast<std::uintptr_t> (this) + 0x388);

	}
	
		auto set_burst_scale(const float sway) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + 0x31C, sway);

	}	
		auto set_repeat_delay(const float sway) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + 0x1FC, sway);
	}

		
	auto set_aim_sway(const float sway) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aim_sway, sway);
	}

	auto set_stance_penalty(const float penalty) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_stance_penalty, penalty);
	}

	auto set_aimcone_penalty(const float penalty) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aimconePenalty, penalty);
	}

	auto set_sight_aimcone_scal(const float scale) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_sight_aim_cone_scale, scale);
	}

	auto set_sight_aimcone_offset(const float offset) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_sight_aim_cone_offset, offset);
	}

	auto set_hip_aimcone_scal(const float scale) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_hip_aim_cone_scale, scale);
	}

	auto set_hip_aimcone_offset(const float offset) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_hip_aim_cone_offset, offset);
	}

	auto set_aim_sway_speed(const float speed) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_aim_sway_speed, speed);
	}

	auto set_did_spark_this_tim(const bool sparked) -> auto
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m__did_spark_this_frame, sparked);
	}

	auto get_pvs() -> float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_projectileVelocityScale);//projectilevelocityscale
	}
	auto set_pvs(const float speed)
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_projectileVelocityScale, speed);//projectilevelocityscale
	}
	auto get_primary_magazin() -> c_primary_magazine*
	{
		return memory.read<c_primary_magazine*>(reinterpret_cast<std::uintptr_t> (this) + m_primary_magazine);
	}

	auto get_recoil_propreties() -> c_recoil_properties*
	{
		return memory.read<c_recoil_properties*>(reinterpret_cast<std::uintptr_t>(this) + m_recoil);
	}

	auto get_created_projectiles(void (*each)(std::uintptr_t)) -> void
	{

		const auto key = memory.read_chain<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this), { m_created_projectiles, 0x10 });


		if (!key)
		{
			return;
		}
		for (int i = 0; i < 1; ++i)
		{
			const auto projectile = memory.read<std::uintptr_t>(key + (0x20 + (i * 0x8)));

			if (!projectile)
			{
				continue;
			}

			each(projectile);
		
		}
	}
	auto get_all_created_projectiles(void (*each)(std::uintptr_t)) -> void
	{
		const auto list = memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_created_projectiles);

		if (!list)
		{
			return;
		}

		const auto key = memory.read<std::uintptr_t>(list + 0x10);

		if (!key)
		{
			return;
		}

		const auto size = memory.read<int>(list + 0x18);

		if (!size)
		{
			return;
		}

		for (int i = 0; i < size; ++i)
		{
			const auto projectile = memory.read<std::uintptr_t>(key + 0x20 + (i * 0x8));

			if (!projectile)
			{
				continue;
			}

			each(projectile);
		}
	}

};

class c_projectile
{
public:

	auto get_item_definition() -> c_item_definition*
	{
		return memory.read<c_item_definition*>(reinterpret_cast<std::uintptr_t>(this) + m_item_definition);
	}

	auto is_weapon() -> bool
	{
		const auto item_definition = this->get_item_definition();

		if (!item_definition)
		{
			return false;
		}

		const auto name = item_definition->get_shortname();

		if (name.empty())
		{
			return false;
		}

		if (name.find(e(L"rifle")) != std::string::npos)
		{
			return true;
		}

		if (name.find(e(L"pistol")) != std::string::npos)
		{
			return true;
		}

		if (name.find(e(L"bow")) != std::string::npos)
		{
			return true;
		}

		if (name.find(e(L"lmg")) != std::string::npos)
		{
			return true;
		}

		if (name.find(e(L"shotgun")) != std::string::npos)
		{
			return true;
		}

		if (name.find(e(L"smg")) != std::string::npos)
		{
			return true;
		}

		return false;
	}

	auto get_uid() -> uint32_t
	{
		return memory.read<uint32_t>(reinterpret_cast<std::uintptr_t> (this) + 0x28);
	}

	auto get_id() -> uint32_t
	{
		return memory.read_chain<uint32_t>(reinterpret_cast<std::uintptr_t> (this), { 0x20, 0x18 });
	}

	auto get_held() -> c_held*
	{
		return memory.read<c_held*>(reinterpret_cast<std::uintptr_t>(this) + m_held_entity);
	}
};


uintptr_t get_component(uintptr_t gameObject, const char* componentNameStr)
{
	if (!gameObject)
		return NULL;

	uintptr_t componentList = memory.read<uintptr_t>(gameObject + 0x30);
	for (int h = 0; h < 20; h++) 
	{
		uintptr_t component = memory.read<uintptr_t>(componentList + (0x10 * h + 0x8));
		if (!component)
			continue;

		uintptr_t unk1 = memory.read<uintptr_t>(component + 0x28);
		if (!unk1)
			continue;

		uintptr_t componentName = memory.read<uintptr_t>(unk1 + 0x0);

		std::string name = memory.ReadASCII(componentName + 0x10, 18);
		if (strcmp(name.c_str(), componentNameStr) == 0)
			return unk1;
	}

	return NULL;
}
enum class category
{
	shirt = 0,
	pants = 5,
	jacket = 1,
	hat = 2,
	mask = 3,
	footwear = 4,
	weapon = 6,
	misc = 7,
	deployable = 9,
	gloves = 10,
};

template <typename t>
class c_array
{
public:

	auto size() -> const std::uint32_t
	{
		return memory.read<std::uint32_t>(reinterpret_cast<std::uintptr_t>(this) + 0x18);
	}

	auto get(const std::uint32_t idx) -> t
	{
		return memory.read<t>(reinterpret_cast<std::uintptr_t>(this) + 0x20ull + (idx * 0x8ull));
	}
};
class c_groups
{
public:

	auto set_material(const std::uintptr_t material) -> void
	{
		memory.write<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_skinnable_material, material);
	}
};
class c_skin_set
{
public:

	auto set_head_material(const std::uintptr_t material) -> void
	{
		memory.write<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_head_material, material);
	}

	auto set_body_material(const std::uintptr_t material) -> void
	{
		memory.write<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_body_material, material);
	}

	auto set_eye_material(const std::uintptr_t material) -> void
	{
		memory.write<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_eye_material, material);
	}

	auto get_head_material() -> const std::uintptr_t
	{
		return memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_head_material);
	}

	auto get_body_material() -> const std::uintptr_t
	{
		return memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_body_material);
	}

	auto get_eye_material() -> const std::uintptr_t
	{
		return memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_eye_material);
	}
};

class c_skin
{
public:

	auto get_skin_set() -> c_array<c_skin_set*>*
	{
		return memory.read< c_array<c_skin_set*>*>(reinterpret_cast<std::uintptr_t>(this) + m_skin_set);
	}
};






#define _(str) e(str)



inline float bullet_gravity(const char* bullet_name)
{
	if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
		return 1.f;
	}
	if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
		return 1.f;
	}
	if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
		return 1.25f;
	}
	if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
		return 1.f;
	}

	if (_stricmp(bullet_name, _("ammo.pistol")) == NULL) {
		return 1.f;//1.f?
	}
	if (_stricmp(bullet_name, _("ammo.pistol.hv")) == NULL) {
		return 1.f;//1.f?
	}
	if (_stricmp(bullet_name, _("ammo.pistol.incendiary")) == NULL) {
		return 1.f;
	}

	if (_stricmp(bullet_name, _("arrow.hv")) == NULL) {
		return 0.5f;
	}
	if (_stricmp(bullet_name, _("arrow.bone")) == NULL) {
		return 0.75f;
	}
	if (_stricmp(bullet_name, _("arrow.wooden")) == NULL) {
		return 0.75f;
	}
	if (_stricmp(bullet_name, _("arrow.fire")) == NULL) {
		return 1.f;
	}

	if (_stricmp(bullet_name, _("ammo.handmade.shell")) == NULL) {
		return 1.f;
	}
	if (_stricmp(bullet_name, _("ammo.shotgun")) == NULL) {
		return 1.f;
	}
	if (_stricmp(bullet_name, _("ammo.shotgun.fire")) == NULL) {
		return 1.f;
	}
	if (_stricmp(bullet_name, _("ammo.shotgun.slug")) == NULL) {
		return 1.f;
	}

	if (_stricmp(bullet_name, _("ammo.nailgun.nails")) == NULL) {
		return 0.75f;
	}

	return 1.f;
}

inline bool has_gun_out(const char* weapon_name)
{
	if (strstr(weapon_name, _("snowball"))) {
		return false;
	}
	if (strstr(weapon_name, _("rock"))) {
		return false;
	}
	else if (strstr(weapon_name, _("rifle"))) {
		return true;
	}
	
	else if (strstr(weapon_name, _("smg"))) {
		return true;
	}
	else if (strstr(weapon_name, _("hmlmg"))) {
		return true;
	}
	else if (strstr(weapon_name, _("m249"))) {
		return true;
	}
	else if (strstr(weapon_name, _("pistol"))) {
		return true;
	}
	else if (strstr(weapon_name, _("shotgun"))) {
		return true;
	}
	else if (strstr(weapon_name, _("bow"))) {
		return true;
	}
	return false;
	}




inline float get_bullet_velocity(const char* weapon_name, const char* bullet_name)
{
	/* rifle ammo */

	if (_stricmp(weapon_name, _("rifle.ak")) == NULL
		|| _stricmp(weapon_name, _("rifle.lr300")) == NULL || _stricmp(weapon_name, _("hmlmg"))) {

		if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
			return 375.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
			return 450.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
			return 225.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
			return 225.f;
		}
	}

	if (_stricmp(weapon_name, _("rifle.bolt")) == NULL) {
		if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
			return 656.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
			return 788.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
			return 394.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
			return 394.f;
		}
	}

	if (_stricmp(weapon_name, _("rifle.l96")) == NULL) {
		if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
			return 1125.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
			return 1350.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
			return 675.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
			return 675.f;
		}
	}

	if (_stricmp(weapon_name, _("rifle.m39")) == NULL) {
		if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
			return 469.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
			return 563.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
			return 281.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
			return 281.f;
		}
	}

	if (_stricmp(weapon_name, _("rifle.semiauto")) == NULL) {
		if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
			return 375.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
			return 450.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
			return 225.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
			return 225.f;
		}
	}


	if (_stricmp(weapon_name, _("lmg.m249"))) {
		if (_stricmp(bullet_name, _("ammo.rifle")) == NULL) {
			return 487.5f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.hv")) == NULL) {
			return 585.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.explosive")) == NULL) {
			return 293.f;
		}
		if (_stricmp(bullet_name, _("ammo.rifle.incendiary")) == NULL) {
			return 293.f;
		}
	}

	/* pistol ammo */

	if (_stricmp(weapon_name, _("smg.2")) == NULL
		|| _stricmp(weapon_name, _("smg.mp5")) == NULL) {

		if (_stricmp(bullet_name, _("ammo.pistol")) == NULL) {
			return 247.5f;
		}
		if (_stricmp(bullet_name, _("ammo.pistol.hv")) == NULL) {
			return 320.f;
		}
		if (_stricmp(bullet_name, _("ammo.pistol.incendiary")) == NULL) {
			return 180.f;
		}
	}

	if (_stricmp(weapon_name, _("pistol.m92")) == NULL
		|| _stricmp(weapon_name, _("pistol.python")) == NULL
		|| _stricmp(weapon_name, _("pistol.revolver")) == NULL
		|| _stricmp(weapon_name, _("pistol.semiauto")) == NULL
		|| _stricmp(weapon_name, _("smg.thompson")) || _stricmp(weapon_name, _("pistol.prototype17"))) {

		if (_stricmp(bullet_name, _("ammo.pistol")) == NULL) {
			return 300.f;
		}
		if (_stricmp(bullet_name, _("ammo.pistol.hv")) == NULL) {
			return 400.f;
		}
		if (_stricmp(bullet_name, _("ammo.pistol.incendiary")) == NULL) {
			return 225.f;
		}
	}

	/* shotgun ammo */

	if (_stricmp(weapon_name, _("shotgun.double")) == NULL
		|| _stricmp(weapon_name, _("shotgun.pump")) == NULL
		|| _stricmp(weapon_name, _("shotgun.waterpipe")) == NULL
		|| _stricmp(weapon_name, _("shotgun.spas12")) == NULL
		|| _stricmp(weapon_name, _("pistol.eoka")) == NULL) {

		if (_stricmp(bullet_name, _("ammo.shotgun.slug")) == NULL) {
			return 225.f;
		}
		if (_stricmp(bullet_name, _("ammo.shotgun.fire")) == NULL) {
			return 100.f;
		}
		if (_stricmp(bullet_name, _("ammo.handmade.shell")) == NULL) {
			return 100.f;
		}
		if (_stricmp(bullet_name, _("ammo.shotgun.slug")) == NULL) {
			return 225.f;
		}
	}

	/* monkey arrows and monkey guns */

	if (_stricmp(weapon_name, _("bow.hunting")) == NULL) {
		if (_stricmp(bullet_name, _("arrow.hv")) == NULL) {
			return 80.f;
		}
		if (_stricmp(bullet_name, _("arrow.bone")) == NULL) {
			return 45.f;
		}
		if (_stricmp(bullet_name, _("arrow.wooden")) == NULL) {
			return 53.f;
		}
		if (_stricmp(bullet_name, _("arrow.fire")) == NULL) {
			return 40.f;
		}
	}

	if (_stricmp(weapon_name, _("bow.compound")) == NULL) {
		if (_stricmp(bullet_name, _("arrow.hv")) == NULL) {
			return 150.f;
		}
		if (_stricmp(bullet_name, _("arrow.bone")) == NULL) {
			return 90.f;
		}
		if (_stricmp(bullet_name, _("arrow.wooden")) == NULL) {
			return 100.f;
		}
		if (_stricmp(bullet_name, _("arrow.fire")) == NULL) {
			return 80.f;
		}
	}

	if (_stricmp(weapon_name, _("crossbow")) == NULL) {
		if (_stricmp(bullet_name, _("arrow.hv")) == NULL) {
			return 90.f;
		}
		if (_stricmp(bullet_name, _("arrow.bone")) == NULL) {
			return 65.f;
		}
		if (_stricmp(bullet_name, _("arrow.wooden")) == NULL) {
			return 55.f;
		}
		if (_stricmp(bullet_name, _("arrow.fire")) == NULL) {
			return 40.f;
		}
	}

	if (_stricmp(weapon_name, _("pistol.nailgun")) == NULL) {
		return 50.f;
	}

	return 1337.f;
}

float thickness = 1.f;
float initialDistanceExploit = 12.f;


auto disable_fat_bullet(c_held* held)
{
	if (held) {
		auto set_thickness = [](std::uintptr_t each) -> void
		{
			if (each) {
				if (memory.read<float>(each + m_thickness) != 0.1f) {
					memory.write<float>(each + m_thickness, 0.1f);
				}
			}
		};
		held->get_created_projectiles(set_thickness);
	}
}

class c_item_projectile_mod
{
public:
	float get_projectile_vel()
	{
		return	memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + 0x34);
	}

	auto set_projectile_spread(const float spread) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_projectile_spread, spread);
	}

	auto set_projectile_velocity_spread(const float spread) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_projectile_velocity_spread, spread);
	}
};

auto shotgun_nospread(c_projectile* projectile, c_held* held) 
{
	if (projectile && held) {
		auto set_projectile_spread = [](const std::uintptr_t rcx) -> void
		{
			if (rcx) {
				auto item_projectile_mod = memory.read<c_item_projectile_mod*>(rcx + m_mod);

				if (!item_projectile_mod)
				{
					return;
				}

				item_projectile_mod->set_projectile_spread(0.f);
				item_projectile_mod->set_projectile_velocity_spread(0.f);
			}
		};

		held->get_all_created_projectiles(set_projectile_spread);
	}
};


auto fat_bullet(c_held* held)
{
	if (held) {
		auto set_thickness = [](std::uintptr_t each) -> void
		{
			if (each) {
				//	if (memory.read<float>(each + m_thickness) != thickness) {
				memory.write<float>(each + m_thickness, thickness);
				//}
			}
		};
		held->get_created_projectiles(set_thickness);
	}
}
auto fast_bullet(c_held* held)
{
	if (held) {
		auto set_projectile_speed = [](std::uintptr_t each) -> void
		{
			if (each){
				
				if (memory.read<float>(each + m_initialDistance) != initialDistanceExploit) {

					memory.write<float>(each + m_initialDistance, initialDistanceExploit);
				}
				}

		};
		held->get_created_projectiles(set_projectile_speed);
	}
}




inline uintptr_t get_camera_object() { //get camera object
/*
	uintptr_t camera_manager = memory.read<uintptr_t>(camera_manager_offset);
	int count = memory.read<int>(camera_manager_offset + 0x10);
	for (int i = 0; i < count; i++) {
		uintptr_t camera = memory.read<uintptr_t>(camera_manager + (0x8 * i));
		if (!camera)continue;
		uintptr_t cam_name_ptr = memory.read_chain<uintptr_t>(camera, { 0x30, 0x60 });
		std::string cam_name = memory.ReadASCII(cam_name_ptr, 256);
		if (cam_name.find("Main Cam") != std::string::npos) {
			return camera;
		}
	}
}


//  check
inline std::string get_class_name(uintptr_t element)
{
	uintptr_t pName = memory.read_chain<uintptr_t>(element, { 0x0, 0x10 });//class_name
	if (!pName)
		return {};
	std::string c_name = memory.ReadASCII(pName, 32);
	return c_name;
}

class c_transform
{
private:
	struct transform_access_read_only_t
	{
		std::uintptr_t data;
	};

	struct transform_data_t
	{
		std::uintptr_t array;
		std::uintptr_t indices;
	};

	struct matrix34_t
	{
		vec4_t _0;
		vec4_t _1;
		vec4_t _2;
	};

public:

	inline 	auto position() -> Vector3
	{
		if (!reinterpret_cast<std::uintptr_t>(this))
		{
			return { 0.f, 0.f, 0.f };
		}

		 __m128 result{};

		const __m128 mulVec0 = { -2.000f, 2.000f, -2.000f, 0.000f };
		const __m128 mulVec1 = { 2.000, -2.000f, -2.000f, 0.000f };
		const __m128 mulVec2 = { -2.000f, -2.000f, 2.000f, 0.000f };

		transform_access_read_only_t transform_access_read_only = memory.read<transform_access_read_only_t >(reinterpret_cast<std::uintptr_t>(this) + 0x38);

		unsigned int index = memory.read<unsigned int>(reinterpret_cast<std::uintptr_t>(this) + 0x40);

		const auto transform_data = memory.read<transform_data_t>(transform_access_read_only.data + 0x18);

		if (transform_data.array && transform_data.indices)
		{
			result = memory.read<__m128>(transform_data.array + 0x30 * index);

			int transform_index = memory.read<int>(transform_data.indices + 0x4 * index);

			int safe = 0;

			while (transform_index >= 0 && safe++ < 175)
			{
				matrix34_t matrix34 = memory.read<matrix34_t>(transform_data.array + 0x30 * transform_index);

				__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34._1), 0x00));	// xxxx
				__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34._1), 0x55));	// yyyy
				__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34._1), 0x8E));	// zwxy
				__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34._1), 0xDB));	// wzyw
				__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34._1), 0xAA));	// zzzz
				__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34._1), 0x71));	// yxwy
				__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34._2), result);

				result = _mm_add_ps(
					_mm_add_ps(
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
									_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
									_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
						_mm_add_ps(
							_mm_mul_ps(
								_mm_sub_ps(
									_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
									_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
								_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
							tmp7)), *(__m128*)(&matrix34._0));

				transform_index = memory.read<int>(transform_data.indices + 0x4 * transform_index);
			}
		}

		return Vector3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
	}
};
inline Vector3 quatmult(const Vector3* point, vec4_t* quat)
{
	float num = quat->x * 2.f;
	float num2 = quat->y * 2.f;
	float num3 = quat->z * 2.f;
	float num4 = quat->x * num;
	float num5 = quat->y * num2;
	float num6 = quat->z * num3;
	float num7 = quat->x * num2;
	float num8 = quat->x * num3;
	float num9 = quat->y * num3;
	float num10 = quat->w * num;
	float num11 = quat->w * num2;
	float num12 = quat->w * num3;
	Vector3 result;
	result.x = (1.f - (num5 + num6)) * point->x + (num7 - num12) * point->y + (num8 + num11) * point->z;
	result.y = (num7 + num12) * point->x + (1.f - (num4 + num6)) * point->y + (num9 - num10) * point->z;
	result.z = (num8 - num11) * point->x + (num9 + num10) * point->y + (1.f - (num4 + num5)) * point->z;
	return result;
}

const Vector3 vecright = { 1.f, 0.f, 0.f };
const Vector3 vecforward = { 0.f, 0.f, 1.f };
const Vector3 vecup = { 0.f, 1.f, 0.f };

static enum Flags
{
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sleeping = 8,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Aiming = 128,
	Prone = 256,
	Mounted = 512,
	Relaxed = 1024,
	OnPhone = 2048,
	Crawling = 4096
};

class c_modelstate
{
public:
	auto setFlag(const int flag) -> void {
		int current_flags = memory.read<int>(reinterpret_cast<uintptr_t>(this) + 0x24);
		memory.write<int>(reinterpret_cast<uintptr_t>(this) + 0x24, current_flags |= flag);
	}
	bool hasFlag(int flag)
	{
		return (memory.read<int>(reinterpret_cast<uintptr_t>(this) + 0x24)) & flag;
	}
};
auto clamp(float& yaw, float& pitch) -> void
{
	if (yaw > 89.0f)
	{
		yaw = 89.0f;
	}
	if (yaw < -89.0f)
	{
		yaw = -89.0f;
	}
	while (pitch > 180.0f)
	{
		pitch -= 360.0f;
	}
	while (pitch < -180.0f)
	{
		pitch += 360.0f;
	}
}



class c_model
{
public:



	auto is_visibl() -> bool
	{
		return memory.read<bool>(reinterpret_cast<std::uintptr_t> (this) + m_visible);
	}

	
	auto get_skin_type() -> int
	{
		return memory.read<int>(reinterpret_cast<std::uintptr_t>(this) + m_skinType);
	}

	auto get_male_skin() -> c_skin*
	{
		return memory.read<c_skin*>(reinterpret_cast<std::uintptr_t> (this) + m_male_skin);
	}

	auto get_female_skin() -> c_skin*
	{
		return memory.read<c_skin*>(reinterpret_cast<std::uintptr_t> (this) + m_female_skin);
	}
	
	auto get_new_velocity() -> Vector3
	{
		return memory.read<Vector3>(reinterpret_cast<std::uintptr_t> (this) + m_new_velocity);
	}
	
};
class c_eyes
{
public:

	auto set_body_rotation(const vec4_t quaternion) -> void
	{
		memory.write<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_body_rotation, quaternion);
	}

	auto get_body_rotation() -> vec4_t
	{
		return memory.read<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_body_rotation);
	}

	auto set_eye_offset(const Vector3 offset) -> void
	{
		memory.write<Vector3>(reinterpret_cast<std::uintptr_t>(this) + m_viewOffset, offset);
	}
};

class c_movement
{
public:
	auto get_max_walking_angle() -> const float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_max_walking_angle);
	}
		auto set_max_walking_angle(const float angle) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_max_walking_angle, angle);
	}

	auto set_ground_angl(const float angle) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_angle, angle);
	}
	auto get_ground_angl() -> const float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_angle);
	}

	auto set_ground_new_angl(const float angle) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_angle_new, angle);
	}

	auto get_ground_new_angl() -> const float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_angle_new);
	}

	auto set_jump_tim(const float time) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_jump_time, time);
	}

	auto get_Targetmovement() -> const Vector3
	{
		return memory.read<Vector3>(reinterpret_cast<std::uintptr_t> (this) + m_targetMovement);
	}

	auto set_running(const float running) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_running, running);
	}

	auto get_running() -> const float
	{
	return	memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_running);
	}

	auto set_grounded(const float grounded) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_grounded, grounded);
	}
	auto get_grounded() -> const float
	{
		return	memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_grounded);
	}


	auto get_jump_tim() -> const float
	{
		memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_jump_time);
	}

	auto set_land_tim(const float time) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_land_time, time);
	}

	auto get_land_tim() -> const float
	{
		memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_land_time);
	}

	auto set_ground_tim(const float time) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_time, time);
	}

	auto get_ground_tim() -> const float
	{
		memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_ground_time);
	}

	auto get_rotation() -> const vec4_t
	{
		return memory.read<vec4_t>(reinterpret_cast<std::uintptr_t> (this) + m_rotation);
	}

	auto get_position() -> const Vector3
	{
		return memory.read<Vector3>(reinterpret_cast<std::uintptr_t> (this) + m_position);
	}
};
class c_mounted
{
public:
	auto get_can_wield_items() -> bool
	{
		return memory.read<bool>(reinterpret_cast<std::uintptr_t>(this) + m_can_wield_items);
	}
	auto set_can_wield_items(const bool can) -> void
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t>(this) + m_can_wield_items, can);
	}
};
/*
public class InputMessage : IDisposable, Pool.IPooled, IProto // TypeDefIndex: 6285
{
	// Fields
	public bool ShouldPool; // 0x10
	private bool _disposed; // 0x11
	public int buttons; // 0x14
	public Vector3 aimAngles; // 0x18
	public Vector3 mouseDelta; // 0x24
*/


class c_input
{
public:

	void set_body_angles(Vector2 angles) 
	{
		memory.write<Vector2>(reinterpret_cast<std::uintptr_t>(this) + m_bodyAngles, angles); //PlayerInput->body angles


	}
	auto get_body_angles() -> Vector2
	{
		return memory.read<Vector2>(reinterpret_cast<std::uintptr_t>(this) + m_bodyAngles); //PlayerInput->body angles

	}
	auto set_recoil_angles(Vector2 angle) -> void
	{
		 memory.write<Vector2>(reinterpret_cast<std::uintptr_t>(this) + m_recoilAngles, angle); //PlayerInput->body angles

	}
	auto get_recoil_angles() -> Vector2
	{
		return memory.read<Vector2>(reinterpret_cast<std::uintptr_t>(this) + m_recoilAngles); //PlayerInput->body angles

	}

};
template <typename t>
auto get_transform(uintptr_t object, const std::uint32_t i) -> t
{
	return memory.read_chain<t>(object, { 0x130, 0x48, 0x20ull + (i * 0x8), 0x10 });
}

class c_player
{
public:
	auto get_input() -> c_input*
	{
		return memory.read<c_input*>(reinterpret_cast<std::uintptr_t> (this) + m_player_input);//0X4F0 //BasePlayer PlayerInput
	}

	auto set_needs_clothes_rebuild(const bool rebuild) -> void
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t> (this) + m_needs_clothes_rebuild, rebuild);
	}
	
	auto get_eyes() -> c_eyes*
	{
		return memory.read<c_eyes*>(reinterpret_cast<std::uintptr_t> (this) + m_eyes);
	}

	auto get_movement() -> c_movement*
	{
		return memory.read<c_movement*>(reinterpret_cast<std::uintptr_t> (this) + m_base_movement);
	}
	

	auto get_health() -> float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_health);
	}

	auto get_max_health() -> float
	{
		return memory.read<float>(reinterpret_cast<std::uintptr_t> (this) + m_maxhealth);
	}


	auto get_mounted() -> c_mounted*
	{
		return memory.read<c_mounted*>(reinterpret_cast<std::uintptr_t> (this) + m_mounted);
	}
	
	
	auto get_model() -> c_model*
	{
		return memory.read<c_model*>(reinterpret_cast<std::uintptr_t> (this) + m_model);
	}
	
	auto get_modelstate() -> c_modelstate*
	{
		return memory.read<c_modelstate*>(reinterpret_cast<std::uintptr_t> (this) + m_modelstate);
	}



	


	auto is_dead() -> bool
	{
		return memory.read<bool>(reinterpret_cast<std::uintptr_t> (this) + m_life_state);
	}

	auto has_flag(std::uint32_t flag) -> bool
	{
		return (this->get_player_flags() & flag);
	}

	auto is_valid(bool local_player = false, bool sleeper_esp = false) -> bool
	{
		if (!this)
		{
			return false;
		}

		const auto health = this->get_health();

		if (health > 150.f || health < 0.f)
		{
			return false;
		}

		if (local_player)
		{
			return !is_dead();
		}

		return ((!this->has_flag(16) && !sleeper_esp) && !is_dead());
	}
	auto get_client_tick_interval()
	{
	return	memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + m_clientTickInterval);
	}
	auto set_client_tick_rate(int interval)
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + 0x64C, interval);
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + 0x650, interval);
	}

	auto set_client_tick_interval (float interval)
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_clientTickInterval, interval);
	}

	auto set_clothing_blocks_aiming(bool block)
	{
		memory.write<bool>(reinterpret_cast<std::uintptr_t>(this) + m_clothing_blocks_aiming, block);
	}

	//auto set_clothing_move_speed_reduction(float reduction)
//	{
	//	memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_clothing_move_speed_reduction, reduction);
//	}

	//auto set_clothing_water_speed_bonus(float bonus)
	//{
	//	memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_clothingWaterSpeedBonus, bonus);
	//}



	auto get_current_team() -> int
	{
		return memory.read<int>(reinterpret_cast<std::uintptr_t> (this) + m_current_team);
	}

	auto get_player_flags() -> std::uint32_t
	{
		return memory.read<std::uint32_t>(reinterpret_cast<std::uintptr_t> (this) + m_player_flags);
	}

	auto set_player_flags(const std::uint32_t flags) -> void
	{
		memory.write<std::uint32_t>(reinterpret_cast<std::uintptr_t> (this) + m_player_flags, flags);
	}

	
	auto get_projectile() -> c_projectile*
	{
		const int active_uid = memory.read<int>(reinterpret_cast<std::uintptr_t> (this) + m_cl_active_item);

		if (!active_uid)
		{
			return nullptr;
		}


		for (int i = 0; i <= 6; i++)
		{
			const auto projectile = memory.read_chain<c_projectile*>(reinterpret_cast<std::uintptr_t> (this), { m_inventory, 0x28, 0x38, 0x10, 0x20ull + i * 0x08 });
	
			if (!projectile)
			{
				continue;
			}
			
			if (active_uid == (int)projectile->get_uid())
			{
				return projectile;
			}
		}

		return nullptr;
	}

	
	auto get_name() -> std::wstring
	{
		const auto shortname = memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t> (this) + m__display_name);

		if (!shortname)
		{
			return std::wstring();
		}

		const auto buffer = std::make_unique<wchar_t[]>(64);

		memory.read(shortname + 0x14, buffer.get(), 64 * sizeof(wchar_t));

		return std::wstring(buffer.get());
	}

	template <typename t>
	auto get_transform(const std::uint32_t i) -> t
	{
		return memory.read_chain<t>(reinterpret_cast<std::uintptr_t> (this), { 0xB8, 0x48, 0x20ull + (i * 0x8), 0x10 });
	}
};
class c_tod_ambient
{
public:

//	auto get_update_interval() -> float
//	{
///		return memory.read<float>(reinterpret_cast<std::uintptr_t>(this) + m_update_interval);
	//}
///	auto set_update_interval(const float interval) -> void
//	{
	//	memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_update_interval, interval);
	//}
};



class c_tod_day
{
public:

	//auto set_ambient_multiplier(const float multiplier) -> void
	//{
	//	memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + m_ambient_multiplier, multiplier);
	//}
};



class c_tod_scattering
{
public:

	auto get_material() -> const std::uintptr_t
	{
		return memory.read<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this) + m_material);
	}
};

class c_tod_components
{
public:

	auto get_scattering() -> c_tod_scattering*
	{
		return memory.read<c_tod_scattering*>(reinterpret_cast<std::uintptr_t>(this) + m_scattering);
	}
};

class c_tod_light
{
public:
	auto set_update_interval(const float interval) -> void
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + 0x10, interval);
	}


};

class c_tod_sky
{
public:


	auto get_tod_light() -> c_tod_light*
	{
		return memory.read< c_tod_light*>(reinterpret_cast<std::uintptr_t>(this) + 0x80);
	}

	auto set_time_since_last_ambient( float timeSinceLast) 
	{
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + 0x230, timeSinceLast);
		memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + 0x238, timeSinceLast);
		 memory.write<float>(reinterpret_cast<std::uintptr_t>(this) + 0x234, timeSinceLast);
	}
	

	auto get_tod_components() -> c_tod_components*
	{
		return memory.read<c_tod_components*>(reinterpret_cast<std::uintptr_t>(this) + m_components);
	}
	auto get_tod_day() -> c_tod_day*
	{
		return memory.read<c_tod_day*>(reinterpret_cast<std::uintptr_t>(this) + m_day);
	}
};

class c_skinnable
{
public:

	auto get_category() -> category
	{
		return memory.read<category>(reinterpret_cast<std::uintptr_t>(this) + m_category);
	}

	auto get_groups() -> c_array<c_groups*>*
	{
		return memory.read< c_array<c_groups*>*>(reinterpret_cast<std::uintptr_t>(this) + m_groups);
	}

	auto get_all() -> c_array<c_skinnable*>*
	{
		return memory.read< c_array<c_skinnable*>*>(reinterpret_cast<std::uintptr_t>(this) + 0x0);
	}
};

class c_game_assembly
{
public:

	/*
	auto get_convar_client() -> c_convar_client*
	{
		return memory.read_chain<c_convar_client*>(reinterpret_cast<std::uintptr_t>(this), { m_convar_client_c, 0xB8 });
	}
	*/
	
	auto get_skinnable() -> c_skinnable*
	{
		return memory.read_chain<c_skinnable*>(reinterpret_cast<std::uintptr_t>(this), { m_skinnable_c, 0xB8 });
	}
	


	auto get_tod_sky() -> c_tod_sky*
	{
		return memory.read_chain<c_tod_sky*>(reinterpret_cast<std::uintptr_t>(this), { m_tod_sky_c, 0xB8, 0x0, 0x10, 0x20 });
	}
};


auto chams(c_player* player, c_tod_sky* tod_sky, c_skinnable* skinnable)
{
	if (tod_sky && player && skinnable) {
		const auto tod_components = tod_sky->get_tod_components();

		if (!tod_components)
		{
			return;
		}

		const auto tod_scattering = tod_components->get_scattering();

		if (!tod_scattering)
		{
			return;
		}

		const auto material = tod_scattering->get_material();

		if (!material)
		{
			return;
		}

		const auto skinnables = skinnable->get_all();

		for (std::uint32_t i = 0; i < skinnables->size(); i++)
		{
			const auto skin = skinnables->get(i);

			if (!skin)
			{
				continue;
			}

			const auto category = skin->get_category();

			if (category == category::footwear || category == category::mask || category == category::gloves || category == category::hat ||
				category == category::jacket || category == category::pants || category == category::shirt)
			{
				const auto groups = skin->get_groups();

				for (std::uint32_t i = 0; i < groups->size(); i++)
				{
					const auto group = groups->get(i);

					if (!group)
					{
						continue;
					}

					group->set_material(material);
				}
			}
		}

		const auto model = player->get_model();

		if (!model)
		{
			return;
		}

		const auto skin = (model->get_skin_type() == 1 ? model->get_female_skin() : model->get_male_skin());

		if (!skin)
		{
			return;
		}

		const auto skin_set = skin->get_skin_set();

		if (!skin_set)
		{
			return;
		}

		for (std::uint8_t i = 0; i < skin_set->size(); i++)
		{
			auto set = skin_set->get(i);

			if (!set)
			{
				continue;
			}

			set->set_eye_material(material);
			set->set_head_material(material);
			set->set_body_material(material);
		}
	}
};