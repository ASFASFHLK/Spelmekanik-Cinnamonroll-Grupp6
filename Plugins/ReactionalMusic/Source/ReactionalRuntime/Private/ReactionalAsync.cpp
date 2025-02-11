/**
* @copyright Copyright © 2024 Reactional Music Group AB. All rights reserved.
*/

#include "ReactionalAsync.h"
#include "ReactionalSubsystem.h"
#include "Json.h"

#define LOCTEXT_NAMESPACE "ReactionalMusic"
#pragma optimize("", off)
namespace Reactional
{
	enum EReactionalResult : uint8 {
		Success = 0,
		Error	= 1,
	};
	
	FString ReactionalAsyncTaskToStr(EReactionalAsyncBPTaskType TaskType)
	{
		switch (TaskType) {
		case EReactionalAsyncBPTaskType::LoadBundleDataAsset:
			return FString(TEXT("LoadBundleDataAsset"));
			
		case EReactionalAsyncBPTaskType::LoadSection:
			return FString(TEXT("LoadSection"));
			
		case EReactionalAsyncBPTaskType::LoadPlayList:
			return FString(TEXT("LoadPlaylist"));
			
		case EReactionalAsyncBPTaskType::LoadTheme:
			return FString(TEXT("LoadTheme"));
			
		default:
			return FString(TEXT("ReactionalAsyncTaskToStr Unknown"));
		}
	}

	template <typename CallableType>
	void ReactionalAsyncExecute(FReactionalAsyncExecutionPolicy ExecutionPolicy, CallableType&& Callable)
	{
		switch (ExecutionPolicy.GetExecutionPolicy())
		{
		case EReactionalAsyncExec::RunOnGameThread:
			if (IsInGameThread())
			{
				Callable();
			}
			else
			{
				Async(EAsyncExecution::TaskGraphMainThread, MoveTemp(Callable));
			}
			break;

		case EReactionalAsyncExec::RunOnGameThreadNextTick:
			Async(EAsyncExecution::TaskGraphMainThread, MoveTemp(Callable));
			break;

		case EReactionalAsyncExec::RunOnThreadPool:
			Async(EAsyncExecution::ThreadPool, MoveTemp(Callable));
			break;

		case EReactionalAsyncExec::RunOnIOThreadPool:
			AsyncPool(*GIOThreadPool, MoveTemp(Callable));
			break;

		case EReactionalAsyncExec::RunInThreadImmediately:
			Callable();
			break;
		case EReactionalAsyncExec::RunOnTaskGraphHiPri:
			// TODO ? or remove?
			// unimplemented case
			break;
		}
	}

