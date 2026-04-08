#pragma once

#include "CoreMinimal.h"
#include "Attributes/GaMaMainAttributeSet.h"
#include "FMainAttributeData.generated.h"

USTRUCT(BlueprintType)
struct FLeveledAttributeData : public FTableRowBase
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AttributeSet")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AttributeSet")
	FCurveTableRowHandle Value;
	
};



UCLASS()
class GASMASTER_API UAttributeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category= "Save",meta=(Keywords="Save"))
	static bool SaveAttributes(FString SaveDirectory,FString FileName,UDataTable* DataTable,bool AllowOverWriting);
	
};
