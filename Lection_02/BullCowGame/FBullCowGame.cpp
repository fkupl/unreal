#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>

//to make syntax Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if guess isn't an isogramm, 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // if guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != Guess.length()) // if guess length is wrong 
	{
		return EGuessStatus::Wrong_Length;
	}
	else
		return EGuessStatus::OK;
	
	return EGuessStatus::OK; 
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, { 5,10 }, { 6,16 },{ 7,20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";  // this MUST be an isogramm
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}


//Receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	
	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) //if they match then
			{
				if (MHWChar == GChar) // if they're in the same place
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)	{
		bGameIsWon = true;
	}
	else	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed letters

		if (LetterSeen[Letter]) { 
			return false;	
		}
		else { 
			LetterSeen[Letter] = true; 
		}
	}
	
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}
