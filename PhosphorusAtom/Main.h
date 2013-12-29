/// \file main.h
/// \brief Implementation file for "Exemplo_N4_C".
/// \version $Revision: 1.0 $
/// \author Dalton Reis.
/// \date 03/05/11.

#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #ifdef WIN32
        #include <windows.h>
		#include "OpenGL.h"
    #endif
#endif
#include <string>

#ifndef RAS_DEG_TO_RAD
    #define RAS_DEG_TO_RAD 0.017453292519943295769236907684886
#endif

enum EKeyCode
{
    RAS_ESCAPE_KEY			= 27,
    RAS_SPECIAL_KEY_OFFSET  = 256,
    RAS_1                   = 49,
    RAS_2                   = 50,
    RAS_3                   = 51,
    RAS_a                   =  97,          RAS_A                   = 65,
    RAS_c                   =  99,          RAS_C                   = 67,
    RAS_m                   = 109,          RAS_M                   = 77,
    RAS_p                   = 112,          RAS_P                   = 80,
    RAS_r                   = 114,          RAS_R                   = 82,
    RAS_LEFT_ARROW_KEY		= GLUT_KEY_LEFT,
    RAS_UP_ARROW_KEY		= GLUT_KEY_UP,
    RAS_RIGHT_ARROW_KEY		= GLUT_KEY_RIGHT,
    RAS_DOWN_ARROW_KEY		= GLUT_KEY_DOWN,
    RAS_PAGE_UP_KEY			= GLUT_KEY_PAGE_UP,
    RAS_PAGE_DOWN_KEY		= GLUT_KEY_PAGE_DOWN,
    RAS_HOME_KEY			= GLUT_KEY_HOME,
    RAS_END_KEY				= GLUT_KEY_END,
};

void inicializa(void);
void redimensiona(int w, int h);
void desenha(void);
void setCamera();
void desenhaSRU(void);
void teclaPressionadaEspecial(int tecla, GLint px, GLint py);
void teclaPressionada(unsigned char tecla, GLint x, GLint y);
void animacao(void);
