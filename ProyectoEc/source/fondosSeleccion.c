#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"


char personaje[10];

void fondosSeleccion(){
			if(PERSONAJE == SONIC){
				BorrarPouAsesino(126,111,79);
				visualizarSonic();
				strcpy(personaje, "sonic");
			}
			else if(PERSONAJE == GOKU){
				BorrarPouAsesino(126,111,79);
				visualizarGoku();
				strcpy(personaje, "goku");
			}
			else if(PERSONAJE == KRATOS){
				visualizarKratos();
				strcpy(personaje, "pou");
				MostrarPouAsesino(126,111,79);
			}
}

