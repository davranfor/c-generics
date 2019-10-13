#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "utils.h"

/* File utilities */

#define FILE_LINE_MAX 256

static long f_get_size(FILE *file)
{
    if (fseek(file, 0L, SEEK_END) == -1)
    {
        perror("fseek");
        return -1;
    }

    long size = ftell(file);

    if (size == -1)
    {
        perror("ftell");
        return -1;
    }
    if (fseek(file, 0L, SEEK_SET) == -1)
    {
        perror("fseek");
        return -1;
    }
    return size;
}

long file_get_size(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        return -1;
    }
    
    long size = f_get_size(file);

    fclose(file);
    return size;
}

static char *f_get_mem(FILE *file, size_t size)
{
    char *str = malloc(size + 1);

    if (str == NULL)
    {
        perror("malloc");
        return NULL;
    }
    if (fread(str, 1, size, file) != size)
    {
        free(str);
        perror("fread");
        return NULL;
    }
    str[size] = '\0';
    return str;
}

static char *f_read(FILE *file)
{
    long size = f_get_size(file);

    if (size == -1)
    {
        return NULL;
    }    
    return f_get_mem(file, (size_t)size);
}

char *file_read(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        return NULL;
    }

    char *str = f_read(file);

    fclose(file);
    return str;
}

char *file_read_line(FILE *file)
{
    assert(file != NULL);

    char str[FILE_LINE_MAX];
    char *buf = NULL;
    char *ptr = NULL;
    size_t size = 0;

    while (fgets(str, sizeof str, file) != NULL)
    {
        size_t len = sizeof str;

        ptr = strchr(str, '\n');
        if (ptr != NULL)
        {
            len = (size_t)(ptr - str) + 1;
            *ptr = '\0';
        }
        ptr = realloc(buf, size + len);
        if (ptr == NULL)
        {
            free(buf);
            perror("realloc");
            return NULL;
        }
        memcpy(ptr + size, str, len);
        if (len != sizeof str)
        {
            return ptr;
        }
        size += len - 1;
        buf = ptr;
    }
    free(buf);
    if (!feof(file) && ferror(file))
    {
        perror("fgets");
    }
    return NULL;
}

size_t file_write(const char *path, const char *str, int append)
{
    FILE *file = fopen(path, append ? "a" : "w");

    if (file == NULL)
    {
        return FILE_WRITE_ERROR;
    }

    size_t size = strlen(str);

    if (fwrite(str, 1, size, file) != size)
    {
        size = FILE_WRITE_ERROR;
        perror("fwrite");
    }
    fclose(file);
    return size;
}

/* String utilities */

char *string_clone(const char *str)
{
    assert(str != NULL);

    size_t size = strlen(str) + 1;
    char *ptr = malloc(size);

    if (ptr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    return memcpy(ptr, str, size);
}

char *string_slice(const char *str, size_t start, size_t end)
{
    assert(str != NULL);
    assert(end >= start);

    size_t diff = end - start;
    char *ptr = malloc(diff + 1);

    if (ptr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    memcpy(ptr, str + start, diff);
    ptr[diff] = '\0';
    return ptr;
}

static char *string_vprint(const char *fmt, va_list args)
{
    va_list copy;

    va_copy(copy, args);

    size_t len = (size_t)vsnprintf(NULL, 0, fmt, args);
    char *str = malloc(len + 1);

    if (str == NULL)
    {
        perror("malloc");
        return NULL;
    }
    vsprintf(str, fmt, copy);
    return str;
}

char *string_print(const char *fmt, ...)
{
    assert(fmt != NULL);

    va_list args;

    va_start(args, fmt);

    char *str = string_vprint(fmt, args);

    va_end(args);
    return str;
}

char *string_trim(const char *str)
{
    assert(str != NULL);

    str += string_lskip(str, isspace);

    return string_slice(str, 0,  string_rskip(str, isspace));
}

char *string_ltrim(const char *str)
{
    assert(str != NULL);

    return string_clone(str + string_lskip(str, isspace));
}

char *string_rtrim(const char *str)
{
    assert(str != NULL);

    return string_slice(str, 0, string_rskip(str, isspace));
}

size_t string_length(const char *str)
{
    size_t len = 0;

    while (*str != 0)
    {
        if ((*str++ & 0xc0) != 0x80)
        {
            len++;
        }
    }
    return len;
}

size_t string_lskip(const char *str, int func(int))
{
    assert((str != NULL) && (func != NULL));

    size_t pos = 0;

    while (func((unsigned char)str[pos]))
    {
        pos++;
    }
    return pos;
}

size_t string_rskip(const char *str, int func(int))
{
    assert((str != NULL) && (func != NULL));

    size_t pos = strlen(str);

    while ((pos > 0) && func((unsigned char)str[pos - 1]))
    {
        pos--;
    }
    return pos;
}

