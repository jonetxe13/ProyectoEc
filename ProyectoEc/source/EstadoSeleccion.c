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


char personaje[10];

void Seleccion(){
	HP1 =100;
	HP2 =100;
	int tocado = 0;
	visualizarSeleccion();

	//prueba de tactil *no va bn tamos en ello*
	touchPosition posPantalla;
	if(tocado == 0){
		touchRead(&posPantalla);
		if(posPantalla.px < 90 && posPantalla.px > 20 && tocado == 0){
			iprintf("\x1b[2J");
			PERSONAJE += 1;
			if(PERSONAJE<0) PERSONAJE=2;
			else if(PERSONAJE>2) PERSONAJE=0;
		}
		tocado = 1;
	}

	//seleccionar personaje con la L y con la R
	if( TeclaDetectada() && TeclaPulsada()==L && presionada ==0){
		iprintf("\x1b[2J");
		presionada=1;
		PERSONAJE-=1;
		if(PERSONAJE<0) PERSONAJE=2;
		else if(PERSONAJE>2) PERSONAJE=0;

	}
	else if(TeclaDetectada() && TeclaPulsada()==R && presionada==0){
		iprintf("\x1b[2J");
		presionada=1;
		PERSONAJE+=1;
		if(PERSONAJE<0) PERSONAJE=2;
		else if(PERSONAJE>2) PERSONAJE=0;

	}
	else if(presionada==1 && TeclaDetectada()==0) {
		iprintf("\x1b[2J");
		presionada=0;
	}

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
