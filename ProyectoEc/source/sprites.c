/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxsonic;
u16* gfxPouAsesino;
u16* gfxSonic;
u16* gfxGoku;

/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void memoriaReserba()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxsonic = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxPouAsesino=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfxSonic=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfxGoku=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(255,0,0); // 1 = Rojo
	SPRITE_PALETTE[2] = RGB15(0,255,255); // 2 = Amarillo
	SPRITE_PALETTE[3] = RGB15(255,255,255); // 3 = Blanco
	SPRITE_PALETTE[4] = RGB15(0,255,0); // 4 = Verde
	SPRITE_PALETTE[5] =	RGB15(0,0,255); // 5 = Blanco
	SPRITE_PALETTE[6]; // 6 = Negro
	SPRITE_PALETTE[7] = RGB15(0,255,255); // 7 = Cyan
	SPRITE_PALETTE[8] = RGB15(255, 0, 255); // 8 = Magenta 
	SPRITE_PALETTE[9] = RGB15(184,184,184); // 9 = Gris 
	SPRITE_PALETTE[10] = RGB15(216,216,216); // 10 = Gris Claro
	SPRITE_PALETTE[11] = RGB15(102,102,102); // 11 = Gris Oscuro
	SPRITE_PALETTE[12] = RGB15(255,150,0); // 12 = Naranja
	SPRITE_PALETTE[13] = RGB15(169,0,0);// 13 = Granate
	SPRITE_PALETTE[14] = RGB15(146,68,0);// 14 = Marron
	SPRITE_PALETTE[15] = RGB15(133,5,227);// 15 = Morado
	SPRITE_PALETTE[16] = RGB15(215,161,255);// 16 = Lila
	SPRITE_PALETTE[17] = RGB15(244,112,255);// 17 = Rosa
	SPRITE_PALETTE[18] = RGB15(112,222,255);// 18 = Azul Claro
	SPRITE_PALETTE[19] = RGB15(0,34,121);// 19 = Azul Marino
	SPRITE_PALETTE[20] = RGB15(0,121,93);// 20 = Verde Azulado
	SPRITE_PALETTE[21] = RGB15(1,84,26);// 21 = Verde Oscuro
	SPRITE_PALETTE[22] = RGB15(92,127,19);// 22 = Verde Oliva
	SPRITE_PALETTE[23] = RGB15(181,255,114);// 23 = Verde Claro
	SPRITE_PALETTE[24] = RGB15(246,253,135);// 24 = Amarillo Claro
}	


/* definición de un sprite de 16x16 píxeles para dibujar un rombo */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho. */

