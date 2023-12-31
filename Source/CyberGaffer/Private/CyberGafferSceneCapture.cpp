﻿// Copyright (c) 2023 ALT LLC.
//
// Distributed under the terms of the MIT License (see the accompanying LICENSE.txt file or get a copy at http://opensource.org/licenses/MIT).


#include "CyberGafferSceneCapture.h"
#include "CyberGafferSceneCaptureComponent2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

ACyberGafferSceneCapture::ACyberGafferSceneCapture(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	_cyberGafferSceneCaptureComponent2D = CreateDefaultSubobject<UCyberGafferSceneCaptureComponent2D>(TEXT("NewCyberGafferSceneCaptureComponent2D"));
	_cyberGafferSceneCaptureComponent2D->SetupAttachment(RootComponent);

	FVector capturePosition = {-300,0,0};
	FVector spherePosition = {0,0,0};
	FVector sphereScale {0.1f,0.1f,0.1f};
	
	_cyberGafferSceneCaptureComponent2D->SetRelativeLocation(capturePosition);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	FString pathMaterial = "Script/Engine.Material'/CyberGaffer/Materials/WhiteDiffuse.WhiteDiffuse'";
	BaseSphereMaterial = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, *pathMaterial));

	_taskSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TaskSphere"));
	_taskSphere->SetupAttachment(RootComponent);
	_taskSphere->SetStaticMesh(SphereMeshAsset.Object);
	_taskSphere->SetVisibleInSceneCaptureOnly(true);
	_taskSphere->SetRelativeLocation(spherePosition);
	_taskSphere->SetWorldScale3D(sphereScale);
	_taskSphere->CastShadow = false;
	
	_gizmoSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GizmoSphere"));
	_gizmoSphere->SetupAttachment(RootComponent);
	_gizmoSphere->SetStaticMesh(SphereMeshAsset.Object);
	_gizmoSphere->SetOnlyOwnerSee(true);
	_gizmoSphere->SetRelativeLocation(spherePosition);
	_gizmoSphere->SetWorldScale3D(sphereScale);
	_gizmoSphere->CastShadow = false;
}

void ACyberGafferSceneCapture::BeginPlay()
{
	
}


void ACyberGafferSceneCapture::OnInterpToggle(bool bEnable) {
	_cyberGafferSceneCaptureComponent2D->SetVisibility(bEnable);
	_taskSphere->SetVisibility(bEnable);
}

void ACyberGafferSceneCapture::PostActorCreated()
{
	_taskSphere->SetMaterial(0, BaseSphereMaterial);
	_gizmoSphere->SetMaterial(0, BaseSphereMaterial);
	
}

