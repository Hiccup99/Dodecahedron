#include <math.h>
#include <GL/glut.h>
int faces[12][5] =
{
	{0, 16, 2, 10, 8},
	{0, 8, 4, 14, 12},
	{16, 17, 1, 12, 0},
	{1, 9, 11, 3, 17},
	{1, 12, 14, 5, 9},
	{2, 13, 15, 6, 10},
	{13, 3, 17, 16, 2},
	{3, 11, 7, 15, 13},
	{4, 8, 10, 6, 18},
	{14, 5, 19, 18, 4},
	{5, 19, 7, 11, 9},
	{15, 7, 19, 18, 6}
};
double points[20][3] =
{
	{1, 1, 1},
	{1, 1, -1},
	{1, -1, 1},
	{1, -1, -1},
	{-1, 1, 1},
	{-1, 1, -1},
	{-1, -1, 1},
	{-1, -1, -1},
	{0, 0.618, 1.618},
	{0, 0.618, -1.618},
	{0, -0.618, 1.618},
	{0, -0.618, -1.618},
	{0.618, 1.618, 0},
	{0.618, -1.618, 0},
	{-0.618, 1.618, 0},
	{-0.618, -1.618, 0},
	{1.618, 0, 0.618},
	{1.618, 0, -0.618},
	{-1.618, 0, 0.618},
	{-1.618, 0, -0.618}
};
void cross(double a[], double b[], double vec1[]) 
{
	vec1[0] = a[1] * b[2] - a[2] * b[1];
	vec1[1] = a[2] * b[0] - a[0] * b[2];
	vec1[2] = a[0] * b[1] - a[1] * b[0];
}
void getNormal(int n, int m, int x, double vec1[]) 
{
	double a[] = { points[m][0] - points[n][0], points[m][1] - points[n][1], points[m][2] - points[n][2] };
	double b[] = { points[m][0] - points[x][0], points[m][1] - points[x][1], points[m][2] - points[x][2] };
	cross(a, b, vec1);
}
double dot(double a[], double b[]) 
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
double mag(double a[]) 
{
	return sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
}

void myFunc(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W')
		glRotated(10.0, 0.0, 0.0, 1.0);                         
	else if (key == 'a' || key == 'A')
		glRotated(10.0, 0.0, -1.0, 0.0);                        
	else if (key == 's' || key == 'S')
		glRotated(10.0, 0.0, 0.0, -1.0);                        
	else if (key == 'd' || key == 'D')
		glRotated(10.0, 0.0, 1.0, 0.0);                         
	glutPostRedisplay();                                        
}
void reshape(int w, int h) {                                     
	double aspect = double(w) / double(h);                      
	glEnable(GL_DEPTH_TEST);                                    
	glMatrixMode(GL_PROJECTION);                                
	glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, -3.0, 3.0); 
	glMatrixMode(GL_MODELVIEW);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
	for (int i = 0; i < 12; i++) 
	{
		glColor3f(0.0, 0.1, 0.1);
		glBegin(GL_TRIANGLE_FAN);
		for (int x = 0; x < 5; x++)
			glVertex3dv(points[faces[i][x]]);
		glEnd();
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_LINE_STRIP);                                
		for (int x = 0; x < 5; x++)
			glVertex3dv(points[faces[i][x]]);
		glVertex3dv(points[faces[i][0]]);               
		glEnd();
	}
	glFlush();
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Ojaswa Sharma IIIT DELHI - Dodecahedron");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);                              
	glutKeyboardFunc(myFunc);
	glutMainLoop();
	return 0;
}