//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CControles
//--------------------------------------------------------------------------------
// Descripción: Clase para controlar teclado y raton
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#include "include/CControles.h"


CControles::CControles()
{
	m_Escena = new CEscena;
}

CControles::~CControles()
{
	delete m_Escena;
}


void CControles::Comprobar(bool bTeclas[256])
{
	

	if (bTeclas['A'])
		m_Escena->m_Camara->AddRotY(-1.0f);
	
	if (bTeclas['D'])
		m_Escena->m_Camara->AddRotY(1.0f);
		    
	if (bTeclas['W'])
		m_Escena->m_Camara->AddRotX(1.0f);
	
	
	if (bTeclas['S'])
		m_Escena->m_Camara->AddRotX(-1.0f);
	
	
	if (bTeclas[VK_RIGHT])
	{
		m_Escena->m_Camara->AddTransX(-1.0f);
		m_Escena->m_pListaMeshes->Obtener(0)->AddTransX(1.0f);
	}
	
	if (bTeclas[VK_LEFT])
	{
		m_Escena->m_Camara->AddTransX(1.0f);
        m_Escena->m_pListaMeshes->Obtener(0)->AddTransX(-1.0f);
	}
	if (bTeclas[VK_DOWN])
	{
		m_Escena->m_Camara->AddTransZ(-1.0f);
		m_Escena->m_pListaMeshes->Obtener(0)->AddTransZ(1.0f);
	}

	if (bTeclas[VK_UP])        // Anula la camara con el suelo, asi el objeto parece que lo mueves
		                       // Si anulase el objeto en lugar del suelo, la camara seguiria 
							   // al objeto mientras este camina sobre el suelo
	{
		m_Escena->m_Camara->AddTransZ(1.0f);
		m_Escena->m_pListaMeshes->Obtener(0)->AddTransZ(-1.0f);
	}

	if (bTeclas[VK_ADD])
		m_Escena->m_Camara->AddTransY(1.0f);
	
	
	if (bTeclas[VK_SUBTRACT])
		m_Escena->m_Camara->AddTransY(-1.0f);
	
	
	if (bTeclas['Z'])
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);        // Ver modelo texturizado

	if (bTeclas['X'])
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);        // Ver solo geometria del modelo

  
}

void CControles::SetEscena(CEscena *Escena)
{
	*m_Escena = *Escena;
}