#include <bits/stdc++.h>
using namespace std;

struct P{
    string id;
    int at,bt,pr,rt,ct,st,rem;
};

struct R{
    vector<pair<string,pair<int,int> > > g;
    double aw,at,ar;
};

vector<P> p;

void addg(vector<pair<string,pair<int,int> > > &g,string id,int s,int e){
    if(s==e)return;
    if(!g.empty()&&g.back().first==id&&g.back().second.second==s)
        g.back().second.second=e;
    else g.push_back(make_pair(id,make_pair(s,e)));
}

R finish(vector<pair<string,pair<int,int> > > g){
    double w=0,t=0,r=0;
    int n=p.size();
    for(int i=0;i<n;i++){
        w+=p[i].ct-p[i].at-p[i].bt;
        t+=p[i].ct-p[i].at;
        r+=p[i].st-p[i].at;
    }
    R x;
    x.g=g;
    x.aw=w/n;
    x.at=t/n;
    x.ar=r/n;
    return x;
}

void reset(){
    for(int i=0;i<(int)p.size();i++){
        p[i].rem=p[i].bt;
        p[i].ct=-1;
        p[i].st=-1;
    }
}

void show(string name,R x){
    cout<<"\n"<<name<<"\nGantt: ";
    for(int i=0;i<(int)x.g.size();i++)
        cout<<"| "<<x.g[i].first<<" "<<x.g[i].second.first<<"-"<<x.g[i].second.second<<" ";
    cout<<"|\n";
    cout<<"Average Waiting Time: "<<fixed<<setprecision(2)<<x.aw<<"\n";
    cout<<"Average Turnaround Time: "<<x.at<<"\n";
    cout<<"Average Response Time: "<<x.ar<<"\n";
}

R fcfs(){
    reset();
    vector<pair<string,pair<int,int> > > g;
    vector<int> a(p.size());
    for(int i=0;i<(int)p.size();i++)a[i]=i;

    stable_sort(a.begin(),a.end(),[](int i,int j){
        return p[i].at==p[j].at?p[i].id<p[j].id:p[i].at<p[j].at;
    });

    int t=0;
    for(int k=0;k<(int)a.size();k++){
        int i=a[k];
        t=max(t,p[i].at);
        p[i].st=t;
        addg(g,p[i].id,t,t+p[i].bt);
        t+=p[i].bt;
        p[i].ct=t;
    }
    return finish(g);
}

R sjf(){
    reset();
    vector<pair<string,pair<int,int> > > g;
    int n=p.size(),done=0,t=0;

    while(done<n){
        int k=-1;
        for(int i=0;i<n;i++)
            if(p[i].ct<0&&p[i].at<=t)
                if(k<0||p[i].bt<p[k].bt||
                  (p[i].bt==p[k].bt&&p[i].at<p[k].at))
                    k=i;

        if(k<0){t++;continue;}

        p[k].st=t;
        addg(g,p[k].id,t,t+p[k].bt);
        t+=p[k].bt;
        p[k].ct=t;
        done++;
    }
    return finish(g);
}

R priority(){
    reset();
    vector<pair<string,pair<int,int> > > g;
    int n=p.size(),done=0,t=0;

    while(done<n){
        int k=-1;
        for(int i=0;i<n;i++)
            if(p[i].ct<0&&p[i].at<=t)
                if(k<0||p[i].pr<p[k].pr||
                  (p[i].pr==p[k].pr&&p[i].at<p[k].at))
                    k=i;

        if(k<0){t++;continue;}

        p[k].st=t;
        addg(g,p[k].id,t,t+p[k].bt);
        t+=p[k].bt;
        p[k].ct=t;
        done++;
    }
    return finish(g);
}

R rr(int q){
    reset();
    vector<pair<string,pair<int,int> > > g;
    queue<int> Q;
    vector<int> in(p.size(),0);
    int t=0,done=0,n=p.size();

    while(done<n){
        for(int i=0;i<n;i++)
            if(!in[i]&&p[i].at<=t){
                in[i]=1;
                Q.push(i);
            }

        if(Q.empty()){t++;continue;}

        int i=Q.front();
        Q.pop();

        if(p[i].st<0)p[i].st=t;

        int d=min(q,p[i].rem);
        addg(g,p[i].id,t,t+d);
        t+=d;
        p[i].rem-=d;

        for(int j=0;j<n;j++)
            if(!in[j]&&p[j].at<=t){
                in[j]=1;
                Q.push(j);
            }

        if(p[i].rem==0){
            p[i].ct=t;
            done++;
        }else Q.push(i);
    }
    return finish(g);
}

R psrtf(){
    reset();
    vector<pair<string,pair<int,int> > > g;
    int n=p.size(),done=0,t=0;

    while(done<n){
        int k=-1;

        for(int i=0;i<n;i++)
            if(p[i].ct<0&&p[i].at<=t)
                if(k<0||p[i].rem<p[k].rem||
                  (p[i].rem==p[k].rem&&p[i].at<p[k].at))
                    k=i;

        if(k<0){t++;continue;}

        if(p[k].st<0)p[k].st=t;

        addg(g,p[k].id,t,t+1);
        p[k].rem--;
        t++;

        if(p[k].rem==0){
            p[k].ct=t;
            done++;
        }
    }
    return finish(g);
}

