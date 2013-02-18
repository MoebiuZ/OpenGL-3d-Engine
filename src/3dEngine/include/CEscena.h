
//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CEscena
//--------------------------------------------------------------------------------
// Descripción: Clase para recopilar todos los elementos de la escena a renderizar
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CESCENA_H_
#define _CESCENA_H_

#include <string.h>

#include "CMesh.h"
#include "CMaterial.h"
#include "CCamara.h"
#include "CListaEnlazada.h"

class CEscena
{
	public:
		CListaEnlazada<CMaterial> *m_pListaMateriales;
		unsigned int			  m_nNumMateriales;
		
		CListaEnlazada<CMesh>	  *m_pListaMeshes;
		unsigned int			  m_nNumMeshes;

		CCamara					  *m_Camara;


		CEscena					  ();
		~CEscena				  ();

		CMesh	*NuevoMesh		  ();
		void	SetCamara		  (CCamara *Camara);
		
};


#endif