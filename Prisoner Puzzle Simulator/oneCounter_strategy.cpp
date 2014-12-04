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

using namespace std;

void oneCounter_strategy(){
    
    // Bool tracking whether the light is on or off. Initial state is off.
    bool light = 0;
    /* Vector containing whether or not the correspondingly
     numbered prisoner had previously flipped the light switch
     if 1, then that prisoner has visited the interrogation
     room and flipped the light switch
     */
    vector<bool> prisoners;
    // Int tracking how many days have elasped since interrogations have started
    int day = 0;
    // The counter's current number of time's flipping the light switch off. At 99
    // He knows all prisoners have been interogated.
    int prisonerCount = 0;
    
    // Initalize random generator
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> prisonerSelector(0,99); // generate number between 0 and 99
    
    // Add prisoners to our vector. 0 indicates they haven't flipped the light switch yet
    for(int i = 0; i < 99; i++){
        prisoners.push_back(0);
    }
    // Number of current prisoner being interrogated
    int currentPrisoner = 0;
    
    while(prisonerCount < 99){
        day++;
        currentPrisoner = prisonerSelector(generator);
        // If the light is off, and the current prisoner hasn't turned it on before,
        // they flip it on, and remember they have done so
        if(light == 0 && prisoners[currentPrisoner] == 0){
            prisoners[currentPrisoner] = 1;
            light = 1;
        }
        // If prisoner 0, our counter, is interrogated and the light is on
        // he increments his count and then switches the light off
        if(currentPrisoner == 0 && light == 1){
            prisonerCount++;
            light = 0;
        }
    }
    
    cout << "The counter solved the puzzle after " << day << " days, or "
    << day/365.242 << " years" << endl;
}