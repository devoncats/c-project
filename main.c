#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Patient {
  char *name;
  char *surname;
  char *id;
  int age;
  char gender;
  char *birthdate;

  struct Report {
    float bmi;
    float pressure;
    float glucose;
  } report;
};

char *read(char *promt, int length);
void registerPatient (struct Patient **patient, int *lenght);
void registerBMI (struct Patient **patient, int length);
void registerPressure (struct Patient **patient, int length);

void main () {
  int options, length = 0;
  struct Patient *patients = NULL;

  printf("Welcome to the patient database!\n");

  do {
    printf("1. Register new patient\n");
    printf("2. Mesure bmi\n");
    printf("3. Mesure arterial pressure\n");
    printf("4. Mesure glucose\n");
    printf("5. Exit\n");
    printf("Enter an option: ");
    scanf("%d", &options);
    getchar();

    switch (options) {
      case 1: // Create new patient
        registerPatient(&patients, &length);
        break;

      case 2: // Mesure bmi
        registerBMI (&patients, length);
        break;
        
      case 3: // Mesure arterial pressure
        // call function to mesure arterial pressure  
        break;

      case 4: // Mesure glucose
        // call function to mesure glucose
        break;

      case 5: // Exit
        printf("Thanks for using the program\n");
        break;

      default: // Invalid option
        printf("Invalid option\n");
        break;
    }

  } while (options != 5);

  printf("%d\n", patients[0].age);

  for (int i = 0; i < length; i++) {
    free(patients[i].name);
    free(patients[i].surname);
    free(patients[i].id);
    free(patients[i].birthdate);
  }

  free(patients);
}

char *read(char *prompt, int max) {
  printf("%s", prompt);

  char *string = malloc(max);

  fgets(string, max, stdin);

  int length = strlen(string);
  
  if (length > 0 && string[length - 1] == '\n') {
    string[length - 1] = '\0';
  }

  return string;
}

void registerPatient (struct Patient **patient, int *lenght) {
  char *name, *surname, *id, *birthdate, gender;
  int age;

  (*lenght)++;    
  *patient = realloc(*patient, (*lenght) * sizeof(struct Patient));

  name = read("Enter the name of the patient: ", 25);
  (*patient)[(*lenght) - 1].name = strdup(name);

  surname = read("Enter the surname of the patient: ", 25);
  (*patient)[(*lenght) - 1].surname = strdup(surname);

  id = read("Enter the id of the patient: ", 12);
  (*patient)[(*lenght) - 1].id = strdup(id);

  printf("Enter the age of the patient: ");
  scanf("%d", &age);
  getchar();
  (*patient)[(*lenght) - 1].age = age;

  printf("Enter the gender of the patient: ");
  scanf(" %c", &gender);
  getchar();
  (*patient)[(*lenght) - 1].gender = tolower(gender);

  birthdate = read("Enter the birthdate of the patient: ", 11);
  (*patient)[(*lenght) - 1].birthdate = strdup(birthdate);
}

void registerBMI (struct Patient **patient, int length) {
  char *id = read("Enter the id of the patient", 12);

  for (int i = 0 ; i < length ; i++) {
    if (strcmp((*patient)[i].id, id) == 0) {
      float weight, height;

      printf("Enter the weight of the patient (kg): ");
      scanf("%f", &weight);
      getchar();

      printf("Enter the height of the patient (m): ");
      scanf("%f", &height);
      getchar();

      (*patient)[i].report.bmi = weight / (height * height);

      printf("The bmi of the patient is: %.2f\n", (*patient)[i].report.bmi);
    } else {
      printf("The id of the patient is not registered\n");
    }
  } 
}

void registerPressure (struct Patient **patient, int length) {
  char *id = read("Enter the id of the patient", 12);

  for (int i = 0 ; i < length ; i++) {
    if (strcmp((*patient)[i].id, id) == 0) {
      float weight, height;

      printf("Enter the weight of the patient (kg): ");
      scanf("%f", &weight);
      getchar();

      printf("Enter the height of the patient (m): ");
      scanf("%f", &height);
      getchar();

      (*patient)[i].report.bmi = weight / (height * height);

      printf("The bmi of the patient is: %.2f\n", (*patient)[i].report.bmi);
    } else {
      printf("The id of the patient is not registered\n");
    }
  }
}
