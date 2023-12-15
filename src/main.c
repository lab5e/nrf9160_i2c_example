/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr/kernel.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include "chipcap2.h"

#define TEST_BUF_SIZE 128

void scan_i2c_bus()
{
    printk("The I2C scanner started\n");
    const struct device *i2c_dev = device_get_binding(DEVICE_DT_NAME(DT_NODELABEL(i2c2)));
    int error;

    if (!i2c_dev) {
        printk("Binding failed.");
        return;
    }

    /* Demonstration of runtime configuration */
    i2c_configure(i2c_dev, I2C_SPEED_SET(I2C_SPEED_STANDARD));
    printk("Value of NRF_TWIM2->PSEL.SCL : %d \n",NRF_TWIM1->PSEL.SCL);
    printk("Value of NRF_TWIM2->PSEL.SDA : %d \n",NRF_TWIM1->PSEL.SDA);
    printk("Value of NRF_TWIM2->FREQUENCY: %d \n",NRF_TWIM1->FREQUENCY);
    printk("26738688 -> 100k\n");

    for (uint8_t i = 4; i <= 0x7F; i++) {
        struct i2c_msg msgs[1];
        uint8_t dst = 1;

        msgs[0].buf = &dst;
        msgs[0].len = 1U;
        msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

        error = i2c_transfer(i2c_dev, &msgs[0], 1, i);
        if (error == 0) {
            printk("I2C device found at address 0x%2x\n", i);
        }
    }
}


void read_chipcap2_data()
{
    CC2_SAMPLE sample;

    cc2_init();
    for (int i=0; i<20; i++)
    {
        cc2_sample_data();
        cc2_get_sample(&sample);

        printk("Sample : %d\n", i);
        printk("Temp: %2.1f\n", sample.Temp_C);
        printk("RH: %2.0f\n\n", sample.RH);
        k_sleep(K_MSEC(1000));
    }
    
}

int main(void)
{
    scan_i2c_bus();
    // read_chipcap2_data();
    return 0; 
}