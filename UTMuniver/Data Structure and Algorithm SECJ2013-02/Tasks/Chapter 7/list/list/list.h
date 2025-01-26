

#ifndef _list_h
#define _list_h

typedef struct list_head list_head;
typedef struct list_element list_element;

#include <stdlib.h>
#include <stddef.h>
#include <string.h>


#define list_type(type) \
   type *

#define list(type, name) \
   list_type (type) name 

#define list_push(list, value) do {                                           \
   typeof (*list) _v_copy = (typeof (*list)) value;                           \
   _list_push ((list_head **) &list, sizeof (_v_copy), &_v_copy);             \
} while (0)                                                                   \

#define list_push_front(list, value) do {                                     \
   typeof (*list) _v_copy = (typeof (*list)) value;                           \
   _list_push_front ((list_head **) &list, sizeof (_v_copy), &_v_copy);       \
} while (0)                                                                   \

#define list_elem(list)                                                       \
   typeof (list)

#define list_elem_front(list)                                                 \
   ((typeof (list)) _list_front ((list_head *) list))                         \

#define list_elem_back(list)                                                  \
   ((typeof (list)) _list_back ((list_head *) list))                          \

#define list_elem_next(elem)                                                  \
   ((typeof (elem)) _list_next ((list_element *) elem))                       \

#define list_elem_prev(elem)                                                  \
   ((typeof (elem)) _list_prev ((list_element *) elem))                       \

#define list_each_elem(list, e)                                               \
   for (typeof (list) e = list_elem_front (list),                             \
         e##_next = list_elem_next (e); e;                                    \
          e = e##_next, e##_next = list_elem_next (e))                        \

#define list_each_r_elem(list, e)                                             \
   for (typeof (list) e = list_elem_back (list),                              \
         e##_prev = list_elem_prev (e); e;                                    \
          e = e##_prev, e##_prev = list_elem_prev (e))                        \

#define list_each(list, e)                                                    \
   for (typeof (*list) e, * _##e = list_elem_front (list),                    \
        * _##e##_next = list_elem_next (_##e); _##e;                          \
          _##e = _##e##_next, _##e##_next = list_elem_next (_##e))            \
             if (!memcpy (&e, _##e, sizeof (e))) {} else                      \

#define list_each_r(list, e)                                                  \
   for (typeof (*list) e, * _##e = list_elem_back (list),                     \
        * _##e##_prev = list_elem_prev (_##e); _##e;                          \
          _##e = _##e##_prev, _##e##_prev = list_elem_prev (_##e))            \
             if (!memcpy (&e, _##e, sizeof (e))) {} else                      \

#ifndef _MSC_VER
   #define list_find(list, value) ({                                          \
      list_elem (list) elem = list_elem_front (list);                         \
      for (; elem; elem = list_elem_next (elem))                              \
         if (*elem == value)                                                  \
            break;                                                            \
      elem;                                                                   \
   })                                                                           
#else
   template <class T> inline T * list_find (T * list, T value)
   {
      list_elem (list) elem = list_elem_front (list);
      for (; elem; elem = list_elem_next (elem))    
         if (*elem == value)                       
            return elem;
      return 0;
   }
#endif

#define list_remove(list, value)                                              \
   list_elem_remove (list_find (list, value))                                 \

#define list_elem_remove(elem)                                                \
   _list_remove ((list_element *) elem)                                       \

#define list_length(list)                                                     \
   _list_length ((list_head *) (list))                                        \

#define list_clear(list)                                                      \
   _list_clear ((list_head **) &(list), sizeof (*list))                       \

#define list_front(list)                                                      \
   (*list_elem_front (list))                                                  \

#define list_back(list)                                                       \
   (*list_elem_back (list))                                                   \

#define list_pop_front(list)                                                  \
   list_elem_remove (list_elem_front (list))                                  \

#define list_pop_back(list)                                                   \
   list_elem_remove (list_elem_back (list))                                   \

#ifdef __cplusplus
   extern "C"
   {
#endif

void          _list_push        (list_head **, size_t value_size, void * value);
void          _list_push_front  (list_head **, size_t value_size, void * value);
list_element* _list_front       (list_head *);
list_element* _list_back        (list_head *);
list_element* _list_next        (list_element *);
list_element* _list_prev        (list_element *);
size_t        _list_length      (list_head *);
void          _list_remove      (list_element *);
void          _list_clear       (list_head **, size_t value_size);

#ifdef __cplusplus
   }
#endif

#endif

