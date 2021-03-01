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

#ifndef SEN44_UART_H
#define SEN44_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sensirion_config.h"

/**
 * sen44_start_measurement() - Starts a continuous measurement.
 *
 * @note This command is only available in idle mode.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_start_measurement(void);

/**
 * sen44_stop_measurement() - Stops the measurement and returns to idle mode.
 *
 * @note This command is only available in measurement mode.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_stop_measurement(void);

/**
 * sen44_read_data_ready() - This command can be used to check if new
 * measurement results are ready to read. The data ready flag is automatically
 * reset after reading the measurement values with the 0x03 \"Read Measured
 * Values\" command.
 *
 * @param data_ready True (0x01) if data is ready, False (0x00) if not.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_read_data_ready(bool* data_ready);

/**
 * sen44_read_measured_pm_values() - Returns the measured particulate matter
 * values. The command 0x02 \"Read Data Ready\" can be used to check if new data
 * is available since the last read operation. If no new data is available, the
 * previous values will be returned again. If no data is available at all (no
 * measurement running or immediately after starting the measurement), an error
 * will be returned.
 *
 * @note This command is only available in measure mode.
 *
 * @param mass_concentration_pm1p0 Mass concentration PM1.0 [µg/m³].
 *
 * @param mass_concentration_pm2p5 Mass concentration PM2.5 [µg/m³].
 *
 * @param mass_concentration_pm4p0 Mass concentration PM4.0 [µg/m³].
 *
 * @param mass_concentration_pm10p0 Mass concentration PM10.0 [µg/m³].
 *
 * @param number_concentration_pm0p5 Number concentration PM0.5 [#/cm³].
 *
 * @param number_concentration_pm1p0 Number concentration PM1.0 [#/cm³].
 *
 * @param number_concentration_pm2p5 Number concentration PM2.5 [#/cm³].
 *
 * @param number_concentration_pm4p0 Number concentration PM4.0 [#/cm³].
 *
 * @param number_concentration_pm10p0 Number concentration PM10.0 [#/cm³].
 *
 * @param typical_particle_size Typical particle size [µm] with scale factor
 * 1000.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_read_measured_pm_values(
    uint16_t* mass_concentration_pm1p0, uint16_t* mass_concentration_pm2p5,
    uint16_t* mass_concentration_pm4p0, uint16_t* mass_concentration_pm10p0,
    uint16_t* number_concentration_pm0p5, uint16_t* number_concentration_pm1p0,
    uint16_t* number_concentration_pm2p5, uint16_t* number_concentration_pm4p0,
    uint16_t* number_concentration_pm10p0, uint16_t* typical_particle_size);

/**
 * sen44_read_measured_mass_concentration_and_ambient_values() - Returns the
 * measured mass concentration, VOC index and ambient temperature and humidity.
 * The command 0x02 \"Read Data Ready\" can be used to check if new data is
 * available since the last read operation. If no new data is available, the
 * previous values will be returned again. If no data is available at all (no
 * measurement running or immediately after starting the measurement), an error
 * will be returned.
 *
 * @note This command is only available in measure mode.
 *
 * @param mass_concentration_pm1p0 Mass concentration PM1.0 [µg/m³].
 *
 * @param mass_concentration_pm2p5 Mass concentration PM2.5 [µg/m³].
 *
 * @param mass_concentration_pm4p0 Mass concentration PM4.0 [µg/m³].
 *
 * @param mass_concentration_pm10p0 Mass concentration PM10.0 [µg/m³].
 *
 * @param voc_index VOC index with scale factor 10.
 *
 * @param ambient_humidity Compensated ambient relative humidity [%RH] with
 * scale factor 100.
 *
 * @param ambient_temperature Compensated ambient temperature [°C] with scale
 * factor 200.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_read_measured_mass_concentration_and_ambient_values(
    uint16_t* mass_concentration_pm1p0, uint16_t* mass_concentration_pm2p5,
    uint16_t* mass_concentration_pm4p0, uint16_t* mass_concentration_pm10p0,
    int16_t* voc_index, int16_t* ambient_humidity,
    int16_t* ambient_temperature);

/**
 * sen44_read_measured_ambient_values() - Returns the measured VOC index and
 * ambient temperature and humidity. The command 0x02 \"Read Data Ready\" can be
 * used to check if new data is available since the last read operation. If no
 * new data is available, the previous values will be returned again. If no data
 * is available at all (no measurement running or immediately after starting the
 * measurement), an error will be returned.
 *
 * @note This command is only available in measure mode.
 *
 * @param voc_index VOC index with scale factor 10.
 *
 * @param ambient_humidity Compensated ambient relative humidity [%RH] with
 * scale factor 100.
 *
 * @param ambient_temperature Compensated ambient temperature [°C] with scale
 * factor 200.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_read_measured_ambient_values(int16_t* voc_index,
                                           int16_t* ambient_humidity,
                                           int16_t* ambient_temperature);

/**
 * sen44_start_fan_cleaning() - Starts the fan cleaning manually.
 *
 * @note This command is only available in measure mode.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_start_fan_cleaning(void);

/**
 * sen44_set_auto_cleaning_interval() - Sets the auto cleaning interval for the
 * device.
 *
 * @param interval Auto cleaning interval [s]. Set to zero to disable auto
 * cleaning.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_set_auto_cleaning_interval(uint32_t interval);

/**
 * sen44_get_auto_cleaning_interval() - Gets the auto cleaning interval from the
 * device.
 *
 * @param interval Auto cleaning interval [s]. Zero means auto cleaning is
 * disabled.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_get_auto_cleaning_interval(uint32_t* interval);

/**
 * sen44_get_article_code() - Gets the article code from the device.
 *
 * @param article_code String containing the article code.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_get_article_code(unsigned char* article_code,
                               uint8_t article_code_size);

/**
 * sen44_get_serial_number() - Gets the serial number from the device.
 *
 * @param serial_number String containing the serial number.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_get_serial_number(unsigned char* serial_number,
                                uint8_t serial_number_size);

/**
 * sen44_get_version() - Gets the version information for the hardware, firmware
 * and SHDLC protocol.
 *
 * @param firmware_major Firmware major version number.
 *
 * @param firmware_minor Firmware minor version number.
 *
 * @param firmware_debug Firmware debug state. If the debug state is set, the
 * firmware is in development.
 *
 * @param hardware_major Hardware major version number.
 *
 * @param hardware_minor Hardware minor version number.
 *
 * @param protocol_major Protocol major version number.
 *
 * @param protocol_minor Protocol minor version number.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_get_version(uint8_t* firmware_major, uint8_t* firmware_minor,
                          bool* firmware_debug, uint8_t* hardware_major,
                          uint8_t* hardware_minor, uint8_t* protocol_major,
                          uint8_t* protocol_minor);

/**
 * sen44_read_device_status() - Reads the current device status.
 *
 * @note Use this command when the slave signalizes a device error in the slave
 * response.
 *
 * @param clear Set to true to clear the error flags after reading.
 *
 * @param device_status Device status (32 flags as integer).
 *
 * @param last_error Reserved for future use.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_read_device_status(bool clear, uint32_t* device_status,
                                 uint8_t* last_error);

/**
 * sen44_device_reset() - Executes a reset on the device. This has the same
 * effect as a power cycle.
 *
 * @note The device will reply before excecuting the reset.
 *
 * @return 0 on success, an error code otherwise
 */
int16_t sen44_device_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* SEN44_UART_H */
