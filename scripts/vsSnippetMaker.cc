//2020724　スニペット自動作成
#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<stdio.h>
#include <unistd.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int intend=4;
string ifname,ofname;
string body,name,prefix,scope,description;
vector<string> reg_first,reg_second;

int makeSnipett(ifstream &in,ofstream &out){
    out << "{" << endl;

    for(auto s:reg_first){
        out << s <<endl;
    }

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
    out <<"\t\t\"description\":\""+description+"\"" <<endl;
    out << "\t}," <<endl;
    for(auto s:reg_second){
        out << s <<endl;
    }
    out << "}" <<endl;
    return 0;
}

void Main(){
    string ans;
    do{
        cout << "# What is snipett name ?" <<endl;
        cout<<"::";cin >> name;
        cout << "# What language is used in this ? Exmple:cpp,python,javascript,etc.." <<endl;
        cout<<"::";cin >> scope;
        cout << "# What is prefix ? " <<endl;
        cout<<"::";cin >> prefix;
        cout << "# Write any description ?? Y/n " <<endl;
        cin >> ans;
        if(ans[0]=='Y'||ans[0]=='y'){
            cout << "## write your description below" <<endl;
            cin.ignore();
            cout<<"::";getline(cin,description);
        } 
        sleep(1);
        cout << "==============" <<endl;
        cout << "  name:"+name+"\n  scope:"+scope+"\n  prefix:"+prefix +"\n description:\""+ description +"\""<<endl;
        cout << "==============" <<endl;
        cout << "# Is this OK ?? (Y/n)\n";
        cin>>ans;
    }while(ans[0]=='n'||ans[0]=='N');

    /*printf("making snipett  ");
    sleep(1);
    printf("making snipett.  ");
    sleep(1);
    printf("making snipett.. ");*/
    sleep(1);
    printf("making snipett...");

    ifstream st(ofname);
    if(!st){
        cout<<"I failed to open output file"<<endl;
        cout<<"maybe there is no such file"<<endl;
        cout<<"so create file"<<endl;
    }
    string line;
    smatch sm;
    while(getline(st,line)){
        if(regex_match(line,sm,regex("\t\""+name+"\":\\{"))){
            cout << "***same name exist***" <<endl;
            sleep(1);
            cout << "# Do you want to OVERWRITE ?? (Y/n)" <<endl;
            cin >> ans;
            if(ans[0] != 'Y'&& ans[0] != 'y'){cout << "Stop.." <<endl;return;}
            while(getline(st,line)){
                if(regex_match(line,sm,regex(R"(\t\},.)")))break;
            }
            break;
        }else if(regex_match(line,sm,regex("\t\t\"prefix\":.*\""+prefix+"\".*"))){
            cout << "***same prefix exist***" <<endl;
            cout << "Stop..." <<endl; return;
        }
        if(regex_search(line,sm,regex(R"(^\})"))||regex_search(line,sm,regex(R"(^\{)")))continue;
        reg_first.push_back(line);
    }
    while(getline(st,line)){
        if(regex_search(line,sm,regex(R"(^\})"))||regex_search(line,sm,regex(R"(^\{)")))continue;
        reg_second.push_back(line);
    }
    st.close();

    ifstream ifs(ifname);
    ofstream ofs(ofname);
    if(!ifs){
        cerr<<"***failed to open INPUT file***"<<endl;
        return;
    }else if(!ofs){
        cerr<<"***failed to open OUTPUT file***"<<endl;
        return;
    }else{
        cout<<"success to open both files"<<endl;
    }
    
    if(makeSnipett(ifs,ofs)==0)cout << "success!!" <<endl;
    else cout << "***failed...***" <<endl;
}

int main(int ARGV,char* ARGC[]){
    ifname=ARGC[1];
    ofname=ARGC[2];
    Main();
}
