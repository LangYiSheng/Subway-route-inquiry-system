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

//������
class Transfer {
    map<pair<int,string>,list<pair<pair<int,string>,Length>>>transfers;//������Ϣ,��·�ź�վ������������Ϣ��ӳ��
    //������Ϣ��һ��map��������·�ź�վ������pair��ֵ��һ��vector�����л��˵�������·��վ�����;���
    //ʵ��������ͼ���ڽӱ����ƵĽṹ
public:
    Transfer () = default;//Ĭ�Ϲ��캯��
    explicit Transfer(map<pair<int,string>,list<pair<pair<int,string>,int>>> transfers):transfers(std::move(transfers)){}//���컻����Ϣ ���ڴ��ļ���ȡ������Ϣ
    bool addTransfer(const pair<int,string>& station1,const pair<int,string>& station2,Length length);//��ӻ�����Ϣ
    bool removeTransfer(const pair<int,string>& station1,const pair<int,string>& station2);//ɾ��������Ϣ
    const list<pair<pair<int,string>,Length>>& getTransfers(const pair<int,string>& station) const;//��ȡĳվ��Ļ�����Ϣ
    bool hasTransfer(const pair<int,string>&station) const;//�ж�ĳվ���Ƿ��л�����Ϣ
    bool hasTransfer(const pair<int,string>&station1,const pair<int,string>&station2) const;//�ж���վ���Ƿ��л�����Ϣ
    const map<pair<int,string>,list<pair<pair<int,string>,Length>>>& getTransfers() const;//��ȡ���л�����Ϣ,���ڱ��浽�ļ�
};

#endif //TRANSFER_H
