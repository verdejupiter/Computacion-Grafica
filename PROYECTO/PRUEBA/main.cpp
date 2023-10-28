#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <MMSystem.h>
#include "glm.h"
#include "Texture.h"
#define FPS 60
#define TO_RADIANS 3.14/180.0

using namespace std;

void camera();
const int width = 16*50;
const int height = 9*50;

///Variables camera --------------------------------

float yaw= 0.0;
int dev_x, x;
//float camX=0.0,camY=55.0,camZ=100.0;
float camX=0.0,camY=15.0,camZ=275.0;

///Sub ventana --------------------------------
int winIdSub;
int winIdSub_2;
int winIdMain;

bool sonido = false, star = false, bandera_1 = false, bandera_2 = false, bandera_3 = false, bandera_4 = false, bandera_5 = false, bandera_6 = false;

///Tipografía Sub ventana ---------------------------------------
void drawString (char *s)
{
  unsigned int i;
  for (i = 0; i < strlen (s); i++)
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, s[i]);
};

void drawStringBig (char *s)
{
  unsigned int i;
  for (i = 0; i < strlen (s); i++)
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, s[i]);
};
///-------------------------------------------------------------

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 10.0f, 10.0f, 10.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

//--------------------------------------------------------
float tx=0,ty=0 ,tz=0, tx1, ty1, tz1,t1x=0,t1y=0,t1z=0,
      t2x=0,t2y=0,t2z=0,ax=0,ay=0,az=0, sx=0,sy=0,sz=0;
//--------------------------------------------------------
float girarhuaco=0,ypoz=0,bandz1=0, tz_1=0,banderaz_1=0,door=0;
bool prin=false, prin2=false,banderita=false;
//--------------------------------------------------------

///Punteros
GLMmodel* punteroM1 = NULL;
GLMmodel* punteroM2 = NULL;
GLMmodel* puerta = NULL;
GLMmodel* marcopuerta = NULL;
///NUBES
GLMmodel* nube = NULL;

///ESCULTURAS
GLMmodel* escultura = NULL;

///AVATAR
GLMmodel* avatar = NULL;
///CHAVIN

GLMmodel* punterosoporte1 = NULL;
GLMmodel* punteroobelisco = NULL;
GLMmodel* punterolanzon = NULL;
GLMmodel* punterocabeza1 = NULL;
GLMmodel* punterocabeza2 = NULL;
GLMmodel* punterojarra = NULL;
GLMmodel* punteroestatua = NULL;
GLMmodel* punterobotella1 = NULL;
GLMmodel* punterobotella2 = NULL;

///NAZCA
GLMmodel* Inca = NULL;
GLMmodel* Soporte_telar_nazca = NULL;
GLMmodel* Soporte = NULL;
GLMmodel* Soporte2 = NULL;
GLMmodel* orca_nazca = NULL;
GLMmodel* Obj1_nasca = NULL;
GLMmodel* Obj2_nasca = NULL;
GLMmodel* Obj18_nasca = NULL;
GLMmodel* Obj19_nasca = NULL;
GLMmodel* Figurina_Nazca = NULL;
GLMmodel* nazca_fish = NULL;
GLMmodel* objeto11_nasca = NULL;
GLMmodel* objeto05_nasca = NULL;
GLMmodel* objeto12_nasca = NULL;
GLMmodel* objeto06_nasca = NULL;
GLMmodel* objeto04_nasca = NULL;

///MOCHE

///huaco_moche01
GLMmodel* M3 = NULL;
///huaco_moche02
GLMmodel* M4 = NULL;
///huaco_moche03
GLMmodel* M5 = NULL;
///huaco_moche04
GLMmodel* M6 = NULL;
///Mesa
GLMmodel* M7 = NULL;
///huaco_moche05
GLMmodel* M8 = NULL;
///huaco_moche06
GLMmodel* M9 = NULL;

///CHIMU
float ch1 = 0;GLMmodel* punteroChimu1 = NULL;
GLMmodel* punteroChimu2 = NULL;
GLMmodel* punteroChimu3 = NULL;
GLMmodel* punteroChimu4 = NULL;
GLMmodel* punteroChimu5 = NULL;
GLMmodel* punteroChimu6 = NULL;
GLMmodel* punteroChimu7 = NULL;
GLMmodel* punteroChimu8 = NULL;
GLMmodel* punteroChimu9 = NULL;
GLMmodel* punteroChimu10 = NULL;
GLMmodel* punteroChimu11 = NULL;
GLMmodel* punteroChimu12 = NULL;


///INCA
GLMmodel* punteroM3 = NULL;
///HUACO1
GLMmodel* punteroM4 = NULL;
///HUACO2
GLMmodel* punteroM5 = NULL;
///HUACO3
GLMmodel* punteroM6 = NULL;
///HUACO5
GLMmodel* punteroM7 = NULL;
///HUACO6
GLMmodel* punteroM8 = NULL;
///HUACO7
GLMmodel* punteroM9 = NULL;
///HUACO8
GLMmodel* punteroM10 = NULL;
///HUACO9
GLMmodel* punteroM11 = NULL;
///HUACO10
GLMmodel* punteroM12 = NULL;
///HUACO11
GLMmodel* punteroM13 = NULL;

///MESA
GLMmodel* punteroM14 = NULL;
GLMmodel* punteroM15 = NULL;

GLuint	texture;
Texture	treeTextureAr[100];

struct Motion
{
    bool Forward,Backward,Left,Right, Up, Down,Gira, Reversa;
};

Motion motion = {false,false,false,false, false, false,false,false};

float color(float a)
{
    a=a/255;

    return(a);
}

void graficarEjes()
{
    glBegin(GL_LINES);
        glVertex3f(1000,0,0);
        glVertex3f(-1000,0,0);

        glVertex3f(0,1000,0);
        glVertex3f(0,-1000,0);

        glVertex3f(0,0,1000);
        glVertex3f(0,0,-1000);
    glEnd();
}

