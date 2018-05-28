
#include  "ext/smc.c"

int main (int argc, char* argv[]) {
  char *sensor_list[] = {AMBIENT_AIR_0, AMBIENT_AIR_1, CPU_0_DIODE,
                         CPU_0_HEATSINK, CPU_0_PROXIMITY, ENCLOSURE_BASE_0,
                         ENCLOSURE_BASE_1, ENCLOSURE_BASE_2, ENCLOSURE_BASE_3
                         GPU_0_DIODE, GPU_0_DIODE, GPU_0_HEATSINK,
                         GPU_0_PROXIMITY, HARD_DRIVE_BAY, MEMORY_SLOT_0,
                         MEMORY_SLOTS_PROXIMITY, NORTHBRIDGE, NORTHBRIDGE_DIODE,
                         NORTHBRIDGE_PROXIMITY, THUNDERBOLT_0, THUNDERBOLT_1,
                         WIRELESS_MODULE};

  system("clear");
  SMCOpen();

  int i = 0, fans = SMCGetFanNumber(SMC_KEY_FAN_NUM);

  printf("FANS:\t%i\n", fans);

  for (i = 0; i < fans; i++)
      printf ("FAN_%i\t%0.1f\tRPM\n", i, SMCGetFanSpeed(i));


      for (i = 0; i < 21; i++) {
        if (SMCGetTemperature(sensor_list[i]) > 0.0){
          printf("%s:\t%0.1f\t°C\n", sensor_list[i], SMCGetTemperature(sensor_list[i]));
        }
      }
/*
  printf("AMBIENT AIR 0:\t%0.1f\t°C\n", SMCGetTemperature(AMBIENT_AIR_0));
  printf("AMBIENT AIR 1:\t%0.1f\t°C\n", SMCGetTemperature(AMBIENT_AIR_1));
  printf("CPU DIODE:\t%0.1f\t°C\n", SMCGetTemperature(CPU_0_DIODE));
  printf("CPU HEATSINK:\t%0.1f\t°C\n", SMCGetTemperature(CPU_0_HEATSINK));
  printf("CPU PROXIMITY:\t%0.1f\t°C\n", SMCGetTemperature(CPU_0_PROXIMITY));
  printf("BATTERY :\t%0.1f\t°C\n", SMCGetTemperature(ENCLOSURE_BASE_0));
*/

  SMCClose();
}
