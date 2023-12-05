#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient structure
struct Patient {
  char *name;
  char *surname;
  char *id;
  int age;
  char gender;
  char *birthdate;

  struct Report {
    float bmi;
    char *bmiStatus;
    float SystolicPressure;
    float DiastolicPressure;
    char *pressureStatus;
    float glucose;
    char *glucoseStatus;
  } report;  
};

// Declare global variables
struct Patient *patients = NULL;


// Function prototypes
void CreatePatient(int *length);
void RegisterBMI (int *length);
void RegisterBMIStatus (int length);
void RegisterPressure (int *length);
void RegisterPressureStatus (int length);
void RegisterGlucose (int *length);
void RegisterGlucoseStatus (int length, char fast);
void PrintPatient(int length);
void PrintAllPatients(int length);

void main () {
  int options, length = 0;

  printf("Welcome to the patient database!\n");

  do {
    printf("\n1. Register new patient\n");
    printf("2. Mesure bmi\n");
    printf("3. Mesure arterial pressure\n");
    printf("4. Mesure glucose\n");
    printf("5. Print report of a patient\n");
    printf("6. Print report of all the patients\n");
    printf("7. Exit\n");
    printf("\nEnter an option: ");
    scanf("%d", &options);
    getchar();

    switch (options) {
      case 1:
        CreatePatient(&length);
        break;

      case 2: // Mesure bmi
        RegisterBMI(&length);
        break;
        
      case 3: // Mesure arterial pressure
        RegisterPressure(&length);
        break;

      case 4: // Mesure glucose
        // call function to mesure glucose
        break;

      case 5: // Print report of a patient
        PrintPatient(length);
        break;

      case 6: // Print report of all the patients
        PrintAllPatients(length);
        break;

      case 7: // Exit
        printf("\nThanks for using the program\n");
        break;
      
      default: // Invalid option
        printf("\nInvalid option\n");
        break;
    }

  } while (options != 7);
}

void CreatePatient(int *length) {
  (*length)++;
  patients = realloc(patients, (*length) * sizeof(struct Patient));

  printf("\nEnter patient name: ");
  patients[(*length) - 1].name = malloc(24 * sizeof(char));
  scanf("%s", patients[(*length) - 1].name);
  getchar();

  printf("Enter patient surname: ");
  patients[(*length) - 1].surname = malloc(24 * sizeof(char));
  scanf("%s", patients[(*length) - 1].surname);
  getchar();

  printf("Enter patient id: ");
  patients[(*length) - 1].id = malloc(12 * sizeof(char));
  scanf("%s", patients[(*length) - 1].id);
  getchar();

  printf("Enter patient age: ");
  scanf("%d", &patients[(*length) - 1].age);
  getchar();

  printf("Enter patient gender (m/f): ");
  scanf(" %c", &patients[(*length) - 1].gender);
  getchar();

  printf("Enter patient birthdate (dd/mm/yyyy): ");
  patients[(*length) - 1].birthdate = malloc(10 * sizeof(char));
  scanf("%s", patients[(*length) - 1].birthdate);
  getchar();

  printf("\nPatient registered successfully\n");
}

void RegisterBMI (int *length) {
  int valid = 0;
  float weight, height;
  char id[12];

  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  for (int i = 0 ; i < (*length) ; i++) {
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nEnter patient weight (Kg): ");
      scanf("%f", &weight);
      getchar();

      printf("Enter patient height (m): ");
      scanf("%f", &height);
      getchar();

      patients[i].report.bmi = weight / (height * height);

      printf("\nThe bmi of the patient is: %.2f\n", patients[i].report.bmi);
      RegisterBMIStatus((*length));

      valid = 1;
    }
  }

  if (valid == 0) {
    printf("The id of the patient is not registered\n");
    CreatePatient(length);
  }
}

void RegisterBMIStatus (int length) {
  int i = length - 1;
  patients[i].report.bmiStatus = malloc(24);

  if (patients[i].report.bmi < 18.5) {
    patients[i].report.bmiStatus = strdup("Underweight");
  } else if (patients[i].report.bmi >= 18.5 && patients[i].report.bmi <= 24.9) {
    patients[i].report.bmiStatus = strdup("Normal weight");
  } else if (patients[i].report.bmi >= 25 && patients[i].report.bmi <= 29.9) {
    patients[i].report.bmiStatus = strdup("Overweight");
  } else if (patients[i].report.bmi >= 30 && patients[i].report.bmi <= 34.9) {
    patients[i].report.bmiStatus = strdup("Obesity I");
  } else if (patients[i].report.bmi >= 35 && patients[i].report.bmi <= 39.9) {
    patients[i].report.bmiStatus = strdup("Obesity II");
  } else if (patients[i].report.bmi >= 40) {
    patients[i].report.bmiStatus = strdup("Obesity III");
  }

  printf("The bmi status of the patient is: %s\n", patients[i].report.bmiStatus);
}

