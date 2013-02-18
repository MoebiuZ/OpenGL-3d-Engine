//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CGL																	  
//--------------------------------------------------------------------------------
// Descripción: Contiene todas las rutinas de inicialización de OpenGL			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CGL_H_
#define _CGL_H_


#include "general.h"


// Procedimiento externo
extern LRESULT CALLBACK GestorMensajes(HWND, UINT,	WPARAM, LPARAM);


class CGL
{
	public:
						CGL						();
		virtual			~CGL		 			();
		BOOL			CreaVentanaGL			(char* szTitulo, int nAncho, int nAlto, int nBits, bool bPantallaCompleta);
		GLvoid			InicializaEscenaGL		(GLsizei ancho, GLsizei alto);	// Cambia de tamaño e inicializa la ventana GL 
		GLvoid			EliminaVentanaGL		(GLvoid);						// Elimina la ventana
		
		
		// Funciones para acceder a las variables miembro
		void			PonPantallaCompleta		(bool bPCompleta)	{m_bPantallaCompleta = bPCompleta;};
		HDC				ObtHDC					()					{return m_hDC;};
		HGLRC			ObtHRC					()					{return m_hRC;};
		HWND			ObtHWnd					()					{return m_hWnd;};
		HINSTANCE		ObtHInstance			()					{return m_hInstance;};
		bool			ObtPantallaCompleta		()					{return m_bPantallaCompleta;};

	private:

		int				InicializaGL			(GLvoid);						// Todas la inicializaciónes de OpenGl vienen aqui
		
		// Variables miembro
		bool			m_bPantallaCompleta;
		HDC				m_hDC;	
		HGLRC			m_hRC;	
		HWND			m_hWnd;	
		HINSTANCE		m_hInstance;	
};

#endif
