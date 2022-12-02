#include "main.h"
#include "logging.h"
#include <windows.h>
#include <cstdio>


DWORD WINAPI DLLAttach(HMODULE hModule)
{
    AllocConsole();
    SetConsoleTitleA("GBHack Version " STR(GBHACK_VERSION) " Output: ");
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    msg(MSGLVL_INFO, "GBHack Version " STR(GBHACK_VERSION) " Loaded, Compiled on " STR(__DATE__) " at " STR(__TIME__));

    for (;;)

    fclose((FILE*)stdin);
    fclose((FILE*)stdout);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 1;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DLLAttach, hModule, 0, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

