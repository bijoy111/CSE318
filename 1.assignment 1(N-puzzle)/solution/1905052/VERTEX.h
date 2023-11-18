#include <bits/stdc++.h>
using namespace std;

class Node
{
    int n; // n*n grid
    int moves; // number of mimimum moves to reach a board from initial board
    int br;//row # of blank
    int bc;//column # of blank
    int** grid;
    Node* parent;

public:

    //constructor
    Node(int n, int** grid, int moves, Node* parent)
    {
        this->moves = moves;
        this->n = n;
        this->parent = parent;

        this->grid = new int*[n+5];
        for (int i = 0; i < n; i++)
        {
            this->grid[i] = new int[n+5];
            for (int j = 0; j < n; j++)
            {
                this->grid[i][j] = grid[i][j];
                if(grid[i][j] == 0)
                {
                    br=i;
                    bc=j;
                }
            }
        }
    }


    //this function will give the grid
    int** Grid()
    {
        int** gr = new int*[n+5];
        for(int i = 0; i < n; i++)
        {
            gr[i] = new int[n+5];
            for(int j = 0; j < n; j++)
            {
                gr[i][j] = grid[i][j];
            }
        }

        return gr;
    }

    //this function will print the current board
    void pGrid()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout<<grid[i][j]<<" ";
            }
            cout << endl;
        }
    }

    //this function will match the current state with target state
    int isTargetBoard()
    {
        int number=1;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j]==0&&i==n-1&&j==n-1)
                {
                    break;
                }
                else if(grid[i][j]==0)
                {
                    return 0;
                }
                else if(grid[i][j]!=number)
                {
                    return 0;
                }
                number++;
            }
        }
        return 1;
    }

    //this function will give  all possible neighbour of the current state
    vector<Node*> Neighbour()
    {

        vector<Node*> nb;


        if(br != (n - 1))
        {
            int** g = Grid();
            g[br][bc] = g[br + 1][bc];
            g[br + 1][bc] = 0;
            nb.push_back(new Node(n, g, moves + 1, this));

            for (int i = 0; i < n; i++)
            {
                delete[] g[i];
            }
            delete[] g;
        }


        if(br != 0)
        {
            int** g = Grid();
            g[br][bc] = g[br - 1][bc];
            g[br - 1][bc] = 0;
            nb.push_back(new Node(n, g, moves + 1, this));

            for(int i = 0; i < n; i++)
            {
                delete[] g[i];
            }
            delete[] g;
        }



        if(bc != (n - 1))
        {
            int** g = Grid();
            g[br][bc] = g[br][bc + 1];
            g[br][bc + 1] = 0;
            nb.push_back(new Node(n, g, moves + 1, this));

            for (int i = 0; i < n; i++)
            {
                delete[] g[i];
            }
            delete[] g;
        }



        if(bc != 0)
        {
            int** g = Grid();
            g[br][bc] = g[br][bc - 1];
            g[br][bc - 1] = 0;
            nb.push_back(new Node(n, g, moves + 1, this));

            for (int i = 0; i < n; i++)
            {
                delete[] g[i];
            }
            delete[] g;
        }



        return nb;
    }

    //this function will give the size of the grid
    int gridSize()
    {
        return n;
    }


    //this function will give the minimum number of moves required to reach the current state from the initial state
    int get_move()
    {
        return moves;
    }

    //this function will give the parent of a node
    Node* pNode()
    {
        return parent;
    }

    //destructor
    ~Node()
    {
        for(int i = 0; i < n; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;
    }

    //estimated cost of the path from the initial state to the goal state( 𝑓(𝑛) = 𝑔(𝑛) + ℎ(𝑛))  using Hamming distance
    int hCost()
    {
        int c=0;
        int number=1;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j]==0)
                {
                    number++;
                    continue;
                }
                else if(grid[i][j]!=number)
                {
                    c++;
                }
                number++;
            }
        }
        return moves+c;
    }

    //estimated cost of the path from the initial state to the goal state( 𝑓(𝑛) = 𝑔(𝑛) + ℎ(𝑛))  using Manhattan distance
    int mCost()
    {
        int c=0;
        int number;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j]==0)
                {
                    continue;
                }
                else
                {
                    number=grid[i][j];
                    //int r1=std::ceil(number*1.0/n);
                    int r1=(number-1)/n;
                    int c1=(number-1)%n;
                    c+=std::abs(i-r1);
                    c+=std::abs(j-c1);
                }
            }
        }
        return moves+c;
    }
};



