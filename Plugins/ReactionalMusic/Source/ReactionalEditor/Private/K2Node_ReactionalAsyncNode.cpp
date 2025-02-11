/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "K2Node_ReactionalAsyncNode.h"
#include "UObject/UnrealType.h"

#include "Kismet/BlueprintAsyncActionBase.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintFunctionNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "GraphEditorSettings.h"
#include "ReactionalBPLibrary.h"

#define LOCTEXT_NAMESPACE "K2Node"

UK2Node_ReactionalAsyncNode::UK2Node_ReactionalAsyncNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyActivateFunctionName = GET_FUNCTION_NAME_CHECKED(UBlueprintAsyncActionBase, Activate);
}

FName UK2Node_ReactionalAsyncNode::GetCornerIcon() const
{
	//return TEXT("Graph.Latent.LatentIcon");
	//return TEXT("Graph.Message.MessageIcon");
	/*
	if (const UFunction* Function = GetTargetFunction())
	{
		if (Function->HasAllFunctionFlags(FUNC_BlueprintAuthorityOnly))
		{
			return TEXT("Graph.Replication.AuthorityOnly");
		}
		else if (Function->HasAllFunctionFlags(FUNC_BlueprintCosmetic))
		{
			return TEXT("Graph.Replication.ClientEvent");
		}
		else if (Function->HasMetaData(FBlueprintMetadata::MD_Latent))
		{
			return TEXT("Graph.Latent.LatentIcon");
		}
	}
	*/
	/*
	if (UFunction* Function = EventReference.ResolveMember<UFunction>(GetBlueprintClassFromNode()))
	{
		if (bOverrideFunction || (CustomFunctionName == NAME_None))
		{
			//@TODO: KISMETREPLICATION: Should do this for events with a custom function name, if it's a newly introduced replicating thingy
			if (Function->HasAllFunctionFlags(FUNC_BlueprintCosmetic) || IsCosmeticTickEvent())
			{
				return TEXT("Graph.Replication.ClientEvent");
			}
			else if (Function->HasAllFunctionFlags(FUNC_BlueprintAuthorityOnly))
			{
				return TEXT("Graph.Replication.AuthorityOnly");
			}
		}
	}

	if (IsUsedByAuthorityOnlyDelegate())
	{
		return TEXT("Graph.Replication.AuthorityOnly");
	}

	if (EventReference.GetMemberParentClass(GetBlueprintClassFromNode()) != nullptr && EventReference.GetMemberParentClass(GetBlueprintClassFromNode())->IsChildOf(UInterface::StaticClass()))
	{
		return TEXT("Graph.Event.InterfaceEventIcon");
	}
	*/
	/*
	if (FProperty const* VariableProperty = VariableReference.ResolveMember<FProperty>(GetBlueprintClassFromNode()))
	{
		if (VariableProperty->HasAllPropertyFlags(CPF_Net | CPF_EditorOnly))
		{
			IconTag = LOCTEXT("ReplicatedEditorOnlyVar", "Editor-Only | Replicated");
		}
		else if (VariableProperty->HasAnyPropertyFlags(CPF_Net))
		{
			IconTag = LOCTEXT("ReplicatedVar", "Replicated");
		}
		else if (VariableProperty->HasAnyPropertyFlags(CPF_EditorOnly))
		{
			IconTag = LOCTEXT("EditorOnlyVar", "Editor-Only");
		}
	}
	*/
	/*
	FSlateIcon UK2Node_GetArrayItem::GetIconAndTint(FLinearColor & OutColor) const
	{
		// emulate the icon/color that we used when this was a UK2Node_CallArrayFunction node
		if (UFunction* WrappedFunction = FindUField<UFunction>(UKismetArrayLibrary::StaticClass(), GET_FUNCTION_NAME_CHECKED(UKismetArrayLibrary, Array_Get)))
		{
			return UK2Node_CallFunction::GetPaletteIconForFunction(WrappedFunction, OutColor);
		}
		return Super::GetIconAndTint(OutColor);
	}
	*/

	if (ProxyFactoryClass != nullptr && ProxyFactoryClass->HasMetaData(FName(TEXT("ReactionalAsyncExecNode"))))
	{
		return TEXT("Graph.Latent.LatentIcon");
	}
	else
	{
		return FName();
	}
}

FSlateIcon UK2Node_ReactionalAsyncNode::GetIconAndTint(FLinearColor& OutColor) const
{
	if (ProxyFactoryClass != nullptr && ProxyFactoryClass->HasMetaData(FName(TEXT("ReactionalAsyncExecNode"))))
	{
		return Super::GetIconAndTint(OutColor);
	}
	else
	{
		OutColor = GetDefault<UGraphEditorSettings>()->FunctionCallNodeTitleColor;

		static FSlateIcon Icon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
		return Icon;
	}
	/*
	if (ProxyClass != nullptr)
	{

	}
	*/
}

void UK2Node_ReactionalAsyncNode::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	struct GetMenuActions_Utils
	{
		static void SetNodeFunc(UEdGraphNode* NewNode, bool /*bIsTemplateNode*/, TWeakObjectPtr<UFunction> FunctionPtr)
		{
			UK2Node_ReactionalAsyncNode* AsyncTaskNode = CastChecked<UK2Node_ReactionalAsyncNode>(NewNode);
			if (FunctionPtr.IsValid())
			{
				UFunction* Func = FunctionPtr.Get();
				FObjectProperty* ReturnProp = CastFieldChecked<FObjectProperty>(Func->GetReturnProperty());
						
				AsyncTaskNode->ProxyFactoryFunctionName = Func->GetFName();
				AsyncTaskNode->ProxyFactoryClass        = Func->GetOuterUClass();
				AsyncTaskNode->ProxyClass               = ReturnProp->PropertyClass;
			}
		}
	};

	UClass* NodeClass = GetClass();
	ActionRegistrar.RegisterClassFactoryActions<UReactionalAsyncTaskBPProxy>(FBlueprintActionDatabaseRegistrar::FMakeFuncSpawnerDelegate::CreateLambda([NodeClass](const UFunction* FactoryFunc)->UBlueprintNodeSpawner*
	{
		UClass* FactoryClass = FactoryFunc ? FactoryFunc->GetOwnerClass() : nullptr;
		
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintFunctionNodeSpawner::Create(FactoryFunc);
		check(NodeSpawner != nullptr);
		NodeSpawner->NodeClass = NodeClass;

		TWeakObjectPtr<UFunction> FunctionPtr = MakeWeakObjectPtr(const_cast<UFunction*>(FactoryFunc));
		NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(GetMenuActions_Utils::SetNodeFunc, FunctionPtr);

		return NodeSpawner;
	}) );
}

#undef LOCTEXT_NAMESPACE
