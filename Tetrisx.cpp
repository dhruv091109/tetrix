/*
_____________________________________________________________________________

Source code:	Tetrisx game

					  Developed by :
						   Suneet Singh Mausil
						   Author of the book
_____________________________________________________________________________
*/

#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>

#define UNOCCUPIED 0
#define OCCUPIED 1

#define YES 1
#define NO 0

#define NORMAL 3
#define SKIP 2
#define DRAW 1
#define DEL  0

#define FIXED 1
#define FALLING 0



int Checker1(int);
int Checker2(int);
int Checker3(int);
int Checker4(int);
int Checker5(int);
int Checker6(int);
int Checker7(int);

int  Block_Setter(int,int,int,int,int);
void Draw_Screen();
void Show_Next_Block(int);
void Initialize();
void Write_Status();
void Present_Block_Setter();

int Column[352],Row[352];
int Status_Cell[22][16];
int Score=0;
int Count_Block_1=0,Count_Block_2=0,Count_Block_3=0,Count_Block_4=0,Count_Block_5=0,Count_Block_6=0,Count_Block_7=0;
int Room1,Room2,Room3,Room4,level1,level2,level3,level4;
int Block_Type,Rotation_Number=0;
int Counter,Time,Color,Speed_Decelarator=5;
int Present_Block,Next_Block;

