#include "MyLib.h"
#include <iostream>
#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>

namespace MyLib
{
    void MyLibClass::saysomething()
    {
        std::cout << "DEU SERTO" << std::endl;
    }
}


int main(int argc, const char * argv[])
{
    NSRect frame = NSMakeRect(100, 100, 200, 200);
    NSUInteger styleMask = NSBorderlessWindowMask;
    NSRect rect = [NSWindow contentRectForFrameRect:frame styleMask:styleMask];
    NSWindow * window =  [[NSWindow alloc] initWithContentRect:rect styleMask:styleMask backing: NSBackingStoreBuffered    defer:false];
    [window setBackgroundColor:[NSColor blueColor]];
    [window makeKeyAndOrderFront: window];
}
