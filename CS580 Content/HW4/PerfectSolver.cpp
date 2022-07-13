#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
using namespace std;
char input[43]; // There are 42 places to play in the board
void Board();
int continuePlay = 0;
int evaluate = 0;


/** 
 * evaluate and continuePlay are variables utilized from within the execution of the NegaMax function.
 * The NegaMax function is a variation of the MiniMax algorithm that takes advantage of the fact that in Connect 4 the score
 * of one of the players will be the opposite of the oppponent's score, and so it is only needed to be callled half the amount of 
 * times that the typical MinixMax function would have to be.
 */

int AIManager();
int winning();
int GetValue(int t);
int NegaMax(int Depth);

/**
 *  Clears the board / array
 *
 */
void clean()
{
    for(int i = 0 ; i<= 80 ; i++)
        input[i]=' ';
}

/**
 *  Pass the function a column that you want to play in and it will return its value in input array.
 *  This function allows the array to understand what position to be placed in by altering the column
 *  given by necessary parameters rather than asking the user individual numbers for each possible
 *  placement, thus simulating a real game of Connect 4.
 *
 *  @parm column : one of 7 possible columns represented as an integer (from 1 to 7)
 */
int GetValue(int column)
{
    if(column > 7)
        return 0;
    int n;
    for(int i = 0 ; i<= 6 ; i++)
    {
        if( input[column+7*i] == ' '  ) // starts at bottom of column and goes up
        {
            n = column+7*i;
            break;
        }
    }
    if ( n > 42 )
        return 0;
    return n;
}

/**
 *  Winning algorithm. Has anyone gotten four in a row yet?
 *
 */
int winning()
{
    int temp=0;
    for(int i = 1 ; i<= 42 ; i++)
    {
        if(input[i] != ' ')
        {
            temp++;
            if( i - int((i-1)/7) * 7 <= 4  )
                if( input[i] == input [i+1] && input[i] == input[i+2] && input[i] == input[i+3] ) //horizontal check
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i <= 21 )
                if ( input[i] == input[i+7] && input[i] == input[i+14] && input[i] == input[i+21]  ) //vertical check
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - int((i-1)/7) * 7 <= 4 && i<=18  )
                if(input[i] == input[i+8] && input[i] == input[i+16] && input[i]==input[i+24]) //back-slash diagonal ('\') check
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - int((i-1)/7) * 7 >= 4 && i <= 21   )
                if(input[i] == input[i+6] && input[i] == input[i+12] && input[i]==input[i+18]) //forward-slash diagonal ('/') check
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
        }

    }
    if (temp == 42)
        return 3;
    return 0;
}

/**
 *  Draw board
 *
 */
void Board()
{
    cout<<endl<<"    1   "<<"    2   "<<"    3   "<<"    4   "<<"    5   "<<"    6   "<<"    7   "<<endl;  //labels columns

    int j = 42;
    for(int i = 0 ; i<= 23 ; i++)
    {
        if(i % 4 == 0)
            cout<<string(57,'-'); //vertical lines
        else
        {
            if( (i - 2) % 4 == 0)
            {
                j=42-(0.25*i+0.5)*6-((0.25*i+0.5)-1) ;  //which position to start with
                for(int i = 0 ; i<=6 ; i++)
                {
                    cout<<"|"<<"   "<<input[j]<<"   ";  // prints blank or 'X' or 'O' for that row in each space
                    j++;
                }
                cout<<"|";
            }
            else
            {
                for(int i = 0 ; i<=6 ; i++)
                    cout<<"|"<<string(7,' '); //prints out just column lines for neatness and spacing between vertical lines
                cout<<"|";
            }
        }
        cout<<endl;
    }
    cout<<string(57,'-');
}


/**
 *  Function that asks you to enter where you like to play
 *
 *  @param XO : Takes the value (typically 'X' or 'O') and establishes input
 */
void PlayPosition(char XO)
{
    int sth;
    cout<<endl<<"Where would you like to play?" << endl;
    while(true)
    {
        cin>>sth;
        sth=GetValue(sth);
        if( sth != 0 )
        {
            input[sth] = XO;
            return ;
        }
        else
            cout<<"ERROR"<<endl;
    }
}

/**
 *  AI Algorithm
 *
 */
int AIManager()
{
    float chance[2] = {9999999 , 0 };
    for(int column = 1 ; column <= 7 ; column ++)
    {
        continuePlay = 0;
        evaluate=0;
        int PlayNumber = GetValue(column);
        if( PlayNumber != 0 )
        {

            input[PlayNumber] = 'O';
            if(winning()==2)
               {
                   input[PlayNumber]=' ';
                   return PlayNumber ;
               }
            float temp = -(100*NegaMax(1));
            if(continuePlay != 0)
                temp -= ((100*evaluate)/continuePlay);
            if( chance[0] > temp  )
            {
                chance[0] = temp  ;
                chance[1] = PlayNumber;
            }
            //cout<<endl<<-temp<<"   "<<evaluate << "   " <<continuePlay;
            input[PlayNumber] = ' ';
        }
    }
    return chance[1];
}

/**
 *  MiniMax algorithm in NegaMax form
 *
 *  @param Depth : number of passes
 */
int NegaMax(int Depth)
{
    char XO;
    int PlayNumber[8] = {0,0,0,0,0,0,0,0}; // The values of the input[] for every column
    int chance=0;
    if(Depth % 2 != 0)
        XO='X';
    else
        XO='O';
    for(int column = 1 ; column <= 7 ; column ++)
        PlayNumber[column]=GetValue(column);
    for(int column = 1 ; column <= 7 ; column++)
    {
        if(PlayNumber[column] != 0)
        {
            input[PlayNumber[column]]=XO;
            if( winning() != 0 )
            {
                continuePlay ++;
                if(XO=='O')
                    evaluate ++;
                else
                    evaluate --;
                input[PlayNumber[column]]=' ';
                return -1;
            }
            input[PlayNumber[column]]=' ';
        }
    }
    if(Depth <= 6)
    {

        for(int column = 1 ; column <= 7 ; column ++)
        {
            int temp=0;
            if( PlayNumber[column] != 0 )
            {
                input[PlayNumber[column]]=XO;
                if( winning() != 0 )
                {
                    continuePlay++;
                    if(XO=='O')
                        evaluate++;
                    else
                        evaluate--;
                    input[PlayNumber[column]]=' ';
                    return -1;
                }
                temp = NegaMax(Depth+1);
                if(column == 1)
                    chance = temp;
                if(chance < temp)
                    chance = temp;
                input[PlayNumber[column]]=' ';
            }
        }
    }
    return -chance;

}

int main()
{
    srand(time(0));
    clean();
    while(true)
    {
        input[AIManager()]='O';
        system("cls"); //Clear the screen
        Board();
        int winningtemp = winning();
        if(winningtemp!=0)
        {
            if(winningtemp == 1)
                cout<<endl<<"Player 2 WON !";
            else if (winningtemp == 2)
                cout<<endl<<"Player 1 WON ! " ; //The Computer
            else if (winningtemp == 3)
                cout<<"You Tie ! ";
            getch();  // pauses the program until keyboard input (allows user to see win condition)
            clean();
        }
        else
            PlayPosition('X');
    }
}