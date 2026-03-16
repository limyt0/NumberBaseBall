#include "MyGameModeBase.h"
#include "MyGameStateBase.h"

void AMyGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AMyGameStateBase* MyGameStateBase = GetGameState<AMyGameStateBase>();
	if (IsValid(MyGameStateBase) == true)
	{
		MyGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXXX"));
	}
}
