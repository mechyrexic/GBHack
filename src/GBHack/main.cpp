#include "main.h"



//globals
int** g_pLocalPlayer = nullptr; //has to be a pointer to pointer for some stupid reason (dont deref twice!)
Vector** g_pLocalPlayerCollider = nullptr;
CGameView* g_pGameView = nullptr;
bool g_bInfiniteHealthEnabled = false;
bool g_bInfiniteAmmoEnabled = false;
bool g_bNoclipEnabled = false;
char* g_cGameBase = nullptr;


//func pointers
int (*TripPlayer)(int*);
int (*DisplayText)(int, const char*);
int (*SetActorPosition)(int*, Vector*, int*);
void (*CopyVectorTramp)(Vector*, Vector*);


void SetupHooks()
{
    MH_CreateHook((g_cGameBase + 0x2C3AD0), &CopyVectorHook, reinterpret_cast<LPVOID*>(&CopyVectorTramp));
    MH_EnableHook(MH_ALL_HOOKS);
    printf("test\n");
}

void CopyVectorHook(Vector *towrite, Vector *toread)
{
    CopyVectorTramp(towrite, toread);
}

void FetchPlayerCollider()
{
    if (!*g_pLocalPlayer)
    {
        g_pLocalPlayerCollider = nullptr;
        return;
    }
    uintptr_t* pCollider = (uintptr_t*)((*(char**)g_pLocalPlayer) + 0xb658); //god this sucks
    Vector* pPos = (Vector*)(((char*)pCollider) + 0x90);
    printf("x: %f\n", pPos->x);
    printf("y: %f\n", pPos->y);
    printf("z: %f\n", pPos->z);
    printf("col: %016X\n", *(uintptr_t*)pCollider);
}

void HandleToggleButtons()
{
    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
    {
        ToggleInfiniteHealth();
    }
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        ToggleInfiniteAmmo();
    }
    if (GetAsyncKeyState('V') & 1)
    {
        ToggleNoclip();
    }
}

void HandleNoclip()
{
    Vector* pPlayerPosition = (Vector*)((*(char**)g_pLocalPlayer) + 0x54);
    //Vector vecorigin;
    //vecorigin.x = 0;
    //vecorigin.y = 0;
    //vecorigin.z = 0;
    Vector aimdir = Rad2Vec(g_pGameView->angle1, g_pGameView->angle2);
    VectorNormalize(aimdir);
    aimdir.x = pPlayerPosition->x + (aimdir.x * 0.01f);
    aimdir.y = pPlayerPosition->y + (aimdir.y * 0.01f);
    aimdir.z = pPlayerPosition->z + (aimdir.z * 0.01f);
    SetActorPosition(*g_pLocalPlayer, &aimdir, nullptr);
}

void ToggleNoclip()
{
    if (g_bNoclipEnabled)
    {
        g_bNoclipEnabled = false;
        DisplayText(TEXT_RIGHT, "Noclip Disabled");
    }
    else
    {
        g_bNoclipEnabled = true;
        DisplayText(TEXT_RIGHT, "Noclip Enabled");
    }
}

void ToggleInfiniteHealth()
{
    if (g_bInfiniteHealthEnabled)
    {
        g_bInfiniteHealthEnabled = false;
        DisplayText(TEXT_RIGHT, "Infinite Health Disabled");
    }
    else
    {
        g_bInfiniteHealthEnabled = true;
        DisplayText(TEXT_RIGHT, "Infinite Health Enabled");
    }
}

void ToggleInfiniteAmmo()
{
    if (g_bInfiniteAmmoEnabled)
    {
        g_bInfiniteAmmoEnabled = false;
        DisplayText(TEXT_RIGHT, "Infinite Ammo Disabled");
    }
    else
    {
        g_bInfiniteAmmoEnabled = true;
        DisplayText(TEXT_RIGHT, "Infinite Ammo Enabled");
    }
}


void RunHackLoop()
{
    while (true)
    {
        if (*g_pLocalPlayer)
        {

            FetchPlayerCollider();

            HandleToggleButtons();

            if (g_bNoclipEnabled)
            {
                HandleNoclip();
            }

            if (g_bInfiniteHealthEnabled)
            {
                char* flHealthAddress = ((*(char**)g_pLocalPlayer) + 0xb860);
                float flNewHealth = 1000.0f;
                memcpy(flHealthAddress, &flNewHealth, sizeof(flNewHealth));
            }
            if (g_bInfiniteAmmoEnabled)
            {
                char* flAmmoAddress = ((*(char**)g_pLocalPlayer) + 0x24e28);
                float flNewAmmo = 0.0f;
                memcpy(flAmmoAddress, &flNewAmmo, sizeof(flNewAmmo));
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            break; //uninject the dll
        }
    }
    return;
}

DWORD WINAPI DLLAttach(HMODULE hModule)
{
    MH_Initialize();
    g_cGameBase = (char*)GetModuleHandle(NULL);
    g_pLocalPlayer = (int**)(g_cGameBase + 0x231C898);
    g_pGameView = (CGameView*)(g_cGameBase + 0x20AA070);
    TripPlayer = (int(*)(int*))(g_cGameBase + 0x77B80);
    DisplayText = (int(*)(int, const char*))(g_cGameBase + 0x2492E0);
    SetActorPosition = (int(*)(int*, Vector*, int*))(g_cGameBase + 0x86960);
    AllocConsole();
    SetConsoleTitleA("Output");
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    SetupHooks();
    RunHackLoop();

    fclose((FILE*)stdin);
    fclose((FILE*)stdout);
    FreeConsole();
    MH_Uninitialize();
    FreeLibraryAndExitThread(hModule, 0);
    return 1;
}