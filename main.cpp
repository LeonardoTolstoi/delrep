#include "delrep.h"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc == 1) std::cout << "You have to specify the folder!\n";
    else if(argc > 2) std::cout << "The command takes only one argument!\n";
    else delrep(argv[1]);
    return 0;
}
