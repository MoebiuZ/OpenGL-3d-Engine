//--------------------------------------------------------------------------------
//							 	   Void of Mercy          							  
//				   		        www.voidofmercy.org   

//--------------------------------------------------------------------------------
// Descripcion: Aplicacion principal
// Autor: Antonio Rodriguez Fernandez  "MoebiuZ"    <moebiuz@voidofmercy.org>
// Fecha: 06/05/2005
//--------------------------------------------------------------------------------


#include "include/general.h"

#include "3DEngine/include/CGL.h"	// Clase de inicializacion de OpenGL
#include "3DEngine/include/CEscenaRender.h"
#include "3DEngine/include/CEscena.h"
#include "3DEngine/include/CCamara.h"
#include "3DEngine/include/CargadorASE.h"

#include "include/CControles.h"



// Globals
int nAnchoVentana = 800, nAltoVentana = 600;  // Tamaño de la ventana
bool bTeclas[256];				              // Utilizado para el control de la pulsación de teclado
bool bActiva = true;				          // Utilizado para saber cuando está activa la ventana


CGL *ObjetoGL;
CEscenaRender *EscenaRender = new CEscenaRender(); // Creamos la Escena para renderizar
CCamara *Camara = new CCamara();				   // Creamos la Camara
CEscena *Escena = new CEscena();                   // Creamos la Escena
CControles *Controles = new CControles();		   // Creamos los Controles
CargadorASE *ASE = new CargadorASE();			   // Creamos un cargador de ficheros ASE


//--------------------------------------------------------------------------------
// Nombre: Control_Entrada
// Descripcion: Ejecuta la acción relacionada con la tecla que se haya pulsado
//--------------------------------------------------------------------------------
/*void Control_Entrada()
{
	if (bTeclas[VK_LEFT])
	//	fRoty -= 0.5f;
	
	if (bTeclas[VK_RIGHT])
	//	fRoty += 0.5f;
	    
	if (bTeclas[VK_UP])
	//	fRotx += 0.5f;
	
	if (bTeclas[VK_DOWN])
	//	fRotx -= 0.5f;
	
	if (bTeclas[VK_ADD])
	//	fDesz += 0.5f;
	
	if (bTeclas[VK_SUBTRACT])
	//	fDesz -= 0.5f;
	
	if (bTeclas['A'])
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	if (bTeclas['S'])
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
};
*/

