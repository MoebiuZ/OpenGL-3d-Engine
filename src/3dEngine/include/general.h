//--------------------------------------------------------------------------------
//						 		   Void of Mercy          							  
//				   		        www.voidofmercy.org        					  


//--------------------------------------------------------------------------------
// Nombre: GENERAL.H																  	
// Descripción: Includes y defines basicos										  
// Autor: Antonio Rodriguez Fernandez  "MoebiuZ"      <moebiuz@voidofmercy.org>  
// Fecha: 06/04/2005																  
//--------------------------------------------------------------------------------

#include "windows.h"		// Archivo cabecera para Windows 
#include "gl\gl.h"			// Librería OpenGL32 
#include "gl\glu.h"			// Librería GLu32
#include "gl\glaux.h"		// Librería Glaux
#include "stdio.h"

#include "CListaEnlazada.h"   // Clase para crear listas enlazadas

#define nBitsColor 32                    // bits de colores para el formato de pixel OpenGL que usaremos
#define fovyAnguloPerspectiva 45.0f
#define zNearPerspectiva 0.1f
#define zFarPerspectiva 4000.0f
