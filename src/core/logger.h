#ifndef __LOGGER_H__
#define __LOGGER_H__

void EngineLog(const char file[], int line, const char* format, ...);

#define LOG(format, ...) EngineLog(__FILE__, __LINE__, format, __VA_ARGS__)

#endif
