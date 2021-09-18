//snake game
#include<stdlib.h>
#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<iostream.h>
char snake_array[20][70];
int m,n,arrx[20],arry[70],k=17,p=68,tail=0,x=34,y=14,score;
void growth()     //the function adds tail to the snake
{
	int prevx,prevy,prev2x,prev2y;
	m=arrx[tail];
	n=arry[tail];
	prevx=arrx[0];
	prevy=arry[0];
	arrx[0]=k;
	arry[0]=p;
	for(int i=1;i<tail;i++)
	{
		prev2x=arrx[i];
		prev2y=arry[i];
		arrx[i]=prevx;
		arry[i]=prevy;
		prevx=prev2x;
		prevy=prev2y;
	}
}
void snake() //the function creates a snake at the bottom left corner
{              	//and displays the score
		cout<<"            __"<<"\n";
		cout<<"    __     /*_>-"<<"\n";
		cout<<" __/__ \\__/ /"<<"                         SCORE: "<<score<<"\n";
		cout<<"<__/   \\__/";
}
int eat()    //the function returns 1 if the snake eats food
{            //and 0 if not
	growth();
	if((y==k&&(x==p-1||x==p+1))||((y==k-1||y==k+1)&&x==p))
	{
		snake_array[y][x]='O';
		k=y;
		p=x;
		tail++;
		return 1;
	}
	return 0;
}
void score_cal(int n)  //calculates score
{
	if(n==1)
		score+=10;
}
void food() //generates food
{
	srand(time(0));
	x=rand()%67 + 1;
	y=rand()%17 + 1;
}
void display()// displays the values of array snake_array
{
	cout<<"\n";
	for(int i=0;i<tail;i++)
	{
		snake_array[arrx[i]][arry[i]]='o';
	}
	snake_array[0][0]='*';
	for( i=0;i<20;i++)
	{
		for(int j=0;j<70;j++)
			cout<<snake_array[i][j];
		cout<<"\n";
	}
}

void wall() //creates boundry wall
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<70;j++)
		{
			if((i==0||i==19)||(j==0||j==69))
				snake_array[i][j]='*';
			else
			{
				if((i!=y||j!=x))
				snake_array[i][j]=' ';

			}
		}
	}
	snake_array[k][p]='O';
	snake_array[y][x]='$';
	display();
	snake();
}
int collision(int a,int b)  //checks whether the snake has collided with itself or not
{
	if(a==m&&b==n)
		return 1;
	for(int i=0;i<tail;i++)
		if(a==arrx[i]&&b==arry[i])
			return 1;
	return 0;
}
int move(int m)//moves the snake in different direction
{
	int n=eat();
	if(n==0)
	{
		switch (m)
		{
			case 'x':
				exit(1);
				break;
			case 'w':
				if(snake_array[k-1][p]=='*'||collision(k-1,p))
				{
					cout<<"\nGAME OVER";
					exit(1);
				}
				snake_array[--k][p]='O';
				break;
			case 's':
				if(snake_array[k+1][p]=='*'||collision(k+1,p))
				{
					cout<<"\nGAME OVER";
					exit(1);
				}
				snake_array[++k][p]='O';
				break;
			case 'a':
				if(snake_array[k][p-1]=='*'||collision(k,p-1))
				{
					cout<<"\nGAME OVER";
					exit(1);
				}
				snake_array[k][--p]='O';
				break;
			case 'd':
				if(snake_array[k][p+1]=='*'||collision(k,p+1))
				{
					cout<<"\nGAME OVER";
					exit(1);
				}
				snake_array[k][++p]='O';
				break;
			default:
				return 2;
		}
	}
	return n;
}
int call()//calls all the function in a sequence for execution of the game
{
	int m,n;
	wall();
	do
	{
		m=getch();
		n=move(m);
	}while(n==2);
	score_cal(n);
	system("cls");
	return n;
}

int main()
{
	clrscr();
	int n;
	cout<<"\n****************************WELCOME**********************";
	cout<<"\n RULES:";
	cout<<"\n1:PRESS W-> to go up";
	cout<<"\n2:PRESS S-> to go down";
	cout<<"\n3:PRESS A-> to go left";
	cout<<"\n4:PRESS D-> to go right";
	cout<<"\n5:PRESS X-> to exit";
	cout<<"\nPRESS 0 TO START GAME";
	cin>>n;
	if(n==0)
	{
		while(1)
		{
			if(n==1)
				food();
			n = call();
		}
	}
	return 0;
}
