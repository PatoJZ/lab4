#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Patient{
    char name[50];
    int age;
    int room;
    float temperature[3];
    struct Patient* next;
} Patient;

void addPatient(Patient** head) {
    Patient* p = malloc(sizeof(Patient));
    printf("Introduce el nombre del paciente: ");
    scanf("%s", p->name);
    printf("Introduce la edad del paciente: ");
    scanf("%d", &p->age);
    printf("Introduce la habitacion del paciente: ");
    scanf("%d", &p->room);
    p -> next = *head;
    *head = p;
    recordTemperatures(p);
}
void printPatient(Patient* head){
    Patient* current = head;
    while (current!= NULL) {
    
        printf(" --------\n Nombre: %s\n Edad: %d\n Habitacion: %d\n", current -> name, current -> age, current -> room);
        for (int i = 0; i < 3; i++){
            printf("Temperatura %d: %f\n", i+1, current -> temperature[i]);
        }
        current = current -> next;
    }
}
void recordTemperatures(Patient* paciente){
        for(int j = 0; j < 3; j++){
            printf("--------Temperatura %d--------\n",j+1);
            printf("Introduce la temperatura del paciente: ");
            scanf("%f",&paciente->temperature[j]);
        }
    }
void dischargePatient(Patient** head){
    char nombrePaciente[50];
    printf("Ingrese el nombre del paciente a dar de alta: ");
    scanf("%s", nombrePaciente);
    
    Patient* current = *head;   
    Patient* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, nombrePaciente) == 0) { // Encontró el paciente
            if (prev == NULL) { // Es el primer elemento de la lista
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("El paciente %s ha sido dado de alta.\n", nombrePaciente);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("El paciente %s no fue encontrado en la lista.\n", nombrePaciente);
}
void freePatients(Patient** lista){
    Patient* current = *lista;;
    while (current!= NULL) {
        Patient* next = current -> next;
        free(current);
        current = next;
    }
}
int main(){
    Patient* listaPacientes = NULL;
    int opcion = 0;
    while (opcion != 5) {
        printf("\nMenu:\n");
        printf("1. Agregar paciente\n");
        printf("2. Imprimir la lista de pacientes\n");
        printf("3 Dar de alta un paciente\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                addPatient(&listaPacientes);
                break;
            case 2:
                printPatient(listaPacientes);
                break;
            case 3:
                dischargePatient(&listaPacientes);
            case 4:
                freePatients(&listaPacientes);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    }
    return 0;
}