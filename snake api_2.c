#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

struct Game
{
    int X,Y;
};
struct Game snake,fruit;

enum direction
{
    LEFT,RIGHT,UP,DOWN
};
enum direction dir;
int c,r,val,wd,ht;
const int width = 50,height = 20;
int gameOver,score,tough = 0,highscore;
int CountTail,tailX[500],tailY[500],levelScore,a[4];
char ch;
HWND hWnd;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void gotoxy(int x, int y) // gotoxy is not defined in codeblocks but defined in turbo,so defining here
{

    COORD c;

    c.X = x;

    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}

void border()
{
	int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < c; i++)
	{ //TOP border
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(c-1,0);
    printf("%c",187); //RIGHT border
    for(i = 1; i < r; i++)
	{
        gotoxy(c-1, i);
        printf("%c",186);
    }
    gotoxy(c-1,r-1);
    printf("%c",188);
    for(i = c-2; i > 0; i--)
	{ //BOTTOM border
        gotoxy(i,r-1);
        printf("%c",205);
    }
    gotoxy(0,r-1);
    printf("%c",200); //LEFT border
    for(i = r-2; i > 0; i--)
	{
        gotoxy(0,i);
        printf("%c",186);
    }
}
void setupSnake()
{
    gameOver = 0;
    score = 0;
    dir = RIGHT;
    CountTail = 0;
    snake.X = width/2;
    snake.Y = height/2;
}

void setupFruit()
{
    int i;
    srand(time(0));

    label1:
    fruit.X = rand()%width;
    if(fruit.X == 0 || fruit.X == width-1)
        goto label1;
    for(i = 0; i<CountTail; i++)
        if(fruit.X == tailX[i])
            goto label1;

    label2:
    fruit.Y = rand()%height;
    if(fruit.Y == 0 || fruit.Y == height-1)
        goto label2;
     for(i = 0; i<CountTail; i++)
        if(fruit.Y == tailY[i])
            goto label2;
}

void draw(char lvl)
{
    gotoxy(0,0);
    int i,j,k ;
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(i==0 || j==0 || i==height-1 || j==width-1)
                printf(" %c",240); //  boundary wall
            else
            {
                if(i == snake.Y && j == snake.X)
                    printf(" %c",254);  // snake head

                else if(i == fruit.Y && j == fruit.X)
                    printf(" O");  // food
                else
                {
                    int flag=0;
                    for(k=0;k<CountTail;k++)
                    {
                        if(i == tailY[k] && j == tailX[k])
                        {
                            printf(" o");  // snake body & tail
                            flag=1;
                        }
                    }
                    if(flag==0)
                        printf("  ");
                }
            }
        }
        printf("\n");
    }
    if(score > levelScore)
            highscore = score;
    else
            highscore = levelScore;
            gotoxy((110-3),(ht-7));
            printf("CLASSIC");
            gotoxy((110-2),(ht-6));
            printf("SNAKE");
            gotoxy((110-1),(ht-5));
            printf("GAME");
	gotoxy((50-14),(ht+5));
	printf("-----------------------------");
	gotoxy((50-14),(ht+6));
    printf("| CURRENTLY PLAYING LEVEL %c |",lvl);
    gotoxy((50-14),(ht+7));
    printf("-----------------------------");

    printf("\n\n SCORE = %d \t\t\t HIGHSCORE = %d\n",score,highscore);

}

