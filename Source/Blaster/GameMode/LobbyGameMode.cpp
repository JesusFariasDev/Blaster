// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) 
{
	// PostLogin first safe place to access the player controller that just joined
	Super::PostLogin(NewPlayer);

	// GameState hold a game state base
	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	// Set to travel to the game map if there are 2 players
	if (NumberOfPlayers == 2) 
	{
		UWorld* World = GetWorld();
		if (World) 
		{
			bUseSeamlessTravel = true;
			// Listen in the path is watching if the map is open to connections
			World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));
		}
	}
}

