#pragma once
#include "CoreMinimal.h"
#include "GaToActorInterface.generated.h"

class UGaToGamePlayAssetComponent;
class UGaToAbilitySystemComponent;
class UGaToMainAttributeSet;

UINTERFACE(MinimalAPI,NotBlueprintable)
class GASMASTER_API UGaToActorInterface : public UInterface
{
GENERATED_BODY()
};

class  GASMASTER_API IGaToActorInterface
{

GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable)
    virtual UGaToAbilitySystemComponent* GetGaToAbilitySystemComponent() const = 0;
    
    UFUNCTION(BlueprintCallable)
    virtual UGaToGamePlayAssetComponent* GetGaToGamePlayAssetComponent() const = 0;
    
    UFUNCTION(BlueprintCallable)
    virtual UGaToMainAttributeSet* GetGaToMainAttributeSet() const = 0;
        
};