	void FReactionalAsyncBPTask::Run()
	{
		if (!BundleSoftObjectPtr.IsSet())
		{
			bIsDone   = true;
			bHadError = true;
			return;
		}

		//This is needed to prevent engine (and by consequence reactional engine lib calls) deallocation while we are running the async task
		TSharedRef<FReactionalEngine> SharedEngineRef = FReactionalEngine::MakeSharedInstance().ToSharedRef();

		UReactionalBundleDataAsset* DataAssetObjectPtr = nullptr;
		if(!LoadDataAssetPackageObj_Impl(*BundleSoftObjectPtr, ThreadingMode, DataAssetObjectPtr))
		{
			REACTIONAL_LOG_ERROR("Failed loading data asset.")
			bIsDone = true;
			bHadError = true;
			return;
		}

		TArray<FReactionalParsedJsonDataElement> JsonData;
		TArray<FReactionalParsedJsonSectionsElement> JsonSections;

		if(!ParseJSONManifest_Impl(
			FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
			JsonData,
			JsonSections
		)) {
			REACTIONAL_LOG_ERROR("Failed parsing JSON manifest.")
			bIsDone = true;
			bHadError = true;
			return;
		}
		
		switch (TaskType) {
			case EReactionalAsyncBPTaskType::LoadBundleDataAsset:
			{
				TArray<FReactionalThemeInfo> ThemesTrackInfo;
				TArray<FReactionalTrackInfo> PlayListTrackInfo;
				AddBundleAssetsData_Impl(
					FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
					JsonData,
					JsonSections,
					ThemesTrackInfo,
					PlayListTrackInfo
				);
				for (const auto& Data : ThemesTrackInfo)
				{
					Subsystem->LoadedThemes.AddUnique(Data);
				}
				for (const auto& Data : PlayListTrackInfo)
				{
					Subsystem->LoadedTracks.AddUnique(Data);
				}
				Subsystem->LoadedBundles.AddUnique(DataAssetObjectPtr);

				bIsDone = true;
				bHadError = false;

				return;
			}
			case EReactionalAsyncBPTaskType::LoadSection:
			{
				TArray<FReactionalThemeInfo> ThemesTrackInfo;
				TArray<FReactionalTrackInfo> PlayListTrackInfo;
				AddSectionAssetsData_Impl(
					FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
					SectionName.GetValue(),
					JsonData,
					JsonSections,
					ThemesTrackInfo,
					PlayListTrackInfo
				);
				for (const auto& Data : ThemesTrackInfo)
				{
					Subsystem->LoadedThemes.AddUnique(Data);
				}
				for (const auto& Data : PlayListTrackInfo)
				{
					Subsystem->LoadedTracks.AddUnique(Data);
				}
				Subsystem->LoadedBundles.AddUnique(DataAssetObjectPtr);

				bIsDone = true;
				bHadError = false;

				return;
			}
			case EReactionalAsyncBPTaskType::LoadPlayList:
			{
				TArray<FReactionalTrackInfo> PlayListTrackInfo;
				AddPlaylistAssetsData_Impl(
					FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
					PlaylistName.GetValue(),
					JsonData,
					JsonSections,
					PlayListTrackInfo
				);
				for (const auto& Data : PlayListTrackInfo)
				{
					Subsystem->LoadedTracks.AddUnique(Data);
				}
				Subsystem->LoadedBundles.AddUnique(DataAssetObjectPtr);

				bIsDone = true;
				bHadError = false;

				return;
			}
			case EReactionalAsyncBPTaskType::LoadTrack:
			{
				TArray<FReactionalTrackInfo> PlayListTrackInfo;
				AddTrackAssetsData_Impl(
					FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
					TrackName.GetValue(),
					JsonData,
					JsonSections,
					PlayListTrackInfo
				);
				for (const auto& Data : PlayListTrackInfo)
				{
					Subsystem->LoadedTracks.AddUnique(Data);
				}
				Subsystem->LoadedBundles.AddUnique(DataAssetObjectPtr);

				bIsDone = true;
				bHadError = false;
				return;
			}
			case EReactionalAsyncBPTaskType::LoadTheme:
			{
				TArray<FReactionalThemeInfo> ThemesTrackInfo;
				AddThemeAssetsData_Impl(
					FPaths::Combine(*FPaths::ProjectContentDir(), *DataAssetObjectPtr->Bundle.BundlePath),
					ThemeName.GetValue(),
					JsonData,
					JsonSections,
					ThemesTrackInfo
				);
				for (const auto& Data : ThemesTrackInfo)
				{
					Subsystem->LoadedThemes.AddUnique(Data);
				}
				Subsystem->LoadedBundles.AddUnique(DataAssetObjectPtr);

				bIsDone = true;
				bHadError = false;
				return;
			}
			default: FString(TEXT("FReactionalAsyncBPTask Run Unknown")); break;
		}
	}
	
	TPair<FString, EReactionalResult> QueryBundlePath(
		const FString& ManifestFilePath,
		const TArray<FReactionalParsedJsonDataElement>&	JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections
	) {
		if (!FPaths::FileExists(ManifestFilePath))
		{
			REACTIONAL_LOG_ERROR("Missing manifest file: %s", *ManifestFilePath)
			return TPairInitializer("", Error);
		}

		const FString BundleDirectoryPath = FPaths::GetPath(ManifestFilePath);
		if (!FPaths::IsUnderDirectory(BundleDirectoryPath, FPaths::ProjectContentDir())
			&& !FPaths::IsUnderDirectory(BundleDirectoryPath, FPaths::EnginePluginsDir())
			&& !FPaths::IsUnderDirectory(BundleDirectoryPath, FPaths::ProjectPluginsDir())
		) {
			REACTIONAL_LOG_ERROR("Bundle %s, not under project or plugin content folder", *BundleDirectoryPath)
			return TPairInitializer(BundleDirectoryPath, Error);
		}

		if (JsonData.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("Parsed Data.Num() == 0")
			return TPairInitializer(BundleDirectoryPath, Error);
		}

		if (JsonSections.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("Parsed Sections.Num() == 0")
			return TPairInitializer(BundleDirectoryPath, Error);
		}
		return TPairInitializer(BundleDirectoryPath, Success);
	}

