//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"

void Menu::MainMenu() {
    if(FileIO::GETSET0()) {
        if(!FileIO::LoadMain(lines,blockedStations,settings)) {
            cout<<"自动读取存档失败"<<endl;
            system("pause");
        }
    }
    while(true) {
        system("cls");
        cout<<"欢迎使用上海地铁线路查询系统"<<endl;
        cout<<"程序内存储线路数量为："<<lines.size()<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.线路查询-获取地铁线路的信息"<<endl;
        cout<<"2.线路编辑-编辑地铁线路的信息"<<endl;
        cout<<"3.路线查询-查询站点间的乘坐线路  "<<endl;
        cout<<"4.保存/读取-保存或读取地铁线路信息"<<endl;
        cout<<"5.设置-设置程序的一些参数"<<endl;
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
            else if(input=="5") {
                SettingMenu();
            }
            else if(input=="99") {
                TestMenu();
            }
            else if(input=="0") {
                cout<<"感谢使用"<<endl;
                if(settings[1]) {
                    if(!FileIO::SaveMain(lines,blockedStations,settings)) {
                        cout<<"自动保存存档失败"<<endl;
                        system("pause");
                    }
                    else {
                        cout<<"已自动保存存档"<<endl;
                    }
                }
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
                InquiryLine();
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
            for(const auto & station : line.second.getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    cout<<"(已封闭)";
                if(station!=line.second.getStationsWithLength().back())
                    if(settings[2])
                        cout<<"->"<<station.second<<"->";
                    else
                        cout<<"->";
            }
            cout<<endl;
        }
    system("pause");
}

void Menu::InquiryLine() {
    system("cls");
    cout<<"当前位于：主页面->线路查询菜单->查询某条线路"<<endl;
    while(true) {
        cout<<"请输入要查询的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                cout<<"未找到该线路，请重新输入："<<endl;
                continue;
            }
            cout<<lineNumber<<"号线"<<": "<<endl;
            for(const auto & station : lines[lineNumber].getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    cout<<"(已封闭)";
                if(station!=lines[lineNumber].getStationsWithLength().back())
                    if(settings[2])
                        cout<<"->"<<station.second<<"->";
                    else
                        cout<<"->";
            }
            cout<<endl;
            break;
        }
        if(input=="0")
            break;
    }
}

void Menu::EditLineMenu() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->线路编辑菜单"<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.添加线路"<<endl;
        cout<<"2.删除线路"<<endl;
        cout<<"3.编辑线路"<<endl;
        cout<<"4.禁用站点"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                AddLine();
            }
            else if(input=="2") {
                RemoveLine();
            }
            else if(input=="3") {
                EditLine();
            }
            else if(input=="4") {
                BlockStationMenu();
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
    cout<<"请输入线路编号(输入0取消新增线路)：";
    string input;
    while(cin>>input) {
        try {
            lineNumber = stoi(input);
            if(lines.find(lineNumber)!=lines.end()) {
                cout<<"该线路已存在，请重新输入："<<endl;
                continue;
            }
            break;
        }
        catch(...) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
    }
    if(lineNumber==0) {
        return;
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
                    if(stations.empty()) {
                        cout<<"添加失败"<<endl;
                        cout<<"请至少输入一个站点"<<endl;
                        system("pause");
                        return;
                    }
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

void Menu::RemoveLine() {
    system("cls");
    cout<<"当前位于：主页面->线路编辑菜单->删除线路"<<endl;
    while(true) {
        cout<<"请输入要删除的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                cout<<"未找到该线路，请重新输入："<<endl;
                continue;
            }
            cout<<"您将删除"<<lineNumber<<"号线的信息"<<endl;
            cout<<"是否确认删除该线路？(y/n)";
            string confirm;
            while(cin>>confirm) {
                if(confirm=="y") {
                    lines.erase(lineNumber);
                    cout<<"删除成功"<<endl;
                    break;
                }
                if(confirm=="n")
                    break;
                cout<<"输入错误，请重新输入："<<endl;
            }
            break;
        }
        if(input=="0")
            break;
    }
}

