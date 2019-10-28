#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define N 8
typedef struct Node
{
    int x,y;
    int distance;
} Node;

int row[]={-2, -1, 1, 2, -2, -1, 1, 2};
int col[]={-1, -2, -2, -1, 1, 2, 2, 1}; 

int visit[N+1][N+1];
Node q[100];
int front=-1;
int rear=-1;



int valid(int x, int y) 
{
    //checking if the coordinate given doesnt go out of the chess board
    if(x<0 || y<0 || x>=N || y>=N)
    {
        return 0;
    }
    else 
        return 1;
}

void push(int x, int y,int distance)
{
    if(rear==N-1)
    {
        printf("Queue is full\n");
        return;
    }
    else
    {
        rear++;
        q[rear].x=x;
        q[rear].y=y;
        q[rear].distance=distance;
    }
    
}
void pop()
{
    if(front==-1)
    {
        printf("Queue Underflow\n");
        return;
    }
    else
    {
        front++;
        return;
    }
    
}

int qisempty()
{
    if(rear==-1 && front ==-1)
    {
        return 1;
    }
    else return 0;
}
int bfs(int sx,int sy,int dx,int dy)
{
    Node t;
    int x,y;
    push(sx,sy,0);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            visit[i][j]=0;
        }
    }
    visit[sx][sy]=1;
    while(!qisempty())
    {
        t=q[front];
        pop();
        if(t.x==dx && t.y==dy)
        {
            return t.distance;
        }
        for(int i=0;i<8;i++)
        {
            x=t.x+row[i];
            y=t.y+col[i];

            if(valid(x,y) &&!visit[x][y])
            {
                visit[x][y]=1;
                push(x,y,t.distance+1);
            }
        }
    }
}

int main()
{
    //Destination coordinates
    int dx,dy;
    //Source coordinates
    int sx,sy;
    printf("Enter the Source Coordinates (x,y): \n");
    scanf("%d%d",&sx,&sy);
    printf("Enter the Destiation Coordinates (x,y): \n");
    scanf("%d%d",&dx,&dy);
    printf("shortest path: %d ",bfs(sx,sy,dx,dy));

}