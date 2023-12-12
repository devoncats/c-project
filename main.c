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

  // Report structure
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
void ClearMemory(int length);

void main () {
  // Declare local variables
  int options, length = 0;

  // User menu
  printf("Welcome to the patient database!\n");

  do {
    printf("\nCantidad de pacientes: %d\n", length);
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

    // Switch between options
    switch (options) {
      case 1: // Register new patient
        CreatePatient(&length);
        break;

      case 2: // Mesure bmi
        RegisterBMI(&length);
        break;
        
      case 3: // Mesure arterial pressure
        RegisterPressure(&length);
        break;

      case 4: // Mesure glucose
        RegisterGlucose(&length);
        break;

      case 5: // Print report of a patient
        PrintPatient(length);
        break;  

      case 6: // Print report of all the patients
        PrintAllPatients(length);
        break;

      case 7: // Exit
        ClearMemory(length);
        system("clear");

        printf("Universidad Tecnologica de Panama\n");
        printf("Facultad de Ingenieria de Sistemas Computacionales\n");
        printf("Licenciatura en Ingenieria de Sistemas y Computacion\n");
        printf("Proyecto Semestral\n");
        printf("Herramientas de Programacion Aplicada I\n");
        printf("Profesora: MSC. Giankaris G. Moreno\n");
        printf("Estudiante: Jose I. Vasquez\n");
        printf("1IL113\n");
        printf("2023\n");

        break;
      
      default: // Invalid option
        printf("\nInvalid option\n");
        break;
    }

  } while (options != 7);
}

void CreatePatient(int *length) {
  // Allocate memory for the new patient
  (*length)++;

  if ((*length) < 100) patients = realloc(patients, (*length) * sizeof(struct Patient));
  else printf("The database is full\n");

  // Fill the patient data
  printf("\nEnter patient name: ");
  patients[(*length) - 1].name = malloc(24 * sizeof(char));
  scanf("%s", patients[(*length) - 1].name);
  getchar();

  printf("Enter patient surname: ");
  patients[(*length) - 1].surname = malloc(24 * sizeof(char));
  scanf("%[^\n]", patients[(*length) - 1].surname);
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
  // Declare local variables
  int valid = 0;
  float weight, height;
  char id[12];
  
  // Ask for the patient id to find it
  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  for (int i = 0 ; i < (*length) ; i++) {
    // Search if the patient exists
    if (strcmp(patients[i].id, id) == 0) {
      // Ask for the weight and height of the patient
      printf("\nEnter patient weight (Kg): ");
      scanf("%f", &weight);
      getchar();

      printf("Enter patient height (m): ");
      scanf("%f", &height);
      getchar();

      // Calculate the bmi of the patient
      patients[i].report.bmi = weight / (height * height);

      // Print the bmi of the patient and register the status
      printf("\nThe bmi of the patient is: %.2f\n", patients[i].report.bmi);
      RegisterBMIStatus((*length));

      // Set the valid variable to 1 to know that the patient exists
      valid = 1;
    }
  }

  // If the patient doesn't exist, ask to create it
  if (valid == 0) {
    printf("The id of the patient is not registered\n");
    CreatePatient(length);
  }
}

void RegisterBMIStatus (int length) {
  // Declare local variables
  int i = length - 1;

  // Allocate memory for the bmi status
  patients[i].report.bmiStatus = malloc(24);

  // Set the bmi status of the patient
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

  // Print the bmi status of the patient
  printf("The bmi status of the patient is: %s\n", patients[i].report.bmiStatus);
}

void RegisterPressure (int *length) {
  // Declare local variables
  int valid = 0;
  char id[12];

  // Ask for the patient id to find it
  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  // Search if the patient exists
  for (int i = 0 ; i < (*length) ; i++) {
    // Ask for the pressure of the patient
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nEnter patient systolic pressure (mmHg): ");
      scanf("%f", &patients[i].report.SystolicPressure);
      getchar();

      printf("Enter patient diastolic pressure (mmHg): ");
      scanf("%f", &patients[i].report.DiastolicPressure);
      getchar();

      // Print the pressure of the patient and register the status
      printf("The systolic pressure of the patient is: %.2f\n", patients[i].report.SystolicPressure);
      printf("The diastolic pressure of the patient is: %.2f\n", patients[i].report.DiastolicPressure);
      RegisterPressureStatus((*length));

      // Set the valid variable to 1 to know that the patient exists
      valid = 1;
    }
  }

  // If the patient doesn't exist, ask to create it
  if (valid == 0) {
    printf("The id of the patient is not registered\n");
    CreatePatient(length);
  }

}

