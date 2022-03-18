#include "ALOHA.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>

#define EVT_TYPE_ARRIVAL 0
#define EVT_TYPE_EOT 1

using namespace std;

ALOHA::ALOHA(float lambda, float T){
    this->lambda =  lambda;
    this->T = T;
    
    channel = 0;
    success = 0;
    S = 0;
    simulationTime = 0;
    arrivals = 0;
    arrivalGenerator.setLambda(lambda);
}

ALOHA::~ALOHA(){
    //cout << "destructor" << endl;
    events.clear();
}

void ALOHA::run(){
    //cout<< "starting ALOHA protocol simulation" << endl; 
    while(arrivals < 2000){
        generateArrival();
        processEvent();
    }
    computeSuccess();
}

float ALOHA::getResult(){
    return S;
}

void ALOHA::generateArrival(){
    //cout << "generating arrival #" << arrivals << endl;
    Event arrival = arrivalGenerator.generate(simulationTime);
    //cout << "arrival push back" << endl;
    events.push_back(arrival);
    //cout << "sort" << endl;
    sort(events.begin(), events.end());
    arrivals++;
}

void ALOHA::processEvent(){
    //take earliest event
    Event e = events[0];
    
    //cout << "Processing event: " << e.getType() << " at t: " << e.getTime() << endl;  

    simulationTime = e.getTime();

    if(e.getType() == EVT_TYPE_ARRIVAL){
        channel++;
        Event endOfTransmision (simulationTime + T, EVT_TYPE_EOT);
        events.push_back(endOfTransmision);
        sort(events.begin(), events.end());
    }
    else if (e.getType() == EVT_TYPE_EOT){
        if (channel == 1){
            success++;
        }
        else{
            //cout << "COLLITION detected" << endl;
        }
        channel--;
    }

    events.erase(events.begin());
}

float ALOHA::computeSuccess(){
    cout << "success:" << success << "Period: " << T << "simulartionTime:" << simulationTime;
    if(simulationTime){
        S = ((float)success * (float)T) / (float)simulationTime;
    }
    return S;
}

////////// Arrival Generator //////////////////
ArrivalGenerator::ArrivalGenerator(){
}

Event ArrivalGenerator::generate(float simulationTime){
    
    int r = (rand() % (1000000));
    float u = ((float) r) / (float)1000000; 
    //cout << "u: " << u <<endl;
    float t = -(1 / this->lambda) * log(1 - u);
    //cout << "time of new Arrival: " << simulationTime + t <<endl;
    Event arr(simulationTime + t, EVT_TYPE_ARRIVAL);
    return arr;
}

void ArrivalGenerator::setLambda(float lambda){
    this->lambda = lambda;
}
////////// Event model ///////////////////

Event::Event(float t, int type){
    this->t = t;
    this->type = type;
}

float Event::getTime(){
    return t;
}
int Event::getType(){
    return type;
}