R mlfq(){
    reset();
    vector<pair<string,pair<int,int> > > g;
    queue<int> q[3];
    vector<int> in(p.size(),0);

    int n=p.size(),done=0,t=0;

    while(done<n){
        for(int i=0;i<n;i++)
            if(!in[i]&&p[i].at<=t){
                in[i]=1;
                q[0].push(i);
            }

        int l;
        if(!q[0].empty())l=0;
        else if(!q[1].empty())l=1;
        else l=2;

        if(q[l].empty()){t++;continue;}

        int i=q[l].front();
        q[l].pop();

        if(p[i].st<0)p[i].st=t;

        int quantum;
        if(l==0)quantum=2;
        else if(l==1)quantum=4;
        else quantum=p[i].rem;

        int d=min(quantum,p[i].rem);

        for(int z=0;z<d;z++){
            addg(g,p[i].id,t,t+1);
            t++;
            p[i].rem--;

            for(int j=0;j<n;j++)
                if(!in[j]&&p[j].at<=t){
                    in[j]=1;
                    q[0].push(j);
                }

            if(p[i].rem==0)break;
        }

        if(p[i].rem==0){
            p[i].ct=t;
            done++;
        }else{
            q[min(2,l+1)].push(i);
        }
    }

    return finish(g);
}

bool load(string f){
    ifstream in(f.c_str());
    if(!in)return false;

    string s;
    getline(in,s);
    p.clear();

    while(getline(in,s)){
        if(s.empty())continue;

        stringstream ss(s);
        string a,b,c,d;

        getline(ss,a,',');
        getline(ss,b,',');
        getline(ss,c,',');
        getline(ss,d,',');

        try{
            P x;
            x.id=a;
            x.at=stoi(b);
            x.bt=stoi(c);
            x.pr=stoi(d);
            x.rem=x.bt;
            x.ct=-1;
            x.st=-1;
            x.rt=0;
            p.push_back(x);
        }catch(...){}
    }

    return !p.empty();
}

int main(){
    string file;
    cout<<"CSV file: ";
    cin>>file;

    if(!load(file)){
        cout<<"Cannot read CSV\n";
        return 1;
    }

    int ch,q;
    R x;
    vector<pair<string,R> > all;

    while(1){
        cout<<"\n1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\n5.PSRTF\n6.MLFQ\n7.All\n0.Exit\nChoice: ";
        cin>>ch;

        if(ch==0)break;

        if(ch==1){
            x=fcfs();
            show("FCFS",x);
            all.push_back(make_pair("FCFS",x));
        }
        else if(ch==2){
            x=sjf();
            show("SJF",x);
            all.push_back(make_pair("SJF",x));
        }
        else if(ch==3){
            x=priority();
            show("Priority",x);
            all.push_back(make_pair("Priority",x));
        }
        else if(ch==4){
            cout<<"Time Quantum: ";
            cin>>q;

            if(q<=0){
                cout<<"Invalid quantum\n";
                continue;
            }

            x=rr(q);
            show("Round Robin",x);
            all.push_back(make_pair("Round Robin",x));
        }
        else if(ch==5){
            x=psrtf();
            show("PSRTF",x);
            all.push_back(make_pair("PSRTF",x));
        }
        else if(ch==6){
            x=mlfq();
            show("MLFQ",x);
            all.push_back(make_pair("MLFQ",x));
        }
        else if(ch==7){
            x=fcfs();
            show("FCFS",x);
            all.push_back(make_pair("FCFS",x));

            x=sjf();
            show("SJF",x);
            all.push_back(make_pair("SJF",x));

            x=priority();
            show("Priority",x);
            all.push_back(make_pair("Priority",x));

            cout<<"Time Quantum: ";
            cin>>q;

            if(q<=0){
                cout<<"Invalid quantum\n";
                continue;
            }

            x=rr(q);
            show("Round Robin",x);
            all.push_back(make_pair("Round Robin",x));

            x=psrtf();
            show("PSRTF",x);
            all.push_back(make_pair("PSRTF",x));

            x=mlfq();
            show("MLFQ",x);
            all.push_back(make_pair("MLFQ",x));
        }
        else cout<<"Invalid choice\n";
    }

    if(!all.empty()){
        cout<<"\nComparison Table\n";
        cout<<left<<setw(18)<<"Algorithm"
            <<setw(15)<<"Avg WT"
            <<setw(15)<<"Avg TAT"
            <<setw(15)<<"Avg RT"<<"\n";

        for(int i=0;i<(int)all.size();i++)
            cout<<left<<setw(18)<<all[i].first
                <<setw(15)<<fixed<<setprecision(2)<<all[i].second.aw
                <<setw(15)<<all[i].second.at
                <<setw(15)<<all[i].second.ar<<"\n";
    }

    return 0;
}

