#define _USE_MATH_DEFINES

#include <cctype> 

#include "Atom.h"
#include "Layer.h"
#include "transform.h"

#include <math.h>
#include "Main.h"
#include <list>

GLint mainWindow = 0;

GLint windowWidth  = 500, windowHeight = 500;

double xEye, yEye, zEye;
double xCenter, yCenter, zCenter;
const double xUp = 0.0f, yUp = 1.0f, zUp = 0.0f;

static GLfloat WHITE[] = { 1.0f, 1.0f, 1.0f};

Atom atom = Atom(15, 16, 15);

#pragma mark INICIALIZACOES
void init(void) {
	glClearColor(0.0f,0.0f,0.0f,1.0);

	xEye = 20.0f;
	yEye = 20.0f;
	zEye = 20.0f;

	xCenter = 0.0f;
	yCenter = 0.0f;
	zCenter = 0.0f;

  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

#pragma mark REDIMENSIONA e DESENHA
void resize(int w, int h) {
	glutPostRedisplay();
}

void setCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 0.1, 300);

	gluLookAt(xEye, yEye, zEye, xCenter, yCenter, zCenter, xUp, yUp, zUp);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, GLint x, GLint y) {
	key = toupper(key);

	switch (key) {
	case RAS_ESCAPE_KEY:
		exit(EXIT_SUCCESS);
		break;
	case 'W':
		xEye++;
		break;

	case 'Q':
		xEye--;
		break;

	case 'E':
		yEye++;
		break;
	case 'D':
		yEye--;
		break;

	case 'Z':
		zEye++;
		break;

	case 'X':
		zEye--;
		break;

	default:
		std::cout << " Invalid keyword! " << std::endl;
		break;
	}
	glutPostRedisplay();    
}

void animate(void) {
	atom.animate();

	glutPostRedisplay();    
}

void draw(void) {

	setCamera();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();

	atom.draw();

	glFlush();
	glutSwapBuffers();
}

#pragma mark PRINCIPAL
int main (int argc, const char * argv[]) {
	glutInit(&argc, (char **)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition (300, 250);
	glutInitWindowSize (windowWidth, windowHeight);
	mainWindow = glutCreateWindow("Phosphorus Atom - Pedro Vereza");
	init();

	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyPressed);
	glutIdleFunc(animate);
	glutMainLoop();

	return 0;
}