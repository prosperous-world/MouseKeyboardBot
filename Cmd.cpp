#include <iostream>
#include <windows.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void moveMouseRandomly() {
    // Get the width and height of the screen
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int randomX = rand() % screenWidth;
    int randomY = rand() % screenHeight;
    SetCursorPos(randomX, randomY);
    Sleep(500);

   /* mouse_event(MOUSEEVENTF_LEFTDOWN, randomX, randomY, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, randomX, randomY, 0, 0);*/
}

void simulateCoding() {
    INPUT inputs[2] = {};

    int keyArray[8] = {
    // Control up
        0x21,
        0x22,
        0x23,
        0x24,
        0x25,
        0x26,
        0x27,
        0x28,
    };

    int selectedKey = keyArray[rand() % 8];

    // Control down
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = selectedKey; // Virtual-key code for Control key

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = selectedKey;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // Flag to indicate key release

    // Send the input events
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

}

void simulateAltTab() {
    // Press ALT key
    keybd_event(VK_MENU, 0, 0, 0); // VK_MENU is the virtual key code for ALT

    // Press TAB key
    keybd_event(VK_TAB, 0, 0, 0); // VK_TAB is the virtual key code for TAB
    Sleep(100); // Short delay to ensure the TAB press is registered
    keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0); // Release TAB key

    // Release ALT key
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); // Release ALT key
}

void simulateCtrlTab() {
    // Prepare the INPUT structure for keyboard events
    INPUT inputs[4] = {};

    // Control down
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL; // Virtual-key code for Control key

    // Tab down
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_TAB; // Virtual-key code for Tab key

    // Tab up
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = VK_TAB;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // Flag to indicate key release

    // Control up
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP; // Flag to indicate key release

    // Send the input events
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}


int main() {
    FreeConsole();
    Sleep(3000); // Wait for 3 seconds before simulating
    //simulateAltTab();
    //simulateCtrlTab();
    long lastAltTab = GetTickCount();
    long lastCtrlTab = GetTickCount();
    long lastMouseMove = GetTickCount();
    long lastKeyCoding = GetTickCount();

    int randAltTabPeriod = 15;
    int randCtrlTabPeriod = 15;
    int randMouseMovePeriod = 10;
    int randKeyCodingPeriod = 20;

    while (1) {
        //check last Alt + Tab, 15s
        if ((GetTickCount() - lastAltTab) / 1000 > randAltTabPeriod) {
            simulateAltTab();
            lastAltTab = GetTickCount();
            randAltTabPeriod = 20 + (rand() % 60);
        }
        //check last Ctrl + Tab
        if ((GetTickCount() - lastCtrlTab) / 1000 > randCtrlTabPeriod) {
            simulateCtrlTab();
            lastCtrlTab = GetTickCount();
            randCtrlTabPeriod = 20 + (rand() % 60);
        }

        //check last Mouseclick
        if ((GetTickCount() - lastMouseMove) / 1000 > randMouseMovePeriod) {
            int randomMoveCnt = 1 + (rand() % 10);
            for (int i = 0; i < randomMoveCnt; i++) {
                moveMouseRandomly();
                Sleep(10);
            }
            lastMouseMove = GetTickCount();
            randMouseMovePeriod = 2 + (rand() % 5);
        }
        //check last key coding 
        if ((GetTickCount() - lastKeyCoding) / 1000 > randKeyCodingPeriod) {
            int randomStrokCnt= 8 + (rand() % 60);
            for (int i = 0; i < randomStrokCnt; i++) {
                simulateCoding();
                Sleep(10);
            }
            lastKeyCoding = GetTickCount();
            randKeyCodingPeriod = 10 + (rand() % 20);
        }


        Sleep(1000);
    }

    return 0;
}