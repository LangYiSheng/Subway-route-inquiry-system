//
// Created by LanCher on 24-7-1.
//

#include "GetRoute.h"

#include <algorithm>


/*typedef pair<int, string> Station;
typedef vector<pair<int, vector<pair<int, pair<string, string>>>>> RouteResult;//·�߲�ѯ���*/

RouteResult GetRoute::InquiryShortestRoute(pair<int, string> start, pair<int, string> end, map<int, Line>&lines, set<string>&blockStations, Transfer&TS) {
    RouteResult result;//���
    map<Station, int> distance;//����վ�㵽���ľ���
    map<Station, Station> prev;//����վ���ǰ��
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq;//���ȶ���
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq_ans;//ǰ������
    pq.emplace(0,start);//������
    distance[start] = 0;//��㵽���ľ���Ϊ0
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();//ȡ������
        if(top.second==end) {
            while(!pq_ans.empty()) {
                prev[end]=pq_ans.top().second;
                distance[end]=pq_ans.top().first;
                pq_ans.pop();
                Station now = end;
                vector<pair<int,pair<string,string>>> route;
                route.emplace_back(now.first,make_pair(now.second,now.second));
                while(now!=start) {
                    if(route.back().first!=prev[now].first) {
                        route.back().second.first = now.second;
                        route.emplace_back(prev[now].first,make_pair(prev[now].second,prev[now].second));
                    }
                    else {
                        route.back().second.first = now.second;
                    }
                    now = prev[now];
                }
                route.back().second.first = start.second;
                reverse(route.begin(),route.end());
                //����Ƿ�����ظ�·��
                bool flag = false;
                for(const auto& r : result) {
                    if(r.second==route) {
                        flag = true;
                        break;
                    }
                }
                if(!flag) {
                    result.emplace_back(distance[end],route);
                }
            }
            break;
        }
        if(distance[top.second]<top.first) {
            continue;//�Ѿ��и��̵�·��
        }
        if(TS.hasTransfer(top.second)) {
            for(const auto& transfer : TS.getTransfers(top.second)) {
                if(blockStations.find(transfer.first.second)!=blockStations.end()) {
                    continue;//��վ���Ƿ��վ��
                }
                if(transfer.first==end) {
                    pq_ans.emplace(distance[top.second]+transfer.second,top.second);
                }
                if(distance.find(transfer.first)==distance.end()||distance[transfer.first]>distance[top.second]+transfer.second) {
                    distance[transfer.first] = distance[top.second]+transfer.second;
                    prev[transfer.first] = top.second;
                    pq.emplace(distance[transfer.first],transfer.first);
                }
            }//�������л�����Ϣ
        }
        if(lines.at(top.second.first).hasStation(top.second.second)) {
            auto station = lines.at(top.second.first).getStationIndex(top.second.second);
            if(!lines.at(top.second.first).isFirstStation(station)) {
                auto frontStation = station;
                --frontStation;
                if(blockStations.find(frontStation->first)==blockStations.end()) {
                    Station now = {top.second.first,frontStation->first};
                    if(now==end) {
                        pq_ans.emplace(distance[top.second]+frontStation->second,top.second);
                    }
                    if(distance.find(now)==distance.end()||
                        distance[now]>distance[top.second]+frontStation->second) {
                        distance[now] = distance[top.second]+frontStation->second;
                        prev[now] = top.second;
                        pq.emplace(distance[now],now);
                        }
                }
            }
            if(!lines.at(top.second.first).isLastStation(station)) {
                auto backStation = station;
                ++backStation;
                if(blockStations.find(backStation->first)==blockStations.end()) {
                    Station now = {top.second.first,backStation->first};
                    if(now==end) {
                        pq_ans.emplace(distance[top.second]+station->second,top.second);
                    }
                    if(distance.find(now)==distance.end()||
                        distance[now]>distance[top.second]+station->second) {
                        distance[now] = distance[top.second]+station->second;
                        prev[now] = top.second;
                        pq.emplace(distance[now],now);
                    }
                }
            }
        }//��������ֱ����Ϣ
    }
    return result;
}

