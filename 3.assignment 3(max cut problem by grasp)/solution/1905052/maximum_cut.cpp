#include<bits/stdc++.h>
#include<random>

using namespace std;

int n,m; // # of vertex and edge
vector<pair<pair<int,int>,int>>vect1;
vector<vector<pair<int,int>>>vect2;
vector<int>solutionX; // vertex in X set , build by semi greedy.
vector<int>solutionY; // vertex in Y set , build by semi greedy.
vector<int>FinalX;
vector<int>FinalY;

int minEdge=INT_MAX;
int maxEdge=INT_MIN;

int localVal=0;
int localItr=0;

double alp=0;

void semiGreedy(int decide)
{
    double alpha;
    int randomInt = rand();
    while(!solutionX.empty())
        solutionX.pop_back();

    while(!solutionY.empty())
        solutionY.pop_back();

    if(decide==0)
        alpha=0;

    else if(decide==1)
        alpha=1;

    else if(decide==2)
    {
        alpha = static_cast<double>(randomInt) / RAND_MAX;
        alp+=alpha;
    }

    double mu=minEdge+alpha*(maxEdge-minEdge);

    vector<pair<int,pair<int,int>>>edgeList;
    for(int i=0; i<vect1.size(); i++)
    {
        if(vect1[i].second>=mu)
            edgeList.push_back({vect1[i].second,{vect1[i].first.first,vect1[i].first.second}});
    }

    int visited[n+1];
    for(int i=1; i<=n; i++)
        visited[i]=0;

    random_device rd;  // Seed generator
    mt19937 rng(rd()); // Mersenne Twister PRNG
    uniform_int_distribution<int> uni(0, edgeList.size()-1); // Define the range
    int rand=uni(rng);

    vector<int>X;
    vector<int>Y;
    X.push_back(edgeList[rand].second.first);
    Y.push_back(edgeList[rand].second.second);

    visited[edgeList[rand].second.first]=1;//1 means vertex is in X set
    visited[edgeList[rand].second.second]=2;//2 means vertex in in Y set

    int costX[n+1];
    int costY[n+1];

    while((X.size()+Y.size())!=n)
    {
        int sigmaX=0, sigmaY=0;
        int minX=INT_MAX,  minY=INT_MAX;
        int maxX=INT_MIN,  maxY=INT_MIN;

        for(int i=1; i<=n; i++)
        {
            if(visited[i]==0)
            {
                sigmaX=0, sigmaY=0;
                for(int j=0; j<vect2[i].size(); j++)
                {
                    if(visited[vect2[i][j].first]==2)
                        sigmaX+=vect2[i][j].second;
                }
                for(int j=0; j<vect2[i].size(); j++)
                {
                    if(visited[vect2[i][j].first]==1)
                        sigmaY+=vect2[i][j].second;
                }
                if(minX>sigmaX)
                    minX=sigmaX;

                if(minY>sigmaY)
                    minY=sigmaY;

                if(maxX<sigmaX)
                    maxX=sigmaX;

                if(maxY<sigmaY)
                    maxY=sigmaY;

                costX[i]=sigmaX;
                costY[i]=sigmaY;
            }
        }
        int Wmin=min(minX,minY);
        int Wmax=max(maxX,maxY);
        mu=Wmin+alpha*(Wmax-Wmin);

        vector<int>vertex;
        for(int i=1; i<=n; i++)
        {
            if(visited[i]==0)
            {
                if(max(costX[i],costY[i])>=mu)
                    vertex.push_back(i);
            }
        }

        if(vertex.size()==1)
            rand=0;
        else
        {
            random_device rd;  // Seed generator
            mt19937 rng(rd()); // Mersenne Twister PRNG
            uniform_int_distribution<int> uni(0, vertex.size()-1); // Define the range
            rand=uni(rng);
        }
        int vert=vertex[rand];
        if(costX[vert]>costY[vert]&&visited[vert]!=1)
        {
            visited[vert]=1;
            X.push_back(vert);
        }
        else if(visited[vert]!=2)
        {
            visited[vert]=2;
            Y.push_back(vert);
        }
    }

    for(int i=0; i<X.size(); i++)
        solutionX.push_back(X[i]);

    for(int i=0; i<Y.size(); i++)
        solutionY.push_back(Y[i]);
}

