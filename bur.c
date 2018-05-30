
#include  "ext/smc.c"
#include <string.h>

char** scan_temp(char** sensor_list, unsigned int* num_sensors);
void save(char** sensor_list);
void print (char** sensor_list, unsigned int* num_sensors);
void display(void);

const char characters[] =
               "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int main (int argc, char* argv[]) {
  char** sensor_list;
  unsigned int num_sensors;

  if (argc > 2)
    return -1;

  sensor_list = malloc(sizeof(char*));
  num_sensors = 0;


  sensor_list = scan_temp(sensor_list, &num_sensors);
  printf("Sensorlist save test: %s, %s", sensor_list[0], sensor_list[1]);
  print(sensor_list, &num_sensors);


  return 0;
}


char** scan_temp(char** sensor_list, unsigned int* num_sensors) {
  SMCOpen();
  /* Go through all possible combinations of T### and see which ones are
   * positive values. Save these ones.
   */
  unsigned int i, j, k;
  char sensor[] = "Taaa";
  char *sensor_ptr = &sensor[0];
  char **list_check;

  // reset incoming array
  // for (i = 0; i < *num_sensors; i++) {
  //   if (sensor_list[i] != NULL)
  //     free(sensor_list[i]);
  // }
  //   if (sensor_list != NULL)
  //     free(sensor_list)
  *num_sensors = 0;

  // setup the array
  //sensor_list = malloc(sizeof (char*) * 1);
  printf("Searching for keys...\n...");


  for (i = 0; i < 62; i++) {
    for (j = 0; j < 62; j++) {
      for (k = 0; k < 62;k++) {
        sensor[1] = characters[i];
        sensor[2] = characters[j];
        sensor[3] = characters[k];
        if (SMCGetTemperature(sensor_ptr) > 0) {
          printf("\rFound %s!", sensor_ptr);
          fflush(stdout);
          // set memory aside for temp label
          sensor_list[*num_sensors] = malloc(sizeof(char)*4);

          // set data in newly set memory
          for (int q = 0; q < 4; q++) {
            sensor_list[*num_sensors][q] = sensor[q];
          }

          // increment sensors
          *num_sensors += 1;

          // resize sensor_list to anticipate new addition. Do not leak the mem
          list_check = realloc(sensor_list, (sizeof(char*) * (*num_sensors + 1)));
          if (list_check != NULL) {
            sensor_list = list_check;
          } else {  // handle in case of memory leak
            free(list_check);
            for (i = 0; i < *num_sensors; i++) {
              free(sensor_list[i]);
            }
            free(sensor_list);
            exit(-1);
          }
        }
      }
    }
  }
  printf("\r                   \n");


  for (i = 0; i < *num_sensors; i++){
    fflush(stdout);
    printf("%s:\t%0.01f\t°C\n", sensor_list[i],SMCGetTemperature(sensor_list[i]));
  }

  SMCClose();

  return sensor_list;

}

void print(char** sensor_list, unsigned int *num_sensors) {
  unsigned int i;

  printf("%d\n", *num_sensors);

  SMCOpen();
  printf("SMCOpen()\n");
  for (i = 0; i < *num_sensors; i++){
    fflush(stdout);
    printf("%s:\t%0.01f\t°C\n", sensor_list[i],SMCGetTemperature(sensor_list[i]));
  }

  SMCClose();
}
