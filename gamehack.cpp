#include "Main.h"

Player* Me;
Target* Him;
Camera* Cam;

void HackMain() {

	while(true) {
		if(PlayerStructPtr)
			Me = (Player*)PlayerPtr;
		if(TargetStructPtr && TargetPtr)
			Him = (Target*)TargetPtr;
		if(CameraStructPtr && CameraPtr)
			Cam = (Camera*)CameraPtr;
		
		//->Teleport<-\\ 
		__try {
			if(GetAsyncKeyState(VK_CONTROL) && TargetDistance <= 20 && TargetPtr!=NULL) {
				while(GetAsyncKeyState(VK_CONTROL))
					Sleep(10);
				Me->PositionX=Him->PositionX;
				Me->PositionY=Him->PositionY;
			}
		}
		__except(1) {
			Sleep(10);
		}

		//->Speedhack<-\\ 
		if(GetAsyncKeyState(VK_SHIFT) && SpeedPtr != NULL) {
			while(GetAsyncKeyState(VK_SHIFT))
				Sleep(10);
			bSpeedhack=!bSpeedhack;
			switch(bSpeedhack) {
				case true:
					MovSpeed = 0x02010004;
					AtkSpeed = 0x0916A0CA;
					break;
				case false:
					MovSpeed = 0x02010002;
					AtkSpeed = 0x0516A0CA;
					break;
			}
		}

		//->Superjump<-\\ 
		if(GetAsyncKeyState(VK_SPACE) && bSuperjump==true) {
			while(GetAsyncKeyState(VK_SPACE))
				Sleep(10);
			for(float i=0.0; i<1.3; i=i+(float)0.1)
				*(float*) (&Me->PositionZ) =  (*(float*) (&Me->PositionZ)+(float)i);
		}

		//->Flyhack<-\\ 
		if(GetAsyncKeyState(VK_NUMPAD0) && asmFly1 && asmFly2) {
			while(GetAsyncKeyState(VK_NUMPAD0))
				Sleep(10);
			bFlyhack=!bFlyhack;
			switch(bFlyhack) {
				case true:
					memcopy(asmFly1, (void*)FlyhackPatch, sizeof(FlyhackPatch));
					memcopy(asmFly1b, (void*)FlyhackPatch, sizeof(FlyhackPatch));
					memcopy(asmFly2, (void*)FlyhackPatch, sizeof(FlyhackPatch));
					memcopy(asmFly2b, (void*)FlyhackPatch, sizeof(FlyhackPatch));
					break;
				case false:
					memcopy(asmFly1, (void*)Flypatch1Old, sizeof(Flypatch1Old));
					memcopy(asmFly1b, (void*)Flypatch1Old, sizeof(Flypatch1Old));
					memcopy(asmFly2, (void*)Flypatch2Old, sizeof(Flypatch2Old));
					memcopy(asmFly2b, (void*)Flypatch2Old, sizeof(Flypatch2Old));
					break;
			}
		}

		if(GetAsyncKeyState(VK_NUMPAD1)) {
			*(float*) (&Me->PositionZ) =  (*(float*) (&Me->PositionZ)+(float)0.2);
			Cam->ViewY = (float)(Me->PositionZ+3.5);
		}

		if(GetAsyncKeyState(VK_NUMPAD2)) {
			*(float*) (&Me->PositionZ) =  (*(float*) (&Me->PositionZ)-(float)0.2);
			Cam->ViewY = (float)(Me->PositionZ+3.5);
		}

		if(GetAsyncKeyState(VK_NUMPAD3)) {
			while(GetAsyncKeyState(VK_NUMPAD3))
				Sleep(10);
			bSuperjump=!bSuperjump;
		}

		Sleep(1);
	}

}


void GetMemory() {
	if(!(baseAddr = (DWORD)GetModuleHandleA("Game.exe")))
		FreeConsole();

	PlayerStructPtr = (*(DWORD*)(dwFindPattern(baseAddr, moduleSize, codePlayerStructPtr, maskPlayerStructPtr)+1));
	if(!PlayerStructPtr)
		printf("Pointer [0x1] couldn't be found\n");

	TargetStructPtr = (byte*)dwFindPattern(baseAddr, moduleSize, codeTargetStructPtr, maskTargetStructPtr);
	if(!TargetStructPtr)
		printf("Pointer [0x2] couldn't be found\n");
	else {
		TargetPtrRet=TargetStructPtr+6;
		memcopy((DWORD)(TargetStructPtr+5), (void*)NOP, sizeof(NOP));
		Detour(TargetStructPtr, (byte*)TargetPtrHook);
	}

	CameraStructPtr = (byte*)dwFindPattern(baseAddr, moduleSize, codeCameraStructPtr, maskCameraStructPtr);
	if(!CameraStructPtr)
		printf("Pointer [0x3] couldn't be found\n");
	else {
		CameraPtrRet=CameraStructPtr+9;
		memcopy((DWORD)(CameraStructPtr+5), (void*)CamPatch, sizeof(CamPatch));
		Detour(CameraStructPtr, (byte*)CameraPtrHook);
	}

	memVisualpatch = *(DWORD*)(dwFindPattern(baseAddr, moduleSize, codeVisualpatch, maskVisualpatch)+21);
	asmVisualpatch = (dwFindPattern(baseAddr, moduleSize, codeVisualpatch, maskVisualpatch)+19);
	if(memVisualpatch && asmVisualpatch) {
		memcopy(asmVisualpatch, (void*)NOP, sizeof(NOP));
		*(DWORD*)memVisualpatch=1;
	}else
		printf("Pointer [0x4] couldn't be found\n");

	SpeedPtr = dwFindPattern(baseAddr, moduleSize, codeSpeedPtr, maskSpeedPtr);
	if(!SpeedPtr)
		printf("Pointer [0x5] couldn't be found\n");
	else {
		SpeedPtrRet = SpeedPtr+7;
		memcopy((DWORD)(SpeedPtr+5), (void*)SpeedPatch, sizeof(SpeedPatch));
		Detour((byte*)SpeedPtr, (byte*)SpeedPtrHook);
		SpeedPtr = NULL;
	}

	asmFly1 = dwFindPattern(baseAddr, moduleSize, codeFlypatch1, maskFlypatch1);
	if(!asmFly1)
		printf("Pointer [0x6] couldn't be found\n");
	asmFly2 = dwFindPattern(baseAddr, moduleSize, codeFlypatch2, maskFlypatch2);
	if(!asmFly2)
		printf("Pointer [0x7] couldn't be found\n");

	HackMain();

}

int WINAPI DllMain(HINSTANCE hInstance, DWORD Reason, LPVOID Reserved) {
	if(Reason==DLL_PROCESS_ATTACH) {

		GetConsole("Shaiya++ Version 2.0");

		printf("Welcome to Shaiya++ v2.0 by u-coRe aka buFFy !\n");
		printf("Status: Undetected (4/26/10)\n\n");

		printf("Hotkeys: \n-------------\n");
		printf("Numpad0: Unlock Gravity / Initiate Flyhack\n");
		printf("Numpad1: Increase Height\n");
		printf("Numpad2: Decrease Height\n");
		printf("Numpad3: Toggle Superjump\n");
		printf("Ctrl: Teleport to Target\n");
		printf("Alt: Toggle Speedhack\n");

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GetMemory, 0, 0, 0);

		return true;
	}
	return false;
}
 