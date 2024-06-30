//
// Created by LanCher on 24-6-25.
//

#include "Line.h"

#include <utility>



Line::Line(int number, const vector<pair<string,Length>>& stations) {
    lineNumber = number;
    for(const auto & station : stations) {
        stationNames.emplace_back(station.first, station.second);
        stationIndexMap[station.first] = --stationNames.end();
    }
}

Line::Line(const Line& line):lineNumber(line.lineNumber),stationNames(line.stationNames) {
    //拷贝构造函数中需要重新构造stationIndexMap
    for(auto it = stationNames.begin();it!=stationNames.end();++it) {
        stationIndexMap[it->first] = it;
    }
}

Line& Line::operator=(const Line& line) {
    lineNumber = line.lineNumber;
    stationNames = line.stationNames;
    //赋值运算符中需要重新构造stationIndexMap
    stationIndexMap.clear();
    for(auto it = stationNames.begin();it!=stationNames.end();++it) {
        stationIndexMap[it->first] = it;
    }
    return *this;
}

bool Line::addStation(const string& station, const string& pos, Length frontLength, Length backLength) {
    const auto findpos = stationIndexMap.find(pos);
    if(findpos == stationIndexMap.end()) {
        return false;//没有找到pos位置
    }
    auto it = findpos->second;
    if(it==--stationNames.end())
        backLength = 0;//如果插入到最后一个站点后面，后一个站点的距离为0

    if(it==stationNames.begin()) {
        stationNames.emplace_front(station,backLength);
        stationIndexMap[station] = stationNames.begin();
    }
    else {
        --it;
        it->second=frontLength;
        stationNames.insert(++it,make_pair(station,backLength));//在pos位置插入新站点
        stationIndexMap[station] = --it;
    }
    return true;
}

bool Line::addStation_back(const string& station, Length frontLength) {
    if(!stationNames.empty()) {
        stationNames.back().second = frontLength;
    }
    stationNames.emplace_back(station,0);
    stationIndexMap[station] = --stationNames.end();
    return true;
}

bool Line::removeStation(const string& station) {
    const auto findpos = stationIndexMap.find(station);
    if(findpos == stationIndexMap.end()) {
        return false;//没有找到pos位置
    }
    auto it = findpos->second;
    if(it!=stationNames.begin()) {
        auto it2 = it;
        --it2;
        if(it!=stationNames.end()--)
            it2->second += it->second;
        else
            it2->second = 0;
    }//将这个节点的backLength加到前一个节点的frontLength上
    stationNames.erase(it);//删除位于pos位置的站点
    stationIndexMap.erase(station);//删除站点名到索引的映射
    return true;
}

void Line::extendLine(const vector<pair<string, Length>>& additionalStations,Length frontlength) {
    if(!stationNames.empty()) {
        stationNames.back().second = frontlength;
    }
    for(const auto & station : additionalStations) {
        stationNames.emplace_back(station.first,station.second);
        stationIndexMap[station.first] = --stationNames.end();
    }
}

void Line::shortenLine(const string& start, int num) {
    const auto findpos = stationIndexMap.find(start);
    if(findpos == stationIndexMap.end()) {
        return;//没有找到pos位置
    }
    auto it = findpos->second;
    for(int i=0;i<num;++i) {
        if(it!=stationNames.begin()) {
            auto it2 = it;
            --it2;
            if(it!=stationNames.end()--)
                it2->second += it->second;
            else
                it2->second = 0;
        }//将这个节点的backLength加到前一个节点的frontLength上
        stationNames.erase(it);//删除位于pos位置的站点
        stationIndexMap.erase(it->first);//删除站点名到索引的映射
        it = it==stationNames.end() ? stationNames.end() : ++it;//如果删除的是最后一个节点，it不变
    }
}




