//
// Created by LanCher on 24-6-29.
//

#ifndef MENU_H
#define MENU_H

#include "Line.h"
#include "FileIO.h"
#include "Transfer.h"
#include <iostream>
#include <map>
#include <set>

class Menu {
    map<int,Line> lines;//��·��Ϣ,��·�ŵ���·��ӳ�䣬ʹ��map��Ϊ�˰��������
    set<string> blockedStations;//����վ��
    Transfer TS;//������Ϣ
    vector<bool> settings;//������Ϣ,����10��boolֵ��������
    //��һ��boolֵ��ʾ�Ƿ��ڳ�������ʱ�Զ���ȡ��·��Ϣ
    //�ڶ���boolֵ��ʾ�Ƿ��ڳ����˳�ʱ�Զ�������·��Ϣ
    //������boolֵ��ʾ�Ƿ�����ʾ·��ʱ��ʾվ������
    //���ĸ�boolֵ��ʾ�Ƿ�����ʾ·��ʱ��ʾվ���Ƿ񱻽���
public:
    Menu():settings(SETTING_NUM,true) {}//��ʼ��������Ϣ;



    void MainMenu();//���˵�
        void InquiryLineMenu();//��·��ѯ�˵�
            void ShowAllLines();//��ʾ������·
            void InquiryLine();//��ʾĳ����·
        void EditLineMenu();//��·���ݱ༭�˵�
            void AddLine();//�����·
            void RemoveLine();//ɾ����·
            void EditLine();//�༭��·
                void AddStation(int line_number);//�༭��·->���վ��
                void RemoveStation(int line_number);//�༭��·->ɾ��վ��
                void EditStationDistance(int line_number);//�༭��·->�༭վ������
                void EditStationName(int line_number);//�༭��·->�༭վ����
                void ExtendLine(int line_number);//�༭��·->�ӳ���·
                void ShortenLine(int line_number);//�༭��·->������·
            void BlockStationMenu();//����վ��˵�
                void ShowBlockedStations();//����վ��˵�->��ʾ����վ��
                void BlockStation();//����վ��˵�->����ָ��վ��
                void BlockStationInterval();//����վ��˵�->����ָ��վ��
                void UnblockStation();//����վ��˵�->���վ��
                void UnblockStationInterval();//����վ��˵�->���վ��
            void TransferMenu();//������Ϣ�˵�
                void ShowAllTransfers();//������Ϣ�˵�->��ʾ���л�����Ϣ
                void ShowStationTransfers();//������Ϣ�˵�->��ʾĳ��·�Ļ�����Ϣ
                void AddTransfer();//������Ϣ�˵�->��ӻ�����Ϣ
                void RemoveTransfer();//������Ϣ�˵�->ɾ��������Ϣ
        void FileMenu();//�ļ������˵�
            void SaveLines();//������·��Ϣ
            void ReadLines();//��ȡ��·��Ϣ
        void SettingMenu();//���ò˵�
        void TestMenu();//���Բ˵�
            void EnterTransferInformationInBatches();//�������뻻����Ϣ
};



#endif //MENU_H
