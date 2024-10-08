#ifndef Q2_H
#define Q2_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace q2{ 
    struct Patient{
        std::string name;
	    size_t age;
	    size_t smokes;
	    size_t area_q;
	    size_t alkhol;
    };

    std::vector<Patient> read_file(std::string filename);

    void sort(std::vector<Patient>& patients);

}
using q2::Patient;

inline std::vector<Patient> q2::read_file(std::string filename)
{
    std::ifstream inputFile(filename);
    std::vector<Patient> patients{};
        if (!inputFile.is_open()) {
            return patients;
        }
    std::string line;
    for (int i = 0; i < 2; ++i) {
        std::getline(inputFile, line);
    }
    while(std::getline(inputFile,line)){
        Patient patient;
        std::string value;
        std::istringstream stream(line);
        std::string Name;
        std::string Surname;
        std::getline(stream, Name, ',');
        std::getline(stream, Surname, ',');
        size_t end = Name.find_last_not_of(' ');
        Name.erase(end + 1);
        patient.name =Name+' '+Surname;

        std::getline(stream, value, ',');
        patient.age = std::stoul(value);

        std::getline(stream, value, ',');
        patient.smokes = std::stoul(value);

        std::getline(stream, value, ',');
        patient.area_q = std::stoul(value);

        std::getline(stream, value);
        patient.alkhol = std::stoul(value);

        patients.push_back(patient);
    }
    inputFile.close();
    return patients;
}

inline double lung(Patient p){

    return 3*p.age+5*p.smokes+2*p.area_q+4*p.alkhol;
}
    inline bool compare (const Patient &A,const Patient &B)
    {

        return lung(A)>lung(B);
    }
inline void q2::sort(std::vector<Patient>& patients)
{
    std::sort(patients.begin(),patients.end(),compare);

}
// sort
// 3*age + 5*smokes + 2*area_q + 4*alkhol
#endif //Q2_H