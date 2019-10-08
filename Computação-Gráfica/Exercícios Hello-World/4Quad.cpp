/**
 * Basic usege of OpenGL and GLFW. 
 */

#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

float x1 = -0.8f, x2 = -0.2f;
float x3 = 0.2f , x4 = 0.8f;
float y1 = 0.8f, y2 = 0.2f;
float y3 = -0.2f, y4 = -0.8f;
float vel = 0.001, sent;

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

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);


		if(x1 <= -0.8){
			sent = +1;
		}else if(x1 >= 0.2){
			sent = -1;
		}

		if(sent > 0 && x1 <= 0.2){
			x1 += vel;
			x2 += vel;
			x3 -= vel;
			x4 -= vel;
			y1 -= vel;
			y2 -= vel;
			y3 += vel;
			y4 += vel;
		}else{
			x1 -= vel;
			x2 -= vel;
			x3 += vel;
			x4 += vel;
			y1 += vel;
			y2 += vel;
			y3 -= vel;
			y4 -= vel;
		}
		
		glBegin(GL_LINES);
			
			//Quadrado 1
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x1, 0.8f, 0.f);
			glVertex3f(x2, 0.8f, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x2, 0.8f, 0.f);
			glVertex3f(x2, 0.2f, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x2, 0.2f, 0.f);
			glVertex3f(x1, 0.2f, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(x1, 0.2f, 0.f);
			glVertex3f(x1, 0.8f, 0.f);

			//Quadrado 2
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(0.2f, y1, 0.f);
			glVertex3f(0.8f, y1, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(0.8f, y1, 0.f);
			glVertex3f(0.8f, y2, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(0.8f, y2, 0.f);
			glVertex3f(0.2f, y2, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(0.2f, y2, 0.f);
			glVertex3f(0.2f, y1, 0.f);
			
			//Quadrado 3
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(-0.8f, y3, 0.f);
			glVertex3f(-0.2f, y3, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(-0.2f, y3, 0.f);
			glVertex3f(-0.2f, y4, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(-0.2f, y4, 0.f);
			glVertex3f(-0.8f, y4, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(-0.8f, y4, 0.f);
			glVertex3f(-0.8f, y3, 0.f);

			//Quadrado 4
			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(x3, -0.2f, 0.f);
			glVertex3f(x4, -0.2f, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(x4, -0.2f, 0.f);
			glVertex3f(x4, -0.8f, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(x4, -0.8f, 0.f);
			glVertex3f(x3, -0.8f, 0.f);

			glColor3f(0.f, 0.f, 1.f);
			glVertex3f(x3, -0.8f, 0.f);
			glVertex3f(x3, -0.2f, 0.f);
			

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
