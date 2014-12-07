/*
 12.4.14
 
 One counter solution included in the Song paper. Each prisoner turns the light switch on
 exactly one time (if they find it currently off) and a single prisoner is designated to
 turn off the light each time he finds it on. When the counter has turned the light off 
 99 times, he knows each of the other prisoners has visited at least once.
 
 code still needs to be functionalized and to utilize classes. 
 
 */

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

class prisoner{
public:
    //Constructors
    prisoner();
    
    //Accessors
    bool hasFlipped();
    
    //Mutator
    void setFlippedTrue();
    
private:
    bool flipped = 0;
    bool isCounter = 0;
};

class counter{
public:
    //constructor
    counter();
    
    //Mutator
    void increaseCount();
    void checkIfSolved();
    
    //Accessor
    int getCount();
    bool solvedPuzzle();
    
private:
    int count = 0;
    bool solved = 0;
    bool isCounter = 1;
    
};

std::vector<prisoner> makePrisonerVector();

void oneCounter_strategy(){
    
    // Initalize random generator to select prisoner for interrogation
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> prisonerSelector(0,99); // generate number between 0 and 99
    
    bool light = 0; // Bool tracking whether the light is on or off.
    int day = 0; // Int tracking how many days have elasped since interrogations have started
    int currentPrisoner = 0; // Int to track the currently interrogated prisoner
    
    // Create ector containing 99 prisoners (excluding the counter)
    std::vector<prisoner> prisoners = makePrisonerVector();
    
    // Create a prisoner who will be the counter
    counter counterPrisoner;
    
    /*
     Main loop starts a new day by selecting a random prisoner. 
     If that prisoner is the counter (prisoner 0) they check if the light bulb is on, if it is
     they increase their count and flip the light back off. When they've flipped it off 99 times,
     they know all prisoners have visited.
     
     If the random prisoner isn't the counter , they merely enter and flip the 
     light on if they have never done so before, and the light is currently off.
     */
    while(counterPrisoner.solvedPuzzle() == false){
        day++;
        currentPrisoner = prisonerSelector(generator);

        if(currentPrisoner == 0 && light == 1){
            counterPrisoner.increaseCount();
            light = 0;
            counterPrisoner.checkIfSolved();
        }
        
        else if(light == 0 && prisoners[currentPrisoner].hasFlipped() == 0){
            prisoners[currentPrisoner].setFlippedTrue();
            light = 1;
        }
    }
    //Output days it took puzzle to be solved puzzle is solved
    std::cout << "The counter solved the puzzle after " << day << " days, or "
    << day/365.242 << " years" << std::endl;
}

// Empty constructor
prisoner::prisoner(){}

// Accessor for whether a prisoner has flipped the lightswitch
bool prisoner::hasFlipped(){
    return flipped;
}

void prisoner::setFlippedTrue(){
    flipped = true;
}

//Empty constructor
counter::counter(){};

//Increase the current count of times the lightswitch has been flipped off
void counter::increaseCount(){
    count++;
}

int counter::getCount(){
    return count;
}

bool counter::solvedPuzzle(){
    return solved;
}

void counter::checkIfSolved(){
    if(count == 99){
        solved = 1;
    }
}

// Create a vector of 100 prisoners, but assign prisoner 0 (the counter) as having flipped
// the switch already
std::vector<prisoner> makePrisonerVector(){
    
    int numberOfPrisoners = 100;
    std::vector<prisoner> prisonerVec;
    
    for(int i = 0; i < numberOfPrisoners; i++){
        prisonerVec.push_back(prisoner());
    }
    
    prisonerVec[0].setFlippedTrue();
    
    if(prisonerVec.size() != 100){
        std::cout << "prisonerVec incorrect size: " << prisonerVec.size();
    }
    return prisonerVec;
}