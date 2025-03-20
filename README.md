# keylogger

This repository contains a basic keylogger implementation for macOS written in C++. It is provided for educational purposes ONLY.

## Requirements

* macOS
* `g++` compiler

## Get Started

### Clone the repository

```shell
$ git clone https://github.com/rubnsbarbosa/keylogger.git
$ cd keylogger
```

### Compile the code

```shell
g++ keylogger.cpp -o keylogger -framework ApplicationServices
```

### Grant accessibility access

Grant access to this application in Privacy & Security settings, located in System Settings. This is a required step for the keylogger to monitor keyboard events, you need to grant your terminal application (or other application, e.g., VS Code) accessibility access.

### Run the keylogger

```shell
./keylogger
```

### Press your keyboard keys

The pressed keys will be recorded in the `logger.txt` file in the same directory where you ran the program.

### Stop the keylogger

Press `Ctrl+C` in the Terminal to stop the program.

### View the log file

Open the `logger.txt` file to see the recorded key events.

## Reference

[Core Graphics | Apple Developer Documentation](https://developer.apple.com/documentation/coregraphics)

```swift
func tapCreate(
    tap: Tap into system-wide events,
    place: Insert the tap at the beginning of the event,
    options: Tap default options
    eventsOfInterest: A bit mask that specifies the set of events of interest,
    callback: An event tap callback method that you provide,
    userInfo: This pointer is passed into the callback method specified in the callback parameter
) -> CFMachPort?
```

Creates an event tap and returns a core foundation mach port that represents the new event tap, or NULL if the event tap could not be created.    

Event taps receive key up and key down events if one of the following conditions is true:

- The current process is running as the root user.
- Access for assistive devices is enabled. In OS X v10.4, you can enable this feature using System Preferences, Universal Access panel, Keyboard view.

After creating an event tap, you can add it to a run loop as follows:

Pass the event tap to the [CFMachPortCreateRunLoopSource(allocator, port, order)](https://developer.apple.com/documentation/corefoundation/1400928-cfmachportcreaterunloopsource) function to create a run loop event source.

Creates a CFRunLoopSourceRef object for a CFMachPort object.

```swift
func CFMachPortCreateRunLoopSource(
    allocator: Pass NULL or kCFAllocatorDefault to use the current default allocator,
    port: The Mach port for which to create a CFRunLoopSource object,
    order: order is currently ignored by CFMachPortRef run loop sources. Pass 0 for this value
) -> CFRunLoopSourceRef?
```

A callback function that’s invoked whenever an associated event tap receives a Quartz event.

```swift
typealias CGEventTapCallBack = (
    CGEventTapProxy,
    CGEventType,
    CGEvent,
    UnsafeMutableRawPointer?
) -> Unmanaged<CGEvent>?
```

proxy: A proxy for the event tap. See `CGEventTapProxy`.  
type: The event type of this event. See `CGEventType`.  
event: The incoming event. This event is owned by the caller, and you do not need to release it.  
refcon: A pointer to user-defined data. You specify this pointer when you create the event tap.  

[CGEventTapLocation](https://developer.apple.com/documentation/coregraphics/cgeventtaplocation)  
[CGEventTapPlacement](https://developer.apple.com/documentation/coregraphics/cgeventtapplacement)  
[CGEventTapOptions](https://developer.apple.com/documentation/coregraphics/cgeventtapoptions)  
[CGEventMask](https://developer.apple.com/documentation/coregraphics/cgeventmask)  
[CGEventTapCallBack](https://developer.apple.com/documentation/coregraphics/cgeventtapcallback)  
[UnsafeMutableRawPointer](https://developer.apple.com/documentation/Swift/UnsafeMutableRawPointer)  
[CFMachPort](https://developer.apple.com/documentation/CoreFoundation/CFMachPort)  
[CFMachPortCreateRunLoopSource](https://developer.apple.com/documentation/corefoundation/cfmachportcreaterunloopsource(_:_:_:))  
[CFAllocator](https://developer.apple.com/documentation/corefoundation/cfallocator)  
[CFMachPort](https://developer.apple.com/documentation/corefoundation/cfmachport)  
[CFIndex](https://developer.apple.com/documentation/corefoundation/cfindex)  
[CFRunLoopSource](https://developer.apple.com/documentation/corefoundation/cfrunloopsource)  
[CGEventTapCallBack](https://developer.apple.com/documentation/coregraphics/cgeventtapcallback)  
[CGEventTapProxy](https://developer.apple.com/documentation/coregraphics/cgeventtapproxy)  
[CGEventType](https://developer.apple.com/documentation/coregraphics/cgeventtype)  
[CGEvent](https://developer.apple.com/documentation/coregraphics/cgevent)  
[UnsafeMutableRawPointer](https://developer.apple.com/documentation/Swift/UnsafeMutableRawPointer)  

Apple deprecated and removed some classes and objects from their [Documentation](https://developer.apple.com/documentation). `¯\_(ツ)_/¯`

## Disclaimer

* This code is not meant to be malicious, so therefore, do not use it for any malicious purposes.
* Using this software to monitor or collect data without user explicit consent is unethical and illegal.
* The contributors of this repository are not responsible for any misuse of this software.

## License<a id="license"></a>

This repository is licensed under the [MIT License](https://github.com/rubnsbarbosa/keylogger/blob/main/LICENSE)
