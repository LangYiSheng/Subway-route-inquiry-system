//
// Created by LanCher on 24-7-1.
//

#include "GetRoute.h"

#include <algorithm>


/*typedef pair<int, string> Station;
typedef vector<pair<int, vector<pair<int, pair<string, string>>>>> RouteResult;//路线查询结果*/

RouteResult GetRoute::InquiryShortestRoute(pair<int, string> start, pair<int, string> end, map<int, Line>&lines, set<string>&blockStations, Transfer&TS) {
    RouteResult result;//结果
    map<Station, int> distance;//各个站点到起点的距离
    map<Station, Station> prev;//各个站点的前驱
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq;//优先队列
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq_ans;//前驱队列
    pq.emplace(0,start);//起点入队
    distance[start] = 0;//起点到起点的距离为0
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();//取出队首
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
                //检查是否存在重复路径
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
            continue;//已经有更短的路径
        }
        if(TS.hasTransfer(top.second)) {
            for(const auto& transfer : TS.getTransfers(top.second)) {
                if(blockStations.find(transfer.first.second)!=blockStations.end()) {
                    continue;//该站点是封闭站点
                }
                if(transfer.first==end) {
                    pq_ans.emplace(distance[top.second]+transfer.second,top.second);
                }
                if(distance.find(transfer.first)==distance.end()||distance[transfer.first]>distance[top.second]+transfer.second) {
                    distance[transfer.first] = distance[top.second]+transfer.second;
                    prev[transfer.first] = top.second;
                    pq.emplace(distance[transfer.first],transfer.first);
                }
            }//遍历所有换乘信息
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
        }//遍历所有直达信息
    }
    return result;
}

RouteResult GetRoute::InquiryLeastTransferRoute(pair<int, string> start, pair<int, string> end, map<int, Line>&lines, set<string>&blockStations, Transfer&TS) {
    RouteResult result;//结果
    map<Station, int> NumberOfTransfers;//各个站点到起点的换乘次数
    map<Station, Station> prev;//各个站点的前驱
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq;//优先队列
    priority_queue<pair<int,Station>,vector<pair<int,Station>>,greater<>> pq_ans;//前驱队列
    pq.emplace(0,start);//起点入队
    NumberOfTransfers[start] = 0;//起点到起点的换乘次数为0
    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();//取出队首
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
                //检查是否存在重复路径
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
            continue;//已经有更短的路径
        }
        if(TS.hasTransfer(top.second)) {
            for(const auto& transfer : TS.getTransfers(top.second)) {
                if(blockStations.find(transfer.first.second)!=blockStations.end()) {
                    continue;//该站点是封闭站点
                }
                if(transfer.first==end) {
                    pq_ans.emplace(NumberOfTransfers[top.second]+1,top.second);
                }
                if(NumberOfTransfers.find(transfer.first)==NumberOfTransfers.end()||NumberOfTransfers[transfer.first]>NumberOfTransfers[top.second]+1) {
                    NumberOfTransfers[transfer.first] = NumberOfTransfers[top.second]+1;
                    prev[transfer.first] = top.second;
                    pq.emplace(NumberOfTransfers[transfer.first],transfer.first);
                }
            }//遍历所有换乘信息
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
        }//遍历所有直达信息
    }
    return result;
}