void main()
{

int d=DETECT,m;
initgraph(&d,&m,"c:\\tc\\bgi");

int x,y;
 x=getmaxx()/2;
 y=getmaxy()/2;

union REGS ii,oo;
int loop,num;
int allow_shift=1;
int go=1;
int freefall=0;
int status=0;

Initialize();
randomize();
Next_Block=random(7);
Draw_Screen();


 for(Counter=500;Counter>=100;Counter-=Speed_Decelarator)
 {

	if(Counter<=400)	 Speed_Decelarator=4;
	if(Counter<=300)	 Speed_Decelarator=3;
	if(Counter<=200)	 Speed_Decelarator=1;
	if(Counter<=100)	 Counter=102;

	Write_Status();

	Present_Block=Next_Block;

	Next_Block=random(7);

	Show_Next_Block(Next_Block);

	Present_Block_Setter();

	status=0;
	Rotation_Number=0;

    while(loop==YES)
    {

		status=Block_Setter(level1,Room1,DRAW,Color,0);
			if(status==FIXED)
				loop=NO;
		status=Block_Setter(level2,Room2,DRAW,Color,0);
			if(status==FIXED)
				loop=NO;
		status=Block_Setter(level3,Room3,DRAW,Color,0);
			if(status==FIXED)
				loop=NO;
		status=Block_Setter(level4,Room4,DRAW,Color,0);
			if(status==FIXED)
				loop=NO;


		if(freefall==0)
		Time=Counter;
		else if(freefall==1)
		Time=0;

		if(loop==YES)
		delay(Time);

		if(level1<22&&level2<22&&level3<22&&level4<22&&loop==YES)
		{
			status=Block_Setter(level1,Room1,DEL,Color,0);
			status=Block_Setter(level2,Room2,DEL,Color,0);
			status=Block_Setter(level3,Room3,DEL,Color,0);
			status=Block_Setter(level4,Room4,DEL,Color,0);

			if(loop==YES)
			{
				level1++;
				level2++;
				level3++;
				level4++;
			}
		}
		else
		{
			loop=NO;
		}

		if(kbhit()&&loop==YES)
		{
			ii.h.ah=0;
			int86(22,&ii,&oo);
			go=1;
			if(oo.h.ah==1)
			{
				closegraph();
				exit(0);
			}
			if(oo.h.ah==77)
			{
				for(num=351;num>=0;num--)
				{
					if(Checker1(num))
					allow_shift=NO;
				}
				if(Room1<16&&Room2<16&&Room3<16&&Room4<16&&allow_shift==YES)
				{
					Room1++;Room2++;Room3++;Room4++;
				}
				allow_shift=YES;
			}
			if(oo.h.ah==75)
			{
				for(num=351;num>=0;num--)
				{
					if(Checker2(num))
					allow_shift=NO;
				}
				if(Room1>1&&Room2>1&&Room3>1&&Room4>1&&allow_shift==YES)
				{
					Room1--;Room2--;Room3--;Room4--;
				}
				allow_shift=YES;
			}
			if(oo.h.ah==72)
			{
				if(Block_Type==2)
				for(num=351;num>=0;num--)
				{
					if(Checker3(num))
					go=0;
					if(Checker4(num))
					go=0;
				}
				else
				for(num=351;num>=0;num--)
				{
					if(Checker5(num))
					go=0;
					if(Checker6(num))
					go=0;
				}
				if(Room1<16&&Room2<16&&Room3<16&&Room4<16&&Room1>1&&Room2>1&&Room3>1&&Room4>1&&level1<22&&level2<22&&level3<22&&level4<22&&go==1)
				{
				 if(Rotation_Number==0)
				 switch(Block_Type)
				 {
					case 1:break;
					case 2:			{Room1--;Room3++;Room4+=2;level1++;level3--;level4-=2;}break;
					case 3:			{Room1+=2;level1++;level3++;}break;
					case 4:			{Room2-=2;level2++;level4++;}break;
					case 5:			{Room1++;level1--;}break;
					case 6:			{Room2++;Room3--;level3-=2;}break;
					case 7:			{Room2--;Room3++;level3-=2;}break;
				 }
				 else if(Rotation_Number==1)
				 switch(Block_Type)
				 {
					case 1:break;
					case 2:			{Room1++;Room3--;Room4-=2;level1--;level3++;level4+=2;}break;
					case 3:			{Room1-=2;level1--;level3--;}break;
					case 4:			{Room2+=2;level2--;level4--;}break;
					case 5:			{Room4--;level4--;}break;
					case 6:			{Room1++;Room3++;level1++;level3++;level2--;level4--;}break;
					case 7:			{Room3-=2;level1++;level3--;}break;
				 }
				else if(Rotation_Number==2)
				switch(Block_Type)
				{
					case 1:break;
					case 2:Room1--;Room3++;Room4+=2;level1++;level3--;level4-=2;break;
					case 3:Room1+=2;level1++;level3++;break;
					case 4:Room2-=2;level2++;level4++;break;
					case 5:Room3--;level3++;break;
					case 6:Room2--;Room4++;level4+=2;break;
					case 7:Room4++;Room3--;level3+=2;break;
				}
				else if(Rotation_Number==3)
				switch(Block_Type)
				{
					case 1:break;
					case 2:Room1++;Room3--;Room4-=2;level1--;level3++;level4+=2;break;
					case 3:Room1-=2;level1--;level3--;break;
					case 4:Room2+=2;level2--;level4--;break;
					case 5:Room1--;Room3++;Room4++;level1++;level3--;level4++;break;
					case 6:Room1--;Room4--;level1--;level2++;level3++;level4--;break;
					case 7:Room2++;Room3+=2;Room4--;level1--;level3++;break;
				}

				Rotation_Number++;
				if(Rotation_Number==4)	Rotation_Number=0;
			 }
			}
			if(oo.h.ah==80)
			{
			freefall=1;
			}
			if(oo.h.ah==28)
			{
				settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
				setcolor(15);
				outtextxy(x-20,y-10,"Paused");
				getch();
				setcolor(0);
				outtextxy(x-20,y-10,"Paused");
			}
		}


		if(loop==NO)
		{
		  Block_Setter(level1,Room1,SKIP,Color,0);
		  Block_Setter(level2,Room2,SKIP,Color,0);
		  Block_Setter(level3,Room3,SKIP,Color,0);
		  Block_Setter(level4,Room4,SKIP,Color,0);
		  Block_Setter(level1,Room1,NORMAL,Color,0);
		  Block_Setter(level2,Room2,NORMAL,Color,0);
		  Block_Setter(level3,Room3,NORMAL,Color,0);
		  Block_Setter(level4,Room4,NORMAL,Color,1);
		  freefall=0;
		}
	    }
		loop=YES;
 }

}

