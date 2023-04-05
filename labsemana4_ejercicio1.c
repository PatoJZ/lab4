#include <stdio.h>
#define MAX_GLOBAL 1


typedef struct {
    char name[50];
    int age;
    int room;
    float temperature;
} Patient;

void addPatient(Patient arr[]){
    int i;
    for(i=0;i<MAX_GLOBAL;i++){
        printf("-----Paciente %d------\n",i+1);
        printf("Introduce el nombre del paciente %d: ",i+1);
        scanf("%s",&(arr[i].name));
        printf("Introduce la edad del paciente %d: ",i+1);
        scanf("%d",&(arr[i].age));
        printf("Introduce la habitacion del paciente %d: ",i+1);
        scanf("%d",&(arr[i].room));
        printf("Introduce la temperatura del paciente %d: ",i+1);
        scanf("%f",&(arr[i].temperature));
    }
}
void printPatient(Patient arr[]){
    for (int i = 0; i < MAX_GLOBAL; i++) {
        printf(" Nombre: %s\n Edad: %d\n Habitacion: %d\n Temperatura: %2f\n", arr[i].name, arr[i].age, arr[i].room, arr[i].temperature);
    }
}
int main(){

    Patient pacientes[MAX_GLOBAL];
    addPatient(pacientes);
    printPatient(pacientes);

    return 0;
}