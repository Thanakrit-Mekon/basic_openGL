#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// define window size
const int Window_Width = 480;
const int Window_Height = 480;

// ---------- Struct ----------//

typedef struct {
  GLfloat x, y, z; // Coordinate (x ,y, z)
	GLfloat r, g, b, a; // RGBA system
} Vertex;

typedef struct {
	GLfloat x, y, z;
} Data;

// ---------- Draw function ---------- //

void drawPoint(Vertex v1, GLfloat size) {
	glPointSize(size); // Specify the size of the point
	glBegin(GL_POINTS); // Set the beginning of the list of vertices

	glColor4f(v1.r, v1.g, v1.b, v1.a); // Set color RGBA to a point
	glVertex3f(v1.x, v1.y, v1.z);  // Set vertex coordinates (x, y, z)

	glEnd(); // Set the end
}

void drawLine(Vertex v1, Vertex v2, GLfloat width) {
	glLineWidth(width); // Set line width
	glBegin(GL_LINES); // Set the primitive type for line drawing

	// Set vertices and the color of the line

	// Coor 1
	glColor4f(v1.r, v1.g, v1.b, v1.a);
	glVertex3f(v1.x, v1.y, v1.z);

	// Coor 2
	glColor4f(v2.r, v2.g, v2.b, v2.a);
	glVertex3f(v2.x, v2.y, v2.z);

	glEnd();
}

void drawTriangle(Vertex v1, Vertex v2, Vertex v3) {
	glBegin(GL_TRIANGLES);

	// Set vertices and coordinate

	// Coor 1
	glColor4f(v1.r, v1.g, v1.b, v1.a);
	glVertex3f(v1.x, v1.y, v1.z);

	// Coor2
	glColor4f(v2.r, v2.g, v2.b, v2.a);
	glVertex3f(v2.x, v2.y, v2.z);

	// Coor 3
	glColor4f(v3.r, v3.g, v3.b, v3.a);
	glVertex3f(v3.x, v3.y, v3.z);

	glEnd();
}

