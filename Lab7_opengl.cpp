#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include <windows.h>
#include "glut.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
float angle1 = 0.0f,
angle2 = 0.0f,
angle3 = 0.0f,
z = 0.0f;
int TYPE = 0;
bool Internal = false;
int SIZE1, SIZE2, SIZE3;
OPENFILENAME ofn;
class Mesh {
public:
    std::vector <float> Vertex;
    std::vector <float> Edge;
    std::vector <float> Face;
    std::vector <float> FaceIn;
    std::vector <char> Location;

    bool LoadFromFile(char* argv);
    float FindMax(std::vector<float> Z, int R);
    float FindMin(std::vector<float> Z, int R);
    void Draw();
    void DrawFace(std::vector<float> F);
    void TransformFace();

};
Mesh Area;
void Mesh::TransformFace() {
    FaceIn = Face;
    int u = 0;

    for (int i = 0; i < SIZE3; i++) {
        if (Location[i] == 'e') {
            FaceIn.erase(FaceIn.begin() + u * 3);
            FaceIn.erase(FaceIn.begin() + u * 3);
            FaceIn.erase(FaceIn.begin() + u * 3);
            u--;
        }
        u++;
    }


}

void Mesh::Draw() {

    glTranslated(0, 0, z);
    glRotatef(angle1, 1, 0, 0);
    glRotatef(angle2, 0, 1, 0);
    glRotatef(angle3, 0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(3);
    glLineWidth(2);
    glColor3f(0, 1, 0);
    float X, Y, Z;
    float Kx = FindMin(Vertex, 0) + (FindMax(Vertex, 0) - FindMin(Vertex, 0)) / 2;
    float Ky = FindMin(Vertex, 1) + (FindMax(Vertex, 1) - FindMin(Vertex, 1)) / 2;
    float Kz = FindMin(Vertex, 2) + (FindMax(Vertex, 2) - FindMin(Vertex, 2)) / 2;
    switch (TYPE)
    {
    case 0:
    {
        glColor3f(1, 1, 1);
        if (Internal) {
            DrawFace(FaceIn);
        }
        else DrawFace(Face);



        // break;

    }
    case 1:
    {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        for (int i = 0; i < SIZE2 * 2; i++) {
            X = Kx > 0 ? Vertex[Edge[i] * 3] - Kx : Vertex[Edge[i] * 3] + Kx;
            Y = Ky > 0 ? Vertex[Edge[i] * 3 + 1] - Ky : Vertex[Edge[i] * 3 + 1] + Ky;
            Z = Kz > 0 ? Vertex[Edge[i] * 3 + 2] - Kz : Vertex[Edge[i] * 3 + 2] + Kz;
            glVertex3f(X, Y, Z);
        }
        glEnd();
        //break;
    }
    case 2:
    {
        glBegin(GL_POINTS);
        for (int i = 0; i < SIZE1 * 3; i += 3) {
            X = Kx > 0 ? Vertex[i] - Kx : Vertex[i] + Kx;
            Y = Ky > 0 ? Vertex[i + 1] - Ky : Vertex[i + 1] + Ky;
            Z = Kz > 0 ? Vertex[i + 2] - Kz : Vertex[i + 2] + Kz;
            glVertex3f(X, Y, Z);
        }
        glEnd();
        break;
    }
    }

}
void Mesh::DrawFace(std::vector<float> F) {
    float X, Y, Z;
    float Kx = FindMin(Vertex, 0) + (FindMax(Vertex, 0) - FindMin(Vertex, 0)) / 2;
    float Ky = FindMin(Vertex, 1) + (FindMax(Vertex, 1) - FindMin(Vertex, 1)) / 2;
    float Kz = FindMin(Vertex, 2) + (FindMax(Vertex, 2) - FindMin(Vertex, 2)) / 2;

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < F.size(); i++) {
        bool Swap = false;
        if (F[i] < 0) {
            F[i] = abs(F[i]) - 1;
            std::swap(Edge[F[i] * 2], Edge[F[i] * 2 + 1]);
            Swap = true;
        }
        X = Kx > 0 ? Vertex[Edge[F[i] * 2] * 3] - Kx : Vertex[Edge[F[i] * 2] * 3] + Kx;
        Y = Ky > 0 ? Vertex[Edge[F[i] * 2] * 3 + 1] - Ky : Vertex[Edge[F[i] * 2] * 3 + 1] + Ky;
        Z = Kz > 0 ? Vertex[Edge[F[i] * 2] * 3 + 2] - Kz : Vertex[Edge[F[i] * 2] * 3 + 2] + Kz;
        glVertex3f(X, Y, Z);

        if (Swap) {
            std::swap(Edge[F[i] * 2], Edge[F[i] * 2 + 1]);
            F[i] = -(F[i] + 1);
            Swap = false;
        }
    }

    glEnd();

}
bool Mesh::LoadFromFile(char* argv) {
    std::ifstream F;
    std::string buff;
    float data;
    Vertex.clear();
    Edge.clear();
    Face.clear();
    Location.clear();

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
        F >> buff;
        F >> buff;
        F >> SIZE1;
        F >> buff;
        F >> buff;
        F >> SIZE2;
        F >> buff;
        F >> buff;
        F >> SIZE3;
        F >> buff;
        F >> buff;
        for (int i = 0; i < SIZE1 * 3; i++) {
            F >> data;
            Vertex.push_back(data);
        }
        F >> buff >> buff >> buff;

        for (int i = 0; i < SIZE2 * 2; i++) {
            F >> data;
            Edge.push_back(data);
        }
        F >> buff >> buff >> buff;

        for (int i = 0; i < SIZE3 * 4; i++) {
            if (i % 4 == 0) {
                F >> buff;
                i++;
            }
            F >> data;
            Face.push_back(data);
        }
        F >> buff >> buff >> buff;
        for (int i = 0; i < SIZE3; i++) {
            F >> buff;
            Location.push_back(buff[0]);
        }
        TransformFace();
    }
    else return false;
    F.close();
    return true;
}



