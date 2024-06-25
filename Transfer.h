//
// Created by LanCher on 24-6-25.
//

#ifndef TRANSFER_H
#define TRANSFER_H

#include <string>
#include <unordered_map>


//������
class Transfer {
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<std::pair<std::string, std::string>,int>>> transfers;
    //������Ϣ����һ��string����·�����ڶ���string��վ������pair�ĵ�һ��string����һ����·�����ڶ���string����һ����·��վ����
    //����transfers["1"]["A"] = {"2","B"}��ʾ1���ߵ�Aվ���Ի��˵�2���ߵ�Bվ

public:
    Transfer() = default;
    explicit Transfer(std::unordered_map<std::string, std::unordered_map<std::string, std::pair<std::pair<std::string, std::string>,int>>> transfers);//���컻����Ϣ ���ڴ��ļ���ȡ������Ϣ
    void addTransfer(const std::string& line1, const std::string& station1, const std::string& line2, const std::string& station2,int length);//��ӻ�����Ϣ lengthΪ���˾���
    void removeTransfer(const std::string& line1, const std::string& station1, const std::string& line2, const std::string& station2);//ɾ��������Ϣ
    std::pair<std::pair<std::string, std::string>,int> getTransfer(const std::string& line, const std::string& station) const;//��ȡ������Ϣ
};

#endif //TRANSFER_H
