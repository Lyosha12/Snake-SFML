//
// Created by Lyosha12 on 18.06.2018.
//

#include <iostream>
#include <mutex>
#include <windows.h>

#include "ErrorPrinter.hpp"

static std::mutex error_mutex;

ErrorPrinter::
ErrorPrinter(std::string cause): cause(cause) { }

void ErrorPrinter::
print() {
    std::lock_guard<std::mutex> lock(error_mutex);
    
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    std::cerr << "Program will stop. Error: \n   \'" << cause << '\'' << std::endl;
    system("PAUSE");
    exit(1);
}