	bool LoadDataAssetPackageObj_Impl(
		TSoftObjectPtr<UReactionalBundleDataAsset> BundleDataAssetPtr,
		EReactionalAsyncBPThreadingMode ThreadingModeForwardFromBPTask,
		UReactionalBundleDataAsset*& OutBundleDataAssetObject
	) {
		const FSoftObjectPath SequenceObjectPath = BundleDataAssetPtr.ToSoftObjectPath();
		UReactionalBundleDataAsset* LoadedDataAssetObject = nullptr;
		OutBundleDataAssetObject = nullptr;

		if (BundleDataAssetPtr.IsValid())
		{
			LoadedDataAssetObject = BundleDataAssetPtr.Get();
			OutBundleDataAssetObject = LoadedDataAssetObject;
			return true;
		}

		if (BundleDataAssetPtr.IsNull())
		{
			REACTIONAL_LOG_ERROR("BundleDataAsset is null.")
			return false;
		}
		else
		{
			//Blueprint Async task GameThread_Synchronous
			if (ThreadingModeForwardFromBPTask == EReactionalAsyncBPThreadingMode::GameThread_Synchronous)
			{
				LoadedDataAssetObject = BundleDataAssetPtr.LoadSynchronous();
				if (!LoadedDataAssetObject)
				{
					REACTIONAL_LOG_WARNING("Data Asset failed to load.")
					return false;
				}

				OutBundleDataAssetObject = LoadedDataAssetObject;
				return true;
			}
			else
			{
				// markus:
				//	We use Async loading here but block wait. Reason is that it is a bit unclear if a LoadSynchronous call is allowed 
				//	in a IO pooled thread (which this code is executed in if EReactionalNodeThreadingMode::PooledThread_Async).
				//	Using Async loading is allowed. Note that we are already in async parallell mode here (in IO pooled thread) so a block wait
				//	here has no impact on GameThread stall or anything like that.

				FThreadSafeBool bLoadingAsyncDone = false;
				FThreadSafeBool bLoadingAsyncError = true;

				auto LoadAndRegister = [&BundleDataAssetPtr, &bLoadingAsyncDone, &bLoadingAsyncError, &LoadedDataAssetObject] (
					const FName& PackageName,
					const UPackage* LoadedPackage,
					EAsyncLoadingResult::Type Result
				) {
					if (Result != EAsyncLoadingResult::Succeeded)
					{
						REACTIONAL_LOG_ERROR("Async Loading failed.")
						bLoadingAsyncDone = true;
					}

					UReactionalBundleDataAsset* LoadedBundleDataAsset = BundleDataAssetPtr.Get();
					if (!LoadedBundleDataAsset)
					{
						bLoadingAsyncDone = true;
						REACTIONAL_LOG_ERROR("Loaded bundle data asset pointer was null.")
					}

					if (Result == EAsyncLoadingResult::Succeeded && LoadedBundleDataAsset)
					{
						TArray<UObject*> ObjsInPackage;
						GetObjectsWithPackage(LoadedPackage, ObjsInPackage, false);
						for (auto ObjIt = ObjsInPackage.CreateConstIterator(); ObjIt; ++ObjIt)
						{
							LoadedDataAssetObject = Cast<UReactionalBundleDataAsset>(*ObjIt);
							if (LoadedDataAssetObject)
							{
								break;
							}
						}

						if (LoadedDataAssetObject)
						{
							bLoadingAsyncError = false;
							bLoadingAsyncDone = true;

							REACTIONAL_LOG("Async Loading succeeded.")
						}
						else
						{
							bLoadingAsyncDone = true;
						}
					}
				};

				// gin:
				//	need to call this from the main thread to spin up worker thread with legacy loader (to be deprecated but who knows when)
				//	look for better solution for the future
				AsyncTask(ENamedThreads::GameThread, [&BundleDataAssetPtr, &LoadAndRegister] {
					LoadPackageAsync(BundleDataAssetPtr.GetLongPackageName(), FLoadPackageAsyncDelegate::CreateLambda(LoadAndRegister));
				});

				while (!bLoadingAsyncDone)
				{
					FPlatformProcess::Sleep(0.0f);
				}

				if (bLoadingAsyncError)
				{
					REACTIONAL_LOG_ERROR("Async Loading failed.")
					return false;
				}
			}
		}

		OutBundleDataAssetObject = LoadedDataAssetObject;
		return true;
	}