void drawGrid(GLfloat width, GLfloat height, GLfloat gridWidth) {

	// Horizontal axis
	for (float i = -height; i < height; i += gridWidth) {
		Vertex v1 = { -width, i, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		Vertex v2 = { width, i, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		drawLine(v1, v2, 0.5f);
	}

	// Vertical axis
	for (float i = -width; i < width; i += gridWidth) {
		Vertex v1 = { i, -height, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		Vertex v2 = { i, height, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		drawLine(v1, v2, 0.5f);
	}
}

void draw2DScatterPlot(const Data* data, int num_points) {
	// Input data stream
	Vertex v1 = { -10.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	Vertex v2 = { 10.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	drawLine(v1, v2, 2.0f);
	v1.x = 0.0f;
	v2.x = 0.0f;
	v1.y = -1.0f;
	v2.y = 1.0f;
	drawLine(v1, v2, 2.0f);

	for (int i = 0; i < num_points; i++) {
		GLfloat x = data[i].x;
		GLfloat y = data[i].y;
		Vertex v = { x, y, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f };
		drawPoint(v, 8.0f);
	}
}

void draw2DlinePlot(const Data* data, int num_points) {
	for (int i = 0; i < num_points - 1; i++) {
		GLfloat x1 = data[i].x;
		GLfloat y1 = data[i].y;
		GLfloat x2 = data[i + 1].x;
		GLfloat y2 = data[i + 1].y;
		Vertex v1 = { x1, y1, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f };
		Vertex v2 = { x2, y2, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f };
		drawLine(v1, v2, 4.0f);
	}
}

void draw2DHeatMap(const Data* data, int num_points) {
	// Locate Min, Max values in dataset
	float MAX_VALUE = -999.9f;
	float MIN_VALUE = 999.9f;
	for (int i = 0; i < num_points; i++) {
		const Data  d = data[i];
		if (d.z > MAX_VALUE) {
			MAX_VALUE = d.z;
		}
		if (d.z < MIN_VALUE) {
			MIN_VALUE = d.z;
		}
	}
	const float halfmax = (MAX_VALUE + MIN_VALUE) / 2;

	// Display result
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < num_points; i++) {
		const Data d = data[i];
		float value = d.z;
		float b = 1.0f - value / halfmax;
		float r = value / halfmax - 1.0f;
		if (b < 0) {
			b = 0;
		}
		if (r < 0) {
			r = 0;
		}
		float g = 1.0f - b - r;
		glColor4f(r, g, b, 0.5f);
		glVertex3f(d.x, d.y, 0.0f);
	}
	glEnd();
}
// ---------- End of draw function ---------- //


// ---------- Draw sample function ---------- //

void drawsamplePoint(int width, int height) {
	// Function to draw sample point
	GLfloat size = 5.0f;
	for (GLfloat x = 0.0f; x <= 1.0f; x += 0.2f, size += 5) {
		Vertex v1 = { x, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		drawPoint(v1, size);
	}
}

void drawSampleLine() {
	// DrawGrid
	drawGrid(5.0f, 1.0f, 0.1f);

	// Vertice and line config
	Vertex v1 = { -5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f };
	Vertex v2 = { 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.7f };
	Vertex v3 = { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.7f };
	Vertex v4 = { 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.7f };

	// Drawline
	drawLine(v1, v2, 10.0f);
	drawLine(v3, v4, 10.0f);
}

void drawSampleTriangle() {
	//drawGrid(5.0f, 1.0f, 0.1f);

	Vertex v1 = { 0.0f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f };
	Vertex v2 = { -1.0f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 0.6f };
	Vertex v3 = { 1.0f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 0.6f };

	drawTriangle(v1, v2, v3);
}

void drawSampleSinusoid(float phaseShift) {
	drawGrid(5.0f, 1.0f, 0.1f);
	GLfloat range = 10.0f;
	const int num_points = 200;
	Data* data = (Data*)malloc(sizeof(Data) * num_points);
	for (int i = 0; i < num_points; i++) {
		data[i].x = ((GLfloat)i / num_points) * range - range / 2.0f;
		data[i].y = (0.8 * cosf(data[i].x * 3.14f + phaseShift));
	}
	draw2DScatterPlot(data, num_points);
	draw2DlinePlot(data, num_points);
	free(data);
}

void sampleGaussian(float sigma) {
	// Construct 1000 x 1000 grid
	const int grid_x = 1000;
	const int grid_y = 1000;
	const int num_points = grid_x * grid_y;
	Data* data = (Data*)malloc(sizeof(Data) * num_points);
	int data_counter = 0;
	for (int x = -grid_x / 2; x < grid_x / 2; x++) {
		for (int y = -grid_y / 2; y < grid_y / 2; y++) {
			float x_data = 2.0f * x / grid_x;
			float y_data = 2.0f * y / grid_y;
			// Compute the height z based on a
			// Gaussian function
			float z_data = exp(-0.5f * (x_data * x_data) / (sigma * sigma) - 0.5f * (y_data * y_data) / (sigma * sigma)) / (sigma * sigma * 2.0f * M_PI);
			data[data_counter].x = x_data;
			data[data_counter].y = y_data;
			data[data_counter].z = z_data;
			data_counter++;
		}
	}
	// Visualize the result
	draw2DHeatMap(data, num_points);
	free(data);
}

// ---------- End of draw sample function ---------- //

int main(void) {
	// Window configuration
	GLFWwindow* window;
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(Window_Width, Window_Height, "sample openGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	// Enable anit-aliasing and smoothing
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float phaseShift = 0.0f;
	float sigma = 0.01f;

	// Window loop
	while (!glfwWindowShouldClose(window)) {
		// Terminate when window is closed
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = (float)width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		// Setup camera for orthographic projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Orthographic projection
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ---------- Main function ---------- //

		//drawsamplePoint(1, 1);

		//drawSampleLine();

		//drawSampleTriangle();


		//SAMPLE SINUSOID
		//drawSampleSinusoid(phaseShift);
		//phaseShift += 0.001f;

		
		// GAUSSIAN HEATMAP
		drawGrid(5.0f, 1.0f, 0.1f);
		sigma += 0.01f;
		if (sigma > 1.0f) {
			sigma = 0.01;
		}
		sampleGaussian(sigma);
		
		// ---------- End of main function ---------- //

		// Swap the front and back buffer 
		glfwSwapBuffers(window);
		// Process event queue to avoid lock-up
		glfwPollEvents();
	}

	// Release the memmory
	// Terminate GLFW library
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}
