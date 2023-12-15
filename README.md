# nrf9160 Direct Access I2C example code.

This code demonstrates:

* I2C scanner (more or less ripped ad verbatim from the internet)
* Low level Chipcap2 I2C communication (from [Air Quality Sensor Node](https://github.com/lab5e/air-quality-sensor-node)
)

## Note:
* The example code is using i2c2, since this is enabled by default in nRF Connect SDK v.2.5.0 (SCL: 31, SDA:30)
* If you want to use i2c0,1,3, and the driver doesn't load, it is a good idea to check the various I2C nodes in the compiled dts (build/zephyr.dts). They will either be marked as "okay" or "disabled".
