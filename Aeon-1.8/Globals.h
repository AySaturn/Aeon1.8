#pragma once
#include "framework.h"

namespace Globals
{
	namespace FortEngine
	{
		UFortEngine* Get()
		{
			auto A = UObject::FindObject<UFortEngine>("FortEngine_");
			return A;
		}
	}

	namespace World
	{
		UWorld* Get()
		{
			auto A = FortEngine::Get()->GameViewport->World;
			return A;
		}
	}

	namespace GameMode
	{
		AFortGameModeAthena* Get()
		{
			auto A = (AFortGameModeAthena*)World::Get()->AuthorityGameMode;
			return A;
		}

		void StartMatch()
		{
			auto A = Get();
			A->StartPlay();
			A->StartMatch();
		}
	}

	namespace GameState
	{
		AFortGameStateAthena* Get()
		{
			auto A = (AFortGameStateAthena*)World::Get()->GameState;
			return A;
		}

		void ChangePlaylistID(int ID)
		{
			Get()->CurrentPlaylistId = ID;
		}

		void LateGame()
		{

		}
	}

	namespace GameSession
	{
		AFortGameSession* Get()
		{
			auto A = (AFortGameSession*)GameMode::Get()->GameSession;
			return A;
		}

		void SetMaxPlayers(int Max)
		{
			Get()->MaxPlayers = Max;
		}
	}

	namespace GameplayStatics
	{
		UGameplayStatics* Get()
		{
			auto A = UObject::FindObject<UGameplayStatics>("GameplayStatics Engine.Default__GameplayStatics");
			return A;
		}

		template<typename T = AActor>
		T* SpawnActor(UClass* Class, FVector Location = {}, FRotator Rotation = {})
		{
			FQuat Quat;
			FTransform Transform;
			Quat.W = 0;
			Quat.X = Rotation.Pitch;
			Quat.Y = Rotation.Roll;
			Quat.Z = Rotation.Yaw;
			Transform.Rotation = Quat;
			Transform.Scale3D = FVector{ 1,1,1 };
			Transform.Translation = Location;

			auto Actor = Get()->STATIC_BeginDeferredActorSpawnFromClass(World::Get(), Class, Transform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn, nullptr);
			Get()->STATIC_FinishSpawningActor(Actor, Transform);
			return (T*)Actor;
		}

		template<typename T = AActor>
		T* SpawnActor(FVector Location = {}, FRotator Rotation = {})
		{
			auto Class = T::StaticClass();

			auto Actor = SpawnActor<T>(Class, Location, Rotation);
			return Actor;
		}

		template<typename T = AActor>
		TArray<T*> GetActors()
		{
			auto Class = T::StaticClass();
			TArray<AActor*> Actors;
			TArray<T*> Ret;
			Get()->STATIC_GetAllActorsOfClass(World::Get(), Class, &Actors);
			for (int i = 0; i < Actors.Num(); i++)
			{
				Ret.Add((T*)Actors[i]);
			}
			return Ret;
		}

		template<typename T = AActor>
		T* FindActor(int i = 0)
		{
			auto Cluster = GetActors<T>();
			return Cluster[i];
		}
	}

	namespace LocalPlayers
	{
		TArray<ULocalPlayer*> Get()
		{
			auto A = World::Get()->OwningGameInstance->LocalPlayers;
			return A;
		}

		ULocalPlayer* At(int i)
		{
			auto A = Get();
			return A[i];
	    }

		void Remove(int i)
		{
			auto A = Get();
			A.Remove(i);
		}
	}

	namespace LocalPlayerController 
	{
		AFortPlayerController* Get()
		{
			auto A = LocalPlayers::At(0)->PlayerController;
			return (AFortPlayerController*)A;
		}

		void SwitchLevel(FString Map = L"Athena_Terrain?Game=/Game/Athena/Athena_GameMode.Athena_GameMode_C")
		{
			Get()->SwitchLevel(Map);
		}
	}

	namespace KismetSystemLibrary
	{
		UKismetSystemLibrary* Get()
		{
			auto A = UObject::FindObject<UKismetSystemLibrary>("KismetSystemLibrary Engine.Default__KismetSystemLibrary");
			return A;
		}

		void ExecuteCommand(FString Command)
		{
			Get()->STATIC_ExecuteConsoleCommand(World::Get(), Command, nullptr);
		}
	}

	namespace KismetMathLibrary
	{
		UKismetMathLibrary* Get()
		{
			auto A = UObject::FindObject<UKismetMathLibrary>("KismetMathLibrary Engine.Default__KismetMathLibrary");
			return A;
		}

		int RandomIntegerInRange(int Min, int Max)
		{
			auto A = Get()->STATIC_RandomIntegerInRange(Min, Max);
			return A;
		}
	}

	namespace KismetTextLibrary
	{
		UKismetTextLibrary* Get()
		{
			auto A = UObject::FindObject<UKismetTextLibrary>("KismetTextLibrary Engine.Default__KismetTextLibrary");
			return A;
		}

		FText StringToText(FString String)
		{
			auto A = Get()->STATIC_Conv_StringToText(String);
			return A;
		}

		FString TextToString(FText Text)
		{
			auto A = Get()->STATIC_Conv_TextToString(Text);
			return A;
		}
	}

	UCustomCharacterPart* BodyPart;
	UCustomCharacterPart* HeadPart;

	bool bEnableMenu = true;	// In-Game Menu.
	static bool bLateGame = false;	// Soon (maybe).
	static bool bEnableCheats = false; // Soon.
	static bool bSTW = false; // Maybe.
	static bool bInfiniteAmmo = true;
	static bool bInfiniteResources = true;
	static int MaxPlayers = 10;
	static int PlaylistID = 2; // 2 = Solo, 
	static int NetSpeed = 30000; // Don't touch
	static FVector BusLocation = { 2500 , 250, 500 };

	void Init()
	{
		BodyPart = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Soldier_01.F_Med_Soldier_01");
		HeadPart = UObject::FindObject<UCustomCharacterPart>("CustomCharacterPart F_Med_Head1.F_Med_Head1");
	}
}