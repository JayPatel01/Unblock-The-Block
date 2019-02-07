/* 
 *
 * Author  : Jay Patel
 * System  : Qt Creator
 *
 * This program takes the input from the user to move the cars on the board,
 * And after smart user moves, it allows the user to win with the red car reaching to its destination.
 *
 */

#include <iostream>
#include<fstream>   //reading from the file
#include<cctype>
#include<cstring>
#include "gobjects.h"  // for all graphics objects
using namespace std;

//All the functions Declarations.

int lowerEdgeError(int);
int upperEdgeError(int);
int ThreeBoxError(int);
void displayIDInfo();
void displayInstructions();

//----------------------------------------------------------

//----------------------------------------------------------
//Function to Display the Author Information.
void displayIDInfo()
{
    cout<<"Author  : Jay Patel \n";
    cout<<"System  : Qt Creator\n ";
    cout<<endl;
}//end displayIDInfo()
//------------------------------------------------------------

//------------------------------------------------------------
//function to Display the Introduction.
void displayInstructions()
{
    cout << "Welcome to The Graphical Version of The Game Unblock the Block. " << endl
         << "                                                        " << endl
         << "Move the vehicles so that the Red car can exit          " << endl
         << "the board to the right. Each move should be of the      " << endl
         << "of the form:   CDN   where:                             " << endl
         << "   C  is the vehicle to be moved                        " << endl
         << "   D  is the direction (u=up, d=down, l=left or r=right)" << endl
         << "   N  is the number of squares to move it               " << endl
         << "For example GR2  means move the G vehicle to the right  " << endl
         << "2 squares.  Lower-case input such as   gr2  is also     " << endl
         << "accepted.  Enter 'reset' to reset board, or 'exit' to exit form the game.  " << endl;
}//end displayInstructions()
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//Function to check the error wether car(length 2) is moving out from the lower edge of the Board or not.
int lowerEdgeError(int error)
{
    if(error==190)
    {
        cout<<"Attempt is made to move a piece off the edge of the board.  Please retry."<<endl;
        return 1;
    }
    else {return 2;}
 }//end of the function.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//Function to check the error wether the car(length 2) is moving out from the upper edge of the Board or not.
