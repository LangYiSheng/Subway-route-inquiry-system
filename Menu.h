//
// Created by LanCher on 24-6-29.
//

#ifndef MENU_H
#define MENU_H

#include "Line.h"
#include<iostream>
#include <map>


class Menu {
    map<int,Line> lines;//��·��Ϣ,��·�ŵ���·��ӳ�䣬ʹ��map��Ϊ�˰��������
public:
    Menu() = default;
    void MainMenu();//���˵�


    void InquiryLineMenu();//��·��ѯ�˵�
    void ShowAllLines();//��ʾ������·

    void EditLineMenu();//��·���ݱ༭�˵�
    void AddLine();//�����·

    void TestMenu();//���Բ˵�
};



#endif //MENU_H
