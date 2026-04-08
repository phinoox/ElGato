#pragma once
#include "CoreMinimal.h"
#include "GaMaActorInterface.generated.h"

class UGaMaGamePlayAssetComponent;
class UGaMaAbilitySystemComponent;
class UGaMaMainAttributeSet;

UINTERFACE(MinimalAPI,NotBlueprintable)
class GASMASTER_API UGaMaActorInterface : public UInterface
{
GENERATED_BODY()
};

class  GASMASTER_API IGaMaActorInterface
{

GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable)
    virtual UGaMaAbilitySystemComponent* GetGaMaAbilitySystemComponent() const = 0;
    
    UFUNCTION(BlueprintCallable)
    virtual UGaMaGamePlayAssetComponent* GetGaMaGamePlayAssetComponent() const = 0;
    
    UFUNCTION(BlueprintCallable)
    virtual UGaMaMainAttributeSet* GetGaMaMainAttributeSet() const = 0;
        
};
