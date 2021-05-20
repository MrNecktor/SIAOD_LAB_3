#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

typedef vector<int> Vertex;

class Graph 
{
public:
    Graph(vector<int>& StartCondition);
    bool HasASolution();
    void GetNextVert(Vertex& v, vector<Vertex>& next);
    void AStar();
    void PrintAns();
    char WhichMove(Vertex from, Vertex to);
    int CountTheHeuristic(Vertex v);
    int LinearConf(Vertex v);
private:
    Vertex Start;
    Vertex Final;
    map<Vertex, int> f;
    map<Vertex, int> g;
    map<Vertex, Vertex> parents;
};

char Graph::WhichMove(Vertex from, Vertex to) 
{
    int FirstSpacePosition = 0;
    int SecSpacePosition = 0;
    for (int i = 0; i < 16; i++) 
    {
        if (from[i] == 0) 
        {
            FirstSpacePosition = i;
            break;
        }
    }
    for (int i = 0; i < 16; i++) 
    {
        if (to[i] == 0) 
        {
            SecSpacePosition = i;
            break;
        }
    }

    switch (SecSpacePosition - FirstSpacePosition) 
    {
    case 1:
        return 'R';
        break;
    case -1:
        return 'L';
        break;
    case 4:
        return 'D';
        break;
    case -4:
        return 'U';
    default:
        break;
    }
    return 0;
}

void Graph::PrintAns()
{
    int NumOfMoves = 0;
    string ReverseWay;
    Vertex tmp = Final;
    while (tmp != Start) 
    {
        NumOfMoves++;
        Vertex prev = parents[tmp];
        ReverseWay += WhichMove(tmp, prev);
        tmp = prev;
    }

    cout << NumOfMoves << endl;
    for (int i = (int)ReverseWay.length() - 1; i >= 0; i--) 
    {
        cout << ReverseWay[i];
    }

}

void Graph::AStar() 
{
    if (!HasASolution()) 
    {
        cout << -1;
        exit(0);
    }
    set<pair<int, Vertex>> q;
    set<Vertex> used;

    g.insert(pair<Vertex, int>(Start, 0));
    f.insert(pair<Vertex, int>(Start, g[Start] + CountTheHeuristic(Start)));
    q.insert(pair<int, Vertex>(f[Start], Start));

    while (!q.empty()) 
    {
        Vertex tmp = q.begin()->second;
        q.erase(q.begin());

        if (tmp == Final) 
        {
            PrintAns();
            return;
        }

        used.insert(tmp);
        vector<Vertex> NextVert;
        GetNextVert(tmp, NextVert);
        for (auto v : NextVert) 
        {
            int TentScore = g[tmp] + 1;
            if (used.find(v) != used.end() && TentScore >= g[v])
            {
                continue;
            }
            if (used.find(v) == used.end() || TentScore < g[v]) 
            {
                parents.insert(pair<Vertex, Vertex>(v, tmp));
                g.insert(pair<Vertex, int>(v, TentScore));
                f.insert(pair<Vertex, int>(v, g[v] + CountTheHeuristic(v)));
                if (q.find({ f[v] - g[v],v }) == q.end())
                    q.insert(pair<int, Vertex>(f[v] - g[v], v));
            }
        }
    }
}

int Graph::CountTheHeuristic(Vertex v)
{
    int Heuristic = 0;
    for (int i = 0; i < v.size(); i++) 
    {
        int elem = v[i];
        if (elem == 0) 
        {
            Heuristic += abs(3 - i / 4) + abs(3 - i % 4);
        }
        else 
        {
            Heuristic += abs((elem - 1) / 4 - i / 4) + abs((elem - 1) % 4 - i % 4);
        }
    }
    return Heuristic;
}

void Graph::GetNextVert(Vertex& v, vector<Vertex>& next) 
{
    int SpacePosition = 0;
    for (int i = 0; i < 16; i++)
    {
        if (v[i] == 0) 
        {
            SpacePosition = i;
            break;
        }
    }
    int i = 0;
    if (SpacePosition < 15 && SpacePosition % 4 != 3) 
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition + 1]);
        i++;
    }

    if (SpacePosition > 0 && SpacePosition % 4 != 0)
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition - 1]);
        i++;
    }

    if (SpacePosition >= 4) 
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition - 4]);
        i++;
    }

    if (SpacePosition <= 11) 
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition + 4]);
    }

}

Graph::Graph(vector<int>& g)
{
    int j = 1;
    for (auto i : g) 
    {
        Start.push_back(i);
        Final.push_back(j);
        j++;
    }
    Final[15] = 0;
}

bool Graph::HasASolution()
{
    int inv = 0;
    for (int i = 0; i < 16; ++i)
        if (Start[i])
            for (int j = 0; j < i; ++j)
                if (Start[j] > Start[i])
                    ++inv;
    for (int i = 0; i < 16; ++i)
        if (Start[i] == 0)
            inv += 1 + i / 4;
    if ((inv & 1) == 1) 
    {
        return false;
    }
    else 
    {
        return true;
    }
}


int main() 
{

    vector<int> g;
    for (int i = 0; i < 16; i++)
    {
         g.push_back(i);
    }

    for (int i = 0; i < 16; i++) 
    {
        int idx = rand() % 16;
        int tmp = g[idx];
        g[idx] = g[0];
        g[0] = tmp;
    }
    for (int i = 0; i < 16; i++)
    {
        cout << g[i] << " ";
        if ((i+1) % 4 == 0) 
        {
            cout << endl;
        }
    }

    time_t st = clock();

    //for (int i = 0; i < 16; i++) 
    //{
        //int tmp = 0;
        //cin >> tmp;
       // g.push_back(tmp);
   // }
    Graph graph(g);
    graph.AStar();
    time_t ft = clock();
    cout << endl << ft - st;
    return 0;
}