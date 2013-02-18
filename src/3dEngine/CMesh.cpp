//--------------------------------------------------------------------------------
//							 	   Void of Mercy          							  
//				   		        www.voidofmercy.org   						  



//--------------------------------------------------------------------------------
// Clase: CMesh																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para almacenar Meshes inanimados
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#include "include/CMesh.h"


CMesh::CMesh()
{

	m_nNumCaras = 0;
	m_nNumVertices = 0;
	m_fColor[0] = 0.0f;
	m_fColor[1] = 0.0f;
	m_fColor[2] = 0.0f;
	m_nIDMaterial = 0;
	
	m_szNombre[0] = '\0';
	m_pListaCaras = new CListaEnlazada<CCara>;        // Lista de Caras del Mesh
	m_pListaVertices = new CListaEnlazada<CVertice>;  // Lista de Vertices del Mesh

	m_pSubMesh = NULL;                                // Mas adelante quiza lo use para enlazar 
	                                                  // varios Meshes relacionados

	m_vPivote = new CVector;

    m_fRotX = 0.0f;
	m_fRotY = 0.0f;
	m_fRotZ = 0.0f;

	m_fTransX = 0.0f;
	m_fTransY = 0.0f;
	m_fTransZ = 0.0f;
}

//---------------------------------------------------------------
// Nombre: Destructor
// Descripcion: Destructor de la clase
// Parametros: Ninguno
//---------------------------------------------------------------
CMesh::~CMesh()
{
	m_pListaCaras->LiberarTodo();
	m_pListaVertices->LiberarTodo();
	delete m_pSubMesh;
	delete m_vPivote;
}



//---------------------------------------------------------------
// Nombre: AddNCaras
// Descripcion: Añade N caras a la lista
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddNCaras(int nNumCaras)
{
	CCara * cara;
	register int i;
	register int total = m_pListaCaras->m_nNumElementos;
	m_pListaCaras->Insertar(nNumCaras);
	
	for (i = 0; i < nNumCaras; i++ )
	{
		cara = new CCara;
		m_pListaCaras->Poner(total + i, cara);
	}
}


//---------------------------------------------------------------
// Nombre: ModCara
// Descripcion: Cambia una cara existente en la lista
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::ModCara(int nNumeroCara, CCara *pCara)
{
if ( nNumeroCara < 0 || nNumeroCara >= m_pListaCaras->Contar() )
		return;

	m_pListaCaras->Obtener(nNumeroCara)->Set(pCara);
}


void CMesh::ModCara(int nNumCara, long Vertices[3])
{
	m_pListaCaras->Obtener(nNumCara)->SetVertice(0, Vertices[0]);
	m_pListaCaras->Obtener(nNumCara)->SetVertice(1, Vertices[1]);
	m_pListaCaras->Obtener(nNumCara)->SetVertice(2, Vertices[2]);
}



//---------------------------------------------------------------
// Nombre: AddNVertices
// Descripcion: Añade N vertices a la lista de vertices
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddNVertices(int nNumeroVertices)
{
	CVertice * vert;
	register int i;
	register int total = m_pListaVertices->Contar();
	m_pListaVertices->Insertar(nNumeroVertices);

	for (i = 0; i < nNumeroVertices; i++)
	{
		vert = new CVertice;
		m_pListaVertices->Poner(total + i, vert);
	}
}



//---------------------------------------------------------------
// Nombre: ModVertice
// Descripcion: Cambia un vertice existente en la lista
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::ModVertice(int nNumeroVertice, CVertice *pVertice)
{
	if ( nNumeroVertice < 0 || nNumeroVertice >= m_pListaVertices->Contar() )
		return;

	m_pListaVertices->Obtener(nNumeroVertice)->Set(pVertice);
}


//---------------------------------------------------------------
// Nombre: GetRotX
// Descripcion: Devuelve el valor de Rotacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
float CMesh::GetRotX()
{
	return m_fRotX;
}


//---------------------------------------------------------------
// Nombre: GetRotY
// Descripcion: Devuelve el valor de Rotacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
float CMesh::GetRotY()
{
	return m_fRotY;
}


//---------------------------------------------------------------
// Nombre: GetRotZ
// Descripcion: Devuelve el valor de Rotacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
float CMesh::GetRotZ()
{
	return m_fRotZ;
}


//---------------------------------------------------------------
// Nombre: GetTransX
// Descripcion: Devuelve el valor de Translacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
float CMesh::GetTransX()
{
	return m_fTransX;
}


//---------------------------------------------------------------
// Nombre: GetTransY
// Descripcion: Devuelve el valor de Translacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
float CMesh::GetTransY()
{
	return m_fTransY;
}


//---------------------------------------------------------------
// Nombre: GetTransZ
// Descripcion: Devuelve el valor de Translacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
float CMesh::GetTransZ()
{
	return m_fTransZ;
}


//---------------------------------------------------------------
// Nombre: SetRotX
// Descripcion: Asigna un nuevo valor de Rotacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::SetRotX(float fValor)
{
	m_fRotX = fValor;
	
}


//---------------------------------------------------------------
// Nombre: SetRotY
// Descripcion: Asigna un nuevo valor de Rotacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::SetRotY(float fValor)
{
	m_fRotY = fValor;
}


//---------------------------------------------------------------
// Nombre: SetRotZ
// Descripcion: Asigna un nuevo valor de Rotacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::SetRotZ(float fValor)
{
	m_fRotZ = fValor;
}


//---------------------------------------------------------------
// Nombre: SeTransX
// Descripcion: Asigna un nuevo valor de Translacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::SetTransX(float fValor)
{
	m_fTransX = fValor;
}


//---------------------------------------------------------------
// Nombre: SetTransY
// Descripcion: Asigna un nuevo valor de Translacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::SetTransY(float fValor)
{
	m_fTransY = fValor;
}


//---------------------------------------------------------------
// Nombre: SetTransZ
// Descripcion: Asigna un nuevo valor de Translacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::SetTransZ(float fValor)
{
	m_fTransZ = fValor;
}


//---------------------------------------------------------------
// Nombre: AddRotX
// Descripcion: Suma (o resta) un valor a la actual Rotacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddRotX(float fValor)
{
	m_fRotX += fValor;
	
}


//---------------------------------------------------------------
// Nombre: AddRotY
// Descripcion: Suma (o resta) un valor a la actual Rotacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddRotY(float fValor)
{
	m_fRotY += fValor;
}


//---------------------------------------------------------------
// Nombre: AddRotZ
// Descripcion: Suma (o resta) un valor a la actual Rotacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddRotZ(float fValor)
{
	m_fRotZ += fValor;
}

//---------------------------------------------------------------
// Nombre: AddTransX
// Descripcion: Suma (o resta) un valor a la actual Translacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddTransX(float fValor)
{
	m_fTransX += fValor;
}


//---------------------------------------------------------------
// Nombre: AddTransY
// Descripcion: Suma (o resta) un valor a la actual Translacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddTransY(float fValor)
{
	m_fTransY += fValor;
}


//---------------------------------------------------------------
// Nombre: AddTransZ
// Descripcion: Suma (o resta) un valor a la actual Translacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CMesh::AddTransZ(float fValor)
{
	m_fTransZ += fValor;
}