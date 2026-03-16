#include "MyPlayerController.h"
#include "UI/MyChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MyGameModeBase.h"
#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "NumberBaseBall.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

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
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
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
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
	BaseChatFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
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