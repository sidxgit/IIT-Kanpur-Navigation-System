#include <bits/stdc++.h>
#include <fstream>

#define pb push_back
using namespace std;

unordered_map <string,int> encrypt;
unordered_map <int,string> decrypt;
map<int,vector<pair<int,double>>> adj;
void constructGraph(string src,string dest,double dist)
{
    adj[encrypt[src]].pb({encrypt[dest],dist});
    adj[encrypt[dest]].pb({encrypt[src],dist});
    
    return;
}

void mapping(int &checkpoint,string src,string dest)
{
    if(encrypt.find(src)==encrypt.end())
    {
        encrypt[src]=checkpoint;
        decrypt[checkpoint]=src;
        checkpoint++;
    }
    
    if(encrypt.find(dest)==encrypt.end())
    {    
        encrypt[dest]=checkpoint;
        decrypt[checkpoint]=dest;
        checkpoint++;
    }
    return;
}
void printHead()
{
    cout<<"\n";
    cout << "                         WELCOME TO IIT KANPUR                        " << "\n";
    cout<<"************************************************************************************"<<"\n";
    cout<<"                                                                                    "<<"\n";
    cout<<"                                             ____________                           "<<"\n";
    cout<<"                                             |          |                           "<<"\n";
    cout<<"                                             | AirStrip |                           "<<"\n";
    cout<<"                                             |__________|                           "<<"\n";
    cout<<"                               ____________________|                                "<<"\n";
    cout<<"                               |                   |                                "<<"\n";
    cout<<"                               |                   |__                              "<<"\n";
    cout<<"                               |                      |                             "<<"\n";
    cout<<"                               |                      |                             "<<"\n";
    cout<<"                               |                  ____|                             "<<"\n";
    cout<<"                               |                  |                                 "<<"\n";
    cout<<"                               |                  |                                 "<<"\n";
    cout<<"                               |              ___|____                           "<<"\n";
    cout<<"                               |             |          |                           "<<"\n";
    cout<<"                               |             | Library  |                           "<<"\n";
    cout<<"     ____________              |             |__________|                           "<<"\n";
    cout<<"     |          |______________|                  |                                 "<<"\n";
    cout<<"     |Hall 12/13|              |        __________|                                 "<<"\n";
    cout<<"     |__________|              |       |                                            "<<"\n";
    cout<<"                               |       |                                            "<<"\n";
    cout<<"                   __________  |       |                                            "<<"\n";
    cout<<"                   |        |_|_______|___                                       "<<"\n";
    cout<<"                   |  Hall2 |  |            |                                       "<<"\n";
    cout<<"                   |________|  |            |                                       "<<"\n";
    cout<<"                               |  __________|                                       "<<"\n";
    cout<<"                               |__|        ||                                       "<<"\n";
    cout<<"                               |  | Hall 1 ||                                       "<<"\n";
    cout<<"                               |  |________||                                       "<<"\n";
    cout<<"                               |            |                                       "<<"\n";
    cout<<"                               |            |                                       "<<"\n";
    cout<<"                               |____________|                                       "<<"\n";
    cout<<"                               |            |                                       "<<"\n";
    cout<<"                               |            |       _____________                   "<<"\n";
    cout<<"                               |            |       |           |                   "<<"\n";
    cout<<"                  _____________|            |_______| Hall 6/GH |                   "<<"\n";
    cout<<"                  |            |                    |___________|                   "<<"\n";
    cout<<"              ___|___        |                          |                         "<<"\n";
    cout<<"             |         |       |__________________________|                         "<<"\n";
    cout<<"             |  OAT    |                                                            "<<"\n";
    cout<<"             |_________|                                                            "<<"\n";
    cout<<"                                                                                    "<<"\n";
    cout<<"************************************************************************************"<<"\n";
    cout<<"HOW CAN I HELP YOU WITH ?"<<"\n";
    cout<<"1.TO GET SHORTEST PATH BETWEEN TWO LOCATIONS -- TYPE 1"<<"\n";
    cout<<"2.TO GET SHORTEST PATH BETWEEN ALL THE LOCATIONS -- TYPE 2"<<"\n";
    cout<<"3.TO GET A TRAVELLING PLAN FOR EXPLORING IIT KANPUR CAMPUS  -- TYPE 3"<<"\n";
    cout<<"PRESS ENTER"<<"\n";
}
class Disjointset{
    public:
        vector<int> rank,parent;
        Disjointset(int n)
        {
            rank.resize(n+1,0);
            parent.resize(n+1,0);
            for(int i=0;i<=n;i++)
            {
                parent[i]=i;
            }
        }
        int findurpar(int node)
        {
            if(parent[node]==node)
            return node;
            return parent[node]=findurpar(parent[node]);
        }
        void unionbyrank(int x,int y)
        {
            int par_x=findurpar(x);
            int par_y=findurpar(y);
            if(par_x==par_y) return;
            if(rank[par_x]<rank[par_y])
            {
                parent[par_x]=par_y;
            }
            else if(rank[par_y]<rank[par_x])
            {
                parent[par_y]=par_x;
            }
            else
            {
                parent[par_x]=par_y;
                rank[par_y]++;
            }

        }
};
//Algorithm block
double Djikstras(string source, string destination) {
    vector<int> path(encrypt.size());
    vector<double> distance(encrypt.size(), (double)1e9);
    set<pair<double, int>> st;
    st.insert({0, encrypt[source]});
    distance[encrypt[source]] = 0;
    path[encrypt[source]] = encrypt[source];

    while (!st.empty()) {
        auto it = *st.begin();
        double d = it.first;
        int node = it.second;
        st.erase(it); // Remove the current node from the set

        for (auto it1 : adj[node]) {
            int adjnode = it1.first;
            double edgewt = it1.second;
            if (d + edgewt < distance[adjnode]) {
                if (distance[adjnode] != (double)1e9) {
                    st.erase({distance[adjnode], adjnode});
                }
                distance[adjnode] = d + edgewt;
                path[adjnode] = node;
                st.insert({distance[adjnode], adjnode});
            }
        }
    }
    vector<string> ans;
    int start = encrypt[destination];
    while (path[start] != start) {
        ans.push_back(decrypt[start]);
        start = path[start];
    }
    ans.push_back(decrypt[start]);
    int n = ans.size();
    cout << "Path to follow: ";
    for (int i = n - 1; i > 0; i--) {
        cout << ans[i] << " --> ";
    }
    cout << ans[0] << "\n";
    
    return distance[encrypt[destination]]; // Return the distance after the loop
}
void floydWarshall()
{
    int n=encrypt.size();
    vector<vector<double>> adjmat(n,vector<double>(n,(double)1e9));
    for(auto it:adj)
    {
        for(auto it1:it.second)
        {
            adjmat[it.first][it1.first]=it1.second;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            adjmat[i][j]=0;
        }
    }
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(adjmat[i][j]>(adjmat[i][k]+adjmat[k][j]) && adjmat[k][j]!=(double)1e9 && adjmat[i][k]!=(double)1e9)
                adjmat[i][j]=adjmat[i][k]+adjmat[k][j];
            }
        }
    }
    cout<<"sources"<<"                  "<< "Destinations"<<"\n";
    for(int i=0;i<n;i++)
    {
        cout<<decrypt[i]<<" : ";
        for(int j=0;j<n;j++)
        {
            cout<<"["<<decrypt[j]<<","<<adjmat[i][j]<<"]"<<",";
        }
        cout<<"\n";
    }
    return;
}
double kruskals(string source)
{
    // int start=encrypt[source];
    int n=encrypt.size();
    Disjointset ds(n);
    vector<pair<double,pair<int,int>>>edges;
    for(auto it:adj)
    {
        for(auto it1:it.second)
        {
            if(it1.first>it.first)
            edges.pb({it1.second,{it.first,it1.first}});
        }
    }
    sort(edges.begin(),edges.end());
    double mst=0;
    for(auto it :edges)
    {
        double wt=it.first;
        int x=it.second.first;
        int y=it.second.second;
        if(ds.findurpar(x)!=ds.findurpar(y))
        {
            mst+=wt;
            ds.unionbyrank(x,y);
        }
    }
    vector<vector<string>> ans;
    vector<int> vis(n,0);
    vector<string> temp;
    for(int i=0;i<n;i++)
    {
        if(vis[i]==0)
        {
            int start=i;
            while(ds.parent[start]!=start)
            {
                temp.pb(decrypt[i]);
            }
            ans.pb(temp);
        }
    }
    for(int i=0;i<ans.size();i++)
    {
        for(int j=ans[i].size()-1;i>0;i--)
        {
            cout<<ans[i][j]<<" -- ";
        }
        cout<<ans[i][0]<<"\n";
    }
    return mst;
}
int main()
{
    ifstream file;
    file.open("Project.txt");
    string line;
    int checkpoint=0;
    while(file.good())
    {
        getline(file,line);
        int i=0;
        string temp="",dest,src;
        double dist=0;
        int count=0;
        while(line[i]!='/')
        {
            if(line[i]==',')
            {
                if(count==0)
                {
                    src=temp;
                    count++;
                }
                else if(count==1)
                {
                    dest=temp;
                    count++;
                }
                temp="";
            }
            else
            {
                temp.pb(line[i]);
            }
            i++;
        }
        dist=stod(temp);
        mapping(checkpoint,src,dest);
        constructGraph(src,dest,dist);
    }
    printHead();
    int input;
    // cin>>input;
    cin>>input;
    if(input==1) //djikstras
    {
        string source,dst;
        cout<<"ENTER SOURCE LOCATION : "<<"\n";
        cin>>source;
        cout<<"ENTER DESTINATION LOCATION : "<<"\n";
        cin>>dst;
        cout<<"Distance :"<<Djikstras(source,dst)<<"km"<<"\n";
    }
    else if(input==2)
    {
        floydWarshall();
    } 
    else
    {
        string source;
        cout<<"ENTER SOURCE LOCATION : "<<"\n";
        cin>>source;
        cout<<"TOTAL DISTANCE : "<<kruskals(source)<<"\n";

    }
    return 0;
}
