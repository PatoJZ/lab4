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

typedef struct Nodo {
    Patient* paciente;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* head;
    Nodo* last;
} Cola;


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
int main(){
    Patient* listaPacientes = NULL;
    Cola colapacientes = {.head = NULL, .last = NULL};
    int opcion = 0;
    while (opcion != 5) {
        printf("----------------------------------------\n");
        printf("\nMenu:\n");
        printf("1. Agregar paciente y ponerlo a la cola\n");
        printf("2. Imprimir la lista de pacientes\n");
        printf("3. Dar de alta un paciente\n");
        printf("4. Sacar de la cola de la lista de pacientes\n");
        printf("5. Saber el siguiente en la lista de pacientes\n");
        printf("6. Saber Cuantos pacientes hay en cola\n");
        printf("7. Cuantos pacientes faltan para atenderse\n");
        printf("8. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                addPatient(&listaPacientes);
                enqueuePatient(&colapacientes, listaPacientes);
                break;
            case 2:
                printPatient(listaPacientes);
                break;
            case 3:
                dischargePatient(&listaPacientes);
                break;
            case 4:
                dequeue(&colapacientes);
                break;
            case 5:
                getNextPatient(&colapacientes);
                break;
            case 6:
                getQueueSize(&colapacientes);
                break;
            case 7:
                getLeftPatients(&colapacientes);
                break;
            case 8:
                freePatients(&listaPacientes);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    }
    return 0;
}