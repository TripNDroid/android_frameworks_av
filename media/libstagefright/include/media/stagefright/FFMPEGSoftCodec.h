/*
 * Copyright (C) 2014 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FFMPEG_SOFT_CODEC_H_
#define FFMPEG_SOFT_CODEC_H_

#include <cutils/properties.h>

#include <utils/Log.h>

#include <media/stagefright/foundation/AMessage.h>

#include <media/stagefright/DataSource.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/ExtendedMediaDefs.h>

#include <media/IOMX.h>
#include <media/MediaDefs.h>
#include <media/MediaCodecInfo.h>

#include "../../libavextensions/stagefright/AVExtensions.h"

#include <dlfcn.h>

namespace android {

struct FFMPEGSoftCodec {

    enum {
        kPortIndexInput  = 0,
        kPortIndexOutput = 1
    };

    typedef MediaExtractor *(*CreateExtractorFunc)(const sp<DataSource> &source,
            const char *mime, const sp<AMessage> &meta);

    static void convertMessageToMetaDataFF(
            const sp<AMessage> &msg, sp<MetaData> &meta);

    static void convertMetaDataToMessageFF(
        const sp<MetaData> &meta, sp<AMessage> *format);

    static const char* overrideComponentName(
            uint32_t quirks, const sp<MetaData> &meta,
            const char *mime, bool isEncoder);

    static void overrideComponentName(
            uint32_t quirks, const sp<AMessage> &msg,
            AString* componentName, AString* mime,
            int32_t isEncoder);

    static const char* getComponentRole(
            bool isEncoder, const char *mime);

    static status_t setAudioFormat(
            const sp<AMessage> &msg, const char* mime,
            sp<IOMXNode> OMXhandle);

    static status_t setVideoFormat(
            status_t status,
            const sp<AMessage> &msg, const char* mime,
            sp<IOMXNode> OMXhandle,
            bool isEncoder, OMX_VIDEO_CODINGTYPE *compressionFormat,
            const char* componentName);

    static status_t getAudioPortFormat(
            OMX_U32 portIndex, int coding,
            sp<AMessage> &notify, sp<IOMXNode> OMXhandle);

    static status_t getVideoPortFormat(
            OMX_U32 portIndex, int coding,
            sp<AMessage> &notify, sp<IOMXNode> OMXhandle);

    static MediaExtractor::SnifferFunc getSniffer();

    static MediaExtractor* createExtractor(const sp<DataSource> &source,
            const char *mime, const sp<AMessage> &meta);

    static AudioEncoding bitsToAudioEncoding(int32_t bits) {
        switch (bits) {
            case 8:
                return kAudioEncodingPcm8bit;
            case 16:
                return kAudioEncodingPcm16bit;
            case 24:
                return kAudioEncodingPcm32bit;
            case 32:
                return kAudioEncodingPcmFloat;
        }
        return kAudioEncodingInvalid;
    }

    static int32_t audioEncodingToBits(AudioEncoding encoding) {
        switch (encoding) {
            case kAudioEncodingInvalid:
                return 0;
            case kAudioEncodingPcm8bit:
                return 8;
            case kAudioEncodingPcm16bit:
                return 16;
            case kAudioEncodingPcm24bitPacked:
            case kAudioEncodingPcm32bit:
                return 24;
            case kAudioEncodingPcmFloat:
                return 32;
        }
        return 0;
    }

private:
    static const char* getMsgKey(int key);

    static status_t setWMVFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setRVFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setFFmpegVideoFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setRawAudioFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setWMAFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setVORBISFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setRAFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setFLACFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setMP2Format(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setAC3Format(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setALACFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setAPEFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setDTSFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

    static status_t setFFmpegAudioFormat(
            const sp<AMessage> &msg, sp<IOMXNode> OMXhandle);

#ifdef QCOM_HARDWARE
    static status_t setQCDIVXFormat(
            const sp<AMessage> &msg, const char* mime,
            sp<IOMXNode> OMXhandle, int port_index);
#endif

    static void loadPlugin();

    static void* sLibHandle;
    static MediaExtractor::SnifferFunc sSnifferFunc;
    static CreateExtractorFunc sExtractorFunc;
};

}
#endif