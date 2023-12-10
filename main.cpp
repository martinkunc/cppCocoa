 /* On MacOs Sonoma 14.1.2 with Apple silicon
  *  g++ -v
  * Apple clang version 15.0.0 (clang-1500.0.40.1)
  * Target: arm64-apple-darwin23.1.0
  * Thread model: posix
  * InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
  * 
  * Compile using:
  *   g++ -framework Cocoa -o main main.cpp
 */
#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc.h>
#include <objc/objc-runtime.h>
#include <iostream>

#define safeObjcMsgSend(target, selector, ...) ((id (*)(id, SEL, ...))objc_msgSend)(target, selector, ##__VA_ARGS__)

extern "C" int NSRunAlertPanel(CFStringRef strTitle, CFStringRef strMsg,
                               CFStringRef strButton1, CFStringRef strButton2, 
                               CFStringRef strButton3, ...);

int main(int argc, char** argv) {
  id app = NULL;
  id pool = (id)objc_getClass("NSAutoreleasePool");
  if (!pool)
  {
    std::cerr << "Unable to get NSAutoreleasePool!\nAborting\n";
    return -1;
  }
 
  pool = safeObjcMsgSend(pool, sel_registerName("alloc"));
  if (!pool) {
    std::cerr << "Unable to create NSAutoreleasePool...\nAborting...\n";
    return -1;
  }
  safeObjcMsgSend(pool, sel_registerName("init"));
  app = safeObjcMsgSend((id)objc_getClass("NSApplication"), sel_registerName("sharedApplication"));

  NSRunAlertPanel(CFSTR("Testing"),
                  CFSTR("This is a simple test to display NSAlertPanel."),
                  CFSTR("OK"), NULL, NULL);

  safeObjcMsgSend(pool, sel_registerName("release"));;
  return 0;
}