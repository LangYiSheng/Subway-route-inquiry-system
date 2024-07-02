//
// Created by LanCher on 24-6-29.
//

#include "Menu.h"


void Menu::PrintTextWithColor(const string& text, int color,bool if_endl = true) {
    if(settings[5]) {
        //如果开启彩色输出
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);//设置颜色
        cout<<text;
        SetConsoleTextAttribute(hConsole, 7);//恢复默认颜色
    }
    else {
        cout<<text;
    }
    if(if_endl)
        cout<<endl;
}

void Menu::MainMenu() {
    if(FileIO::GETSET0()) {
        if(!FileIO::LoadMain("lines.txt",lines,blockedStations,settings,TS)) {
            PrintTextWithColor("自动读取存档失败",4);
            system("pause");
        }
    }
    //更改窗口标题为
    SetConsoleTitle("上海地铁线路查询系统");
    while(true) {
        system("cls");
        PrintTextWithColor("欢迎使用上海地铁线路查询系统",2);
        PrintTextWithColor("   当前版本：2024.7.2",1);
        cout<<"程序内存储线路数量为："<<lines.size()<<endl;
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.线路查询\t- 获取地铁线路的信息"<<endl;
        cout<<"2.线路编辑\t- 编辑地铁线路的信息"<<endl;
        cout<<"3.路线查询\t- 查询站点间的乘坐线路  "<<endl;
        cout<<"4.保存/读取\t- 保存或读取地铁线路信息"<<endl;
        cout<<"5.设置\t\t- 设置程序的一些参数"<<endl;
        /*cout<<"99.开发者测试菜单"<<endl;*/
        PrintTextWithColor("0.退出",4);
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
                InquiryRouteMenu();
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
                PrintTextWithColor("确定要退出吗？(y/n)",4);
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        cout<<"感谢使用"<<endl;
                        if(settings[1]) {
                            if(!FileIO::SaveMain(lines,blockedStations,settings,TS)) {
                                PrintTextWithColor("自动保存存档失败！",4);
                                PrintTextWithColor("正在返回主菜单",4);
                                system("pause");
                                input="1";//重新进入主菜单
                                break;
                            }
                            cout<<"已自动保存存档"<<endl;
                        }
                        Sleep(2000);
                        return;
                    }
                    if(confirm=="n") {
                        input = "1";
                        break;
                    }
                    PrintTextWithColor("输入错误，请重新输入：",4);
                }
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
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
        PrintTextWithColor("当前位于：主页面->线路查询菜单",2);
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
                PrintTextWithColor("输入错误，请重新输入：",4);
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
    PrintTextWithColor("当前位于：主页面->线路查询菜单->显示所有线路",2);
    if(lines.empty())
        cout<<"暂无线路信息"<<endl;
    else
        for(const auto & line : lines) {
            PrintTextWithColor(to_string(line.first)+"号线",6);
            for(const auto & station : line.second.getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    PrintTextWithColor("(已封闭）",4,false);
                if(settings[4]&&TS.hasTransfer({line.first,station.first})) {
                    PrintTextWithColor("( 可换乘至：" , 9 , false);
                    for(const auto & transfer : TS.getTransfers({line.first,station.first})) {
                        cout<<transfer.first.first<<"号线"<<transfer.first.second<<" ";
                    }
                    PrintTextWithColor(")" , 9 , false);
                }
                if(station!=line.second.getStationsWithLength().back())
                    if(settings[2])
                        PrintTextWithColor("->"+to_string(station.second)+"->",3,false);
                    else
                        PrintTextWithColor("->",3,false);
            }
            cout<<endl;
        }
    system("pause");
}

