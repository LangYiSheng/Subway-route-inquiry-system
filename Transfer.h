//
// Created by LanCher on 24-6-25.
// Finsihed by LanCher on 24-7-1.
//


#ifndef TRANSFER_H
#define TRANSFER_H

#include <string>
#include <map>
#include <utility>
#include <list>

#include "Line.h"
using namespace std;

//换乘类
class Transfer {
    map<pair<int,string>,list<pair<pair<int,string>,Length>>>transfers;//换乘信息,线路号和站点名到换乘信息的映射
    //换乘信息是一个map，键是线路号和站点名的pair，值是一个vector，存有换乘到其他线路的站点名和距离
    //实现与无向图的邻接表类似的结构
public:
    Transfer () = default;//默认构造函数
    explicit Transfer(map<pair<int,string>,list<pair<pair<int,string>,int>>> transfers):transfers(std::move(transfers)){}//构造换乘信息 用于从文件读取换乘信息
    bool addTransfer(const pair<int,string>& station1,const pair<int,string>& station2,Length length);//添加换乘信息
    bool removeTransfer(const pair<int,string>& station1,const pair<int,string>& station2);//删除换乘信息
    const list<pair<pair<int,string>,Length>>& getTransfers(const pair<int,string>& station) const;//获取某站点的换乘信息
    bool hasTransfer(const pair<int,string>&station) const;//判断某站点是否有换乘信息
    bool hasTransfer(const pair<int,string>&station1,const pair<int,string>&station2) const;//判断两站点是否有换乘信息
    const map<pair<int,string>,list<pair<pair<int,string>,Length>>>& getTransfers() const;//获取所有换乘信息,用于保存到文件
};

#endif //TRANSFER_H
