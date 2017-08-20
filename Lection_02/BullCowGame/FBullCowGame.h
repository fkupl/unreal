/* The game logic (no view code or direct user interaction)
The game is a simple guessword game based on Mastermind*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialzed to 0
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // Contructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);
	
private:
	//see contructor for initialization values
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};