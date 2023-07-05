#pragma once

// Fortnite (1.8) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass LCD_Constr_PortoPotty.LCD_Constr_PortoPotty_C
// 0x0020 (0x10F0 - 0x10D0)
class ALCD_Constr_PortoPotty_C : public ABuildingContainer
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x10D0(0x0008) (Transient, DuplicateTransient)
	class UAudioComponent*                             Plumbing_Non_Loop;                                        // 0x10D8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UAudioComponent*                             Water_Loop;                                               // 0x10E0(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UParticleSystemComponent*                    Effect;                                                   // 0x10E8(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass LCD_Constr_PortoPotty.LCD_Constr_PortoPotty_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnLoot();
	void OnDeathPlayEffects(float* Damage, struct FGameplayTagContainer* DamageTags, struct FVector* Momentum, struct FHitResult* HitInfo, class AFortPawn** InstigatedBy, class AActor** DamageCauser, struct FGameplayEffectContextHandle* EffectContext);
	void ExecuteUbergraph_LCD_Constr_PortoPotty(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