int upperEdgeError(int error)
{
    if(error==30)
    {
        cout<<"Attempt is made to move a piece off the edge of the board.  Please retry."<<endl;
        return 1;
    }
    else {return 2;}
}//end of function.
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Function to check the error wether the car(length 3)is moving out from the lower edge of the Board or not.
int ThreeBoxError(int error)
{
    if(error==150)
    {
        cout<<"Attempt is made to move a piece off the edge of the board.  Please retry."<<endl;
        return 1;
    }
    else {return 2;}
}//end of Function.
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
//Main function starts here..
int main()
{
    //All the Veriable declarations.
    string userInput;
    int i,j,x,y,rValue,Value,Value1,Value2,Value3,
        Value4,Value5,Value6,Value7,Value8,Value9,
        Value10,Value11,Value12,Value13,Value14;
    bool win=false;
    ifstream inputFileStream;

    //Initialization so we don't get garbage values.
    char carColor[8]     = {' ',' ',' ',' ',' ',' ',' ',' '};
    char carDirection[8] = {' ',' ',' ',' ',' ',' ',' ',' '};
    int xCoordinate[8]   = {0,0,0,0,0,0,0,0};
    int yCoordinate[8]   = {0,0,0,0,0,0,0,0};
    int carLength[8]     = {0,0,0,0,0,0,0,0};
    string color[8]      = {"ABCDEFGH"};

    int actualCarX[8] = {0,0,0,0,0,0,0,0};
    int actualCarY[8] = {0,0,0,0,0,0,0,0};
    int carSize[8]    = {0,0,0,0,0,0,0,0};

    int numberOfCars = 0;

    displayIDInfo();
    displayInstructions();

    //Openning the FIle name board.txt.
    inputFileStream.open("board.txt");
    if(!inputFileStream.is_open())
         {
             cout<<"the file could not be found..."<<endl;
             return 0;
         }

     inputFileStream >> numberOfCars;

      int constant = 30;
      int tempVar1[8] = {0,0,0,0,0,0,0,0};
      int tempVar2[8] = {0,0,0,0,0,0,0,0};
      //Using the for loop to read the file each time.
      for( int i=0; i<numberOfCars; i++)
          {
             inputFileStream >> carColor[i]    >> carDirection[i]
                             >> xCoordinate[i] >> yCoordinate[i]
                             >> carLength[i];
             //Swith function to assign appropriate colors of the car.
             switch(carColor[i])
             {
                case 'G': color[i]="GREEN  "; break;
                case 'Y': color[i]="YELLOW "; break;
                case 'M': color[i]="MAGENTA"; break;
                case 'R': color[i]="RED    "; break;
                case 'B': color[i]="BLUE   "; break;
                case 'O': color[i]="ORANGE "; break;
                case 'C': color[i]="CYAN   "; break;
                case 'P': color[i]="PINK   "; break;
              }
                //Logic behind converting the File date into ectual representation of the board.
                 actualCarX[i]= 30+40*(yCoordinate[i]-1);
                 actualCarY[i]= 30+40*(xCoordinate[i]-1);
                 carSize[i]   = 30+40*(carLength[i]-1);
                 //reading the Verical and Horizaontal orientations of the cars from the file.
                 if(carDirection[i] == 'H')
                 {
                    tempVar1[i] = carSize[i];
                    tempVar2[i] = constant;
                 }
                 else if(carDirection[i] == 'V')
                 {
                     tempVar1[i] = constant;
                     tempVar2[i] = carSize[i];
                 }
            }

            inputFileStream.close();  // Closeing the file.

    // Createing a graphics window, which will be used to draw graphical shapes
    GWindow graphicsWindow(300, 300);   // Set the size
    graphicsWindow.setWindowTitle("CS 141 Program 4 by jpate225 and spath3 ");

    //Border Outline
    GRect *rectangle1 = new GRect(10, 10, 270, 270);
    rectangle1->setFilled(true);
    rectangle1->setColor("DARKGRAY");
    // Add it to the graphics window.  Without this it will exist, but will not show up.
    graphicsWindow.add(rectangle1);

    //Inner playing board
    GRect *rectangle2 = new GRect(20, 20, 250, 250);
    rectangle2->setFilled(true);
    rectangle2->setColor("GRAY");
    // Add it to the graphics window.  Without this it will exist, but will not show up.
    graphicsWindow.add(rectangle2);

    //Exit openning
    GRect *rectangle3 = new GRect(270, 100, 10, 50);
    rectangle3->setFilled(true);
    rectangle3->setColor("LIGHTGRAY");
    // Add it to the graphics window.  Without this it will exist, but will not show up.
    graphicsWindow.add(rectangle3);

    //Horizontal lines of rectangles.
    x=20;
    for( i=0;i<7;i++)
    {

        GRect *Horizontal = new GRect(x, 20, 10, 250);
        Horizontal->setFilled(true);
        Horizontal->setColor("LIGHTGRAY");
        // Add it to the graphics window.  Without this it will exist, but will not show up.
        graphicsWindow.add(Horizontal);
        x=x+40;
    }
    //Verticle lines of rectangles.
    y=20;
    for( j=0;j<7;j++)
    {
        GRect *Verticle = new GRect(20, y, 250, 10);
        Verticle->setFilled(true);
        Verticle->setColor("LIGHTGRAY");
        // Add it to the graphics window.  Without this it will exist, but will not show up.
        graphicsWindow.add(Verticle);
        y=y+40;
    }

    //the code below takes the data from the file and generates the Cars according to it.

    //Green Car
    GRect *greenCar = new GRect(actualCarX[0], actualCarY[0],  tempVar1[0], tempVar2[0]);
    greenCar->setFilled(true);
    greenCar->setColor(color[0]);
    graphicsWindow.add(greenCar);

    //Yellow Car
    GRect *yellowCar  = new GRect(actualCarX[1], actualCarY[1], tempVar1[1], tempVar2[1]);
    yellowCar->setFilled(true);
    yellowCar->setColor(color[1]);
    graphicsWindow.add(yellowCar);

    //Magenta Car
    GRect *magentaCar  = new GRect(actualCarX[2], actualCarY[2], tempVar1[2], tempVar2[2]);
    magentaCar->setFilled(true);
    magentaCar->setColor(color[2]);
    graphicsWindow.add(magentaCar);

    //Red Car
    GRect *redCar = new GRect(actualCarX[3], actualCarY[3],  tempVar1[3], tempVar2[3]);
    redCar->setFilled(true);
    redCar->setColor(color[3]);
    graphicsWindow.add(redCar);

    //Blue Car
    GRect *blueCar  = new GRect(actualCarX[4], actualCarY[4], tempVar1[4], tempVar2[4]);
    blueCar->setFilled(true);
    blueCar->setColor(color[4]);
    graphicsWindow.add(blueCar);

    //Orange Car
    GRect *orangeCar  = new GRect(actualCarX[5], actualCarY[5], tempVar1[5], tempVar2[5]);
    orangeCar->setFilled(true);
    orangeCar->setColor(color[5]);
    graphicsWindow.add(orangeCar);

    //Cyan car
    GRect *cyanCar = new GRect(actualCarX[6], actualCarY[6],  tempVar1[6], tempVar2[6]);
    cyanCar->setFilled(true);
    cyanCar->setColor(color[6]);
    graphicsWindow.add(cyanCar);

    //Pink Car
    GRect *pinkCar = new GRect(actualCarX[7], actualCarY[7],  tempVar1[7], tempVar2[7]);
    pinkCar->setFilled(true);
    pinkCar->setColor(color[7]);
    graphicsWindow.add(pinkCar);

    int counter=1;//To count the number of moves.
    //Begining of the do while loop.
    do{
        cout<<counter++<<". Your Move -> ";
        cin>>userInput;

        if(userInput=="EXIT" || userInput=="exit")
        {
            break;
        }

        if(userInput=="RESET" || userInput=="reset")
        {
            //To clear the graphic window.
            graphicsWindow.remove(redCar);
            graphicsWindow.remove(greenCar);
            graphicsWindow.remove(blueCar);
            graphicsWindow.remove(cyanCar);
            graphicsWindow.remove(yellowCar);
            graphicsWindow.remove(pinkCar);
            graphicsWindow.remove(magentaCar);
            graphicsWindow.remove(orangeCar);

            continue;

        }

        userInput.at(0)=tolower(userInput.at(0));
        userInput.at(1)=tolower(userInput.at(1));

        //Checking all the possible inputs from user with the,
        //initials of car color, directions , and number of moves to make.
        if(userInput.at(0)=='g')
            {
                if(userInput.at(1)=='r')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect = retrect+1;
                        Value7=lowerEdgeError(greenCar->getX());//error check
                        if(Value7==1)
                        {
                            for(int i=retrect-1;i>0;i--)//loop keeps the car on same place if invalid input is given.
                            {greenCar->move(-40,0);}
                            break;}
                        if(Value7!=1)
                        {greenCar->move(40,0);}//moves the car to the right.
                    }
                }
                else if(userInput.at(1)=='l')
                {
                    int retrect1 =0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1 =retrect1+1;
                        Value8=upperEdgeError(greenCar->getX());
                        if(Value8==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {greenCar->move(40,0);}
                            break;}
                        if(Value8!=1)
                        {greenCar->move(-40,0);}//moves the car to the left.
                    }
                }
                else if(userInput.at(1)!='r' || userInput.at(1)!='l')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }
         else if(userInput.at(0)=='r')
            {
                if(userInput.at(1)=='r')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect=retrect+1;
                        Value9=lowerEdgeError(redCar->getX());
                        if(Value9==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {redCar->move(-40,0);}
                            break;}
                        if(Value9!=1)
                        {redCar->move(40,0);}
                    }
                }
                else if(userInput.at(1)=='l')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value10=upperEdgeError(redCar->getX());
                        if(Value10==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {redCar->move(40,0);}
                            break;}
                        if(Value10!=1)
                        {redCar->move(-40,0);}
                    }
                }
                else if(userInput.at(1)!='r' || userInput.at(1)!='l')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }

          else if(userInput.at(0)=='c')
            {
                if(userInput.at(1)=='r')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect=retrect+1;
                        Value11=lowerEdgeError(cyanCar->getX());
                        if(Value11==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {cyanCar->move(-40,0);}
                            break;}
                        if(Value11!=1)
                        {cyanCar->move(40,0);}
                    }
                }
                else if(userInput.at(1)=='l')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value12=upperEdgeError(cyanCar->getX());
                        if(Value12==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {cyanCar->move(40,0);}
                            break;}
                        if(Value12!=1)
                        {cyanCar->move(-40,0);}
                    }
                }
                else if(userInput.at(1)!='r' || userInput.at(1)!='l')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }

          else if(userInput.at(0)=='p')
            {
                if(userInput.at(1)=='r')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect=retrect+1;
                        Value13=ThreeBoxError(pinkCar->getX());
                        if(Value13==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {pinkCar->move(-40,0);}
                            break;}
                        if(Value13!=1)
                        {pinkCar->move(40,0);}
                    }
                }
                else if(userInput.at(1)=='l')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value14=upperEdgeError(pinkCar->getX());
                        if(Value14==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {pinkCar->move(40,0);}
                            break;}
                        if(Value14!=1)
                        {pinkCar->move(-40,0);}
                    }
                }
                else if(userInput.at(1)!='r' || userInput.at(1)!='l')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }

            //Verticle car userInput checking.

          else if(userInput.at(0)=='y')
            {
                if(userInput.at(1)=='d')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect=retrect+1;
                        Value3= ThreeBoxError(yellowCar->getY());
                        if(Value3==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {yellowCar->move(0,-40);}
                            break;}
                        if(Value3!=1)
                        {yellowCar->move(0,40);}
                    }
                }
                else if(userInput.at(1)=='u')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value4=upperEdgeError(yellowCar->getY());
                        if(Value4==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {yellowCar->move(0,40);}
                            break;}
                        if(Value4!=1)
                        {yellowCar->move(0,-40);}
                    }
                }
                else if(userInput.at(1)!='d' || userInput.at(1)!='u')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }

          else if(userInput.at(0)=='m')
            {
            int retrect=0;
                if(userInput.at(1)=='d')
                {
                    retrect=retrect+1;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        Value1= ThreeBoxError(magentaCar->getY());
                        if(Value1==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {magentaCar->move(0,-40);}
                            break;}
                        if(Value1!=1)
                        {magentaCar->move(0,40);}
                    }
                }
                else if(userInput.at(1)=='u')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value2=upperEdgeError(magentaCar->getY());
                        if(Value2==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {magentaCar->move(0,40);}
                            break;}
                        if(Value2!=1)
                        {magentaCar->move(0,-40);}
                    }
                }
                else if(userInput.at(1)!='d' || userInput.at(1)!='u')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }

          else if(userInput.at(0)=='b')
            {
                if(userInput.at(1)=='d')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect=retrect+1;
                        Value5= ThreeBoxError(blueCar->getY());
                        if(Value5==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {blueCar->move(0,-40);}
                            break;}
                        if(Value5!=1)
                        {blueCar->move(0,40);}
                    }
                }
                else if(userInput.at(1)=='u')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value6=upperEdgeError(blueCar->getY());
                        if(Value6==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {blueCar->move(0,40);}
                            break;}
                        if(Value6!=1)
                        {blueCar->move(0,-40);}
                    }
                }
                else if(userInput.at(1)!='d' || userInput.at(1)!='u')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }

          else if(userInput.at(0)=='o')
            {
                if(userInput.at(1)=='d')
                {
                    int retrect=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect=retrect+1;
                        rValue=lowerEdgeError(orangeCar->getY());
                        if(rValue==1)
                        {
                            for(int i=retrect-1;i>0;i--)
                            {orangeCar->move(0,-40);}
                            break;}
                        if(rValue!=1)
                        {orangeCar->move(0,40);}

                    }
                }
                else if(userInput.at(1)=='u')
                {
                    int retrect1=0;
                    for(int a=1;a<=userInput.at(2)-'0';a++)
                    {
                        retrect1=retrect1+1;
                        Value=upperEdgeError(orangeCar->getY());
                        if(Value==1)
                        {
                            for(int i=retrect1-1;i>0;i--)
                            {orangeCar->move(0,40);}
                            break;}
                        if(Value!=1)
                        {orangeCar->move(0,-40);}
                    }
                }
                else if(userInput.at(1)!='d' || userInput.at(1)!='u')
                {
                    cout<<"Attempt was made to move a piece in the wrong direction.  Please retry."<<endl;
                }
            }
        else
        {
            cout<<"User input is not one of the valid color or action items.  Please retry."<<endl;
            continue;
        }

    }while(redCar->getX()!=190);//Checking the winning condition.
    //Do..While loop ends here.

    if( userInput=="exit" || userInput=="EXIT")
    {
        win=false;
       // exit the program
    }
    else
    {
        win=true;
        if(win==true)//to print out the message on the board when User Wins.
        {
            GLabel *message = new GLabel(" YOU WON ", 100,150);
            // Add it to the graphics window.   Without this it will exist, but will not show up.
            graphicsWindow.add(message);

            cout<<"Congratulations you won....Exiting... in 7 Seconds."<<endl;
            pause(7000);
        }
    }


    // Closeing the windows, first the graphics window, then the console window.
    graphicsWindow.requestFocus();
    graphicsWindow.close();
    exitGraphics();

    return 0;
}//The main function as well as the program ends here.
//----------------------------------------------------------------------------------------------------
//                                                THE END
//----------------------------------------------------------------------------------------------------