int Block_Setter(int level,int Room,int col,int b_Color,int check)
{
    int num_fix=0,return_1=NO;
    int x,y;
    int num;
    int skip=NO;

    x=getmaxx()/2;
    y=getmaxy()/2;

    if(col==SKIP)
    {
	col=1;
	skip=YES;
    }

    if(skip==NO)
    {
	for(num=351;num>=0;num--)
	    if(level==Column[num]-1&&Room==Row[num])
	    {
		if(level<=1)
		{
			setcolor(14);
			settextstyle(3,0,1);
			bar(x-55,y-25,x+55,y+10);
			outtextxy(x-47,y-20,"Game Over");
			getch();
			sleep(1);
			closegraph();
			exit(0);
		}
		col=NORMAL;
	    }
    }

    if(col==DRAW)
    {
	setfillstyle(SOLID_FILL,b_Color);
	bar(x-160+1+20*(Room-1),y-220+1+20*(level-1),x-140-1+20*(Room-1),y-200-1+20*(level-1));
    }
    else if(col==DEL)
    {
	setfillstyle(SOLID_FILL,0);
	bar(x-160+1+20*(Room-1),y-220+1+20*(level-1),x-140-1+20*(Room-1),y-200-1+20*(level-1));
    }
    else
    {
	Status_Cell[level-1][Room-1]=OCCUPIED;
	int repeat=1;
	while(repeat==1)
	{
		repeat=0;
		if(Column[num_fix]==0&&Row[num_fix]==0)
		{
			Column[num_fix]=level;
			Row[num_fix]=Room;
		}
		else
		{
			num_fix++;
			repeat=1;
		}
	}
	if(num_fix==351)	num_fix=0;
	else			num_fix++;

	sound(200);	delay(30);	nosound();

	return_1=YES;
    }

	int comp[22];
	int checkagain=1;
	int loop1,loop2;

   while(checkagain==1)
   {
       checkagain=0;
       if(check==1)
       {

	 for(loop1=0;loop1<22;loop1++)
		 comp[loop1]=1;

	 for(loop1=0;loop1<22;loop1++)
	     for(loop2=0;loop2<16;loop2++)
		 if(Status_Cell[loop1][loop2]==UNOCCUPIED)
			 comp[loop1]=0;

	 for(loop1=21;loop1>=0;loop1--)
	 if(comp[loop1]==1)
	 {
		 for(num=351;num>=0;num--)
		  if(Column[num]==loop1+1)
		  {
			   Column[num]=0;Row[num]=0;
		  }
		 for(num=351;num>=0;num--)
		  if(Column[num]<=loop1&&Column[num]!=0)
		  {
			   Column[num]++;
		  }
		 for(loop2=loop1;loop2>0;loop2--)
		   for(num=0;num<16;num++)
		   {
			    Status_Cell[loop2][num]=Status_Cell[loop2-1][num];
		   }
		   for(num=0;num<16;num++)
			  Status_Cell[0][num]=UNOCCUPIED;

		setfillstyle(SOLID_FILL,0);
		bar(x-160,y-220,x+160,y+220);
		setcolor(WHITE);
		rectangle(x-161,y-221,x+161,y+221);
		rectangle(x-163,y-223,x+163,y+223);
		setfillstyle(SOLID_FILL,0);

		for(num=0;num<16;num++)
		bar(x-160+1+20*(num),y-220+1+20*(loop1),x-140-1+20*(num),y-200-1+20*(loop1));
		setfillstyle(SOLID_FILL,LIGHTRED);

		for(loop2=21;loop2>=0;loop2--)
		{
		 for(num=0;num<16;num++)
		  if(Status_Cell[loop2][num]==OCCUPIED)
		   bar(x-160+1+20*(num),y-220+1+20*(loop2),x-140-1+20*(num),y-200-1+20*(loop2));
		}
		checkagain=1;
		loop1=-1;
		Score++;
	 }
      }
    }

	if(return_1==YES)
		return FIXED;
	else
		return FALLING;
}