float Mesh::FindMax(std::vector<float> Z, int R) {
    float Max = 0;
    for (int i = R; i < Z.size(); i += 3) {
        if (Z[i] > Max)
            Max = Z[i];
    };
    return(Max);
}
float Mesh::FindMin(std::vector<float> Z, int R) {
    float Min = Z[0];

    for (int i = R; i < Z.size(); i += 3) {
        if (Z[i] < Min)
            Min = Z[i];
    };
    return(Min);
}


void RenderScene() {
    glClearColor(0.1, 0.1, 0.1, 0.0f);
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
    glTranslated(0, 0, -20);
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
    if (key == 'M')
        Internal = true ? Internal == false : false;
    if (key == '-')
        z -= 1.0f;
    if (key == 27) exit(0);
    glutPostRedisplay();
}
void special(int key, int, int) {
    if (key == GLUT_KEY_PAGE_DOWN) {
        TYPE--;
        if (TYPE < 0) TYPE = 0;
    }
    if (key == GLUT_KEY_PAGE_UP) {
        TYPE++;
        if (TYPE > 2) TYPE = 2;
    }
    if (key == GLUT_KEY_HOME)
        z = 0.0f;
    if (key == GLUT_KEY_END) {
        angle1 = 0;
        angle2 = 0;
        angle3 = 0;
    }


    if (key == GLUT_KEY_F1) {
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
        if (!strcmp(argv[2], "In"))
            Internal = true;
    }
    if (argc > 1) {

        if (!Area.LoadFromFile(argv[1])) {
            std::cout << "Error!!!"; return 0;
        }
    }
    else {
        if (!Area.LoadFromFile(nullptr)) {
            std::cout << "Error!!!"; return 0;
        }
    }

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ReshapeWindow);
    glutKeyboardFunc(keys);
    glutSpecialFunc(special);

    glutMainLoop();
    return 0;
}
