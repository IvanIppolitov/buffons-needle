#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#define SIZE 100.0f

using std::cout;
using std::endl;
using std::stof;

//[a; b] - range
int randomInt(int a, int b){
    return rand()%(b - a + 1) + a;
}

//[a; b] - range
float randomFloat(float a, float b){
    float fl = ((float)rand()/(float)rand()); 
    return (float)randomInt((int)a, (int)b - 1) + (fl - (float)((int)fl));
}

//Needle
class Needle{
public:
    Needle(float _L) : L(_L){}

    void drop(){
        Ax = randomFloat(0, SIZE);
        Ay = randomFloat(0, SIZE);
        By = sin(randomFloat(0, 2 * 3.14159265358979323)) * L + Ay;
    }

    bool cross(float r) const {
        for (int y = 0; y < SIZE; y += r) if ((By <= y && Ay >= y) || (Ay <= y && By >= y)) return true;
        return false;
    }

    void info() const {
        cout << "A( " << Ax << "; " << Ay << " )" << endl;
        cout << "B( " << Bx << "; " << By << " )" << endl;
    }
    
    float L;        //Needle length 
    float Ax, Ay,   //Point A coords
          Bx, By;   //Point B coords
};
    //n.Bx = randomFloat(n.Ax - L, n.Ax + L);
    //n.By = sqrt((L * L) - (n.Bx - n.Ax)) + n.Ay;

int main(int argc, char** argv){
    if (argc != 3) return 0;

    srand(time(NULL));  
    cout.precision(17);

    float L = stof(argv[1]),
          r = stof(argv[2]);
    float crs = 0,
          count = 0;

    cout << "\e[?25l" << '\n';

    Needle needle(L);
    while (true){
        needle.drop();
        if (needle.cross(r)) crs++;
        count++;
        cout << "\e[1A" << "\e[1G";
        cout << "Crossing\t\tCount\t\t\t\tPI\n";
        cout << crs << "\t\t\t" << count << "\t\t\t" << (2 * L)/(((float)crs/(float)count) * r);
    }
    
    return 0;
}
