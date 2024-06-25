//
// Created by LanCher on 24-6-25.
//

#ifndef LINE_H
#define LINE_H


#include <vector>
#include <string>
#include <unordered_map>


//��·��
class Line {
    int lineNumber;//��·���
    std::vector<std::string> stationNames;//վ��������
    std::unordered_map<std::string, int> stationIndexMap;//վ������������ӳ��
    std::vector<int> lengthToNext;//����һ��վ��ľ���
    //վ���������飬���ȱ�վ����������1���±�i��Ӧվ��i��վ��i+1֮��ľ���

public:
    Line(int number, const std::vector<std::string>& stations,std::vector<int>length);//������·����·��ź�վ���������վ������
    void addStation(const std::string& station,int pos = -1,int frontLength = 1,int backLength = 1);//���վ�㣬posΪ-1ʱĬ����ӵ����frontLength��backLength�ֱ�Ϊ��վ�㵽ǰһ��վ��ͺ�һ��վ��ľ���
    void removeStation(const std::string& station,int pos = -1);//ɾ��վ�㣬posΪ-1ʱĬ��ɾ�����һ����ɾ��վ���վ������Ҳ�ᱻɾ�������Ҫ����վ�����룬ʹ��ɾ��վ����վ�����벻��
    void extendLine(const std::vector<std::string>& additionalStations);//�ӳ���· ����·ĩβ���վ�㣬վ������ΪĬ��ֵ
    void shortenLine(int start,int length);//������· ��start��ʼɾ��length��վ��
    void setLengthToNext(int index,int length);//����վ������,indexΪվ������,lengthΪվ������

    int getLineNumber() const;//��ȡ��·���
    int getStationIndex(const std::string& station) const;//��ȡվ������
    std::string getStationName(int index) const;//��ȡվ����
    int getLengthToNext(int index) const;//��ȡ����һ��վ��ľ���
    std::vector<std::string> getStations() const;//��ȡվ��������
};


#endif //LINE_H