void input()
{
    if(!kbhit())
    {
        switch(ch)
        {
            case 72:
            case 'W' :
            case 'w' : dir=UP ;
                        break ;
            case 75:
            case 'A' :
            case 'a' : dir=LEFT ;
                        break ;
            case 80:
            case 'S' :
            case 's' : dir=DOWN ;
                        break ;
            case 77:
            case 'D' :
            case 'd' : dir=RIGHT ;
                        break ;
        }
    }
    else
    {
        switch(getch())
        {
            case 72:
            case 'W':
            case 'w' : dir=UP ;
                        ch='w' ;
                        break ;
            case 75:
            case 'A' :
            case 'a' : dir=LEFT ;
                        ch='a' ;
                        break ;
            case 80:
            case 'S' :
            case 's' : dir=DOWN ;
                        ch='s' ;
                        break ;
            case 77:
            case 'D' :
            case 'd' : dir=RIGHT ;
                        ch='d' ;
                        break ;
            case 'X' :
            case 'x' :  val=MessageBox(hWnd,"ARE YOU SURE TO EXIT GAME ?","CONFIRMATION",MB_ICONQUESTION |MB_YESNO);
     					if(val!=IDNO)
						gameOver=1;
                        system("cls");
                        break ;

        }
    }
}

void logic()
{
    int i;
    int prevX,prevY,prev2X,prec2Y;
    prevX=tailX[0] ;
    prevY=tailY[0] ;
    tailX[0]=snake.X ;
    tailY[0]=snake.Y ;

    for(i=1;i<=CountTail;i++)
    {
        prev2X = tailX[i];
        prec2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prec2Y;
    }
    switch(dir)
    {
        case UP   :     snake.Y-- ;
                        break ;
        case DOWN :     snake.Y++ ;
                        break ;
        case LEFT :     snake.X-- ;
                        break ;
        case RIGHT :    snake.X++ ;
                        break ;
        default    :    break;
    }
    for(i=0;i<=CountTail;i++)
    {
        if(tailX[i]==snake.X && tailY[i]==snake.Y)
        {
            gameOver=1 ;
            Beep(2750,1500);
            delay(800);
            system("cls") ;
            MessageBox(hWnd,"GAME OVER : YOU HIT/BITE THE TAIL !!!","GAME OVER",MB_ICONEXCLAMATION |MB_OK);
            printf("\n GAME OVER : You hit/bite your tail\n" );
            printf("\n BETTER LUCK NEXT TIME ");
        }
    }
    if(tough==1)
    {
        if(snake.X == 0 || snake.X == width-1 || snake.Y == 0 || snake.Y == height-1)
        {
            Beep(2750,1500);
            gameOver=1 ;
            delay(800);
            system("cls") ;
            MessageBox(hWnd,"GAME OVER : YOU HIT THE WALL !!!","GAME OVER",MB_ICONEXCLAMATION |MB_OK);
                printf("\n GAME OVER : You hit the wall " );
                printf("\n BETTER LUCK NEXT TIME ");
        }
    }
    else
    {
        if(snake.X == 0)
            snake.X = width-2 ;
        else if(snake.X == width-1)
            snake.X = 1 ;
        if(snake.Y == 0)
            snake.Y = height-2 ;
        else if(snake.Y == height-1)
            snake.Y = 1 ;
    }
    if(snake.X == fruit.X && snake.Y == fruit.Y)
    {

        score+=10 ;
        Beep(1200,50);
        setupFruit();
        CountTail++ ;
    }

}

int Highscore(char choice,int score)
{
      if(choice=='1')
        {
            if(score > a[0])
            {
                a[0] = score;
                return a[0];
            }
        }
        if(choice=='2')
        {
            if(score > a[1])
            {
                a[1] = score;
                return a[1];
            }
        }
        if(choice=='3')
        {
            if(score > a[2])
            {
                a[2] = score;
                return a[2];
            }
        }
        if(choice=='4')
        {
            if(score > a[3])
            {
                a[3] = score;
                return a[3];
            }
        }
}

void saveScore()
{
    FILE *fp = fopen("score.txt","r+");
    if(fp == NULL)
        fp = fopen("score.txt","w");
    fwrite(a,sizeof(int),4,fp);
    fclose(fp);
}

