//--------------------------------------------------------------------------------//
//								   ANDROMEDA STUDIOS							  //
//							  www.andromeda_studios.es.fm						  //
//						 usuarios.tripod.es/andromeda_studios					  //
//--------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------//
// Clase: CTextura																  //
//--------------------------------------------------------------------------------//
// Descripción: Contiene función para la carga y el manejo de texturas en OpenGL  //
// Autor: Fernando José Serrano García -KILE-      fernandosg@ole.com			  //
// Fecha: 13/4/2001																  //
//--------------------------------------------------------------------------------//

#ifndef __CTEXTURA_H_
#define __CTEXTURA_H_

#include "general.h"

class CTextura
{
public:
	// Constructor / Destructor
					CTextura			();
					~CTextura			();
	
	// Operaciones sobre la textura
	void			Eliminar		    ();
	void			Usar			    ();

	// Crea la textura y carga los ficheros
	bool			CargarBMP			(char* szNombreFichero);
	bool		  	Crear				(char* szNombreFichero);
	
	char                m_szNombre[12];
	unsigned int		m_nID;
	unsigned int		m_nAncho, m_nAlto;
	float				m_uTile;
	float				m_vTile;
	float				m_uOffset;
	float				m_vOffset;

};

#endif 
