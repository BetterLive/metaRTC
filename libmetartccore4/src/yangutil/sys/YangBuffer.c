﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#include <yangutil/buffer/YangCBuffer.h>
#include <stdio.h>
#include <string.h>


void yang_init_buffer(YangBuffer* buf,char* b, int32_t nn){
	  buf->head = buf->data = b;
	    buf->size = nn;
}
void yang_destroy_buffer(YangBuffer* buf){

}
int32_t yang_buffer_pos(YangBuffer* buf)
{
    return (int)(buf->head - buf->data);
}

int32_t yang_buffer_left(YangBuffer* buf)
{
    return buf->size - (int)(buf->head - buf->data);
}

int32_t yang_buffer_empty(YangBuffer* buf)
{
    return !buf->data || (buf->head >= buf->data + buf->size);
}

int32_t yang_buffer_require(YangBuffer* buf,int32_t required_size)
{
    if (required_size < 0) {
        return 0;
    }

    return required_size <= buf->size - (buf->head - buf->data);
}

void yang_buffer_skip(YangBuffer* buf,int32_t size)
{
   if(buf==NULL) return;

    buf->head += size;
}

char yang_read_1bytes(YangBuffer* buf)
{
   // //yang_assert(require(1));
	//require(1);
    return *buf->head++;
}

int16_t yang_read_2bytes(YangBuffer* buf)
{
   // //yang_assert(require(2));

    int16_t value;
    char* pp = (char*)&value;
    pp[1] = *buf->head++;
    pp[0] = *buf->head++;

    return value;
}

int16_t yang_read_le2bytes(YangBuffer* buf)
{
    ////yang_assert(require(2));

    int16_t value;
    char* pp = (char*)&value;
    pp[0] = *buf->head++;
    pp[1] = *buf->head++;

    return value;
}

int32_t yang_read_3bytes(YangBuffer* buf)
{
   // //yang_assert(require(3));

    int32_t value = 0x00;
    char* pp = (char*)&value;
    pp[2] = *buf->head++;
    pp[1] = *buf->head++;
    pp[0] = *buf->head++;

    return value;
}

int32_t yang_read_le3bytes(YangBuffer* buf)
{
    ////yang_assert(require(3));

    int32_t value = 0x00;
    char* pp = (char*)&value;
    pp[0] = *buf->head++;
    pp[1] = *buf->head++;
    pp[2] = *buf->head++;

    return value;
}

int32_t yang_read_4bytes(YangBuffer* buf)
{
    ////yang_assert(require(4));

    int32_t value;
    char* pp = (char*)&value;
    pp[3] = *buf->head++;
    pp[2] = *buf->head++;
    pp[1] = *buf->head++;
    pp[0] = *buf->head++;

    return value;
}

int32_t yang_read_le4bytes(YangBuffer* buf)
{
    ////yang_assert(require(4));

    int32_t value;
    char* pp = (char*)&value;
    pp[0] = *buf->head++;
    pp[1] = *buf->head++;
    pp[2] = *buf->head++;
    pp[3] = *buf->head++;

    return value;
}

int64_t yang_read_8bytes(YangBuffer* buf)
{
   // //yang_assert(require(8));

    int64_t value;
    char* pp = (char*)&value;
    pp[7] = *buf->head++;
    pp[6] = *buf->head++;
    pp[5] = *buf->head++;
    pp[4] = *buf->head++;
    pp[3] = *buf->head++;
    pp[2] = *buf->head++;
    pp[1] = *buf->head++;
    pp[0] = *buf->head++;

    return value;
}

int64_t yang_read_le8bytes(YangBuffer* buf)
{
    ////yang_assert(require(8));

    int64_t value;
    char* pp = (char*)&value;
    pp[0] = *buf->head++;
    pp[1] = *buf->head++;
    pp[2] = *buf->head++;
    pp[3] = *buf->head++;
    pp[4] = *buf->head++;
    pp[5] = *buf->head++;
    pp[6] = *buf->head++;
    pp[7] = *buf->head++;

    return value;
}



void yang_read_bytes(YangBuffer* buf,char* data, int32_t size)
{
    //yang_assert(require(size));

    memcpy(data, buf->head, size);

    buf->head += size;
}

void yang_write_1bytes(YangBuffer* buf,char value)
{
    //yang_assert(require(1));

    *buf->head++ = value;
}

void yang_write_2bytes(YangBuffer* buf,int16_t value)
{
    //yang_assert(require(2));

    char* pp = (char*)&value;
    *buf->head++ = pp[1];
    *buf->head++ = pp[0];
}

void yang_write_le2bytes(YangBuffer* buf,int16_t value)
{
    //yang_assert(require(2));

    char* pp = (char*)&value;
    *buf->head++ = pp[0];
    *buf->head++ = pp[1];
}

void yang_write_4bytes(YangBuffer* buf,int32_t value)
{
    //yang_assert(require(4));

    char* pp = (char*)&value;
    *buf->head++ = pp[3];
    *buf->head++ = pp[2];
    *buf->head++ = pp[1];
    *buf->head++ = pp[0];
}

void yang_write_le4bytes(YangBuffer* buf,int32_t value)
{
    //yang_assert(require(4));

    char* pp = (char*)&value;
    *buf->head++ = pp[0];
    *buf->head++ = pp[1];
    *buf->head++ = pp[2];
    *buf->head++ = pp[3];
}

void yang_write_3bytes(YangBuffer* buf,int32_t value)
{
    //yang_assert(require(3));

    char* pp = (char*)&value;
    *buf->head++ = pp[2];
    *buf->head++ = pp[1];
    *buf->head++ = pp[0];
}

void yang_write_le3bytes(YangBuffer* buf,int32_t value)
{
    //yang_assert(require(3));

    char* pp = (char*)&value;
    *buf->head++ = pp[0];
    *buf->head++ = pp[1];
    *buf->head++ = pp[2];
}

void yang_write_8bytes(YangBuffer* buf,int64_t value)
{
    //yang_assert(require(8));

    char* pp = (char*)&value;
    *buf->head++ = pp[7];
    *buf->head++ = pp[6];
    *buf->head++ = pp[5];
    *buf->head++ = pp[4];
    *buf->head++ = pp[3];
    *buf->head++ = pp[2];
    *buf->head++ = pp[1];
    *buf->head++ = pp[0];
}

void yang_write_le8bytes(YangBuffer* buf,int64_t value)
{
    //yang_assert(require(8));

    char* pp = (char*)&value;
    *buf->head++ = pp[0];
    *buf->head++ = pp[1];
    *buf->head++ = pp[2];
    *buf->head++ = pp[3];
    *buf->head++ = pp[4];
    *buf->head++ = pp[5];
    *buf->head++ = pp[6];
    *buf->head++ = pp[7];
}


void yang_write_bytes(YangBuffer* buf,char* data, int32_t size)
{
    //yang_assert(require(size));

    memcpy(buf->head, data, size);
    buf->head += size;
}
void yang_write_cstring(YangBuffer* buf,char* data)
{
    //yang_assert(require(size));
	int32_t datasize=strlen(data);
    memcpy(buf->head, data, datasize);
    buf->head += datasize;
}
