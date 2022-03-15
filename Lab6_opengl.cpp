#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include <windows.h>
#include "glut.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
float MinMax;
float angle1 = 0.0f,
angle2 = 0.0f,
angle3 = 0.0f,
z = 0.0f;
bool AXES = 0;
int SIZEX, SIZEY;
OPENFILENAME ofn;
class Mesh {
public:
    std::vector <float> Z;

    bool LoadFromFile(char* argv);
    float FindMax();
    float FindMin();
    void Draw();
};
Mesh Area;
void Mesh::Draw() {

    glTranslated(0, 0, z);
    glRotatef(angle1, 1, 0, 0);
    glRotatef(angle2, 0, 1, 0);
    glRotatef(angle3, 0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1);

    glBegin(GL_QUADS);
    float k = 1 / (FindMax() - FindMin());
    float m = FindMin();
    float l = FindMax();
    int sx = SIZEX / 2,
        sy = SIZEY / 2;

    for (int j = 0; j < SIZEY - 1; j++) {
        for (int i = 0; i < SIZEX - 1; i++) {
            glColor3f(k * (Z[i + j * SIZEX] - m), 1, k * (Z[i + j * SIZEX] - m));
            glVertex3f(-sx + i, sy - j, Z[i + j * SIZEX]);
            glColor3f(k * (Z[i + 1 + j * SIZEX] - m), 1, k * (Z[i + 1 + j * SIZEX] - m));
            glVertex3f(-sx + i + 1, sy - j, Z[i + 1 + j * SIZEX]);
            glColor3f(k * (Z[i + SIZEX + 1 + j * SIZEX] - m), 1, k * (Z[i + SIZEX + 1 + j * SIZEX]) - m);
            glVertex3f(i + 1 - sx, -j - 1 + sy, Z[i + SIZEX + 1 + j * SIZEX]);
            glColor3f(k * (Z[i + SIZEX + j * SIZEX] - m), 1, k * (Z[i + SIZEX + j * SIZEX] - m));
            glVertex3f(i - sx, -j - 1 + sy, Z[i + SIZEX + j * SIZEX]);
        }
    }
    glEnd();
    if (AXES) {
        glLineWidth(1);
        glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(-100, 0, 0);
        glVertex3f(100, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, 100, 0);
        glVertex3f(0, -100, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -100);
        glVertex3f(0, 0, 100);
        glEnd();
    }
}
bool arg = false;
bool Mesh::LoadFromFile(char* argv) {
    std::ifstream F;
    float data;
    Z.clear();

    if (argv == NULL) {
        wchar_t szFileName[MAX_PATH] = L"";
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
        ofn.lpstrFile = szFileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
        ofn.lpstrDefExt = L"txt";
        GetOpenFileName(&ofn);


        F.open(ofn.lpstrFile, std::ios::in);
    }
    else {
        F.open(argv, std::ios::in);
    }
    if (F.is_open()) {
        F >> SIZEX;
        F >> SIZEY;
        while (!F.eof()) {
            F >> data;
            Z.push_back(data);
        }
    }
    else return false;
    F.close();
    return true;
}



float Mesh::FindMax() {
    MinMax = 0;
    std::for_each(Z.begin(), Z.end(), [](float x) {if (x > MinMax) MinMax = x; });
    return(MinMax);
}
float Mesh::FindMin() {
    MinMax = Z[0];
    std::for_each(Z.begin(), Z.end(), [](float x) {if (x < MinMax) MinMax = x; });
    return(MinMax);
}


void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Начало нашего кода
    glTranslated(0, 0, -150);
    glTranslated(-60, -60, 0);
    glRotatef(angle1, 1, 0, 0);
    glRotatef(angle2, 0, 1, 0);
    glRotatef(angle3, 0, 0, 1);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 5, 0);
    glVertex3f(0, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    glEnd();
    glLoadIdentity();
    glTranslated(0, 0, -150);
    Area.Draw();

    // Конец нашего кода
    glutSwapBuffers();
}


void keys(unsigned char key, int, int) {
    if (key == 'a')
        angle1 += 1.0f;
    if (key == 's')
        angle2 += 1.0f;
    if (key == 'd')
        angle3 += 1.0f;
    if (key == '=')
        z += 1.0f;
    if (key == '-')
        z -= 1.0f;
    if (key == 27) exit(0);
    glutPostRedisplay();
}
void special(int key, int, int) {
    if (key == GLUT_KEY_HOME)
        z = 0.0f;
    if (key == GLUT_KEY_END) {
        angle1 = 0;
        angle2 = 0;
        angle3 = 0;
    }

    if (key == GLUT_KEY_F2)
        AXES = true ? AXES == false : false;
    if (key == GLUT_KEY_F1) {
        arg = false;
        if (Area.LoadFromFile(NULL));
        else exit(0);
    }
    glutPostRedisplay();
}

void ReshapeWindow(GLsizei width, GLsizei height) {
    if (height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Пример вывода 3D графики");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(0, 0, 0, 1);


    if (argc == 3) {
        if (!strcmp(argv[2], "axes"))
            AXES = true;
    }
    if (argc > 1) {
        //arg = true;
        if (!Area.LoadFromFile(argv[1])) {
            std::cout << "Error!!!"; return 0;
        }
    }
    else {
        if (!Area.LoadFromFile(nullptr)) {
            std::cout << "Error!!!"; return 0;
        }
    }
    std::cout << Area.FindMax() << "\n" << Area.FindMin();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ReshapeWindow);
    glutKeyboardFunc(keys);
    glutSpecialFunc(special);

    glutMainLoop();
    return 0;
}
