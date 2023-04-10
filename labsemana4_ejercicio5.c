#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Patient{
    char name[50];
    int age;
    int room;
    float temperature;
    struct Patient* next;
} Patient;

typedef struct Nodo {
    Patient* paciente;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* head;
    Nodo* last;
} Cola;

void addPatient(Patient** head, char *name, int age, int room) {
    Patient* newPatient = malloc(sizeof(Patient));
    strcpy(newPatient->name, name);
    newPatient->age = age;
    newPatient->room = room;
    newPatient -> next = *head;
    *head = newPatient;
}
void printPatient(Patient* head){
    Patient* current = head;
    while (current!= NULL) {
        printf(" --------\n Nombre: %s\n Edad: %d\n Habitacion: %d\n", current -> name, current -> age, current -> room);
        current = current -> next;
    }
}
void getNextPatient(Cola* cola) { 
    if (cola->head == NULL) {
        printf("La cola esta vacia.\n");
    } else {
        printf("Siguiente paciente en la cola:\n");
        printf("Nombre: %s\n", cola->head->paciente->name);
        printf("Edad: %d\n", cola->head->paciente->age);
        printf("Habitacion: %d\n", cola->head->paciente->room);
    }
}
int getQueueSize(Cola* cola) {
    int size = 0;
    Nodo* nodoActual = cola->head;
    while (nodoActual != NULL) {
        size++;
        nodoActual = nodoActual->next;
    }
    return size;
}
void getLeftPatients(Cola* cola) {
    int left = 0;
    char nombre[50];
    printf("Ingrese el nombre del paciente: ");
    scanf("%s", nombre);
    Nodo* nodoActual = cola->head;
    while (nodoActual != NULL) {
        if (strcmp(nodoActual->paciente->name, nombre) == 0) {
            break; // Encontramos al paciente en la cola, salimos del ciclo
        }
        left++;
        nodoActual = nodoActual->next;
    }
    printf("Quedan %d pacientes para que pueda atenderse", left);
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
void enqueuePatient(Cola* cola, Patient* paciente){
    Nodo* nuevoNodo = (Nodo*) malloc(sizeof(Nodo));
    nuevoNodo->paciente = paciente;
    nuevoNodo->next = NULL;
    
    if (cola->head == NULL) { // La cola estaba vacía
        cola->head = nuevoNodo;
        cola->last = nuevoNodo;
    } else {
        cola->last->next = nuevoNodo;
        cola->last = nuevoNodo;
    }
}
void dequeue(Cola* cola) {
    if (cola->head == NULL) {
        printf("La cola esta vacia.\n");
    } else {
        Nodo* nodoAEliminar = cola->head;
        cola->head = nodoAEliminar->next;
        free(nodoAEliminar);
        printf("Se elimino al paciente en el head de la cola.\n");
    }
}
int main(int argc, char *argv[]){
    Patient* listaPacientes = NULL;
    Cola colapacientes = {.head = NULL, .last = NULL};
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_name);
        return 1;
    }
    char line[100];
    while (fgets(line, 100, file) != NULL) {
        char *token;
       
        token = strtok(line, ",");
        char name[50];
        strcpy(name, token);
        
        int age = atoi(strtok(NULL, ","));
        int room = atoi(strtok(NULL, ","));
        float temperature = atof(strtok(NULL, ","));
        printf("%s, age:%d T°:%.1f ROOM:%d\n",name,age,temperature,room);
        addPatient(&listaPacientes, name, age, room);
        enqueuePatient(&colapacientes, listaPacientes);
    }
    fclose(file);
    int opcion = 0;
    while (opcion != 5) {
        printf("----------------------------------------\n");
        printf("\nMenu:\n");
        printf("1. Imprimir la lista de pacientes\n");
        printf("2. Dar de alta un paciente\n");
        printf("3. Sacar de la cola de la lista de pacientes\n");
        printf("4. Saber el siguiente en la lista de pacientes\n");
        printf("5. Saber Cuantos pacientes hay en cola\n");
        printf("6. Cuantos pacientes faltan para atenderse\n");
        printf("7. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printPatient(listaPacientes);
                break;
            case 2:
                dischargePatient(&listaPacientes);
                break;
            case 3:
                dequeue(&colapacientes);
                break;
            case 4:
                getNextPatient(&colapacientes);
                break;
            case 5:
                getQueueSize(&colapacientes);
                break;
            case 6:
                getLeftPatients(&colapacientes);
                break;
            case 7:
                freePatients(&listaPacientes);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    }
    return 0;
}