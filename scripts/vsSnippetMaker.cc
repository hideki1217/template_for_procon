//2020724　スニペット自動作成
#include<iostream>
#include<string>
#include<fstream>
#include<regex>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int intend=4;
string ifname,ofname;
string body,name,prefix,scope;
vector<string> reg;

int makeSnipett(ifstream &in,ofstream &out){
    out << "{" << endl;

    for(auto s:reg){
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
    out << "\t}," <<endl;

    out << "}" <<endl;
    return 0;
}

void Main(){
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

    ifstream st(ofname);
    if(!st){
        cerr<<"I failed to open output file"<<endl;
        cerr<<"maybe there is no such file"<<endl;
        cerr<<"so create file"<<endl;
    }
    string line;
    smatch sm;
    while(getline(st,line)){
        if(regex_match(line,sm,regex(".*("+name+"|"+prefix+").*"))){
            cout << "***same name or prefix exist***" <<endl;
            return;
        }
        if(regex_search(line,sm,regex(R"(^\})"))||regex_search(line,sm,regex(R"(^\{)")))continue;
        reg.push_back(line);
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
