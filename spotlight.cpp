#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "first.h"

/* Some <math.h> files do not define M_PI... */
#ifndef M_PI
#define M_PI 3.14159265
#endif
void *currentfont;
#define TWO_PI	(2*M_PI)
void Start1();
void drawstring(GLfloat x, GLfloat y, const char *string)
{
	const char *c;
	glRasterPos2f(x, y);
	for (c = string;
		*c != '\0';
		c++)
	{
		glutBitmapCharacter(currentfont, *c);
	}
}
typedef struct lightRec {
	float amb[4];
	float diff[4];
	float spec[4];
	float pos[4];
	float spotDir[3];
	float spotExp;
	float spotCutoff;
	float atten[3];

	float trans[3];
	float rot[3];
	float swing[3];
	float arc[3];
	float arcIncr[3];
} Light;

static int useSAME_AMB_SPEC = 1;
/* *INDENT-OFF* */
static float modelAmb[4] = { 0.2, 0.2, 0.2, 1.0 };

static float matAmb[4] = { 0.2, 0.2, 0.2, 1.0 };
static float matDiff[4] = { 0.8, 0.8, 0.8, 1.0 };
static float matSpec[4] = { 0.4, 0.4, 0.4, 1.0 };
static float matEmission[4] = { 0.0, 0.0, 0.0, 1.0 };
/* *INDENT-ON* */

