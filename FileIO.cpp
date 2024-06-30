//
// Created by LanCher on 24-6-25.
//

#include "FileIO.h"

void FileIO::SaveSetting(ofstream& os, const vector<bool>& settings) {
    for(const auto& setting : settings) {
        os<<setting<<endl;
    }
}

void FileIO::SaveLine(ofstream& os, const Line& line) {
    os<<line.getLineNumber()<<endl;
    auto stations = line.getStationsWithLength();
    os<<stations.size()<<endl;
    for(const auto& station : stations) {
        os<<station.first<<" "<<station.second<<endl;
    }
}

void FileIO::SaveBlockedStations(ofstream& os, const set<string>& blocked_stations) {
    os<<blocked_stations.size()<<endl;
    for(const auto& station : blocked_stations) {
        os<<station<<endl;
    }
}

vector<bool> FileIO::LoadSetting(ifstream& is) {
    vector<bool> settings(SETTING_NUM);
    for(int i=0;i<SETTING_NUM;++i) {
        bool setting;
        is>>setting;
        settings[i]=setting;
    }
    return settings;
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

set<string> FileIO::LoadBlockedStations(ifstream& is) {
    int size;
    is>>size;
    set<string> blocked_stations;
    for(int i=0;i<size;++i) {
        string station;
        is>>station;
        blocked_stations.insert(station);
    }
    return blocked_stations;
}

bool FileIO::GETSET0() {
    ifstream file(R"(lines.txt)");
    if(!file) {
        return false;
    }
    bool ans;
    file>>ans;
    return ans;
}

bool FileIO::SaveMain(const map<int, Line>& lines,const set<string>& blocked_stations,const vector<bool>& settings) {
    ofstream file(R"(lines.txt)");
    if(!file) {
        return false;
    }
    SaveSetting(file,settings);
    file<<lines.size()<<endl;
    for(const auto& line : lines) {
        SaveLine(file,line.second);
    }
    SaveBlockedStations(file,blocked_stations);
    return true;
}

bool FileIO::LoadMain(map<int, Line>& lines,set<string>& blocked_stations,vector<bool>& settings) {
    ifstream file(R"(lines.txt)");
    if(!file) {
        return false;
    }
    settings = LoadSetting(file);
    lines.clear();//清空原有数据
    int size;
    file>>size;
    for(int i=0;i<size;++i) {
        Line line = LoadLine(file);
        lines[line.getLineNumber()] = line;
    }
    blocked_stations = LoadBlockedStations(file);
    return true;
}

