﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangsrs/YangSrsSdp.h>
#include <yangutil/sys/YangSsrc.h>
#include <yangutil/sys/YangMath.h>
#include <yangutil/sys/YangLog.h>
#include <yangutil/sys/YangCString.h>
#include <yangutil/sys/YangHttpSocket.h>
#include <yangsdp/YangRtcSdp.h>
#include <yangsdp/YangSdp.h>
#include <yangrtc/YangRtcSessionH.h>

#include <stdio.h>
#include <stdlib.h>
#define Yang_SDP_BUFFERLEN 1024*12

void yang_destroy_srsresponse(SrsSdpResponseType* srs){
	if(srs==NULL) return;
	yang_free(srs->sdp);
	yang_free(srs->serverIp);
	yang_free(srs->sessionid);
}

int32_t yang_sdp_querySrs(YangRtcSession* session,SrsSdpResponseType* srs,int32_t isplay,char* ip,int32_t port,char* purl, char* psdp)
{

	int32_t err=Yang_Ok;

	char* sdp=(char*)calloc(1,Yang_SDP_BUFFERLEN);
	if(yang_http_post(sdp,ip, port, purl, (uint8_t*)psdp, strlen(psdp))){
		yang_free(sdp);
		return yang_error_wrap(1,"query srs sdp failure!");
	}
	char* sBuffer=(char*)calloc(1,Yang_SDP_BUFFERLEN);

	yang_cstr_replace(sdp,sBuffer, "{", "");
	memset(sdp,0,Yang_SDP_BUFFERLEN);
	strcpy(sdp,sBuffer);
	memset(sBuffer,0,Yang_SDP_BUFFERLEN);
	yang_cstr_replace(sdp,sBuffer, "}", "");

	memset(sdp,0,Yang_SDP_BUFFERLEN);
	strcpy(sdp,sBuffer);
	memset(sBuffer,0,Yang_SDP_BUFFERLEN);
	yang_cstr_replace(sdp,sBuffer, "\\r\\n", "\n");

	YangStrings strs;
	memset(&strs,0,sizeof(YangStrings));
	yang_cstr_split(sBuffer, (char*)",",&strs);


	char* p=NULL;
	for (int32_t i = 0; i < strs.vsize; i++) {

		if ((p = strstr(strs.str[i], "\"code\":"))) {
			char *buf = (char*) calloc(1, strlen(p) + 1);
			yang_cstr_replace(p + strlen("\"code\":"), buf, "\"", "");
			srs->retcode = atoi(buf);
			yang_free(buf);
			if ((err = srs->retcode) != 0)	break;

			continue;
		}

		if ((p = strstr(strs.str[i], "\"server\":"))) {
			srs->serverIp = (char*) calloc(1, strlen(p) + 1);
			yang_cstr_replace(p + strlen("\"server\":"), srs->serverIp, "\"", "");

			continue;
		}

		if ((p = strstr(strs.str[i], "\"sessionid\":"))) {

			srs->sessionid = (char*) calloc(1, strlen(p) + 1);
			yang_cstr_replace(p + strlen("\"sessionid\":"), srs->sessionid, "\"","");

			continue;
		}

		if ((p = strstr(strs.str[i], "\"sdp\":"))) {
			srs->sdp = (char*) calloc(1, strlen(p) + 1);
			yang_cstr_replace(p + strlen("\"sdp\":"), srs->sdp, "\"", "");

			continue;
		}

	}



	yang_destroy_strings(&strs);
	yang_free(sdp);

	return err;

}

int32_t yang_srs_getSignal(YangRtcSession* session,SrsSdpResponseType* srs) {
	int32_t err = Yang_Ok;
	char *srsSdp = (char*)calloc(1,1024*12);
	char *tsdp=NULL;

	int32_t localport=session->context.streamConf->localPort;
	YangStreamOptType role=session->context.streamConf->streamOptType;
	yang_sdp_genLocalSdp(session,localport, &tsdp,role);

	char qt = '"';
	const char* roleStr=role==Yang_Stream_Play?"play":"publish";
	sprintf(srsSdp,
			"{%capi%c:%chttp://%s:%d/rtc/v1/%s/%c,%cstreamurl%c:%cwebrtc://%s:%d/%s/%s%c,%cclientip%c:null,%csdp%c:%c%s%c}",
			qt, qt, qt, session->context.streamConf->remoteIp, session->context.streamConf->remotePort,roleStr ,qt, qt, qt, qt, session->context.streamConf->remoteIp,
			session->context.streamConf->remotePort, session->context.streamConf->app, session->context.streamConf->stream, qt, qt, qt, qt, qt, qt, tsdp, qt);


	char apiurl[256] ;
	memset(apiurl,0,sizeof(apiurl));

	sprintf(apiurl, "rtc/v1/%s/", roleStr);
	err=yang_sdp_querySrs(session,srs,role==Yang_Stream_Play?1:0,(char*)session->context.streamConf->remoteIp,session->context.streamConf->remotePort,apiurl, srsSdp);


	yang_free(srsSdp);
	yang_free(tsdp);

	return err;
}
