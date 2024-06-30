//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"

void Menu::MainMenu() {
    while(true) {
        system("cls");
        cout<<"欢迎使用上海地铁线路查询系统"<<endl;
        cout<<"程序内存储线路数量为："<<lines.size()<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.线路查询-获取地铁线路的信息"<<endl;
        cout<<"2.线路编辑-编辑地铁线路的信息"<<endl;
        cout<<"3.路线查询-查询站点间的乘坐线路  "<<endl;
        cout<<"4.保存/读取-保存或读取地铁线路信息"<<endl;
        /*cout<<"9.程序设置-设置程序的一些参数"<<endl;*/
        cout<<"99.开发者测试菜单"<<endl;
        cout<<"0.退出"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                InquiryLineMenu();
            }
            else if(input=="2") {
                EditLineMenu();
            }
            else if(input=="3") {
                /*InquiryRouteMenu();*/
                cout<<"暂未开放"<<endl;
                system("pause");
            }
            else if(input=="4") {
                FileMenu();
            }
            /*else if(input=="9") {
                /*SettingMenu();#1#
                cout<<"暂未开放"<<endl;
                system("pause");
            }*/
            else if(input=="99") {
                TestMenu();
            }
            else if(input=="0") {
                cout<<"感谢使用"<<endl;
                system("pause");
            }
            else {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::InquiryLineMenu() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->线路查询菜单"<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.显示目前所有线路"<<endl;
        cout<<"2.查询某条线路"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                ShowAllLines();
            }
            else if(input=="2") {
                /*InquiryLine();*/
                cout<<"暂未开放"<<endl;
                system("pause");
            }
            else if(input=="0") {
                break;
            }
            else {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::ShowAllLines() {
    system("cls");
    cout<<"当前位于：主页面->线路查询菜单->显示所有线路"<<endl;
    if(lines.empty())
        cout<<"暂无线路信息"<<endl;
    else
        for(const auto & line : lines) {
            cout<<line.first<<"号线"<<": "<<endl;
            for(const auto & station : line.second.getStations()) {
                if(station == line.second.getStations().back())
                    cout<<station<<' ';
                else
                    cout<<' '<<station<<' '<<"->";
            }
            cout<<endl;
        }
    system("pause");
}

void Menu::EditLineMenu() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->线路编辑菜单"<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.添加线路"<<endl;
        cout<<"2.删除线路"<<endl;
        cout<<"3.编辑线路"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                AddLine();
            }
            else if(input=="2") {
                /*RemoveLine();*/
                cout<<"暂未开放"<<endl;
                system("pause");
            }
            else if(input=="3") {
                /*EditLine();*/
                cout<<"暂未开放"<<endl;
                system("pause");
            }
            else if(input=="0") {
                break;
            }
            else {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::AddLine() {
    system("cls");
    cout<<"当前位于：主页面->线路编辑菜单->添加线路"<<endl;
    vector<pair<string,Length>> stations;
    int lineNumber=0;
    cout<<"请输入线路编号：";
    string input;
    while(cin>>input) {
        try {
            lineNumber = stoi(input);
            break;
        }
        catch(...) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
    }
    cout<<"是否额外输入站点间距离？(程序默认距离为1)(y/n)";
    string extra;
    while(cin>>extra) {
        if(extra=="y") {
            cout<<"请输入站点间距离，输入格式为：站点名1 距离1 站点名2 距离2 站点名3 距离3 ..."<<endl;
            cout<<"站点名之间用空格隔开，站点名不能包含空格，距离为正整数"<<endl;
            cout<<"距离为该站点到下一个站点的距离，最后一个距离输入0即可"<<endl;
            cout<<"输入0结束输入"<<endl;
            cout<<"请输入：";
            string station;
            while(cin>>station) {
                if(station=="0") {
                    break;
                }
                string length;
                while(cin>>length) {
                    if(length=="0") {
                        stations.emplace_back(station,0);
                        break;
                    }
                    try {
                        Length len = stoi(length);
                        stations.emplace_back(station,len);
                        break;
                    }
                    catch(...) {
                        cout<<"输入错误，请重新输入："<<endl;
                        continue;
                    }
                }
                if(length == "0")
                    break;
            }
            break;
        }
        else if(extra=="n") {
            cout<<"请输入站点信息，输入格式为：站点名1 站点名2 站点名3 ..."<<endl;
            cout<<"站点名之间用空格隔开，站点名不能包含空格"<<endl;
            cout<<"输入0结束输入"<<endl;
            cout<<"请输入：";
            string station;
            while(cin>>station) {
                if(station=="0") {
                    stations[stations.size()-1].second = 0;
                    break;
                }
                stations.emplace_back(station,1);
            }
            break;
        }
        else {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
    }
    Line line(lineNumber,stations);
    lines[lineNumber] = line;
    cout<<"添加成功"<<endl;
    system("pause");
}

void Menu::FileMenu() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->文件操作菜单"<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"数据位于程序目录下的data文件夹中"<<endl;
        cout<<"1.保存当前数据"<<endl;
        cout<<"2.读取存档数据"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                SaveLines();
            }
            else if(input=="2") {
                ReadLines();
            }
            else if(input=="0") {
                break;
            }
            else {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::SaveLines() {
    if(!FileIO::SaveMain(lines)) {
        cout<<"保存失败"<<endl;
        cout<<"可能原因：创建/打开文件失败"<<endl;
    }
    else cout<<"已完成保存"<<endl;
    system("pause");
}

void Menu::ReadLines() {
    if(!FileIO::LoadMain(lines)) {
        cout<<"读取失败"<<endl;
        cout<<"可能原因：文件不存在或文件格式错误"<<endl;
    }
    else cout<<"已完成读取"<<endl;
    system("pause");
}

void Menu::TestMenu() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->开发者测试菜单"<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="0") {
                break;
            }
            else {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}
