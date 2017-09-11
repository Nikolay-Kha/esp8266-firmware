/**
 * @file
 * @brief ADS1115 command handlers.
 * @copyright 2016 [DeviceHive](http://devicehive.com)
 * @author Nikolay Khabarov
 */
#ifndef _COMMANDS_ADS1115_CMD_H_
#define _COMMANDS_ADS1115_CMD_H_

#include "user_config.h"
#if defined(DH_COMMANDS_ADS1115) && defined(DH_DEVICE_ADS1115)
#include "dhsender_data.h"

/**
 * @brief Handle "devices/ads1115/read" command.
 */
void dh_handle_devices_ads1115_read(COMMAND_RESULT *cmd_res, const char *command,
                                    const char *params, unsigned int params_len);

#endif /* DH_COMMANDS_ADS1115 && DH_DEVICE_ADS1115 */
#endif /* _COMMANDS_ADS1115_CMD_H_ */
