#include<bits/stdc++.h> //Header file that include every standard library.
#include<fstream>
#define pb push_back    //push_back can be replaced by pb in our program now.
using namespace std;

int temp = 0; //To check if path is avaiable or not.
vector < string > final; //for storing the final itinerary.
const int INF = 1000000000;
vector<vector<pair<int, float>>> adj(9);
vector< float > min_distance(9);
vector< int > parent(9);
map < string, int > mp;//Each of the node is assigned a particular value corresponding to the string of the place that they represent.
string reverse_mp[9];

int num=0;

class DisjointSet{
    vector <int> rank,par;
public:
    DisjointSet(int n)
    {
        rank.resize(n,1);
        par.resize(n,1);
        for(int i=1;i<n;i++)
        {
            parent[i]=i;
        }
    }
    int findPar(int node)
    {
        if(node==par[node])
        return node;
        
        return par[node]=findPar(par[node]);
    }
    void UnionByRank(int u,int v)
    {
        int par_u=findPar(u);
        int par_v=findPar(v);
        if(par_u==par_v)return;
        
        if(rank[par_u]<rank[par_v])
        {
            par[par_u]=par_v;
        }
        else if(rank[par_v]<rank[par_u])
        {
            par[par_v]=par_u;
        }
        else
        {
            par[par_u]=par_v;
            rank[par_u]++;
        }
    }
};
class touristMap { //Class touristMap consists of all the methods used.
        map < string, list < pair < string, float > > > m; //Container of STL where first argument is Place and Pair consists of connected Place and its Distance.
        
        public:
        
        void addPath(string u, string v, float dist) { //addPath for adding new places.
        //Assuming Bidirectional Way
        m[u].pb(make_pair(v, dist));
        m[v].pb(make_pair(u, dist));
        if(mp.find(u)==mp.end()){
          cout<<u<<" "<<num;
          printf("\n");
          mp[u]=num;
          reverse_mp[num]=u;
          num++;
        }
        if(mp.find(v)==mp.end()){
          cout<<v<<" "<<num;
          printf("\n");
          mp[v]=num;
          reverse_mp[num]=v;
          num++;
        }
        adj[mp[u]].push_back({mp[v],dist});
        adj[mp[v]].push_back({mp[u],dist});
        }
        
        void printAdjList() { //For printing all the connected Places from a particular place.
        
        for (auto j: m) {
        cout << j.first << "-->";
        for (auto vertex: j.second) {
        cout << "(" << vertex.first << "," << vertex.second << ")";
        }
        printf("\n");
        }
        
        int s;
        for (s=0;s<9;s++)
        {
            for (auto f:adj[s])
            {
                cout<<"The first edge is from "<<s<<" "<<f.first<<" "<<f.second;
                printf("\n");
            }
            }
        }
        
