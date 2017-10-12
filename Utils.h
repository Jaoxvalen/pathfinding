#pragma once
#include <math.h>
#include <time.h>
#include <fstream>

using namespace std;
class Utils
{
public:
static int initialize_randomness(int seed)
    { // initializes the seed, if seed is -1 then it uses system time as seed
        int seed1;
        time_t* tp;
        tp = NULL;
        if(seed == -1)
            seed1 = time(tp);
        else
            seed1 = seed;
        srand(seed1);
        return seed1;
    }
    
    static void getWord(ifstream& fichero, string& line)
    {
        line = "";
        char c = ' ';
        bool scaning = false;
        while((c == ' ' || c == '\n' || c == '\r') || scaning) {
            fichero.get(c);
            if(c != ' ' && c != '\n' && c != '\r') {
                scaning = true;
                line += c;
            } else {
                if(scaning) {
                    break;
                }
            }
        }
    }
};