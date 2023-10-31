#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

// Math definitions
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI			3.14159265359f

// Typedefs
using uint = unsigned int;
using ulong = unsigned long;

// Enums
enum update_status {
    UPDATE_CONTINUE = 1,
    UPDATE_STOP,
    UPDATE_ERROR
};

#endif
