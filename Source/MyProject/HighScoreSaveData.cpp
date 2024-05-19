// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreSaveData.h"

TArray<FHighScoreData> UHighScoreSaveData::GetSortedListOfHighScores(const int CutOff)
{
	const int Target = CutOff < HighScores.Num()?  CutOff: HighScores.Num() -1; 
	TArray<FHighScoreData> ReturnArray;
	
	HighScores.Sort([](const FHighScoreData& A, const FHighScoreData& B) {
		return A.RoundReached > B.RoundReached;
	});

	for (int i = 0; i < Target; i++) {
		ReturnArray.Add(HighScores[i]);
	}

	return ReturnArray; 	
}
