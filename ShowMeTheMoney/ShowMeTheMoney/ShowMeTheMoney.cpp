#include "stdafx.h"
#include "Manager.h"
#include "CMainGame.h"

GLvoid Reshape(int w, int h);
GLvoid Update();
GLvoid Input_Mouse(int button, int state, int x, int y);
GLvoid Input_MouseMotion(int x, int y);
GLvoid Input_KeyBoard(unsigned char key, int x, int y);
GLvoid Input_KeyBoardDir(int key, int x, int y);
GLvoid Release();
GLvoid Check_Frame(bool bCheck);

CMainGame* g_pMainGame;

CKeyManager* g_pKeyMgr;
CTimeManager* g_pTimeMgr;
CFrameManager* g_pFrameMgr;

GLuint g_iRenderCall = 0;
double g_dwTimerAcc = 0.0;

HWND g_hWnd;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINCX, WINCY);
	glutCreateWindow("Client");

	if (glewInit() != GLEW_OK) {
		cerr << "Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else cout << "GLEW Initialized\n";

	g_pMainGame = CMainGame::Create();
	if (!g_pMainGame)
	{
		cerr << "“Unable to initialize MainGame" << endl;
		exit(EXIT_FAILURE);
	}
	
	g_pKeyMgr = CKeyManager::GetInstance();
	g_pTimeMgr = CTimeManager::GetInstance();
	g_pFrameMgr = CFrameManager::GetInstance();

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Update);
	glutIdleFunc(Update);

	glutMouseFunc(Input_Mouse);
	glutMotionFunc(Input_MouseMotion);
	glutKeyboardFunc(Input_KeyBoard);
	glutSpecialFunc(Input_KeyBoardDir);

	glutMainLoop();

	return 0;
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	return GLvoid();
}

GLvoid Update()
{
	if (g_pFrameMgr->Frame_Limit(60.f))
	{
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_pTimeMgr->Update_Time();
		g_pKeyMgr->Update_Key();
		g_pMainGame->Update();
		g_pMainGame->Render();

		glutSwapBuffers();

		Check_Frame(true);
	}
}

GLvoid Input_Mouse(int button, int state, int x, int y)
{
	g_pKeyMgr->Update_Mouse(x, y);

	return GLvoid();
}

GLvoid Input_MouseMotion(int x, int y)
{
	g_pKeyMgr->Update_Mouse(x, y);

	return GLvoid();
}

GLvoid Input_KeyBoard(unsigned char key, int x, int y)
{
	return GLvoid();
}

GLvoid Input_KeyBoardDir(int key, int x, int y)
{
	return GLvoid();
}

GLvoid Release()
{
	SafeDelete(g_pMainGame);
}

GLvoid Check_Frame(bool bCheck)
{
	if (!bCheck)
		return;

	g_dwTimerAcc += g_pTimeMgr->Get_Delta();
	++g_iRenderCall;

	if (1.0 <= g_dwTimerAcc)
	{
		cout << "FPS : " << g_iRenderCall << endl;
		g_iRenderCall = 0;
		g_dwTimerAcc = 0.0;
	}
}
