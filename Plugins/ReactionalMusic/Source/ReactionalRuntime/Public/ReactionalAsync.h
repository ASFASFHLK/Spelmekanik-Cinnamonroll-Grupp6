/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Stats/Stats.h"
#include "Logging//LogMacros.h"
#include "HAL/CriticalSection.h"
#include "Tickable.h"
#include "ASync/ASync.h"
#include "Engine/DataAsset.h"
#include "ReactionalEngine.h"

#include "ReactionalAsync.generated.h"

// markus:
//There are lots and lots of different Async construct/modes/entities/solutions in UE.
//One good article that describes some of the base is https://forums.unrealengine.com/t/new-core-feature-async-framework-master-branch-and-4-8/18855
//For our heavy stuff (load theme/load track etc) the best is to use the IO thread pool. This execution thread pool is not supported directly by the Async and AsyncTask functions.
//"AsyncTask" always runs on the task graph (you can specify type of task graph thread). While with "Async" you can in addition also set execution to a new spawned thread and a thread pool. 
//"AsyncPool" let you specify thread pool which is what we want.
//The reason we would want IO ThreadPool is because the work is quite heavy but also high priority. In addition other audio load/encode/decode functions also use IO thread pool.
//TAsyncQueuedWork is used to wrap a callable/promise to a thread pool.
//In addition to this we also have FAsyncReactionalTask that derives from IQueuedWork.

//TODO FReactionalAsyncExecutionPolicy

enum class EReactionalAsyncBPThreadingMode : uint8;
class FReactionalLoadBundleTask;
class FReactionalLoadBundleDataAssetTask;
class FReactionalLoadFromJSONTask;
class UReactionalBundleDataAsset;

namespace Reactional
{
	enum class EReactionalAsyncBPTaskType : uint8
	{
		InitEngineInstance,
		FreeEngineInstance,
		LoadBundleDataAsset,
		LoadSection,
		LoadPlayList,
		LoadTrack,
		LoadTheme
	};

	enum class EReactionalAsyncExec : uint8
	{
		RunOnGameThread,
		RunOnGameThreadNextTick,
		RunOnTaskGraphHiPri,
		RunOnThreadPool,
		RunOnIOThreadPool,
		RunInThreadImmediately
	};

	class FReactionalAsyncExecutionPolicy
	{
	public:
		FReactionalAsyncExecutionPolicy(EReactionalAsyncExec InExecutionPolicy)
			: ExecutionPolicy(InExecutionPolicy) {}

		static FReactionalAsyncExecutionPolicy RunOnGameThread()		 { return FReactionalAsyncExecutionPolicy(EReactionalAsyncExec::RunOnGameThread); }
		static FReactionalAsyncExecutionPolicy RunOnGameThreadNextTick() { return FReactionalAsyncExecutionPolicy(EReactionalAsyncExec::RunOnGameThreadNextTick); }
		static FReactionalAsyncExecutionPolicy RunOnTaskGraphHiPri()	 { return FReactionalAsyncExecutionPolicy(EReactionalAsyncExec::RunOnTaskGraphHiPri); }
		static FReactionalAsyncExecutionPolicy RunOnThreadPool()		 { return FReactionalAsyncExecutionPolicy(EReactionalAsyncExec::RunOnThreadPool); }
		static FReactionalAsyncExecutionPolicy RunOnIOThreadPool()		 { return FReactionalAsyncExecutionPolicy(EReactionalAsyncExec::RunOnIOThreadPool); }
		static FReactionalAsyncExecutionPolicy RunInThreadImmediately()  { return FReactionalAsyncExecutionPolicy(EReactionalAsyncExec::RunInThreadImmediately); }

		const EReactionalAsyncExec& GetExecutionPolicy() const { return ExecutionPolicy; }

	private:
		EReactionalAsyncExec ExecutionPolicy;
	};

	bool LoadDataAssetPackageObj_Impl(
		TSoftObjectPtr<UReactionalBundleDataAsset> BundleDataAssetPtr,
		EReactionalAsyncBPThreadingMode ThreadingModeForwardFromBPTask,
		UReactionalBundleDataAsset*& OutBundleDataAssetObject
	);
	
	bool ParseJSONManifest_Impl(
		const FString& ManifestFilePath,
		TArray<FReactionalParsedJsonDataElement>& OutJsonData,
		TArray<FReactionalParsedJsonSectionsElement>& OutJsonSections
	);
	
