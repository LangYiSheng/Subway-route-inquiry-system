//
// Created by LanCher on 24-6-25.
//

#include "Transfer.h"

bool Transfer::addTransfer(const pair<int, string>& station1, const pair<int, string>& station2, Length length) {
    if(station1.first==station2.first) {
        return false;//同一线路的站点不能换乘
    }
    if(hasTransfer(station1,station2)) {
        return false;//已经存在换乘信息
    }
    transfers[station1].emplace_back(station2,length);
    transfers[station2].emplace_back(station1,length);
    return true;
}

bool Transfer::removeTransfer(const pair<int, string>& station1, const pair<int, string>& station2) {
    if(!hasTransfer(station1,station2)) {
        return false;//不存在换乘信息
    }
    for(auto it = transfers[station1].begin();it!=transfers[station1].end();++it) {
        if(it->first==station2) {
            transfers[station1].erase(it);
            break;
        }
    }
    if(transfers[station1].empty()) {
        transfers.erase(station1);
    }
    for(auto it = transfers[station2].begin();it!=transfers[station2].end();++it) {
        if(it->first==station1) {
            transfers[station2].erase(it);
            break;
        }
    }
    if(transfers[station2].empty()) {
        transfers.erase(station2);
    }
    return true;
}

const list<pair<pair<int, string>, Length>>& Transfer::getTransfers(const pair<int, string>& station) const {
    return transfers.at(station);
}

bool Transfer::hasTransfer(const pair<int, string>& station) const {
    return transfers.find(station)!=transfers.end();
}

bool Transfer::hasTransfer(const pair<int, string>& station1, const pair<int, string>& station2) const {
    if(!hasTransfer(station1)) {
        return false;
    }
    for(const auto& transfer : transfers.at(station1)) {
        if(transfer.first==station2) {
            return true;
        }
    }
    return false;
}

const map<pair<int, string>, list<pair<pair<int, string>, Length>>>& Transfer::getTransfers() const {
    return transfers;
}

