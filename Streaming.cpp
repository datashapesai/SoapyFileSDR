/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Charles J. Cliffe
 * Copyright (c) 2015-2017 Josh Blum

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "SoapyFileSDR.hpp"
#include <SoapySDR/Logger.hpp>
#include <SoapySDR/Formats.hpp>
#include <SoapySDR/Time.hpp>
#include <algorithm> //min
#include <climits> //SHRT_MAX
#include <cstring> // memcpy


std::vector<std::string> SoapyFileSDR::getStreamFormats(const int direction, const size_t channel) const {
    std::vector<std::string> formats;
    formats.push_back(SOAPY_SDR_CF32);
    return formats;
}

std::string SoapyFileSDR::getNativeStreamFormat(const int direction, const size_t channel, double &fullScale) const {
    //check that direction is SOAPY_SDR_RX
     if (direction != SOAPY_SDR_RX) {
         throw std::runtime_error("FileSDR is RX only, use SOAPY_SDR_RX");
     }

     fullScale = uint32_t(1<<31);
     return SOAPY_SDR_CF32;
}

SoapySDR::ArgInfoList SoapyFileSDR::getStreamArgsInfo(const int direction, const size_t channel) const {
    //check that direction is SOAPY_SDR_RX
     if (direction != SOAPY_SDR_RX) {
         throw std::runtime_error("FileSDR is RX only, use SOAPY_SDR_RX");
     }

    SoapySDR::ArgInfoList streamArgs;
    return streamArgs;
}

/*******************************************************************
 * Stream API
 ******************************************************************/

SoapySDR::Stream *SoapyFileSDR::setupStream(
        const int direction,
        const std::string &format,
        const std::vector<size_t> &channels,
        const SoapySDR::Kwargs &args)
{
    if (direction != SOAPY_SDR_RX)
    {
        throw std::runtime_error("FileSDR is RX only, use SOAPY_SDR_RX");
    }

    //check the channel configuration
    if (channels.size() > 1 or (channels.size() > 0 and channels.at(0) != 0))
    {
        throw std::runtime_error("setupStream invalid channel selection");
    }

    //check the format
    if (format == SOAPY_SDR_CF32)
    {
        SoapySDR_log(SOAPY_SDR_INFO, "Using format CF32.");
    }
    else
    {
        throw std::runtime_error(
                "setupStream invalid format '" + format
                        + "' -- Only CF32 is supported by SoapyFileSDR module.");
    }

    return (SoapySDR::Stream *) this;
}

void SoapyFileSDR::closeStream(SoapySDR::Stream *stream)
{
    this->deactivateStream(stream, 0, 0);
}

size_t SoapyFileSDR::getStreamMTU(SoapySDR::Stream *stream) const
{
    return  bufferLength / BYTES_PER_SAMPLE;
}

int SoapyFileSDR::activateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs,
        const size_t numElems)
{
    if (flags != 0) return SOAPY_SDR_NOT_SUPPORTED;
    return 0;
}

int SoapyFileSDR::deactivateStream(SoapySDR::Stream *stream, const int flags, const long long timeNs)
{
    if (flags != 0) return SOAPY_SDR_NOT_SUPPORTED;
    return 0;
}

int SoapyFileSDR::readStream(
        SoapySDR::Stream *stream,
        void * const *buffs,
        const size_t numElems,
        int &flags,
        long long &timeNs,
        const long timeoutUs)
{
    return 0;
}
