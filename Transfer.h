//
// Created by LanCher on 24-6-25.
//

#ifndef TRANSFER_H
#define TRANSFER_H

#include <string>
#include <unordered_map>


//换乘类
class Transfer {
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<std::pair<std::string, std::string>,int>>> transfers;
    //换乘信息，第一个string是线路名，第二个string是站点名，pair的第一个string是另一条线路名，第二个string是另一条线路的站点名
    //例如transfers["1"]["A"] = {"2","B"}表示1号线的A站可以换乘到2号线的B站

public:
    Transfer() = default;
    explicit Transfer(std::unordered_map<std::string, std::unordered_map<std::string, std::pair<std::pair<std::string, std::string>,int>>> transfers);//构造换乘信息 用于从文件读取换乘信息
    void addTransfer(const std::string& line1, const std::string& station1, const std::string& line2, const std::string& station2,int length);//添加换乘信息 length为换乘距离
    void removeTransfer(const std::string& line1, const std::string& station1, const std::string& line2, const std::string& station2);//删除换乘信息
    std::pair<std::pair<std::string, std::string>,int> getTransfer(const std::string& line, const std::string& station) const;//获取换乘信息
};

#endif //TRANSFER_H
