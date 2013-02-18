//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CMaterial
//--------------------------------------------------------------------------------
// Descripción: Clase para almacenar Materiales
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CMATERIAL_H_
#define _CMATERIAL_H_

#include "CTextura.h"

class CMaterial
{
	public:
		float		m_fDifuso[4];
		float		m_fEspecular[4];
		float		m_fBrillo;

		char		m_szNombre[17];
		CTextura	*m_pTextura;
};

#endif