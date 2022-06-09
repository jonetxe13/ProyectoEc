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
  //pone el fondo del estado seleccion
	visualizarSeleccion();

	//prueba de tactil 
	touchPosition posPantalla;
	touchRead(&posPantalla);
  //si se toca dentro del rango de X y de Y y la variable tocado es 0 se cambia el personaje a una posicion hacia atras 
	if(posPantalla.px < 70 && posPantalla.px > 20 && posPantalla.py > 76 && posPantalla.py < 116 && tocado == 0){
			iprintf("\x1b[2J");
			PERSONAJE -= 1;
      //el personaje tiene que ser 0, 1 o 2 asi que lo limitamos asi
			if(PERSONAJE<0) PERSONAJE=2;
			else if(PERSONAJE>2) PERSONAJE=0;
			tocado = 1;
	}
	else if(tocado == 1 && posPantalla.px == 0 && posPantalla.py == 0){
			tocado = 0;
	}

	touchPosition posPantalla2;
	touchRead(&posPantalla2);
  //lo mismo que arriba pero para el boton de la izquierda y aqui el personaje lo movemos una posicion hacia delante
	if(posPantalla2.px > 185 && posPantalla2.px < 235 && posPantalla2.py > 76 && posPantalla2.py < 116 && tocado == 0){
			iprintf("\x1b[2J");
			PERSONAJE += 1;
			if(PERSONAJE<0) PERSONAJE=2;
			else if(PERSONAJE>2) PERSONAJE=0;
			tocado = 1;
	}
	else if(tocado == 1 && posPantalla2.px == 0 && posPantalla2.py == 0){
			tocado = 0;
	} 
	//seleccionar el personaje siguiente con la L y presionada actua como booleana para que solo se ejecute una vez
	if( TeclaDetectada() && TeclaPulsada()==L && presionada ==0){
		iprintf("\x1b[2J");
		presionada=1;
		PERSONAJE-=1;
		if(PERSONAJE<0) PERSONAJE=2;
		else if(PERSONAJE>2) PERSONAJE=0;

	}
	//seleccionar el personaje anterior con la R y presionada actua como booleana para que solo se ejecute una vez
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

  //se muestra el personaje seleccionado y se guarda en la variable personaje la String que corresponda
	if(PERSONAJE == SONIC){
		strcpy(personaje, "Sonic");
		MostrarSonic(1,111,79);
	}
	else if(PERSONAJE == GOKU){
		strcpy(personaje, "Goku");
		MostrarGoku(1,111,79);
	}
	else if(PERSONAJE == KRATOS){
		strcpy(personaje, "Pou");
		MostrarPouAsesino(1,111,79);
	}
}  
