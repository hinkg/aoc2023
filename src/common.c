#ifndef _common_c_
#define _common_c_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;

typedef float f32;
typedef double f64;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define ABS(x) ((x) < 0 ? (-(x)) : (x))
#define SIGN(x) (((x) > 0) - ((x) < 0))

#define DEGREES(radians) ((radians) * 180 / PI)
#define RADIANS(degrees) ((degrees) * PI / 180)

#define CLOSEST_MUL(a, b) (((b) + ((a) - 1)) & ~((a) - 1))

//
// FILE HANDLING
//

typedef struct file_t {
    char *data;
    usize size;
} file_t;

int file_load(file_t *file, const char *path) {
    FILE *f = fopen(path, "rb");

    if (!f) {
        printf("Failed to open file at \"%s\"\n", path);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    rewind(f);
    char *data = (char *)malloc((size_t)length + 1);
    memset(data, 0, (size_t)length + 1);
    fread(data, 1, (size_t)length, f);
    fclose(f);

    file->size = (size_t)length;
    file->data = data;
    return 0;
}

int file_write(const char *path, const char * data) {
    FILE *f = fopen(path, "wb");
    fprintf(f, "%s", data);
    fclose(f);
    return 0;
}

void file_free(file_t *file) {
    free(file->data);
    memset(file, 0, sizeof(file_t));
}

//
// LOGGING
//

static char buffer[512];

void log_print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf_s(buffer, 1, format, args);
    va_end(args);

    printf("%s", buffer);
}

//
// TIME
//

#ifdef _WIN32 

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static i64 qpc_freq;

// Is this even accurate?
i64 time_tick_now(void) {
    if (qpc_freq == 0) {
        QueryPerformanceFrequency((LARGE_INTEGER *)&qpc_freq);
    }

    i64 now;
    QueryPerformanceCounter((LARGE_INTEGER *)&now);

    return (now / qpc_freq) * (1000000000LL) + (now % qpc_freq) * (1000000000LL) / (qpc_freq);
}

#else 

// TODO: non-windows time

#endif

double time_seconds(i64 ticks) {
    i64 sec = ticks / (1000000000LL);
    i64 nsec = ticks % (1000000000LL);
    return (f64)(sec) + (f64)(nsec) / (1e9);
}

double time_milliseconds(i64 ticks) {
    return time_seconds(ticks) * 1000;
}

double time_microseconds(i64 ticks) {
    return time_seconds(ticks) * 1000000;
}

#endif
