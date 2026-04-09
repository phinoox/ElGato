// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GaToTags
{
	/**
	 * Tag for walking mode
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Walk);

	/**
	 * Tag for running mode
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Run);
	
	/**
	 * Tag for Swimming mode
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Swimming);
	
	/**
	 * Tag for Flying mode
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Flying);
	
	/**
	 * Status tag for damaged Characters
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Teleported);
	
	/**
	 * Status Tag for stunned characters
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Stunned);
	
	/**
	 * Status Tag for immobile characters
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Immobile);
	
	/**
	 * Status Tag for immobile characters
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Invincible);
	
	/**
	 * Status tag for damaged Characters
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Damaged);
	/**
	 * Status tag for dead Characters
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Dead);
	/**
	 * General Tag for active Abilities 
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Abilities_General_Active);
	/**
	 * General Tag for active Abilities 
	 */
	GASMASTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Hit);

}