bool LoadTreeTextures()
{
	int i;

	if (LoadTGA(&treeTextureAr[0], "modelos/MuseoFirme_baseColorTexture.tga")&& LoadTGA(&treeTextureAr[1], "modelos/2.tga")
     && LoadTGA(&treeTextureAr[2], "modelos/nube.tga")
     ///CHAVIN
     && LoadTGA(&treeTextureAr[2], "modelos/chavin/textura_soporte.tga") && LoadTGA(&treeTextureAr[3], "modelos/chavin/textura_obelisco.tga" )
     && LoadTGA(&treeTextureAr[4], "modelos/chavin/textura_lanzon.tga") && LoadTGA(&treeTextureAr[5], "modelos/chavin/cabeza1.tga")
     && LoadTGA(&treeTextureAr[6], "modelos/chavin/cabeza2.tga") && LoadTGA(&treeTextureAr[7], "modelos/chavin/jarra.tga")
     && LoadTGA(&treeTextureAr[8], "modelos/chavin/estatua.tga") && LoadTGA(&treeTextureAr[9], "modelos/chavin/botella1.tga")
     && LoadTGA(&treeTextureAr[10], "modelos/chavin/botella2.tga")
     ///INCA
     && LoadTGA(&treeTextureAr[11], "modelos/inca/textura1.tga") && LoadTGA(&treeTextureAr[12], "modelos/inca/textura2.tga")
     && LoadTGA(&treeTextureAr[13], "modelos/inca/textura3.tga") && LoadTGA(&treeTextureAr[14], "modelos/inca/textura5.tga")
     && LoadTGA(&treeTextureAr[15], "modelos/inca/textura6.tga") && LoadTGA(&treeTextureAr[16], "modelos/inca/textura7.tga")
     && LoadTGA(&treeTextureAr[17], "modelos/inca/textura8.tga") && LoadTGA(&treeTextureAr[18], "modelos/inca/textura9.tga")
     && LoadTGA(&treeTextureAr[19], "modelos/inca/textura10.tga") && LoadTGA(&treeTextureAr[20], "modelos/inca/textura11.tga")
     && LoadTGA(&treeTextureAr[21], "modelos/inca/Table.tga") && LoadTGA(&treeTextureAr[22], "modelos/inca/mesanegra.tga")
     ///NAZCA
     &&LoadTGA(&treeTextureAr[23], "modelos/Nazca/objeto04_nasca.tga") &&LoadTGA(&treeTextureAr[24], "modelos/Nazca/objeto06_nasca.tga")
     &&LoadTGA(&treeTextureAr[25], "modelos/Nazca/objeto12_nasca.tga") &&LoadTGA(&treeTextureAr[26], "modelos/Nazca/textura_objeto05_nasca.tga")
     &&LoadTGA(&treeTextureAr[27], "modelos/Nazca/textura_objeto11_nasca.tga") &&LoadTGA(&treeTextureAr[28], "modelos/Nazca/nazca_fish.tga")
     &&LoadTGA(&treeTextureAr[29], "modelos/Nazca/textura_figurina_nazca.tga") &&LoadTGA(&treeTextureAr[30], "modelos/Nazca/textura_objeto19_nasca.tga")
     &&LoadTGA(&treeTextureAr[31], "modelos/Nazca/textura_objeto18_nasca.tga") &&LoadTGA(&treeTextureAr[32], "modelos/Nazca/textura_orca_nazca.tga")
     &&LoadTGA(&treeTextureAr[33], "modelos/Nazca/textura_telar.tga") &&LoadTGA(&treeTextureAr[34], "modelos/Nazca/textura_objeto02_nasca.tga")
     &&LoadTGA(&treeTextureAr[35], "modelos/Nazca/textura_objeto01_nasca.tga") &&LoadTGA(&treeTextureAr[36], "modelos/Nazca/textura_Soporte_2.tga")
     &&LoadTGA(&treeTextureAr[37], "modelos/Nazca/textura_soporte.tga") &&LoadTGA(&treeTextureAr[38], "modelos/Nazca/textura_inca.tga")
     ///CHIMU
     &&LoadTGA(&treeTextureAr[39], "modelos/chimu/Cajon_Normal_diffuse.tga") && LoadTGA(&treeTextureAr[40], "modelos/chimu/textura 02.tga")
     && LoadTGA(&treeTextureAr[41], "modelos/chimu/textura 03.tga") && LoadTGA(&treeTextureAr[42], "modelos/chimu/textura 04.tga")
     && LoadTGA(&treeTextureAr[43], "modelos/chimu/textura 05.tga") && LoadTGA(&treeTextureAr[44], "modelos/chimu/textura 06.tga")
     && LoadTGA(&treeTextureAr[45], "modelos/chimu/mesanegra.tga") && LoadTGA(&treeTextureAr[46], "modelos/chimu/textura 07.tga")
     && LoadTGA(&treeTextureAr[47], "modelos/chimu/textura 08.tga") && LoadTGA(&treeTextureAr[48], "modelos/chimu/textura 09.tga")
     && LoadTGA(&treeTextureAr[49], "modelos/chimu/textura 10.tga")
    ///Avatar
    && LoadTGA(&treeTextureAr[50], "modelos/avatar2.tga")
    ///ESCULTURA
    && LoadTGA(&treeTextureAr[51], "modelos/scultura1.tga")
     ///MOCHE
     && LoadTGA(&treeTextureAr[52], "modelos/moche/huaco01.tga")
     && LoadTGA(&treeTextureAr[53], "modelos/moche/huaco02.tga")
     && LoadTGA(&treeTextureAr[54], "modelos/moche/huaco03.tga")
     && LoadTGA(&treeTextureAr[55], "modelos/moche/huaco04.tga")
     && LoadTGA(&treeTextureAr[56], "modelos/moche/Table.tga")
     && LoadTGA(&treeTextureAr[57], "modelos/moche/huaco05.tga")
     && LoadTGA(&treeTextureAr[58], "modelos/moche/huaco06.tga")
     ///telares
     && LoadTGA(&treeTextureAr[59], "modelos/textura_telar12.tga")
     && LoadTGA(&treeTextureAr[60], "modelos/textura_telar13.tga")
     && LoadTGA(&treeTextureAr[61], "modelos/textura_telar14.tga")
     && LoadTGA(&treeTextureAr[62], "modelos/textura_telar15.tga")


     )
	{
		for (i = 0; i<100; i++){
			glGenTextures(1, &treeTextureAr[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeTextureAr[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeTextureAr[i].bpp / 8, treeTextureAr[i].width, treeTextureAr[i].height, 0, treeTextureAr[i].type, GL_UNSIGNED_BYTE, treeTextureAr[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeTextureAr[i].imageData)
			{
				free(treeTextureAr[i].imageData);
			}
		}
		return true;
	}
	else{
		return false;
	}
}

void init(void)
{
	glClearColor(0.73,0.9,0.91, 0.0);
	LoadTreeTextures();
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
}

void abrirpuerta(int i){

	if (door<90)
        door+= 0.5;
	glutPostRedisplay();
	glutTimerFunc(1,abrirpuerta, 2);
}


void graficar(void)
{
	glutSetWindow (winIdMain); //Acciona ventana principal

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    ///
    glPushMatrix();
        glTranslatef(camX+15,camY-5,camZ-40);
        glRotated(-90,1,0,0);
        glScaled(15,15,15);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[50].texID);
        glmDraw(avatar, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///
    graficarEjes();

    glPushMatrix();
        glRotatef(180,1,0,0);
        glScalef(570,385,1200);
        glRotatef(90,1,0,0);
        glScalef(0.5,0.5,0.5);
        glTranslatef(0.014,-0.064,0.049);
        glRotatef(door,0,0,1);
        glTranslatef(-0.014,0.064,-0.049);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
        glmDraw(puerta, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
      glPushMatrix();
        glRotatef(180,1,0,0);
        glScalef(570,385,1200);
        glRotatef(90,1,0,0);
        glScalef(0.5,0.5,0.5);
        //glTranslated(0,-11.5,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
        glmDraw(marcopuerta, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glRotatef(180,1,0,0);
        glScalef(570,385,1200);
        glRotatef(90,1,0,0);
        glScalef(0.5,0.5,0.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
        glmDraw(punteroM1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-60,-11.5,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
        glmDraw(punteroM2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///NUBES
     /*glPushMatrix();
        glScalef(570,385,1200);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(nube, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();*/
    ///ESCULTURA
    glPushMatrix();
        glTranslated(14,13,80);
        glRotatef(180,0,1,0);
        glScalef(150.5,150.5,150.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[51].texID);
        glmDraw(escultura, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-14,13,80);
        glRotatef(180,0,1,0);
        glScalef(150.5,150.5,150.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[51].texID);
        glmDraw(escultura, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///CULTURA  CHAVIN
	///-----------------------------------------------------------
     glPushMatrix();
        glRotatef(180,1,0,0);
        glScalef(570,385,1200);
        glRotatef(90,1,0,0);
        glScalef(0.5,0.5,0.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
        glmDraw(punteroM1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-60,-11.5,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
        glmDraw(punteroM2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///------------------------------------------------------------
    glPushMatrix();
        glTranslated(-30,7,65);
        glScalef(0.005,0.011,0.010);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(punterosoporte1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-30,8,65);
        glScalef(6,6,6);
        glTranslated(-0.026824,0.066152,-0.014);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(0.026824,-0.066152,0.014);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[3].texID);
        glmDraw(punteroobelisco, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    //---------------------------------------------------------------
    glPushMatrix();
        glTranslated(-50,7,65);
        glScalef(0.005,0.011,0.010);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(punterosoporte1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-51,8,65);
        glScalef(12,13,5);
        glTranslated(0.069604,0.031033,0.018642);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.069604,-0.031033,-0.018642);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[4].texID);
        glmDraw(punterolanzon, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    //---------------------------------------------------------------
    glPushMatrix();
        glTranslated(-65,11,50);
        glScalef(0.005,0.018,0.015);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(punterosoporte1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
         glTranslated(-65,12,45);
         glRotatef(150,0,1,0);
         glScalef(9,9,5);
         glTranslated(0.150104,0.074812,-0.030317);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.150104,-0.074812,0.030317);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[5].texID);
        glmDraw(punterocabeza1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
         glTranslated(-65,12,53);
         glRotatef(200,0,1,0);
         glScalef(13,13,7);
         /*glTranslated(0.105867,0.156751,-0.010774);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.105867,-0.156751,0.010774);*/
        glTranslated(tz_1,0,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[6].texID);
        glmDraw(punterocabeza2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    //---------------------------------------------------------------
    glPushMatrix();
        glTranslated(-65,11,30);
        glScalef(0.005,0.018,0.015);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(punterosoporte1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
         glTranslated(-65,14,33);
         glRotatef(200,0,1,0);
         glScalef(46,46,46);
         glTranslated(0.000613,0.002043,-0.016732);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.000613,-0.002043,0.016732);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[9].texID);
        glmDraw(punterobotella1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
         glTranslated(-65,14,25);
         glRotatef(200,0,1,0);
         glScalef(46,46,46);
         glTranslated(-0.000764,0.002193,-0.02066);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(0.000764,-0.002193,0.02066);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[10].texID);
        glmDraw(punterobotella2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    //---------------------------------------------------------------
    glPushMatrix();
        glTranslated(-30,7,25);
        glScalef(0.005,0.011,0.010);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(punterosoporte1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-30,8,25);
        glScalef(3,3,3);
        glTranslated(0.119932,0.532782,0.035897);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.119932,-0.532782,-0.035897);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[7].texID);
        glmDraw(punterojarra, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    //---------------------------------------------------------------
    glPushMatrix();
        glTranslated(-50,7,25);
        glScalef(0.005,0.011,0.010);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[2].texID);
        glmDraw(punterosoporte1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-52,15,25);
        glScalef(33,33,23);
        glTranslated(0.051315,0.029393,0.010868);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.051315,-0.029393,-0.010868);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[8].texID);
        glmDraw(punteroestatua, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
	///-----------------------------------------------------------

	///CULTURA  NAZCA
	///-----------------------------------------------------------
      ///Inca exterior -------------------------------------------
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[38].texID);
        glTranslatef(0,10,200);
        glRotatef(-90,0,1,0);
        glScalef(8,8,8);
        glmDraw(Inca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Nazca----------------------------------------------------
    ///Soporte Telar
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[33].texID);
        glTranslatef(2.7,20,-67);
        glScalef(40,40,40);
        glRotatef(-180,0,0,1);
        glmDraw(Soporte_telar_nazca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Horizontal
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(-10,5.9,-62);
        glScalef(0.008,0.01,0.008);
        glRotatef(270,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Horizontal 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(-12,5.9,2);
        glScalef(0.005,0.01,0.005);
        glRotatef(270,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Vertical 1
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(14,10.6,-66);
        glScalef(0.005,0.018,0.001);
        glRotatef(85,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Vertical 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(15,10.6,-56);
        glScalef(0.005,0.018,0.001);
        glRotatef(85,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Vertical 3
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(16,10.6,-46);
        glScalef(0.005,0.018,0.001);
        glRotatef(85,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Vertical 4
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(17,10.6,-36);
        glScalef(0.005,0.018,0.001);
        glRotatef(85,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Vertical 5
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(18,10.6,-26);
        glScalef(0.005,0.018,0.001);
        glRotatef(85,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Vertical 6
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[37].texID);
        glTranslatef(19,10.6,-16);
        glScalef(0.005,0.018,0.001);
        glRotatef(85,0,1,0);
        glmDraw(Soporte, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Horizontal 2 -1
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[36].texID);
        glTranslatef(-14,4,-38);
        glScalef(30,30,30);
        glRotatef(180,0,0,1);
        glRotatef(270,0,1,0);
        glmDraw(Soporte2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Horizontal 2 -2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[36].texID);
        glTranslatef(-14,4,-18);
        glScalef(30,30,30);
        glRotatef(180,0,0,1);
        glRotatef(270,0,1,0);
        glmDraw(Soporte2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///Soporte Horizontal 2 -3
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[36].texID);
        glTranslatef(-14,10.5,-25);
        glScalef(30,30,30);
        glRotatef(180,0,0,1);
        glRotatef(270,0,1,0);
        glmDraw(Soporte2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 1
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[35].texID);
        glTranslatef(-9,6.5,-64);
        glScalef(7,7,7);
        glRotatef(-90,0,1,0);

        glTranslated(0.002738,0.5903,-0.027515);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.002738,-0.5903,0.027515);

        glmDraw(Obj1_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[34].texID);
        glTranslatef(-11,6.5,-56);
        glScalef(7,7,7);
        glRotatef(-90,0,1,0);

        glTranslated(0.0700956,0.644838,-0.006576);
            glRotatef(90-ypoz, 0, 1, 0);
        glTranslated(-0.0700956,-0.644838,0.006576);

        glmDraw(Obj2_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 18 . soporte vertical 1
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[31].texID);
        glTranslatef(14,11.5,-66);
        glScalef(6,6,6);
        glRotatef(270,0,1,0);

        glTranslated(0.031085,0.882436,0.052672);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.031085,-0.882436,-0.052672);
        glmDraw(Obj18_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto orca . soporte 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[32].texID);
        glTranslatef(15,13,-56);
        glScalef(0.7,0.7,0.7);
        glRotatef(105,0,1,0);

        glTranslated(0.138211,1.724001,-0.044232);
            glRotatef(90-ypoz, 0, 1, 0);
        glTranslated(-0.138211,-1.724001,0.044232);
        glmDraw(orca_nazca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 19 . soporte vertical 3
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[30].texID);
        glTranslatef(16,11.5,-46);
        glScalef(6,6,6);
        glRotatef(180,0,1,0);

        glTranslated(0.089019,0.853842,0.010043);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.089019,-0.853842,-0.010043);
        glmDraw(Obj19_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto figurina . soporte vertical 4
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[29].texID);
        glTranslatef(14,13.5,-38);
        glRotatef(270,0,1,0);

        glTranslated(1.458714,0.07937,-3.394784);
            glRotatef(90-ypoz, 0, 1, 0);
        glTranslated(-1.458714,-0.07937,3.394784);
        glmDraw(Figurina_Nazca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto nazca fish . soporte vertical 5
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[28].texID);
        glTranslatef(19,22,-26);
        glScalef(1.05,1.05,1.05);
        glRotatef(270,1,0,0);

        glTranslated(-0.467584,1.113596,-7.7612);
            glRotatef(ypoz, 0, 0, 1);
        glTranslated(0.467584,-1.113596,7.7612);
        glmDraw(nazca_fish, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 11. soporte vertical 6
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[27].texID);
        glTranslatef(18.5,11.5,-16);
        glScalef(6,6,6);
        glRotatef(270,0,1,0);

        glTranslated(0.051313,0.454302,-0.038031);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.051313,-0.454302,0.038031);
        glmDraw(objeto11_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 05. soporte horizontal 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[26].texID);
        glTranslatef(-11.5,13.3,-30.5);
        glScalef(6,6,6);
        glRotatef(90,0,1,0);

        glTranslated(0.051313,0.454302,-0.038031);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.051313,-0.454302,0.038031);
        glmDraw(objeto05_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 12. soporte horizontal 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[25].texID);
        glTranslatef(-12,13.3,-20);
        glScalef(5.5,5.5,5.5);
        glRotatef(90,0,1,0);

        glTranslated(0.051313,0.454302,-0.038031);
            glRotatef(90-ypoz, 0, 1, 0);
        glTranslated(-0.051313,-0.454302,0.038031);
        glmDraw(objeto12_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 06. soporte horizontal 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[24].texID);
        glTranslatef(-12,7.5,-24);
        glScalef(4,4,4);
        glRotatef(90,0,1,0);

        glTranslated(0.051313,0.454302,-0.038031);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(-0.051313,-0.454302,0.038031);
        glmDraw(objeto06_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    //Objeto 04. soporte horizontal 2
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[23].texID);
        glTranslatef(-12,6.5,2);
        glScalef(5,5,5);
        glRotatef(90,0,1,0);

        glTranslated(-0.038173,0.324794,0.000698);
            glRotatef(ypoz, 0, 1, 0);
        glTranslated(0.038173,-0.324794,-0.000698);
        glmDraw(objeto04_nasca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
	///-----------------------------------------------------------

	///CULTURA  MOCHE
	///-----------------------------------------------------------
     glPushMatrix();
        glScalef(5, 5, 5);
        glTranslatef(-12, 1.2, -13);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[52].texID);
        glmDraw(M3, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-50, 5.2, -65);
        glScalef(2, 2, 2);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[53].texID);
        glmDraw(M4, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-40, 5.2, -65);
        glScalef(5, 5, 5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[54].texID);
        glmDraw(M5, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-30, 5.2, -65);
        glRotatef(-90, 0, 1, 0);
        glScalef(2, 2, 2);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[55].texID);
        glmDraw(M6, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-29, 0, -65);
        glScalef(1, 0.6, 1);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[56].texID);
        glmDraw(M7, GLM_SMOOTH | GLM_TEXTURE);
        glPushMatrix();
            glTranslatef(-9, 0, 0);
            glBindTexture(GL_TEXTURE_2D, treeTextureAr[56].texID);
            glmDraw(M7, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-20, 0, 0);
            glBindTexture(GL_TEXTURE_2D, treeTextureAr[56].texID);
            glmDraw(M7, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-30, 0, 0);
            glBindTexture(GL_TEXTURE_2D, treeTextureAr[56].texID);
            glmDraw(M7, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-65, 0, -55);
        glScalef(1, 0.6, 1);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[56].texID);
        glmDraw(M7, GLM_SMOOTH | GLM_TEXTURE);
        glPushMatrix();
            glTranslatef(0, 10, 0);
            glScalef(5, 5, 5);
            glBindTexture(GL_TEXTURE_2D, treeTextureAr[57].texID);
            glmDraw(M8, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-65, 0, -40);
        glScalef(1, 0.6, 1);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[56].texID);
        glmDraw(M7, GLM_SMOOTH | GLM_TEXTURE);
        glPushMatrix();
            glTranslatef(0, 10, 0);
            glScalef(5, 5, 5);
            glBindTexture(GL_TEXTURE_2D, treeTextureAr[58].texID);
            glmDraw( M9, GLM_SMOOTH | GLM_TEXTURE);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-25, 1.2, -45);
        glRotatef(-180, 0, 1, 0);
        glScalef(4, 4, 4);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[55].texID);
        glmDraw( M6, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-25, 1.2, -25);
        glRotatef(-90, 0, 1, 0);
        glScalef(4, 4, 4);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[53].texID);
        glmDraw(M4, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
	///-----------------------------------------------------------

	///CULTURA  CHIMÚ
	///-----------------------------------------------------------
    //MESAS1
  glPushMatrix();
        glTranslated(2,-1,-30);
        glScalef(7.5,7.5,7.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[39].texID);
        glmDraw(punteroChimu1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
///OBJETOS
    glPushMatrix();
        glTranslated(34.5,4.8,-62);
        glScalef(3.5,3.5,3.5);
        glRotatef(ch1,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[40].texID);
        glmDraw(punteroChimu2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(41.5,6.8,-62);
        glScalef(3.5,3.5,3.5);
        glRotatef(ch1,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[41].texID);
        glmDraw(punteroChimu3, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

     glPushMatrix();
        glTranslated(48.5,11.8,-62);
        glScalef(1.5,1.5,1.5);
        glRotatef(ch1,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[42].texID);
        glmDraw(punteroChimu4, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(54.9,14.3,-62);
        glScalef(5.5,5.5,5.5);
        glRotatef(ch1,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[43].texID);
        glmDraw(punteroChimu5, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(62.9,16.3,-59);
        glScalef(5.5,5.5,5.5);
        glRotatef(ch1,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[44].texID);
        glmDraw(punteroChimu6, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    ///MESA NEGRA
    glPushMatrix();
        glTranslated(69.9,0,-39);
        glScalef(8.5,16,8.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[45].texID);
        glmDraw(punteroChimu7, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(35,0,-39);
        glScalef(8.5,16,8.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[45].texID);
        glmDraw(punteroChimu8, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///objetos
     glPushMatrix();
        glTranslated(31.8,10,-41);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[46].texID);
        glmDraw(punteroChimu9, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glTranslated(29,10,-41);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[47].texID);
        glmDraw(punteroChimu10, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

     glPushMatrix();
        glTranslated(67.5,9,-41);
        glScalef(3.5,3.5,3.5);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[48].texID);
        glmDraw(punteroChimu11, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

     glPushMatrix();
        glTranslated(63,10,-41);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[49].texID);
        glmDraw(punteroChimu12, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
	///-----------------------------------------------------------

	///CULTURA  INCA
	///-----------------------------------------------------------
    ///HUACO 1
   glPushMatrix();
        glTranslated(63,8.5,4);
        glScalef(2.5,2.5,2.5);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[11].texID);
        glmDraw(punteroM4, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///HUACO 2
    glPushMatrix();
        glTranslated(65,8.5,9);
        glScalef(4,4,4);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[12].texID);
        glmDraw(punteroM5, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///HUACO 3
    glPushMatrix();
        glTranslated(64,8,13.5);
        glScalef(4,4,4);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[13].texID);
        glmDraw(punteroM6, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///HUACO 5
    glPushMatrix();
        glTranslated(58,8,9);
        glScalef(3,3,3);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[14].texID);
        glmDraw(punteroM7, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
     ///HUACO 6
    glPushMatrix();
        glTranslated(63,8,35);
        glScalef(15,15,15);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[15].texID);
        glmDraw(punteroM8, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
     ///HUACO 7
    glPushMatrix();
        glTranslated( 58,8.5,40);
        glScalef(10,10,10);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[16].texID);
        glmDraw(punteroM9, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
     ///HUACO 8
    glPushMatrix();
        glTranslated(63,8,45);
        glScalef(9,9,9);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[17].texID);
        glmDraw(punteroM10, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
     ///HUACO 9
    glPushMatrix();
        glTranslated(65,8,41);
        glScalef(10,10,10);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[18].texID);
        glmDraw(punteroM11, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
     ///HUACO 10
    glPushMatrix();
        glTranslated(49,9,51);
        glScalef(12,12,12);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[19].texID);
        glmDraw(punteroM12, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
     ///HUACO 11
    glPushMatrix();
        glTranslated(64,9.5,26);
        glScalef(12,12,12);
        glRotatef(girarhuaco,0,1,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[20].texID);
        glmDraw(punteroM13, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    ///MESAS
    glPushMatrix();
        glTranslated(65,0,25);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[21].texID);
        glmDraw(punteroM14, GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslated(50,0,50);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[21].texID);
        glmDraw(punteroM14, GLM_TEXTURE);
    glPopMatrix();
     glPushMatrix();
        glTranslated(70,0,15);
        glScalef(15,15,15);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[22].texID);
        glmDraw(punteroM15, GLM_TEXTURE);
    glPopMatrix();
    glPushMatrix();
        glTranslated(70,0,45);
        glScalef(15,15,15);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[22].texID);
        glmDraw(punteroM15, GLM_TEXTURE);
    glPopMatrix();
    /*glPushMatrix();
        glTranslated(35,10,0);
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[13].texID);
        glmDraw(punteroM5, GLM_TEXTURE);
    glPopMatrix();*/

    ///Telares
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[59].texID);
        glTranslatef(67,20,-25);///cambia
        glScalef(40,40,40);
        glRotatef(-180,0,0,1);
        glRotatef(90,0,1,0);
        glmDraw(Soporte_telar_nazca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, treeTextureAr[60].texID);
        glTranslatef(40,20,70);
        glScalef(40,40,40);
        glRotatef(-180,0,0,1);
        glmDraw(Soporte_telar_nazca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, treeTextureAr[61].texID);
        glTranslatef(-73,20,-5);///cambia
        glScalef(40,40,40);
        glRotatef(-180,0,0,1);
        glRotatef(90,0,1,0);
        glmDraw(Soporte_telar_nazca, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

  	glutSwapBuffers();
}

void redimensionar(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();

    ///Subventana 1
    glutSetWindow (winIdSub);
    glutPositionWindow (1500,800);
    glutSetWindow (winIdMain);

    /*///Subventana 2
    glutSetWindow (winIdSub_2);
    glutPositionWindow (700,850);
    glutSetWindow (winIdMain);*/
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(10/FPS,timer,0);
}

void camera()
{
    if(motion.Forward)
    {
        camX += cos((90)*TO_RADIANS)/5.0;
        camZ -= sin((90)*TO_RADIANS)/5.0;
        camY += cos((90)*TO_RADIANS)/5.0;
    }
    if(motion.Backward)
    {
        camX += cos((90+180)*TO_RADIANS)/5.0;
        camZ -= sin((90+180)*TO_RADIANS)/5.0;
        camY += cos((90+180)*TO_RADIANS)/5.0;
    }
    if(motion.Left)
    {
        camX += cos((90+90)*TO_RADIANS)/5.0;
        camZ -= sin((90+90)*TO_RADIANS)/5.0;
        camY += sin((90+90)*TO_RADIANS)/5.0;
    }
    if(motion.Right)
    {
        camX += cos((90-90)*TO_RADIANS)/5.0;
        camZ -= sin((90-90)*TO_RADIANS)/5.0;
        camY += sin((90-90)*TO_RADIANS)/5.0;
    }

    if(motion.Up)
    {
        camX += cos((90)*TO_RADIANS)/5.0;
        camZ += sin((90-90)*TO_RADIANS)/5.0;
        camY += cos((90-90)*TO_RADIANS)/5.0;
    }
    if(motion.Down)
    {
        camX += cos((90)*TO_RADIANS)/5.0;
        camZ += sin((90+90)*TO_RADIANS)/5.0;
        camY += cos((90+90)*TO_RADIANS)/5.0;
    }

    if(motion.Gira)
    {
        dev_x = (width/10)-camX;
        yaw= yaw + (float)dev_x/100.0;
    }
     if(motion.Reversa)
    {
        dev_x = (width/10)-camX;
        yaw= yaw - (float)dev_x/100.0;
    }

    if (bandera_1) //Ir a entrada Museo
    {
        camX = 0.0;
        camY = 15.0;
        camZ = 175.0;
        yaw = 0.0;
        bandera_1 = false;
    }

    if (bandera_2) //Ir a Chavin
    {
        camX = -9.14562;
        camY = 15.1323;
        camZ = 23.5231;
        yaw = 111.56;
        bandera_2 = false;
    }

    if (bandera_3) //Ir a Moche
    {
        camX = -36.084;
        camY = 15.1831;
        camZ = -3.06642;
        yaw = 7.96017;
        bandera_3 = false;
    }

    if (bandera_4) //Ir a Chavin
    {
        camX = 0.297632;
        camY = 15.1014;
        camZ = 32.7976;
        yaw = -3.93983;
        bandera_4 = false;
    }

    if (bandera_5) //Ir a Chimu
    {
        camX = 30.5323;
        camY = 15.1444;
        camZ = -10.411;
        yaw = -27.6898;
        bandera_5 = false;
    }

    if (bandera_6) //Ir a Inca
    {
        camX = 16.6028;
        camY = 15.0759;
        camZ = 19.5276;
        yaw = -102.89;
        bandera_6 = false;
    }

    glTranslatef(-camX,-camY,-camZ);

    glTranslatef(camX,camY,camZ);
        glRotatef(-yaw,0.0,1.0,0.0);
    glTranslatef(-camX,-camY,-camZ);
}
void keyboard(unsigned char key,int x,int y)
{
    static int info_banner = 1;
    switch(key)
    {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'I':
    case 'i':
        motion.Up = true;
        break;
    case 'O':
    case 'o':
        motion.Down = true;
        break;
    case 'G':
    case 'g':
        motion.Gira = true;
        break;
    case 'B':
    case 'b':
        motion.Reversa = true;
        break;
    ///Oculta y aparece sub-ventana
    case 'y':
    case 'Y':
        if (info_banner)
        {
            glutSetWindow (winIdSub);
            glutHideWindow ();
        }
        else
        {
            glutSetWindow (winIdSub);
            glutShowWindow ();
        };
        info_banner = !info_banner;
        break;
    case 'E':
    case 'e':
        sonido = true;
        if (sonido == true)
            sndPlaySound("condor_pasa.wav",SND_ASYNC);
        break;
    case 'N':
    case 'n':
        sonido = false;
            sndPlaySound(".wav",SND_ASYNC);
        break;
    case '1':
        bandera_1 = true;
        break;
    case '2':
        bandera_2 = true;
        break;
    case '3':
        bandera_3 = true;
        break;
    case '4':
        bandera_4 = true;
        break;
    case '5':
        bandera_5 = true;
        break;
    case '6':
        bandera_6 = true;
        break;
    }
}

void keyboard_up(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'I':
    case 'i':
        motion.Up = false;
        break;
    case 'O':
    case 'o':
        motion.Down = false;
        break;
    case 'G':
    case 'g':
        motion.Gira = false;
        break;
    case 'B':
    case 'b':
        motion.Reversa = false;
        break;
    }
}
///Movimientos Chavin---------------------------
void movetodo(int i)
{
	ypoz += 0.5;
	if (ypoz>360) ypoz = 0;
	glutPostRedisplay();
	glutTimerFunc(2, movetodo, 1);
}

void animate_1(int i)
{
	if(bandz1==true)
    {
        if(tz_1<0.105)
        {
            banderaz_1=1;
            tz_1=tz_1+0.001*banderaz_1;
        }
        else
        {
            bandz1=false;
        }
    }
    if(bandz1==false)
    {
       if(tz_1>-0.105)
        {
            banderaz_1=-1;
            tz_1=tz_1+0.001*banderaz_1;
        }
        else
        {
            bandz1=true;
        }
    }
	glutPostRedisplay();
	glutTimerFunc(2, animate_1, 1);
}
///-----------------------------

void girar(int i){
    girarhuaco+= 0.5;
	if (girarhuaco>360)
       girarhuaco = 0;
	glutPostRedisplay();
	glutTimerFunc(1,girar, 2);
}

void animatechimu (int i)
{
    ch1 += 0.99;
    if(ch1 >= 360) ch1 = 0;
    glutPostRedisplay();
	glutTimerFunc(2, animatechimu,3);
}

void subDisplay()
{
    // Establece el color de la ventana
    glutSetWindow (winIdSub);
    //glClearColor (0.25, 0.25, 0.25, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dibuja borde ventana
    glColor3f (0.0F, 1.0F, 0.0F);

    glBegin (GL_LINE_LOOP);
        glVertex2f (-0.99F, -0.99F); //inferior izquierdo
        glVertex2f (-0.99F, 0.99F); //superior izquierdo
        glVertex2f (1.0F, 0.99F); //superior derecho
        glVertex2f (1.0F, -1.0F);
    glEnd ();

    if (star==false)
    {
        glColor3f (1.0F, 1.0F, 1.0F);
        glRasterPos2f (-0.85, 0.65);
        drawStringBig("Museo Virtual de Culturas Prehispanicas\n");
        glRasterPos2f (-0.3, 0.45);
        drawString(" Bienvenid@ \n");
        glRasterPos2f (-0.6, 0.25);
        drawString("\n E: Activar audio     N: Desactivar Audio\n");

        glRasterPos2f (-0.9, 0.0);
        drawString("\n 1. Ir a la Entrada del Museo\n ");
        glRasterPos2f (0.1, 0.0);
        drawString("\n 2. Ir a la Cultura Chavin \n");

        glRasterPos2f (-0.9, -0.2);
        drawString("\n 3. Ir a la Cultura Moche \n ");
        glRasterPos2f (0.1, -0.2);
        drawString("\n 4. Ir a la Cultura Nazca\n ");

        glRasterPos2f (-0.9, -0.4);
        drawString("\n 5. Ir a la Cultura Chimu \n");
        glRasterPos2f (0.1, -0.4);
        drawString("\n 6. Ir a la Cultura Inca \n");

        glRasterPos2f (-0.2, -0.6);
        drawString("\n Navegacion \n");
        glRasterPos2f (-0.9, -0.75);
        drawString(" A - D : Derecha, Izquierda ");
        glRasterPos2f (0.1, -0.75);
        drawString(" W - S : Atras, Adelante ");
        glRasterPos2f (-0.9, -0.89);
        drawString(" I - O : Arriba, Abajo");
        glRasterPos2f (0.1, -0.89);
        drawString(" G - B : Gira ");
    }

    if (star==true)
    {
        glColor3f (1.0F, 1.0F, 1.0F);
        glRasterPos2f (-0.8, 0.5);
        drawStringBig("Museo de\n ");
    }

   glutSwapBuffers ();
};

void subDisplay_2()
{
    // Establece el color de la ventana
    glutSetWindow (winIdSub_2);
    glClearColor ( color(83), color(107), color(141), 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dibuja borde ventana
    //glColor3f (0.0F, 1.0F, 0.0F);

    glBegin (GL_LINE_LOOP);
        glVertex2f (-0.99F, -0.99F); //inferior izquierdo
        glVertex2f (-0.99F, 0.99F); //superior izquierdo
        glVertex2f (1.0F, 0.99F); //superior derecho
        glVertex2f (1.0F, -1.0F);
    glEnd ();

    glutSwapBuffers ();
};

void subReshape (int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glMatrixMode(GL_MODELVIEW);
};

void subReshape_2 (int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glMatrixMode(GL_MODELVIEW);
};

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1800, 1000);
	glutInitWindowPosition(100, 0);

	winIdMain = glutCreateWindow("Museo Peruano");
	init();

	///Punteros
	//punteroM1 = glmReadOBJ("modelos/conmuros.obj");    //sinpuerta
	punteroM1 = glmReadOBJ("modelos/museofirme3.obj");    //sinpuerta
	marcopuerta = glmReadOBJ("modelos/marcopuerta.obj");
	punteroM2 = glmReadOBJ("modelos/grass.obj");
	puerta = glmReadOBJ("modelos/puerta.obj");
	nube = glmReadOBJ("modelos/nubes.obj");
	avatar = glmReadOBJ("modelos/avatar2.obj");
	escultura= glmReadOBJ("modelos/escultura1.obj");
	///CULTURA  CHAVIN
	///-----------------------------------------------------------
    punterosoporte1 = glmReadOBJ("modelos/chavin/Soporte.obj");
    punteroobelisco = glmReadOBJ("modelos/chavin/obelisco.obj");
    punterolanzon = glmReadOBJ("modelos/chavin/lanzon.obj");
    punterocabeza1 = glmReadOBJ("modelos/chavin/cabeza1.obj");
    punterocabeza2 = glmReadOBJ("modelos/chavin/cabeza2.obj");
    punterojarra = glmReadOBJ("modelos/chavin/jarra.obj");
    punteroestatua = glmReadOBJ("modelos/chavin/estatua.obj");
    punterobotella1 = glmReadOBJ("modelos/chavin/botella1.obj");
    punterobotella2 = glmReadOBJ("modelos/chavin/botella2.obj");
	///-----------------------------------------------------------

	///CULTURA  NAZCA
	///-----------------------------------------------------------
    Inca = glmReadOBJ("modelos/Nazca/Inca.obj");
    Soporte_telar_nazca = glmReadOBJ("modelos/Nazca/Soporte_telar_nazca.obj");
	Soporte = glmReadOBJ("modelos/Nazca/Soporte.obj");
	Soporte2 = glmReadOBJ("modelos/Nazca/Soporte2.obj");
    orca_nazca = glmReadOBJ("modelos/Nazca/orca_nazca.obj");
	Obj1_nasca = glmReadOBJ("modelos/Nazca/objeto01_nasca.obj");
    Obj2_nasca = glmReadOBJ("modelos/Nazca/objeto02_nasca.obj");
    Obj18_nasca = glmReadOBJ("modelos/Nazca/objeto18_nasca.obj");
    Obj19_nasca = glmReadOBJ("modelos/Nazca/objeto19_nasca.obj");
    Figurina_Nazca = glmReadOBJ("modelos/Nazca/Figurina_Nazca.obj");
    nazca_fish = glmReadOBJ("modelos/Nazca/nazca_fish.obj");
    objeto11_nasca = glmReadOBJ("modelos/Nazca/objeto11_nasca.obj");
    objeto05_nasca = glmReadOBJ("modelos/Nazca/objeto05_nasca.obj");
    objeto12_nasca = glmReadOBJ("modelos/Nazca/objeto12_nasca.obj");
    objeto06_nasca = glmReadOBJ("modelos/Nazca/objeto06_nasca.obj");
    objeto04_nasca = glmReadOBJ("modelos/Nazca/objeto04_nasca.obj");
	///-----------------------------------------------------------

	///CULTURA  MOCHE
	///-----------------------------------------------------------
    M3 = glmReadOBJ("modelos/moche/huaco01.obj");
	M4 = glmReadOBJ("modelos/moche/huaco02.obj");
	M5 = glmReadOBJ("modelos/moche/huaco03.obj");
	M6 = glmReadOBJ("modelos/moche/huaco04.obj");
	M7 = glmReadOBJ("modelos/moche/Table.obj");
    M8 = glmReadOBJ("modelos/moche/huaco05.obj");
    M9 = glmReadOBJ("modelos/moche/huaco06.obj");
	///-----------------------------------------------------------

	///CULTURA  CHIMÚ
	///-----------------------------------------------------------
    punteroChimu1 = glmReadOBJ("modelos/chimu/MesasApiladas.obj");
	punteroChimu2 = glmReadOBJ("modelos/chimu/chimu2.obj");
    punteroChimu3 = glmReadOBJ("modelos/chimu/chimu3.obj");
    punteroChimu4 = glmReadOBJ("modelos/chimu/chimu4.obj");
    punteroChimu5 = glmReadOBJ("modelos/chimu/chimu5.obj");
    punteroChimu6 = glmReadOBJ("modelos/chimu/chimu6.obj");
    punteroChimu7 = glmReadOBJ("modelos/chimu/mesanegra.obj");
    punteroChimu8 = glmReadOBJ("modelos/chimu/mesanegra.obj");
    punteroChimu9 = glmReadOBJ("modelos/chimu/chimu7.obj");
    punteroChimu10 = glmReadOBJ("modelos/chimu/chimu8.obj");
    punteroChimu11 = glmReadOBJ("modelos/chimu/chimu9.obj");
    punteroChimu12 = glmReadOBJ("modelos/chimu/chimu10.obj");
	///-----------------------------------------------------------

	///CULTURA  INCA
	///-----------------------------------------------------------
    punteroM4 = glmReadOBJ("modelos/inca/uno.obj");
	punteroM5 = glmReadOBJ("modelos/inca/dos.obj");
	punteroM6 = glmReadOBJ("modelos/inca/tres.obj");
	punteroM7 = glmReadOBJ("modelos/inca/cinco.obj");
	punteroM8 = glmReadOBJ("modelos/inca/seis.obj");
	punteroM9 = glmReadOBJ("modelos/inca/siete.obj");
	punteroM10 = glmReadOBJ("modelos/inca/ocho.obj");
	punteroM11 = glmReadOBJ("modelos/inca/nueve.obj");
	punteroM12 = glmReadOBJ("modelos/inca/diez.obj");
	punteroM13 = glmReadOBJ("modelos/inca/once.obj");
    punteroM14 = glmReadOBJ("modelos/inca/Table.obj");
    punteroM15 = glmReadOBJ("modelos/inca/mesanegra.obj");
	///-----------------------------------------------------------

	glutDisplayFunc(graficar);
	glutReshapeFunc(redimensionar);
    glutTimerFunc(0,timer,0);    //more info about this is given below at definition of timer()
    glutTimerFunc(1,abrirpuerta, 2);
    ///-----------------------------------------------------------
    ///CHAVIN Y NAZCA
    glutTimerFunc(2, movetodo, 1);
    glutTimerFunc(2, animate_1, 1);
    ///CHIMU
    glutTimerFunc(2, animatechimu,3);
    ///INCA
    glutTimerFunc(5,girar, 1);
    ///-----------------------------------------------------------

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    ///Creación: Sub - Ventana 1 - Menú
    winIdSub = glutCreateSubWindow (winIdMain,1500,800,400,200); //ventana y: vertical x:horizontal
        glutDisplayFunc (subDisplay);
        glutReshapeFunc (subReshape);

    /*///Creación: Sub - Ventana
    winIdSub_2 = glutCreateSubWindow (winIdMain,700,850,500,200); //ventana y: vertical x:horizontal
        glutDisplayFunc (subDisplay_2);
        glutReshapeFunc (subReshape_2);*/

    ///Instrucciones y Autores
    cout << "\n |Museo de Culturas Prehispanicas Peruanas |";
    cout << "\n\n\n Creadores - Autores:";
    cout << "\n . Julian Garcia Fabricio";
    cout << "\n . Mendez Cruz Angely";
    cout << "\n . Mendez Cruz Ciara";
    cout << "\n . Padilla Leyva Valentina";
    cout << "\n . Recalde Monzon Angie";

    cout << "\n\n Presione Y o y : para ocultar la subventana";

	glutMainLoop();
	return 0;
}
