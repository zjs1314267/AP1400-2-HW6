#ifndef Q3_H
#define Q3_H
#include <queue>
#include <vector>
#include <string>
#include <fstream>

namespace q3{
struct Flight
{
	std::string flight_number;
	size_t duration;
	size_t connections;
	size_t connection_times;
	size_t price;
};

class Compare {
    public :
        bool operator()(Flight a, Flight b)
        {
            size_t priorOfA = a.duration + a.connection_times + 3 * a.price;
            size_t priorOfB = b.duration + b.connection_times + 3 * b.price;
            return priorOfA > priorOfB;
        }
};


inline size_t TimeToNum(std::string time)
    {
        size_t hourPos=time.find('h');
        size_t hour= stoul(time.substr(0,hourPos));

        size_t minutePos = time.find('m');
        size_t minute = 0;
        if (minutePos != std::string::npos){
            minute = stoul(time.substr(hourPos + 1, minutePos - hourPos - 1));
        }
        return hour * 60 +  minute;
    }

inline std::priority_queue<Flight,std::vector<Flight>,Compare>gather_flights(std::string filename)
{
    std::priority_queue<Flight,std::vector<Flight>,Compare> pq;
    std::ifstream inputFile(filename);
    Flight flight{};
    std::string line;
    size_t startPos, endPos;

    while(std::getline(inputFile,line)){
        startPos=line.find(':');
        line=line.substr(startPos+1);
        endPos=line.find(' ');
        flight.flight_number=line.substr(0,endPos);

        startPos=line.find(':');
        line=line.substr(startPos+1);
        endPos=line.find(' ');
        flight.duration=TimeToNum(line.substr(0,endPos));

        startPos=line.find(':');
        line=line.substr(startPos+1);
        endPos=line.find(' ');
        flight.connections=stoul(line.substr(0,endPos));

        size_t time=0;
        startPos=line.find(':');
        line=line.substr(startPos+1);
        for (int i = 0; i < flight.connections-1; i++)
        {
            endPos = line.find(',');
            time+=TimeToNum(line.substr(0,endPos));
            line=line.substr(endPos+1);
        }
        endPos=line.find(' ');
        time+= TimeToNum(line.substr(0,endPos));
        flight.connection_times=time;

        startPos=line.find(':');
        line=line.substr(startPos+1);
        endPos=line.find(' ');
        flight.price=stoul(line.substr(0,endPos));

        pq.push(flight);
    }
    inputFile.close();
    return pq;
}
}
#endif