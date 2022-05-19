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
//Borrar Ataques
    BorrarAtaque(12,posx,posy);
    BorrarAtaque(12,pos2x,pos2y);
//Borrar Enemigos
    BorrarSonic(2,174,45);
    BorrarGoku(2,174,45);
    BorrarPouAsesino(2,174,45);
//Borrar Aliados
    BorrarSonic(1,40,140);
    BorrarGoku(1,40,140);
    BorrarPouAsesino(1,40,140);
//BorrarSeleccion
    BorrarSonic(1,111,79);
    BorrarGoku(1,111,79);
    BorrarPouAsesino(1,111,79);
}
