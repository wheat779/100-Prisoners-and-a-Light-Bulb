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
#include <chrono>
#include <random>

using namespace std;

class prisoner2{
public:
    // Constructors
    prisoner2(); // empty constructor
    prisoner2(int prisonerNum); // The prisoner's corresponding day/number
    
    // Accessors
    bool hasSeenLight(int dayNum);
    bool hasSolved();
    
    // Mutators
    void addKnownDay(int dayNum);
    void checkIfSolved();
    
private:
    vector<bool> lightsSeen;
    bool solved = 0;
};

void naive_strategy(){
    
    // Initalize random generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> prisonerSelector(0,99); // generate number between 0 and 99
    
    // Initial state is the light is off
    bool light = 0;
    int day = 0;
    
    // Seed rand function
    srand(time(NULL));
    
    // Create a vector of 100 prisoners and set so each has an assigned number
    vector<prisoner2> prisonerVec;
    for(int i = 0; i < 100; i++){
        prisonerVec.push_back(prisoner2(i));
    }
    
    // Int of currently interrogated prisoner
    int currentPrisoner = 0;
    
    // While loop ends when an interrogated prisoner solves puzzle
    while(prisonerVec[currentPrisoner].hasSolved() == 0){
        day++;
        
        // select a prisoner number between 0-99
        currentPrisoner = prisonerSelector(generator);
        
        // If they see the light on, they add the previous day as a known interrogation date
        if(light == 1){
            prisonerVec[currentPrisoner].addKnownDay((day-1) % 100);
        }
        
        // If they are in the room on a date they know that the corresponding prisoner has
        // been interrogated, they flip the light on to signal the next prisoner
        if(prisonerVec[currentPrisoner].hasSeenLight(day%100)){
            light = 1;
        }
        
        // Otherwise they turn the light off
        else{
            light = 0;
        }
        
        // Check if the prisoner has solved the puzzle (seen all days), if so update status
        prisonerVec[currentPrisoner].checkIfSolved();
    }
    
    cout << "Prisoner " << currentPrisoner << " solved the puzzle after " << day << " days, or "
    << day/365.242 << " years" << endl;
    
}
//empty constructor
prisoner2::prisoner2(){
}

// Use the int argument to set the initial chosen light for that prisoner
prisoner2::prisoner2(int prisonNum){
    vector<bool> lights;
    for(int i = 0; i < 100; i++){
        lights.push_back(0);
    }
    lights[prisonNum] = 1;
    
    lightsSeen = lights;
}

// Return true if the prisoner has previously seen the light on for argument day, else false
bool prisoner2::hasSeenLight(int dayNum){
    return lightsSeen[dayNum];
}

void prisoner2::addKnownDay(int dayNum){
    lightsSeen[dayNum] = 1;
}

// Check if prisoner has seen all 100 days, if they have set private var to solved = 1
void prisoner2::checkIfSolved(){
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
bool prisoner2::hasSolved(){
    return solved;
}