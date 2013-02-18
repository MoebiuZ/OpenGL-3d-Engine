//--------------------------------------------------------------------------------
//							 	   Void of Mercy          							  
//				   		        www.voidofmercy.org        					  


//--------------------------------------------------------------------------------
// Nombre: UTILS.H																  	
// Descripción: Rutinas de interés general										  
// Autor: Antonio Rodriguez Fernandez  "MoebiuZ"      <moebiuz@voidofmercy.org>  
// Fecha: 06/04/2005																  
//--------------------------------------------------------------------------------



#include "stdio.h"


#define SAFE_ARRAY_DELETE(x) if (x) delete [] x;


//---------------------------------------------------------------
// Nombre: LeerCadena
// Descripcion: Devuelve una linea del fichero que se pasa como parámetro
//              saltando las lineas en blanco y las que comienzan con /
// Parametros: 
//              FILE *f: Fichero del que leer la linea
//				char *cadena: Cadena a devolver
//---------------------------------------------------------------
void LeerCadena(FILE *f, char *cadena)
{
	do 
	{
		fgets(cadena, 255, f);
	} 
	while ((cadena[0] == '/') || (cadena[0] == '\n'));
	return;
}