u8 sonic[256] = 
{
	0,0,0,6,6,6,6,6,
        6,6,0,0,6,6,0,0,	//	0,0,0,6,6,6,6,6, 6,6,0,0,6,6,0,0,
	0,0,6,6,5,5,5,5,
        5,5,6,6,5,5,6,0,	//	0,0,6,6,5,5,5,5, 5,5,6,6,5,5,6,0,
	0,0,0,0,6,5,6,24,
        5,5,5,5,5,5,5,6,	//	0,0,0,0,6,5,6,24, 5,5,5,5,5,5,5,6,
	0,0,0,6,5,5,6,24,
        5,3,3,5,5,5,5,6,	//	0,0,0,6,5,5,6,24, 5,3,3,5,5,5,5,6,
 
	0,0,6,5,5,5,5,5,
        3,3,3,3,5,3,6,0,	//	0,0,6,5,5,5,5,5, 3,3,3,3,5,3,6,0,
	0,6,6,6,6,6,5,5,
        3,3,3,6,5,3,6,0,	//	0,6,6,6,6,6,5,5, 3,3,3,6,5,3,6,0,
	0,0,0,0,6,5,5,3,
        3,3,6,3,6,6,6,0,	//	0,0,0,0,6,5,5,3, 3,3,6,3,6,6,6,0,
	0,0,0,6,5,5,5,5,
        24,3,3,3,24,24,6,2,	//	0,0,0,6,5,5,5,5, 24,3,3,3,24,24,6,2,

	0,0,6,6,6,6,6,6,
        24,24,24,24,24,24,6,0,	//	0,0,6,6,6,6,6,6, 24,24,24,24,24,24,6,0,
	0,0,0,0,0,0,6,5,
        6,6,6,6,6,6,6,6,	//	0,0,0,0,0,0,6,5, 6,6,6,6,6,6,6,6,
	0,0,0,0,0,6,5,6,
        6,5,24,24,6,3,3,6,	//	0,0,0,0,0,6,5,6, 6,5,24,24,6,3,3,6,
	0,0,0,0,0,6,6,3,
        3,6,24,24,6,3,3,6,	//	0,0,0,0,0,6,6,3, 3,6,24,24,6,3,3,6,

	0,0,0,0,0,0,6,3,
        3,6,5,24,6,3,6,0,	//	0,0,0,0,0,0,6,3, 3,6,5,24,6,3,6,0,
	0,0,0,0,0,0,6,6,
        6,6,6,6,6,6,0,0,	//	0,0,0,0,0,0,6,6, 6,6,6,6,6,6,0,0,
	0,0,0,0,0,6,1,1,
        1,3,6,1,1,3,6,0,	//	0,0,0,0,0,6,1,1, 1,3,6,1,1,3,6,0,
	0,0,0,0,0,6,1,1,
        3,1,1,6,3,1,1,6,	//	0,0,0,0,0,6,1,1, 3,1,1,6,3,1,1,6,
};
u8 ataque[1024] =
{
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	19 ,	0 ,	19 ,	19 ,	19 ,	0 , 19 ,	19 ,	5 ,	19 ,	19 ,	19 ,	19 ,	19 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 19 ,	19 ,	19 ,	0 ,	0 ,	0 ,	0 ,	0 , 19 ,	5 ,	5 ,	19 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	5 ,	5 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	5 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	5 , 0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	19 ,
19 ,	19 ,	19 ,	19 ,	5 ,	19 ,	19 ,	5 , 5 ,	5 ,	19 ,	19 ,	19 ,	5 ,	19 ,	19 , 5 ,	5 ,	5 ,	5 ,	19 ,	5 ,	5 ,	5 , 19 ,	19 ,	5 ,	18 ,	19 ,	18 ,	19 ,	5 ,
5 ,	5 ,	19 ,	5 ,	5 ,	5 ,	5 ,	18 , 5 ,	5 ,	5 ,	18 ,	5 ,	18 ,	18 ,	5 , 18 ,	5 ,	18 ,	5 ,	5 ,	3 ,	18 ,	3 , 5 ,	18 ,	5 ,	18 ,	18 ,	3 ,	3 ,	3 ,
19 ,	5 ,	5 ,	19 ,	19 ,	0 ,	0 ,	0 , 19 ,	19 ,	19 ,	5 ,	5 ,	19 ,	19 ,	0 , 19 ,	5 ,	5 ,	5 ,	5 ,	5 ,	19 ,	0 , 18 ,	5 ,	19 ,	5 ,	5 ,	19 ,	19 ,	19 ,
5 ,	5 ,	18 ,	5 ,	19 ,	19 ,	19 ,	0 , 18 ,	18 ,	5 ,	19 ,	5 ,	19 ,	19 ,	19 , 5 ,	18 ,	18 ,	5 ,	19 ,	19 ,	5 ,	19 , 18 ,	18 ,	5 ,	18 ,	5 ,	19 ,	19 ,	19 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 19 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	5 ,	19 , 0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	5 ,	19 ,	5 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	5 ,	5 ,
0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	5 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	5 ,
5 ,	18 ,	18 ,	3 ,	3 ,	18 ,	3 ,	3 , 5 ,	5 ,	18 ,	3 ,	3 ,	3 ,	18 ,	3 , 19 ,	5 ,	18 ,	5 ,	18 ,	3 ,	3 ,	3 , 5 ,	18 ,	5 ,	18 ,	18 ,	3 ,	3 ,	18 ,
5 ,	5 ,	18 ,	5 ,	18 ,	18 ,	5 ,	18 , 19 ,	5 ,	5 ,	18 ,	5 ,	5 ,	18 ,	5 , 5 ,	19 ,	5 ,	19 ,	5 ,	19 ,	5 ,	18 , 5 ,	5 ,	5 ,	18 ,	5 ,	18 ,	5 ,	5 ,
18 ,	3 ,	18 ,	19 ,	5 ,	19 ,	5 ,	5 , 3 ,	3 ,	5 ,	18 ,	18 ,	19 ,	19 ,	19 , 18 ,	5 ,	5 ,	18 ,	5 ,	19 ,	5 ,	19 , 18 ,	18 ,	19 ,	19 ,	5 ,	19 ,	19 ,	19 ,
5 ,	5 ,	5 ,	18 ,	5 ,	5 ,	19 ,	5 , 18 ,	5 ,	18 ,	5 ,	19 ,	19 ,	19 ,	19 , 19 ,	18 ,	5 ,	19 ,	5 ,	19 ,	19 ,	0 , 5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	19 ,	19 ,
19 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 19 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 19 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
19 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	5 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
19 ,	5 ,	19 ,	19 ,	19 ,	19 ,	19 ,	19 , 5 ,	19 ,	5 ,	19 ,	19 ,	5 ,	19 ,	19 , 0 ,	19 ,	19 ,	v	0 ,	19 ,	5 ,	19 , 0 ,	0 ,	19 ,	5 ,	19 ,	0 ,	0 ,	5 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
5 ,	19 ,	19 ,	5 ,	19 ,	5 ,	19 ,	0 , 19 ,	5 ,	5 ,	5 ,	5 ,	19 ,	0 ,	0 , 19 ,	5 ,	5 ,	19 ,	19 ,	0 ,	0 ,	0 , 5 ,	0 ,	19 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
};
u8 Goku[1024] = 
{
//Cuadrante1.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante1.2
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	11 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,0 ,	0 ,	0 ,	0 ,	0 ,	11 ,	11 ,	6 ,0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	11 ,	11 ,
//Cuadrante1.3
0 ,	11 ,	11 ,	11 ,	0 ,	0 ,	11 ,	11 ,11 ,	 9 ,	11 ,	0 ,	0 ,	11 ,	 9 ,	6 ,11 ,	 9 ,	 9 ,	0 ,	6 ,	6 ,	6 ,	6 ,6 ,	6 ,	11 ,	11 ,	6 ,	6 ,	 9,	6 ,
6 ,	6 ,	6 ,	6 ,	6 ,	11 ,	6 ,	6 ,6 ,	6 ,	11 ,	6 ,	6 ,	11 ,	6 ,	11 ,6 ,	6 ,	6 ,	11 ,	6 ,	6 ,	11 ,	0 ,6 ,	6 ,	6 ,	11 ,	6 ,	6 ,	6 ,	 9 ,
//Cuadrante1.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,11 ,	11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,11 ,	 9 ,	11 ,	0 ,	0 ,	0 ,	0 ,	0 ,6 ,	 9 ,	 9 ,	11 ,	0 ,	0 ,	0 ,	0 ,
6 ,	11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,11 ,	11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante2.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	6 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	24 ,0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	24 ,	24 ,
//Cuadrante2.2
6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	6 ,6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	24 ,6 ,	11 ,	 9 ,	6 ,	6 ,	24 ,	6 ,	24 ,
6 ,	6 ,	11 ,	6 ,	6 ,	24 ,	24 ,	24 ,6 ,	6 ,	6 ,	6 ,	12 ,	6 ,	6 ,	24 ,6 ,	24 ,	6 ,	6 ,	12 ,	6 ,	5 ,	6 ,6 ,	6 ,	5 ,	6 ,	12 ,	6 ,	19 ,	5 ,
//Cuadrante2.3
6 ,	6 ,	6 ,	6 ,	11 ,	6 ,	6 ,	6 ,6 ,	6 ,	24 ,	6 ,	24 ,	6 ,	6 ,	11 ,6 ,	6 ,	24 ,	24 ,	24 ,	6 ,	11 ,	0 ,24 ,	3 ,	6 ,	24 ,	24 ,	6 ,	0 ,	0 ,
24 ,	24 ,	24 ,	24 ,	24 ,	6 ,	0 ,	0 ,24 ,	24 ,	6 ,	6 ,	24 ,	6 ,	0 ,	0 ,6 ,	24 ,	24 ,	24 ,	6 ,	6 ,	6 ,	0 ,5 ,	6 ,	6 ,	6 ,	6 ,	5 ,	6 ,	0 ,
//Cuadrante2.4
9 ,	11 ,	11 ,	11 ,	0 ,	0 ,	0 ,	0 ,11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante3.1
0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	24 ,	24 ,0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	24 ,	24 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	6 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante3.2
6 ,	5 ,	6 ,	6 ,	13 ,	6 ,	19 ,	19 ,6 ,	6 ,	0 ,	6 ,	13 ,	13 ,	6 ,	19 ,0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	6 ,0 ,	0 ,	0 ,	0 ,	6 ,	19 ,	5 ,	6 ,
0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	5 ,0 ,	0 ,	0 ,	6 ,	12 ,	12 ,	6 ,	5 ,0 ,	0 ,	6 ,	12 ,	12 ,	12 ,	6 ,	5 ,0 ,	6 ,	12 ,	12 ,	12 ,	12 ,	6 ,	5 ,
//Cuadrante3.3
5 ,	5 ,	6 ,	12 ,	6 ,	19 ,	6 ,	6 ,19 ,	6 ,	12 ,	13 ,	6 ,	6 ,	24 ,	6 ,6 ,	12 ,	13 ,	6 ,	6 ,	6 ,	24 ,	6 ,6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	6 ,	24 ,
5 ,	19 ,	19 ,	6 ,	0 ,	0 ,	0 ,	6 ,19 ,	6 ,	6 ,	6 ,	6 ,	0 ,	0 ,	0 ,6 ,	12 ,	12 ,	12 ,	6 ,	0 ,	0 ,	0 ,6 ,	13 ,	12 ,	12 ,	6 ,	0 ,	0 ,	0 ,
//Cuadrante3.4
6 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,24 ,	24 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,24 ,	24 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,24 ,	24 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,
6 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante4.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante4.2
0 ,	6 ,	12 ,	12 ,	12 ,	13 ,	6 ,	5 ,6 ,	13 ,	12 ,	12 ,	13 ,	13 ,	6 ,	5 ,6 ,	13 ,	13 ,	13 ,	13 ,	6 ,	6 ,	6 ,0 ,	6 ,	6 ,	6 ,	6 ,	6 ,	0 ,	0 ,
0 ,	11 ,	6 ,	2 ,	6 ,	0 ,	0 ,	0 ,0 ,	11 ,	2 ,	6 ,	6 ,	0 ,	0 ,	0 ,11 ,	6 ,	2 ,	6 ,	6 ,	0 ,	0 ,	0 ,11 ,	6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante4.3
6 ,	13 ,	12 ,	12 ,	12 ,	6 ,	0 ,	0 ,6 ,	6 ,	13 ,	12 ,	12 ,	13 ,	6 ,	0 ,6 ,	6 ,	13 ,	13 ,	13 ,	13 ,	6 ,	0 ,0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	11 ,	0 ,
0 ,	0 ,	6 ,	6 ,	2 ,	6 ,	11 ,	0 ,0 ,	0 ,	0 ,	6 ,	6 ,	2 ,	6 ,	11 ,0 ,	0 ,	0 ,	6 ,	6 ,	2 ,	6 ,	11 ,0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	2 ,	11 ,
//Cuadrante4.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,11 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
};

