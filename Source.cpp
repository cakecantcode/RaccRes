/*

(\_._/)
( 0 0 )
 > ^ <

 RaccResV2

 added more res, cleaned up outputs, stylized, rewritten, faster.

 @cakeracc on twitter

 simple res changer for valorant 1280x882

(\_._/)
( 0 0 )
 > ^ <


*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

static DEVMODE originalMode;
static int originalSaved = 0;

#define TAGLINE "RaccResV2, quickly switch resolution for VALORANT | @cakeracc on twitter | open source"

// clear console
static void clear_console() {
    system("cls"); 
}

// status banner output
static void banner(const string& msg) {
    clear_console();
    cout << "------------------------------------------------------\n";
    cout << msg << "\n";
    cout << "------------------------------------------------------\n\n";
    cout << TAGLINE << "\n\n";
}

// restore res
static void restore_original(void) {
    if (originalSaved) {
        ChangeDisplaySettings(&originalMode, 0);
        banner("RESOLUTION RESTORED TO ORIGINAL");
    }
}

// apply res
static int apply_resolution(DWORD w, DWORD h) {
    DEVMODE dm{};
    dm.dmSize = sizeof(dm);

    if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        banner("ERROR: CANNOT READ CURRENT DISPLAY SETTINGS");
        return 0;
    }

    dm.dmPelsWidth = w;
    dm.dmPelsHeight = h;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    LONG test = ChangeDisplaySettings(&dm, CDS_TEST);
    if (test != DISP_CHANGE_SUCCESSFUL) {
        banner("ERROR: MODE NOT SUPPORTED");
        return 0;
    }

    LONG res = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
    if (res == DISP_CHANGE_SUCCESSFUL) {
        banner("RESOLUTION CHANGED TO " + to_string(w) + "x" + to_string(h));
        return 1;
    }
    else {
        banner("ERROR: FAILED TO APPLY MODE");
        return 0;
    }
}

// menu banner output
static void print_menu(void) {
    cout << "\n=== ultra-fast resolution switcher ===\n";
    cout << "  1) 1920 x 1080 (native 1080p)\n";
    cout << "  2) 1280 x 882\n";
    cout << "  3) 1280 x 960\n";
    cout << "  4) 1024 x 768\n";
    cout << "  5) 1440 x 1080\n";
    cout << "  6) 1680 x 1050\n";
    cout << "  r) restore original resolution\n";
    cout << "  q) quit\n";
    cout << "> ";
}

int main(void) {
    // store original res for restore_original
    ZeroMemory(&originalMode, sizeof(originalMode));
    originalMode.dmSize = sizeof(originalMode);
    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &originalMode)) {
        originalSaved = 1;
        atexit(restore_original);
    }

    string choice;
    for (;;) {
        print_menu();
        if (!getline(cin, choice)) break;

        switch (choice[0]) {
        case '1': apply_resolution(1920, 1080); break;
        case '2': apply_resolution(1280, 882); break;
        case '3': apply_resolution(1280, 960); break;
        case '4': apply_resolution(1024, 768); break;
        case '5': apply_resolution(1440, 1080); break;
        case '6': apply_resolution(1680, 1050); break;
        case 'r': case 'R':
            if (originalSaved) {
                ChangeDisplaySettings(&originalMode, 0);
                banner("RESOLUTION RESTORED TO ORIGINAL");
            }
            else {
                banner("ERROR: ORIGINAL RESOLUTION NOT SAVED");
            }
            break;
        case 'q': case 'Q':
            banner("EXITING PROGRAM");
            return 0;
        default:
            banner("INVALID CHOICE");
        }
    }
    return 0;
}
