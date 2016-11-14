#pragma once
#include "ObjectsGeometry.cpp"

#include <Windows.h>
#include <GL/glew.h>

#include <GL/GL.h>              // Заголовочный файл для OpenGL32 библиотеки
#include <GL/GLU.h>             // Заголовочный файл для GLu32 библиотеки
#include <GL/glut.h>            // Заголовочный файл для GLUT библиотеки
#include <GL/GLAux.h>           // Заголовочный файл для GLaux библиотеки


 
#pragma comment (lib,"OPENGL32.lib")
#pragma comment (lib,"glut32.lib")
#pragma comment (lib,"GLU32.lib")
#pragma comment (lib,"Glaux.lib")
#pragma comment (lib,"glui32")
#pragma comment (lib,"glew32")
 
void Redraw(void);
void DrawFigures(void);
void Display(void);
void Draw_Trangle(double a,double x, double y, double z);
void executeDraw();
 
const float Circle::PI = 3.14;

int main(int argc, char **argv)
{
	
    glutInit(&argc, argv);        //Инициализация функций библиотеки GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(540,360); 
    glutCreateWindow("Figures OpenGL");
    glutDisplayFunc(Display);     // Регистрация функции построения изображения
    glutIdleFunc(Redraw);         // Регистрация функции обновления изображения
    glEnable(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
     
    glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
    GLfloat LightAmbient[] = {1.0, 1.0, 1.0, 1.0};        // Глоб фоновый свет
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);
    
    glutMainLoop(); //Цикл обработки событий
    return 0;
} 
 
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очищаем экран
    DrawFigures();                                      // Построение объектов
    glutSwapBuffers();                                  // Перестановка буферов кадра	
}

void Redraw(void)
{
    glutPostRedisplay(); // Сигнал для вызова процедуры создания изображения (для обновления)
}



 void DrawFigures(void)
 {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85, 640.0/480.0, 2, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, 4, 0,1,0);
	executeDraw();
    
 }
 
void Draw_Triangle(double a,double x, double y, double z)  
{
	
    glBegin(GL_QUADS);    
    
	glColor3d(0.0f, 0.0f, 1.0f);
    glVertex3f(-x, -y, z);
    glColor3d(0.0f, 1.0f, 0.0f);
    glVertex3f( x, -y, z);
    glColor3d(1.0f, 0.0f, 0.0f);
	glVertex3f(0, y, z);
    glVertex3f(0, y, z);
	
    glEnd();
	
}

void Draw_Square(double a,double x, double y, double z)
{
    glBegin(GL_QUADS);    

	glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
    glVertex3f(2*x/3, 2*y/3, z);
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glVertex3f(2*x/3, -2*y/3, z);
    glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
    glVertex3f(-2*x/3, -2*y/3, z);
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glVertex3f(-2*x/3, 2*y/3, z);
    glColor3d(0.0f, 0.0f, 1.0f);

	glEnd();
}

void Draw_cRectangle(double a,double x, double y, double z)  
{
    glBegin(GL_QUADS);    

	glColor3f(0.2f, 0.0f, 0.2f); 
    glVertex3f(x, y/2, z);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex3f(x, -y/2, z);
    glColor3f(0.2f, 0.2f, 0.0f); 
    glVertex3f(-x, -y/2, z);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex3f(-x, y/2, z);
    glColor3d(0.0f, 0.0f, 1.0f);

	glEnd();
}

void Draw_Circle(double a,double x, double y, double z)  
{
	glBegin(GL_LINE_LOOP);
	
	glColor3f(0.0f, 0.0f, 1.0f);  
    glVertex3f(0.0f, 0.0f, 0.0f); 
    int numSegments = 150,
		ballRadius = a;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = i * 2.0f * Circle::PI / numSegments;  // 360 deg for all segments
        glVertex3f(cos(angle) * ballRadius, sin(angle) * ballRadius, z);
    }
	glEnd();
}

void executeDraw() {
    
    Figure *figures;
    switch (rand() % 4) {
        case 0: figures = new Circle((rand() % 1000) / 100.);
                break;
        case 1: figures = new cRectangle((rand() % 1000) / 100.,
                                       (rand() % 1000) / 100.);
                break;
        case 2: figures = new Square((rand() % 1000) / 100.); 
                break;
		case 3: figures = new Triangle((rand() % 1000) / 100.,
                                       (rand() % 1000) / 100.);
                break;
    }
	figures->Draw();
    delete figures;
	Sleep(1000);
}