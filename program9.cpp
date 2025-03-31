#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main(int argc, char const *argv[])
{
    int nodes;
    cout<<"Enter the number of Nodes : ";
    cin>>nodes;

    int links;
    cout<<"Enter the number of Links : ";
    cin>>links;

    vector<vector<pair<int, int>>> graph(nodes, vector<pair<int, int>>());

    for (int i = 0; i < links; i++)
    {
        char a, b;
        cin>>a>>b;
        int wt;
        cin>>wt;

        graph[a - 'A'].push_back({b - 'A', wt});
        graph[b - 'A'].push_back({a - 'A', wt});
    }
    
    vector<vector<pair<char, int>>> link_state(nodes, vector<pair<char, int>>(nodes));

    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            if(i == j) link_state[i][j] = {i + 'A', 0};
            else link_state[i][j] = {'-', INT_MAX};
        }
        
    }
    

    for (int start = 0; start < nodes; start++)
    {
        vector<bool> vis(nodes);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, start});

        while (!pq.empty())
        {
            auto p = pq.top(); pq.pop();
            int dest = p.second;
            int dist = p.first;

            if(vis[dest]) continue;
            vis[dest] = 1;

            link_state[start][dest].second = dist;

            for(auto v : graph[dest]) if(!vis[v.first])
            {
                int next_dest = v.first;
                int new_dist = v.second;

                if(link_state[start][next_dest].second > link_state[start][dest].second + new_dist)
                {
                    link_state[start][next_dest].second = link_state[start][dest].second + new_dist;

                    if(dest == start) link_state[start][next_dest].first = next_dest + 'A';
                    else link_state[start][next_dest].first = link_state[start][dest].first;
                }

                pq.push({link_state[start][dest].second + new_dist, next_dest});
            }
        }
    }
    
    
    for(int i = 0; i < nodes; i++)
    {
        cout<<endl;
        cout<<"Node : "<<(char)(i + 'A')<<endl;
        cout<<"Destination"<<"\t"<<"Next Hop"<<"\t"<<"Cost"<<endl;

        for(int j = 0; j < nodes; j++)
        {
            cout<<(char)(j + 'A')<<'\t'<<'\t';
            cout<<link_state[i][j].first<<'\t'<<'\t';
            cout<<link_state[i][j].second<<endl;
        }
    }
    return 0;
}