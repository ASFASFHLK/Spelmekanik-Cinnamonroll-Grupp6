/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "K2Node_AsyncAction.h"
#include "K2Node_ReactionalAsyncNode.generated.h"

class FBlueprintActionDatabaseRegistrar;

UCLASS()
class REACTIONALEDITOR_API UK2Node_ReactionalAsyncNode : public UK2Node_AsyncAction
{
	GENERATED_UCLASS_BODY()
	
	// UK2Node interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FName GetCornerIcon() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	// End of UK2Node interface
};
