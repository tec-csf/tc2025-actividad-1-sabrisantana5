//
//  main.c
//  Actividad individual 1: Aritmética de apuntadores
//  Se quiere desarrollar una aplicación para llevar el control de pacientes ingresados en un hospital.
//  Created by Sabrina Lizette Santana Lazos on 8/18/20.
//  Copyright © 2020 Sabrina Lizette Santana Lazos. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 5 //Opciones menu
#define C 5 //Numero de camas extra

typedef struct
{
    char * nombre;
    char * apellidos;
    int edad;
    char * telefono;
} paciente;

typedef struct
{
    int id;
    int disponible;
    paciente * p;
} cama;

typedef void (* menu)();

void incorporarPaciente(cama *hospital,int total_camas);
void camaPaciente(cama *hospital,int total_camas);
void altaPaciente(cama *hospital,int total_camas);
void listaPacientes(cama *hospital,int total_camas);
void camasDisp(cama *hospital,int total_camas);

int main(int argc, const char * argv[]) {

    //Inicializar menu y pacientes
    int opc = -1;
    menu * opcs = (menu *) malloc(sizeof(menu)*N);
    cama * hospital = (cama *) malloc(sizeof(cama)*10);
    int total_camas = 1;
    hospital -> id = 1;
    hospital -> disponible = 1;

    //Opciiones de menu
    *opcs = incorporarPaciente;
    *(opcs+1) = camaPaciente;
    *(opcs+2) = altaPaciente;
    *(opcs+3) = listaPacientes;
    *(opcs+4) = camasDisp;

    //Menu
    while (opc != 0) {
        printf("\n1. Incorporar paciente \n2. Ingresar ID de cama \n3. Dar de alta paciente por número de cama\n4. Lista de pacientes \n5. Número de camas disponibles y ocupadas\n0. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opc);

        if (opc > 0 && opc <= N) {
            (*(opcs[opc-1]))(hospital , total_camas);
        }
    }
    //Liberar memoria
    cama * aux1 = hospital;
    cama * final = hospital + total_camas;

    for (aux1 = hospital; aux1 < final; ++aux1) {
        free(aux1-> p ->nombre);
        free(aux1-> p -> apellidos);
        free(aux1-> p -> telefono);
        free(aux1->p);
    }
    free(opcs);
    free(hospital);
    return 0;
}

void incorporarPaciente(cama * hospital, int total_camas)
{
    printf("Inicio total camas: %d",total_camas);
    paciente * nueva = (paciente *) malloc(sizeof(paciente)*1);
    cama * aux = hospital;
    cama * final = hospital + total_camas;

    nueva->nombre  = (char *) malloc(sizeof(char)*25);
    nueva->apellidos = (char *) malloc(sizeof(char)*40);
    nueva->telefono = (char *) malloc(sizeof(char)*30);

    //Pedir datos
    printf("Incorporación de paciente, por favor ingrese los siguientes datos:\n");
    printf("Nombre: ");
    scanf("%s",nueva->nombre );
    printf("Apellidos ");
    scanf("%s",nueva->apellidos);
    printf("Edad: ");
    scanf("%d",&nueva->edad);
    printf("Telefono: ");
    scanf("%s",nueva->telefono);


    while(aux < final && aux->disponible != 1){
        aux++;
    }
    if(aux < final){
        aux -> p = nueva;
        aux -> disponible = 0;
        printf("Nuevo paciente asignado: %s %s Edad: %d Telefono: %s Cama asignada: %d\n",nueva -> nombre, nueva -> apellidos,  nueva -> edad, nueva -> telefono, aux->id);
    } else{
      printf("Por ahora se va a sin el realloc");
        aux = hospital + total_camas + 1;
        aux -> p = nueva;
        aux -> disponible = 0;

      /*
        hospital = (cama *) realloc(hospital, sizeof(cama) * (total_camas + 1));
        printf("Cuando no hay usuario total camas %d",total_camas);
        aux = hospital + total_camas + 1;
        aux -> p = nueva;
        aux -> disponible = 0;
        ++total_camas;
        printf("El camas mas mas %d",total_camas);
        aux -> id = total_camas;
        printf("Nuevo paciente asignado: %s %s Edad: %d Telefono: %s Cama asignada: %d\n",nueva -> nombre, nueva -> apellidos,  nueva -> edad, nueva -> telefono, aux->id);
        /*
         total_camas += 1;
         *aux++;
         aux -> id = total_camas;
         aux -> disponible = 1;
         */
    }
    free(nueva->nombre);
    free(nueva->apellidos);
    free(nueva->telefono);
    free(nueva);
}

void camaPaciente(cama *hospital,int total_camas)
{
    /*
     int check_cama;

     printf("Ingresa el ID de la cama de la que deseas conocer su disponibilidad y/0 paciente asignado\n");
     scanf("%d",&check_cama);

     cama * ic = camas;
     cama * fc = camas + h.numeroCamas;
     int encontrado = 0;
     for(;ic<=fc;ic++){
     if((ic -> identificador) == check_cama){
     printf("La cama con identificador: %d \n",ic -> identificador);
     if((ic -> estatus) == 1){
     printf("Se encuentra disponible \n");
     encontrado = 1;
     }
     if((ic -> estatus) == 0){
     persona * inicio = pacientes;
     persona * final = pacientes + h.noPacientes;
     for (;inicio<=final;inicio++) {
     if((inicio -> ident_cama)->identificador == check_cama){
     printf("se encuentra ocupada por el paciente: %s %s . Edad: %s Telefono: %s \n",inicio -> nombre,inicio -> apellidos,inicio->edad,inicio->telefono);
     encontrado = 1;
     }
     }
     }
     break;
     }
     }
     if(encontrado == 0){
     printf("El identificador de cama no se encuentra registrado\n");
     }
     */
}
void altaPaciente(cama *hospital,int total_camas)
{
    /*
     printf("Dar de alta paciente por número de cama\n");
     int check_cama;

     printf("Ingresa el ID de la cama\n");
     scanf("%d",&check_cama);

     cama * ic = camas;
     cama * fc = camas + h.numeroCamas;
     int encontrado = 0;
     for(;ic<=fc;ic++){
     if((ic -> identificador) == check_cama){
     encontrado = 1;
     ic -> estatus = 1;
     persona * inicio = pacientes;
     persona * final = pacientes + h.noPacientes;
     for (;inicio<=final;inicio++) {
     if((inicio -> ident_cama)->identificador == check_cama){
     //Eliminar persona
     free(inicio); //Por el momento no sirve
     printf("El paciente: %s %s se ha dado de alta exitosamente \n",inicio -> nombre,inicio -> apellidos);
     }
     }
     }
     }
     if(encontrado==0){
     printf("El identificador de cama no se encuentra registrado\n");
     }
     */
}

void listaPacientes(cama *hospital, int total_camas)
{
    /*
     printf("Lista de pacientes");
     cama * aux = hospital;
     cama * final = hospital + total_camas;
     while(aux < final && aux->p){
     printf("Nombre: %s\tApellidos: %s\tEdad: %s\tTeléfono: %s\t Cama asignada: %d\n", (aux->p) -> nombre, (aux->p ) -> apellidos, (aux->p)-> edad,(aux->p) -> telefono, aux->id);
     aux++;
     }
     */
    /*
     printf("Lista de pacientes con cama asignada\n");
     if( h.noPacientes == 0){
     printf("No se encuentran pacientes registrados\n");
     } else {
     persona * inicio = pacientes;
     persona * final = pacientes + h.noPacientes;
     for (;inicio<=final;inicio++) {
     printf("Nombre: %s\tApellidos: %s\tEdad: %s\tTeléfono: %s\t Cama asignada: %d\n", inicio -> nombre, inicio -> apellidos, inicio -> edad,inicio -> telefono, (final -> ident_cama)->identificador);
     }
     }
     */
}

void camasDisp(cama *hospital,int total_camas)
{
    /*
     printf("Número de camas disponibles y ocupadas\n");
     cama * ic = camas;
     cama * fc = camas + h.numeroCamas;
     int contador = 0;
     for(;ic<=fc;ic++){
     if((ic -> estatus) == 1){
     contador++;
     }
     }
     printf("Número de camas disponibles: %d\n",contador);
     printf("Número de camas ocupadas: %d\n",(h.numeroCamas-contador));
     */
}
