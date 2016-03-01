#include <iostream>
#include<string.h>
#include<stdlib.h>
#include <fstream>

using namespace std;

class footBallTeam{//基础球队类，包含了基本的球队信息
public:
    string name;//队伍名
    int race_total=0;//总场次
    int race_win=0;//胜利场次
    int race_equal=0;//平局场次
    int race_lose=0;//失败场次
    int ball_goal=0;//进球数
    int ball_lose=0;//失球数
    int integral=0;//积分
    footBallTeam(){
        name = "";
    }
    void setDataByAll(string Name,int Race_total,int Race_win,int Race_equal,int Race_lose,int Ball_goal,int Ball_lose,int Integral){
        name = Name;
        race_total = Race_total;
        race_win = Race_win;
        race_equal = Race_equal;
        race_lose = Race_lose;
        ball_goal = Ball_goal;
        ball_lose = Ball_lose;
        integral = Integral;
    }
    void show(){
        cout<<name<<"\t场次："<<race_total<<"\t胜："<<race_win<<"\t平:"<<race_equal<<"\t负:"<<race_lose<<"\t进球:"<<ball_goal<<"\t失球:"<<ball_lose<<"\t积分:"<<integral<<"\n"<<endl;
    }
};
class RaceA_footBallTeam:public footBallTeam{//甲A专用球队类，主要含有比较函数，为了适应多种比赛，重写这个类的CompareTo函数即可。
public:
    RaceA_footBallTeam(string tn){//构造函数，参数为(球队名称)
        name = tn;//调用strcpy函数对name字符串赋值
    }
    RaceA_footBallTeam(){
        name = "";
    }
    bool CompareTo(RaceA_footBallTeam a,RaceA_footBallTeam b){//比较函数，通过一定的规则来判断两个球队的排名先后，重写这个函数以适应更多比赛
        if(a.integral<b.integral){//如果前一队积分小于后一队，则交换
                return true;
        }
        else if(a.integral==b.integral){//若积分相等，则比较净球数
            int deltaA = a.ball_goal-a.ball_lose,deltaB=b.ball_goal-b.ball_lose;//计算净球数
            if(deltaA<deltaB){//如果前队净球数少，则交换
                return true;
            }
        }
        return false;
    }
};
class Race{//比赛类，定义了基本的比赛信息，里面包含了一组球队和一些基本的加分规则
protected:
    RaceA_footBallTeam fbt[100];
    int team_total=0;//球队总数
    int win_score=0;//胜利后获得积分
    int equal_score=0;//平局积分
    int lose_score=0;//输了的积分
public:
    Race(int Win_score,int Equal_score,int Lose_score){//设置三个积分参数的构造函数
        win_score = Win_score;
        equal_score = Equal_score;
        lose_score = Lose_score;
    }
    bool adddata(int ida,int idb,int ball_in,int ball_out){//添加比赛数据，参数为(第一个序号，第二个序号，进球数，失球数)
        fbt[ida].ball_goal+=ball_in;
        fbt[idb].ball_goal+=ball_out;
        fbt[ida].ball_lose+=ball_out;
        fbt[idb].ball_lose+=ball_in;
        if(ball_in>ball_out){//如果进球数大于失球数，则胜利，积分加3，胜场加1
            fbt[ida].race_win++;
            fbt[idb].race_lose++;
            fbt[ida].integral+=win_score;
            fbt[idb].integral+=lose_score;
        }
        else if(ball_in==ball_out){//如果进球数等于失球数，则平局，积分加1，平局加1
            fbt[ida].race_equal++;
            fbt[idb].race_equal++;
            fbt[ida].integral+=equal_score;
            fbt[idb].integral+=equal_score;
        }
        if(ball_in<ball_out){//如果进球数小于失球数，则负局，负局加1
            fbt[ida].race_lose++;
            fbt[idb].race_win++;
            fbt[idb].integral+=win_score;
            fbt[ida].integral+=lose_score;
        }
        fbt[ida].race_total++;//总场次加1
        fbt[idb].race_total++;
        return true;
    }
    void show(){//输出到屏幕
        for(int i=0;i<team_total;i++){
            cout<<i+1<<":";
            fbt[i].show();
        }
    }
    void sort(){//冒泡排序
        for(int i=0;i<team_total;i++){
            for(int j=i;j<team_total-1;j++){
                if(fbt[j].CompareTo(fbt[j],fbt[j+1])){
                    RaceA_footBallTeam temp = fbt[j];
                    fbt[j] = fbt[j+1];
                    fbt[j+1] = temp;
                }
            }
        }
    }
    void addTeam(string name){//添加球队
        fbt[team_total++].name = name;
    }
};
class RaceWithFile:public Race{//增加了从文件读取的比赛类，相较于之前的Race类，这个类具有文件读写功能
public:
    RaceWithFile(int x,int y,int z):Race(x,y,z){//继承Race类的构造函数
    };
    void addTeamByFile(string name,int race_total,int race_win,int race_equal,int race_lose,int ball_goal,int ball_lose,int integral){//通过详细参数添加球队
        fbt[team_total++].setDataByAll(name,race_total,race_win,race_equal,race_lose,ball_goal,ball_lose,integral);
    }
    bool ReadFromFile(){//从文件中读取数据
        ifstream myinf;//文件输入流
        myinf.open("data.dat");//打开文件，位置在当前文件夹下
        while(myinf){//循环读取
            int i=0,race_total,race_win,race_equal,race_lose,ball_goal,ball_lose,integral;
            string name;
            myinf>>name>>race_total>>race_win>>race_equal>>race_lose>>ball_goal>>ball_lose>>integral;//读入数据
            if(name!="") addTeamByFile(name,race_total,race_win,race_equal,race_lose,ball_goal,ball_lose,integral);//添加一个球队
        }
        myinf.close();//关闭文件输入流
    }
    bool OutToFile(){//保存到文件
        ofstream  myos;//文件输出流
        myos.open("data.dat");
        for(int i=0;i<team_total;i++){//循环输出
            myos<<fbt[i].name<<" "<<fbt[i].race_total<<" "<<fbt[i].race_win<<" "<<fbt[i].race_equal<<" "<<fbt[i].race_lose<<" "<<fbt[i].ball_goal<<" "<<fbt[i].ball_lose<<" "<<fbt[i].integral<<" ";
        }
        myos.close();
    }
};
int main()
{
    RaceWithFile* game = new RaceWithFile(3,1,0);//实例化RaceWithFile对象，并设置三种积分：获胜积分，平局积分，失败积分
    game->ReadFromFile();//从文件读取数据
    //football a[15] = {"上海申花","上海国际","大连实德","辽宁中顺","深圳健力宝","沈阳金德","云南红塔","北京现代","四川冠城","青岛贝莱特","天津康师傅","山东鲁能","重庆力帆","陕西国力","八一湘潭"};//按照2003年甲A参赛队伍初始化积分表数组
    while(1){
        int cmd=0;
        int zc,kc,zs,ks;
        string name;
        system("cls");//调用系统函数清屏
        cout<<"请输入操作序号：\n1.添加一轮比赛得分。2.添加球队。3.输出当前排名。4.退出程序"<<endl;
        cin>>cmd;
        switch(cmd){//循环选择分支
            case 1:
                cout<<"输入格式：主场队(序号) 客场队(序号) 主场得分 客场得分）"<<endl;
                cin>>zc>>kc>>zs>>ks;//获取主场队(序号) 客场队(序号) 主场得分 客场得分
                game->adddata(zc-1,kc-1,zs,ks);
                break;
            case 2:
                cout<<"输入格式：球队名"<<endl;
                cin>>name;//获取球队序号 球队名
                game->addTeam(name);
                break;
            case 3:
                game->sort();//排序
                game->show();//输出到屏幕
                game->OutToFile();//输出数据到文件
                system("pause");//暂停
                break;
            case 4:
                game->OutToFile();
                return 0;//退出
                break;
        }
    }
    return 0;
}
