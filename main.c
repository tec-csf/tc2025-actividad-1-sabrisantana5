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

//ESTRUCTURA de paciente
typedef struct
{
    char * nombre;
    char * apellidos;
    int edad;
    char * telefono;
} paciente;

//ESTRUCTURA de cama
typedef struct
{
    int id;
    int disponible;
    paciente * p;
} cama;

//MENU
typedef void (* menu)(cama *, int *);

//Funciones a implementar
void incorporarPaciente(cama *hospital,int * total_camas);
void camaPaciente(cama *hospital,int * total_camas);
void altaPaciente(cama *hospital,int * total_camas);
void listaPacientes(cama *hospital,int * total_camas);
void camasDisp(cama *hospital,int * total_camas);

//Main
int main(int argc, const char * argv[]) {

    //Inicializar menu y camas
    int opc = -1;
    menu * opcs = (menu *) malloc(sizeof(menu)*N);
    cama * hospital = (cama *) malloc(sizeof(cama)*2);
    int total_camas = 2;
    hospital -> id = 1;
    hospital -> disponible = 1;
    (hospital + 1 )-> id = 2;
    (hospital + 1 )-> disponible = 1;

    //Opciones de menu
    *opcs = incorporarPaciente;
    *(opcs+1) = camaPaciente;
    *(opcs+2) = altaPaciente;
    *(opcs+3) = listaPacientes;
    *(opcs+4) = camasDisp;

    //Menu con apuntadores
    while (opc != 0) {
        printf("\n1. Incorporar paciente \n2. Ingresar ID de cama \n3. Dar de alta paciente por número de cama\n4. Lista de pacientes \n5. Número de camas disponibles y ocupadas\n0. Salir\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opc);

        if (opc > 0 && opc <= N) {
            (*(opcs[opc-1]))(hospital , &total_camas);
        }
    }

    //Liberar memoria , por el momento da segmentation error

    cama * aux1 = hospital;
    cama * final = hospital + total_camas;
    for (; aux1 < final; ++aux1) {
      if(aux1->disponible!=1){
        free(aux1-> p ->nombre);
        free(aux1-> p -> apellidos);
        free(aux1-> p -> telefono);
        free(aux1->p);
      }
        else{
        free(aux1->p);
      }
    }
    free(opcs);
    free(hospital);


    return 0;
}

//Función para incorporar paciente al hospital
void incorporarPaciente(cama * hospital, int * total_camas)
{
    //Asignar espacio para el nuevo paciente
    paciente * nueva = (paciente *) malloc(sizeof(paciente));

    //
    cama * aux = hospital;
    cama * final = hospital + *total_camas;

    //Asignar espacio para los atributos del nuevo paciente
    nueva->nombre  = (char *) malloc(sizeof(char)*25);
    nueva->apellidos = (char *) malloc(sizeof(char)*40);
    nueva->telefono = (char *) malloc(sizeof(char)*30);

    //Pedir datos
    printf("Incorporación de paciente, por favor ingrese los siguientes datos:\n");
    printf("Nombre: ");
    scanf("%s",nueva->nombre );
    printf("Apellidos: ");
    scanf("%s",nueva->apellidos);
    printf("Edad: ");
    scanf("%d",&nueva->edad);
    printf("Telefono: ");
    scanf("%s",nueva->telefono);

    //Pasar por cada cama del hospital hasta que encuentra una disponible, cuando la encuentra se sale
    while(aux < final && aux->disponible != 1){
        aux++;
    }

    //Asignamos un puntero extra ya que no se estaba haciendo bien el realloc en el puntero de hospital
    cama * temp_hospital;

    //Si encontró una cama disponible asignarla al paciente
    if(aux < final){
        aux -> p = nueva;
        aux -> disponible = 0;
        printf("Nuevo paciente asignado: %s %s Edad: %d Telefono: %s Cama asignada: %d\n",(aux->p) -> nombre, (aux->p) -> apellidos,  (aux->p)-> edad, (aux->p) -> telefono, aux->id);
    }
    //Si no encontró una cama disponible agregar 5 y asignar la primera disponible al paciente
    else{
        temp_hospital = (cama *) realloc(hospital, sizeof(cama) * (*total_camas + 5));
        aux = hospital + *total_camas;
        aux -> p = nueva;
        aux -> disponible = 0;
        aux -> id = *total_camas + 1;
        printf("Nuevo paciente asignado: %s %s Edad: %d Telefono: %s Cama asignada: %d\n",nueva -> nombre, nueva -> apellidos,  nueva -> edad, nueva -> telefono, aux->id);

        //Asignar id a las nuevas camas
        (aux + 1 ) -> id = *total_camas + 2;
        (aux + 1 )-> disponible = 1;
        (aux + 2 )-> id = *total_camas + 3;
        (aux + 2 )-> disponible = 1;
        (aux + 3 )-> id = *total_camas + 4;
        (aux + 3 )-> disponible = 1;
        (aux + 4 )-> id = *total_camas + 5;
        (aux + 4 )-> disponible = 1;

        //Incrementar total de camas
        *total_camas = *total_camas + 5;

      }
      hospital = temp_hospital;
}

//Función para
void camaPaciente(cama *hospital,int * total_camas)
{

  int check_cama;

  printf("Ingresa el ID de la cama de la que deseas conocer su disponibilidad y/0 paciente asignado\n");
  scanf("%d",&check_cama);

  cama * aux = hospital;
  cama * final = hospital + *total_camas;

  while(aux < final && aux->id != check_cama){
      aux++;
  }
  if(aux < final){
      if(aux -> disponible == 1){
        printf("La cama con ID: %d se encuentra disponible \n",aux->id);
      } else{
        printf("La cama con ID: %d se encuentra ocupada por el paciente: %s \n",aux->id,(aux->p)->nombre); //SEGMENTATION FAULT
      }
    } else{
    printf("El identificador de cama no existe\n");
  }

}

void altaPaciente(cama *hospital,int * total_camas)
{

  printf("Dar de alta paciente por número de cama\n");
  int check_cama;

  printf("Ingresa el ID de la cama\n");
  scanf("%d",&check_cama);

  cama * aux = hospital;
  cama * final = hospital + *total_camas;

  while(aux < final && aux->id != check_cama){
      aux++;
  }
  if(aux < final){
      if(aux -> disponible == 1){
        printf("La cama especificada se encuentra disponible\n");
      } else{
        aux -> disponible = 1;//Liberar cama
        free(aux->p->nombre);
        free(aux->p->apellidos);
        free(aux->p->telefono);
        free(aux->p);
        printf("El paciente se ha dado de alta correctamente\n");
      }
    } else{
    printf("El identificador de cama no existe\n");
  }

}

void listaPacientes(cama *hospital, int *total_camas)
{
     printf("Lista de pacientes\n");
     cama * aux = hospital;
     cama * final = hospital + *total_camas;
     while(aux < final){
       if(aux->disponible!=1){
       printf("Id de cama: %d Nombre: %s Apellidos: %s Telefono: %s\n", aux->id, aux->p->nombre, aux->p->apellidos, aux->p->telefono);
      }
      aux++;
     }
}

void camasDisp(cama *hospital,int * total_camas)
{

  cama * aux = hospital;
  cama * final = hospital + *total_camas;
  int contador = 0;
  while(aux < final){
    if(aux->disponible == 1){
      contador++;
    }
  aux++;
  }
  printf("Número de camas disponibles: %d\n",contador);
  printf("Número de camas ocupadas: %d\n",*total_camas-contador);

}
