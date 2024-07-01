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
typedef vector<pair<int, vector<pair<int, pair<string, string>>>>> RouteResult;//·�߲�ѯ���

class GetRoute {
public:
    // vector<pair<·�߳���,vector<pair<��·����,<�ϳ�վ��,�³�վ��>>>>>
    static RouteResult InquiryShortestRoute(pair<int,string> start, pair<int,string> end, map<int,Line>& lines,set<string>& blockStations,Transfer& TS);//��ѯ���ȣ�ʱ�䣩���·��
    // vector<pair<·�߳���,vector<pair<���˴���,<�ϳ�վ��,�³�վ��>>>>>
    static RouteResult InquiryLeastTransferRoute(pair<int,string> start, pair<int,string> end, map<int,Line>& lines,set<string>& blockStations,Transfer& TS);//��ѯ���˴�������·��
};



#endif //GETROUTE_H
