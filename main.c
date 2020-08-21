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

    for (; aux1 < final; ++aux1) {
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
    paciente * nueva = (paciente *) malloc(sizeof(paciente));
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

    //Va pasando por todas las direcciones hasta que encuentra una disponible, cuando la encuentra se sale
    while(aux < final && aux->disponible != 1){
        aux++;
    }
    if(aux < final){
        aux -> p = nueva;
        aux -> disponible = 0;
        printf("Nuevo paciente asignado: %s %s Edad: %d Telefono: %s Cama asignada: %d\n",(aux->p) -> nombre, (aux->p) -> apellidos,  (aux->p)-> edad, (aux->p) -> telefono, aux->id);
    }
    else{
        hospital = (cama *) realloc(hospital, sizeof(cama) * (total_camas + 1));
        aux = hospital + total_camas + 1;
        aux -> p = nueva;
        aux -> disponible = 0;
        ++total_camas;
        aux -> id = total_camas;
        printf("Nuevo paciente asignado: %s %s Edad: %d Telefono: %s Cama asignada: %d\n",nueva -> nombre, nueva -> apellidos,  nueva -> edad, nueva -> telefono, aux->id);
      }
    free(nueva->nombre);
    free(nueva->apellidos);
    free(nueva->telefono);
    free(nueva);
}

void camaPaciente(cama *hospital,int total_camas)
{
  int check_cama;

  printf("Ingresa el ID de la cama de la que deseas conocer su disponibilidad y/0 paciente asignado\n");
  scanf("%d",&check_cama);

  cama * aux = hospital;
  cama * final = hospital + total_camas;

  while(aux < final && aux->id != check_cama){
      aux++;
  }
  if(aux < final){
      if(aux -> disponible == 1){
        printf("La cama con ID: %d se encuentra disponible",aux->id);
      } else{
        printf("La cama con ID: %d se encuentra ocupada por el paciente: %s",aux->id,(aux->p)->nombre); //SEGMENTATION FAULT
      }
    } else{
    printf("El identificador de cama no existe");
  }
}

void altaPaciente(cama *hospital,int total_camas)
{
  printf("Dar de alta paciente por número de cama\n");
  int check_cama;

  printf("Ingresa el ID de la cama\n");
  scanf("%d",&check_cama);

  cama * aux = hospital;
  cama * final = hospital + total_camas;

  while(aux < final && aux->id != check_cama){
      aux++;
  }
  if(aux < final){
      aux -> disponible = 1;//Liberar cama
      //Eliminar paciente, estos frees dan SEGMENTATION FAULT
      free((aux->p)->nombre);
      free((aux->p)->apellidos);
      free((aux->p)->telefono);
      free(aux->p);
    } else{
    printf("El identificador de cama no existe");
  }
}

void listaPacientes(cama *hospital, int total_camas)
{
     printf("Lista de pacientes\n");
     cama * aux = hospital;
     cama * final = hospital + total_camas;
     while(aux < final){
       printf("%10d %10d\n", aux->id, aux->disponible);
       //printf("%10d %10d %10s\n", aux->id, aux->disponible, (aux->p)->nombre); Se rompe por alguna extraña razón del universo
      aux++;
     }
}

void camasDisp(cama *hospital,int total_camas)
{
  cama * aux = hospital;
  cama * final = hospital + total_camas;
  int contador = 0;
  while(aux < final){
    if(aux->disponible == 1){
      contador++;
    }
  aux++;
  }
  printf("Número de camas disponibles: %d\n",contador);
  printf("Número de camas ocupadas: %d\n",total_camas-contador);

}
