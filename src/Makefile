# Makefile
TOP = ..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

LIBRARY_IOC += ipmitool

DBD += ipmitool.dbd

ipmitool_SRCS += epics_device.c
ipmitool_SRCS += epics_functions.c
ipmitool_SRCS += ipmi_connection.cc
ipmitool_SRCS += ipmi_device.cc
ipmitool_SRCS += ipmi_device_private.cc
ipmitool_SRCS += ipmi_internal.cc
ipmitool_SRCS += ipmi_reader_thread.cc
ipmitool_SRCS += ipmi_types.cc

ipmitool_LIBS += $(EPICS_BASE_IOC_LIBS)
ipmitool_SYS_LIBS += ssl crypto

STATIC_LDLIBS += $(IPMITOOL)/lib/.libs/libipmitool.a
STATIC_LDLIBS += $(IPMITOOL)/src/plugins/.libs/libintf.a

USR_INCLUDES += -I $(IPMITOOL)/include
USR_INCLUDES += -I $(IPMITOOL)/src/plugins/lan
USR_CXXFLAGS += -std=c++11

include $(TOP)/configure/RULES

#----------------------------------------
#  ADD RULES AFTER THIS LINE