void Menu::InquiryLine() {
    system("cls");
    PrintTextWithColor("当前位于：主页面->线路查询菜单->查询某条线路",2);
    while(true) {
        cout<<"请输入要查询的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                PrintTextWithColor("未找到该线路，请重新输入：",4);
                continue;
            }
            PrintTextWithColor(to_string(lineNumber)+"号线",6);
            for(const auto & station : lines[lineNumber].getStationsWithLength()) {
                cout<<station.first;
                if(settings[3]&&blockedStations.find(station.first)!=blockedStations.end())
                    PrintTextWithColor("(已封闭）",4,false);
                if(settings[4]&&TS.hasTransfer({lineNumber,station.first})) {
                    PrintTextWithColor("( 可换乘至：" , 9 , false);
                    for(const auto & transfer : TS.getTransfers({lineNumber,station.first})) {
                        cout<<transfer.first.first<<"号线"<<transfer.first.second<<" ";
                    }
                    PrintTextWithColor(")" , 9 , false);
                }
                if(station!=lines[lineNumber].getStationsWithLength().back())
                    if(settings[2])
                        PrintTextWithColor("->"+to_string(station.second)+"->",3,false);
                    else
                        PrintTextWithColor("->",3,false);
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
        PrintTextWithColor("当前位于：主页面->线路编辑菜单",2);
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.添加线路"<<endl;
        cout<<"2.删除线路"<<endl;
        cout<<"3.编辑线路"<<endl;
        cout<<"4.禁用站点菜单"<<endl;
        cout<<"5.换乘信息菜单"<<endl;
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
            else if(input=="5") {
                TransferMenu();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
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
    PrintTextWithColor("当前位于：主页面->线路编辑菜单->添加线路",2);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
                        PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
    PrintTextWithColor("当前位于：主页面->线路编辑菜单->删除线路",2);
    while(true) {
        cout<<"请输入要删除的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                PrintTextWithColor("未找到该线路，请重新输入：",4);
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
                PrintTextWithColor("输入错误，请重新输入：",4);
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
        PrintTextWithColor("当前位于：主页面->线路编辑菜单->编辑线路",2);
        cout<<"请输入要编辑的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber) == lines.end()) {
                PrintTextWithColor("未找到该线路，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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
                        PrintTextWithColor("输入错误，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
                PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
                        PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
            continue;
        }
        if(num<=0) {
            PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
        }
        break;
    }
}

void Menu::BlockStationMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("当前位于：主页面->线路编辑菜单->禁用站点",2);
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
                PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor(station,4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("未找到该线路，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
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
            PrintTextWithColor("输入错误，请重新输入：",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("未找到该线路，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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
                    PrintTextWithColor("输入错误，请重新输入：",4);
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

void Menu::TransferMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("当前位于：主页面->线路编辑菜单->换乘信息菜单",2);
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.显示目前所有换乘信息"<<endl;
        cout<<"2.显示某站点的换乘信息"<<endl;
        cout<<"3.添加换乘信息"<<endl;
        cout<<"4.删除换乘信息"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                ShowAllTransfers();
            }
            else if(input=="2") {
                ShowStationTransfers();
            }
            else if(input=="3") {
                AddTransfer();
            }
            else if(input=="4") {
                RemoveTransfer();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
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

void Menu::ShowAllTransfers() {
    if(TS.getTransfers().empty()) {
        cout<<"暂无换乘信息"<<endl;
        return;
    }
    const auto & transfers = TS.getTransfers();
    for(const auto & transfer : transfers) {
        cout<<transfer.first.first<<"号线的"<<transfer.first.second<<"站点可以换成至以下站点："<<endl;
        for(const auto & station : transfer.second) {
            PrintTextWithColor("("+to_string(station.first.first)+"号线) "+station.first.second+"站点 距离为"+to_string(station.second),6);
            cout<<station.first.second<<"站点 距离为"<<station.second<<endl;
        }
    }
}

void Menu::ShowStationTransfers() {
    cout<<"请输入要查询站点所在的线路编号(输入0返回至上一级)：";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("输入错误，请重新输入：",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("未找到该线路，请重新输入：",4);
            continue;
        }
        cout<<"请输入要查询的站点名称：";
        string station;
        while(cin>>station) {
            if(!lines[lineNumber].hasStation(station)) {
                cout<<"未找到该站点，请重新输入："<<endl;
                continue;
            }
            cout<<lineNumber<<"号线的"<<station<<"站点可以换成至以下站点："<<endl;
            for(const auto & transfer : TS.getTransfers({lineNumber,station})) {
                PrintTextWithColor("("+to_string(transfer.first.first)+"号线) ",6);
                cout<<transfer.first.second<<"站点 距离为"<<transfer.second<<endl;
            }
            break;
        }
        break;
    }
}

void Menu::AddTransfer() {
    cout<<"请输入要添加换乘信息的站点所在的线路编号(输入0返回至上一级)：";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("输入错误，请重新输入：",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("未找到该线路，请重新输入：",4);
            continue;
        }
        cout<<"请输入要添加换乘信息的站点名称：";
        string station;
        while(cin>>station) {
            if(!lines[lineNumber].hasStation(station)) {
                cout<<"未找到该站点，请重新输入："<<endl;
                continue;
            }
            cout<<"请输入要换乘至的线路编号：";
            string input2;
            while(cin>>input2) {
                int lineNumber2;
                try {
                    lineNumber2 = stoi(input2);
                }
                catch(...) {
                    PrintTextWithColor("输入错误，请重新输入：",4);
                    continue;
                }
                if(lines.find(lineNumber2)==lines.end()) {
                    PrintTextWithColor("未找到该线路，请重新输入：",4);
                    continue;
                }
                cout<<"请输入要换乘至的站点名称：";
                string station2;
                while(cin>>station2) {
                    if(!lines[lineNumber2].hasStation(station2)) {
                        cout<<"未找到该站点，请重新输入："<<endl;
                        continue;
                    }
                    cout<<"请输入两站点之间的距离：";
                    string input3;
                    while(cin>>input3) {
                        Length len;
                        try {
                            len = stoi(input3);
                        }
                        catch(...) {
                            PrintTextWithColor("输入错误，请重新输入：",4);
                            continue;
                        }
                        if(TS.addTransfer({lineNumber,station},{lineNumber2,station2},len)) {
                            cout<<"添加成功"<<endl;
                        }
                        else {
                            cout<<"添加失败"<<endl;
                            cout<<"可能原因：换乘信息已存在/换乘线路相同"<<endl;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    }
}

void Menu::RemoveTransfer() {
    cout<<"请输入要删除换乘信息的站点所在的线路编号(输入0返回至上一级)：";
    string input;
    while(cin>>input) {
        int lineNumber;
        try {
            lineNumber = stoi(input);
        }
        catch(...) {
            PrintTextWithColor("输入错误，请重新输入：",4);
            continue;
        }
        if(lineNumber==0)
            break;
        if(lines.find(lineNumber)==lines.end()) {
            PrintTextWithColor("未找到该线路，请重新输入：",4);
            continue;
        }
        cout<<"请输入要删除换乘信息的站点名称：";
        string station;
        while(cin>>station) {
            if(!lines[lineNumber].hasStation(station)) {
                cout<<"未找到该站点，请重新输入："<<endl;
                continue;
            }
            cout<<"请输入要删除换乘信息的换乘线路编号：";
            string input2;
            while(cin>>input2) {
                int lineNumber2;
                try {
                    lineNumber2 = stoi(input2);
                }
                catch(...) {
                    PrintTextWithColor("输入错误，请重新输入：",4);
                    continue;
                }
                if(lines.find(lineNumber2)==lines.end()) {
                    PrintTextWithColor("未找到该线路，请重新输入：",4);
                    continue;
                }
                cout<<"请输入要删除换乘信息的换乘站点名称：";
                string station2;
                while(cin>>station2) {
                    if(!lines[lineNumber2].hasStation(station2)) {
                        cout<<"未找到该站点，请重新输入："<<endl;
                        continue;
                    }
                    PrintTextWithColor("您将删除"+to_string(lineNumber)+"号线的"+station+"站点到"+to_string(lineNumber2)+"号线的"+station2+"站点的换乘信息",4);
                    cout<<"是否确认删除？(y/n)";
                    string confirm;
                    while(cin>>confirm) {
                        if(confirm=="y") {
                            if(TS.removeTransfer({lineNumber,station},{lineNumber2,station2})) {
                                cout<<"删除成功"<<endl;
                            }
                            else {
                                cout<<"删除失败"<<endl;
                                cout<<"可能原因：换乘信息不存在"<<endl;
                            }
                            break;
                        }
                        if(confirm=="n")
                            break;
                        PrintTextWithColor("输入错误，请重新输入：",4);
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    }
}

void Menu::InquiryRouteMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("当前位于：主页面->路线查询菜单",2);
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.查询两站点之间的";PrintTextWithColor("时间最短",6,false);cout<<"路线"<<endl;
        cout<<"2.查询两站点之间的";PrintTextWithColor("换乘最少",6,false);cout<<"路线"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="1") {
                InquiryShortestRoute();
            }
            else if(input=="2") {
                InquiryLeastTransferRoute();
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::InquiryShortestRoute() {
    while(true) {
        system("cls");
        PrintTextWithColor("当前位于：主页面->路线查询菜单->时间最短路线查询",2);
        cout<<"请输入起始站点所在的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber)==lines.end()) {
                PrintTextWithColor("未找到该线路，请重新输入：",4);
                continue;
            }
            cout<<"请输入起始站点名称：";
            string start;
            while(cin>>start) {
                if(!lines[lineNumber].hasStation(start)) {
                    PrintTextWithColor("未找到该站点，请重新输入：",4);
                    continue;
                }
                cout<<"请输入终点站点所在的线路编号：";
                string input2;
                while(cin>>input2) {
                    int lineNumber2;
                    try {
                        lineNumber2 = stoi(input2);
                    }
                    catch(...) {
                        PrintTextWithColor("输入错误，请重新输入：",4);
                        continue;
                    }
                    if(lines.find(lineNumber2)==lines.end()) {
                        PrintTextWithColor("未找到该线路，请重新输入：",4);
                        continue;
                    }
                    cout<<"请输入终点站点名称：";
                    string end;
                    while(cin>>end) {
                        if(!lines[lineNumber2].hasStation(end)) {
                            PrintTextWithColor("未找到该站点，请重新输入：",4);
                            continue;
                        }
                        if(lineNumber==lineNumber2&&start==end) {
                            PrintTextWithColor("起点与终点相同，不用走路，您已经在终点了。",4);
                            system("pause");
                            break;
                        }
                        // vector<pair<路线长度,vector<pair<线路名称,<上车站点,下车站点>>>>>
                        RouteResult result =GetRoute::InquiryShortestRoute({lineNumber,start},{lineNumber2,end},lines,blockedStations,TS);
                        system("cls");
                        if(result.empty()) {
                            PrintTextWithColor("未找到符合条件的路线",4);
                        }
                        else {
                            if(result.size()!=1) {
                                cout<<"找到了"<<result.size()<<"条符合";PrintTextWithColor("时间最短",6,false);cout<<"的路线:"<<endl;
                            }
                            int i = 1;
                            for(const auto & route : result) {
                                if(result.size()!=1)
                                    PrintTextWithColor("路线"+to_string(i),9,false);
                                else
                                    PrintTextWithColor("查询到路线：",9,false);
                                cout<<" 总时间为";PrintTextWithColor(to_string(route.first),6,false);cout<<"分钟"<<endl;
                                for(const auto & line : route.second) {
                                    if(line.second.first==line.second.second)
                                        continue;
                                    cout<<"乘坐";PrintTextWithColor(to_string(line.first)+"号线",3,false);
                                    cout<<"从 "<<line.second.first<<" 站上车 -> "<<line.second.second<<" 站下车"<<endl;
                                }
                                i++;
                                if(i==4) {
                                    PrintTextWithColor("最多显示3条路线",4);
                                    break;
                                }
                            }
                        }
                        system("pause");
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::InquiryLeastTransferRoute() {
    while(true) {
        system("cls");
        PrintTextWithColor("当前位于：主页面->路线查询菜单->换乘最少路线查询",2);
        cout<<"请输入起始站点所在的线路编号(输入0返回至上一级)：";
        string input;
        while(cin>>input) {
            int lineNumber;
            try {
                lineNumber = stoi(input);
            }
            catch(...) {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            if(lineNumber==0)
                break;
            if(lines.find(lineNumber)==lines.end()) {
                PrintTextWithColor("未找到该线路，请重新输入：",4);
                continue;
            }
            cout<<"请输入起始站点名称：";
            string start;
            while(cin>>start) {
                if(!lines[lineNumber].hasStation(start)) {
                    PrintTextWithColor("未找到该站点，请重新输入：",4);
                    continue;
                }
                cout<<"请输入终点站点所在的线路编号：";
                string input2;
                while(cin>>input2) {
                    int lineNumber2;
                    try {
                        lineNumber2 = stoi(input2);
                    }
                    catch(...) {
                        PrintTextWithColor("输入错误，请重新输入：",4);
                        continue;
                    }
                    if(lines.find(lineNumber2)==lines.end()) {
                        PrintTextWithColor("未找到该线路，请重新输入：",4);
                        continue;
                    }
                    cout<<"请输入终点站点名称：";
                    string end;
                    while(cin>>end) {
                        if(!lines[lineNumber2].hasStation(end)) {
                            PrintTextWithColor("未找到该站点，请重新输入：",4);
                            continue;
                        }
                        if(lineNumber==lineNumber2&&start==end) {
                            PrintTextWithColor("起点与终点相同，不用走路，您已经在终点了。",4);
                            system("pause");
                            break;
                        }
                        // vector<pair<换乘次数,vector<pair<线路名称,<上车站点,下车站点>>>>>
                        RouteResult result = GetRoute::InquiryLeastTransferRoute({lineNumber,start},{lineNumber2,end},lines,blockedStations,TS);
                        system("cls");
                        if(result.empty()) {
                            PrintTextWithColor("未找到符合条件的路线",4);
                        }
                        else {
                            if(result.size()!=1) {
                                cout<<"找到了"<<result.size()<<"条符合";PrintTextWithColor("换乘最少",6,false);cout<<"的路线:"<<endl;
                            }
                            int i = 1;
                            for(const auto & route : result) {
                                if(result.size()!=1)
                                    PrintTextWithColor("路线"+to_string(i),9,false);
                                else
                                    PrintTextWithColor("查询到路线：",9,false);
                                cout<<" 总换乘次数为";PrintTextWithColor(to_string(route.first),6,false);cout<<"次"<<endl;
                                for(const auto & line : route.second) {
                                    if(line.second.first==line.second.second)
                                        continue;
                                    cout<<"乘坐";PrintTextWithColor(to_string(line.first)+"号线",3,false);
                                    cout<<"从 "<<line.second.first<<" 站上车 -> "<<line.second.second<<" 站下车"<<endl;
                                }
                                i++;
                                if(i==4) {
                                    PrintTextWithColor("最多显示3条路线",4);
                                    break;
                                }
                            }
                        }
                        system("pause");
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::FileMenu() {
    while(true) {
        system("cls");
        PrintTextWithColor("当前位于：主页面->文件操作菜单",2);
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"数据位于程序目录下的line.txt中"<<endl;
        cout<<"1.保存当前数据"<<endl;
        cout<<"2.读取存档数据"<<endl;
        cout<<"3.从指定文件读取数据"<<endl;
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
            else if(input=="3") {
                cout<<"请输入文件名：";
                string filename;
                while(cin>>filename) {
                    //如果前后存在双引号，则删除
                    if(filename.front()=='\"'&&filename.back()=='\"') {
                        filename = filename.substr(1,filename.size()-2);
                    }
                    if(!FileIO::LoadMain(filename,lines,blockedStations,settings,TS)) {
                        PrintTextWithColor("读取失败",4);
                        cout<<"可能原因：文件不存在或文件格式错误"<<endl;
                    }
                    else cout<<"已完成读取"<<endl;
                    system("pause");
                    break;
                }
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
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
    if(!FileIO::SaveMain(lines,blockedStations,settings,TS)) {
        PrintTextWithColor("保存失败",4);
        cout<<"可能原因：创建/打开文件失败"<<endl;
    }
    else cout<<"已完成保存"<<endl;
    system("pause");
}

void Menu::ReadLines() {
    if(!FileIO::LoadMain("lines.txt",lines,blockedStations,settings,TS)) {
        PrintTextWithColor("读取失败",4);
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
        PrintTextWithColor("当前位于：主页面->设置菜单",2);
        cout<<"请通过输入数字来改变功能的是否启用："<<endl;
        cout<<"1.程序启动时自动读取线路信息\t\t";PrintTextWithColor((settings[0]?"(√)":"(×)"),settings[0]?2:4);
        cout<<"2.程序退出时自动保存线路信息\t\t";PrintTextWithColor((settings[1]?"(√)":"(×)"),settings[1]?2:4);
        cout<<"3.在显示路线时显示站点间距离\t\t";PrintTextWithColor((settings[2]?"(√)":"(×)"),settings[2]?2:4);
        cout<<"4.在显示路线时显示站点是否被禁用\t";PrintTextWithColor((settings[3]?"(√)":"(×)"),settings[3]?2:4);
        cout<<"5.在显示路线时显示站点换乘信息\t\t";PrintTextWithColor((settings[4]?"(√)":"(×)"),settings[4]?2:4);
        cout<<"6.开启彩色输出\t\t\t\t";PrintTextWithColor((settings[5]?"(√)":"(×)"),settings[5]?2:4);
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
            else if(input=="5") {
                settings[4] = !settings[4];
            }
            else if(input=="6") {
                settings[5] = !settings[5];
            }
            else if(input=="0") {
                break;
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
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
        PrintTextWithColor("当前位于：主页面->开发者菜单",2);
        cout<<"请通过输入数字来选择功能："<<endl;
        cout<<"1.批量输入换乘信息"<<endl;
        cout<<"2.清除所有数据"<<endl;
        cout<<"0.返回上一级菜单"<<endl;
        cout<<"请输入您的选择：";
        string input;
        while(cin>>input) {
            if(input=="0") {
                break;
            }
            if(input=="1") {
                EnterTransferInformationInBatches();
            }
            else if(input=="2") {
                PrintTextWithColor("您将清除所有数据",4);
                cout<<"是否确认清除？(y/n)";
                string confirm;
                while(cin>>confirm) {
                    if(confirm=="y") {
                        lines.clear();
                        blockedStations.clear();
                        settings = {false,false,true,true,true,true,true,true,true,true};
                        TS.clear();
                        cout<<"清除完成"<<endl;
                        PrintTextWithColor("注意：您的存档文件不会被删除，你可以随时恢复到存档状态",4);
                        system("pause");
                        break;
                    }
                    if(confirm=="n")
                        break;
                    PrintTextWithColor("输入错误，请重新输入：",4);
                }
            }
            else {
                PrintTextWithColor("输入错误，请重新输入：",4);
                continue;
            }
            break;
        }
        if(input=="0") {
            break;
        }
    }
}

void Menu::EnterTransferInformationInBatches() {
    cout<<"请输入换乘信息，输入格式为：站点名 线路号数组...0结束数组输入，直到输入#结束全部输入"<<endl;
    string station;
    while(cin>>station) {
        if(station=="#") {
            break;
        }
        if(blockedStations.find(station)!=blockedStations.end()) {
            cout<<"此站点已被封闭"<<endl;
            continue;
        }
        vector<int> targetLines;
        string input;
        while(cin>>input) {
            if(input=="0") {
                break;
            }
            try {
                int lineNumber = stoi(input);
                if(lines.find(lineNumber)==lines.end()) {
                    cout<<"未找到该线路，请重新输入："<<endl;
                    continue;
                }
                targetLines.push_back(lineNumber);
            }
            catch(...) {
                cout<<"输入错误，请重新输入："<<endl;
                continue;
            }
        }
        if(targetLines.empty()) {
            cout<<"请至少输入一个线路号"<<endl;
            continue;
        }
        for(int i = 0;i<targetLines.size()-1;i++) {
            for(int j = i+1;j<targetLines.size();j++) {
                TS.addTransfer(pair<int,string>(targetLines[i],station),pair<int,string>(targetLines[j],station),1);
            }
        }//所有线路的两两组合
    }
    cout<<"输入完成"<<endl;
    system("pause");
}
