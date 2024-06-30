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
typedef int Length;//վ������ ����Ϊ�˷����޸�վ�����������
typedef list<pair<string,Length>>::iterator StationIt;//վ�������

//��·��
class Line {
    int lineNumber{};//��·���
    list<pair<string,Length>> stationNames;//վ��������͵���һ��վ��ľ���
    unordered_map<string,StationIt> stationIndexMap;//վ������������ӳ��,���ڿ��ٲ���վ��
public:
    Line()=default;
    Line(int number, const vector<pair<string,Length>>& stations);//������·����·��ź�վ���������վ������
    Line(const Line& line);//�������캯��
    Line& operator=(const Line& line);//��ֵ�����
    bool addStation(const string& station,const string& pos,Length frontLength = 1,Length backLength = 1);//���վ��frontLength��backLength�ֱ�Ϊ��վ�㵽ǰһ��վ��ͺ�һ��վ��ľ���,���ҵ�posλ�ò�����վ�㣬����վ��λ��posλ��
    bool addStation_back(const string& station,Length frontLength);//���վ��frontLengthΪ��վ�㵽ǰһ��վ��ľ���,�����һ��վ��������վ��
    bool removeStation(const string& station);//ɾ��վ���վ������Ҳ�ᱻɾ�������Ҫ����վ�����룬ʹ��ɾ��վ����վ�����벻��
    void extendLine(const vector<pair<string,Length>>& additionalStations,Length frontlength);//�ӳ���· ����·ĩβ���վ�㣬վ������ΪĬ��ֵ
    void shortenLine(int num);//������· ��β��ɾ��num��վ��

    //���´��������ڻ�ȡ��Ϣ�ĺ�����ֱ��д��inline����
    int getLineNumber() const {return lineNumber;}//��ȡ��·���
    bool hasStation(const string& station) const {return stationIndexMap.find(station) != stationIndexMap.end();}//�ж��Ƿ���վ��
    StationIt getFirstStation() {return stationNames.begin();}//��ȡ��һ��վ��ĵ�����
    StationIt getStationIndex(const string&station) const {
        return stationIndexMap.at(station);
    }//��ȡվ������
    bool changeStationName(const string& string, const std::string& new_station);//�޸�վ����

    static string getStationName(const StationIt index) {return index->first;}//��ȡվ����
    static Length getLengthToNext(const StationIt index) {return index->second;}//��ȡվ������
    static void setLengthToNext(const StationIt index,const Length length) {index->second = length;}//����վ������
    Length getLengthToNext(const string& station) const {return stationIndexMap.at(station)->second;}
    //��ȡ����һ��վ��ľ���
    StationIt getNextStation(const string& station) const {
        auto it = stationIndexMap.at(station);
        return ++it;
    }//��ȡ��վ�����һ��վ��ĵ�����
    StationIt getPrevStation(const string& station) const {
        auto it = stationIndexMap.at(station);
        return --it;
    }//��ȡ��վ�����һ��վ��ĵ�����
    bool isLastStation(const StationIt index) const {return index == --stationNames.end();}//ͨ���������ж��Ƿ������һ��վ��
    bool isFirstStation(const StationIt index) const {return index == stationNames.begin();}//ͨ���������ж��Ƿ��ǵ�һ��վ��
    vector<string> getStations() const {
        vector<string> stations;
        for(const auto& station : stationNames) {
            stations.push_back(station.first);
        }
        return stations;
    }//��ȡվ��������
    vector<pair<string,Length>> getStationsWithLength() const {
        vector<pair<string,Length>> stations;
        for(const auto& station : stationNames) {
            stations.push_back(station);
        }
        return stations;
    }//��ȡվ���������վ������
    int getStationNum() const {return (int)stationNames.size();}//��ȡվ������
    bool isStationEmpty() const {return stationNames.empty();}//�ж�վ���Ƿ�Ϊ��
    int getStationIndexNum(const string& station) const {
        int i= 0;
        for(const auto & stationName : stationNames) {
            if(stationName.first == station) {
                return i;
            }
            ++i;
        }
        return -1;
    }//��ȡվ������
};


#endif //LINE_H