void Draw_Screen()
{
int x,y;
x=getmaxx()/2;
y=getmaxy()/2;

setcolor(WHITE);
 rectangle(x-161,y-221,x+161,y+221);
 rectangle(x-163,y-223,x+163,y+223);

setfillstyle(11,8);
floodfill(x-290,y+220,WHITE);
setfillstyle(SOLID_FILL,BLUE);
bar(x+210+1,y-220+1,x+230-1,y-200-1);
bar(x+190+1,y-220+1,x+210-1,y-200-1);
bar(x+210+1,y-200+1,x+230-1,y-180-1);
bar(x+190+1,y-200+1,x+210-1,y-180-1);
setfillstyle(SOLID_FILL,GREEN);
bar(x+210+1,y-160+1,x+230-1,y-140-1);
bar(x+230+1,y-160+1,x+250-1,y-140-1);
bar(x+190+1,y-160+1,x+210-1,y-140-1);
bar(x+170+1,y-160+1,x+190-1,y-140-1);
setfillstyle(SOLID_FILL,RED);
bar(x+210+1,y-75+1,x+230-1,y-55-1);
bar(x+210+1,y-55+1,x+230-1,y-35-1);
bar(x+190+1,y-35+1,x+210-1,y-15-1);
bar(x+190+1,y-55+1,x+210-1,y-35-1);
setfillstyle(SOLID_FILL,7);
bar(x+200+1,y-5+1,x+220-1,y+15-1);
bar(x+200+1,y+15+1,x+220-1,y+35-1);
bar(x+220+1,y-5+1,x+240-1,y+15-1);
bar(x+180+1,y-5+1,x+200-1,y+15-1);
setfillstyle(SOLID_FILL,BROWN);
bar(x+200+1,y+45+1,x+220-1,y+65-1);
bar(x+220+1,y+65+1,x+240-1,y+85-1);
bar(x+220+1,y+45+1,x+240-1,y+65-1);
bar(x+180+1,y+45+1,x+200-1,y+65-1);
setfillstyle(SOLID_FILL,MAGENTA);
bar(x+200+1,y-110+1,x+220-1,y-90-1);
bar(x+220+1,y-130+1,x+240-1,y-110-1);
bar(x+220+1,y-110+1,x+240-1,y-90-1);
bar(x+180+1,y-110+1,x+200-1,y-90-1);
setfillstyle(SOLID_FILL,CYAN);
bar(x+190+1,y+100+1,x+210-1,y+120-1);
bar(x+210+1,y+100+1,x+230-1,y+120-1);
bar(x+210+1,y+120+1,x+230-1,y+140-1);
bar(x+190+1,y+80+1,x+210-1,y+100-1);
setcolor(RED);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
outtextxy(x+190,y+205,"STATISTICS");

setlinestyle(SOLID_LINE,1,3);
line(x-285,y+120,x-285,y+135);
line(x-285,y+120,x-290,y+125);
line(x-285,y+120,x-280,y+125);
line(x-285,y+185,x-285,y+200);
line(x-285,y+200,x-290,y+195);
line(x-285,y+200,x-280,y+195);
line(x-292,y+150,x-278,y+150);
line(x-292,y+150,x-287,y+155);
line(x-292,y+150,x-287,y+145);
line(x-292,y+170,x-278,y+170);
line(x-278,y+170,x-283,y+175);
line(x-278,y+170,x-283,y+165);
setlinestyle(SOLID_LINE,1,1);
setcolor(BROWN);
line(x-265,y+170,x-260,y+170);
line(x-265,y+190,x-260,y+190);
line(x-265,y+150,x-260,y+150);
line(x-265,y+128,x-260,y+128);
line(x-255,y+217,x-250,y+217);
outtextxy(x-292,y+205,"ESC");
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
outtextxy(x-240,y+215,"Exit");
setcolor(BLUE);
outtextxy(x-285,y-70,"Enter");
outtextxy(x-230,y-70,"Pause");
setcolor(5);
line(x-243,y-67,x-237,y-67);
setcolor(RED);
outtextxy(x-250,y+125,"Rotate");
outtextxy(x-250,y+146,"Move left");
outtextxy(x-250,y+188,"Free fall");
outtextxy(x-250,y+166,"Move right");


setcolor(GREEN);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
outtextxy(x-263,y+55,"NEXT");
setcolor(WHITE);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
outtextxy(x-300,y-215,"LINES  __");

}

