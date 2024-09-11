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
#include <algorithm>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


SoapyFileSDR::SoapyFileSDR(const SoapySDR::Kwargs &args) : fifo_path("/tmp/file_sdr"),
                                                           input_fd(-1),
                                                           sampleRate(0),
                                                           centerFrequency(0),
                                                           bufferLength(DEFAULT_BUFFER_LENGTH)

{
    for (const auto &arg : args)
    {
        if (arg.first == "fifo")
        {
            this->writeSetting(arg.first, arg.second);
        }
    }
    SoapySDR_logf(SOAPY_SDR_DEBUG, "FileSDR opening named pipe at %s", fifo_path.c_str());
}

SoapyFileSDR::~SoapyFileSDR(void)
{
    if (this->input_fd > 0) {
        close(this->input_fd);
        this->input_fd = -1;
    }
}

/*******************************************************************
 * Identification API
 ******************************************************************/

std::string SoapyFileSDR::getDriverKey(void) const
{
    return "filesdr";
}

std::string SoapyFileSDR::getHardwareKey(void) const
{
    return "fifo";
}

SoapySDR::Kwargs SoapyFileSDR::getHardwareInfo(void) const
{
    // key/value pairs for any useful information
    // this also gets printed in --probe
    SoapySDR::Kwargs args;

    args["origin"] = "https://github.com/datashapesai/SoapyFileSDR";
    args["fifo"] = fifo_path;

    return args;
}

/*******************************************************************
 * Channels API
 ******************************************************************/

size_t SoapyFileSDR::getNumChannels(const int dir) const
{
    return (dir == SOAPY_SDR_RX) ? 1 : 0;
}

bool SoapyFileSDR::getFullDuplex(const int direction, const size_t channel) const
{
    return false;
}

/*******************************************************************
 * Frequency API
 ******************************************************************/

void SoapyFileSDR::setFrequency(
    const int direction,
    const size_t channel,
    const std::string &name,
    const double frequency,
    const SoapySDR::Kwargs &args)
{
    if (name == "RF" || name == "")
    {
        SoapySDR_logf(SOAPY_SDR_DEBUG, "Setting center freq: %d", (uint32_t)frequency);
        centerFrequency = frequency;
    }
}

double SoapyFileSDR::getFrequency(const int direction, const size_t channel, const std::string &name) const
{
    if (name == "RF" || name == "")
    {
        return (double)centerFrequency;
    }
    return 0;
}

std::vector<std::string> SoapyFileSDR::listFrequencies(const int direction, const size_t channel) const
{
    std::vector<std::string> names;
    names.push_back("RF");
    return names;
}

SoapySDR::RangeList SoapyFileSDR::getFrequencyRange(
    const int direction,
    const size_t channel,
    const std::string &name) const
{
    SoapySDR::RangeList results;
    //    results.push_back(SoapySDR::Range(0, MAX_FREQUENCY));
    return results;
}

SoapySDR::ArgInfoList SoapyFileSDR::getFrequencyArgsInfo(const int direction, const size_t channel) const
{
    SoapySDR::ArgInfoList freqArgs;
    return freqArgs;
}

/*******************************************************************
 * Sample Rate API
 ******************************************************************/

void SoapyFileSDR::setSampleRate(const int direction, const size_t channel, const double rate)
{
    sampleRate = rate;
    SoapySDR_logf(SOAPY_SDR_DEBUG, "Setting sample rate: %d", sampleRate);
}

double SoapyFileSDR::getSampleRate(const int direction, const size_t channel) const
{
    return sampleRate;
}

std::vector<double> SoapyFileSDR::listSampleRates(const int direction, const size_t channel) const
{
    std::vector<double> results;
    return results;
}

SoapySDR::RangeList SoapyFileSDR::getSampleRateRange(const int direction, const size_t channel) const
{
    SoapySDR::RangeList results;
    return results;
}

/*******************************************************************
 * Settings API
 ******************************************************************/

SoapySDR::ArgInfoList SoapyFileSDR::getSettingInfo(void) const
{
    SoapySDR::ArgInfoList setArgs;

    SoapySDR::ArgInfo input;
    input.key = "fifo";
    input.value = "/tmp/file_sdr";
    input.name = "Named pipe";
    input.description = "Path the named pipe created by `mkfifo` accepting cf32_le bytes.";
    input.type = SoapySDR::ArgInfo::STRING;

    setArgs.push_back(input);

    return setArgs;
}

void SoapyFileSDR::writeSetting(const std::string &key, const std::string &value)
{
    if (key == "fifo")
    {
        fifo_path = value;
        SoapySDR_logf(SOAPY_SDR_DEBUG, "FileSDR input fifo path: %s", fifo_path.c_str());
    }
    else
    {
        SoapySDR_logf(SOAPY_SDR_WARNING, "Unknown setting '%s'", key.c_str());
    }
}

std::string SoapyFileSDR::readSetting(const std::string &key) const
{
    if (key == "fifo")
    {
        return fifo_path;
    }
    else
    {
        SoapySDR_logf(SOAPY_SDR_WARNING, "Unknown setting '%s'", key.c_str());
    }
    return "";
}
