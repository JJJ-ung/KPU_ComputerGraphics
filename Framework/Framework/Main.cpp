#include "stdafx.h"
#include "SceneInclude.h"

#include "CShaderLoader.h"
#include "CShape.h"

GLuint g_iWinCX = 800;
GLuint g_iWinCY = 800;
vec4	 g_vBufCol = vec4(0.1f, 0.1f, 0.1f, 1.f);

GLvoid SetWindowSize(GLuint iNum);
CScene* CreateScene(GLuint iNum);
GLvoid RenderScene();
GLvoid Reshape(int w, int h);
GLvoid TimerFunction(int value);
GLvoid Input_Mouse(int button, int state, int x, int y);
GLvoid Input_KeyBoard(unsigned char key, int x, int y);
GLvoid Input_KeyBoardDir(int key, int x, int y);
GLvoid Release();

CScene* g_pScene = nullptr;
CShaderLoader* g_pShaderLoader = CShaderLoader::GetInstance();

int main(int argc, char** argv)
{
	srand(unsigned(time(NULL)));

	SetWindowSize(SCENENUM);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(g_iWinCX, g_iWinCY);
	glutCreateWindow("½Ç½À");

	glClearColor(g_vBufCol.r, g_vBufCol.g, g_vBufCol.b, g_vBufCol.a);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cerr << "¡°Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Initialized" << endl;

	if (CreateScene(SCENENUM) == nullptr)
	{
		cout << "Failed to Create Scene" << endl;
		exit(EXIT_FAILURE);
	}

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Input_Mouse);
	glutKeyboardFunc(Input_KeyBoard);
	glutSpecialFunc(Input_KeyBoardDir);
	glutTimerFunc(10, TimerFunction, 1);
	glutMainLoop();

	return 0;
}

GLvoid SetWindowSize(GLuint iNum)
{
	switch (iNum)
	{
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	case 18:
		break;
	case 19:
		break;
	case 20:
		break;
	default:
		g_pScene = nullptr;
		break;
	}

	return GLvoid();
}

CScene* CreateScene(GLuint iNum)
{
	switch (iNum)
	{
	case 12:
		g_pScene = CScene12::Create();
		break;
	case 13:
		g_pScene = CScene13::Create();
		break;
	case 14:
		g_pScene = CScene14::Create();
		break;
	case 15:
		g_pScene = CScene15::Create();
		break;
	case 16:
		g_pScene = CScene16::Create();
		break;
	case 17:
		g_pScene = CScene17::Create();
		break;
	case 18:
		g_pScene = CScene18::Create();
		break;
	case 19:
		g_pScene = CScene19::Create();
		break;
	case 20:
		g_pScene = CScene20::Create();
		break;
	default:
		g_pScene = nullptr;
		break;
	}

	return g_pScene;
}

GLvoid RenderScene()
{
	glClearColor(g_vBufCol.r, g_vBufCol.g, g_vBufCol.b, g_vBufCol.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(g_pShaderLoader->s_program);
	
	g_pScene->Render();

	glutSwapBuffers();

	return GLvoid();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	return GLvoid();
}

GLvoid TimerFunction(int value)
{
	g_pScene->Update();

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);

	return GLvoid();
}

GLvoid Input_Mouse(int button, int state, int x, int y)
{
	g_pScene->Input_Mouse(button, state, x, y);

	return GLvoid();
}

GLvoid Input_KeyBoard(unsigned char key, int x, int y)
{
	g_pScene->Input_KeyBoard(key, x, y);

	return GLvoid();
}

GLvoid Input_KeyBoardDir(int key, int x, int y)
{
	g_pScene->Input_KeyBoardDir(key, x, y);

	return GLvoid();
}

GLvoid Release()
{
	SafeDelete(g_pScene);

	return GLvoid();
}