void Show_Next_Block(int Block)
{

int x,y;
 x=getmaxx()/2;
 y=getmaxy()/2;

int shift_x=-450;

setfillstyle(SOLID_FILL,BLACK);
bar(x-290+1,y-50,x-191,y+50);
setcolor(WHITE);
rectangle(x-290+1,y-50,x-191,y+50);

	switch(Block)
	{
	  case 0:
		setfillstyle(SOLID_FILL,BLUE);
		bar(x+210+1+shift_x,y-220+1+200,x+230-1+shift_x,y-200-1+200);
		bar(x+190+1+shift_x,y-220+1+200,x+210-1+shift_x,y-200-1+200);
		bar(x+210+1+shift_x,y-200+1+200,x+230-1+shift_x,y-180-1+200);
		bar(x+190+1+shift_x,y-200+1+200,x+210-1+shift_x,y-180-1+200);
	  break;
	  case 1:
		setfillstyle(SOLID_FILL,GREEN);
		bar(x+210+1+shift_x,y-160+1+150,x+230-1+shift_x,y-140-1+150);
		bar(x+230+1+shift_x,y-160+1+150,x+250-1+shift_x,y-140-1+150);
		bar(x+190+1+shift_x,y-160+1+150,x+210-1+shift_x,y-140-1+150);
		bar(x+170+1+shift_x,y-160+1+150,x+190-1+shift_x,y-140-1+150);
	  break;
	  case 2:
		setfillstyle(SOLID_FILL,CYAN);
		bar(x+190+1+shift_x,y+110+1-10-110,x+210-1+shift_x,y+130-1-10-110);
		bar(x+210+1+shift_x,y+110+1-10-110,x+230-1+shift_x,y+130-1-10-110);
		bar(x+210+1+shift_x,y+130+1-10-110,x+230-1+shift_x,y+150-1-10-110);
		bar(x+190+1+shift_x,y+90+1-10-110,x+210-1+shift_x,y+110-1-10-110);
	  break;
	  case 3:
		setfillstyle(SOLID_FILL,RED);
		bar(x+210+1+shift_x,y-60+1-15+45,x+230-1+shift_x,y-40-1-15+45);
		bar(x+210+1+shift_x,y-40+1-15+45,x+230-1+shift_x,y-20-1-15+45);
		bar(x+190+1+shift_x,y-20+1-15+45,x+210-1+shift_x,y-0-1-15+45);
		bar(x+190+1+shift_x,y-40+1-15+45,x+210-1+shift_x,y-20-1-15+45);
	  break;
	  case 4:
		setfillstyle(SOLID_FILL,7);
		bar(x+200+1+shift_x,y+10+1-15-5,x+220-1+shift_x,y+30-1-15-5);
		bar(x+200+1+shift_x,y+30+1-15-5,x+220-1+shift_x,y+50-1-15-5);
		bar(x+220+1+shift_x,y+10+1-15-5,x+240-1+shift_x,y+30-1-15-5);
		bar(x+180+1+shift_x,y+10+1-15-5,x+200-1+shift_x,y+30-1-15-5);
	  break;
	  case 5:
		setfillstyle(SOLID_FILL,BROWN);
		bar(x+200+1+shift_x,y+60+1-15-55,x+220-1+shift_x,y+80-1-15-55);
		bar(x+220+1+shift_x,y+80+1-15-55,x+240-1+shift_x,y+100-1-15-55);
		bar(x+220+1+shift_x,y+60+1-15-55,x+240-1+shift_x,y+80-1-15-55);
		bar(x+180+1+shift_x,y+60+1-15-55,x+200-1+shift_x,y+80-1-15-55);
	  break;
	  case 6:
		setfillstyle(SOLID_FILL,MAGENTA);
		bar(x+200+1+shift_x,y-110+1+105,x+220-1+shift_x,y-90-1+105);
		bar(x+220+1+shift_x,y-130+1+105,x+240-1+shift_x,y-110-1+105);
		bar(x+220+1+shift_x,y-110+1+105,x+240-1+shift_x,y-90-1+105);
		bar(x+180+1+shift_x,y-110+1+105,x+200-1+shift_x,y-90-1+105);
	  break;
	  default:
	  break;
	}
}

