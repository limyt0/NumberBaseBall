#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UMyChatInput;

UCLASS()
class NUMBERBASEBALL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMyChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr< UMyChatInput> ChatInputWidgetInstance;
	
	FString ChatMessageString;
};
