#include <nds.h>               //librería de la nds
#include <stdio.h>             //librería de entrada/salida estándar de C
#include <stdlib.h>            //librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>            //librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "juego.h"

void BorrarTodos(){
//Borrar Enemigos
    BorrarSonic(125,174,45);
    BorrarGoku(125,174,45);
    BorrarPouAsesino(125,174,45);
//Borrar Aliados
    BorrarSonic(126,40,140);
    BorrarGoku(126,40,140);
    BorrarPouAsesino(126,40,140);
}