void Menu::EditLine() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->线路编辑菜单->编辑线路"<<endl;
        cout<<"请输入要编辑的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                cout<<"未找到该线路，请重新输入："<<endl;
                continue;
            }
            cout<<"您将编辑"<<lineNumber<<"号线的信息"<<endl;
            cout<<"请通过输入数字来选择功能："<<endl;
            cout<<"1.添加站点"<<endl;
            cout<<"2.删除站点"<<endl;
            cout<<"3.修改站点距离"<<endl;
            cout<<"4.修改站点名称"<<endl;
            cout<<"5.扩充线路长度"<<endl;
            cout<<"6.缩短线路长度"<<endl;
            cout<<"0.返回上一级菜单"<<endl;
            cout<<"请输入您的选择：";
            string input2;
            while(cin>>input2) {
                if(input2=="1") {
                    AddStation(lineNumber);
                }
                else if(input2=="2") {
                    RemoveStation(lineNumber);
                }
                else if(input2=="3") {
                    EditStationDistance(lineNumber);
                }
                else if(input2=="4") {
                    EditStationName(lineNumber);
                }
                else if(input2=="5") {
                    ExtendLine(lineNumber);
                }
                else if(input2=="6") {
                    ShortenLine(lineNumber);
                }
                else if(input2=="0") {
                    break;
                }
                else {
                    cout<<"输入错误，请重新输入："<<endl;
                    continue;
                }
                break;
            }
            system("pause");
            break;
        }
        if(input=="0")
            break;
    }
}

void Menu::AddStation(int line_number) {
    cout<<"请输入要添加的站点所在原站点的名称(输入0返回至上一级，输入-1添加到结尾)"<<endl;
    cout<<"例如：在A站和B站之间添加C站，输入B"<<endl;
    string pos;
    while(cin>>pos) {
        if(pos=="0")
            break;
        if(pos!="-1"&&!lines[line_number].hasStation(pos)) {
            cout<<"未找到该站点，请重新输入："<<endl;
            continue;
        }
        cout<<"请输入要添加的站点名称：";
        string station;
        while(cin>>station) {
            if(lines[line_number].hasStation(station)) {
                cout<<"该站点已存在，请重新输入："<<endl;
                continue;
            }
            break;
        }
        if(pos=="-1") {
            Length frontLength = 1;
            cout<<"请输入新站点与前一个站点的距离：";
            string input;
            while(cin>>input) {
                try {
                    frontLength = stoi(input);
                    break;
                }
                catch(...) {
                    cout<<"输入错误，请重新输入："<<endl;
                    continue;
                }
            }
            if(!lines[line_number].addStation_back(station,frontLength)) {
                cout<<"添加失败"<<endl;
            }
            else cout<<"添加成功"<<endl;
        }
        else {
            Length frontLength = 1;
            Length backLength = 1;
            if(pos!=lines[line_number].getFirstStation()->first) {
                cout<<"请输入新站点与前一个站点的距离：";
                string input;
                while(cin>>input) {
                    try {
                        frontLength = stoi(input);
                        break;
                    }
                    catch(...) {
                        cout<<"输入错误，请重新输入："<<endl;
                        continue;
                    }
                }
            }
            cout<<"请输入新站点与后一个站点的距离：";
            string input;
            while(cin>>input) {
                try {
                    backLength = stoi(input);
                    break;
                }
                catch(...) {
                    cout<<"输入错误，请重新输入："<<endl;
                    continue;
                }
            }
            if(!lines[line_number].addStation(station,pos,frontLength,backLength)) {
                cout<<"添加失败"<<endl;
            }
            else cout<<"添加成功"<<endl;
        }
        break;
    }
}

void Menu::RemoveStation(int line_number) {
    cout<<"请输入要删除的站点名称(输入0返回至上一级)：";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(!lines[line_number].hasStation(station)) {
            cout<<"未找到该站点，请重新输入："<<endl;
            continue;
        }
        cout<<"您将删除"<<station<<"站点的信息"<<endl;
        cout<<"是否确认删除该站点？(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                if(!lines[line_number].removeStation(station)) {
                    cout<<"删除失败"<<endl;
                }
                else cout<<"删除成功"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            cout<<"输入错误，请重新输入："<<endl;
        }
        break;
    }
}

void Menu::EditStationDistance(int line_number) {
    cout<<"请输入要编辑的站点名称(输入0返回至上一级，编辑的距离为此站点与其后一个站点的距离)：";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(!lines[line_number].hasStation(station)) {
            cout<<"未找到该站点，请重新输入："<<endl;
            continue;
        }
        if(lines[line_number].isLastStation(lines[line_number].getStationIndex(station))) {
            cout<<"该站点为最后一个站点，无法编辑距离"<<endl;
            break;
        }
        cout<<"请输入新的站点间距离：";
        string input;
        while(cin>>input) {
            try {
                Length len = stoi(input);
                lines[line_number].getStationIndex(station)->second = len;
                break;
            }
            catch(...) {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
        }
        cout<<"修改成功"<<endl;
        break;
    }
}

void Menu::EditStationName(int line_number) {
    cout<<"请输入要编辑的站点名称(输入0返回至上一级)：";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(!lines[line_number].hasStation(station)) {
            cout<<"未找到该站点，请重新输入："<<endl;
            continue;
        }
        cout<<"请输入新的站点名称：";
        string newStation;
        while(cin>>newStation) {
            if(lines[line_number].hasStation(newStation)) {
                cout<<"该站点已存在，请重新输入："<<endl;
                continue;
            }
            break;
        }
        cout<<"您将把"<<station<<"站点修改为"<<newStation<<"站点"<<endl;
        cout<<"是否确认修改？(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                if(lines[line_number].changeStationName(station,newStation))
                    cout<<"修改成功"<<endl;
                else
                    cout<<"修改失败"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            cout<<"输入错误，请重新输入："<<endl;
        }
        break;
    }
}