void RegisterPressure (int *length) {
  int valid = 0;
  char id[12];

  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  for (int i = 0 ; i < (*length) ; i++) {
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nEnter patient systolic pressure (mmHg): ");
      scanf("%f", &patients[i].report.SystolicPressure);
      getchar();

      printf("Enter patient diastolic pressure (mmHg): ");
      scanf("%f", &patients[i].report.DiastolicPressure);
      getchar();

      printf("The systolic pressure of the patient is: %.2f\n", patients[i].report.SystolicPressure);
      printf("The diastolic pressure of the patient is: %.2f\n", patients[i].report.DiastolicPressure);
      RegisterPressureStatus((*length));

      valid = 1;
    }
  }

  if (valid == 0) {
    printf("The id of the patient is not registered\n");
    CreatePatient(length);
  }

}

void RegisterPressureStatus (int length) {
  int i = length - 1;
  patients[i].report.pressureStatus = malloc(24);

  if (patients[i].report.SystolicPressure < 120 && patients[i].report.DiastolicPressure < 80) {
    patients[i].report.pressureStatus = strdup("Normal");
  } else if (patients[i].report.SystolicPressure >= 120 && patients[i].report.SystolicPressure <= 129 && patients[i].report.DiastolicPressure < 80) {
    patients[i].report.pressureStatus = strdup("Elevated");
  } else if (patients[i].report.SystolicPressure >= 130 && patients[i].report.SystolicPressure <= 139 && patients[i].report.DiastolicPressure >= 80 && patients[i].report.DiastolicPressure <= 89) {
    patients[i].report.pressureStatus = strdup("High blood pressure I");
  } else if (patients[i].report.SystolicPressure >= 140 && patients[i].report.SystolicPressure <= 180 && patients[i].report.DiastolicPressure >= 90 && patients[i].report.DiastolicPressure <= 120) {
    patients[i].report.pressureStatus = strdup("High blood pressure II");
  } else if (patients[i].report.SystolicPressure > 180 && patients[i].report.DiastolicPressure > 120) {
    patients[i].report.pressureStatus = strdup("Hypertensive crisis");
  }

  printf("The pressure status of the patient is: %s\n", patients[i].report.pressureStatus);
}

void RegisterGlucose (int *length) {
  int valid = 0;
  char id[12], fast;

  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  for (int i = 0 ; i < (*length) ; i++) {
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nEnter patient glucose (mg/dL): ");
      scanf("%f", &patients[i].report.glucose);
      getchar();

      printf("Is the patient fasting? (y/n): ");
      scanf(" %c", &fast);
      getchar();

      printf("The glucose of the patient is: %.2f\n", patients[i].report.glucose);
      RegisterGlucoseStatus((*length), fast);

      valid = 1;
    }
  }

  if (valid == 0) {
    printf("The id of the patient is not registered\n");
    CreatePatient(length);
  }

}

void RegisterGlucoseStatus (int length, char fast) {
  int i = length - 1;
  patients[i].report.glucoseStatus = malloc(24);

  if (fast == 'y') {
    if (patients[i].report.glucose >= 70 && patients[i].report.glucose <= 100) {
      patients[i].report.glucoseStatus = strdup("Normal");
    } else if (patients[i].report.glucose > 100 && patients[i].report.glucose <= 125) {
      patients[i].report.glucoseStatus = strdup("Prediabetes");
    } else if (patients[i].report.glucose > 125) {
      patients[i].report.glucoseStatus = strdup("Diabetes");
    }
  } else if (fast == 'n') {
    if (patients[i].report.glucose < 140) {
      patients[i].report.glucoseStatus = strdup("Normal");
    } else if (patients[i].report.glucose >= 140 && patients[i].report.glucose <= 199) {
      patients[i].report.glucoseStatus = strdup("Prediabetes");
    } else if (patients[i].report.glucose > 199) {
      patients[i].report.glucoseStatus = strdup("Diabetes");
    }
  }

  printf("The glucose status of the patient is: %s\n", patients[i].report.glucoseStatus);
}

void PrintPatient(int length) {
  char id[12];

  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  for (int i = 0 ; i < length ; i++) {
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nName: %s\n", patients[i].name);
      printf("Surname: %s\n", patients[i].surname);
      printf("Id: %s\n", patients[i].id);
      patients[i].gender == 'm' ? printf("Gender: Masculine\n") : printf("Gender: Feminine\n");
      printf("Age: %d\n", patients[i].age);
      printf("Birthdate: %s\n", patients[i].birthdate);
      printf("BMI: %.2f\n", patients[i].report.bmiStatus);
      printf("Pressure: %s\n", patients[i].report.pressureStatus);
      printf("Glucose: %s\n", patients[i].report.glucoseStatus);
    }
  }
}

void PrintAllPatients(int length) {
  for (int i = 0 ; i < length ; i++) {
    printf("\nName: %s\n", patients[i].name);
    printf("Surname: %s\n", patients[i].surname);
    printf("Id: %s\n", patients[i].id);
    patients[i].gender == 'm' ? printf("Gender: Masculine\n") : printf("Gender: Feminine\n");
    printf("Age: %d\n", patients[i].age);
    printf("Birthdate: %s\n", patients[i].birthdate);
    printf("BMI: %.2f\n", patients[i].report.bmiStatus);
    printf("Pressure: %s\n", patients[i].report.pressureStatus);
    printf("Glucose: %s\n", patients[i].report.glucoseStatus);
  }
}