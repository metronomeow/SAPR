#include "glut.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")

float angle1 = 0.0f;
float angle2 = 0.0f;
float deltaX = 0.0f,
deltaY = 0.0f;


void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	// ������ ������ ����. ���� ��� - ����!
	//glColor3b(250, 100, 0); - rgb
   // glPointSize(5);
	//glBegin(GL_POINTS); 
	//glLineWidth(4);
	//glBegin(GL_LINES); 
	//glBegin(GL_LINE_LOOP); ��������� �������
	//glBegin(GL_LINE_STRIP); // �������
	//glBegin(GL_QUADS);

	glLoadIdentity();// �������� ��������������, ���� ������ ��� � ������������ ������ � �� ������������ �� 5 ���
	glPushMatrix();
	//glTranslatef(0, deltaY, 0); // ������������ ������� ��������� �� 0.4
	glTranslatef(-0.4, 0.4, 0);
	glRotatef(angle1, 0, 0, 1); // ������� ������������ ��� z
	glBegin(GL_QUADS);
	glColor3f(1, 0.06, 0);
	glVertex2f(0.2, 0.2);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.2, -0.2);
	glVertex2f(0.2, -0.2);
	glEnd();

	glPopMatrix();
	// glLoadIdentity();
	glTranslatef(0.4, -0.4, 0);
	glRotatef(angle2, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.06, 0);
	glVertex2f(0, 0.2);
	glColor3f(0, 0.06, 0.6);
	glVertex2f(-0.2, -0.2);
	glColor3f(1, 0.06, 1);
	glVertex2f(0.2, -0.2);

	glEnd();
	// ����� ������ ����. ���� ��� - ����!
	glFlush();
}


void keyboard(unsigned char key, int, int) {
	if (key == 's')
		angle1 += 10;
	if (key == 'a')
		angle2 += 10;
	glutPostRedisplay();
}


void special(int key, int, int) {
	if (key == GLUT_KEY_UP)
		deltaY += 0.1f;
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_ALPHA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("������ ������ 2D �������");
	glClearColor(0, 0, 0, 1);

	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glutMainLoop();
	return 0;
}
