# Soapy SDR module for file-base IQ sources

## Build

Follows standard `cmake` build process, as used by other Soapy modules.

```
git clone https://github.com/datashapesai/SoapyFileSDR.git
cd SoapyFileSDR
mkdir build
cd build
cmake ..
make
sudo make install
```

## Notes

Use `SOAPY_SDR_PLUGIN_PATH` to add to the module search path. See `poke.sh`, `test-io.sh` and `send-file.sh` for examples of use.