        //   void printMap() { //printMap for printing the map manually according to the data entered.
            cout << "WELCOME TO IIT KANPUR" << "\n"<<"\n"<<"\n";
    
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
            cout<<"                               |             _____|______                           "<<"\n";
            cout<<"                               |             |          |                           "<<"\n";
            cout<<"                               |             | Library  |                           "<<"\n";
            cout<<"     ____________              |             |__________|                           "<<"\n";
            cout<<"     |          |______________|                  |                                 "<<"\n";
            cout<<"     |Hall 12/13|              |        __________|                                 "<<"\n";
            cout<<"     |__________|              |       |                                            "<<"\n";
            cout<<"                               |       |                                            "<<"\n";
            cout<<"                   __________  |       |                                            "<<"\n";
            cout<<"                   |        |__|_______|_____                                       "<<"\n";
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
            cout<<"             _____|_____       |                          |                         "<<"\n";
            cout<<"             |         |       |__________________________|                         "<<"\n";
            cout<<"             |  OAT    |                                                            "<<"\n";
            cout<<"             |_________|                                                            "<<"\n";
            cout<<"                                                                                    "<<"\n";
            cout<<"************************************************************************************"<<"\n";
         
        }
        
        //Algorithm Block
        void MST(vector<string> &userInput)
        {
            map<int,bool> t;
            int size = userInput.size();
            for(int i=0;i<size;i++)
            {
                t[mp[userInput[i]]]=true;
            }
            vector <pair<int,pair<int,int>>> edges;
            for(auto it1 : adj)
            {
                for(auto it2 : it1)
                {
                    if(t.find(it1)!=t.end() && t.find(it2.first)!=t.end())
                    {
                        edges.push_back({it2.second,{it1,it2.first}});
                    }
                }
            }
            sort(edges.begin(),edges.end());
            DisjointSet ds(7);
            vector<vector<string>> ans;
            int maxDist=0;
            for(auto it:edges)
            {
                float wt=it.first;
                int u=it.second.first;
                int v=it.second.second;
                if(ds.findPar(u)!=ds.findPar(v))
                {
                    maxDist+=wt;
                    ds.UnionByRank(u,v);
                    ans.push_back({reverse_mp[u],reverse_mp[v],to_string(wt)});
                }
            }
            for (auto it : ans)
            {
                cout<<it[0]<<" -- "<<it[1]<<" = "<<it[2]<<"\n";
            }
        }
        
        
        long long dijkstra(string source, string destination) {
        int s= mp[source];
        int n = 9;
        min_distance.assign(n, INF);
        parent.assign(n, -1);
        vector<bool> u(n, false);
        
        min_distance[s] = 0;
        for (int i = 0; i < n; i++) {
           int v = -1;
           for (int j = 0; j < n; j++) {
               if (!u[j] && (v == -1 || min_distance[j] < min_distance[v]))
                   v = j;
            }
        
            if (min_distance[v] == INF)
                break;
        
            u[v] = true;
            for (auto edge : adj[v]) {
                int to = edge.first;
                int len = edge.second;
        
                if (min_distance[v] + len < min_distance[to]) {
                   min_distance[to] = min_distance[v] + len;
                   cout<<min_distance[to]<<" "<<to;
                   printf("\n");
                   parent[to] = v;
                }
            }
        }
        cout<<mp[destination];
        printf("\n");
        return min_distance[mp[destination]];
    }
        

};

int main() {
    touristMap ourMap;
    ifstream file("text.txt");
    if(!file.is_open()){
        cout<<"File failed to open"<<endl;
        return 0;
    }

    string srchall, desthall, dist;
    vector<string>source, destination;
    vector<float>all_dist;
    float distance;

    string mystring;
    string line;
    
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss, srchall,',');
        source.push_back(srchall);
        getline(ss, desthall,',');
        destination.push_back(desthall);
        getline(ss, dist,',');
        distance=stof(dist);
        all_dist.push_back(distance);
        cout<<distance<<endl;
    }
    file.close();

    int n=source.size();
    for(int i=0;i<n;i++)
    {
        ourMap.addPath(source[i],destination[i],all_dist[i]);
    }
    ourMap.printAdjList();
  //Printing the Map.
  //ourMap.printMap();

    string source, destination;

    cout << "Enter your Source and Destination" << endl;
    cout << "Source :" << " ";
    cin >> source;

    cout << "Destination:" << " ";
    cin >> destination;

    vector < string > v;
    map < string, bool > marked; //For checking out if the place is visited before.

  ///passing source,destination and time in our backtracking algorithm..
    temp = ourMap.dijkstra(source, destination);

    if (temp == INF) {
        cout << "Sorry,no path is possible" << endl;
    }
    else {
        cout<<" The shortest distance is "<<" "<<temp;
        printf("\n");
        cout << "Best way to go is ";
        cout << endl;
    for (int i = 0; i < 9; ++i) {
        if(destination==source){
            break;
        }
        cout << destination << "-->";
        destination=reverse_mp[parent[mp[destination]]];
    }
    cout << destination;
    cout << endl << endl;
    cout << "Wohoo we will visit " << " " << final.size() << " places and reach our Destination on Time" << endl;
  }
  return 0;
}
