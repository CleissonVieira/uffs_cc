/**
 * Simple demonstration of transformations.
 */

#include <GL/glut.h>
#include <GL/gl.h>

void renderCoordinateAxis()
{
	// X axis - green color
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		// Left side, negative X
		glVertex2f(-1.0, 0.0);
		glVertex2f(0.0, 0.0);

		// Right side, positive X
		glVertex2f(0.0, 0.0);
		glVertex2f(1.0, 0.0);
	glEnd();

	// Y axis - blue color
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		// Top side, positive Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);

		// Bottom side, negative Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -1.0);
	glEnd();
}

void torre(){
	glPushMatrix();

	//Cubos da base de cima da torre
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.0, 0.0, 0.0);
			glTranslatef(0.0, 0.62, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.0, 0.0, 0.0);
			glTranslatef(0.0, 0.71, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(-0.14, 0.0, 0.0);
			glTranslatef(0.0, 0.655, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.14, 0.0, 0.0);
			glTranslatef(0.0, 0.655, 0.0);
			glutSolidCube(0.08);
		glPopMatrix();

	//Base de cima
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glScalef(0.45, 0.45, 0.45);
			glTranslatef(0.0, 1.23, 1.0);
			glRotatef(25, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(0.20, 0.25, 10, 10);
		glPopMatrix();

	//Corpo meio
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glTranslatef(0.0, 0.3, 1.0);
			glScalef(.5, 1, .5);
			glutSolidCube(0.5);
		glPopMatrix();


	//Bases de baixo
		glPushMatrix();
			glColor3f(0., 0., 0.);
			glScalef(0.45, 0.45, 0.45);
			glTranslatef(0.0, 0.0, 1.0);
			glRotatef(25, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(0.20, 0.25, 10, 10);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0., 0., 0.);
			glScalef(0.5,0.5,0.5);
			glTranslatef(0.0, -0.1, 1.0);
			glRotatef(25, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 0, 1, 0);
			glutSolidTorus(0.20, 0.25, 10, 10);
		glPopMatrix();
	glPopMatrix();
	
}

void display()
{
	// Clear the screen painting it all with the white color
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Inform OpenGL we want to make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	
	// Render the X and Y axis to guide ourselves.
	renderCoordinateAxis();

	torre();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		// ESC key
		exit(0);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Transformation - Simple");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}