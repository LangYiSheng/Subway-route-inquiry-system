//
// Created by LanCher on 24-6-25.
//

#include "FileIO.h"

void FileIO::SaveLine(ofstream& os, const Line& line) {
    os<<line.getLineNumber()<<endl;
    auto stations = line.getStationsWithLength();
    os<<stations.size()<<endl;
    for(const auto& station : stations) {
        os<<station.first<<" "<<station.second<<endl;
    }
}

Line FileIO::LoadLine(ifstream& is) {
    int lineNumber;
    is>>lineNumber;
    int size;
    is>>size;
    vector<pair<string,Length>> stations;
    for(int i=0;i<size;++i) {
        string station;
        Length length;
        is>>station>>length;
        stations.emplace_back(station,length);
    }
    return {lineNumber,stations};
}

bool FileIO::SaveMain(const map<int, Line>& lines) {
    ofstream file(R"(lines.txt)");
    if(!file) {
        return false;
    }
    file<<lines.size()<<endl;
    for(const auto& line : lines) {
        SaveLine(file,line.second);
    }
    return true;
}

bool FileIO::LoadMain(map<int, Line>& lines) {
    ifstream file(R"(lines.txt)");
    if(!file) {
        return false;
    }
    int size;
    file>>size;
    for(int i=0;i<size;++i) {
        Line line = LoadLine(file);
        lines[line.getLineNumber()] = line;
    }
    return true;
}

