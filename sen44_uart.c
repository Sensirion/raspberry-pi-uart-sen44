/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * SHDLC-Generator: 0.8.2
 * Yaml Version: 0.1.0
 * Template Version: 0.7.0
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "sen44_uart.h"
#include "sensirion_common.h"
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"

#define SEN44_UART_ADDRESS 0x00

int16_t sen44_start_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x00, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x02);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t sen44_stop_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x01, SEN44_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(120000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t sen44_read_data_ready(bool* data_ready) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[14];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x02, SEN44_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(5000);

    error = sensirion_shdlc_rx_inplace(&frame, 1, &header);
    if (error) {
        return error;
    }
    *data_ready = buffer[0];
    return NO_ERROR;
}

int16_t sen44_read_measured_pm_values(
    uint16_t* mass_concentration_pm1p0, uint16_t* mass_concentration_pm2p5,
    uint16_t* mass_concentration_pm4p0, uint16_t* mass_concentration_pm10p0,
    uint16_t* number_concentration_pm0p5, uint16_t* number_concentration_pm1p0,
    uint16_t* number_concentration_pm2p5, uint16_t* number_concentration_pm4p0,
    uint16_t* number_concentration_pm10p0, uint16_t* typical_particle_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[52];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x05);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 20, &header);
    if (error) {
        return error;
    }
    *mass_concentration_pm1p0 = sensirion_common_bytes_to_uint16_t(&buffer[0]);
    *mass_concentration_pm2p5 = sensirion_common_bytes_to_uint16_t(&buffer[2]);
    *mass_concentration_pm4p0 = sensirion_common_bytes_to_uint16_t(&buffer[4]);
    *mass_concentration_pm10p0 = sensirion_common_bytes_to_uint16_t(&buffer[6]);
    *number_concentration_pm0p5 =
        sensirion_common_bytes_to_uint16_t(&buffer[8]);
    *number_concentration_pm1p0 =
        sensirion_common_bytes_to_uint16_t(&buffer[10]);
    *number_concentration_pm2p5 =
        sensirion_common_bytes_to_uint16_t(&buffer[12]);
    *number_concentration_pm4p0 =
        sensirion_common_bytes_to_uint16_t(&buffer[14]);
    *number_concentration_pm10p0 =
        sensirion_common_bytes_to_uint16_t(&buffer[16]);
    *typical_particle_size = sensirion_common_bytes_to_uint16_t(&buffer[18]);
    return NO_ERROR;
}

int16_t sen44_read_measured_mass_concentration_and_ambient_values_ticks(
    uint16_t* mass_concentration_pm1p0, uint16_t* mass_concentration_pm2p5,
    uint16_t* mass_concentration_pm4p0, uint16_t* mass_concentration_pm10p0,
    int16_t* voc_index, int16_t* ambient_humidity,
    int16_t* ambient_temperature) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[40];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x07);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 14, &header);
    if (error) {
        return error;
    }
    *mass_concentration_pm1p0 = sensirion_common_bytes_to_uint16_t(&buffer[0]);
    *mass_concentration_pm2p5 = sensirion_common_bytes_to_uint16_t(&buffer[2]);
    *mass_concentration_pm4p0 = sensirion_common_bytes_to_uint16_t(&buffer[4]);
    *mass_concentration_pm10p0 = sensirion_common_bytes_to_uint16_t(&buffer[6]);
    *voc_index = sensirion_common_bytes_to_int16_t(&buffer[8]);
    *ambient_humidity = sensirion_common_bytes_to_int16_t(&buffer[10]);
    *ambient_temperature = sensirion_common_bytes_to_int16_t(&buffer[12]);
    return NO_ERROR;
}

