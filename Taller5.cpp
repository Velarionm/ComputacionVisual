#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Variables para manejar la cámara
GLfloat px0 = 0, py0 = 0, pz0 = 5;
GLfloat px1 = 0, py1 = 0, pz1 = 4;
GLdouble angulo = 0, incremento_angulo = 0.1;
GLdouble const radio = 0.5;
static GLfloat theta[] = { 0.0, 0.0, 0.0 };
static GLint axis = 2;

void iniciar(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();

    // Configurar la cámara con gluLookAt
    gluLookAt(px0, 0.0, pz0, px1, 0.0, pz1, 0, 1, 0);

    glColor3f(1.0, 0.0, 0.0);
    // Dibujar los ejes
    glBegin(GL_LINES);
    glVertex3d(0, 0, 2);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(2, 0, 0);
    glEnd();

    // Rotar y dibujar un dodecaedro alámbrico
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glutWireDodecahedron();

    glPopMatrix();
    glutSwapBuffers();
}

void rotarCamara() {
    px1 = px0 + radio * sin(angulo);
    pz1 = pz0 - radio * cos(angulo);
}

void avanzar() {
    px0 = px1; pz0 = pz1;
    px1 = px0 + radio * sin(angulo);
    pz1 = pz0 - radio * cos(angulo);
}

void retroceder() {
    px1 = px0; pz1 = pz0;
    px0 = px0 - radio * sin(angulo);
    pz0 = pz0 + radio * cos(angulo);
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case 'i': avanzar(); break;
    case 'm': retroceder(); break;
    case 'j': angulo += incremento_angulo; rotarCamara(); break;
    case 'k': angulo -= incremento_angulo; rotarCamara(); break;
    case 'f': exit(0); break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cámara Móvil - OpenGL");
    iniciar();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
