#!/bin/sh

SOAPY_SDR_LOG_LEVEL=DEBUG SOAPY_SDR_PLUGIN_PATH=$PWD/build SoapySDRUtil --args=driver=filesdr --rate=1000000 --direction=RX --channels=0