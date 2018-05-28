/*
 * Apple System Management Control (SMC) Tool
 * Copyright (C) 2006 devnull
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#ifndef __SMC_H__
#define __SMC_H__

#define VERSION               "0.01"

#define KERNEL_INDEX_SMC      2

#define SMC_CMD_READ_BYTES    5
#define SMC_CMD_WRITE_BYTES   6
#define SMC_CMD_READ_INDEX    8
#define SMC_CMD_READ_KEYINFO  9
#define SMC_CMD_READ_PLIMIT   11
#define SMC_CMD_READ_VERS     12

#define DATATYPE_FPE2         "fpe2"
#define DATATYPE_UINT8        "ui8 "
#define DATATYPE_UINT16       "ui16"
#define DATATYPE_UINT32       "ui32"
#define DATATYPE_SP78         "sp78"

/**
SMC keys for temperature sensors - 4 byte multi-character constants
Not applicable to all Mac's of course. In adition, the definition of the codes
may not be 100% accurate necessarily. Finally, list is incomplete.
Presumed letter translations:
- T = Temperature (if first char)
- C = CPU
- G = GPU
- P = Proximity
- D = Diode
- H = Heatsink
Sources:
- https://www.apple.com/downloads/dashboard/status/istatpro.html
- https://github.com/hholtmann/smcFanControl
- https://github.com/jedda/OSX-Monitoring-Tools
- http://www.parhelia.ch/blog/statics/k3_keys.html

Added sources:
- https://github.com/Chris911/iStats
*/
#define AMBIENT_AIR_0          "TA0P"
#define AMBIENT_AIR_0_1        "TA0p"
#define AMBIENT_AIR_1          "TA1P"
#define AMBIENT_AIR_1_1        "TA1p"
#define PCI_SLOT_1_POS_1       "TA0S"
#define PCI_SLOT_1_POS_2       "TA1S"
#define PCI_SLOT_2_POS_1       "TA2S"
#define PCI_SLOT_2_POS_2       "TA3S"
#define ENCLOSURE_BASE_0       "TB0T"
#define ENCLOSURE_BASE_1       "TB1T"
#define ENCLOSURE_BASE_2       "TB2T"
#define ENCLOSURE_BASE_3       "TB3T"
#define CPU_0_CORE             "TC0C"
#define CPU_0_DIODE            "TC0D"
#define PECI_CPU_0_0           "TCXC"
#define PECI_CPU_0_1           "TCXc"
#define CPU_0_E                "TC0E"
#define CPU_0_F                "TC0F"
#define CPU_0_G                "TC0G"
#define CPU_0_HEATSINK         "TC0H"
#define CPU_0_J                "TC0J"
#define CPU_0_PROXIMITY        "TC0P"
#define GPU_0_DIODE            "TG0D"
#define GPU_0_HEATSINK         "TG0H"
#define GPU_0_PROXIMITY        "TG0P"
#define HARD_DRIVE_BAY         "TH0P"
#define MEMORY_SLOT_0          "TM0S"
#define MEMORY_SLOTS_PROXIMITY "TM0P"
#define NORTHBRIDGE            "TN0H"
#define NORTHBRIDGE_DIODE      "TN0D"
#define NORTHBRIDGE_PROXIMITY  "TN0P"
#define SKIN_PROXIMITY         "Ts0P"
#define THUNDERBOLT_0          "TI0P"
#define THUNDERBOLT_1          "TI1P"
#define WIRELESS_MODULE        "TW0P"

// key values

//#define SMC_KEY_CPU_TEMP      "TC0P"
#define SMC_KEY_FAN_SPEED     "F%dAc"
#define SMC_KEY_FAN_NUM       "FNum"
//#define SMC_KEY_BATTERY_TEMP  "TB0T"


typedef struct {
    char                  major;
    char                  minor;
    char                  build;
    char                  reserved[1];
    UInt16                release;
} SMCKeyData_vers_t;

typedef struct {
    UInt16                version;
    UInt16                length;
    UInt32                cpuPLimit;
    UInt32                gpuPLimit;
    UInt32                memPLimit;
} SMCKeyData_pLimitData_t;

typedef struct {
    UInt32                dataSize;
    UInt32                dataType;
    char                  dataAttributes;
} SMCKeyData_keyInfo_t;

typedef char              SMCBytes_t[32];

typedef struct {
    UInt32                  key;
    SMCKeyData_vers_t       vers;
    SMCKeyData_pLimitData_t pLimitData;
    SMCKeyData_keyInfo_t    keyInfo;
    char                    result;
    char                    status;
    char                    data8;
    UInt32                  data32;
    SMCBytes_t              bytes;
} SMCKeyData_t;

typedef char              UInt32Char_t[5];

typedef struct {
    UInt32Char_t            key;
    UInt32                  dataSize;
    UInt32Char_t            dataType;
    SMCBytes_t              bytes;
} SMCVal_t;

// prototypes
float SMCGetFanSpeed(int fanNum);
int SMCGetFanNumber(char *key);
double SMCGetTemperature(char *key);
const char* getBatteryHealth();
int getDesignCycleCount();
int getBatteryCharge();
CFTypeRef IOPSCopyPowerSourcesInfo(void);
CFArrayRef IOPSCopyPowerSourcesList(CFTypeRef blob);
CFDictionaryRef IOPSGetPowerSourceDescription(CFTypeRef blob, CFTypeRef ps);


#endif // __SMC_H__
