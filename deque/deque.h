/*! 
 *  \brief     deque (Double-ended queue)
 *  \author    David Ranieri <davranfor@gmail.com>
 *  \copyright GNU Public License.
 */

#ifndef DEQUE_H
#define DEQUE_H

typedef struct deque deque;

deque *deque_create(void);
void *deque_push_head(deque *, void *);
void *deque_push_tail(deque *, void *);
void *deque_pop(deque *);
void *deque_fetch(const deque *, const void **);
void *deque_head(const deque *);
void *deque_tail(const deque *);
size_t deque_size(const deque *);
void deque_destroy(deque *, void (*)(void *));

#endif /* DEQUE_H */

