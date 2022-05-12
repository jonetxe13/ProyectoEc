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
int tocado = 0;

void Seleccion(){
	HP1 =100;
	HP2 =100;
	visualizarSeleccion();

	//prueba de tactil 
	touchPosition posPantalla;
	touchRead(&posPantalla);
	if(posPantalla.px < 70 && posPantalla.px > 20 && posPantalla.py > 76 && posPantalla.py < 116 && tocado == 0){
			iprintf("\x1b[2J");
			PERSONAJE += 1;
			if(PERSONAJE<0) PERSONAJE=2;
			else if(PERSONAJE>2) PERSONAJE=0;
			tocado = 1;
	}
	else if(tocado == 1 && posPantalla.px == 0 && posPantalla.py == 0){
			tocado = 0;
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
		strcpy(personaje, "Sonic");
		MostrarSonic(126,111,79);
	}
	else if(PERSONAJE == GOKU){
		strcpy(personaje, "Goku");
		MostrarGoku(126,111,79);
	}
	else if(PERSONAJE == KRATOS){
		strcpy(personaje, "Pou");
		MostrarPouAsesino(126,111,79);
	}
}  
