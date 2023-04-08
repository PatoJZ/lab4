#include <stdio.h>
#include <string.h>
#define MAX_GlOBAL 10


typedef struct {
    char name[50];
    int age;
    int room;
    float temperature[3];
} Patient;

void addPatient(Patient arr[], int* NumPatients){
    if (*NumPatients <= MAX_GlOBAL ){
        printf("-----Paciente %d------\n",*NumPatients+1);
        printf("Introduce el nombre del paciente %d: ",*NumPatients+1);
        scanf("%s",&(arr[*NumPatients].name));
        printf("Introduce la edad del paciente %d: ",*NumPatients+1);
        scanf("%d",&(arr[*NumPatients].age));
        printf("Introduce la habitacion del paciente %d: ",*NumPatients+1);
        scanf("%d",&(arr[*NumPatients].room));
    }
    (*NumPatients)++;
}
void printPatient(Patient arr[], int max){
    printf(" --------\n Nombre: %s\n Edad: %d\n Habitacion: %d\n ", arr[max].name, arr[max].age, arr[max].room);
    for (int i = 0; i < 3; i++){
        printf("Temperatura %d: %f\n", i+1, arr[max].temperature[i]);
    }
}
void recordTemperatures(Patient arr[], int max){
    int i;
    for (i = 0; i < max; i++){
        for(int j = 0; j < 3; j++){
            printf("--------Temperatura %d--------\n",j+1);
            printf("Introduce la temperatura del paciente %d: ",i+1);
            scanf("%f",&(arr[i].temperature[j]));
        }
    }
}
int main(){
    Patient pacientes[MAX_GlOBAL];
    int* NumPatients = 0;
    int temp = 0;
    printf("Ingrese el numero de pacientes a atender: ");
    scanf("%d",&temp);
    
    for(int i=0;i<temp;i++){
        addPatient(pacientes, &NumPatients);
    }
    recordTemperatures(pacientes, temp);

    for(int i=0; i<temp; i++){
        printPatient(pacientes,i);
    }
    

    return 0;
}