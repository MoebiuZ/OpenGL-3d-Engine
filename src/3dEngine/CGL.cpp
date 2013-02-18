//--------------------------------------------------------------------------------
//							 	   Void of Mercy          							  
//				   		        www.voidofmercy.org         						  



//--------------------------------------------------------------------------------
// Clase: CGL																	  
//--------------------------------------------------------------------------------
// Descripción: Contiene todas las rutinas de inicialización de OpenGL			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#include "include/CGL.h"

#include "include/general.h"

//---------------------------------------------------------------
// Nombre: Constructor
// Descripcion: Constructor de la clase. Inicializa las variables
// Parametros: Ninguno
//---------------------------------------------------------------
CGL::CGL()
{
	m_hDC=NULL;	
	m_hRC=NULL;	
	m_hWnd=NULL;	
}

//---------------------------------------------------------------
// Nombre: Destructor
// Descripcion: Destructor de la clase
// Parametros: Ninguno
//---------------------------------------------------------------
CGL::~CGL()
{
}


//---------------------------------------------------------------
// Nombre: InicializaEscenaGL
// Descripcion: Inicializa los parametros iniciales de la escena
// Parametros: 
//		Glsizei ancho: Ancho de la escena
//		Glsizei alto: Alto de la escena
//---------------------------------------------------------------
GLvoid CGL::InicializaEscenaGL(GLsizei ancho, GLsizei alto)		
{
	if (alto==0)									// Previene de la división entre 0
	{
		alto=1;										// Establece la altura = 1
	}

	glViewport(0,0,ancho,alto);						// Resetea el actual puerto de visión (ViewPort)

	glMatrixMode(GL_PROJECTION);					// Selecciona la matriz de proyección
	glLoadIdentity();								// Resetea la matriz de proyección

	// Calcula el Aspect Ratio de la ventana 
	gluPerspective(fovyAnguloPerspectiva, (GLfloat)ancho / (GLfloat)alto, zNearPerspectiva, zFarPerspectiva);
	
	glMatrixMode(GL_MODELVIEW);						// Selecciona la matriz de modelado
	glLoadIdentity();								// Resetea la matriz de modelado
}

//---------------------------------------------------------------
// Nombre: InicializaGL
// Descripcion: Inicializa los valores iniciales de OGL
// Parametros: Ninguno
//---------------------------------------------------------------
int CGL::InicializaGL(GLvoid)						
{
	
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);							// Activa sombreado suave (Smooth Shading)
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Activa Z-Buffer
	glDepthFunc(GL_LEQUAL);								// El tipo de Depth Testing que se va a realizar 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Muy buena correción de perspectiva
	glEnable(GL_TEXTURE_2D);							// Activa mapeado de texturas
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Fondo negro
	return TRUE;										// La inicialización ha ido bien

}

//---------------------------------------------------------------
// Nombre: EliminaVentanaGL
// Descripcion: Destruye toda la información sobre la ventana GL
// Parametros: Ninguno
//---------------------------------------------------------------
GLvoid CGL::EliminaVentanaGL(GLvoid)				
{
		
	if (m_bPantallaCompleta)							// ¿Estamos en modo pantalla completa?
	{
		ChangeDisplaySettings(NULL,0);					// Volvemos al escritorio 
		ShowCursor(TRUE);								// Muestra el cursor 
	}

	if (m_hRC)											// ¿Hay un Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// ¿Podemos eliminar el DC Context y el RC Context?
		{
			MessageBox(NULL,"Fallo al eliminar el DC y el RC.","ERROR DE SALIDA",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(m_hRC))					// ¿Podemos eliminar el RC?
		{
			MessageBox(NULL,"Fallo al eliminar el RC.","ERROR DE SALIDA",MB_OK | MB_ICONINFORMATION);
		}
		m_hRC=NULL;									
	}

	if (m_hDC && !ReleaseDC(m_hWnd,m_hDC))				// ¿Podemos eliminar el DC?
	{
		MessageBox(NULL,"Fallo al eliminar Release Device Context.","ERROR DE SALIDA",MB_OK | MB_ICONINFORMATION);
		m_hDC=NULL;									
	}

	if (m_hWnd && !DestroyWindow(m_hWnd))				// ¿Podemos eliminar la ventana?
	{
		MessageBox(NULL,"No podemos eliminar m_hWnd.","ERROR DE SALIDA",MB_OK | MB_ICONINFORMATION);
		m_hWnd=NULL;								
	}

	if (!UnregisterClass("OpenGL",m_hInstance))			// ¿Podemos "desregistrar" la clase
	{
		MessageBox(NULL,"No podemos 'desregistrar' la clase.","ERROR DE SALIDA",MB_OK | MB_ICONINFORMATION);
		m_hInstance=NULL;							
	}
}


