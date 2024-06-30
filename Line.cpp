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
    //�������캯������Ҫ���¹���stationIndexMap
    for(auto it = stationNames.begin();it!=stationNames.end();++it) {
        stationIndexMap[it->first] = it;
    }
}

Line& Line::operator=(const Line& line) {
    lineNumber = line.lineNumber;
    stationNames = line.stationNames;
    //��ֵ���������Ҫ���¹���stationIndexMap
    stationIndexMap.clear();
    for(auto it = stationNames.begin();it!=stationNames.end();++it) {
        stationIndexMap[it->first] = it;
    }
    return *this;
}

bool Line::addStation(const string& station, const string& pos, Length frontLength, Length backLength) {
    const auto findpos = stationIndexMap.find(pos);
    if(findpos == stationIndexMap.end()) {
        return false;//û���ҵ�posλ��
    }
    auto it = findpos->second;
    if(it==--stationNames.end())
        backLength = 0;//������뵽���һ��վ����棬��һ��վ��ľ���Ϊ0

    if(it==stationNames.begin()) {
        stationNames.emplace_front(station,backLength);
        stationIndexMap[station] = stationNames.begin();
    }
    else {
        --it;
        it->second=frontLength;
        stationNames.insert(++it,make_pair(station,backLength));//��posλ�ò�����վ��
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
        return false;//û���ҵ�posλ��
    }
    auto it = findpos->second;
    if(it!=stationNames.begin()) {
        auto it2 = it;
        --it2;
        if(it!=stationNames.end()--)
            it2->second += it->second;
        else
            it2->second = 0;
    }//������ڵ��backLength�ӵ�ǰһ���ڵ��frontLength��
    stationNames.erase(it);//ɾ��λ��posλ�õ�վ��
    stationIndexMap.erase(station);//ɾ��վ������������ӳ��
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
        return;//û���ҵ�posλ��
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
        }//������ڵ��backLength�ӵ�ǰһ���ڵ��frontLength��
        stationNames.erase(it);//ɾ��λ��posλ�õ�վ��
        stationIndexMap.erase(it->first);//ɾ��վ������������ӳ��
        it = it==stationNames.end() ? stationNames.end() : ++it;//���ɾ���������һ���ڵ㣬it����
    }
}




