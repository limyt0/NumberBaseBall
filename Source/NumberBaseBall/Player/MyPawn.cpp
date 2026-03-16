#include "Player/MyPawn.h"
#include "NumberBaseBall.h"

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = BaseChatFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("MyPawn::BeginPlay() %s [%s]"), *BaseChatFunctionLibrary::GetNetModeString(this), *NetRoleString);
	BaseChatFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void AMyPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = BaseChatFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *BaseChatFunctionLibrary::GetNetModeString(this), *NetRoleString);
	BaseChatFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}