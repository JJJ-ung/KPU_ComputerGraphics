#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include "ShaderLoader.cpp"

#include <time.h>
#include <Windows.h>

using namespace std;

struct shape
{
	GLfloat triShape[3][3] = {// 삼각형 꼭짓점 좌표값
	{-0.5, -0.5, 0.0},
	{ 0.5, -0.5, 0.0 },
	{ 0.0, 0.5, 0.0} };

	GLfloat colors[3][3] = { // 삼각형 꼭짓점 색상
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0} };

	GLuint vao, vbo[2];

	float x;
	float y;

	GLfloat dir[3];
};

shape g_tShape[4];
int g_iIndex = 0;
GLenum g_eMode = GL_FILL;
bool g_bMove = false;

void Initialize();
void Init_Buffer();
void Init_Shader();
void Update();
void Render();

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid KeyBoard(unsigned char key, int x, int y);

void Set_Triangle(int iIndex, float x, float y);
void Set_Color(int iIndex);
void Rand_Dir(int iIndex);

int main(int argc, char** argv)
{
	srand(unsigned(time(NULL)));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("실습04");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "“Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Initialized";

	Initialize();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(KeyBoard);
	glutTimerFunc(10, TimerFunction, 1);
	glutMainLoop();

	return 0;
}

void Initialize()
{
	Set_Triangle(0, -0.5f, 0.5f);
	Set_Triangle(1, 0.5f, 0.5f);
	Set_Triangle(2, 0.5f, -0.5f);
	Set_Triangle(3, -0.5f, -0.5f);

	for (int i = 0; i < 4; ++i)
	{
		Set_Color(i);
		g_tShape[i].dir[0] = 0.01f;
		g_tShape[i].dir[1] = 0.f;
	}

	Init_Buffer();
	Init_Shader();
}

void Init_Buffer()
{
	for (int i = 0; i < 4; ++i)
	{
		glGenVertexArrays(1, &g_tShape[i].vao); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(g_tShape[i].vao); //--- VAO를 바인드하기
		glGenBuffers(2, g_tShape[i].vbo); //--- 2개의 VBO를 지정하고 할당하기

		glBindBuffer(GL_ARRAY_BUFFER, g_tShape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), g_tShape[i].triShape, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, g_tShape[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), g_tShape[i].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
}

void Init_Shader()
{
	Create_VertexShader();
	Create_PixelShader();

	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);

	//--- 세이더 삭제하기
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	//--- Shader Program 사용하기
	glUseProgram(s_program);
}

void Update()
{
	if (g_bMove)
	{
		for (int i = 0; i < 4; ++i)
		{
			g_tShape[i].x += g_tShape[i].dir[0];
			g_tShape[i].y += g_tShape[i].dir[1];

			if (g_tShape[i].x > 1.f - 0.25f)
			{
				g_tShape[i].dir[0] = 0.f;
				g_tShape[i].dir[1] = -0.01f;
			}
			if (g_tShape[i].y < -1.f + 0.25f)
			{
				g_tShape[i].dir[0] = -0.01f;
				g_tShape[i].dir[1] = 0.f;
			}
			if (g_tShape[i].x < -1.f + 0.25f)
			{
				g_tShape[i].dir[0] = 0.f;
				g_tShape[i].dir[1] = 0.01f;
			}
			if (g_tShape[i].y > 1.f - 0.25f)
			{
				g_tShape[i].dir[0] = 0.01f;
				g_tShape[i].dir[1] = 0.f;
			}

			Set_Triangle(i, g_tShape[i].x, g_tShape[i].y);
		}							  
	}
}

void Render()
{
	glUseProgram(s_program);

	glPolygonMode(GL_FRONT, g_eMode);
	for (int i = 0; i < 4; ++i)
	{
		glBindVertexArray(g_tShape[i].vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	Render();

	glutSwapBuffers();

	return GLvoid();
}

GLvoid RenderScene()
{
	return GLvoid();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	return GLvoid();
}

GLvoid TimerFunction(int value)
{
	Update();

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);

	return GLvoid();
}

GLvoid Input_Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid Input_KeyBoard(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'f' || key == 'F')
	{
		if (g_eMode == GL_FILL)
			g_eMode = GL_LINE;
		else if (g_eMode == GL_LINE)
			g_eMode = GL_FILL;
	}
	if (key == 'm' || key == 'M')
	{
		g_bMove = true;
	}
	if (key == 's' || key == 'S')
	{
		g_bMove = false;
	}
	if (key == 'c' || key == 'C')
	{
		for (int i = 0; i < 4; ++i)
			Set_Color(i);
	}
	if (key == 'Q' || key == 'q')
		glutLeaveMainLoop();

	glutPostRedisplay();

	return GLvoid();
}


void Set_Triangle(int iIndex, float x, float y)
{
	GLfloat temp[3][3] =
	{// 삼각형 꼭짓점 좌표값
			{x, y + 0.25f, 0.f},
			{x - 0.25f, y - 0.25f, 1.f},
			{x + 0.25f, y - 0.25f, 0.f}
	};

	g_tShape[iIndex].x = x;
	g_tShape[iIndex].y = y;

	memcpy(g_tShape[iIndex].triShape, temp, sizeof(GLfloat) * 9);
	glBindBuffer(GL_ARRAY_BUFFER, g_tShape[iIndex].vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), g_tShape[iIndex].triShape, GL_STATIC_DRAW);
}

void Set_Color(int iIndex)
{
	float r = rand() % 255 / 255.f;
	float g = rand() % 255 / 255.f;
	float b = rand() % 255 / 255.f;

	GLfloat colors[3][3] =
	{ // 삼각형 꼭짓점 색상
			{r, g, b},
			{r, g, b},
			{r, g, b}
	};

	memcpy(g_tShape[iIndex].colors, colors, sizeof(GLfloat) * 9);
	glBindBuffer(GL_ARRAY_BUFFER, g_tShape[iIndex].vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), g_tShape[iIndex].colors, GL_STATIC_DRAW);
}

void Rand_Dir(int iIndex)
{
	int i = rand() % 4;

	switch (i)
	{
	case 0:
		g_tShape[iIndex].dir[0] = 0.01f;
		g_tShape[iIndex].dir[1] = 0.f;
	case 1:
		g_tShape[iIndex].dir[0] = -0.01f;
		g_tShape[iIndex].dir[1] = 0.f;
	case 2:
		g_tShape[iIndex].dir[0] = 0.f;
		g_tShape[iIndex].dir[1] = 0.01f;
	case 3:
		g_tShape[iIndex].dir[0] = 0.f;
		g_tShape[iIndex].dir[1] = -0.01f;
	default:
		break;
	}
}
