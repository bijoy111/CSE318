#include<bits/stdc++.h>
#include "VERTEX.h"
using namespace std;

//this function is used for checking the solvability of the puzzle problem
int isSolvable(int n,int* check,int** grid)
{
    if(n%2==1)
    {
        int inv=0;
        for(int i=0; i<(n*n)-1; i++)
        {
            for(int j=i+1; j<(n*n)-1; j++)
            {
                if(check[i]>check[j])
                {
                    inv++;
                }
            }
        }
        if(inv%2==0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        int inv=0;
        for(int i=0; i<(n*n)-1; i++)
        {
            for(int j=i+1; j<(n*n)-1; j++)
            {
                if(check[i]>check[j])
                {
                    inv++;
                }
            }
        }
        int row=0,col;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j]==0)
                {
                    row=i,col=j;
                    break;
                }
            }
            if(row!=0)
                break;
        }
        row=(n-row);
        col=(n-col);
        if(row%2==0&&inv%2==1)
        {
            return 1;
        }
        else if(row%2==1&&inv%2==0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}


class hamComparator
{
public:
    bool operator()(Node* t1,Node* t2)
    {
        return t1->hCost()   >   t2->hCost();
    }
};


class manComparator
{
public:
    bool operator()(Node* t1,Node* t2)
    {
        return t1->mCost()   >   t2->mCost();
    }
};



class nComparator
{
public:
    bool operator()(Node* t1, Node* t2) const
    {
        int n = t1->gridSize();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (t1->Grid()[i][j] != t2->Grid()[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
};

class nHash
{
public:
    size_t operator()( Node* tmp) const
    {
        string str;
        int n=tmp->gridSize();
        int** grd=tmp->Grid();
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                str += to_string(grd[i][j]) + ",";
            }
        }
        return hash<string>{}(str);
    }
};

void HammingDistance(int n, int** grid)
{
    Node* given_board = new Node(n, grid,0,nullptr);
    std::unordered_set<Node*, nHash, nComparator> result;
    std::priority_queue<Node*, std::vector<Node*>, hamComparator> pq;
    pq.push(given_board);
    while (!pq.empty())
    {
        Node* cb = pq.top();
        pq.pop();
        if (cb->isTargetBoard())
        {
            cout << cb->get_move()<<endl<<endl;
            vector<Node*> vec;
            while(cb->pNode() != nullptr)
            {
                vec.push_back(cb);
                cb=cb->pNode();
            }

            for(int i=vec.size()-1; i>=0; i--)
            {
                Node* tmp=vec[i];
                tmp->pGrid();
                cout<<endl<<endl;
            }

            delete given_board;
            return;
        }

        vector<Node*> nb = cb->Neighbour();
        for (int i = 0; i < nb.size(); i++)
        {
            if (result.find(nb[i]) == result.end())
            {
                pq.push(nb[i]);
            }
            else
            {
                delete nb[i];
            }
        }

        result.insert(cb);
    }
}

void ManhattanDistance(int n, int** grid)
{
    Node* given_board = new Node(n, grid,0,nullptr);
    std::unordered_set<Node*, nHash, nComparator> result;
    std::priority_queue<Node*, std::vector<Node*>, manComparator> pq;
    pq.push(given_board);
    while (!pq.empty())
    {
        Node* cb = pq.top();
        pq.pop();
        if (cb->isTargetBoard())
        {
            cout << cb->get_move()<<endl<<endl;
            vector<Node*> vec;
            while(cb->pNode() != nullptr)
            {
                vec.push_back(cb);
                cb=cb->pNode();
            }

            for(int i=vec.size()-1; i>=0; i--)
            {
                Node* tmp=vec[i];
                tmp->pGrid();
                cout<<endl<<endl;
            }

            delete given_board;
            return;
        }

        vector<Node*> nb = cb->Neighbour();
        for (int i = 0; i < nb.size(); i++)
        {
            if (result.find(nb[i]) == result.end())
            {
                pq.push(nb[i]);
            }
            else
            {
                delete nb[i];
            }
        }

        result.insert(cb);
    }
}

int main()
{
    int n; //grid size is n*n
    int **grid; //it is used to take the board
    int* check; //it is used for checking the puzzle is solvable or not

    cin>>n;
    grid=new int*[n+5];
    check=new int[(n*n)+5];
    int k=0;
    for(int i=0; i<n; i++)
    {
        grid[i]=new int[n+5];
        for(int j=0; j<n; j++)
        {
            int tmp;
            cin>>tmp;
            grid[i][j]=tmp;
            if(tmp!=0)
            {
                check[k++]=tmp;
            }
        }
    }

    if(!isSolvable(n,check,grid))
    {
        cout<<"Unsolvable puzzle"<<endl;
        return 0;
    }

    cout<<"This puzzle problem is solvable"<<endl<<endl;

    HammingDistance(n,grid);
    //ManhattanDistance(n,grid);


    return 0;
}
