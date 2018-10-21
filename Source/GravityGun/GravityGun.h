// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//////////////////////////////////////////////////////////////////////////

#define ECC_TRACE_PROJECTILE ECC_GameTraceChannel1 // used by tracing projectiles
#define ECC_OBJECT_PROJECTILE ECC_GameTraceChannel2 // used by moving projectiles

//////////////////////////////////////////////////////////////////////////
// Inline for final builds otherwise allow us to breakpoint in inlined functions
#if UE_BUILD_SHIPPING || UE_BUILD_TEST
#define GG_FORCEINLINE FORCEINLINE
#else
#define GG_FORCEINLINE
#endif