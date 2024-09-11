#!/bin/sh

SOAPY_SDR_LOG_LEVEL=DEBUG SOAPY_SDR_PLUGIN_PATH=$PWD/build SoapySDRUtil --probe=driver=filesdr