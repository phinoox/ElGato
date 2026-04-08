#include "Data/FMainAttributeData.h"

bool UAttributeLibrary::SaveAttributes(FString SaveDirectory, FString FileName, UDataTable* DataTable,
	bool AllowOverWriting)
{
	SaveDirectory +="/";
	SaveDirectory += FileName;
	
	if (!DataTable){return false;}
	if (AllowOverWriting || !FPaths::FileExists(SaveDirectory))
	{
		FString Content = DataTable->GetTableAsCSV();
		return FFileHelper::SaveStringToFile(Content, *SaveDirectory);
	} else {
		return false;
	}
}
