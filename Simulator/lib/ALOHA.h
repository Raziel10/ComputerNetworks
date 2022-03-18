#include <vector>

class Event {
    float t;
    int type; //0 - Arrival, 1 - EOT - end of transmission 
public:
    Event(float t, int type);
    //operator for sorting
    bool operator<( const Event& x) const{
        return t < x.t;
    }
    float getTime();
    int getType();
};

class ArrivalGenerator{
    float lambda;
public:
    ArrivalGenerator();
    void setLambda(float lambda);
    Event generate(float simulationTime);
};

class ALOHA{
    float lambda;
    float T;
    int channel;
    int success;
    float simulationTime;
    float S;
    int arrivals;
    ArrivalGenerator arrivalGenerator;
    std::vector<Event> events;
    void generateArrival();
    void processEvent();
    float computeSuccess();

public:
    ALOHA(float lambda, float T);
    ~ALOHA();
    void run();    
    float getResult();
};