//
// Created by LanCher on 24-6-25.
//

#ifndef LINE_H
#define LINE_H


#include <vector>
#include <string>
#include <unordered_map>


//线路类
class Line {
    int lineNumber;//线路编号
    std::vector<std::string> stationNames;//站点名数组
    std::unordered_map<std::string, int> stationIndexMap;//站点名到索引的映射
    std::vector<int> lengthToNext;//到下一个站点的距离
    //站点间距离数组，长度比站点名数组少1，下标i对应站点i和站点i+1之间的距离

public:
    Line(int number, const std::vector<std::string>& stations,std::vector<int>length);//构造线路，线路编号和站点名数组和站点间距离
    void addStation(const std::string& station,int pos = -1,int frontLength = 1,int backLength = 1);//添加站点，pos为-1时默认添加到最后，frontLength和backLength分别为新站点到前一个站点和后一个站点的距离
    void removeStation(const std::string& station,int pos = -1);//删除站点，pos为-1时默认删除最后一个，删除站点后，站点间距离也会被删除，因此要更新站点间距离，使得删除站点后的站点间距离不变
    void extendLine(const std::vector<std::string>& additionalStations);//延长线路 在线路末尾添加站点，站点间距离为默认值
    void shortenLine(int start,int length);//缩短线路 从start开始删除length个站点
    void setLengthToNext(int index,int length);//设置站点间距离,index为站点索引,length为站点间距离

    int getLineNumber() const;//获取线路编号
    int getStationIndex(const std::string& station) const;//获取站点索引
    std::string getStationName(int index) const;//获取站点名
    int getLengthToNext(int index) const;//获取到下一个站点的距离
    std::vector<std::string> getStations() const;//获取站点名数组
};


#endif //LINE_H
