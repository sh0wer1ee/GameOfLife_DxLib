#include <DxLib.h>
#include <time.h>

#define WIDTH          1280
#define HEIGHT         720
#define WIDTHNUM      (320 + 2)
#define HEIGHTNUM     (180 + 2)
#define ALIVE          1
#define DEAD           0
#define PROG_INIT      0
#define PROG_RUNNING   1
#define PROG_PAUSE     2
#define BLOCKLENGTH    4
#define FREQUENCY      1


int program_state = PROG_INIT;
int neighbor_count, cell_count, turn, prog_count;
int font;
bool cell_now[WIDTHNUM][HEIGHTNUM];
bool cell_new[WIDTHNUM-2][HEIGHTNUM-2];

void killAll()
{
	for (int i = 0; i < WIDTHNUM; i++)
	{
		for (int j = 0; j < HEIGHTNUM; j++)
		{
			cell_now[i][j] = DEAD;
		}
	}
}

void randomStart()
{
	for (int i = 1; i < WIDTHNUM - 1; i++)
	{
		for (int j = 1; j < HEIGHTNUM - 1; j++)
		{
			cell_now[i][j] = GetRand(1);
		}
	}
}

void followRules()
{
	for (int i = 1; i < WIDTHNUM - 1; i++)
	{
		for (int j = 1; j < HEIGHTNUM - 1; j++)
		{
			neighbor_count = cell_now[i - 1][j - 1] + cell_now[i - 1][j] + cell_now[i - 1][j + 1]
				+ cell_now[i][j - 1] + cell_now[i][j + 1] + cell_now[i + 1][j - 1]
				+ cell_now[i + 1][j] + cell_now[i + 1][j + 1];
			switch (neighbor_count)
			{
			case 2:
				break;
			case 3:
				cell_new[i-1][j-1] = ALIVE;
				break;
			default:
				cell_new[i-1][j-1] = DEAD;
				break;
			}
		}
	}

	killAll();
	
	for (int i = 1; i < WIDTHNUM - 1; i++)
	{
		for (int j = 1; j < HEIGHTNUM - 1; j++)
		{
			if (cell_new[i - 1][j - 1] == ALIVE)
				cell_now[i][j] = ALIVE;
		}
	}

}

void calculate()
{
	cell_count = 0;
	for (int i = 1; i < WIDTHNUM - 1; i++)
	{
		for (int j = 1; j < HEIGHTNUM - 1; j++)
		{
			cell_count += cell_now[i][j];
		}
	}
	turn++;
}

void initialize() 
{
	srand((unsigned int)time(0));
	
	neighbor_count = 0;
	cell_count = 0;
	turn = 0;
	prog_count = 0;
	font = CreateFontToHandle("Fixedsys", 10, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	killAll();	
}

void showCells() 
{
	for (int i = 1; i < WIDTHNUM - 1; i++)
	{
		for (int j = 1; j < HEIGHTNUM - 1; j++)
		{
			if (cell_new[i-1][j-1])
				DrawCircle(BLOCKLENGTH*(i - 1)+ BLOCKLENGTH / 2, 
				           BLOCKLENGTH*(j - 1)+ BLOCKLENGTH / 2,
				           BLOCKLENGTH/2,GetColor(255, 255, 0), TRUE);
                  /*DrawBox(BLOCKLENGTH*(i - 1), BLOCKLENGTH*(j - 1),
					    BLOCKLENGTH*i, BLOCKLENGTH*j,
					    GetColor(255, 255, 0), TRUE);*/
		}
	}
}