void RegisterPressureStatus (int length) {
  // Declare local variables
  int i = length - 1;

  // Allocate memory for the pressure status
  patients[i].report.pressureStatus = malloc(24);

  // Set the pressure status of the patient
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

  // Print the pressure status of the patient
  printf("The pressure status of the patient is: %s\n", patients[i].report.pressureStatus);
}

void RegisterGlucose (int *length) {
  // Declare local variables
  int valid = 0;
  char id[12], fast;

  // Ask for the patient id to find it
  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar();

  // Search if the patient exists
  for (int i = 0 ; i < (*length) ; i++) {
    // Ask for the glucose and if they are fasting of the patient
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nEnter patient glucose (mg/dL): ");
      scanf("%f", &patients[i].report.glucose);
      getchar();

      printf("Is the patient fasting? (y/n): ");
      scanf(" %c", &fast);
      getchar();

      // Print the glucose of the patient and register the status      
      printf("The glucose of the patient is: %.2f\n", patients[i].report.glucose);
      RegisterGlucoseStatus((*length), fast);

      // Set the valid variable to 1 to know that the patient exists
      valid = 1;
    }
  }

  // If the patient doesn't exist, ask to create it
  if (valid == 0) {
    printf("The id of the patient is not registered\n");
    CreatePatient(length);
  }

}

void RegisterGlucoseStatus (int length, char fast) {
  // Declare local variables
  int i = length - 1;

  // Allocate memory for the glucose status
  patients[i].report.glucoseStatus = malloc(12);

  // Set the glucose status of the patient
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

  // Print the glucose status of the patient
  printf("The glucose status of the patient is: %s\n", patients[i].report.glucoseStatus);
}

void PrintPatient(int length) {
  // Declare local variables
  char id[12];

  // Ask for the patient id to find it
  printf("\nEnter patient id: ");
  scanf("%s", id);
  getchar(); 

  // Search if the patient exists
  for (int i = 0 ; i < length ; i++) {
    // Print the patient data
    if (strcmp(patients[i].id, id) == 0) {
      printf("\nGeneral information of the patient\n");
      printf("\n%-13s %-20s\n", "Name: ", patients[i].name);
      printf("%-13s %-20s\n", "Surname: ", patients[i].surname);
      printf("%-13s %-20s\n", "ID: ", patients[i].id);
      patients[i].gender == 'm' ? printf("%-13s %-20s\n", "Gender: ", "Masculine") : printf("%-13s %-20s\n", "Gender: ", "Feminine");
      printf("%-13s %-20d\n", "Age: ", patients[i].age);
      printf("%-13s %-20s\n", "Birthdate", patients[i].birthdate);
      printf("\nMedical report\n");
      printf("\n%-13s %-20s\n", "BMI: ", patients[i].report.bmiStatus);
      printf("%-13s %-20s\n", "Pressure: ", patients[i].report.pressureStatus);
      printf("%-13s %-20s\n", "Glucose", patients[i].report.glucoseStatus); 
    }
  }
}

void PrintAllPatients(int length) {
  // Print the header of the table
  printf("%-2c %-16s %-16s %-14s %-8s %-4s %-12s %-16s %-16s %-16s\n", '#', "Name", "Surname", "ID", "Gender", "Age", "Birthdate", "BMI", "Pressure", "Glucose");
  for (int i = 0 ; i < length ; i++) {
    // Print the data of the patients
    printf("%-2d %-16s %-16s %-14s %-8c %-4d %-12s %-16s %-16s %-16s", i + 1, patients[i].name, patients[i].surname, patients[i].id, patients[i].gender, patients[i].age, patients[i].birthdate, patients[i].report.bmiStatus, patients[i].report.pressureStatus, patients[i].report.glucoseStatus);
  }
}

void ClearMemory(int length) {
  // Free the memory of the patients
  for (int i = 0 ; i < length ; i++) {
    free(patients[i].name);
    free(patients[i].surname);
    free(patients[i].id);
    free(patients[i].birthdate);
    free(patients[i].report.bmiStatus);
    free(patients[i].report.pressureStatus);
    free(patients[i].report.glucoseStatus);
  }

  // Free the memory of the patients
  free(patients);
}