void exitgame()
{
	int q;
	system("cls");
    	system("COLOR 0C");
    	border();
		gotoxy(63,19);
		gotoxy((wd-11),(ht));
    	printf(".....EXITING GAME.....");

    gotoxy((wd-30),(ht+3));
	for(int x=0;x<60;x++)
	{
		printf("%c",219);
		delay(100);
	}
    system("cls");

	for(q=0;q<8;q++)
	{
		system("COLOR 0A");

		border();
        printf("\n\tCLASSIC SNAKE GAME");
        printf("\n\tDEVELOPED BY: SUYASH JAISWAL");
        printf("\n\t              VALENTINA ROY");
        printf("\n\t              KASHIS JAISWAL");
        printf("\n\t              FAIZAN AHMAD");
        printf("\n\t              ARKA ADHYA");
		gotoxy((wd-21),(ht-1));
		printf("------------------------------------------ ");
		gotoxy((wd-22),(ht));
		printf("| THANK YOU FOR PLAYING CLASSIC SNAKE GAME |");
		gotoxy((wd-21),(ht+1));
		printf("------------------------------------------ ");
			gotoxy((wd-15),(ht+2));
			printf("| HOPE TO SEE YOU BACK AGAIN |");
			gotoxy((wd-15),(ht+3));
			printf(" ---------------------------- ");
			delay(1000);
	}
        exit(0);
}

