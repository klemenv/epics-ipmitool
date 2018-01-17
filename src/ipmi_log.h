/* SPDX-License-Identifier: MIT */
#pragma once

#include <stdio.h>

#define IPMI_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)

#define IPMI_LOG_DEBUG(fmt, ...) IPMI_LOG("DEBUG: " # fmt, ##__VA_ARGS__)
#define IPMI_LOG_INFO(fmt, ...)  IPMI_LOG("INFO: " # fmt, ##__VA_ARGS__)
#define IPMI_LOG_WARN(fmt, ...)  IPMI_LOG("WARN: " # fmt, ##__VA_ARGS__)
#define IPMI_LOG_ERROR(fmt, ...) IPMI_LOG("ERROR: " # fmt, ##__VA_ARGS__)
