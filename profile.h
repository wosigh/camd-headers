#ifndef _PROFILE_H_
#define _PROFILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ENABLE_PROFILING

#include <sys/time.h>
#include <time.h>

        int profile_register_event(const char *file, const char *func, int line,
                                   const char *call_str);
        void profile_pre_event(int id);
        void profile_post_event(int id);
        void profile_print_stats(int show_only_new);


/* for global non-scoped profiling */
#define PROF_EVENT_DECL_GLBL(n) extern int id_##n
#define PROF_EVENT_DEF_GLBL(n) int id_##n = -1
#define PROF_BEGIN(n) do { \
    if (id_##n == -1) \
        id_##n = profile_register_event(__FILE__, __FUNCTION__, __LINE__, #n); \
    profile_pre_event(id_##n); \
} while (0)

#define PROF_END(n) profile_post_event(id_##n)


/* for scoped profiling */
#define __PROF_EVENT_DEF(id) \
    static int id = -1

#define __PROF_SECT_BEGIN(id, desc) \
    if (id == -1) \
        id = profile_register_event(__FILE__, __FUNCTION__, __LINE__, desc); \
    profile_pre_event(id)

#define PROF_SECT_DECL_BEGIN(n) \
{ \
    __PROF_EVENT_DEF(id_##n); \
    __PROF_SECT_BEGIN(id_##n, #n)

#define PROF_SECT_END(n) \
    profile_post_event(id_##n); \
}

#define PROF_CALL(x) \
      do { \
          static int id = -1; \
          if (id == -1) \
              id = profile_register_event(__FILE__, __FUNCTION__, __LINE__, #x); \
          profile_pre_event(id); \
          x; \
          profile_post_event(id); \
      } while (0)

#else /* ENABLE_PROFILING */

#define PROF_EVENT_DEF_GLBL(n)
#define PROF_EVENT_DECL_GLBL(n)
#define PROF_BEGIN(n)
#define PROF_END(n)

#define PROF_CALL(x)  x
#define PROF_EVENT_DECL_GLBL(n)
#define PROF_SECT_DECL_BEGIN(n)
#define PROF_SECT_END(n)

#endif /* ENABLE_PROFILING */

#ifdef __cplusplus
}                               /* extern "C" */
#endif
#endif                          /* _PROFILE_H_ */