void Write_Status()
{
	gotoxy(15,3);	cout<<Score;
	gotoxy(75,3);	cout<<Count_Block_1;
	gotoxy(75,6);	cout<<Count_Block_2;
	gotoxy(75,9);	cout<<Count_Block_7;
	gotoxy(75,13);	cout<<Count_Block_4;
	gotoxy(75,16);	cout<<Count_Block_5;
	gotoxy(75,19);	cout<<Count_Block_6;
	gotoxy(75,23);	cout<<Count_Block_3;
}

void Present_Block_Setter()
{
	switch(Present_Block)
	{
		case 0:
			Count_Block_1++;
			Block_Type=1;
			Room1=8;Room2=9;Room3=8;Room4=9;
			level1=1;level2=1;level3=2;level4=2;
			Color=1;
							break;
		case 1:
			Count_Block_2++;
			Block_Type=2;
			Room1=8;Room2=8;Room3=8;Room4=8;
			level1=1;level2=2;level3=3;level4=4;
			Color=2;
							break;
		case 2:
			Count_Block_3++;
			Block_Type=3;
			Room1=8;Room2=9;Room3=8;Room4=9;
			level1=1;level2=2;level3=2;level4=3;
			Color=3;
							break;
		case 3:
			Count_Block_4++;
			Block_Type=4;
			Room1=8;Room2=9;Room3=8;Room4=9;
			level1=2;level2=1;level3=3;level4=2;
			Color=4;
							break;
		case 4:
			Count_Block_5++;
			Block_Type=5;
			Room1=8;Room2=9;Room3=10;Room4=9;
			level1=1;level2=1;level3=1;level4=2;
			Color=7;
							break;
		case 5:
			Count_Block_6++;
			Block_Type=6;
			Room1=8;Room2=8;Room3=8;Room4=9;
			level1=1;level2=2;level3=3;level4=1;
			Color=6;
							break;
		case 6:
			Count_Block_7++;
			Block_Type=7;
			Room1=8;Room2=8;Room3=8;Room4=7;
			level1=1;level2=2;level3=3;level4=1;
			Color=5;
							break;
	}
}


void Initialize()
{

    for(int q=0;q<22;q++)
	for(int q1=0;q1<16;q1++)
	     Status_Cell[q][q1]=UNOCCUPIED;

    for(q=0;q<351;q++)
    {
	 Column[q]=0;
	 Row[q]=0;
    }

}
int Checker1(int num)
{
if(level1==Column[num]-1&&Room1+1==Row[num]||level2==Column[num]-1&&Room2+1==Row[num]||level3==Column[num]-1&&Room3+1==Row[num]||level4==Column[num]-1&&Room4+1==Row[num]||level1==Column[num]&&Room1+1==Row[num]||level2==Column[num]&&Room2+1==Row[num]||level3==Column[num]&&Room3+1==Row[num]||level4==Column[num]&&Room4+1==Row[num])
return 1;
else
return 0;

}