	bool AddPlaylistAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& PlaylistName,
		const TArray<FReactionalParsedJsonDataElement>& JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	);
	
	bool AddSectionAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& SectionName,
		const TArray<FReactionalParsedJsonDataElement>& JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalThemeInfo>& OutThemesTrackInfo,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	);
	
	bool AddBundleAssetsData_Impl(
		const FString& ManifestFilePath,
		const TArray<FReactionalParsedJsonDataElement>& JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalThemeInfo>& OutThemesTrackInfo,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	);
	
	bool AddTrackAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& TrackName,
		const TArray<FReactionalParsedJsonDataElement>& JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	);
	
	bool AddThemeAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& ThemeName,
		const TArray<FReactionalParsedJsonDataElement>& JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalThemeInfo>& OutThemesTrackInfo
	);
	
	bool TrackInfoSetAssetData(
		const TArray<FString>& StringHashValues,
		TArray<FReactionalTrackInfo>& ResTrackInfos,
		const FString& BundleDirectoryPath,
		const FString& RequestedName = ""
	);
	
	bool ThemeInfoSetAssetData(
		const TArray<FString>& StringHashValues,
		TArray<FReactionalThemeInfo>& ResTrackInfos,
		const FString& BundleDirectoryPath,
		const FString& RequestedName = ""
	);

	bool LoadBundle(FString BundleName);
	bool LoadSection(const FString& BundleName, const FString& SectionName);
	bool LoadPlaylist(const FString& BundleName, const FString& PlaylistName);
	bool LoadTheme(const FString& BundleName, const FString& SectionName, const FString& ThemeName);
	bool LoadTrack(const FString& BundleName, const FString& TrackName);

	void FadeIn(float fadein);
	void FadeOut(float fadeout);

	template <typename CallableType>
	void ReactionalAsyncExecute(FReactionalAsyncExecutionPolicy ExecutionPolicy, CallableType&& Callable);

	//void ReactionalAsyncBPTaskDispatchRun(EReactionalAsyncBPTaskType AsyncBPTaskType, EReactionalAsyncBPThreadingMode ThreadingMode);

	FString ReactionalAsyncTaskToStr(EReactionalAsyncBPTaskType TaskType);

	//TODO: Check if should be auto delete task
	//Check how destructor is called and when (by debug breakpoint for example) 
	class FReactionalAsyncBPTask : public IQueuedWork
	{
	public:
		FReactionalAsyncBPTask() = delete;
		FReactionalAsyncBPTask(EReactionalAsyncBPTaskType InTaskType, EReactionalAsyncBPThreadingMode InThreadingMode)
			: TaskType(InTaskType)
			, ThreadingMode(InThreadingMode) {}

		virtual void DoThreadedWork() override { Run(); };

		virtual void Abandon() override { bHadError = true; bIsDone = true; };

		virtual void Run();
		
		/** @return whether the task succeeded or not */
		bool HadError() const { return bHadError; };
		
		/** @return information about the error if there was one */
		/** @return whether the task has completed or not */
		bool IsDone() const { return bIsDone; };

		int32 ReturnValueInt = -1;
		int32 ReturnValueErrorCodeInt = 0;

		FString ReturnErrorString = FString(TEXT(""));

		EReactionalAsyncBPTaskType TaskType;
		EReactionalAsyncBPThreadingMode ThreadingMode;

		//Since we share one proxy and one task object for all the latent/async BP nodes...
		//not all the stored input parameters will be used in a given node, hence the TOptional
		TOptional<FString> FilePath;
		TOptional<TSoftObjectPtr<UReactionalBundleDataAsset>> BundleSoftObjectPtr;
		
		TOptional<FString> BundleName;
		TOptional<FString> SectionName;
		TOptional<FString> PlaylistName;
		TOptional<FString> ThemeName;
		TOptional<FString> TrackName;

		TWeakObjectPtr<UReactionalSubsystem> Subsystem;

	protected:
		FThreadSafeBool bIsDone;
		FThreadSafeBool bHadError;
	};
}

using EReactionalAsyncBPTaskType = Reactional::EReactionalAsyncBPTaskType;
using EReactionalAsyncExec = Reactional::EReactionalAsyncExec;
using FReactionalAsyncExecutionPolicy = Reactional::FReactionalAsyncExecutionPolicy;
using FReactionalAsyncBPTask = Reactional::FReactionalAsyncBPTask;

//Unreal reflection types (UENUM, UFUNCTION, USTRUCT, UCLASS) does not like namespaces, so these are not in Reactional::
UENUM(BlueprintType)
enum class EReactionalAsyncBPThreadingMode : uint8
{
	/** Immediate synchronous blocking call on main Game Thread. Recommend for calls happening before or after gameplay. (IE Pre or Begin gameplay. */
	GameThread_Synchronous,
	/** Aynchronous non-blocking call executed on shared UE Thread Pool. Recommend for setup and load during gameplay. */
	PooledThread_Async
};


