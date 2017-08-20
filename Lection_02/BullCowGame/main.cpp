// "BullCowGame.cpp": Definiert den Einstiegspunkt für die Konsolenanwendung.
//
/* This is the console executable, that makes use ofthe BullCow class
This acts as the view in a MVC pattern, and is responsible for all user 
interaction. For game logic see the FBullCowGame class
*/
#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBackResult(FText);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

int main()
{	
	bool bPlayAgain = false;
	do	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())	{
		std::cout << "YOU WON!\n You needed " << BCGame.GetCurrentTry()-1 << " trys to find the word.\n";
	}
	else
	{
		std::cout << "YOU LOST!\n Better luck next time.\n";
	}
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	

	// loop asking for guesses while the game is 
	// NOT won and there are still trys remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << "\n";
	}
	PrintGameSummary();
	
	
	return;
}

// loop continually until user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		
		std::cout << std::endl << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << " | Please enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter the word lowercase only.\n";
			break;
		default:
			// assume guess is valid
			break;
		}
		
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again with the same hidden word? (y|n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');
}