RouteResult GetRoute::InquiryLeastTransferRoute(pair<int, string> start, pair<int, string> end, map<int, Line>&lines, set<string>&blockStations, Transfer&TS) {
    RouteResult result;//���
    map<Station, int> NumberOfTransfers;//����վ�㵽���Ļ��˴���
    map<Station, Station> prev;//����վ���ǰ��
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq;//���ȶ���
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq_ans;//ǰ������
    pq.emplace(0,start);//������
    NumberOfTransfers[start] = 0;//��㵽���Ļ��˴���Ϊ0
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();//ȡ������
        if(top.second==end) {
            while(!pq_ans.empty()) {
                prev[end]=pq_ans.top().second;
                NumberOfTransfers[end]=pq_ans.top().first;
                pq_ans.pop();
                Station now = end;
                vector<pair<int,pair<string,string>>> route;
                route.emplace_back(now.first,make_pair(now.second,now.second));
                while(now!=start) {
                    if(route.back().first!=prev[now].first) {
                        route.back().second.first = now.second;
                        route.emplace_back(prev[now].first,make_pair(prev[now].second,prev[now].second));
                    }
                    else {
                        route.back().second.first = now.second;
                    }
                    now = prev[now];
                }
                route.back().second.first = start.second;
                reverse(route.begin(),route.end());
                //����Ƿ�����ظ�·��
                bool flag = false;
                for(const auto& r : result) {
                    if(r.second==route) {
                        flag = true;
                        break;
                    }
                }
                if(!flag) {
                    result.emplace_back(NumberOfTransfers[end],route);
                }
            }
            break;
        }
        if(NumberOfTransfers[top.second]<top.first) {
            continue;//�Ѿ��и��̵�·��
        }
        if(TS.hasTransfer(top.second)) {
            for(const auto& transfer : TS.getTransfers(top.second)) {
                if(blockStations.find(transfer.first.second)!=blockStations.end()) {
                    continue;//��վ���Ƿ��վ��
                }
                if(transfer.first==end) {
                    pq_ans.emplace(NumberOfTransfers[top.second]+1,top.second);
                }
                if(NumberOfTransfers.find(transfer.first)==NumberOfTransfers.end()||NumberOfTransfers[transfer.first]>NumberOfTransfers[top.second]+1) {
                    NumberOfTransfers[transfer.first] = NumberOfTransfers[top.second]+1;
                    prev[transfer.first] = top.second;
                    pq.emplace(NumberOfTransfers[transfer.first],transfer.first);
                }
            }//�������л�����Ϣ
        }
        if(lines.at(top.second.first).hasStation(top.second.second)) {
            auto station = lines.at(top.second.first).getStationIndex(top.second.second);
            if(!lines.at(top.second.first).isFirstStation(station)) {
                auto frontStation = station;
                --frontStation;
                if(blockStations.find(frontStation->first)==blockStations.end()) {
                    Station now = {top.second.first,frontStation->first};
                    if(now==end) {
                        pq_ans.emplace(NumberOfTransfers[top.second],top.second);
                    }
                    if(NumberOfTransfers.find(now)==NumberOfTransfers.end()||
                        NumberOfTransfers[now]>NumberOfTransfers[top.second]) {
                        NumberOfTransfers[now] = NumberOfTransfers[top.second];
                        prev[now] = top.second;
                        pq.emplace(NumberOfTransfers[now],now);
                        }
                }
            }
            if(!lines.at(top.second.first).isLastStation(station)) {
                auto backStation = station;
                ++backStation;
                if(blockStations.find(backStation->first)==blockStations.end()) {
                    Station now = {top.second.first,backStation->first};
                    if(now==end) {
                        pq_ans.emplace(NumberOfTransfers[top.second],top.second);
                    }
                    if(NumberOfTransfers.find(now)==NumberOfTransfers.end()||
                        NumberOfTransfers[now]>NumberOfTransfers[top.second]) {
                        NumberOfTransfers[now] = NumberOfTransfers[top.second];
                        prev[now] = top.second;
                        pq.emplace(NumberOfTransfers[now],now);
                    }
                }
            }
        }//��������ֱ����Ϣ
    }
    return result;
}