//--------------------------------------------------------------------------------
//							 	   Void of Mercy          							  
//				   		        www.voidofmercy.org   


//--------------------------------------------------------------------------------
// Clase: CCamara																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para el control de la camara			  
//
//    La usaremos tambien para posicionar y rotar los Meshes en al escena
//
//
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#include "include/general.h"
#include "include/CCamara.h"


CCamara::CCamara()
{
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
CCamara::~CCamara()
{
}


//---------------------------------------------------------------
// Nombre: GetRotX
// Descripcion: Devuelve el valor de Rotacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
float CCamara::GetRotX()
{
	return m_fRotX;
}


//---------------------------------------------------------------
// Nombre: GetRotY
// Descripcion: Devuelve el valor de Rotacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
float CCamara::GetRotY()
{
	return m_fRotY;
}


//---------------------------------------------------------------
// Nombre: GetRotZ
// Descripcion: Devuelve el valor de Rotacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
float CCamara::GetRotZ()
{
	return m_fRotZ;
}


//---------------------------------------------------------------
// Nombre: GetTransX
// Descripcion: Devuelve el valor de Translacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
float CCamara::GetTransX()
{
	return m_fTransX;
}


//---------------------------------------------------------------
// Nombre: GetTransY
// Descripcion: Devuelve el valor de Translacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
float CCamara::GetTransY()
{
	return m_fTransY;
}


//---------------------------------------------------------------
// Nombre: GetTransZ
// Descripcion: Devuelve el valor de Translacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
float CCamara::GetTransZ()
{
	return m_fTransZ;
}


//---------------------------------------------------------------
// Nombre: SetRotX
// Descripcion: Asigna un nuevo valor de Rotacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::SetRotX(float fValor)
{
	m_fRotX = fValor;
	
}


//---------------------------------------------------------------
// Nombre: SetRotY
// Descripcion: Asigna un nuevo valor de Rotacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::SetRotY(float fValor)
{
	m_fRotY = fValor;
}


//---------------------------------------------------------------
// Nombre: SetRotZ
// Descripcion: Asigna un nuevo valor de Rotacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::SetRotZ(float fValor)
{
	m_fRotZ = fValor;
}


//---------------------------------------------------------------
// Nombre: SetTransX
// Descripcion: Asigna un nuevo valor de Translacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::SetTransX(float fValor)
{
	m_fTransX = fValor;
}


//---------------------------------------------------------------
// Nombre: SetTransY
// Descripcion: Asigna un nuevo valor de Translacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::SetTransY(float fValor)
{
	m_fTransY = fValor;
}


//---------------------------------------------------------------
// Nombre: SetTransZ
// Descripcion: Asigna un nuevo valor de Translacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::SetTransZ(float fValor)
{
	m_fTransZ = fValor;
}


//---------------------------------------------------------------
// Nombre: AddRotX
// Descripcion: Suma (o resta) un valor a la actual Rotacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::AddRotX(float fValor)
{
	m_fRotX += fValor;
}


//---------------------------------------------------------------
// Nombre: AddRotY
// Descripcion: Suma (o resta) un valor a la actual Rotacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::AddRotY(float fValor)
{
	m_fRotY += fValor;
}


//---------------------------------------------------------------
// Nombre: AddRotZ
// Descripcion: Suma (o resta) un valor a la actual Rotacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::AddRotZ(float fValor)
{
	m_fRotZ += fValor;
}

//---------------------------------------------------------------
// Nombre: AddTransX
// Descripcion: Suma (o resta) un valor a la actual Translacion en el eje X
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::AddTransX(float fValor)
{
	m_fTransX += fValor;
}


//---------------------------------------------------------------
// Nombre: AddTransY
// Descripcion: Suma (o resta) un valor a la actual Translacion en el eje Y
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::AddTransY(float fValor)
{
	m_fTransY += fValor;
}


//---------------------------------------------------------------
// Nombre: AddTransZ
// Descripcion: Suma (o resta) un valor a la actual Translacion en el eje Z
// Parametros: Ninguno
//---------------------------------------------------------------
void CCamara::AddTransZ(float fValor)
{
	m_fTransZ += fValor;
}
