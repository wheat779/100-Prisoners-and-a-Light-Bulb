/*
 Last updated: 12.4.14
 
 Collection of solutions to the "One Hundred Prisoners and A Light Bulb" puzzle (https://www.math.washington.edu/~morrow/336_11/papers/yisong.pdf)
 */

#include "Solutions.h"
#include <iostream>
#include <string>

int chooseStrategy();
void runStrategy(int strategyChoice);

int main(){

    
    int strategyChoice = chooseStrategy();

    runStrategy(strategyChoice);

    return 0;
}

/*
 Have the user choose which strategy function they'd like to run.
 @return the number corresponding to the strategy
 
 */
int chooseStrategy(){
    std::string choice = "NA";
    
    
    while(choice == "NA"){
    std::cout << "What solution would you like to run?" << std::endl;
    std::cout << "1: Naive Strategy" << std::endl;
    std::cout << "2: One Counter Strategy" << std::endl;
    
        std::getline(std::cin, choice);
        //If the user chose a valid strategy from the list, return value
        if(choice == "1" || choice == "Naive"){
            return 1;
        }
        if(choice == "2" || choice == "One Counter"){
            return 2;
        }
        else{ choice = "NA";} //repeat question
    }
    
    std::cout << "Error in chooseStrategy: no strategy chosen";
    return -2;
}


/*
 Run the file corresponding to the users choice
 */
void runStrategy(int strategyChoice){
    
    if(strategyChoice == 1){
        naive_strategy();
    }
    if(strategyChoice == 2){
        oneCounter_strategy();
    }
}