void Menu::ExtendLine(int line_number) {
    vector<pair<string,Length>> stations;
    Length frontlength = 1;
    cout<<"请输入延长线路与原线路最后一个站点的距离：";
    string input;
    while(cin>>input) {
        try {
            frontlength = stoi(input);
            break;
        }
        catch(...) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
    }
    cout<<"是否输入站点间距离？(程序默认距离为1)(y/n)";
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
                if(lines[line_number].hasStation(station)) {
                    cout<<"此站点已存在"<<endl;
                    continue;
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
                    if(stations.empty()) {
                        cout<<"添加失败"<<endl;
                        cout<<"请至少输入一个站点"<<endl;
                        system("pause");
                        return;
                    }
                    stations[stations.size()-1].second = 0;
                    break;
                }
                if(lines[line_number].hasStation(station)) {
                    cout<<"此站点已存在"<<endl;
                    continue;
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
    lines[line_number].extendLine(stations,frontlength);
    cout<<"延长完成"<<endl;
}

void Menu::ShortenLine(int line_number) {
    cout<<"请输入要从尾部缩短的站点数量:";
    string input;
    while(cin>>input) {
        int num;
        try {
            num = stoi(input);
        }
        catch(...) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
        if(num<=0) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
        if(num>lines[line_number].getStations().size()) {
            cout<<"您输入的站点超出已有站点个数，请重新输入："<<endl;
            continue;
        }
        cout<<"您将删除"<<num<<"个站点"<<endl;
        cout<<"是否确认删除？(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                lines[line_number].shortenLine(num);
                cout<<"缩短完成"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            cout<<"输入错误，请重新输入："<<endl;
        }
        break;
    }
}

void Menu::BlockStationMenu() {
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->线路编辑菜单->禁用站点"<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.显示目前所有被封闭的站点"<<endl;
        cout<<"2.禁用指定站点"<<endl;
        cout<<"3.禁用指定区间的所有站点"<<endl;
        cout<<"4.解禁站点"<<endl;
        cout<<"5.解禁区间的所有站点"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                ShowBlockedStations();
            }
            else if(input=="2") {
                BlockStation();
            }
            else if(input=="3") {
                BlockStationInterval();
            }
            else if(input=="4") {
                UnblockStation();
            }
            else if(input=="5") {
                UnblockStationInterval();
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
        system("pause");
    }
}

void Menu::ShowBlockedStations() {
    if(blockedStations.empty()) {
        cout<<"暂无被封闭的站点"<<endl;
    }
    else {
        cout<<"目前已被封闭的站点有："<<endl;
        for(const auto & station : blockedStations) {
            cout<<station<<endl;
        }
    };
}

void Menu::BlockStation() {
    cout<<"请输入要封闭的站点名称(输入0返回至上一级)：";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(blockedStations.find(station)!=blockedStations.end()) {
            cout<<"该站点已被封闭，请重新输入："<<endl;
            continue;
        }
        cout<<"您将封闭"<<station<<"站点"<<endl;
        cout<<"是否确认封闭该站点？(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                blockedStations.insert(station);
                cout<<"封闭成功"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            cout<<"输入错误，请重新输入："<<endl;
        }
        break;
    }
}

void Menu::BlockStationInterval() {
    cout<<"请输入要封闭的站点区间所在的线路号(输入0返回至上一级)：";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"未找到该线路，请重新输入："<<endl;
            continue;
        }
        cout<<"请输入要封闭的站点区间的起始站点名称：";
        string start;
        while(cin>>start) {
            if(!lines[lineNumber].hasStation(start)) {
                cout<<"未找到该站点，请重新输入："<<endl;
                continue;
            }
            cout<<"请输入要封闭的站点区间的终点站点名称：";
            string end;
            while(cin>>end) {
                if(!lines[lineNumber].hasStation(end)) {
                    cout<<"未找到该站点，请重新输入："<<endl;
                    continue;
                }
                if(lines[lineNumber].getStationIndexNum(start)>lines[lineNumber].getStationIndexNum(end)) {
                    cout<<"输入错误，请重新输入："<<endl;
                    end = "0";
                    break;
                }
                cout<<"您将封闭"<<lineNumber<<"号线的"<<start<<"站点到"<<end<<"站点的区间"<<endl;
                cout<<"是否确认封闭该区间？(y/n)";
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        for(auto it = lines[lineNumber].getStationIndex(start);it!=lines[lineNumber].getStationIndex(end);++it) {
                            blockedStations.insert(it->first);
                        }
                        blockedStations.insert(lines[lineNumber].getStationIndex(end)->first);
                        cout<<"封闭成功"<<endl;
                        break;
                    }
                    if(confirm=="n")
                        break;
                    cout<<"输入错误，请重新输入："<<endl;
                }
                break;
            }
            if(end == "0")
                continue;
            break;
        }
        break;
    }
}

