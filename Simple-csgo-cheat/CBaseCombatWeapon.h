#pragma once
#include "CMemory.h"

enum CSGO_Weapon_ID
{
	weapon_none,
	weapon_deagle,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_p228,
	weapon_usp,
	weapon_ak47,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galil,
	weapon_galilar,
	weapon_m249,
	weapon_m3,
	weapon_m4a1,
	weapon_mac10,
	weapon_mp5navy,
	weapon_p90,
	weapon_scout,
	weapon_sg550,
	weapon_sg552,
	weapon_tmp,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_scar17,
	weapon_scar20,
	weapon_sg556,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4
};

class CBaseCombatWeapon
{
private:
	int m_iWeaponId;
public:
	void setWeaponID(int weaponID);
	int getWeaponID();
	std::string getWeaponNameByIndex(short weaponIndex);
};