	bool ParseJSONManifest_Impl(
		const FString& ManifestFilePath,
		TArray<FReactionalParsedJsonDataElement>& OutJsonData,
		TArray<FReactionalParsedJsonSectionsElement>& OutJsonSections
	) {
		if (!FPaths::FileExists(ManifestFilePath))
		{
			REACTIONAL_LOG_ERROR("Missing manifest file: %s", *ManifestFilePath)
			return false;
		}

		const FString BundleDirectoryPath = FPaths::GetPath(ManifestFilePath);
		if (!FPaths::IsUnderDirectory(BundleDirectoryPath, FPaths::ProjectContentDir()) && !FPaths::IsUnderDirectory(BundleDirectoryPath, FPaths::EnginePluginsDir()) && !FPaths::IsUnderDirectory(BundleDirectoryPath, FPaths::ProjectPluginsDir()) )
		{
			REACTIONAL_LOG_ERROR("Bundle %s, not under project or plugin content folder", *BundleDirectoryPath)
			return false;
		}

		FString JsonContent;
		if (!FFileHelper::LoadFileToString(JsonContent, *ManifestFilePath))
		{
			REACTIONAL_LOG_ERROR("Failed loading manifest file: %s", *ManifestFilePath)
			return false;
		}
			
		TArray<FReactionalParsedJsonDataElement> parsedDataEntries;
		TArray<FReactionalParsedJsonSectionsElement> parsedSectionsEntries;

		OutJsonData.Empty();
		OutJsonSections.Empty();
	
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonContent);
		TSharedPtr<FJsonObject> RootJsonObject = MakeShareable(new FJsonObject());
		if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid())
		{	
			if (RootJsonObject->HasTypedField<EJson::Object>(TEXT("data")))
			{
				const TSharedPtr<FJsonObject>& DataField = RootJsonObject->GetObjectField(TEXT("data"));
				if (DataField.IsValid())
				{
					FReactionalParsedJsonDataElement dataEntryElement;	
					for (const auto& ValuePair : DataField->Values)
					{
						dataEntryElement.stringHashKey = FString();
						dataEntryElement.stringHashValues.Empty();
	
						dataEntryElement.stringHashKey = ValuePair.Key;
	
						const TSharedPtr<FJsonValue>& JsonValue = ValuePair.Value;
						const TArray<TSharedPtr<FJsonValue>>& arrayObject = JsonValue->AsArray();
						for (const auto& hashValue : arrayObject)
						{
							if (hashValue.IsValid() && hashValue->Type == EJson::String)
							{
								dataEntryElement.stringHashValues.Add(hashValue->AsString());
							}
							else
							{
								REACTIONAL_LOG_ERROR("Invalid JSON, deserialize failed %s", *ManifestFilePath)
								return false;
							}
						}
						parsedDataEntries.Add(dataEntryElement);
					}
				}
			}
	
			if (RootJsonObject->HasTypedField<EJson::Object>(TEXT("sections")))
			{
				const TSharedPtr<FJsonObject>& SectionsField = RootJsonObject->GetObjectField(TEXT("sections"));
				if (SectionsField.IsValid())
				{	
					FReactionalParsedJsonSectionsElement sectionsEntryElement;
					for (const auto& ValuePair : SectionsField->Values)
					{
						sectionsEntryElement.parsedSectionName = FString();
						sectionsEntryElement.parsedJsonThemes.Empty();
						sectionsEntryElement.parsedJsonPlaylists.Empty();
	
						const FString& JsonKey = ValuePair.Key;
						sectionsEntryElement.parsedSectionName = JsonKey;

						const TSharedPtr<FJsonValue>& JsonValue = ValuePair.Value;
						const TSharedPtr<FJsonObject>& valueObject = JsonValue->AsObject();
	
						for (const auto& sectionsValuePair : valueObject->Values)
						{
							const FString& sectionsJsonKey = sectionsValuePair.Key;
							const TSharedPtr<FJsonValue>& sectionsJsonValue = sectionsValuePair.Value;
	
							if (sectionsJsonKey.Equals(TEXT("themes")))
							{
								FReactionalParsedJsonThemesElement themesEntry;
	
								const TArray< TSharedPtr<FJsonValue> > arrayObject = sectionsJsonValue->AsArray();
								for ( const auto& hashValue : arrayObject )
								{
									if (hashValue->Type == EJson::String)
									{
										themesEntry.stringHashValues.Add(hashValue->AsString());
									}
									else
									{
										REACTIONAL_LOG_ERROR("Invalid JSON, deserialize failed %s", *ManifestFilePath)
										return false;
									}
								}
								sectionsEntryElement.parsedJsonThemes.Add(themesEntry);
							}
							else if (sectionsJsonKey.Equals(TEXT("playlists")))
							{
								TSharedPtr<FJsonValue> playlistsJsonObject = valueObject->GetField<EJson::Array>(TEXT("playlists"));
								if (playlistsJsonObject.IsValid())
								{
									FReactionalParsedJsonPlaylistsElement playlistsEntry;
	
									const TArray< TSharedPtr<FJsonValue> > playlistsArray = playlistsJsonObject->AsArray();
									for ( const auto& playlist : playlistsArray )
									{
										if (playlist->Type == EJson::Object)
										{
											const TSharedPtr<FJsonObject> playlistObject = playlist->AsObject();
											for (const auto& trackValuePair : playlistObject->Values)
											{
												const FString& trackJsonKey = trackValuePair.Key;
												const TSharedPtr<FJsonValue>& trackJsonValue = trackValuePair.Value;
	
												if (trackJsonKey.Equals(TEXT("name")))
												{
													playlistsEntry.parsedPlaylistName = trackJsonValue->AsString();
												}
												else if (trackJsonKey.Equals(TEXT("tracks")))
												{
													const TArray< TSharedPtr<FJsonValue> > trackArray = trackJsonValue->AsArray();
													for (const auto& track : trackArray)
													{
														if (track->Type == EJson::String)
														{
															playlistsEntry.stringHashValues.Add(track->AsString());
														}
														else
														{
															REACTIONAL_LOG_ERROR("Invalid JSON, deserialize failed %s", *ManifestFilePath)
															return false;
														}
													}
												}
											}
										}
									}
									sectionsEntryElement.parsedJsonPlaylists.Add(playlistsEntry);
								}
							}
						}
						parsedSectionsEntries.Add(sectionsEntryElement);
					}
				}
			}
		}
		else //FAILED FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid()
		{
			REACTIONAL_LOG_ERROR("Invalid JSON, deserialize failed %s", *ManifestFilePath)
			return false;
		}

		OutJsonData = MoveTemp(parsedDataEntries);
		OutJsonSections = MoveTemp(parsedSectionsEntries);

		return true;
	}

	bool AddBundleAssetsData_Impl(
		const FString& ManifestFilePath,
		const TArray<FReactionalParsedJsonDataElement>&	JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalThemeInfo>& OutThemesTrackInfo,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	) {
		auto [BundleDirectoryPath, Result] = QueryBundlePath(ManifestFilePath, JsonData, JsonSections);
		if (Result != Success) { return false; }
		
		TArray<FReactionalThemeInfo> themesJSONTracks;
		TArray<FReactionalTrackInfo> playlistJSONTracks;
		for (const auto& sectionElement : JsonSections)
		{
			for (const auto& themesElement : sectionElement.parsedJsonThemes)
			{
				if (!ThemeInfoSetAssetData(themesElement.stringHashValues, themesJSONTracks, BundleDirectoryPath))
				{
					//return false;
				}
			}
				
			for (const auto& playlistElement : sectionElement.parsedJsonPlaylists)
			{
				if (!TrackInfoSetAssetData(playlistElement.stringHashValues, playlistJSONTracks, BundleDirectoryPath))
				{
					//return false;
				}
			}
		}

		if (themesJSONTracks.Num() == 0 && playlistJSONTracks.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("No valid bundle data")
			return false;
		}
		OutThemesTrackInfo   = MoveTemp(themesJSONTracks);
		OutPlayListTrackInfo = MoveTemp(playlistJSONTracks);

		return true;
	}
	
	bool AddSectionAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& SectionName,
		const TArray<FReactionalParsedJsonDataElement>&	JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalThemeInfo>& OutThemesTrackInfo,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	) {
		auto [BundleDirectoryPath, Result] = QueryBundlePath(ManifestFilePath, JsonData, JsonSections);
		if (Result != Success) { return false; }

		const FReactionalParsedJsonSectionsElement* SectionElement;
		if(SectionName.IsEmpty())
		{
			SectionElement = &JsonSections[0];
		}
		else
		{
			SectionElement = JsonSections
				.FindByPredicate([SectionName](const auto& X) {
					return X.parsedSectionName == SectionName;
				});
		}
		if (SectionElement == nullptr) { return false; }
		
		TArray<FReactionalThemeInfo> themesJSONTracks;
		TArray<FReactionalTrackInfo> playlistJSONTracks;
		for (const auto& themesElement : SectionElement->parsedJsonThemes)
		{
			if (!ThemeInfoSetAssetData(themesElement.stringHashValues, themesJSONTracks, BundleDirectoryPath) )
			{ /*return false;*/ }
		}
		for (const auto& playlistElement : SectionElement->parsedJsonPlaylists)
		{
			if (!TrackInfoSetAssetData(playlistElement.stringHashValues, playlistJSONTracks, BundleDirectoryPath))
			{ /*return false;*/ }
		}
		
		if (themesJSONTracks.Num() == 0 && playlistJSONTracks.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("No valid section data")
			return false;
		}
		OutThemesTrackInfo = MoveTemp(themesJSONTracks);
		OutPlayListTrackInfo = MoveTemp(playlistJSONTracks);

		return true;
	}
	
	bool AddPlaylistAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& PlaylistName,
		const TArray<FReactionalParsedJsonDataElement>&	JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	) {
		auto [BundleDirectoryPath, Result] = QueryBundlePath(ManifestFilePath, JsonData, JsonSections);
		if (Result != Success) { return false; }

		TArray<FReactionalTrackInfo> themesJSONTracks;
		TArray<FReactionalTrackInfo> playlistJSONTracks;
		for (const auto& sectionElement : JsonSections)
		{
			if(sectionElement.parsedJsonPlaylists.Num() == 0)
			{
				break;
			}
			
			const FReactionalParsedJsonPlaylistsElement* PlaylistElement;
			if(PlaylistName.IsEmpty())
			{
				PlaylistElement = &sectionElement.parsedJsonPlaylists[0];
			}
			else
			{
				PlaylistElement = sectionElement.parsedJsonPlaylists
					.FindByPredicate([PlaylistName](const auto& X) {
						return X.parsedPlaylistName == PlaylistName;
					});
			}
			if (PlaylistElement == nullptr) { return false; }
			
			if (!TrackInfoSetAssetData(PlaylistElement->stringHashValues, playlistJSONTracks, BundleDirectoryPath))
			{ return false; }
		}
		
		if (playlistJSONTracks.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("No valid playlist data")
			return false;
		}
		OutPlayListTrackInfo = MoveTemp(playlistJSONTracks);

		return true;
	}

	bool AddTrackAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& TrackName,
		const TArray<FReactionalParsedJsonDataElement>&	JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalTrackInfo>& OutPlayListTrackInfo
	) {
		auto [BundleDirectoryPath, Result] = QueryBundlePath(ManifestFilePath, JsonData, JsonSections);
		if (Result != Success) { return false; }
		
		TArray<FReactionalTrackInfo> playlistJSONTracks;
		if(TrackName.IsEmpty())
		{
			if(auto track = &JsonSections[0].parsedJsonPlaylists[0])
			{
				if (!TrackInfoSetAssetData(track->stringHashValues, playlistJSONTracks, BundleDirectoryPath))
				{ return false; }
			}
		}
		else
		{
			for (const auto& sectionElement : JsonSections)
				for (const auto& playlistElement : sectionElement.parsedJsonPlaylists)
			{
				if (!TrackInfoSetAssetData(playlistElement.stringHashValues, playlistJSONTracks, BundleDirectoryPath, TrackName))
				{ return false; }
			}
		}
		
		if (playlistJSONTracks.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("No valid section track data.")
			return false;
		}
		OutPlayListTrackInfo = MoveTemp(playlistJSONTracks);
		
		return true;
	}
	
	bool AddThemeAssetsData_Impl(
		const FString& ManifestFilePath,
		const FString& ThemeName,
		const TArray<FReactionalParsedJsonDataElement>&	JsonData,
		const TArray<FReactionalParsedJsonSectionsElement>& JsonSections,
		TArray<FReactionalThemeInfo>& OutThemesTrackInfo
	) {
		auto [BundleDirectoryPath, Result] = QueryBundlePath(ManifestFilePath, JsonData, JsonSections);
		if (Result != Success) { return false; }

		TArray<FReactionalThemeInfo> themesJSONTracks;
		if(ThemeName.IsEmpty())
		{
			if(auto theme = &JsonSections[0].parsedJsonThemes[0])
			{
				if (!ThemeInfoSetAssetData(theme->stringHashValues, themesJSONTracks, BundleDirectoryPath))
				{ return false; }
			}
		}
		else
		{
			for (const auto& sectionElement : JsonSections)
				for (const auto& themesElement : sectionElement.parsedJsonThemes)
			{
				if (!ThemeInfoSetAssetData(themesElement.stringHashValues, themesJSONTracks, BundleDirectoryPath, ThemeName))
				{ return false; }
			}
		}
		if (themesJSONTracks.Num() == 0)
		{
			REACTIONAL_LOG_ERROR("No valid section theme data.")
			return false;
		}
		OutThemesTrackInfo = MoveTemp(themesJSONTracks);

		return true;
	}
	
	bool TrackInfoSetAssetData(
		const TArray<FString>& StringHashValues,
		TArray<FReactionalTrackInfo>& ResTrackInfos,
		const FString& BundleDirectoryPath,
		const FString& RequestedName
	) {
		REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
		
		for (const auto& hashValue : StringHashValues)
		{
			bool loaded = false;
			for(auto track : UReactionalSubsystem::GetSubsystem()->LoadedTracks)
			{
				if(track.trackHash == hashValue) { loaded = true; break; }
			}
			if(loaded) { continue; }
			
			FString assetHashPath = FString::Printf(TEXT("%s/%s"), *BundleDirectoryPath, *hashValue);

			TUniquePtr<FArchive> assetHashFileReader(IFileManager::Get().CreateFileReader(*assetHashPath));
			if(!assetHashFileReader.IsValid())
			{
				REACTIONAL_LOG_ERROR("Failed to create file reader.")
				return false;
			}
			int32 fileSize = static_cast<int32>(assetHashFileReader->TotalSize());

			int32 nkl_size = 256;
			int32 trackId = -1;
			{
				TArray<uint8> byteBufferStr;
				byteBufferStr.Empty(fileSize + 1);
				byteBufferStr.AddZeroed(fileSize + 1);

				TArray<uint8> nklBuffer;
				nklBuffer.Empty(nkl_size);
				nklBuffer.AddZeroed(nkl_size);

				assetHashFileReader->Seek(fileSize - nkl_size);
				assetHashFileReader->Serialize(nklBuffer.GetData(), nkl_size);

				assetHashFileReader->Seek(0);
				assetHashFileReader->Serialize(byteBufferStr.GetData(), fileSize);

				trackId = reactional_add_track_from_string(
					lib_ptr,
					reinterpret_cast<const char*>(byteBufferStr.GetData()),
					fileSize,
					nklBuffer.GetData(),
					nkl_size
				);
				if (trackId < 0)
				{
					const char* errorString = reactional_string_error(trackId);
					REACTIONAL_LOG_ERROR("Failed to parse track data. Reason: %hs.", errorString)
				}
			}

			if (trackId >= 0)
			{
				TArray<char> charBuf;
				charBuf.AddZeroed(100);
				charBuf[99] = '\0';

				FReactionalTrackInfo newTrackInfo;

				int namearamIdx = reactional_find_param(lib_ptr, trackId, TCHAR_TO_ANSI(TEXT("name")));
				int result = reactional_get_param_string(lib_ptr, trackId, namearamIdx, charBuf.GetData(), charBuf.Num() - 1);
				if (result > 0)
				{
					FString trackName = ANSI_TO_TCHAR(charBuf.GetData());
					newTrackInfo.trackName = trackName;
					if(RequestedName.Len() != 0 && !RequestedName.Equals(trackName)) { continue; }
				}

				int trackNbrAssets = reactional_get_num_assets(lib_ptr, trackId);
				for (int assetIdx = 0; assetIdx < trackNbrAssets; assetIdx++)
				{
					const char* assetID = reactional_get_asset_id(lib_ptr, trackId, assetIdx);
					const char* assetURI = reactional_get_asset_uri(lib_ptr, trackId, assetIdx);
					const char* assetType = reactional_get_asset_type(lib_ptr, trackId, assetIdx);

					FString assetFilePath = FString::Printf(TEXT("%s/%s"), *BundleDirectoryPath, ANSI_TO_TCHAR(assetURI));

					TUniquePtr<FArchive> assetFileReader(IFileManager::Get().CreateFileReader(*assetFilePath));
					int32 assetFileSize = static_cast<int32>(assetFileReader->TotalSize());

					TArray<uint8>assetFileByteBuffer;
					assetFileByteBuffer.Empty(assetFileSize - nkl_size);
					assetFileByteBuffer.AddZeroed(assetFileSize - nkl_size);

					assetFileReader->Serialize(assetFileByteBuffer.GetData(), assetFileSize - nkl_size);

					TArray<uint8> nkl_uri;
					nkl_uri.Empty(nkl_size);
					nkl_uri.AddZeroed(nkl_size);

					assetFileReader->Seek(assetFileSize - nkl_size);
					assetFileReader->Serialize(nkl_uri.GetData(), nkl_size);

					int errorID = reactional_set_asset_data(
						lib_ptr,
						trackId,
						assetID,
						assetType,
						assetFileByteBuffer.GetData(),
						assetFileByteBuffer.Num(),
						nkl_uri.GetData(),
						nkl_size
					);
					if (errorID != 0)
					{
						return false;
					}
				}
				newTrackInfo.trackHash = *hashValue;
				newTrackInfo.trackID = trackId;

				ResTrackInfos.Add(newTrackInfo);
			}
		}
		if (ResTrackInfos.IsEmpty()) { return false; }
		return true;
	}
	
	bool ThemeInfoSetAssetData(
		const TArray<FString>& StringHashValues,
		TArray<FReactionalThemeInfo>& ResTrackInfos,
		const FString& BundleDirectoryPath,
		const FString& RequestedName
	) {
		REACTIONAL_GET_LIB_PTR_OR_RETURN(false)
		
		for (const auto& hashValue : StringHashValues)
		{
			bool loaded = false;
			for(auto theme : UReactionalSubsystem::GetSubsystem()->LoadedThemes)
			{
				if(theme.themeHash == hashValue) { loaded = true; break; }
			}
			
			if(loaded) { continue; }
			FString assetHashPath = FString::Printf(TEXT("%s/%s"), *BundleDirectoryPath, *hashValue);

			TUniquePtr<FArchive> assetHashFileReader(IFileManager::Get().CreateFileReader(*assetHashPath));
			if(!assetHashFileReader.IsValid())
			{
				REACTIONAL_LOG_ERROR("Failed to create file reader.")
				return false;
			}
			int32 fileSize = static_cast<int32>(assetHashFileReader->TotalSize());

			int32 nkl_size = 256;
			int32 trackId = -1;
			{
				TArray<uint8> byteBufferStr;
				byteBufferStr.Empty(fileSize + 1);
				byteBufferStr.AddZeroed(fileSize + 1);

				TArray<uint8> nklBuffer;
				nklBuffer.Empty(nkl_size);
				nklBuffer.AddZeroed(nkl_size);

				assetHashFileReader->Seek(fileSize - nkl_size);
				assetHashFileReader->Serialize(nklBuffer.GetData(), nkl_size);

				assetHashFileReader->Seek(0);
				assetHashFileReader->Serialize(byteBufferStr.GetData(), fileSize);

				trackId = reactional_add_track_from_string(
					lib_ptr,
					reinterpret_cast<const char*>(byteBufferStr.GetData()),
					fileSize,
					nklBuffer.GetData(),
					nkl_size
				);
				if (trackId < 0)
				{
					const char* errorString = reactional_string_error(trackId);
					REACTIONAL_LOG_ERROR("Failed to parse track data. Reason: %hs.", errorString)
				}
			}

			if (trackId >= 0)
			{
				TArray<char> charBuf;
				charBuf.AddZeroed(100);
				charBuf[99] = '\0';

				FReactionalThemeInfo newTrackInfo;

				int namearamIdx = reactional_find_param(lib_ptr, trackId, TCHAR_TO_ANSI(TEXT("name")));
				int result = reactional_get_param_string(lib_ptr, trackId, namearamIdx, charBuf.GetData(), charBuf.Num() - 1);
				if (result > 0)
				{
					FString trackName = ANSI_TO_TCHAR(charBuf.GetData());
					newTrackInfo.themeName = trackName;
					if(RequestedName.Len() != 0 && !RequestedName.Equals(trackName)) { continue; }
				}

				int trackNbrAssets = reactional_get_num_assets(lib_ptr, trackId);
				for (int assetIdx = 0; assetIdx < trackNbrAssets; assetIdx++)
				{
					const char* assetID = reactional_get_asset_id(lib_ptr, trackId, assetIdx);
					const char* assetURI = reactional_get_asset_uri(lib_ptr, trackId, assetIdx);
					const char* assetType = reactional_get_asset_type(lib_ptr, trackId, assetIdx);

					FString assetFilePath = FString::Printf(TEXT("%s/%s"), *BundleDirectoryPath, ANSI_TO_TCHAR(assetURI));

					TUniquePtr<FArchive> assetFileReader(IFileManager::Get().CreateFileReader(*assetFilePath));
					int32 assetFileSize = static_cast<int32>(assetFileReader->TotalSize());

					TArray<uint8>assetFileByteBuffer;
					assetFileByteBuffer.Empty(assetFileSize - nkl_size);
					assetFileByteBuffer.AddZeroed(assetFileSize - nkl_size);

					assetFileReader->Serialize(assetFileByteBuffer.GetData(), assetFileSize - nkl_size);

					TArray<uint8> nkl_uri;
					nkl_uri.Empty(nkl_size);
					nkl_uri.AddZeroed(nkl_size);

					assetFileReader->Seek(assetFileSize - nkl_size);
					assetFileReader->Serialize(nkl_uri.GetData(), nkl_size);

					int errorID = reactional_set_asset_data(
						lib_ptr,
						trackId,
						assetID,
						assetType,
						assetFileByteBuffer.GetData(),
						assetFileByteBuffer.Num(),
						nkl_uri.GetData(),
						nkl_size
					);
					if (errorID != 0)
					{
						return false;
					}
				}
				newTrackInfo.themeHash = *hashValue;
				newTrackInfo.themeID = trackId;

				ResTrackInfos.Add(newTrackInfo);
			}
		}
		if (ResTrackInfos.IsEmpty()) { return false; }
		return true;
	}
}

#pragma optimize("", on)
#undef LOCTEXT_NAMESPACE