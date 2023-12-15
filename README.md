# nrf9160 Direct Access I2C example code.

This code demonstrates:

* I2C scanner (more or less ripped ad verbatim from the internet)
* Low level Chipcap2 I2C communication (from [Air Quality Sensor Node](https://github.com/lab5e/air-quality-sensor-node)
)

## Note:
* If you want to use i2c0,1,3, and the driver doesn't load, it is a good idea to check the various I2C nodes in the compiled dts (build/zephyr.dts). They will either be marked as "okay" or "disabled".
* The code is tested on nRF9160DK using nRF Connect SDK v.2.5.0 (SCL: 31, SDA:30).
* The example code is using i2c2, since this is enabled by default.
* Don't forget to add pullup resistors between the SDA/SCL and VDD (4.7k-10k).

# Example output

## I2C Scanner

```
*** Booting nRF Connect SDK v2.5.0 ***
The I2C scanner started 
Value of NRF_TWIM2->PSEL.SCL : -1  
Value of NRF_TWIM2->PSEL.SDA : -1 
Value of NRF_TWIM2->FREQUENCY: 67108864  
26738688 -> 100k 
I2C device found at address 0x28
``` 

## Chipcap2

```
*** Booting nRF Connect SDK v2.5.0 *** 

Sample : 0
Temp: 25.8
RH: 34

Sample : 1
Temp: 25.8
RH: 34

Sample : 2
Temp: 25.8
RH: 35
```
