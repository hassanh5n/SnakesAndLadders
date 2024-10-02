#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct
{
    int type; 
    int to;    
}Cell;

struct small
{
	char name[100];
	int num;
};

float average(FILE *ptr)
{
	char b[100];
	int a,sum=0,c=0;
	float av;
	while(feof(ptr)==0)
	{
	    fscanf(ptr,"%s",&b);
		fscanf(ptr,"%d",&a);
		printf("%s\t\t",b);
		printf("%d Moves\n",a);
		
		sum=sum+a;
		c++;
	}
	av=(float)sum/(float)c;
	printf("\nAverage Move Count = %.2f",av);
	return av;
}

int check(FILE *ptr1)
{
	struct small small,a;
	fscanf(ptr1,"%s",&small.name);
	fscanf(ptr1,"%d",&small.num);
	
	while(feof(ptr1)==0)
	{
		
		fscanf(ptr1,"%s",&a.name);
		fscanf(ptr1,"%d",&a.num);
		if(small.num>=a.num)
		{
			strcpy(small.name,a.name);
			small.num = a.num;
		}
	}
	
	printf("\n\nCurrent Leader = %s",small.name);
	printf("\n%s's Move Count = %d Moves\n",small.name,small.num);
	if(small.num<a.num)
	{
		return 0;
	}
	else
	{
		return 1;
	}		
}

void initialize(Cell** gameboard)
{
    int i;
    for(i=0; i<100; i++){
        gameboard[i] = (Cell*)malloc(sizeof(Cell));
        gameboard[i]->type = 0; 
        gameboard[i]->to = 0;
    }
}


void addSnakeOrLadder(Cell** gameboard, int start, int end, int type)
{
    gameboard[start]->type = type; 
    gameboard[start]->to = end;
}

void play(Cell** gameboard)
{
    int position = 0;
    int dice;
    int temp;
    int c=0;
    int lives=3;

   // printf("Position : %d\n\n", position);

    while(position != 100 )
	{
    	char a[100];
    	//printf("-------------------------------------");
        printf("\nEnter any key to roll the dice...\n");
        dice-=(getch());
        dice=(rand()%6)+1;
        c++;
        printf("\nYou roll dice: |%d| \n",dice);
        position = position + dice;
        if(position>100)
        {
        	printf("\nRoll Again!! ");
        	position=position-dice;
		}
        printf("\nNew Position: |%d|\n", position);

        if(position == 100)
		{
        	printf("\n-------------CONGRATULATIONS-------------");
            printf("\nYOU HAVE WON THE GAME!!!\n\n");
            printf("YOU HAVE COMPLETED THE GAME IN %d ROLLS\n\n",c);
            displayBoard(position);
            getchar();
            printf("Enter Your First Name:\n");
    	    gets(a);
            FILE *fp;
	        fp=fopen("f.txt","a");
	        printf("\n---------------------------\n");
	        printf("\nLeaderBoard\tMoves");
	        printf("\n---------------------------\n");
	        fprintf(fp,"%s\t",a);
            fprintf(fp,"%d",c);
            fclose(fp);
            fp=fopen("f.txt","a+");
            printf("\n");
            int z=average(fp);
            printf("\n");
	        if(c==z)
            {
    	        printf("\nThe Move Count is Equal to Average");
	        }
	        else if(c>z)
            {
    	        printf("\nUnfortunately, \nYour Move Count is Higher than Average");
	        }
	        else if(c<z)
            {
    	        printf("\nYou did Great! \nYour Move Count is Lower than Average");
	        }
	
	        fclose(fp);
	        
	        fp=fopen("f.txt","a+");
	        int b=check(fp);
	        if(b==1)
	        {
		        printf("\nYOU ARE THE NEW LEADER");
	        }
	        if(b==0)
	        {
                printf("\nBETTER LUCK NEXT TIME");
	        }
	        printf("\n\n\n\n--------MADE BY HASSAN, MOHID, AAQIB------------");
	        fclose(fp);
            break;
        }
        

        if(gameboard[position]->type == 1)
		{
            printf("\nClimbing up the ladder\n");
            printf("\t|-|\n");
            printf("\t|-|\n");
            printf("\t|-|\n");
            position = gameboard[position]->to;
        }
        else if(gameboard[position]->type == 2)
		{
            printf("Sliding down the snake\n");
            printf("\t~-----.<\n");
            position = gameboard[position]->to;
            lives--;
            if (lives == 0)
            {
            	printf("\n-------------UNFORTUNATELY-------------");
   				printf("\nYOU HAVE FAILED.\n");
   				printf("Your position was %d\n\n",position);
   				displayBoard(position);
            	break;
			}
        }
        else
		{
            position = position;
        }
        printf("Position : %d\n", position);
        printf("\nYou have %d lives left\n\n",lives);
        displayBoard(position);
    }
    getch();
}

