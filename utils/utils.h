#ifndef UTILS_H
#define UTILS_H

/* File utilities */

#define FILE_TRUNCATE 0
#define FILE_APPEND 1

#define FILE_WRITE_ERROR ((size_t)-1)

long file_get_size(const char *);
char *file_read(const char *);
size_t file_write(const char *, const char *, int);
char *file_get_line(FILE *);

/* String utilities */
char *string_clone(const char *);
char *string_slice(const char *, size_t, size_t);
char *string_print(const char *, ...);
char *string_trim(const char *);
char *string_ltrim(const char *);
char *string_rtrim(const char *);

#endif /* UTILS_H */

