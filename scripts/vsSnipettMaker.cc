//2020724　スニペット自動作成
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int intend=4;
string ifname,ofname;
string body,name,prefix,scope;

int makeSnipett(ifstream &in,ofstream &out){
    out << "\t\""+name+"\":{" << endl; 
    out << "\t\t\"scope\": \""+ scope + "\"," << endl;
    out << "\t\t\"prefix\": \""+ prefix + "\"," << endl;
    out << "\t\t\"body\": [" << endl;
    while(getline(in,body)){
        bool fixed=false;
        int cou=0;
        //空白文字の\tへの置き換え
        for(cou;body[cou]==' ';cou++);
        string a="";
        rep(i,(cou+intend-1)/intend)a+="\\t";
        body.replace(0,cou,a);
        cou=a.size();
        //その他の文字の置き換え
        while(body[cou]!='\0'){
            if(fixed){
                fixed=false;
                cou++;
                continue;
            }
            char s=body[cou];
            if(s=='\"'){
                body.insert(cou,"\\");
                fixed=true;
            }else if(s=='\\'){
                body.insert(cou,"\\");
                fixed=true;
            }
            cou++;
        }
        body="\t\t\t\""+body+"\",";
        //書き込み
        out<<body<<endl;
    }
    out << "\t\t]," <<endl;
    out << "\t}," <<endl;

    return 0;
}

void Main(){
    ofname=ifname+"_snipett";

    ifstream ifs(ifname);
    ofstream ofs(ofname);
    if(!ifs){
        cerr<<"I failed to opne INPUT file"<<endl;
        return;
    }else if(!ofs){
        cerr<<"I failed to opne OUTPUT file"<<endl;
        return;
    }else{
        cout<<"success to open both files"<<endl;
    }
    //処理
    string ans;
    do{
        cout << "# What is snipett name ?" <<endl;
        cin >> name;
        cout << "# What language is used in this ? Exmple:cpp,python,javascript,etc.." <<endl;
        cin >> scope;
        cout << "# What is prefix ? " <<endl;
        cin >> prefix;
        cout << "==============" <<endl;
        cout << "  name:"+name+"\n  scope:"+scope+"\n  prefix:"+prefix <<endl;
        cout << "==============" <<endl;
        cout << "# Is this OK ?? (Y/n)\n";
        cin>>ans;
    }while(ans[0]=='n'||ans[0]=='N');

    cout << "making snipett ..." <<endl;
    
    if(makeSnipett(ifs,ofs)==0)cout << "success!!" <<endl;
}

int main(int ARGV,char* ARGC[]){
    ifname=ARGC[1];
    Main();
}
