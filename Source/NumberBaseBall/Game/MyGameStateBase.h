#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

UCLASS()
class NUMBERBASEBALL_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));
};
