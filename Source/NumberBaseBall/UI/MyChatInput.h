#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class NUMBERBASEBALL_API UMyChatInput : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;
protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