int16_t sen44_read_measured_mass_concentration_and_ambient_values(
    uint16_t* mass_concentration_pm1p0, uint16_t* mass_concentration_pm2p5,
    uint16_t* mass_concentration_pm4p0, uint16_t* mass_concentration_pm10p0,
    float* voc_index, float* ambient_humidity, float* ambient_temperature) {
    int16_t error = 0;
    int16_t voc_index_ticks;
    int16_t ambient_humidity_ticks;
    int16_t ambient_temperature_ticks;

    error = sen44_read_measured_mass_concentration_and_ambient_values_ticks(
        mass_concentration_pm1p0, mass_concentration_pm2p5,
        mass_concentration_pm4p0, mass_concentration_pm10p0, &voc_index_ticks,
        &ambient_humidity_ticks, &ambient_temperature_ticks);
    if (error) {
        return error;
    }

    *voc_index = (float)voc_index_ticks / 10.0f;
    *ambient_humidity = (float)ambient_humidity_ticks / 100.0f;
    *ambient_temperature = (float)ambient_temperature_ticks / 200.0f;
    return NO_ERROR;
}

int16_t sen44_read_measured_ambient_values_ticks(int16_t* voc_index,
                                                 int16_t* ambient_humidity,
                                                 int16_t* ambient_temperature) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[24];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x0A);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 6, &header);
    if (error) {
        return error;
    }
    *voc_index = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *ambient_humidity = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *ambient_temperature = sensirion_common_bytes_to_int16_t(&buffer[4]);
    return NO_ERROR;
}

int16_t sen44_read_measured_ambient_values(float* voc_index,
                                           float* ambient_humidity,
                                           float* ambient_temperature) {
    int16_t error = 0;
    int16_t voc_index_ticks;
    int16_t ambient_humidity_ticks;
    int16_t ambient_temperature_ticks;

    error = sen44_read_measured_ambient_values_ticks(
        &voc_index_ticks, &ambient_humidity_ticks, &ambient_temperature_ticks);
    if (error) {
        return error;
    }

    *voc_index = (float)voc_index_ticks / 10.0f;
    *ambient_humidity = (float)ambient_humidity_ticks / 100.0f;
    *ambient_temperature = (float)ambient_temperature_ticks / 200.0f;
    return NO_ERROR;
}

int16_t sen44_start_fan_cleaning(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x56, SEN44_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t sen44_set_auto_cleaning_interval(uint32_t interval) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[20];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x80, SEN44_UART_ADDRESS,
                                5);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_add_uint32_t_to_frame(&frame, interval);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(100000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t sen44_get_auto_cleaning_interval(uint32_t* interval) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[20];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x80, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 4, &header);
    if (error) {
        return error;
    }
    *interval = sensirion_common_bytes_to_uint32_t(&buffer[0]);
    return NO_ERROR;
}

int16_t sen44_get_article_code(unsigned char* article_code,
                               uint8_t article_code_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[522];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x02);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 255, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], article_code, article_code_size);
    return NO_ERROR;
}

int16_t sen44_get_serial_number(unsigned char* serial_number,
                                uint8_t serial_number_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[522];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SEN44_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x03);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 255, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], serial_number, serial_number_size);
    return NO_ERROR;
}

int16_t sen44_get_version(uint8_t* firmware_major, uint8_t* firmware_minor,
                          bool* firmware_debug, uint8_t* hardware_major,
                          uint8_t* hardware_minor, uint8_t* protocol_major,
                          uint8_t* protocol_minor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[26];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD1, SEN44_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 7, &header);
    if (error) {
        return error;
    }
    *firmware_major = buffer[0];
    *firmware_minor = buffer[1];
    *firmware_debug = buffer[2];
    *hardware_major = buffer[3];
    *hardware_minor = buffer[4];
    *protocol_major = buffer[5];
    *protocol_minor = buffer[6];
    return NO_ERROR;
}

int16_t sen44_read_device_status(bool clear, uint32_t* device_status,
                                 uint8_t* last_error) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[22];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD2, SEN44_UART_ADDRESS,
                                1);

    sensirion_shdlc_add_bool_to_frame(&frame, clear);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 5, &header);
    if (error) {
        return error;
    }
    *device_status = sensirion_common_bytes_to_uint32_t(&buffer[0]);
    *last_error = buffer[4];
    return NO_ERROR;
}

int16_t sen44_device_reset(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD3, SEN44_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(20000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    sensirion_uart_hal_sleep_usec(100000);
    return NO_ERROR;
}
