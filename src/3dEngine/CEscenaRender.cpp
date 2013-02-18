//--------------------------------------------------------------------------------
//							 	   Void of Mercy          							  
//				   		        www.voidofmercy.org          						  



//--------------------------------------------------------------------------------
// Clase: CEscenaRender																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para renderizar una escena completa			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#include "include/CEscenaRender.h"


CEscenaRender::CEscenaRender()
{
	m_Escena = new CEscena;
	
}

//---------------------------------------------------------------
// Nombre: Destructor
// Descripcion: Destructor de la clase
// Parametros: Ninguno
//---------------------------------------------------------------
CEscenaRender::~CEscenaRender()
{
	delete m_Escena;
	
}


//---------------------------------------------------------------
// Nombre: SetEscena
// Descripcion: Carga la Escena a renderizar
// Parametros: Ninguno
//---------------------------------------------------------------
void CEscenaRender::SetEscena(CEscena *Escena)
{
   *m_Escena = *Escena;
}

//---------------------------------------------------------------
// Nombre: Renderizar
// Descripcion: Renderiza la escena
// Parametros: Ninguno
//---------------------------------------------------------------
void CEscenaRender::Renderizar()
{
m_Escena->m_pListaMeshes->Obtener(0)->SetTransY(-120.0f);
	RenderEscena();
	
}

	








int CEscenaRender::RenderEscena()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Borramos la pantalla y el buffer de profundidad



	for(int i = 0; i < m_Escena->m_pListaMeshes->m_nNumElementos; i++)
	{
		if (m_Escena->m_pListaMateriales->m_nNumElementos > 0) 
		{
			m_Escena->m_pListaMateriales->Obtener(m_Escena->m_pListaMeshes->Obtener(i)->m_nIDMaterial)->m_pTextura->Usar();
		}

		RenderMesh(i, m_Escena->m_pListaMeshes->Obtener(i));
		
	}

	
	return TRUE;										// Todo ha ido bien 
}







int CEscenaRender::RenderMesh(int nIndice, CMesh *pMesh)
{

	glLoadIdentity();    // Reseteamos la matriz actual

    
	// Sumamos los valores de posicion del Mesh con los de la Camara 
	// para simular que la camara se mueve (en realidad es al escena la que lo hace)
	glTranslatef(pMesh->GetTransX() + m_Escena->m_Camara->GetTransX(), 
		         pMesh->GetTransY() + m_Escena->m_Camara->GetTransY(), 
		         pMesh->GetTransZ() + m_Escena->m_Camara->GetTransZ() -270.0f);

	glRotatef(pMesh->GetRotX() + m_Escena->m_Camara->GetRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef(pMesh->GetRotY() + m_Escena->m_Camara->GetRotY(), 0.0f, 1.0f, 0.0f);
	glRotatef(pMesh->GetRotZ() + m_Escena->m_Camara->GetRotZ(), 0.0f, 0.0f, 1.0f);



	for (int j = 0; j < m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaCaras->m_nNumElementos; j++)	
	{

		glBegin(GL_TRIANGLES);
		
		for (int k = 0; k < 3; k++)
		{
			CCara *cara = m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaCaras->Obtener(j);
			
			glTexCoord3f(m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaVertices->Obtener(cara->m_Vertices[k])->m_fU,
			             m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaVertices->Obtener(cara->m_Vertices[k])->m_fV,
						 m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaVertices->Obtener(cara->m_Vertices[k])->m_fW);
			
			float x = m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaVertices->Obtener(cara->m_Vertices[k])->m_cPunto.m_fX;
			float y = m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaVertices->Obtener(cara->m_Vertices[k])->m_cPunto.m_fY;
			float z = m_Escena->m_pListaMeshes->Obtener(nIndice)->m_pListaVertices->Obtener(cara->m_Vertices[k])->m_cPunto.m_fZ;
			glVertex3f(x, y, z);
		}
	}
	glEnd();	
	
    
	return TRUE;										// Todo ha ido bien 
}