//---------------------------------------------------------------
// Nombre: CrearVentanaGL
// Descripcion: Crea una ventana OGL
// Parametros: 
//			char* Titulo: Titulo de la ventana
//			int ancho: Ancho de la ventana o en modo pantalla completa
//			int alto: Alto de la ventana o en modo pantalla completa
//			int bits: Numero de bits usados para el color (8/16/24/32)
//			bool fullscreen: Usar pantalla completa (TRUE) o ventana (FALSE)
//---------------------------------------------------------------
BOOL CGL::CreaVentanaGL(char* Titulo, int ancho, int alto, int bits, bool fullscreen)
{
	GLuint		PixelFormat;			
	WNDCLASS	wc;						// Estructura de la clase ventana (Windows Class Structure)
	DWORD		dwExStyle;				// Estilo extendido de ventana 
	DWORD		dwStyle;				// Estilo de ventana 
	RECT		WindowRect;				// Graba el rectangulo de valores Arriba-izquierda/Abajo-derecha
	WindowRect.left=(long)0;			// Pone el valor Left a 0
	WindowRect.right=(long)ancho;		// Pone el valor Right al valor pasado en ancho
	WindowRect.top=(long)0;				// Pone el valor Top a 0
	WindowRect.bottom=(long)alto;		// Pone el valor Bottom al valor pasado como alto

	m_bPantallaCompleta = fullscreen;	// Establece el flag global de pantalla completa

	m_hInstance			= GetModuleHandle(NULL);				// Graba una instancia para nuestra ventana 
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) GestorMensajes;				// Manejador de mensajes WndProc
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= m_hInstance;							// Establece la instancia
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Carga del Icono por defecto
	
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Carga del puntero de flecha
	wc.hbrBackground	= NULL;									// No hace falta un fondo para GL
	wc.lpszMenuName		= NULL;									// No queremos un menú
	wc.lpszClassName	= "OpenGL";								// Establece el nombre de la clase

	if (!RegisterClass(&wc))									// Intentamos registrar la clase
	{
		MessageBox(NULL, "Fallo al registrar la clase ventana.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Devolvemos FALSE
	}
	
	if (fullscreen)												// Intentamos modo pantalla completa
	{
		DEVMODE dmScreenSettings;								// Modo del dispositivo
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Nos aseguramos de la memoria
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Tamaño de la estructura Devmode
		dmScreenSettings.dmPelsWidth	= ancho;				// Ancho de la pantalla
		dmScreenSettings.dmPelsHeight	= alto;					// Altura de la pantalla
		dmScreenSettings.dmBitsPerPel	= bits;					// Bits por pixel seleccionados
		dmScreenSettings.dmFields=DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Intentamos cargar el modo seleccionado y obtener los resultados.
		// NOTA: CDS_FULLSCREEN es usado para eliminar la barra de inicio
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// Si el modo falla. Hay dos opciones: Salir o poner modo ventana
			if (MessageBox(NULL, "El modo pantalla completa no es soportado por\nSu tarjeta gráfica. ¿Desea usar modo ventana?", "¿Ventana?", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Modo ventana seleccionado. Fullscreen = FALSE
			}
			else
			{
				// Mostramos un mensaje y cerramos
				MessageBox(NULL, "El programa cerrará.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Devolver FALSE
			}
		}
	}
	
	ShowCursor(FALSE);   
	
	if (fullscreen)												// Estamos en modo pantalla completa?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Estilo extendido de ventana (Window Extended Style)
		dwStyle = WS_POPUP;										// Estilo de ventana
		ShowCursor(FALSE);										// Ocultamos el cursor del ratón
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Estilo extendido de ventana (Window Extended Style)
		dwStyle = WS_OVERLAPPEDWINDOW;							// Estilo de ventana
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Ajustamos la ventana al tamaño solicitado

	// Creando la ventana
	if (!(m_hWnd = CreateWindowEx(dwExStyle,		  			 	    // Estilo extendido de ventana (Window Extended Style)
								"OpenGL",							// Nombre de la clase
								Titulo,								// Titulo de la ventana
								dwStyle |							// Estilo de ventana definido
								WS_CLIPSIBLINGS |					// Estilo de ventana requerido
								WS_CLIPCHILDREN,					// Estilo de ventana requerido
								0, 0,								// Posición de la ventana
								WindowRect.right-WindowRect.left,	// Calculamos el ancho de la ventana
								WindowRect.bottom-WindowRect.top,	// Calculamos el alto de la ventana
								NULL,								// No tiene ventana padre
								NULL,								// Sin menu
								m_hInstance,						// Instancia
								NULL)))								// No pasar nada a WM_CREATE
	{
		EliminaVentanaGL();							
		MessageBox(NULL, "Error en la creación de la ventana.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Devolver FALSE
	}
		
	static	PIXELFORMATDESCRIPTOR pfd=				
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Tamaño del descriptor del formato de pixel
		1,											// Numero de version
		PFD_DRAW_TO_WINDOW |						// El formato debe soportar Ventanas
		PFD_SUPPORT_OPENGL |						// El formato debe soportar OpenGL
		PFD_DOUBLEBUFFER,							// Soporta doble buffer
		PFD_TYPE_RGBA,								// Pedimos un formato RGBA
		bits,										// Seleccionamos la profundidad del color
		0, 0, 0, 0, 0, 0,							// Ignoramos los color bits
		0,											// No queremos buffer alpha
		0,											// Ignoramos Shift Bit
		0,											// No queremos buffer de Acumulación
		0, 0, 0, 0,									// Ignoramos Accumulation Bits
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No usamos buffer de pincel
		0,											// No usamos buffer auxiliar
		PFD_MAIN_PLANE,								// Layer principal de dibujo
		0,											// Reservado
		0, 0, 0										// Ignoramos Layer Masks
	};
	
	if (!(m_hDC=GetDC(m_hWnd)))						// Hemos obtenido el contexto del dispositivo?
	{
		EliminaVentanaGL();							
		MessageBox(NULL, "No podemos crear un GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Devolver FALSE
	}
	
	if (!(PixelFormat = ChoosePixelFormat(m_hDC,&pfd)))	// Hemos obtenido el formato de pixel?
	{
		EliminaVentanaGL();							
		MessageBox(NULL, "No podemos encontrar un formato de pixel aceptable.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Devolver FALSE
	}
	
	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))		// ¿Podemos establecer el formato de pixel?
	{
		EliminaVentanaGL();						
		MessageBox(NULL, "No se puede establacer el formato de Pixel.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							
	}
	
	if (!(m_hRC = wglCreateContext(m_hDC)))			// Podemos obtener un contexto de renderización?
	{
		EliminaVentanaGL();						
		MessageBox(NULL, "No se puede crear un GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							
	}
	
	if(!wglMakeCurrent(m_hDC, m_hRC))				// Vamos a activar el contexto de rend.
	{
		EliminaVentanaGL();						
		MessageBox(NULL, "No se puede activar el GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;							
	}

	ShowWindow(m_hWnd, SW_SHOW);						// Mostrar la ventana
	SetForegroundWindow(m_hWnd);					// Prioridad total
	SetFocus(m_hWnd);								// Establecemos el foco del teclado a la ventana
	InicializaEscenaGL(ancho, alto);				// Inicializamos la escena en perspectiva GL

	if (!InicializaGL())							// Inicializamos ventana GL
	{
		EliminaVentanaGL();						
		MessageBox(NULL, "Fallo en la inicialización.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;					
	}

	return TRUE;									// Todo correcto
}


