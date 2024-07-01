//
// Created by LanCher on 24-7-1.
//

#ifndef GETROUTE_H
#define GETROUTE_H

#include <set>
#include <queue>
#include "Line.h"
#include "Transfer.h"
using namespace std;

typedef pair<int, string> Station;
typedef vector<pair<int, vector<pair<int, pair<string, string>>>>> RouteResult;//路线查询结果

class GetRoute {
public:
    // vector<pair<路线长度,vector<pair<线路名称,<上车站点,下车站点>>>>>
    static RouteResult InquiryShortestRoute(pair<int,string> start, pair<int,string> end, map<int,Line>& lines,set<string>& blockStations,Transfer& TS);//查询长度（时间）最短路线
    // vector<pair<路线长度,vector<pair<换乘次数,<上车站点,下车站点>>>>>
    static RouteResult InquiryLeastTransferRoute(pair<int,string> start, pair<int,string> end, map<int,Line>& lines,set<string>& blockStations,Transfer& TS);//查询换乘次数最少路线
};



#endif //GETROUTE_H
