#include <cstdio>
#include <Windows.h>

//globals
static int** g_pLocalPlayer = nullptr; //has to be a pointer to pointer for some stupid reason (dont deref twice!)


//func pointers
int (*TripPlayer)(int*);
int (*DisplayText)(int, const char*);

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

void RunHackLoop()
{
    while (true)
    {
        /*if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            //float flHealth = 100.0f;
            //memcpy((uintptr_t*)g_pLocalPlayer + 0xb860, &flHealth, sizeof(float));
            printf("%f\n", *(float*)((char*)g_pLocalPlayer + 0xb860));
        }*/
        //printf("player pointer: %p\n", (char*)g_pLocalPlayer);
        //printf("base pointer: %p\n", iBase);
       // printf("player pointer no deref: %p\n", g_pLocalPlayer);
        //printf("player pointer one deref: %p\n", *g_pLocalPlayer);
        //printf("base pointer one deref: %016X\n", *iBase);
        //printf("player health: %f\n", (float)*(((int*)g_pLocalPlayer) + 0xb860));
        //printf("player pointer two deref: %X\n", **(int**)g_pLocalPlayer);
        if (*g_pLocalPlayer)
        {
            char* flHealthAddress = ((*(char**)g_pLocalPlayer) + 0xb860);
            //float flHealth = *(float*)flHealthAddress;
            //printf("local player health: %f\n", flHealth); //print player health which is 0xb860 bytes offset from the player pointer (have to cast to char** because of C++ type nonsense)
            float flNewHealth = 1000.0f;
            memcpy(flHealthAddress , &flNewHealth, sizeof(flNewHealth));
            if (GetAsyncKeyState(VK_NUMPAD5) & 1)
            {
                //float flHealth = 100.0f;
                //memcpy((uintptr_t*)g_pLocalPlayer + 0xb860, &flHealth, sizeof(float));
                //TripPlayer(*g_pLocalPlayer);
                DisplayText(TEXT_BOTTOM2, "shitting and farting");
                printf("Tripping the player!\n");
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
    char* iBase = (char*)GetModuleHandle(NULL);
    //char* pPlayerPointer = iBase + 0x14CD998;
    g_pLocalPlayer = (int**)(iBase + 0x231C898); //a pointer will ALWAYS reside at this address that will always point to the player
    TripPlayer = (int(*)(int*))(iBase + 0x77B80);
    DisplayText = (int(*)(int, const char*))(iBase + 0x2492E0);
    AllocConsole();
    SetConsoleTitleA("Output");
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    RunHackLoop();

    fclose((FILE*)stdin);
    fclose((FILE*)stdout);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 1;
}