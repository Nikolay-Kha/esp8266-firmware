/*
 * dhzc_post.h
 *
 * Copyright 2015 DeviceHive
 *
 * Author: Nikolay Khabarov
 *
 */
#include "dhzc_post.h"
#include "dhsettings.h"
#include "dhutils.h"

#include <c_types.h>
#include <osapi.h>
#include <os_type.h>
#include <user_interface.h>
#include <ets_forward.h>

typedef int (*Char_Test)(char c);

LOCAL int ICACHE_FLASH_ATTR read_value(const char *data, unsigned int len, char *value, unsigned int *rb, Char_Test test) {
	if(*rb == 0)
		return 0;
	unsigned int pos;
	unsigned int vp = 0;
	unsigned int vl = *rb - 1;
	for(pos = 0; pos < len; pos++) {
		char c;
		int set = 1;
		if(data[pos] == '&') {
			break;
		} else if(data[pos] == '+') {
			c = ' ';
		} else if(data[pos] == '%') {
			char b[2] = {0, 0};
			if(pos + 1 < len)
				b[0] = data[pos + 1];
			if(pos + 2 < len)
				b[1] = data[pos + 2];
			set = hexToByte(b, (uint8_t*)&c);
			pos += set;
		} else {
			c = data[pos];
		}
		if(set) {
			if(test) {
				if(test(c) == 0)
					return 0;
			}
			value[vp++] = c;
			if(vp >= vl)
				break;
		}
	}
	value[vp] = 0;
	*rb = vp;
	return 1;
}

char * ICACHE_FLASH_ATTR dhzc_post_parse(const char *data, unsigned int len) {
	if(len == 0)
		return "POST data not found.";
	const char mode[] = "mode=";
	const char ssid[] = "ssid=";
	const char pass[] = "pass=";
	const char url[] = "url=";
	const char id[] = "id=";
	const char key[] = "key=";
	unsigned int pos = 0;
	char value[2048];
	unsigned char found = 0;
	while(pos < len) {
		unsigned int rb = sizeof(value);
		if(os_strncmp(&data[pos], mode, sizeof(mode) - 1) == 0) {
			pos += sizeof(mode) - 1;
			if(pos <= len) {
				int vl = read_value(&data[pos], len - pos, value, &rb, 0);
				if(vl)
					pos += rb;
				if(vl && os_strcmp(value, "cl") == 0) {
					dhsettings_set_wifi_mode(WIFI_MODE_CLIENT);
				} else if(vl && os_strcmp(value, "ap") == 0) {
					dhsettings_set_wifi_mode(WIFI_MODE_AP);
				} else {
					return "Wrong WiFi mode.";
				}
				found = 1;
			}
		} else if(os_strncmp(&data[pos], ssid, sizeof(ssid) - 1) == 0) {
			pos += sizeof(ssid) - 1;
			if(pos <= len) {
				int vl = read_value(&data[pos], len - pos, value, &rb, 0);
				if(vl == 0)
					return "Wrong Wi-Fi SSID value.";
				pos += rb;
				if(rb > DHSETTINGS_SSID_MAX_LENGTH - 1)
					return "SSID too long";
				dhsettings_set_wifi_ssid(value);
				found = 1;
			}
		} else if(os_strncmp(&data[pos], pass, sizeof(pass) - 1) == 0) {
			pos += sizeof(pass) - 1;
			if(pos <= len) {
				int vl = read_value(&data[pos], len - pos, value, &rb, 0);
				if(vl == 0)
					return "Wrong Wi-Fi password value.";
				pos += rb;
				if(rb) {
					if(rb > DHSETTINGS_PASSWORD_MAX_LENGTH - 1)
						return "Wi-Fi password too long";
					dhsettings_set_wifi_password(value);
					found = 1;
				}
			}
		} else if(os_strncmp(&data[pos], url, sizeof(url) - 1) == 0) {
			pos += sizeof(url) - 1;
			if(pos <= len) {
				int vl = read_value(&data[pos], len - pos, value, &rb, dhsettings_server_filter);
				if(vl == 0)
					return "Wrong DeviceHive API Url.";
				pos += rb;
				if(rb > DHSETTINGS_SERVER_MAX_LENGTH - 1)
					return "API URL too long";
				dhsettings_set_devicehive_server(value);
				found = 1;
			}
		} else if(os_strncmp(&data[pos], id, sizeof(id) - 1) == 0) {
			pos += sizeof(id) - 1;
			if(pos <= len) {
				int vl = read_value(&data[pos], len - pos, value, &rb, dhsettings_deviceid_filter);
				if(vl == 0)
					return "Wrong DeviceId.";
				pos += rb;
				if(rb > DHSETTINGS_DEVICEID_MAX_LENGTH - 1)
					return "DeviceId too long";
				dhsettings_set_devicehive_deviceid(value);
				found = 1;
			}
		} else if(os_strncmp(&data[pos], key, sizeof(key) - 1) == 0) {
			pos += sizeof(key) - 1;
			if(pos <= len) {
				int vl = read_value(&data[pos], len - pos, value, &rb, dhsettings_key_filter);
				if(vl == 0)
					return "Wrong Key.";
				pos += rb;
				if(rb) {
					if(rb > DHSETTINGS_KEY_MAX_LENGTH - 1)
						return "Key too long";
					dhsettings_set_devicehive_key(value);
					found = 1;
				}
			}
		} else {
			pos++;
		}
	}
	if(found)
		return 0;
	return "Empty data.";
}