//--------------------------------------------------------------------------------
// Nombre: Inicializar
// Descripcion: Inicializa todas las variables de la aplicación
//--------------------------------------------------------------------------------
bool Inicializar()
{
	bool bPCompleta = true;
	// Pregunta al usuario si quiere ejecutar en modo pantalla completa 
	if (MessageBox(NULL, "¿Pantalla completa?", sTituloVentana, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		bPCompleta = false;							// Modo ventana
	}

	// Creamos nuestra ventana OpenGL 
	ObjetoGL = new CGL;
	if (!ObjetoGL->CreaVentanaGL(sTituloVentana, nAnchoVentana, nAltoVentana, nBitsColor, bPCompleta))
	{
		return 0;					// Salir si la ventana no se ha creado
	}

	return 1;

}

//--------------------------------------------------------------------------------
// NOMBRE: Destruir
// DESCRIPCION: Elimina la ventana y destruye los objetos que hayamos creado
//--------------------------------------------------------------------------------
void Destruir()
{
	ObjetoGL->EliminaVentanaGL();					// Elimina la ventana
	delete ObjetoGL;
}

//--------------------------------------------------------------------------------
// NOMBRE: GestorMensajes
// DESCRIPCION: El manejador de mensajes para nuestra clase de ventana
//--------------------------------------------------------------------------------
LRESULT CALLBACK GestorMensajes(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
switch (uMsg)								
	{
		case WM_ACTIVATE:					// Comprobamos el mensaje de ventana activa
		{
			if (!HIWORD(wParam))			// Comprobamos si hemos minimizado
			{
				bActiva = TRUE;				// El programa está activo
			}
			else
			{
				bActiva = FALSE;			// El programa no está activo
			}
			return 0;						// Volvemos al bucle de mensajes
		}

		case WM_SYSCOMMAND:					// Interceptamos comandos del sistema
		{
			switch (wParam)					// Check System Calls
			{
				case SC_SCREENSAVE:			// Evitamos que se active el salvapantallas
				case SC_MONITORPOWER:		// Evitamos que se active el modo sleep del monitor
				return 0;					
			}
			break;							// Salimos
		}

		case WM_CLOSE:						// ¿Hemos recibido el mensaje de SALIDA?
		{
			PostQuitMessage(0);				// Enviamos el mensaje de cerrar la aplicación
			return 0;						
		}

		case WM_KEYDOWN:					// ¿Se ha pulsado alguna tecla?
		{
			bTeclas[wParam] = TRUE;			
			return 0;						
		}

		case WM_KEYUP:						// ¿Se ha dejado de pulsar alguna tecla?
		{
			bTeclas[wParam] = FALSE;	
			return 0;					
		}

		case WM_SIZE:						// Cambiar el tamaño de la ventana
		{
			ObjetoGL->InicializaEscenaGL(LOWORD(lParam), HIWORD(lParam));  // LoWord=Ancho, HiWord=Alto
			return 0;								
		}
	}

	// Pasamos todos los demás mensajes al gestor de mensajes por defecto
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//--------------------------------------------------------------------------------
// NOMBRE: WinMain
// DESCRIPCION: Punto de entrada en el programa. Define la clase de la ventana, 
// la crea y ejecuta el bucle principal.
//--------------------------------------------------------------------------------
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instancia
					HINSTANCE	hPrevInstance,		// Instancia anterior
					LPSTR		lpCmdLine,			// Parametros de la línea de comandos
					int			nCmdShow)			// Estado de vista de la ventana
{
	MSG		msg;									// Estructura de mensajes de la ventana
	BOOL	bAplicacionFinalizada = false;			// Variable booleana para salir del bucle
	
	if (!Inicializar())
		return 0;

	//////////// Pruebas del motor
    ASE->Cargar("suelo.ase", Escena);
	ASE->Cargar("marte.ase", Escena);    // Cargamos el archivo de modelo
	
	ASE->Cargar("tuercasol.ase", Escena);
	

	delete ASE;

	Escena->SetCamara(Camara);           // Añadimos la Camara a al escena
	Controles->SetEscena(Escena);        // Añadimos la Escena a controlar

    EscenaRender->SetEscena(Escena);

    //////////////////////////////


    while(!bAplicacionFinalizada)					// Bucle que se ejecuta mientras bAplicacionFinalizada=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// ¿Hay un mensaje esperando? 
		{
			if (msg.message == WM_QUIT)				// ¿Hemos recibido el mensaje de SALIDA?
			{
				bAplicacionFinalizada = TRUE;		
			}
			else									// Sino lo pasamos al gestor de mensajes
			{
				TranslateMessage(&msg);				// Traducimos el mensaje
				DispatchMessage(&msg);				// Lo procesamos
			}
		}
		else										// Sino hay mensajes
		{
			// Dibujamos la escena. 
			
			if (bActiva && bTeclas[VK_ESCAPE])		// ¿Se ha pulsado la tecla ESC o se ha minimizado?
			{
				bAplicacionFinalizada = TRUE;		// Salimos
			}
			else									// Sino tenemos que salir actualizamos la pantalla
			{
				EscenaRender->Renderizar();			    // Dibujamos la pantalla
				SwapBuffers(ObjetoGL->ObtHDC());	    // Intercambiamos las buffer (Usamos Double buffering)

				Controles->Comprobar(bTeclas);
		//		Control_Entrada();
			}

		}
	}

	// Salir
    Destruir();
	return (msg.wParam);
}