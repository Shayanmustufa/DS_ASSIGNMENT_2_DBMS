#include "random_record_generator.h"
#include <cstdlib>  
#include <ctime>    
#include <string>
#include <vector>
using namespace std;

void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        std::srand(1000);
        initialized = true;
    }
}


int generateRandomID(int lower, int upper) {
    initRandomSeed();
    return lower + rand() % (upper - lower + 1);
}

int generateRandomAGE(int lower, int upper) {
    initRandomSeed();
    return lower + rand() % (upper - lower + 1);
}
string consonants[]= {"b", "c", "d", "f", "gu", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z"};
string vowels[]= {"a", "e", "i", "o", "u"};
int size=21;
int size2=5;
 string generateRandomName(int syllableCount = 3) {
    string name = "";
    for (int i = 0; i < syllableCount; ++i) {
        name += consonants[rand() % size];
        name += vowels[rand() % size2];
    }
    name[0] = toupper(name[0]);

    return name;
}

int generateSortedNums(int till) {
    static int current = 0;
    if (current < till) {
        return ++current;
    } else {
        current = 0; 
        return -1;   
		    }
}
