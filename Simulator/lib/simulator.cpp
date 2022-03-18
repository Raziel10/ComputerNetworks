#include "simulator.h"
#include "ALOHA.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Simulator::Simulator(){
    cout << "running simulator constructor" << endl;
}

void Simulator::run(){
    srand(time(NULL));
    fstream outputFile;
    outputFile.open("results.txt", ios::out);
    if(!outputFile){
        cout << "Error while opening file";
        return;
    }
    outputFile << "l,T,S," << endl;
    ALOHA* aloha = NULL;
    vector<float> alohaResults;
    cout << "RUNNING SIMULATION" << endl; 

    for(float lambda = 0.1; lambda <= 5; lambda+=0.1){
        for(float T = 0.1; T <= 5; T+=0.1){
            cout << "New simulation lambda: " << lambda << " T:" << T << endl;
            aloha = new ALOHA(lambda, T);
            aloha->run();
            cout << "S: " << aloha->getResult() << ", "<< endl;
            
            outputFile << lambda << ", " << T <<  "," << aloha->getResult() << ", "<< endl;
            //alohaResults.push_back(aloha->getResult());
            cout << endl;
            delete aloha;
        }
    }

    /*for(auto& result: alohaResults){
        cout << "S: "<< result << endl;
    }*/
    outputFile.close();
}

