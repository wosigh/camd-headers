#ifndef _CAM_MSG_H_
#define _CAM_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

        /* N = Notification
         * Q = Query
         */
        typedef enum {
                CAMD_MSG_ID_N_ILLEGAL = 0,
                CAMD_MSG_ID_N_POWER,
                CAMD_MSG_ID_N_PREVIEW,
                CAMD_MSG_ID_N_FLASH,
                CAMD_MSG_ID_N_PRE_STILL,
                CAMD_MSG_ID_N_STILL_CAPTURE,
                CAMD_MSG_ID_N_POST_STILL_DBG,
                CAMD_MSG_ID_N_VIDEO_CAPTURE,
                CAMD_MSG_ID_N_TORCH_CURRENT,
                CAMD_MSG_ID_N_STROBE_CURRENT,
                CAMD_MSG_ID_Q_IS_PREFLASH_OK,
                CAMD_MSG_ID_ABORT,
                CAMD_MSG_ID_LAST,
        } camd_msg_id_t;

        typedef enum {
                CAMD_MSG_ARG_ILLEGAL = 0,
                CAMD_MSG_ARG_STATE_OFF,
                CAMD_MSG_ARG_STATE_ON,
                CAMD_MSG_ARG_STATE_AUTO,
                CAMD_MSG_ARG_NONE,
                CAMD_MSG_ARG_LAST
        } camd_msg_arg_t;

        typedef enum {
                CAMD_MSG_ACK_UNUSED = 0,
                CAMD_MSG_ACK_REQUEST,
                CAMD_MSG_ACK_REPLY,
                CAMD_MSG_ACK_LAST,
        } camd_msg_ack_t;

        typedef struct {
                camd_msg_id_t id;
                camd_msg_arg_t arg;
                camd_msg_ack_t ack;
                int payload_size;
        } camd_msg_packet_data_t;

        typedef struct {
                camd_msg_packet_data_t ph; /* for packet header */
                void *payload;
                int refcount;
        } camd_msg_packet_t;

        typedef struct {
                // 0 = numerator
                // 1 = denominator
                unsigned int exposure_time[2];
        } camd_msg_post_still_data_t;

        void *camd_msg_init(void *h_sipc);
        void camd_msg_uninit(void *h);

        /* msg packet API */
        void camd_msg_packet_init(camd_msg_packet_t *p);
        void camd_msg_packet_refcount_inc(camd_msg_packet_t *p);
        void camd_msg_packet_refcount_dec(camd_msg_packet_t *p);
        int camd_msg_packet_refcount_get(camd_msg_packet_t *p);

        /* write */
        int camd_msg_packet_write_header(void *h, camd_msg_packet_t * p);
        int camd_msg_packet_write(void *h, camd_msg_packet_t *p);
        int camd_msg_packet_write_wait_ack(void *h, camd_msg_packet_t * p);
        int camd_msg_packet_write_ack(void *h, camd_msg_packet_t *p,
                        void *payload, int payload_size);
       
        /* read */
        int camd_msg_packet_read_header(void *h, camd_msg_packet_t * p);
        int camd_msg_packet_read_payload(void *h, camd_msg_packet_t *p,
                        void *payload_container, int payload_container_size);

        /* combined write msg + read reply + read payload */
        int camd_msg_request_data(void *h, camd_msg_id_t id, camd_msg_arg_t arg,
                        void *data, int size);

        /* if an error occured, call this to get the err desc str */
        const char *camd_msg_get_err_str(void *h);

#ifdef DEBUG
        const char *camd_msg_id2str(void *h, camd_msg_id_t id);
        const char *camd_msg_arg2str(void *h, camd_msg_arg_t arg);
        void camd_msg_contents_disp(void *h, camd_msg_packet_t * m);

        typedef struct {
        } camd_msg_post_still_dbg_data_t;
#endif
#ifdef __cplusplus
}                               /* extern "C" */
#endif
#endif                          /* _CAM_MSG_H_ */
 