
#include  "ext/smc.c"

int main (int argc, char* argv[]) {
  SMCOpen();

  int i = 0, fans = SMCGetFanNumber(SMC_KEY_FAN_NUM);
  printf("CPU\t%0.1f\t°C\n", SMCGetTemperature(SMC_KEY_CPU_TEMP));
  printf("FAN_NUM\t%i\n", fans);
  for (i = 0; i < fans; i++)
      printf ("FAN_%i\t%0.1f\tRPM\n", i, SMCGetFanSpeed(i));

  SMCClose();
}
