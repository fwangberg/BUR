
#include  "ext/smc.c"
#include <string.h>

int main (int argc, char* argv[]) {
  //char *sensor_list[] = {};
  char characters[] =
               "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  char sensor[] = "Taaa";
  char *sensor_ptr = &sensor[0];

  //system("clear");
  SMCOpen();

  int i = 0, j = 0, k = 0, fans = SMCGetFanNumber(SMC_KEY_FAN_NUM);

  printf("FAN_NUM\t%i\n", fans);


  for (i = 0; i < 62; i++) {
    for (j = 0; j < 62; j++) {
      for (k = 0; k < 62;k++) {
        sensor[1] = characters[i];
        sensor[2] = characters[j];
        sensor[3] = characters[k];
        if (SMCGetTemperature(sensor_ptr) > 0)
          printf("%s:\t%0.01f\t°C\n", sensor_ptr, SMCGetTemperature(sensor_ptr));
      }
    }
  }

/*  for (i = 0; i < fans; i++)
      printf ("FAN_%i\t%0.1f\tRPM\n", i, SMCGetFanSpeed(i));


      for (i = 0; i < 22; i++) {
        if (SMCGetTemperature(sensor_list[i]) > 0.0){
          printf("%s:\t%0.1f\t°C\n", sensor_list[i], SMCGetTemperature(sensor_list[i]));
        }
      }*/
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
