#include <iostream>
#include <climits>
#include <vector>
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
    
    vector<vector<pair<char, int>>> dist_vec(nodes, vector<pair<char, int>>(nodes));

    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            if(i == j) dist_vec[i][j] = {i + 'A', 0};
            else dist_vec[i][j] = {'-', INT_MAX};
        }
        
    }
    

    bool update = 0;
    do
    {
        update = 0;

        for(int start = 0; start < nodes; start++)
        {
            for(int dest = 0; dest < nodes; dest++)
            {
                for(auto v : graph[start])
                {
                    int next_hop = v.first;
                    int wt = v.second;

                    if((dist_vec[next_hop][dest].second != INT_MAX) && (dist_vec[start][dest].second > dist_vec[next_hop][dest].second + wt))
                    {
                        dist_vec[start][dest].second = dist_vec[next_hop][dest].second + wt;
                        dist_vec[start][dest].first = next_hop + 'A';
                        update = 1;
                    }
                }
            }
        }
    } while (update);
    
    for(int i = 0; i < nodes; i++)
    {
        cout<<endl;
        cout<<"Node : "<<(char)(i + 'A')<<endl;
        cout<<"Destination"<<"\t"<<"Next Hop"<<"\t"<<"Cost"<<endl;

        for(int j = 0; j < nodes; j++)
        {
            cout<<(char)(j + 'A')<<'\t'<<'\t';
            cout<<dist_vec[i][j].first<<'\t'<<'\t';
            cout<<dist_vec[i][j].second<<endl;
        }
    }
    return 0;
}