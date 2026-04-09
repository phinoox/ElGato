// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GaToTags
{
	/**
	 * Tag for walking mode
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Walk);

	/**
	 * Tag for running mode
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Run);
	
	/**
	 * Tag for Swimming mode
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Swimming);
	
	/**
	 * Tag for Flying mode
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Movement_Mode_Flying);
	
	/**
	 * Status tag for damaged Characters
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Teleported);
	
	/**
	 * Status Tag for stunned characters
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Stunned);
	
	/**
	 * Status Tag for immobile characters
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Immobile);
	
	/**
	 * Status Tag for immobile characters
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Invincible);
	
	/**
	 * Status tag for damaged Characters
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Damaged);
	/**
	 * Status tag for dead Characters
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Dead);
	/**
	 * General Tag for active Abilities 
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Abilities_General_Active);
	/**
	 * General Tag for active Abilities 
	 */
	ElGaTo_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Status_Hit);

}