void localSearch()
{
    int change=1;
    int visited[n+1];
    for(int i=1; i<=n; i++)
        visited[i]=0;

    for(int i=0; i<solutionX.size(); i++)
        visited[solutionX[i]]=1;

    for(int i=0; i<solutionY.size(); i++)
        visited[solutionY[i]]=2;

    while(change)
    {
        localItr++;
        change=0;
        for(int i=1; i<=n; i++)
        {
            if(visited[i]==1)
            {
                int cost1=0,cost2=0;
                for(int j=0; j<vect2[i].size(); j++)
                {
                    if(visited[vect2[i][j].first]==1)
                        cost1+=vect2[i][j].second;

                    if(visited[vect2[i][j].first]==2)
                        cost2+=vect2[i][j].second;
                }
                if(cost1>cost2)
                {
                    visited[i]=2;
                    change=1;
                }
            }
            else if(visited[i]==2)
            {
                int cost1=0,cost2=0;
                for(int j=0; j<vect2[i].size(); j++)
                {
                    if(visited[vect2[i][j].first]==2)
                        cost1+=vect2[i][j].second;

                    if(visited[vect2[i][j].first]==1)
                        cost2+=vect2[i][j].second;
                }
                if(cost1>cost2)
                {
                    visited[i]=1;
                    change=1;
                }
            }
            if(change==1)
                break;
        }
    }
    while(!solutionX.empty())
        solutionX.pop_back();

    while(!solutionY.empty())
        solutionY.pop_back();

    for(int i=1; i<=n; i++)
    {
        if(visited[i]==1)
            solutionX.push_back(i);

        else if(visited[i]==2)
            solutionY.push_back(i);
    }

    int visited1[n+1];
    for(int i=1; i<=n; i++)
        visited1[i]=0;

    for(int i=0; i<solutionX.size(); i++)
        visited1[solutionX[i]]=1;

    for(int i=0; i<solutionY.size(); i++)
        visited1[solutionY[i]]=2;

    int ans1=0;
    for(int k=0; k<solutionX.size(); k++)
    {
        int i=solutionX[k];
        for(int j=0; j<vect2[i].size(); j++)
        {
            if(visited1[vect2[i][j].first]==2)
                ans1+=vect2[i][j].second;
        }
    }

    localVal+=ans1;
}

void grasp(int maxItr)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    for(int i=1; i<=maxItr; i++)
    {
        semiGreedy(2);
        cout<<i<<": "<<"semigreedy end"<<endl;
        localSearch();
        cout<<i<<": "<<"local search end"<<endl<<endl;
        if(i==1)
        {
            for(int i=0; i<solutionX.size(); i++)
                FinalX.push_back(solutionX[i]);

            for(int i=0; i<solutionY.size(); i++)
                FinalY.push_back(solutionY[i]);
        }
        else
        {
            int visited[n+1];
            for(int i=1; i<=n; i++)
                visited[i]=0;

            for(int i=0; i<solutionX.size(); i++)
                visited[solutionX[i]]=1;

            for(int i=0; i<solutionY.size(); i++)
                visited[solutionY[i]]=2;

            int weight1=0;
            for(int i=0; i<vect1.size(); i++)
            {
                int s=vect1[i].first.first , d=vect1[i].first.second , c=vect1[i].second;
                if(visited[s]==1&&visited[d]==2)
                    weight1+=c;

                else if(visited[s]==2&&visited[d]==1)
                    weight1+=c;
            }
            int weight2=0;
            for(int i=1; i<=n; i++)
                visited[i]=0;

            for(int i=0; i<FinalX.size(); i++)
                visited[FinalX[i]]=1;

            for(int i=0; i<FinalY.size(); i++)
                visited[FinalY[i]]=2;

            for(int i=0; i<vect1.size(); i++)
            {
                int s=vect1[i].first.first , d=vect1[i].first.second , c=vect1[i].second;
                if(visited[s]==1&&visited[d]==2)
                    weight2+=c;

                else if(visited[s]==2&&visited[d]==1)
                    weight2+=c;
            }
            if(weight1>weight2)
            {
                while(!FinalX.empty())
                    FinalX.pop_back();

                while(!FinalY.empty())
                    FinalY.pop_back();

                for(int i=0; i<solutionX.size(); i++)
                    FinalX.push_back(solutionX[i]);

                for(int i=0; i<solutionY.size(); i++)
                    FinalY.push_back(solutionY[i]);
            }
        }
    }
}

