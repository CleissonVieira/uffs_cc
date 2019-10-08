/**
 * Basic usege of OpenGL and GLFW. 
 */

#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

float x1 = -0.2f, x2 = 0.2f;
float y1 = 0.2f, y2 = -0.2f;
float sx = 0.5, sy = 0.5;
float vel = 0.0001, sent;


int main() {
	GLFWwindow* window;
	int width, height;

	if (!glfwInit()) {
		std::cout << "Problem to initialize GLFW" << std::endl;
		exit(1);
	}
	
	window = glfwCreateWindow(WIDTH, HEIGHT, "Atividade 1, GLFW!", NULL, NULL);

	if (!window) {
		std::cout << "Problem to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	while(glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) == 0) {
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //cor de fundo

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o caminho por onde os vértices passam
															//se desabilitar preenche com a cor do vértice por onde passa

		glLoadIdentity();

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		/*
		if(glfwGetKey(window, GLFW_KEY_2)){
			glScaled(2.f, 2.f, 0.f);
		}if(glfwGetKey(window, GLFW_KEY_3)){
			glScaled(3.f, 3.f, 0.f);
		}if(glfwGetKey(window, GLFW_KEY_4)){
			glScaled(4.f, 4.f, 0.f);
		}*/
		
		if(x1 <= -0.8){
			sent = +1;
		}else if(x1 >= 0.2){
			sent = -1;
		}

		if(sent > 0 && x1 <= 0.2){
			x1 += vel;
			x2 += vel;
			y1 -= vel;
			y2 -= vel;
			glScalef(1.f + vel, 1.f + vel, 0.f);
		}else{
			x1 -= vel;
			x2 -= vel;
			y1 += vel;
			y2 += vel;
			glScalef(2.f + vel, 2.f + vel, 0.f);
		}

		
		glBegin(GL_LINES);
			//Quadrado 1
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x1, y1, 0.f);
			glVertex3f(x2, y1, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x2, y1, 0.f);
			glVertex3f(x2, y2, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x2, y2, 1.f);
			glVertex3f(x1, y2, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x1, y2, 0.f);
			glVertex3f(x1, y1, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
