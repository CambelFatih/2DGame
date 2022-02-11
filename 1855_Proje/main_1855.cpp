#include"glew.h"
#include < GL/freeglut.h>
#include"freeglut.h"
#include<iostream>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
int SCREEN_FPS = 40;
int cx = 480, cy = 640, iter = 0, iter2 = 100;
float ucgenk = 0.25f, leftright = 0, dortgenk = 0.3f;
bool left = 1, right = 0,gameover=1;
int puan = 0,zaman=0;
float matris[220],randmatris[8];
float ucgenlr[7][5], ucgenlr2[7][5];
float sldx, sldy, sgdx, sgdy;
bool control = 0;

void oyunbitti(float ucgens[7][5]);
int enkucuk(float dizi[7][5]);
double fRand(double fMin, double fMax);
void randomdizi(float ucgendizi[7][5],int toplam);
void doldur(void);
void SpecialInput(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void ciz();
void display(void);
void timer(int v);
void dortgen(float x);
void ucgenciz(float x, float y, float color1, float color2, float color3);

int main(int argc, char** argv)
{
    doldur();
    randomdizi(ucgenlr,2);
    randomdizi(ucgenlr2, 4);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(750, 200);//glut penceresinin ekran konumu
    glutInitWindowSize(cx, cy); //glut penceresinin boyutlarý
    glutCreateWindow("18010011055-Fatih Furkan-Çambel");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutTimerFunc(100, timer, 0);
    glutDisplayFunc(display);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
    return 0;
}
void display(void) {
    if (gameover == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        dortgen(matris[iter2]);
        //ucgenciz(0, matris[iter]);
        for (int i = 0; i < 4; i++)
        {
            ucgenciz(ucgenlr[i][0], ucgenlr[i][1], ucgenlr[i][2], ucgenlr[i][3], ucgenlr[i][4]);
            ucgenciz(ucgenlr2[i][0], ucgenlr2[i][1], ucgenlr2[i][2], ucgenlr2[i][3], ucgenlr2[i][4]);
        }
        //ciz();
        double w = glutGet(GLUT_WINDOW_WIDTH);
        double h = glutGet(GLUT_WINDOW_HEIGHT);
        glOrtho(0, w, 0, h, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos2f(340.0f, 600.0f);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)(("Puan: " + to_string(puan)).c_str()));
        glEnd();
        glFlush();
        glutSwapBuffers();
    }
}
double fRand(double fMin, double fMax)//float random rastegel sayý üretme fonksiyonu
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
void randomdizi(float ucgendizi[7][5],int toplam)// ucgenlerin konumlarý random olarak anatýyor
{
    double temp=-1.125;
    for (int i = 0; i < 8; i++)
    {
        temp+=0.25;
        randmatris[i] = temp;
    }
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 1)
            {
                ucgendizi[i][1] = randmatris[rand() % 8]+ toplam;
            }
            else if (j > 1)
            {
                ucgendizi[i][j] = fRand(0,1);

            }
            else
            {
                ucgendizi[i][j] = randmatris[rand()%8];

            }
        }
    }
    for (int i = 0; i < 7; i++)//ucgenlerin ust uste gelmemesi için kontrol ediliyor 
    {
        for (int j = 0; j < 7; j++)
        {
            if (j != i)
            {
                if(ucgendizi[i][0]== ucgendizi[j][0]&& ucgendizi[i][1] == ucgendizi[j][1])
                {
                    ucgendizi[i][0] = randmatris[rand() % 8]; ucgendizi[i][1] = randmatris[rand() % 8]+toplam;
                }
                    
            }
        }
    }
}
void doldur(void)
{
    float doldurk = 1.0f;
    for (int i = 0; i < 220; i++)
    {
        matris[i] = doldurk;
        doldurk -= 0.01f;
    }
}
int enkucuk(float dizi[7][5])
{
    double temp = -3;
    for (int i = 0; i < 7; i++)
    {
  
        if (dizi[i][1] > temp)
            temp = dizi[i][1];
    }
    return temp;
}
void timer(int v) {
        if (iter >= SCREEN_FPS) { puan += 2; iter = 0; }
        iter++;
        if (enkucuk(ucgenlr) <= -1.125)
        {
            randomdizi(ucgenlr, 2);
        }
        if (enkucuk(ucgenlr2) <= -1.125)
        {
            randomdizi(ucgenlr2, 2);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        display();     
        for (int i = 0; i < 7; i++)
        {
            ucgenlr[i][1] -= 0.01;
            ucgenlr2[i][1] -= 0.01;
        }   
        oyunbitti(ucgenlr);
        oyunbitti(ucgenlr2);
    glutTimerFunc(1000 / SCREEN_FPS, timer, 0);
}
void oyunbitti(float ucgens[7][5])
{
    for (int i = 0; i < 4; i++)
    {
        if (sldx >= ucgens[i][0] && sldx <= (ucgens[i][0] + ucgenk / 2) && (float)(ucgens[i][1] + ((ucgenk / 4) * sqrt(3))) >= sldy && sldy >= (float)(ucgens[i][1] + 0.1))
        {
            printf("oyun bitti1\n"); gameover = 0;
            randomdizi(ucgens, 2);
        }
        if (sgdx <= ucgens[i][0] && sgdx >= (ucgens[i][0] - ucgenk / 2) && (float)(ucgens[i][1] + ((ucgenk / 4) * sqrt(3))) >= sgdy && sgdy >= (float)(ucgens[i][1] + 0.1))
        {
            printf("oyun bitti2\n"); gameover = 0;
            randomdizi(ucgens, 2);
        }
        if ((sldx + 0.125) <= (ucgens[i][0] + ucgenk / 2) && (sldx + 0.125) >= (ucgens[i][0] - ucgenk / 2) && sgdy >= (float)(ucgens[i][1] - ((ucgenk / 4) * sqrt(3))) && sgdy <= (float)(ucgens[i][1] + ((ucgenk / 4) * sqrt(3))))
        {
            printf("oyun bitti3\n"); gameover = 0;
            randomdizi(ucgens, 2);
        }
    }
}
void SpecialInput(int key, int x, int y)
{
    int l = 6, r = 6;
    switch (key)
    {
    case GLUT_KEY_LEFT:

        if (186 > iter2)
            iter2 += l;
        printf("left arrow %f iter:%d\n", matris[iter2], iter2);

        break;
    case GLUT_KEY_RIGHT:
        if (13 < iter2)
            iter2 -= r;
        printf("right arrow %f iter %d \n", matris[iter2], iter2);
        break;
    }
    glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 13:
        printf("\nrand:%d Enter %f",rand()%8, fRand(-0.9, +0.9));// rand() % 100
        if (gameover == 0)
        {
            gameover = 1;
            puan = 0;
            randomdizi(ucgenlr, 2);
            randomdizi(ucgenlr2, 4);
        }
        break;
    }
}
void ciz()
{
    float cizgi = -1;
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        glVertex2f(cizgi, 1);
        glVertex2f(cizgi, -1);
        cizgi += 0.25;
    }
    glColor3f(0, 0, 0);
    cizgi = -1;
    for (int i = 0; i < 8; i++)
    {
        glVertex2f(1, cizgi);
        glVertex2f(-1, cizgi);
        cizgi += 0.25;
    }
}
void ucgenciz(float x, float y, float color1, float color2, float color3)
{
    glBegin(GL_TRIANGLES);
    glColor3f(color1, color2, color3);
    glVertex2f(x, (float)(y - ((ucgenk / 4) * sqrt(3))));//ucu
    glVertex2f(x + ucgenk / 2, (float)(y + ((ucgenk / 4) * sqrt(3))));//sag uc
    glVertex2f(x - ucgenk / 2, (float)(y + ((ucgenk / 4) * sqrt(3))));//sol uc
    glEnd();
    glFlush();
}
void dortgen(float x)
{
    float yd = -0.9;
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.125, yd + 0.061);//sol ust
    glVertex2f(x + 0.125, yd + 0.061);//sag ust
    glVertex2f(x + 0.125, yd - 0.061);
    glVertex2f(x - 0.125, yd - 0.061);
    sldx = x - 0.125;
    sldy = yd + 0.061;
    sgdx = x + 0.125;
    sgdy = yd + 0.061;
    glEnd();
    glFlush();
}
