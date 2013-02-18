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

#include "include/CEscena.h"


CEscena::CEscena()
{
	m_pListaMateriales = new CListaEnlazada<CMaterial>;
	m_pListaMeshes = new CListaEnlazada<CMesh>;
	m_nNumMateriales = 0;
	m_nNumMeshes = 0;

	m_Camara = new CCamara;
}

CEscena::~CEscena()
{
	m_pListaMateriales->LiberarTodo();
	m_pListaMeshes->LiberarTodo();
	delete []m_pListaMateriales;
	delete []m_pListaMeshes;
	delete m_Camara;
}

CMesh *CEscena::NuevoMesh()
{
	CMesh * pNuevoMesh = new CMesh();
//	pNuevoMesh->m_pEscena = this;
//	strcpy(pNuevoMesh->m_szNombre, szNombre);
	m_pListaMeshes->Anadir(pNuevoMesh);
	return pNuevoMesh;
}

void CEscena::SetCamara(CCamara *Camara)
{
	*m_Camara = *Camara;
}
