#include <iostream>
#include<string.h>
#include<stdlib.h>
#include <fstream>

using namespace std;

class footBallTeam{//��������࣬�����˻����������Ϣ
public:
    string name;//������
    int race_total=0;//�ܳ���
    int race_win=0;//ʤ������
    int race_equal=0;//ƽ�ֳ���
    int race_lose=0;//ʧ�ܳ���
    int ball_goal=0;//������
    int ball_lose=0;//ʧ����
    int integral=0;//����
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
        cout<<name<<"\t���Σ�"<<race_total<<"\tʤ��"<<race_win<<"\tƽ:"<<race_equal<<"\t��:"<<race_lose<<"\t����:"<<ball_goal<<"\tʧ��:"<<ball_lose<<"\t����:"<<integral<<"\n"<<endl;
    }
};
class RaceA_footBallTeam:public footBallTeam{//��Aר������࣬��Ҫ���бȽϺ�����Ϊ����Ӧ���ֱ�������д������CompareTo�������ɡ�
public:
    RaceA_footBallTeam(string tn){//���캯��������Ϊ(�������)
        name = tn;//����strcpy������name�ַ�����ֵ
    }
    RaceA_footBallTeam(){
        name = "";
    }
    bool CompareTo(RaceA_footBallTeam a,RaceA_footBallTeam b){//�ȽϺ�����ͨ��һ���Ĺ������ж�������ӵ������Ⱥ���д�����������Ӧ�������
        if(a.integral<b.integral){//���ǰһ�ӻ���С�ں�һ�ӣ��򽻻�
                return true;
        }
        else if(a.integral==b.integral){//��������ȣ���ȽϾ�����
            int deltaA = a.ball_goal-a.ball_lose,deltaB=b.ball_goal-b.ball_lose;//���㾻����
            if(deltaA<deltaB){//���ǰ�Ӿ������٣��򽻻�
                return true;
            }
        }
        return false;
    }
};
class Race{//�����࣬�����˻����ı�����Ϣ�����������һ����Ӻ�һЩ�����ļӷֹ���
protected:
    RaceA_footBallTeam fbt[100];
    int team_total=0;//�������
    int win_score=0;//ʤ�����û���
    int equal_score=0;//ƽ�ֻ���
    int lose_score=0;//���˵Ļ���
public:
    Race(int Win_score,int Equal_score,int Lose_score){//�����������ֲ����Ĺ��캯��
        win_score = Win_score;
        equal_score = Equal_score;
        lose_score = Lose_score;
    }
    bool adddata(int ida,int idb,int ball_in,int ball_out){//��ӱ������ݣ�����Ϊ(��һ����ţ��ڶ�����ţ���������ʧ����)
        fbt[ida].ball_goal+=ball_in;
        fbt[idb].ball_goal+=ball_out;
        fbt[ida].ball_lose+=ball_out;
        fbt[idb].ball_lose+=ball_in;
        if(ball_in>ball_out){//�������������ʧ��������ʤ�������ּ�3��ʤ����1
            fbt[ida].race_win++;
            fbt[idb].race_lose++;
            fbt[ida].integral+=win_score;
            fbt[idb].integral+=lose_score;
        }
        else if(ball_in==ball_out){//�������������ʧ��������ƽ�֣����ּ�1��ƽ�ּ�1
            fbt[ida].race_equal++;
            fbt[idb].race_equal++;
            fbt[ida].integral+=equal_score;
            fbt[idb].integral+=equal_score;
        }
        if(ball_in<ball_out){//���������С��ʧ�������򸺾֣����ּ�1
            fbt[ida].race_lose++;
            fbt[idb].race_win++;
            fbt[idb].integral+=win_score;
            fbt[ida].integral+=lose_score;
        }
        fbt[ida].race_total++;//�ܳ��μ�1
        fbt[idb].race_total++;
        return true;
    }
    void show(){//�������Ļ
        for(int i=0;i<team_total;i++){
            cout<<i+1<<":";
            fbt[i].show();
        }
    }
    void sort(){//ð������
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
    void addTeam(string name){//������
        fbt[team_total++].name = name;
    }
};
class RaceWithFile:public Race{//�����˴��ļ���ȡ�ı����࣬�����֮ǰ��Race�࣬���������ļ���д����
public:
    RaceWithFile(int x,int y,int z):Race(x,y,z){//�̳�Race��Ĺ��캯��
    };
    void addTeamByFile(string name,int race_total,int race_win,int race_equal,int race_lose,int ball_goal,int ball_lose,int integral){//ͨ����ϸ����������
        fbt[team_total++].setDataByAll(name,race_total,race_win,race_equal,race_lose,ball_goal,ball_lose,integral);
    }
    bool ReadFromFile(){//���ļ��ж�ȡ����
        ifstream myinf;//�ļ�������
        myinf.open("data.dat");//���ļ���λ���ڵ�ǰ�ļ�����
        while(myinf){//ѭ����ȡ
            int i=0,race_total,race_win,race_equal,race_lose,ball_goal,ball_lose,integral;
            string name;
            myinf>>name>>race_total>>race_win>>race_equal>>race_lose>>ball_goal>>ball_lose>>integral;//��������
            if(name!="") addTeamByFile(name,race_total,race_win,race_equal,race_lose,ball_goal,ball_lose,integral);//���һ�����
        }
        myinf.close();//�ر��ļ�������
    }
    bool OutToFile(){//���浽�ļ�
        ofstream  myos;//�ļ������
        myos.open("data.dat");
        for(int i=0;i<team_total;i++){//ѭ�����
            myos<<fbt[i].name<<" "<<fbt[i].race_total<<" "<<fbt[i].race_win<<" "<<fbt[i].race_equal<<" "<<fbt[i].race_lose<<" "<<fbt[i].ball_goal<<" "<<fbt[i].ball_lose<<" "<<fbt[i].integral<<" ";
        }
        myos.close();
    }
};
int main()
{
    RaceWithFile* game = new RaceWithFile(3,1,0);//ʵ����RaceWithFile���󣬲��������ֻ��֣���ʤ���֣�ƽ�ֻ��֣�ʧ�ܻ���
    game->ReadFromFile();//���ļ���ȡ����
    //football a[15] = {"�Ϻ��껨","�Ϻ�����","����ʵ��","������˳","���ڽ�����","�������","���Ϻ���","�����ִ�","�Ĵ��ڳ�","�ൺ������","���ʦ��","ɽ��³��","��������","��������","��һ��̶"};//����2003���A���������ʼ�����ֱ�����
    while(1){
        int cmd=0;
        int zc,kc,zs,ks;
        string name;
        system("cls");//����ϵͳ��������
        cout<<"�����������ţ�\n1.���һ�ֱ����÷֡�2.�����ӡ�3.�����ǰ������4.�˳�����"<<endl;
        cin>>cmd;
        switch(cmd){//ѭ��ѡ���֧
            case 1:
                cout<<"�����ʽ��������(���) �ͳ���(���) �����÷� �ͳ��÷֣�"<<endl;
                cin>>zc>>kc>>zs>>ks;//��ȡ������(���) �ͳ���(���) �����÷� �ͳ��÷�
                game->adddata(zc-1,kc-1,zs,ks);
                break;
            case 2:
                cout<<"�����ʽ�������"<<endl;
                cin>>name;//��ȡ������ �����
                game->addTeam(name);
                break;
            case 3:
                game->sort();//����
                game->show();//�������Ļ
                game->OutToFile();//������ݵ��ļ�
                system("pause");//��ͣ
                break;
            case 4:
                game->OutToFile();
                return 0;//�˳�
                break;
        }
    }
    return 0;
}
