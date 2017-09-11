/**
 * @file
 * @brief Simple communication with ADS1115 ADC.
 * @copyright 2016 [DeviceHive](http://devicehive.com)
 * @author Nikolay Khabarov
 */
#ifndef _SOURCES_DEVICES_ADS1115_H_
#define _SOURCES_DEVICES_ADS1115_H_

#include "user_config.h"
#if defined(DH_DEVICE_ADS1115)

/**
 * @brief Get ADC voltages.
 * @param[in] sda Pin for I2C's SDA. Can be DH_I2C_NO_PIN.
 * @param[in] scl Pin for I2C's SCL. Can be DH_I2C_NO_PIN.
 * @param[out] values Pointer to four float values to store result in Volts.
 * @return Status value, one of DH_I2C_Status enum.
 */
int ads1115_read(int sda, int scl, float values[4]);


/**
 * @brief Set sensor address which should be used while reading.
 * @param[in] address I2C end device address.
 */
void ads1115_set_address(int address);

#endif /* DH_DEVICE_ADS1115 */
#endif /* _SOURCES_DEVICES_ADS1115_H_ */
