/* SPDX-License-Identifier: MIT */
#include "ipmi_connection.h"
#include "ipmi_device.h"
#include "ipmi_internal.h"
#include "ipmi_log.h"

extern "C" {
#include <ipmitool/ipmi.h>
#include <ipmitool/log.h>
}

#include <aiRecord.h>
#include <errlog.h>
#include <link.h>
#include <map>
#include <mbbiDirectRecord.h>
#include <mbbiRecord.h>
#include <new>
#include <sstream>
#include <stdlib.h>
#include <utility>


namespace {

IPMIIOC::Device* findDevice(const link& _inp) {
  const auto& it = IPMIIOC::s_interfaces.find(_inp.value.abio.link);
  if (it == IPMIIOC::s_interfaces.end()) return NULL;
  else return it->second;
} // findDevice

} // namespace


void ipmiConnect(int _id, const char* _hostname, const char* _username,
                const char* _password, const char* _proto, int _privlevel) {
 ::log_init("ipmitool-ioc", 0, ::verbose);

 try {
   IPMIIOC::Device* d = new IPMIIOC::Device(_id);
   d->connect(_hostname, _username, _password, _proto, _privlevel);
   IPMIIOC::s_interfaces[_id] = d;
 } catch (std::bad_alloc& ba) {
   ::errlogSevPrintf(::errlogMajor, "Memory allocation error: %s\n", ba.what());
   return;
 } // catch
} // ipmiConnect


void ipmiInitAiRecord(aiRecord* _rec) {
 IPMIIOC::Device* d = findDevice(_rec->inp);
 if (d) d->initAiRecord(_rec);
} // ipmiInitAiRecord


void ipmiReadAiSensor(aiRecord* _rec) {
 IPMIIOC::Device* d = findDevice(_rec->inp);
 if (d) d->readAiSensor(_rec);
} // ipmiReadAiSensor


void ipmiInitMbbiDirectRecord(mbbiDirectRecord* _rec) {
 IPMIIOC::Device* d = findDevice(_rec->inp);
 if (d) d->initMbbiDirectRecord(_rec);
} // ipmiInitMbbiDirectRecord


void ipmiReadMbbiDirectSensor(mbbiDirectRecord* _rec) {
 IPMIIOC::Device* d = findDevice(_rec->inp);
 if (d) d->readMbbiDirectSensor(_rec);
} // ipmiReadMbbiDirectSensor


void ipmiInitMbbiRecord(mbbiRecord* _rec) {
 IPMIIOC::Device* d = findDevice(_rec->inp);
 if (d) d->initMbbiRecord(_rec);
} // ipmiInitMbbiRecord


void ipmiReadMbbiSensor(mbbiRecord* _rec) {
 IPMIIOC::Device* d = findDevice(_rec->inp);
 if (d) d->readMbbiSensor(_rec);
} // ipmiReadMbbiSensor


void ipmiScanDevice(int _id) {
 const auto& it = IPMIIOC::s_interfaces.find(_id);
 if (it == IPMIIOC::s_interfaces.end()) {
   IPMI_LOG_WARN("Device %d not found.", _id);
   return;
 }
 it->second->detectSensors();
} // ipmiScanDevice


void ipmiDumpDatabase(int _id, const char* _file) {
 if (!_file) {
   IPMI_LOG_WARN("No filename provided.");
   return;
 }
 const auto& it = IPMIIOC::s_interfaces.find(_id);
 if (it == IPMIIOC::s_interfaces.end()) {
   IPMI_LOG_WARN("Device not known.");
   return;
 }
 it->second->dumpDatabase(_file);
}


void ipmiInitialScan() {
  for(const auto& i : IPMIIOC::s_interfaces) {
     i.second->scanActiveIPMBs();
  }
}
