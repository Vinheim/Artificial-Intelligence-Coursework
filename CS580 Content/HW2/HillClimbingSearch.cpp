#include<iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

double eggholderFunction(double x, double y){
    if( (x < 10000 && x > -10000) && (y < 10000 && y > -10000) )
        return ( (-1 * (y + 47)) * sin(sqrt(abs( (x/2) + (y + 47) ))) - (x * sin(sqrt(abs( (x - (y + 47)) ))) ) );
    else if(x < 10000 && x > -10000)
        cout << "\n\n Y is out of bounds\n\n";
    else
        cout << "\n\n X is out of bounds\n\n";
}

int main(){

    uniform_real_distribution<double> xy(-9999.5, 9999.5);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);

    uniform_real_distribution<double> distribution (0.0,1.0);

    double offset = (distribution(generator) - 0.5);
    double x = xy(generator), y = xy(generator);
    double f = eggholderFunction(x, y);
    double testF = 0, testX = 0, testY = 0;

    int notLowerFound = 0, lowestFound = 0;

    ofstream out("Assign-2_Hill-Climbing-Search_Results.txt");

    while(lowestFound < 100){
        x = xy(generator);
        y = xy(generator);
        while(notLowerFound < 100){

            f = eggholderFunction(x, y);

            offset = (distribution(generator) - 0.5);
            testX += offset;
            offset = (distribution(generator) - 0.5);
            testY += offset;

            testF = eggholderFunction(x, y);

            if(testF < f){
                y = testY;
                x = testX;
                notLowerFound = 0;
            }
            else
                notLowerFound++;
        }
        lowestFound++;
        out << "\n\nX : " << x << "\nY : " << y;
        out << "\nf(x, y) = " << eggholderFunction(x, y);
    }


    return 0;
}
