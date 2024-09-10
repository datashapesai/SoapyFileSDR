/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Charles J. Cliffe

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
#include <SoapySDR/Registry.hpp>
#include <mutex>
#include <map>

/// @brief  Find the FileSDR via identification of a config file.
static std::vector<SoapySDR::Kwargs> findFileSDR(const SoapySDR::Kwargs &args)
{
    std::vector<SoapySDR::Kwargs> results;

    std::string arg_str = SoapySDR::KwargsToString(args);

    SoapySDR_logf(SOAPY_SDR_DEBUG, "FileSDR inspecting %s", arg_str.c_str());

    SoapySDR::Kwargs devInfo;
    devInfo["label"] = "filesdr";
    results.push_back(devInfo);

    return results;
}

static SoapySDR::Device *makeFileSDR(const SoapySDR::Kwargs &args)
{
    return new SoapyFileSDR(args);
}

static SoapySDR::Registry registerRTLSDR("filesdr", &findFileSDR, &makeFileSDR, SOAPY_SDR_ABI_VERSION);
