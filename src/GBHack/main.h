#pragma once
#include <cstdio>
#include "include/MinHook.h"
#include "maths.h"
#include <windows.h>

//structure defs
enum DisplayTextType
{
    TEXT_BOTTOM = 0,
    TEXT_BOTTOM2,
    TEXT_SPIRITGUIDE,
    TEXT_NEWOBJECTIVE,
    TEXT_TOP = 11,
    TEXT_SUBTITLE,
    TEXT_RIGHT,
    TEXT_QUITWARNING
};

#pragma pack(1)
class CGameView
{
public:
    void* vtable;
    float position1;
    float unknown1;
    float position2;
    float angle1;
    float angle2;
    float empty1;
    float fov;
    float empty2[2];
    float screenwidth;
    float screenheight;
    float empty3[10];
    float unknown2;
    float empty4[3];
    float position3;
    float angle3;
    float position4;
};
#pragma pack()

//globals
extern int** g_pLocalPlayer; //has to be a pointer to pointer for some stupid reason (dont deref twice!)
extern Vector* g_pLocalPlayerCollider;
extern CGameView* g_pGameView;
extern bool g_bInfiniteHealthEnabled;
extern bool g_bInfiniteAmmoEnabled;
extern bool g_bNoclipEnabled;
extern char* g_cGameBase;


//func pointers
extern int (*TripPlayer)(int*);
extern int (*DisplayText)(int, const char*);
extern int (*SetActorPosition)(int*, Vector*, int*);
extern void (*CopyVectorTramp)(Vector*, Vector*);


//func defs
DWORD WINAPI DLLAttach(HMODULE hModule);
void SetupHooks();
void CopyVectorHook(Vector *towrite, Vector *toread);
void FetchPlayerCollider();
void HandleToggleButtons();
void HandleNoclip();
void ToggleNoclip();
void ToggleInfiniteHealth();
void ToggleInfiniteAmmo();
void RunHackLoop();