void displayBoard(int position) 
{
    int board[10][10],i, j, count = 100;
    for (i=0;i<10;i++) 
	{
        if (i%2 == 0) 
		{
            for (j=0;j<10;j++) 
			{
                board[i][j] = count--;
            }
        } 
		else 
		{
            for (j=9;j>=0;j--) 
			{
                board[i][j] = count--;
            }
        }
    }
    printf("\t\t   S N A K E S   A N D   L A D D E R S\n");
	printf("_______________________________________________________________________________\n\n");
    for (i=0;i<10;i++) 
	{
        for (j=0;j<10;j++) 
		{
            if (board[i][j] == position) 
			{
                printf(" |X|\t"); 
            } 
			else 
			{
                printf("  %d\t", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("_______________________________________________________________________________\n\n");
}


int main()
{
    Cell** gameboard;
    int i,choice;
    char a[100];
    srand(time(NULL));
    
    gameboard = (Cell*)malloc(100 * sizeof(Cell));
    printf("SNAKES AND LADDERS\n");
    printf("Press [1] to READ THE RULES");
    printf("\nPress [2] to PLAY THE GAME\n");
    scanf("%d",&choice);
    switch (choice)
    {
    	
    case 1:	
   printf("\nRules");
   printf("\n[1]If The Snake Bites You 3 Times, THE GAME IS OVER");
   printf("\n[2]Game will Start from 0 Position and Ends on 100 Position");
   printf("\n[3]Snakes are Your ENEMIES and Ladders are Your FRIENDS");
   printf("\n[4]You can Press ANY Key to Roll the Dice");
   printf("\n[5]There are In Total, 3 Ladders and 5 Snakes.");
   printf("\n[6]You need to complete the Game in order to reach the Leaderboard.");
   printf("Enjoy the game!");
   printf("\n\n");
   case 2:
   printf("\n\t  WELCOME TO SNAKES AND LADDER \n");
   printf("_________________________________________________________________\n\n");
   printf(" | 100 99  98  97  96  95  94  93  92  91  | 1 = Start \n");
   printf(" | 81  82  83  84  85  86  87  88  89  90  | 4 = Ladder to 14\n");  
   printf(" | 80  79  78  77  76  75  74  73  72  71  | 17 = Snake to 7\n");  
   printf(" | 61  62  63  64  65  66  67  68  69  70  | 21 = Ladder to 42\n"); 
   printf(" | 60  59  58  57  56  55  54  53  52  51  | 46 = Snake to 13\n");  
   printf(" | 41  42  43  44  45  46  47  48  49  50  | 62 = Snake to 19\n"); 
   printf(" | 40  39  38  37  36  35  34  33  32  31  | 72 = Ladder to 91\n");
   printf(" | 21  22  23  24  25  26  27  28  29  30  | 89 = Snake to 70\n");
   printf(" | 20  19  18  17  16  15  14  13  12  11  | 99 = Snake to 1\n");
   printf(" | 1   2   3   4   5   6   7   8   9   10  | 100 = End\n");
   printf("_________________________________________________________________\n\n");
   //printf("\n\n");
   
    
    initialize(gameboard);

    addSnakeOrLadder(gameboard, 4, 14, 1);
    addSnakeOrLadder(gameboard, 21, 42, 1);
    addSnakeOrLadder(gameboard, 72, 91, 1);
    addSnakeOrLadder(gameboard, 62, 19, 2);
    addSnakeOrLadder(gameboard, 46, 13, 2);
    addSnakeOrLadder(gameboard, 17, 7, 2);
    addSnakeOrLadder(gameboard, 89, 70, 2);
    addSnakeOrLadder(gameboard, 99, 1, 2);
    

    play(gameboard);

    for( i=0; i<100; i++)
	{
        free(gameboard[i]);
    }
    free(gameboard);
    break;
}
    return 0;
}