void Menu::UnblockStation() {
    cout<<"请输入要解封的站点名称(输入0返回至上一级)：";
    string station;
    while(cin>>station) {
        if(station=="0")
            break;
        if(blockedStations.find(station)==blockedStations.end()) {
            cout<<"该站点未被封闭，请重新输入："<<endl;
            continue;
        }
        cout<<"您将解封"<<station<<"站点"<<endl;
        cout<<"是否确认解封该站点？(y/n)";
        string confirm;
        while(cin>>confirm) {
            if(confirm=="y") {
                blockedStations.erase(station);
                cout<<"解封成功"<<endl;
                break;
            }
            if(confirm=="n")
                break;
            cout<<"输入错误，请重新输入："<<endl;
        }
        break;
    }
}

void Menu::UnblockStationInterval() {
    cout<<"请输入要恢复的站点区间所在的线路号(输入0返回至上一级)：";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            cout<<"输入错误，请重新输入："<<endl;
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            cout<<"未找到该线路，请重新输入："<<endl;
            continue;
        }
        cout<<"请输入要恢复的站点区间的起始站点名称：";
        string start;
        while(cin>>start) {
            if(!lines[lineNumber].hasStation(start)) {
                cout<<"未找到该站点，请重新输入："<<endl;
                continue;
            }
            cout<<"请输入要恢复的站点区间的终点站点名称：";
            string end;
            while(cin>>end) {
                if(!lines[lineNumber].hasStation(end)) {
                    cout<<"未找到该站点，请重新输入："<<endl;
                    continue;
                }
                if(lines[lineNumber].getStationIndexNum(start)>lines[lineNumber].getStationIndexNum(end)) {
                    cout<<"输入错误，请重新输入："<<endl;
                    end = "0";
                    break;
                }
                cout<<"您将恢复"<<lineNumber<<"号线的"<<start<<"站点到"<<end<<"站点的区间"<<endl;
                cout<<"是否确认恢复该区间？(y/n)";
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        for(auto it = lines[lineNumber].getStationIndex(start);it!=lines[lineNumber].getStationIndex(end);++it) {
                            blockedStations.erase(it->first);
                        }
                        blockedStations.erase(lines[lineNumber].getStationIndex(end)->first);
                        cout<<"恢复成功"<<endl;
                        break;
                    }
                    if(confirm=="n")
                        break;
                    cout<<"输入错误，请重新输入："<<endl;
                }
                break;
            }
            if(end == "0")
                continue;
            break;
        }
        break;
    }
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
    if(!FileIO::SaveMain(lines,blockedStations,settings)) {
        cout<<"保存失败"<<endl;
        cout<<"可能原因：创建/打开文件失败"<<endl;
    }
    else cout<<"已完成保存"<<endl;
    system("pause");
}

void Menu::ReadLines() {
    if(!FileIO::LoadMain(lines,blockedStations,settings)) {
        cout<<"读取失败"<<endl;
        cout<<"可能原因：文件不存在或文件格式错误"<<endl;
    }
    else cout<<"已完成读取"<<endl;
    system("pause");
}


void Menu::SettingMenu() {
    //第一个bool值表示是否在程序启动时自动读取线路信息
    //第二个bool值表示是否在程序退出时自动保存线路信息
    //第三个bool值表示是否在显示路线时显示站点间距离
    //第四个bool值表示是否在显示路线时显示站点是否被禁用
    while(true) {
        system("cls");
        cout<<"当前位于：主页面->设置菜单"<<endl;
        cout<<"请通过输入数字来改变功能的是否启用："<<endl;
        cout<<"1.程序启动时自动读取线路信息\t\t"<<(settings[0]?"(√)":"(×)")<<endl;
        cout<<"2.程序退出时自动保存线路信息\t\t"<<(settings[1]?"(√)":"(×)")<<endl;
        cout<<"3.在显示路线时显示站点间距离\t\t"<<(settings[2]?"(√)":"(×)")<<endl;
        cout<<"4.在显示路线时显示站点是否被禁用\t"<<(settings[3]?"(√)":"(×)")<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                settings[0] = !settings[0];
            }
            else if(input=="2") {
                settings[1] = !settings[1];
            }
            else if(input=="3") {
                settings[2] = !settings[2];
            }
            else if(input=="4") {
                settings[3] = !settings[3];
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