int Checker2(int num)
{
if(level1==Column[num]-1&&Room1-1==Row[num]||level2==Column[num]-1&&Room2-1==Row[num]||level3==Column[num]-1&&Room3-1==Row[num]||level4==Column[num]-1&&Room4-1==Row[num]||level1==Column[num]&&Room1-1==Row[num]||level2==Column[num]&&Room2-1==Row[num]||level3==Column[num]&&Room3-1==Row[num]||level4==Column[num]&&Room4-1==Row[num])
return 1;
else
return 0;
}

int Checker3(int num)
{
if(level1==Column[num]-1&&Room1+1==Row[num]||level2==Column[num]-1&&Room2+1==Row[num]||level3==Column[num]-1&&Room3+1==Row[num]||level4==Column[num]-1&&Room4+1==Row[num]||level1==Column[num]&&Room1+1==Row[num]||level2==Column[num]&&Room2+1==Row[num]||level3==Column[num]&&Room3+1==Row[num]||level4==Column[num]&&Room4+1==Row[num]&&level1==Column[num]-2&&Room1+1==Row[num]||level2==Column[num]-2&&Room2+1==Row[num]||level3==Column[num]-2&&Room3+1==Row[num]||level4==Column[num]-2&&Room4+1==Row[num]||level1==Column[num]&&Room1+1==Row[num]||level2==Column[num]&&Room2+1==Row[num]||level3==Column[num]&&Room3+1==Row[num]||level4==Column[num]&&Room4+1==Row[num])
return 1;
else
return 0;
}


int Checker4(int num)
{
if(level1==Column[num]-1&&Room1-1==Row[num]||level2==Column[num]-1&&Room2-1==Row[num]||level3==Column[num]-1&&Room3-1==Row[num]||level4==Column[num]-1&&Room4-1==Row[num]||level1==Column[num]&&Room1-1==Row[num]||level2==Column[num]&&Room2-1==Row[num]||level3==Column[num]&&Room3-1==Row[num]||level4==Column[num]&&Room4-1==Row[num]&&level1==Column[num]-2&&Room1-1==Row[num]||level2==Column[num]-2&&Room2-1==Row[num]||level3==Column[num]-2&&Room3-1==Row[num]||level4==Column[num]-2&&Room4-1==Row[num]||level1==Column[num]&&Room1-1==Row[num]||level2==Column[num]&&Room2-1==Row[num]||level3==Column[num]&&Room3-1==Row[num]||level4==Column[num]&&Room4-1==Row[num]||level1>=21||level2>=21||level3>=21||level4>=21)
return 1;
else
return 0;
}

int Checker5(int num)
{
if(level1==Column[num]-1&&Room1+1==Row[num]||level2==Column[num]-1&&Room2+1==Row[num]||level3==Column[num]-1&&Room3+1==Row[num]||level4==Column[num]-1&&Room4+1==Row[num]||level1==Column[num]&&Room1+1==Row[num]||level2==Column[num]&&Room2+1==Row[num]||level3==Column[num]&&Room3+1==Row[num]||level4==Column[num]&&Room4+1==Row[num])
return 1;
else
return 0;
}

int Checker6(int num)
{
if(level1==Column[num]-1&&Room1-1==Row[num]||level2==Column[num]-1&&Room2-1==Row[num]||level3==Column[num]-1&&Room3-1==Row[num]||level4==Column[num]-1&&Room4-1==Row[num]||level1==Column[num]&&Room1-1==Row[num]||level2==Column[num]&&Room2-1==Row[num]||level3==Column[num]&&Room3-1==Row[num]||level4==Column[num]&&Room4-1==Row[num])
return 1;
else
return 0;
}







