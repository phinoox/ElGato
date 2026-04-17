#pragma once

namespace GATOCONFIG
{
	/* the folder for automatically generated assets inside the data folder set in the plugin config*/
	constexpr FStringView DEFAULT_ASSET_PATH = TEXTVIEW("Default/"); 
	/* DataTable for access to all Gato Gameplay Effects*/
	constexpr FStringView DT_EFFECTS_NAME = TEXTVIEW("EffectData");
	/* DataTable for access to all Gato Gameplay Effects*/
	constexpr FStringView ST_EFFECTS_NAME = TEXTVIEW("EffectStrings");
	
	/* DataTable for access to all Gato Gameplay Abilities*/
	constexpr FStringView DT_ABILITIES_NAME = TEXTVIEW("AbilityData");
	/* DataTable for access to all Gato Gameplay Abilities*/
	constexpr FStringView ST_ABILITIES_NAME = TEXTVIEW("AbilityStrings");
	
	/* Prefix for automatically generated attributelevel curve tables*/
	constexpr FStringView CT_ATTRIBUTELEVELS_PREFIX = TEXTVIEW("CT_AttributeLevels_");
	/* Prefix for automatically generated attribute Data tables*/
	constexpr FStringView DT_ATTRIBUTS_PREFIX = TEXTVIEW("DT_Attributes_");
	
	constexpr FStringView DA_GAMEPLAY_PREFIX = TEXTVIEW("DA_Gameplay_");
	constexpr FStringView DA_ABILITYSET_PREFIX = TEXTVIEW("DA_AbilitySet_");
	constexpr FStringView DA_EFFECTSET_PREFIX = TEXTVIEW("DA_EffectSet_");
}
