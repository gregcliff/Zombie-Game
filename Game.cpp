#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <cstdio>
#include <fstream>
#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include <AL\al.h>
#include <AL\alc.h>


#ifdef __APPLE__
#include <GLUT/glut.h>  //apple include line
#else
#include <GL/glut.h> //linux and windows include line
#endif
#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096

using namespace std;

const int NUMKEYS = 256;
char keys[NUMKEYS];

struct MainGraphics {
	int winheight, winwidth;
	bool enableBlend;
	GLfloat light[4];
};

MainGraphics graph;
Player *player;
vector<Zombie> zombies;
vector<Bullet> bullets;
GLfloat *light1_position;
int zombiesKilled = 47;
vector<string> gameStats;
Level stage;
Timer timer;
GLfloat *spot_direction;
int circleQuality = 20;
int pid, files[2];
ALCdevice *dev;
ALCcontext *ctx;
struct stat statbuf;
bool superZombieSpawned = false;
bool pMouse = false;
bool pLevelUp = false;
FILE *f;
void drawCircle(int, int, float, int);
void mydisplay();
void init();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void text(string, float, float);
void mouse(int button, int state, int x, int y);
void reshape(int, int);
void idle(); 
void initSound();
void passiveMotionFunc(int x, int y);
void activeMotionFunc(int x, int y);


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	init();
	//initSound();
	glutMainLoop();
	zombies.clear();
}

void initSound() {
	//sound
	dev = alcOpenDevice(NULL);
	if (!dev)
	{
		fprintf(stderr, "Oops\n");
		return;
	}
	ctx = alcCreateContext(dev, NULL);
	alcMakeContextCurrent(ctx);
	if (!ctx)
	{
		fprintf(stderr, "Oops2\n");
		return;
	}
	alGetError();
	ALuint buffers[NUM_BUFFERS];

	// Create the buffers
	alGenBuffers(NUM_BUFFERS, buffers);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("buffer error");
		return;
	}
	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	ALboolean  loop;
	ALvoid*    data;

	
	
}

//the initialization function
void init() {
	graph.enableBlend = true;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	graph.winwidth = graph.winheight = 700;
	glutInitWindowSize(graph.winwidth, graph.winheight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Greg");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passiveMotionFunc);
	glutMotionFunc(activeMotionFunc);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.1, 1.0, 0.1);

	glEnable(GL_LIGHTING);
	GLfloat light1_ambient[] = { 1, 1, 1, 1 };
	GLfloat light1_diffuse[] = { 1, 1, 1, 1 }; // , 0.1

	GLfloat light1_specular[] = { 0.0, 0.2, 0.5, 0.1 };
	light1_position = new GLfloat[4];
	light1_position[0] = light1_position[1] = 250.0;
	light1_position[2] = 0.0;
	light1_position[3] = 1; 

	GLfloat lmodel_ambient[] = { 0.02, 0.02, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


	GLfloat light0_position[] = { 0, 0, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	spot_direction = new GLfloat[] { 1.0, 1.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.005);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);//half cone
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
	glEnable(GL_LIGHT1);

	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();

	glOrtho(0, graph.winwidth, 0, graph.winheight, -100, 100);
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	glLineWidth(1);

	stage.startXBound = 0;
	stage.endXBound = graph.winwidth;
	stage.startYBound = 0;
	stage.endYBound = graph.winheight;
	stage.setManagerSpawnTime(2500);
	//stage.init();
	stage.addSpawn(0, 0);
	stage.addSpawn(graph.winwidth, 0);
	stage.addSpawn(graph.winwidth, graph.winheight);
	stage.addSpawn(0, graph.winheight);

	player = new Player(stage.startXBound, stage.endXBound, stage.startYBound, stage.endYBound);
	player->x = graph.winwidth / 2;
	player->y = graph.winheight / 2;
	player->radius = 10;
	player->setSpeed(5);
	
	string score = "Zombies killed: ";
	string weapon = player->weapon->getName();
	string ammo = "";
	gameStats.push_back(score);
	gameStats.push_back(weapon);
	gameStats.push_back(ammo);
}

void text(string s, float x, float y) {
	glRasterPos2d(x, y);
	unsigned int i = 0;
	for (; i < s.length(); i++)     {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);

	}
}


void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	graph.winheight = h;
	graph.winwidth = w;
}


