#include "MyPlayerController.h"
#include "UI/MyChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MyGameModeBase.h"
#include "MyPlayerState.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UMyChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void AMyPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		// ServerRPCPrintChatMessageString(InChatMessageString);

		AMyPlayerState* MyPS = GetPlayerState<AMyPlayerState>();
		if (IsValid(MyPS) == true)
		{
			//FString CombinedMessageString = MyPS->PlayerNameString + TEXT(": ") + InChatMessageString;
			FString CombinedMessageString = MyPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;


			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void AMyPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
}

void AMyPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AMyPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	//for (TActorIterator<AMyPlayerController> It(GetWorld()); It; ++It)
	//{
	//	AMyPlayerController* MyPlayerController = *It;
	//	if (IsValid(MyPlayerController) == true)
	//	{
	//		MyPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
	//	}
	//}

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		AMyGameModeBase* MyGM = Cast<AMyGameModeBase>(GM);
		if (IsValid(MyGM) == true)
		{
			MyGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}