// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreSaveData.h"

bool UHighScoreSaveData::HasHighScoreData() const
{
	return HighScores.Num() > 0; 
}

TArray<FHighScoreData> UHighScoreSaveData::GetSortedListOfHighScores(const int CutOff)
{
	const int Target = CutOff < HighScores.Num() and CutOff > 0  ? CutOff: HighScores.Num(); 
	TArray<FHighScoreData> ReturnArray;
	
	HighScores.Sort([](const FHighScoreData& A, const FHighScoreData& B) {
		return A.RoundReached > B.RoundReached;
	});

	for (int i = 0; i < Target; i++) {
		ReturnArray.Add(HighScores[i]);
	}

	return ReturnArray; 	
}

void UHighScoreSaveData::AddHighScoreItem(const FHighScoreData &HighScore)
{
	HighScores.Add(HighScore);
}
