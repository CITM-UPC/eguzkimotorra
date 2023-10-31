#include "logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include "core/application.h"

#ifdef _WIN32
#include <Windows.h>
#endif

const unsigned int kmax_buffer_size = 4096;

void SystemLog(const char* log) {
    std::cout << log << std::endl;

    // Output to Visual Studio Console
    #ifdef _WIN32
    wchar_t wString[kmax_buffer_size];
    MultiByteToWideChar(CP_ACP, 0, log, -1, wString, kmax_buffer_size);
    OutputDebugString(wString);
    #endif
}

void EngineLog(const char file[], int line, const char* format, ...) {
	char tmp_string[kmax_buffer_size];
    char tmp_string_full[kmax_buffer_size];
	va_list ap;
	va_start(ap, format);
	vsprintf_s(tmp_string, kmax_buffer_size, format, ap);
	va_end(ap);

    sprintf_s(tmp_string_full, kmax_buffer_size, "\n%s(%d) : %s", file, line, tmp_string);

    #ifdef _DEBUG
    SystemLog(tmp_string_full);
    #endif

    if (app)
        app->Log(tmp_string_full);
};
