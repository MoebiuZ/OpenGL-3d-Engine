//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CVector																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para almacenar Vectores
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CVECTOR_H_
#define _CVECTOR_H_


class CVector
{
	public:
	    // Variables miembro	
	 	  float m_fX, m_fY, m_fZ;

  	    // Funciones principales
 		  inline void Inicializa(float x, float y, float z) 
		  {
			  m_fX = x; 
			  m_fY = y; 
			  m_fZ = z;
		  };
};


#endif

