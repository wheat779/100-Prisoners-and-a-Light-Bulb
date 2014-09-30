/*
 9/30/14
 
 My naive solution to the "One Hundred Prisoners and A Light Bulb" puzzle (https://www.math.washington.edu/~morrow/336_11/papers/yisong.pdf)
 This solution could also easily be modified to work for the variation where all prisoners 
 must know all other prisoners have been interrogated. Unfortunately average time until 
 solution appears to be ~240 years.
 
 General principle is that the prisoners each assign themselves a unique number 1-100, and track
 interrogation days in blocks of 100. If their number happens to match up with the day 
 they are called in to be interrogated, then they flip the light switch on. Additionally,
 each prisoner also takes note of which other days they have seen the light switch turned on
 and also turn on the light switch on days they know other prisoners have been interrogated. 
 Thus toward the later days of the puzzle, each prisoner has a long list of prisoners he 
 knows has been interrogated, and uses this list to flip the light on for each of those previously
 seen days.
 
 ex. 1
 Prisoner 5 gets called in on day 5, the light switch is already off, and since his number
 matches the current day, he turns the light switch on.
 
 ex. 2
 Prisoner 65 gets called in on day 62, and sees the light switch on. Prisoner 65 now knows 
 prisoner 61 was interrogated, but turns the light switch off before leaving,
 because he does not know if prisoner 62 has been interrogated.
 
 ex 3. 
 Prisoner 21 gets called in on day 78, and the light switch is off. Prisoner 21 has previously
 come in on day 79 and seen the light switch on, so he knows prisoner 78 has been interrogated,
 so prisoner 21 turns the light switch on before leaving the room.
 
 */


#include <iostream>
#include <vector>
#include <time.h> // Time for rand() seed
#include <stdlib.h> // Use of rand()
#include <stdio.h> // Use of NULL

using namespace std;

class prisoner{
public:
    // Constructors
    prisoner(); // empty constructor
    prisoner(int prisonerNum); // The prisoner's corresponding day/number
    
    // Accessors
    bool hasSeenLight(int dayNum);
    bool hasSolved();
    
    // Mutator
    void addKnownDay(int dayNum);
    void checkIfSolved();
    
private:
    vector<bool> lightsSeen;
    bool solved = 0;
};

int main(){
    // Initial state is the light is off
    bool light = 0;
    int day = 0;
    
    // Seed rand function
    srand(time(NULL));
    
    // Create a vector of 100 prisoners and set so each has an assigned number
    vector<prisoner> prisonerVec;
    for(int i = 0; i < 100; i++){
        prisonerVec.push_back(prisoner(i));
    }
    

    // an int to keep track of the currently interrogated prisoner
    int currentPrisoner = 0;
    
    // While loop ends when an interrogated prisoner solves puzzle
    while(prisonerVec[currentPrisoner].hasSolved() == 0){
        day++;
        //cout << "day = " << day << endl;
        currentPrisoner = rand() % 100; // select a prisoner number between 1-100
        //cout << "current prisoner: " << currentPrisoner << endl;
        //cout << "light " << light << endl;
        if(light == 1){
            prisonerVec[currentPrisoner].addKnownDay((day-1) % 100);
            //cout << "prisoner adds day " << (day-1)%100 << endl;
        }
        if(prisonerVec[currentPrisoner].hasSeenLight(day%100)){
            light = 1;
            //cout << "prisoner " << currentPrisoner << " turns on the light" << endl;
        }
        else{
        light = 0;
        //cout << "prisoner " << currentPrisoner << " turns off the light" << endl;
        }
        prisonerVec[currentPrisoner].checkIfSolved();
    }
    
    cout << "Prisoner " << currentPrisoner << " solved the puzzle after " << day << " days, or "
    << day/365.242 << " years" << endl;
    
}

prisoner::prisoner(){
    //empty constructor
}

// Use the int argument to set the initial chosen light for that prisoner
prisoner::prisoner(int prisonNum){
    vector<bool> lights;
    for(int i = 0; i < 100; i++){
        lights.push_back(0);
    }
    lights[prisonNum] = 1;
    
    lightsSeen = lights;
}

// Return true if the prisoner has previously seen the light on for argument day, else false
bool prisoner::hasSeenLight(int dayNum){
    return lightsSeen[dayNum];
}

void prisoner::addKnownDay(int dayNum){
    lightsSeen[dayNum] = 1;
}

// Check if prisoner has seen all 100 days, if they have set private var to solved = 1
void prisoner::checkIfSolved(){
    for(int i = 0; i < lightsSeen.size(); i++){
        if(lightsSeen[i]){
            if(i == 99){
                solved = 1;
            }
        }
        else{
            break;
        }
    }
}

// Return whether or not the prisoner has solved the puzzle
bool prisoner::hasSolved(){
    return solved;
}