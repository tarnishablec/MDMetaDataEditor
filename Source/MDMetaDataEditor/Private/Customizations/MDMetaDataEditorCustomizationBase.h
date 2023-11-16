// Copyright Dylan Dumesnil. All Rights Reserved.

#pragma once

#include "IDetailCustomization.h"
#include "Input/Reply.h"
#include "Layout/Visibility.h"
#include "Runtime/Launch/Resources/Version.h"
#include "UObject/WeakFieldPtr.h"

namespace ETextCommit
{
#if ENGINE_MAJOR_VERSION > 5 || ENGINE_MINOR_VERSION >= 2
	enum Type : int;
#else
	enum Type;
#endif
}

class IBlueprintEditor;
class SWidget;
class UBlueprint;
class UK2Node_CustomEvent;
class UK2Node_FunctionEntry;
class UK2Node_Tunnel;
enum class ECheckBoxState : uint8;
struct FMDMetaDataKey;

class FMDMetaDataEditorCustomizationBase : public IDetailCustomization
{
public:
	FMDMetaDataEditorCustomizationBase(const TWeakPtr<IBlueprintEditor>& BlueprintEditor, TWeakObjectPtr<UBlueprint>&& BlueprintPtr);

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

private:
	EVisibility GetRemoveMetaDataButtonVisibility(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	FReply OnRemoveMetaData(FName Key, TWeakFieldPtr<FProperty> PropertyPtr);

	TSharedRef<SWidget> CreateMetaDataValueWidget(const FMDMetaDataKey& Key, FProperty* Property);

	void AddMetaDataKey(const FName& Key, TWeakFieldPtr<FProperty> PropertyPtr);
	void SetMetaDataValue(const FName& Key, const FString& Value, TWeakFieldPtr<FProperty> PropertyPtr);
	bool HasMetaDataValue(const FName& Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	TOptional<FString> GetMetaDataValue(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	void RemoveMetaDataKey(const FName& Key, TWeakFieldPtr<FProperty> PropertyPtr);

	void CopyMetaData(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	bool CanCopyMetaData(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	void PasteMetaData(FName Key, TWeakFieldPtr<FProperty> PropertyPtr);
	bool CanPasteMetaData(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;

	template<bool bIsBoolean>
	ECheckBoxState IsChecked(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	template<bool bIsBoolean>
	void HandleChecked(ECheckBoxState State, FName Key, TWeakFieldPtr<FProperty> PropertyPtr);
	template<bool bIsBoolean>
	FText GetCheckBoxToolTip(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;

	FText GetMetaDataValueText(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	void OnMetaDataValueTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, FName Key, TWeakFieldPtr<FProperty> PropertyPtr);

	TOptional<int32> GetMetaDataValueInt(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	void OnMetaDataValueIntCommitted(int32 Value, ETextCommit::Type InTextCommit, FName Key, TWeakFieldPtr<FProperty> PropertyPtr);

	TOptional<float> GetMetaDataValueFloat(FName Key, TWeakFieldPtr<FProperty> PropertyPtr) const;
	void OnMetaDataValueFloatCommitted(float Value, ETextCommit::Type InTextCommit, FName Key, TWeakFieldPtr<FProperty> PropertyPtr);

	TWeakPtr<IBlueprintEditor> BlueprintEditor;
	TWeakObjectPtr<UBlueprint> BlueprintPtr;

	TWeakFieldPtr<FProperty> PropertyBeingCustomized;
	TWeakObjectPtr<UK2Node_FunctionEntry> FunctionBeingCustomized;
	TWeakObjectPtr<UK2Node_Tunnel> TunnelBeingCustomized;
	TWeakObjectPtr<UK2Node_CustomEvent> EventBeingCustomized;
};
