#include <iostream>

using namespace std;

class Assigner {
    public:
        int defLOC();
        char defComment();
        int defNumberInComment();
};

char Assigner::defComment(string comment){
    if(comment.length() < 2 || comment[2] != '.')
        return 'c';

    switch(comment[3]){
        case 'i':
            return 'i';
            break;
        case 'b':
            return 'b';
            break;
        case 'd':
            return 'd';
        case 'm':
            return 'm';
    }
    
    return 'c';
}