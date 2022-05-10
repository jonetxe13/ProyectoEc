#include <nds.h>               //librería de la nds
#include <stdio.h>             //librería de entrada/salida estándar de C
#include <stdlib.h>            //librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>            //librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"


char personaje[10];

void fondosSeleccion(){
    if(PERSONAJE == SONIC){
        BorrarGoku(126,111,79);
        BorrarPouAsesino(126,111,79);
        strcpy(personaje, "Sonic");
        MostrarSonic(126,111,79);
    }
    else if(PERSONAJE == GOKU){
        BorrarSonic(126,111,79);
        BorrarPouAsesino(126,111,79);
        strcpy(personaje, "Goku");
        MostrarGoku(126,111,79);
    }
    else if(PERSONAJE == KRATOS){
        BorrarGoku(126,111,79);
        BorrarSonic(126,111,79);
        strcpy(personaje, "Pou");
        MostrarPouAsesino(126,111,79);
    }
}  
