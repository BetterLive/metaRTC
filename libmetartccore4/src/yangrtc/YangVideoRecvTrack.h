﻿
//
// Copyright (c) 2019-2022 yanggaofeng
//
#ifndef SRC_YANGWEBRTC_YANGRTCVIDEORECVTRACK1_H_
#define SRC_YANGWEBRTC_YANGRTCVIDEORECVTRACK1_H_

#include <yangrtc/YangRecvTrack.h>

#ifdef __cplusplus
extern "C"{
#endif

void yang_create_recvvideoTrack(YangRtcContext* context,YangVideoRecvTrack* videorecv);
void yang_destroy_recvvideoTrack(YangVideoRecvTrack* videorecv);
int32_t yang_recvvideoTrack_on_rtp(YangRtcContext* context,YangVideoRecvTrack* videorecv,YangRtpPacket *pkt);
int32_t yang_recvvideoTrack_check_send_nacks(YangRtcContext* context,YangVideoRecvTrack* videorecv);

#ifdef __cplusplus
}
#endif


#endif /* SRC_YANGWEBRTC_YANGRTCVIDEORECVTRACK_H_ */
