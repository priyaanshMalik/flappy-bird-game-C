#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>

void firstPage(int );  		        //displays the first page
void instructions();        	//display the instruction to game
char gameover(int  );
void main()
{
    clrscr();

    //bird settings
    char again='y';
    int birdY=200;
    int birdX=200;

    int gravity=15;
    int upForce=20;
    int birdRadius=10;
    char quit;
    int highscore=0;

    //variable for storing keyboard keys
    char ch;

    int pipe1x1=700;
    int pipe1y1=0;
    int pipe1x2=pipe1x1+100;
    int pipe1y2=pipe1y1+150;

    int pipe2x1=400;
    int pipe2x2=pipe2x1 +100;
    int pipe2y1=0;
    int pipe2y2=pipe2y1+200;

    int pipeSpeed=50;

    int collide=0;
    int score=0;

    while(again!='n')
    {

        again='y';
        birdY=200;
        birdRadius=10;

        pipe1x1=700;
        pipe1y1=0;
        pipe1x2=pipe1x1+100;
        pipe1y2=pipe1y1+150;

        pipe2x1=400;
        pipe2x2=pipe2x1 +100;
        pipe2y1=0;
        pipe2y2=pipe2y1+200;

        collide=0;
        score=0;

        int birdBeak[]={210,195,220,200,210,205,210,195};
        int color[]={215,200};

        int gd=DETECT, gm;
        initgraph(&gd, &gm, "c:/TURBOC3/BGI");

        firstPage(highscore);//goes to first page of game...
        getch();
        instructions(); //goes to instruction function
        getch();
        closegraph();

        initgraph(&gd, &gm, "c:/TURBOC3/BGI");
        setbkcolor(BLUE);

        while(1)
        {
            //check collision
            if (birdY<0||birdY>550)
                collide=1;

            if((birdY+15<pipe1y2&&birdY+15>pipe1y1&&birdX+15>pipe1x1&&birdX+15<pipe1x2)
                    ||(birdY+15>pipe1y1+300&&birdY+15<pipe1y2+550&&
                       birdX+15>pipe1x1&&birdX+15<pipe1x2))
            {
                collide=1;
            }

            if((birdY+15<pipe2y2&&birdY+15>pipe2y1&&birdX+15>pipe2x1&&birdX+15<pipe2x2)
                    ||(birdY+15>pipe2y1+400&&birdY+15<pipe2y2+550&&
                        birdX+15>pipe2x1&&birdX+15<pipe2x2))
            {
                collide=1;
            }

            //draw pipes on screen
            setfillstyle(SOLID_FILL, GREEN);
            setcolor(BLACK);

            //pipe1 set upper
            bar(pipe1x1, pipe1y1, pipe1x2, pipe1y2);
            rectangle(pipe1x1, pipe1y1, pipe1x2, pipe1y2);

            //pipe2 set upper
            bar(pipe2x1, pipe2y1, pipe2x2, pipe2y2);
            rectangle(pipe2x1, pipe2y1, pipe2x2, pipe2y2);

            //pipe1 set bottom
            bar(pipe1x1, pipe1y1+300, pipe1x2, pipe1y2+550);
            rectangle(pipe1x1, pipe1y1+300, pipe1x2, pipe1y2+550);

            //pipe2 set bottom
            bar(pipe2x1, pipe2y1+400, pipe2x2, pipe2y2+550);
            rectangle(pipe2x1, pipe2y1+400, pipe2x2, pipe2y2+550);

            //draw blue background to remove pipe trace .
            setfillstyle(SOLID_FILL, BLUE);
            setcolor(BLACK);

            bar(pipe1x2, 0, pipe1x2+pipeSpeed, 150);
            rectangle(pipe1x2, 0, pipe1x2+pipeSpeed, 150);

            bar(pipe1x2, 300, pipe1x2+pipeSpeed, 550);
            rectangle(pipe1x2, 300, pipe1x2+pipeSpeed, 550);

            bar(pipe2x2, 400, pipe2x2+pipeSpeed, 550);
            rectangle(pipe2x2, 400, pipe2x2+pipeSpeed, 550);

            bar(pipe2x2, 0, pipe2x2+pipeSpeed, 200);
            rectangle(pipe2x2, 0, pipe2x2+pipeSpeed, 200);

            if (pipe1x2<0)//if pipe1 moves out of screen
            {
                pipe1x1=600;
                pipe1x2=pipe1x1+100;
            }
            if (pipe2x2<0) //if pipe 2 moves out of screen
            {
                pipe2x1=pipe1x1+400;
                pipe2x2=pipe2x1+100;
                pipe2x2=pipe2x1+100;
            }
            delay(50);

            pipe1x1-=8;
            pipe1x2-=8;

            pipe2x2-=8;
            pipe2x1-=8;

            score+=10;

            if (collide==1)
                break;

            //to capture keyboard hit
            if(kbhit())
            {
                ch=getch();
                quit=ch;
                if (quit==27)
                    break;

                if(ch!='p'||ch!=27)
                {
                    birdY-=upForce;
                    birdBeak[1]-=upForce;
                    birdBeak[3]-=upForce;
                    birdBeak[5]-=upForce;
                    birdBeak[7]-=upForce;

                    color[1]-=upForce;

                    setfillstyle(SOLID_FILL, BLUE);
                    bar(birdX-birdRadius, birdY+(upForce+birdRadius),birdX+birdRadius+10,birdY+birdRadius);

                    setfillstyle(SOLID_FILL, YELLOW);
                    fillellipse(birdX, birdY, birdRadius, birdRadius);

                    setfillstyle(SOLID_FILL, RED);
                    fillellipse(birdX, birdY,birdRadius-6,birdRadius-6);
                    setcolor(WHITE);
                    drawpoly(4, birdBeak);
                    floodfill(color[0],color[1],WHITE);
                }
                else
                {
                    break;
                }
            }
            else
            {
                birdY+=gravity;
                birdBeak[1]+=gravity;
                birdBeak[3]+=gravity;
                birdBeak[5]+=gravity;
                birdBeak[7]+=gravity;

                color[1]+=gravity;

                setfillstyle(SOLID_FILL, BLUE);
                bar(birdX-birdRadius, birdY-(gravity+birdRadius), birdX+birdRadius+10, birdY-birdRadius);
                setfillstyle(SOLID_FILL,YELLOW);
                fillellipse(birdX,birdY, birdRadius, birdRadius);
                setcolor(WHITE);
                drawpoly(4, birdBeak);
                floodfill(color[0],color[1],WHITE);
            }
        }
        setbkcolor(BLUE);
        closegraph();
        initgraph(&gd, &gm, "c:/TURBOC3/BGI");
        if(score>highscore)
            highscore=score;
        again=gameover(score);
    }
    closegraph();
}
void firstPage(int highscore)    //create first page
{
   textcolor(WHITE);
   char str[5];
   itoa(highscore, str, 10);
   settextstyle(8,HORIZ_DIR,3);
   outtextxy(220,150,"!! FLAPPYBIRD !!");
   outtextxy(155,200," High score is: ");
   outtextxy(165,250,str);
   outtextxy(155,300," Press any key to start ");
}
void instructions()
{
    cleardevice();
    textcolor(WHITE);
    settextstyle(8,HORIZ_DIR,3);
    outtextxy(140,150,"this is a flappy bird game");
    outtextxy(140, 200, "~priyaansh and yash, cse3");
    outtextxy(140, 250, "to exit press Esc key (midgame)");
    outtextxy(155,300," Press any key to start ");
    getch();
}
char gameover(int score)
{
    cleardevice();
    textcolor(WHITE);
    char str[5];
    char ch;
    itoa(score, str, 10);
    settextstyle(8,HORIZ_DIR,3);
    while(1)
    {
        outtextxy(165,125,"Oh no! GAMEOVER!!!");
        outtextxy(165,175, "your total score is: ");
        outtextxy(200, 225, str);
        outtextxy(155,275," Press Esc key to exit ");
        outtextxy(155,325," Play again? y/n ");
        ch=getch();
        if(ch==27||ch=='n')
            return 'n';
        else if(ch=='y')
            return ch;
    }
}