int NUM_LIGHTS = 6;
static Light spots[] =
{

  {
	{0.2, 0.0, 0.0, 1.0},  /* ambient */
	{0.8, 0.0, 0.0, 1.0},  /* diffuse */
	{0.4, 0.0, 0.0, 1.0},  /* specular */
	{0.0, 0.0, 0.0, 1.0},  /* position */
	{0.0, -1.0, 0.0},   /* direction */
	{20.0},
	{60.0},             /* exponent, cutoff */
	{1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
	{0.0, 0.0, 0.0},    /* rotation */
	{20.0, 0.0, 40.0},  /* swing */
	{0.0, 0.0, 0.0},    /* arc */
	{TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  },

  {
	{0.0, 0.2, 0.0, 1.0},  /* ambient */
	{0.0, 0.8, 0.0, 1.0},  /* diffuse */
	{0.0, 0.4, 0.0, 1.0},  /* specular */
	{0.0, 0.0, 0.0, 1.0},  /* position */
	{0.0, -1.0, 0.0},   /* direction */
	{20.0},
	{60.0},             /* exponent, cutoff */
	{1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
	{0.0, 0.0, 0.0},    /* rotation */
	{20.0, 0.0, 40.0},  /* swing */
	{0.0, 0.0, 0.0},    /* arc */
	{TWO_PI / 120.0, 0.0, TWO_PI / 60.0}  /* arc increment */
  },
  {
	{0.0, 0.0, 0.2, 1.0},  /* ambient */
	{0.0, 0.0, 0.8, 1.0},  /* diffuse */
	{0.0, 0.0, 0.4, 1.0},  /* specular */
	{0.0, 0.0, 0.0, 1.0},  /* position */
	{0.0, -1.0, 0.0},   /* direction */
	{20.0},
	{60.0},             /* exponent, cutoff */
	{1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
	{0.0, 0.0, 0.0},    /* rotation */
	{20.0, 0.0, 40.0},  /* swing */
	{0.0, 0.0, 0.0},    /* arc */
	{TWO_PI / 50.0, 0.0, TWO_PI / 100.0}  /* arc increment */
  },
  {
	{0.2, 0.0, 0.0, 1.0},  /* ambient */
	{0.5, 0.8, 0.0, 1.0},  /* diffuse */
	{0.4, 0.0, 0.0, 1.0},  /* specular */
	{0.0, 0.0, 0.0, 1.0},  /* position */
	{0.0, -1.0, 0.0},   /* direction */
	{20.0},
	{60.0},             /* exponent, cutoff */
	{1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
	{0.0, 0.0, 0.0},    /* rotation */
	{20.0, 0.0, 40.0},  /* swing */
	{0.0, 0.0, 0.0},    /* arc */
	{TWO_PI / 30.0, 0.0, TWO_PI / 10.0}  /* arc increment */
  },
  {
	{0.0, 0.0, 0.2, 1.0},  /* ambient */
	{0.4, 0.2, 0.3, 1.0},  /* diffuse */
	{0.0, 0.0, 0.4, 1.0},  /* specular */
	{0.0, 0.0, 0.0, 1.0},  /* position */
	{0.0, -1.0, 0.0},   /* direction */
	{20.0},
	{60.0},             /* exponent, cutoff */
	{1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
	{0.0, 0.0, 0.0},    /* rotation */
	{20.0, 0.0, 40.0},  /* swing */
	{0.0, 0.0, 0.0},    /* arc */
	{TWO_PI / 5.0, 0.0, TWO_PI / 130.0}  /* arc increment */
  },
  {
	{0.0, 0.0, 0.2, 1.0},  /* ambient */
	{0.43, 1.0, 0.8, 1.0},  /* diffuse */
	{0.0, 0.0, 0.4, 1.0},  /* specular */
	{0.0, 0.0, 0.0, 1.0},  /* position */
	{0.0, -1.0, 0.0},   /* direction */
	{20.0},
	{60.0},             /* exponent, cutoff */
	{1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
	{0.0, 0.0, 0.0},    /* rotation */
	{20.0, 0.0, 40.0},  /* swing */
	{0.0, 0.0, 0.0},    /* arc */
	{TWO_PI / 50.0, 0.0, TWO_PI / 100.0}  /* arc increment */
  }
};

static void usage(char *name)
{
	printf("\n");
	printf("usage: %s [options]\n", name);
	printf("\n");
	printf("  Options:\n");
	printf("    -geometry Specify size and position WxH+X+Y\n");
	printf("    -lm       Toggle lighting(SPECULAR and AMBIENT are/not same\n");
	printf("\n");
#ifndef EXIT_FAILURE /* should be defined by ANSI C <stdlib.h> */
#define EXIT_FAILURE 1
#endif
	exit(EXIT_FAILURE);
}
void man()
{
glColor3f(0, 1, 0);							//Droid1
glBegin(GL_POLYGON);						//Head
glVertex2f(110, 145);
glVertex2f(110, 155);
glVertex2f(115, 165);
glVertex2f(125, 170);
glVertex2f(135, 165);
glVertex2f(140, 155);
glVertex2f(140, 145);
glEnd();

glLineWidth(7);
glBegin(GL_LINES);
glVertex2f(130, 165);
glVertex2f(135, 180);
glVertex2f(125, 165);
glVertex2f(123, 180);
glEnd();

glBegin(GL_POLYGON);						//Body
glVertex2f(110, 140);
glVertex2f(110, 80);
glVertex2f(140, 80);
glVertex2f(140, 140);
glEnd();

glLineWidth(15);							//Legs
glBegin(GL_LINES);
glVertex2f(122, 80);
glVertex2f(120, 55);
glVertex2f(130, 80);
glVertex2f(130, 55);
glEnd();

glLineWidth(17);							//Hand
glBegin(GL_LINES);
glVertex2f(135, 125);
glVertex2f(155, 140);
glEnd();

glColor3f(0, 0, 0);							//Eye
glPointSize(7);
glBegin(GL_POINTS);
glVertex2f(132, 155);
glEnd();
}
static void initLights(void)
{
	int k;
	for (k = 0; k < NUM_LIGHTS; ++k) {
		int lt = GL_LIGHT0 + k;
		Light *light = &spots[k];

		glEnable(lt);
		glLightfv(lt, GL_AMBIENT, light->amb);
		glLightfv(lt, GL_DIFFUSE, light->diff);

		if (useSAME_AMB_SPEC)
			glLightfv(lt, GL_SPECULAR, light->amb);
		else
			glLightfv(lt, GL_SPECULAR, light->spec);

		glLightf(lt, GL_SPOT_EXPONENT, light->spotExp);
		glLightf(lt, GL_SPOT_CUTOFF, light->spotCutoff);
		glLightf(lt, GL_CONSTANT_ATTENUATION, light->atten[0]);
		glLightf(lt, GL_LINEAR_ATTENUATION, light->atten[1]);
		glLightf(lt, GL_QUADRATIC_ATTENUATION, light->atten[2]);
	}
}

static void aimLights(void)
{
	int k;

	for (k = 0; k < NUM_LIGHTS; ++k) {
		Light *light = &spots[k];

		light->rot[0] = light->swing[0] * sin(light->arc[0]);
		light->arc[0] += light->arcIncr[0];
		if (light->arc[0] > TWO_PI)
			light->arc[0] -= TWO_PI;

		light->rot[1] = light->swing[1] * sin(light->arc[1]);
		light->arc[1] += light->arcIncr[1];
		if (light->arc[1] > TWO_PI)
			light->arc[1] -= TWO_PI;

		light->rot[2] = light->swing[2] * sin(light->arc[2]);
		light->arc[2] += light->arcIncr[2];
		if (light->arc[2] > TWO_PI)
			light->arc[2] -= TWO_PI;
	}
}

static void setLights(void)
{
	int k;

	for (k = 0; k < NUM_LIGHTS; ++k) {
		int lt = GL_LIGHT0 + k;
		Light *light = &spots[k];

		glPushMatrix();
		glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
		glRotatef(light->rot[0], 1, 0, 0);
		glRotatef(light->rot[1], 0, 1, 0);
		glRotatef(light->rot[2], 0, 0, 1);
		glLightfv(lt, GL_POSITION, light->pos);
		glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
		glPopMatrix();
	}
}

static void drawLights(void)
{
	int k;

	glDisable(GL_LIGHTING);
	for (k = 0; k < NUM_LIGHTS; ++k) {
		Light *light = &spots[k];

		glColor4fv(light->diff);

		glPushMatrix();
		glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
		glRotatef(light->rot[0], 1, 0, 0);
		glRotatef(light->rot[1], 0, 1, 0);
		glRotatef(light->rot[2], 0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(light->pos[0], light->pos[1], light->pos[2]);
		glVertex3f(light->spotDir[0], light->spotDir[1], light->spotDir[2]);
		glEnd();
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
}

static void drawPlane(int w, int h)
{
	int i, j;
	float dw = 1.0 / w;
	float dh = 1.0 / h;

	glNormal3f(0.0, 0.0, 1.0);
	for (j = 0; j < h; ++j) {
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= w; ++i) {
			glVertex2f(dw * i, dh * (j + 1));
			glVertex2f(dw * i, dh * j);
		}
		glEnd();
	}
}

int spin = 0;

void display(void)
{
	if (NUM_LIGHTS > 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glRotatef(spin, 0, 1, 0);

		aimLights();
		setLights();

		glPushMatrix();
		glRotatef(-90.0, 1, 0, 0);
		glScalef(1.9, 1.9, 1.0);
		glTranslatef(-0.5, -0.5, 0.0);
		drawPlane(16, 16);
		glPopMatrix();

		drawLights();
		glPopMatrix();

		glutSwapBuffers();
	}
	else
	{

	}
}

void animate(void)
{
	spin += 0.5;
	if (spin > 360.0)
		spin -= 360.0;
	glutPostRedisplay();
}

void visibility(int state)
{
	if (state == GLUT_VISIBLE) {
		glutIdleFunc(animate);
	}
	else {
		glutIdleFunc(NULL);
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':NUM_LIGHTS++;
		printf("%d\n", NUM_LIGHTS);
		glutDisplayFunc(display);
		break;
	case 'b':NUM_LIGHTS--;
		glutPostRedisplay();
		printf("%d\n", NUM_LIGHTS);
		if (NUM_LIGHTS == 0)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			/*delay();
			glColor3f(0, 0, 1);*/
			printf("Party Over\n");
			//drawstring(250, 250, "Party Over");
			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
			glutInitWindowSize(1000, 1000);
			glutCreateWindow("SPOTLIGHT");
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0, 500, 0, 500);
			Start1();
			glFlush();
			glutKeyboardFunc(keyboard);
		}
		break;
	case 'q':exit(0);
	/*case 'd':man();
		break;*/
	default:
		printf("No Function for this key\n");
		break;
	}
}
void setFont(void *font)
{
	currentfont = font;
}
int spotmain()
{
	int i;
	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	/* process commmand line args
	for (i = 1; i < argc; ++i) {
		if (!strcmp("-lm", argv[i])) {
			useSAME_AMB_SPEC = !useSAME_AMB_SPEC;
		}
		else {
			usage(argv[0]);
		}
	}*/

	glutCreateWindow("SPOTLIGHT");

	glutDisplayFunc(display);
	glutVisibilityFunc(visibility);

	glMatrixMode(GL_PROJECTION);
	glFrustum(-1, 1, -1, 1, 2, 6);

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0, 0.0, -3.0);
	glRotatef(45.0, 1, 0, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glutKeyboardFunc(keyboard);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0);

	initLights();

	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}
