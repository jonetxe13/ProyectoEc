#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "EstadoSeleccion.h"

int Mapa = rand()%3;

void FondoPelea(){
    if(Mapa == 0){
        visualizarPelea1();
    }
    else if(Mapa == 1){
        visualizarPelea2();
    }
    else if(Mapa == 2){
        visualizarPelea3();
    }
}