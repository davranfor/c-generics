#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>

/* ************************************************************************* */
/* File utilities                                                            */
/* ************************************************************************* */

#define FILE_TRUNCATE 0
#define FILE_APPEND 1

#define FILE_ERROR ((size_t)-1)
#define file_error(f) ferror(f)
#define file_eof(f) feof(f)

size_t file_get_size(const char *);
char *file_read(const char *);
char *file_read_with_prefix(const char *, const char *);
char *file_read_with_suffix(const char *, const char *);
char *file_read_quoted(const char *, const char *, const char *);
char *file_read_line(FILE *);
char *file_read_buffer(FILE *, char *, size_t);
size_t file_write(const char *, const char *, int);

/* ************************************************************************* */
/* String utilities                                                          */
/* ************************************************************************* */

#define string_isempty(str) (*(str) == '\0')
#define string_isequal(str1, str2) (!strcmp((str1), (str2)))

/* Functions returning a new string */
char *string_clone(const char *);
char *string_slice(const char *, size_t, size_t);
char *string_replace(const char *, const char *, const char *);
char *string_print(const char *, ...);
char *string_trim(const char *);
char *string_ltrim(const char *);
char *string_rtrim(const char *);
/* Functions working inplace or returning a new string if 1st param is NULL */
char *string_reverse(char *, const char *);
char *string_convert(char *, const char *, int (*)(int));
char *string_repeat(char *, const char *, size_t);
/* Functions working inplace */
int string_format(char *, double, int, const char *);
char *string_tokenize(char **, int);
size_t string_length(const char *);
size_t string_count(const char *, const char *);
size_t string_lskip(const char *, int(*)(int));
size_t string_rskip(const char *, int(*)(int));
int string_casecmp(const char *, const char *);

/* ************************************************************************* */
/* Date utilities                                                            */
/* ************************************************************************* */

void today(int *, int *, int *);
void now(int *, int *, int *);
void day_add(int *, int *, int *, int);
int days_diff(int, int, int, int, int, int);
int day_of_week(int, int, int);
int ISO_day_of_week(int, int, int);
int day_of_year(int, int, int);
int week_of_month(int, int, int);
int week_of_year(int, int, int);
int month_days(int, int);
int leap_years(int, int);
int year_isleap(int);
int date_isvalid(int, int, int);

/* ************************************************************************* */
/* Misc utilities                                                            */
/* ************************************************************************* */

#define ISNULL(ptr) ((ptr) == NULL)

#ifdef __GNUC__
#define MIN(a, b)               \
    __extension__               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })
#define MAX(a, b)               \
    __extension__               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })
#else
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

int rrand(int);

#endif /* UTILS_H */

