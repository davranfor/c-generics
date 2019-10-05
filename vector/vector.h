/*! 
 *  \brief     Vector
 *  \author    David Ranieri <davranfor@gmail.com>
 *  \copyright GNU Public License.
 */

#ifndef VECTOR_H
#define VECTOR_H

void *vector_create(size_t, void (*)(void *));
void *vector_resize(void *, int);
void *vector_concat(void *, const void *, size_t);
size_t vector_size(const void *);
void vector_sort(void *, int (*)(const void *, const void *));
void *vector_search(const void *, const void *, int (*)(const void *, const void *));
void *vector_clear(void *);
void vector_destroy(void *);

#endif /* VECTOR_H */

