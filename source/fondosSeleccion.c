#include <nds.h>               //librería de la nds
#include <stdio.h>             //librería de entrada/salida estándar de C
#include <stdlib.h>            //librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>            //librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

void fondosSeleccion(){
    //pone los sprites en el centro de la pantalla en el estado seleccion
    if(PERSONAJE == SONIC){
        BorrarPouAsesino(1,111,79);
        MostrarSonic(1,111,79);
    }
    else if(PERSONAJE == GOKU){
        BorrarSonic(1,111,79);
        BorrarPouAsesino(1,111,79);
    }
    else if(PERSONAJE == KRATOS){
        BorrarSonic(1,111,79);
        MostrarPouAsesino(1,111,79);
    }
}  