u8 Sonic[1024] = 
{
//Cuadrante1.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	5 , 0 ,	0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	19 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	5 ,	5 ,0 ,	0 ,	0 ,	0 ,	0 ,	5 ,	5 ,	5 ,
//Cuadrante1.2
5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	5 , 19 ,	19 ,	5 ,	5 ,	5 ,	19 ,	19 ,	5 , 19 ,	19 ,	19 ,	5 ,	5 ,	19 ,	24 ,	19 , 0 ,	0 ,	19 ,	19 ,	19 ,	12 ,	24 ,	24 ,
0 ,	0 ,	19 ,	5 ,	19 ,	12 ,	24 ,	24 , 0 ,	5 ,	5 ,	5 ,	5 ,	12 ,	12 ,	5 , 5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	5 , 5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	19 ,
//Cuadrante1.3
5 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,5 ,	5 ,	5 ,	0 ,	0 ,	0 ,	19 ,	0 ,5 ,	5 ,	5 ,	5 ,	0 ,	19 ,	19 ,	0 ,19 ,	5 ,	5 ,	5 ,	5 ,	19 ,	19 ,	0 ,
24 ,	5 ,	5 ,	5 ,	5 ,	5 ,	19 ,	0 ,5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	5 ,	0 ,19 ,	19 ,	19 ,	5 ,	5 ,	5 ,	5 ,	5 ,19 ,	10 ,	3 ,	3 ,	5 ,	5 ,	5 ,	0 ,
//Cuadrante1.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante2.1
0 ,	0 ,	0 ,	0 ,	5 ,	19 ,	19 ,	19 ,0 ,	0 ,	0 ,	19 ,	19 ,	19 ,	19 ,	19 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	5 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	5 ,	5 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	5 ,	19 ,
//Cuadrante2.2
19 ,	19 ,	19 ,	19 ,	5 ,	5 ,	5 ,	19 ,19 ,	19 ,	19 ,	19 ,	19 ,	5 ,	5 ,	19 ,19 ,	19 ,	19 ,	19 ,	19 ,	5 ,	5 ,	5 ,0 ,	5 ,	19 ,	19 ,	19 ,	5 ,	12 ,	12 ,
5 ,	5 ,	5 ,	19 ,	19 ,	12 ,	24 ,	24 ,5 ,	5 ,	19 ,	19 ,	19 ,	12 ,	24 ,	24 ,19 ,	19 ,	19 ,	19 ,	19 ,	19 ,	12 ,	12 ,0 ,	0 ,	0 ,	19 ,	19 ,	19 ,	19 ,	19 ,
//Cuadrante2.3
10 ,	3 ,	3 ,	10 ,	6 ,	5 ,	6 ,	0 ,10 ,	3 ,	3 ,	10 ,	6 ,	3 ,	6 ,	0 ,10 ,	3 ,	3 ,	10 ,	 9 ,	3 ,	 9 ,	0 ,12 ,	3 ,	3 ,	3 ,	3 ,	12 ,	10 ,	6 ,
24 ,	24 ,	24 ,	10 ,	24 ,	24 ,	6 ,	6 ,24 ,	24 ,	24 ,	24 ,	24 ,	24 ,	12 ,	0 ,24 ,	24 ,	24 ,	24 ,	12 ,	12 ,	0 ,	0 ,12 ,	12 ,	12 ,	12 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante2.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,6 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
10 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante3.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//cuadrante3.2
0 ,	0 ,	19 ,	19 ,	19 ,	12 ,	24 ,	19 ,0 ,	19 ,	19 ,	19 ,	12 ,	24 ,	19 ,	5 ,0 ,	19 ,	0 ,	12 ,	 9 ,	10 ,	3 ,	3 ,0 ,	0 ,	0 ,	11 ,	10 ,	10 ,	3 ,	3 ,
0 ,	0 ,	0 ,	11 ,	10 ,	3 ,	3 ,	3 ,0 ,	0 ,	0 ,	11 ,	 9 ,	10 ,	3 ,	10 ,0 ,	0 ,	0 ,	0 ,	 9 ,	10 ,	3 ,	10 ,0 ,	0 ,	0 ,	0 ,	19 ,	 9 ,	 9 ,	 9 ,
//Cuadrante3.3
19 ,	19 ,	19 ,	0 ,	0 ,	0 ,	0 ,	0 ,5 ,	12 ,	24 ,	24 ,	0 ,	0 ,	10 ,	10 ,12 ,	24 ,	24 ,	24 ,	11 ,	3 ,	3 ,	3 ,12 ,	12 ,	12 ,	24 ,	11 ,	 9 ,	3 ,	10 ,
3 ,	12 ,	12 ,	5 ,	11 ,	3 ,	3 ,	10 ,10 ,	0 ,	5 ,	5 ,	0 ,	 9 ,	 9 ,	0 ,9 ,	0 ,	19 ,	5 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	19 ,	5 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante3.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,10 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante4.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante4.2
0 ,	0 ,	0 ,	0 ,	19 ,	19 ,	5 ,	0 ,0 ,	0 ,	0 ,	11 ,	11 ,	19 ,	5 ,	 9 ,0 ,	0 ,	0 ,	11 ,	 9 ,	3 ,	3 ,	11 ,0 ,	0 ,	0 ,	6 ,	13 ,	1 ,	13 ,	6 ,
0 ,	0 ,	6 ,	13 ,	3 ,	3 ,	3 ,	3 ,0 ,	0 ,	6 ,	3 ,	13 ,	1 ,	1 ,	1 ,0 ,	0 ,	6 ,	13 ,	13 ,	13 ,	1 ,	3 ,0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	6 ,
//Cuadrante4.3
0 ,	 9 ,	19 ,	5 ,	 9 ,	0 ,	0 ,	0 ,11 ,	3 ,	3 ,	3 ,	 9 ,	0 ,	0 ,	0 ,11 ,	11 ,	 9 ,	 9 ,	11 ,	0 ,	0 ,	0 ,13 ,	10 ,	10 ,	13 ,	1 ,	3 ,	3 ,	1 ,
6 ,	13 ,	13 ,	13 ,	3 ,	3 ,	3 ,	1 ,13 ,	6 ,	13 ,	3 ,	3 ,	3 ,	13 ,	1 ,13 ,	6 ,	13 ,	3 ,	3 ,	13 ,	13 ,	13 ,6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,
//Cuadrante4.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
3 ,	1 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,3 ,	1 ,	1 ,	0 ,	0 ,	0 ,	0 ,	0 ,13 ,	13 ,	1 ,	0 ,	0 ,	0 ,	0 ,	0 ,6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,
};