void load()
{

	gotoxy((wd-5),(ht+8));
	printf("LOADING...");
	gotoxy((wd-30),(ht+10));
	for(int x=0;x<60;x++)
	{
		printf("%c",219);
		delay(100);
	}
	gotoxy((wd-13),(ht+12));
	printf("PRESS ANY KEY TO CONTINUE ");
 	getch();
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{

	CONSOLE_SCREEN_BUFFER_INFO csbi;

    hWnd = GetConsoleWindow();
    SetWindowLong(hWnd,GWL_STYLE,GetWindowLong(hWnd,GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);         //GETTING THE TERMINAL SIZE OF THE USER SYSTEM
    c = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    r = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    wd=c/2;
    ht=r/2;
	int seconds,q;  //
    char ch1,choice;
    FILE *fp = fopen("score.txt","r");
    if(fp!=NULL)
        fread(a,sizeof(int),4,fp);

	hidecursor();
    system("cls");
    system("COLOR F6");
    border();
    gotoxy((wd-16),(ht));
    printf("WELCOME TO THE CLASSIC SNAKE GAME");
    delay(900);
    load();

    system("cls");
    system("COLOR F4");
    	border();
    	gotoxy((wd-8),(ht-4));
    	printf("Instructions");
    	gotoxy((wd-13),(ht-2));
        printf("Press a/A to move LEFt.");
        gotoxy((wd-13),(ht-1));
        printf("Press w/W to move UPWARD.");
        gotoxy((wd-13),(ht));
        printf("Press d/D to move RIGHT.");
        gotoxy((wd-13),(ht+1));
        printf("Press s/S to move DOWNWARD.");
        gotoxy((wd-13),(ht+2));
        printf("Press x/X to EXIT/QUIT THE GAME");
        gotoxy((wd-27),(ht+4));
        printf("RUNNING OVER THE SNAKE ITSELF, WILL LEAD TO GAME OVER ");

    gotoxy((wd-13),(ht+12));
    printf("PRESS ANY KEY TO CONTINUE:");
    ch1=getch();
    if(ch1=='X' || ch1=='x')
    {
	val=MessageBox(hWnd,"ARE YOU SURE TO EXIT GAME ?","CONFIRMATION",MB_ICONQUESTION |MB_YESNO);
     if(val!=IDNO)
    exitgame();
	}


    system("cls");
    labell:
	do
	{
        system("COLOR F2");
        border();
        printf("\n\n\n\t\t Enter level of game you want to play\n\n\t " );
        printf("\n\t\t 1. BEGINNER \n\t\t 2. BASIC \n\t\t 3. INTERMEDIATE " );
        printf("\n\t\t 4. ADVANCED (if you hit the wall game will be over )" );
        printf("\n\n\t\t  Press any other key to exit..");
        printf("\n\n\t\t  HighScores of each level : %d %d %d %d",a[0],a[1],a[2],a[3]);
        printf("\n\n\t\t  Please Enter Your Choice : " );
        choice=getch();
        if(choice=='1')
        {	printf("\n\n\t\t  BEGINNER LEVEL");
			val=MessageBox(hWnd,"BEGINNER LEVEL SELECTED..!!!  CONTINUE ?","LEVEL CONFIRMATION",MB_ICONINFORMATION |MB_YESNO);
        	if(val==IDYES)
            {system("COLOR 0A");
            seconds=100 ;
            levelScore = a[0];
        	}
        	else
			{ system("cls");
        	goto labell;
        	}
        }
        else if(choice == '2')
        {	printf("\n\n\t\t  BASIC LEVEL");
			val=MessageBox(hWnd,"BASIC LEVEL SELECTED..!!!  CONTINUE ?","LEVEL CONFIRMATION",MB_ICONINFORMATION |MB_YESNO);
            if(val==IDYES)
			{system("COLOR 09");
            levelScore = a[1];
            seconds=50 ;
        	}
        	else
			{ system("cls");
        	goto labell;
        	}
        }
        else if(choice == '3')
        {	printf("\n\n\t\t  INTERMEDIATE LEVEL");
			val=MessageBox(hWnd,"INTERMEDIATE LEVEL SELECTED..!!!  CONTINUE ?","LEVEL CONFIRMATION",MB_ICONINFORMATION |MB_YESNO);
            if(val==IDYES)
			{
			system("COLOR 0D");
            seconds=5 ;
            levelScore = a[2];
            }
            else
			{ system("cls");
        	goto labell;
        	}
        }
        else if(choice == '4')
        {	printf("\n\n\t\t  ADVANCED LEVEL");
			val=MessageBox(hWnd,"ADVANCED LEVEL SELECTED..!!!  CONTINUE ?","LEVEL CONFIRMATION",MB_ICONINFORMATION |MB_YESNO);
            if(val==IDYES)
			{
			system("COLOR 0C");
            levelScore = a[3];
            tough=1 ;
            seconds=10;
        	}
            else
			{ system("cls");
        	goto labell;
        	}
        }
        else
        {
		val=MessageBox(hWnd,"ARE YOU SURE TO EXIT GAME ?","EXIT GAME",MB_ICONQUESTION |MB_YESNO);
		if(val!=IDNO)
		    exitgame();
		 else
		goto labell;
		}


        system("cls");
            setupSnake();
            setupFruit();
            while(gameOver == 0)
            {
                gotoxy(0,0);
                draw(choice);
                input();
                if (gameOver==1)
                    break;
                logic();
                Sleep(seconds);
            }system("COLOR 0F");
        highscore = Highscore(choice,score);
        saveScore();
        border();
        printf("\n\n\n\t...................................................................");
        printf("\n\t YOUR FINAL SCORE = %d ",score);
        printf("\n\t...................................................................");
        if(highscore > levelScore)
        {
            printf("\n\n\n\t...................................................................");
            printf("\n\t NEW HIGHSCORE = %d ",highscore);
            printf("\n\t...................................................................");
        }

        val=MessageBox(hWnd," DO YOU WANT TO CONTINUE PLAYING ?","CONFIRMATION",MB_ICONQUESTION |MB_YESNO);
        fflush(stdin);

        if(val==IDYES)
         {
			   system("cls");
			   system("COLOR FC");
			   border();
			   gotoxy((wd-11),ht);
			   printf("RETURNING TO MAIN MENU");
			   load();
			   system("cls");
        tough = 0;}

		else if(val==IDNO)
		{
        exitgame();
    	}
    }
    while(val=IDYES);
    if(fp!=NULL)
        fclose(fp);

    return 0;
}