void mydisplay() {

	glClear(GL_COLOR_BUFFER_BIT);
	light1_position[0] = player->x;
	light1_position[1] = player->y;
	float length = sqrtf((player->aimX - player->x)*(player->aimX - player->x) + 
		(player->aimY - player->y)*(player->aimY - player->y));
	spot_direction[0] = (player->aimX - player->x)/length;
	spot_direction[1] = (player->aimY - player->y)/length;
	
	glDisable(GL_LIGHTING);
	glColor3f(.31, .31, 0);
	glPushMatrix();
	glTranslatef(player->x, player->y, 0);
	glRotatef(atan2(spot_direction[1], spot_direction[0]) * 180 / 3.141 - 45, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex2f(0, 0);
	glColor3f(0, 0, 0);
	glVertex2f(1000, 0);
	glColor3f(0, 0, 0);
	glVertex2f(0, 1000);

	glEnd();
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	/*light1_position[0] = 100.0;
	light1_position[1] = 0.8;
	light1_position[2] = 0.0;
	light1_position[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHT1);*/
	
	for (int i = 0; i < stage.walls.size(); i++) {
		/*glRectf(stage.getRectIndex(i), stage.getRectIndex(i + 1),
			stage.getRectIndex(i + 2), stage.getRectIndex(i + 3));*/
		Wall wall = stage.getWall(i);
		glRectf(wall.sx, wall.sy, wall.ex, wall.ey);
	}

	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < bullets.size(); i++) {
		glVertex2d(bullets.at(i).getCurrentX(), bullets.at(i).getCurrentY());
		glVertex2d(bullets.at(i).getNextX(), bullets.at(i).getNextY());
	}
	
	glEnd();


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColor4f(1.0f, 0.0f, 0.0f, 1);
	glPushMatrix();
	glTranslatef(player->x, player->y, 0);
	glutSolidSphere(player->radius,20,20);
	glPopMatrix();
//	drawCircle(player->x, player->y, player->radius, circleQuality);
	glDisable(GL_LIGHT0);

	GLfloat green[] = {0, .3, 0, 1 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, green);
	glColor4f(1.0f, 1.0f, 0.0f, 1);
	for (int i = 0; i < zombies.size(); i++) {
		float x = zombies.at(i).getX() - player->x;
		float y = zombies.at(i).getY() - player->y;
		float len = 1.0f / sqrt(x*x + y*y);
		x *= len;
		y *= len;
		GLfloat light1_ambient[] = { .01, .01, .01, 1 };
		GLfloat light1_ambientb[] = {0,0,0,1 };
		
		if (x * spot_direction[0] +
			y * spot_direction[1] > cos(3.1415*0.25)){
			float start = 300;
			
			if (len > 1.0f / start) len = 1.0f / start;
			light1_ambient[1] = len*start*0.5;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);

		}
		else {
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambientb);
		}

		glPushMatrix();
		glTranslatef(zombies.at(i).getX(), zombies.at(i).getY(),  0);
		glutSolidSphere(zombies.at(i).getRadius(), 20, 20);
		glPopMatrix();
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	char *mo = new char[5];
	char *shotsFired = new char[3];
	char *totalShots = new char[3];
	sprintf_s(mo, 5, "%d", zombiesKilled);
	sprintf_s(shotsFired, 3, "%d", (player->weapon->getClipSize() - player->weapon->getShotsFired()));
	sprintf_s(totalShots, 3, "%d", player->weapon->getClipSize());
	string show = gameStats.at(0) + " " + mo;
	string show2 = player->weapon->getName();
	string show3 = shotsFired;
	glDisable(GL_LIGHTING);
	text(show, 200, 200);
	text(show2, 200, 150);
	text(show3, 200, 100);
	delete[] mo;
	delete[] shotsFired;
	delete[] totalShots;
	glEnable(GL_LIGHTING);
	//glBegin(GL_LINES);
	//glVertex2d(player.x, player.y);
	//glVertex2d(player.aimX, player.aimY);
	//glEnd();
	glutSwapBuffers();//double buffer only
}

void keyboardUp(unsigned char key, int x, int y) {
	keys[key] = false;
	if (key == 'f') pMouse = false;
}

//the keyboard function
void keyboard(unsigned char key, int x, int y) {
	y = graph.winheight - y;
	keys[key] = true;
	
	if (key == 27) exit(0);
	if (key == '1') player->setWeapon(0);
	if (key == '2') player->setWeapon(1);
	if (key == '3') player->setWeapon(2);
	if (key == 'r') player->reloadWeapon();
	if (key == 'f') {
		vector<Bullet> *newBullets = player->fireWeapon();
		for (int i = 0; i < newBullets->size(); i++) {
			bullets.push_back(newBullets->at(i));
		}
		pMouse = true;
	}
}

