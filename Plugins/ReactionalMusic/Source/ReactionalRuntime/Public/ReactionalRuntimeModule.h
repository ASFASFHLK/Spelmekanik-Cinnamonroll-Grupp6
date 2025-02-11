/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FReactionalRuntimeModule : public IModuleInterface
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	static void* GetGETimelinePluginHandle();

	//TWeakPtr<struct FReactionalEngine> ReactionalEngineWeakPtr;

private:
	void* GETIMELINEHandle = nullptr;
};
