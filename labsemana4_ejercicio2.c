    #include <stdio.h>
#define MAX_GlOBAL 10


typedef struct {
    char name[50];
    int age;
    int room;
    float temperature;
} Patient;

void addPatient(Patient arr[], int *max){
    if (max < *NumPatients && a )
        printf("-----Paciente %d------\n",max+1);
        printf("Introduce el nombre del paciente %d: ",max+1);
        scanf("%s",&(arr[max].name));
        printf("Introduce la edad del paciente %d: ",max+1);
        scanf("%d",&(arr[max].age));
        printf("Introduce la habitacion del paciente %d: ",max+1);
        scanf("%d",&(arr[max].room));
        printf("Introduce la temperatura del paciente %d: ",max+1);
        scanf("%f",&(arr[max].temperature));
}

void printPatient(Patient arr[], int max){
    for (int i = 0; i < max; i++) {
        printf(" Nombre: %s\n Edad: %d\n Habitacion: %d\n Temperatura: %2f\n", arr[i].name, arr[i].age, arr[i].room, arr[i].temperature);
    }
}
int main(){
    Patient pacientes[MAX_GlOBAL];
    int *NumPatients;
    printf("Ingrese el numero de pacientes a atender: ");
    scanf("%d",&*NumPatients);
    
    for(int i=0;i<NumPatients;i++){
        addPatient(pacientes,&NumPatients);
    }


    printPatient(pacientes, );

    return 0;
}