#include "Game/MyGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerController.h"

void AMyGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			AMyPlayerController* MyPC = Cast<AMyPlayerController>(PC);
			if (IsValid(MyPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				MyPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}
