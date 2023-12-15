/*
    Note:
        Chipcap2 application guide: https://www.cdiweb.com/datasheets/telaire-amphenol/chipcap2applicationnote.pdf
*/

#include <zephyr/kernel.h>
#include "chipcap2.h"
#include <stdio.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>

#define CC2_VALID_DATA (0x00)
#define CC2_STALE_DATA (0x01)


const struct device * get_I2C_device()
{
    const struct device *i2c_dev = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(i2c2)));
    int error;

    if (!i2c_dev) {
        printk("Binding to I2C device failed.");
        return NULL;
    }

    return i2c_dev;
}

int cc2_init()
{
    uint8_t NORMAL_OPERATION_MODE[] = {CHIPCAP2_NORMAL_OPERATION_MODE, 0, 0};
    return i2c_write(get_I2C_device(), NORMAL_OPERATION_MODE, 3, CHIPCAP2_ADDRESS);
}

static CC2_SAMPLE current;

void cc2_sample_data()
{
    struct device *i2c_device = get_I2C_device();
    uint8_t rxBuffer[] = {0, 0, 0, 0};
    int err = i2c_read(i2c_device, rxBuffer, 4, CHIPCAP2_ADDRESS);
    if (0 != err)
    {
        printk("Unable to get Chipcap2 sensor reading. i2c_read failed with error: %d", err);
        return;
    }

    // uint8_t status = rxBuffer[0] >> 6;
    float RH_H = (rxBuffer[0] & 0b00111111);
    float RH_L = rxBuffer[1];
    current.RH = ((RH_H * 256 + RH_L) / 16384) * 100;
    float TempC_H = rxBuffer[2];
    float TempC_L = rxBuffer[3] >> 4;
    current.Temp_C = ((TempC_H * 64 + TempC_L) / 16384) * 165 - 40;

    // Send a new measurement request after reading. Cannot be sent before first read
    //    uint8_t measurement_request = 1;

    err = i2c_write(i2c_device, NULL, 0, CHIPCAP2_ADDRESS);
    if (0 != err)
    {
        printk("Unable to send measurement request to Chipcap2 sensor. i2c_write failed with error: %d", err);
    }
}

void cc2_get_sample(CC2_SAMPLE *msg)
{
    memcpy(msg, &current, sizeof(current));
}