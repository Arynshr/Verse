#include <bits/stdc++.h>

// Define a macro to check inclusion
#define CHECK_WINDOWS_H_INCLUDED

// Attempt to include windows.h
#ifdef CHECK_WINDOWS_H_INCLUDED
    #include <windows.h>
#endif

int main() {
    #ifdef WIN32
        std::cout << "windows.h has been included successfully." << std::endl;
    #else
        std::cout << "windows.h could not be included." << std::endl;
    #endif

    return 0;
}
