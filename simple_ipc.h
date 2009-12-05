#ifndef _SIMPLE_IPC_H_
#define _SIMPLE_IPC_H_

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAMD_ON_DEMAND
#define CAMD_IPC_ADDR "camd.ipc"

        typedef enum {
                SIPC_MODE_SERVER = 0,
                SIPC_MODE_CLIENT,
        } sipc_mode_t;

        void *sipc_create(void);
        int sipc_init(void *h, sipc_mode_t mode, const char *addr);
        int sipc_uninit(void *addr);
        int sipc_server_accept(void *h);

        /* tries to connect w/timeout seconds
         * timeout = 0 : no timeout
         * timeout = -1 : default (set internally)
         */
        int sipc_client_connect_timeout(void *h, int timeout_sec);
        int sipc_disconnect(void *h);
        size_t sipc_read(void *h, char *buf, size_t n);
        size_t sipc_write(void *h, char *buf, size_t n);
        int sipc_get_connection_fd(void *h);
        int sipc_server_get_accept_fd(void *h);
        const char *sipc_get_err_str(void *h);

#ifdef __cplusplus
}
#endif
#endif