void mouse(int button, int state, int x, int y) {
	y = graph.winheight - y;

	player->aimX = player->x + 100*(x-player->x);
	player->aimY = player->y + 100*(y-player->y);

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		//Bullet bullet = Bullet(player->x, player->y, x, y, 2);
		vector<Bullet> *newBullets = player->fireWeapon();
		for (int i = 0; i < newBullets->size(); i++) {
			newBullets->at(i).setDamage(player->weapon->damage);
			bullets.push_back(newBullets->at(i));
		}
		pMouse = true;
	}
	else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		pMouse = false;
	}
	
	//if the mouse is clicked - redraw
	glutPostRedisplay();

}


void motionFunc(int x, int y) {
}

void drawCircle(int x, int y, float radius, int numPoints) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x, y);
	for (int i = 0; i <= numPoints; i++)
	{
		float t = 2.0f *3.1459f * (float)i / (float)numPoints;
		float nx = radius * cosf(t);
		float ny = radius * sinf(t);
		glVertex2d(x + nx, y + ny);
	}
	glEnd();
	return;
}

//idle is what to do when you're not rendering
//display only happens once until glutpostredisplay is called
//between redisplays - idle happens
void idle()  {
	for (int i = 0; i < stage.spawnCount(); i++) {
		if (stage.getSpawn(i).isReady(zombies) && zombies.size() < 20) {
			zombies.push_back(stage.getSpawn(i).nextZombie());
		}
	}

	if (pMouse) {
		vector<Bullet> *newBullets = player->fireWeapon();
		for (int i = 0; i < newBullets->size(); i++) {
			newBullets->at(i).setDamage(player->weapon->damage);
			bullets.push_back(newBullets->at(i));
		}
	}

	if (!pLevelUp){
		stage.checkEnvironment();
		if (zombiesKilled % 10 == 0 && zombiesKilled > 0) {
			superZombieSpawned = false;
			pLevelUp = true;
			stage.setManagerSpawnTime(stage.getManagerSpawnTime() - 50);
			int spawnGroup = 0;
			if (zombiesKilled % 50 == 0) {
				spawnGroup = zombiesKilled / 50 * 5;
				player->increaseWeaponDamage(.1f);
			}
			for (int i = 0; i < spawnGroup; i++) {
				stage.getSpawn(rand()%4).queueZombie(100);
			}
		}
	}

	if (zombiesKilled % 10 > 0){
		pLevelUp = false;
	}

	if (zombiesKilled > 0 && zombiesKilled % 20 == 0 && !superZombieSpawned) {
		player->decreaseReloadTime(100);
		superZombieSpawned = true;
		int r = (rand() % (zombiesKilled / 20)) + 1;
		for (int i = 0; i < r; i++) stage.getSpawn(rand() % 4).queueSuperZombie();
	}

	player->setDirection(keys);
	player->move(zombies, stage.walls);

	for (int i = 0; i < zombies.size(); i++) {
		zombies.at(i).move(player->x, player->y, player->radius, zombies);
	}

	for (int i = 0; i < bullets.size(); i++) {
		if (bullets.at(i).life.elapsed() > 3000) {
			bullets.erase(bullets.begin() + i);
			continue;
		}
		bullets.at(i).update();
		for (int j = 0; j < zombies.size(); j++) {
			Zombie *zom = &zombies.at(j);
			float xdif = (bullets.at(i).getNextX() - zom->getX())*(bullets.at(i).getNextX() - zom->getX());
			float ydif = (bullets.at(i).getNextY() - zom->getY())*(bullets.at(i).getNextY() - zom->getY());
			if ((float)zom->getRadius() >= sqrtf(xdif + ydif))
			{
				zom->health -= bullets.at(i).damage;
				if (zom->health <= 0) {
					zombies.erase(zombies.begin() + j);
					zombiesKilled++;
				}
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}

	glutPostRedisplay();
}

void activeMotionFunc(int x, int y) {
	player->aimX = x;
	player->aimY = graph.winheight-y;
}

void passiveMotionFunc(int x, int y) {
	player->aimX = x;
	player->aimY = graph.winheight-y;
}

