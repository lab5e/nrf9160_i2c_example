#pragma once
#include <stdint.h>

typedef struct
{
    float RH;
    float Temp_C;
} CC2_SAMPLE;

#define CHIPCAP2_ADDRESS 0x28

#define CHIPCAP2_NORMAL_OPERATION_MODE 0x80

int cc2_init();
void cc2_sample_data();
void cc2_get_sample(CC2_SAMPLE *msg);