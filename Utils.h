#pragma once
#include <math.h>
#include <time.h>
#include <fstream>
#include <limits>
#include <string>

using namespace std;
class Utils
{
public:
    static int randint(int lower, int upper)
    { // returns a random integer between lower and upper
        return lower + rand() % (upper - lower + 1);
    }

    static double randdouble(double a, double b)
    { // retorna un random double entre a y b
        return a + (b - a) * rand() / ((double)RAND_MAX);
    }


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

    fstream& gotoLine(std::fstream& file, unsigned int num){
        file.seekg(std::ios::beg);
        for(int i=0; i < num - 1; ++i){
            file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return file;
    }

    static void getWord(ifstream& fichero, string& line)
    {
        // jaox
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
    
    static void getWordString(string & fichero, string& line)
    {
        // jaox
        line = "";
        char c = ' ';
        bool scaning = false;
        int pos=0;
        while(pos<fichero.size()) {
            c=fichero.at(pos);
            if(c != ' ' && c != '\n' && c != '\r') {
                scaning = true;
                line += c;
            } else {
                if(scaning) {
                    break;
                }
            }
            pos++;
        }
        if(pos<fichero.size())
        {
            fichero=fichero.substr(pos,fichero.size()-pos);
        }
        else
        {
            fichero="";
        }
    }
};