u8 PouAsesino[1024] = 
{
//Cuadrante 1.1 
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante 1.2
0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	0 , 0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,
0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	6 ,	6 ,	3,	3,	3,	3,  0 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,
//Cuadrante 1.3
0 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 , 6 ,	6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 , 6 ,	6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 , 6 ,	6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 ,
6 ,	6 ,	3,	3,	6 ,	6 ,	0 ,	0 , 3,	3,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	0 ,
//Cuadrante 1.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante 2.1
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	12, 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	12, 0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	12,	12,
//Cuadrante 2.2
0 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	6 ,	12,	12,	12,	12,	12, 0 ,	6 ,	12,	12,	6 ,	6 ,	6 ,	12, 6 ,	12,	12,	6 ,	6 ,	6 ,	6 ,	6 ,
12,	12,	12,	6 ,	6 ,	3,	6 ,	6 , 12,	12,	12,	6 ,	6 ,	6 ,	6 ,	6 , 12,	12,	12,	1,	6 ,	6 ,	6 ,	1, 12,	12,	12,	1,	1,	1,	1,	1,
//Cuadrante 2.3
12,	12,	12,	12,	12,	6 ,	0 ,	0 , 12,	12,	12,	12,	12,	12,	6 ,	0 , 12,	12,	6 ,	6 ,	6 ,	12,	12,	6 , 12,	6 ,	6 ,	6 ,	6 ,	6 ,	12,	12,
12,	6 ,	6 ,	3,	6 ,	6 ,	12,	12, 1,	6 ,	6 ,	6 ,	6 ,	1,	12,	12, 12,	1,	6 ,	6 ,	6 ,	1,	12,	12, 12,	1,	1,	6 ,	1,	12,	12,	12,
//Cuadrante 2.4
0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,6 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
12,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 12,	12,	6 ,	0 ,	0 ,	0 ,	0 ,	0 , 12,	12,	6 ,	0 ,	0 ,	0 ,	0 ,	0 , 12,	12,	12,	6 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante 3.1
0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	12,	12, 0 ,	0 ,	0 ,	0 ,	6 ,	12,	12,	12, 0 ,	0 ,	0 ,	0 ,	6 ,	12,	12,	12, 0 ,	0 ,	0 ,	6 ,	12,	12,	12,	12,
0 ,	0 ,	0 ,	6 ,	12,	12,	12,	12, 0 ,	0 ,	6 ,	12,	12,	12,	12,	12, 0 ,	0 ,	6 ,	12,	12,	12,	12,	12, 0 ,	0 ,	6 ,	3,	12,	12,	12,	12,
//Cuadrante 3.2
6 ,	12,	12,	12,	1,	12,	1,	12, 6 ,	3,	12,	1,	12,	12,	12,	12, 6 ,	1,	3,	12,	12,	12,	1,	12, 6 ,	6 ,	6 ,	3,	12,	12,	12,	12,
3,	6 ,	6 ,	1,	3,	3,	12,	12, 12,	1,	6 ,	1,	6 ,	3,	3,	3, 12,	3,	6 ,	6 ,	6 ,	1,	6 ,	3, 12,	12,	1,	3,	6 ,	6 ,	6 ,	1,
//Cuadrante 3.3
12,	12,	1,	12,	12,	1,	12,	12, 12,	1,	12,	12,	1,	12,	12,	3, 12,	12,	12,	12,	12,	12,	3,	1, 12,	12,	12,	12,	12,	3,	6 ,	6 ,
12,	12,	12,	3,	1,	3,	6 ,	6 , 6 ,	3,	3,	6 ,	6 ,	1,	6 ,	1, 6 ,	1,	6 ,	6 ,	6 ,	6 ,	6 ,	3, 6 ,	1,	6 ,	6 ,	6 ,	1,	3,	12,
//Cuadrante 3.4
6 ,	12,	12,	6 ,	0 ,	0 ,	0 ,	0 , 6 ,	12,	12,	12,	6 ,	0 ,	0 ,	0 , 6 ,	12,	12,	12,	6 ,	0 ,	0 ,	0 , 6 ,	12,	12,	12,	12,	6 ,	0 ,	0 ,
1,	12,	12,	12,	12,	6 ,	0 ,	0 , 12,	12,	12,	12,	12,	12,	6 ,	0 , 12,	12,	12,	12,	12,	12,	6 ,	0 ,12,	12,	12,	12,	12,	3,	6 ,	0 ,
//Cuadrante 4.1
0 ,	0 ,	6 ,	6 ,	3,	3,	12,	12, 0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	3,	3, 0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	6 ,
0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	0 ,	0 ,	0 ,	6 ,	6 ,	6 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	6 ,0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
//Cuadrante 4.2
12,	12,	12,	3,  6 ,	1,	6 ,	6 , 12,	12,	12,	12,	1,	3,	6 ,	1, 3,	3,	3,	12,	12,	12,	3,	1, 6 ,	6 ,	6 ,	3,	3,	3,	5,	5,
6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	5,	5, 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 0 ,	0 ,	0 ,	6 ,	6 ,	6 ,	6 ,	6 ,
//Cuadrante 4.3
6 ,	6 ,	6 ,	1,	6 ,	3,	12,	12, 6 ,	1,	6 ,	3,	3,	12,	12,	12, 1,	3,	1,	12,	12,	12,	3,	3, 5,	5,	5,	3,	3,	3,	6 ,	6 ,
3,	5,	5,	6 ,	6 ,	6 ,	6 ,	6 , 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 3,	6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	6 , 6 ,	6 ,	6 ,	6 ,	6 ,	6 ,	0 ,	0 ,
//Cuadrante 4.4
12,	12,	12,	3,	3,	6 ,	6 ,	0 , 12,	3,	3,	6 ,	6 ,	6 ,	6 ,	0 , 3,	6 ,	5,	6 ,	6 ,	6 ,	6 ,	0 , 6 ,	5,	5,	5,	6 ,	6 ,	0 ,	0 ,
6 ,	3,	3,	3,	6 ,	0 ,	0 ,	0 , 6 ,	6 ,	6 ,	6 ,	0 ,	0 ,	0 ,	0 , 6 ,	6 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 , 0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,	0 ,
	
};
/* Carga en memoria cada uno de los sprites que hemos dibujado. */

void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxsonic[i] = sonic[i*2] | (sonic[(i*2)+1]<<8);				
	}
	//sprite de 32x32
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxPouAsesino[i] = PouAsesino[i*2] | (PouAsesino[(i*2)+1]<<8);				
	}
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxSonic[i] = Sonic[i*2] | (Sonic[(i*2)+1]<<8);				
	}
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxGoku[i] = Goku[i*2] | (Goku[(i*2)+1]<<8);				
	}
}

/* Esta función dibuja un rombo en la posición x-y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un indice distinto, un valor entre 0 y 126. */

void Mostrarsonic(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxsonic,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		true	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/*Esta función borra de la pantalla el Rombo con el índice indicado*/
void BorrarRombo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxsonic,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarPouAsesino(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxPouAsesino,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarPouAsesino(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxPouAsesino,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarSonic(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxSonic,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarSonic(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxSonic,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarGoku(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxGoku,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarGoku(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxGoku,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}
