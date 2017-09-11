/**
 * @file
 * @brief PCF8591 command handlers.
 * @copyright 2016 [DeviceHive](http://devicehive.com)
 * @author Nikolay Khabarov
 */
#ifndef _COMMANDS_PCF8591_CMD_H_
#define _COMMANDS_PCF8591_CMD_H_

#include "user_config.h"
#if defined(DH_COMMANDS_PCF8591) && defined(DH_DEVICE_PCF8591)
#include "dhsender_data.h"

/**
 * @brief Handle "devices/pcf8591/read" command.
 */
void dh_handle_devices_pcf8591_read(COMMAND_RESULT *cmd_res, const char *command,
                                    const char *params, unsigned int params_len);


/**
 * @brief Handle "devices/pcf8591/write" command.
 */
void dh_handle_devices_pcf8591_write(COMMAND_RESULT *cmd_res, const char *command,
                                     const char *params, unsigned int params_len);

#endif /* DH_COMMANDS_PCF8591 && DH_DEVICE_PCF8591 */
#endif /* _COMMANDS_PCF8591_CMD_H_ */
