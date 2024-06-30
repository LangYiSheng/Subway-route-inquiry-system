//
// Created by LanCher on 24-6-25.
// Finish on 24-6-29.
//

#ifndef LINE_H
#define LINE_H


#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <iterator>
using namespace std;
typedef int Length;//站点间距离 这是为了方便修改站点间距离的类型
typedef list<pair<string,Length>>::iterator StationIt;//站点迭代器

//线路类
class Line {
    int lineNumber{};//线路编号
    list<pair<string,Length>> stationNames;//站点名数组和到下一个站点的距离
    unordered_map<string,StationIt> stationIndexMap;//站点名到索引的映射,用于快速查找站点
public:
    Line()=default;
    Line(int number, const vector<pair<string,Length>>& stations);//构造线路，线路编号和站点名数组和站点间距离
    Line(const Line& line);//拷贝构造函数
    Line& operator=(const Line& line);//赋值运算符
    bool addStation(const string& station,const string& pos,Length frontLength = 1,Length backLength = 1);//添加站点frontLength和backLength分别为新站点到前一个站点和后一个站点的距离,在找到pos位置插入新站点，最终站点位于pos位置
    bool addStation_back(const string& station,Length frontLength);//添加站点frontLength为新站点到前一个站点的距离,在最后一个站点后插入新站点
    bool removeStation(const string& station);//删除站点后，站点间距离也会被删除，因此要更新站点间距离，使得删除站点后的站点间距离不变
    void extendLine(const vector<pair<string,Length>>& additionalStations,Length frontlength);//延长线路 在线路末尾添加站点，站点间距离为默认值
    void shortenLine(int num);//缩短线路 从尾部删除num个站点

    //以下代码是用于获取信息的函数，直接写成inline函数
    int getLineNumber() const {return lineNumber;}//获取线路编号
    bool hasStation(const string& station) const {return stationIndexMap.find(station) != stationIndexMap.end();}//判断是否有站点
    StationIt getFirstStation() {return stationNames.begin();}//获取第一个站点的迭代器
    StationIt getStationIndex(const string&station) const {
        return stationIndexMap.at(station);
    }//获取站点索引
    bool changeStationName(const string& string, const std::string& new_station);//修改站点名

    static string getStationName(const StationIt index) {return index->first;}//获取站点名
    static Length getLengthToNext(const StationIt index) {return index->second;}//获取站点间距离
    static void setLengthToNext(const StationIt index,const Length length) {index->second = length;}//设置站点间距离
    Length getLengthToNext(const string& station) const {return stationIndexMap.at(station)->second;}
    //获取到下一个站点的距离
    StationIt getNextStation(const string& station) const {
        auto it = stationIndexMap.at(station);
        return ++it;
    }//获取该站点的下一个站点的迭代器
    StationIt getPrevStation(const string& station) const {
        auto it = stationIndexMap.at(station);
        return --it;
    }//获取该站点的上一个站点的迭代器
    bool isLastStation(const StationIt index) const {return index == --stationNames.end();}//通过迭代器判断是否是最后一个站点
    bool isFirstStation(const StationIt index) const {return index == stationNames.begin();}//通过迭代器判断是否是第一个站点
    vector<string> getStations() const {
        vector<string> stations;
        for(const auto& station : stationNames) {
            stations.push_back(station.first);
        }
        return stations;
    }//获取站点名数组
    vector<pair<string,Length>> getStationsWithLength() const {
        vector<pair<string,Length>> stations;
        for(const auto& station : stationNames) {
            stations.push_back(station);
        }
        return stations;
    }//获取站点名数组和站点间距离
    int getStationNum() const {return (int)stationNames.size();}//获取站点数量
    bool isStationEmpty() const {return stationNames.empty();}//判断站点是否为空
    int getStationIndexNum(const string& station) const {
        int i= 0;
        for(const auto & stationName : stationNames) {
            if(stationName.first == station) {
                return i;
            }
            ++i;
        }
        return -1;
    }//获取站点索引
};


#endif //LINE_H
