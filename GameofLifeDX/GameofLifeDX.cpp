#include "GameofLifeDX.h"
int ProcessLoop()
{
	if (ProcessMessage() != 0)   return -1;
	if (ClearDrawScreen() != 0)  return -1;
	//GetKey();           //get keyboard input
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Game of Life");
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
	{
		return -1;
	}
	while (ProcessLoop() == 0)
	{
		switch (program_state)
		{
		case PROG_INIT:
			initialize();
			randomStart();
			program_state = PROG_RUNNING;
			break;
		case PROG_RUNNING:	
			if (prog_count % FREQUENCY == 0)
			{
				followRules();			
				calculate();
			}
				showCells();
				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && program_state == PROG_RUNNING)
					program_state = PROG_PAUSE;
			break;
		case PROG_PAUSE:
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && program_state == PROG_PAUSE)
				program_state = PROG_RUNNING;
			break;
		default:
			printfDx("Unknown state!");
			break;
		}
		
		DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255),
			font, "Number of alive cells: %d\nturn: %d\n",
			cell_count, turn);

		prog_count++;
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}