int main()
{
    ofstream wfile("output.txt");
    wfile<<"|\t\tProblem\t\t\t|"<<"\t"<<"\tConstructive algorithm "<<" \t|\t"<<"\tLocal search\t"<<"\t|\t"<<"\tGrasp\t\t"<<"\t|\t"<<"upper bound"<<"\t|\t"<<"Alpha for semi greedy-1"<<"\t\t|\t"<<"weight"<<"\t|"<<endl<<endl;
    wfile<<"|Name\t\t|"<<"V or n\t|" <<"E  or m\t|"<<"Ranomized-1\t|"<<"Greedy-1\t|"<<"Semi greedy-1\t|"<<"\tNo. of itr|\t"<<"Best value\t|"<<"\tNo. of itr|\t"<<"Best value\t|"<<endl<<endl;

    ifstream rinput("input.txt");
    int loop=24;
    while(loop)
    {
        cout<<24-loop+1<<endl;
        alp=0;
        while(!vect1.empty())
            vect1.pop_back();
        while(!vect2.empty())
            vect2.pop_back();
        while(!solutionX.empty())
            solutionX.pop_back();
        while(!solutionY.empty())
            solutionY.pop_back();
        while(!FinalX.empty())
            FinalX.pop_back();
        while(!FinalY.empty())
            FinalY.pop_back();

        minEdge=INT_MAX, maxEdge=INT_MIN;
        localVal=0,localItr=0;

        loop--;
        string fileName;
        int ubound;
        rinput>>fileName>>ubound;
        ifstream rfile(fileName);

        rfile>>n>>m; // take input the number of vertex and edge
        vect2.resize(n+1);
        for(int i=1; i<=m; i++)
        {
            int s,d,c;
            rfile>>s>>d>>c;
            vect1.push_back({{s,d},c});
            vect2[s].push_back({d,c});
            vect2[d].push_back({s,c});
        }

        wfile<<"|"<<fileName<<"\t|";
        wfile<<n<<"\t|";
        wfile<<m<<"\t\t|";

        for(int i=0; i<vect1.size(); i++)
        {
            if(vect1[i].second<minEdge)
                minEdge=vect1[i].second;
            if(vect1[i].second>maxEdge)
                maxEdge=vect1[i].second;
        }

        int visited1[n+1];
        int loop1=3;
        int rgreedyAns=0;
        while(loop1)
        {
            loop1--;
            semiGreedy(0); // simple randomized or randomized 1

            for(int i=1; i<=n; i++)
                visited1[i]=0;

            for(int i=0; i<solutionX.size(); i++)
                visited1[solutionX[i]]=1;

            for(int i=0; i<solutionY.size(); i++)
                visited1[solutionY[i]]=2;

            int ans1=0;
            for(int k=0; k<solutionX.size(); k++)
            {
                int i=solutionX[k];
                for(int j=0; j<vect2[i].size(); j++)
                {
                    if(visited1[vect2[i][j].first]==2)
                        ans1+=vect2[i][j].second;
                }
            }
            rgreedyAns+=ans1;
        }
        wfile<<rgreedyAns/3<<"\t\t|";

        semiGreedy(1);
        for(int i=1; i<=n; i++)
            visited1[i]=0;

        for(int i=0; i<solutionX.size(); i++)
            visited1[solutionX[i]]=1;

        for(int i=0; i<solutionY.size(); i++)
            visited1[solutionY[i]]=2;

        int greedyAns=0;
        for(int k=0; k<solutionX.size(); k++)
        {
            int i=solutionX[k];
            for(int j=0; j<vect2[i].size(); j++)
            {
                if(visited1[vect2[i][j].first]==2)
                    greedyAns+=vect2[i][j].second;
            }
        }
        wfile<<greedyAns<<"\t\t|";

        loop1=3;
        int sgreedyAns=0;
        while(loop1)
        {
            loop1--;
            semiGreedy(2);
            for(int i=1; i<=n; i++)
                visited1[i]=0;

            for(int i=0; i<solutionX.size(); i++)
                visited1[solutionX[i]]=1;

            for(int i=0; i<solutionY.size(); i++)
                visited1[solutionY[i]]=2;

            int ans1=0;
            for(int k=0; k<solutionX.size(); k++)
            {
                int i=solutionX[k];
                for(int j=0; j<vect2[i].size(); j++)
                {
                    if(visited1[vect2[i][j].first]==2)
                        ans1+=vect2[i][j].second;
                }
            }
            sgreedyAns+=ans1;
        }
        double sAlpha=alp/3.0;
        wfile<<sgreedyAns/3<<"\t\t|";

        int maxItr;
        mt19937 rn(time(nullptr));
        uniform_int_distribution<int> distribution(5, 30);  // Define the range for the random value
        maxItr = distribution(rn); // Generate a random value between 5 and 30
        cout<<"maximum iteration: "<<maxItr<<endl;

        localVal=0 , localItr=0;
        grasp(maxItr);

        int visited[n+1];
        for(int i=1; i<=n; i++)
            visited[i]=0;

        for(int i=0; i<FinalX.size(); i++)
            visited[FinalX[i]]=1;

        for(int i=0; i<FinalY.size(); i++)
            visited[FinalY[i]]=2;

        int ans=0;
        for(int k=0; k<FinalX.size(); k++)
        {
            int i=FinalX[k];
            for(int j=0; j<vect2[i].size(); j++)
            {
                if(visited[vect2[i][j].first]==2)
                    ans+=vect2[i][j].second;
            }
        }
        cout<<"Answer: "<<ans<<endl;
        wfile <<"\t"<<localItr/maxItr<<"\t  |\t"       <<localVal/maxItr<<"\t\t|\t"               <<maxItr<<"\t  |\t"       <<ans<<"\t\t|"<<"\t"<<ubound<<"\t\t|\t"<<setprecision(2)<<sAlpha<<"\t\t\t\t|\t";

        if(minEdge==maxEdge)
            wfile<<minEdge<<"\t|";
        else
            wfile<<minEdge<<" to "<<maxEdge<<"\t|";
        wfile<<endl<<endl;

        rfile.close();
    }
    rinput.close();
    wfile.close();
    return 0;
}
