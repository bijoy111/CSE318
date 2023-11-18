#include<bits/stdc++.h>
using namespace std;
class Mancala
{
    int home_position[3]; //the index 1 is used for player1 and index 2 is used for player2 to count the total stone in their storage
    int bin[3][7]; //used for counting the number of stones of bins in each side.
    int extraMove,captureStone;
public:
    Mancala()
    {
        extraMove=0,captureStone=0;
        home_position[1]=0,home_position[2]=0;
        for(int i=1; i<=2; i++)
            for(int j=1; j<=6; j++)
                bin[i][j]=4;
    }
    pair<int,int> get_storage()
    {
        pair<int,int> storage;
        storage.first=home_position[1],storage.second=home_position[2];
        return storage;
    }
    pair<int,int> get_totalStone()
    {
        pair<int,int> tStone;
        tStone.first=0,tStone.second=0;
        for(int i=1; i<=6; i++)
            tStone.first+=bin[1][i],tStone.second+=bin[2][i];
        return tStone;
    }
    int get_extraMove()
    {
        return extraMove;
    }
    int get_captureStone()
    {
        return captureStone;
    }
    int get_StoneFrombin(int p,int i) // p means which player and i means which bin
    {
        return bin[p][i];
    }
    Mancala get_gameFrame() // this will copy the mancala's gameframe
    {
        Mancala gameFrame;
        gameFrame.extraMove=this->extraMove,gameFrame.captureStone=this->captureStone;
        gameFrame.home_position[1]=this->home_position[1],gameFrame.home_position[2]=this->home_position[2];
        for(int i=1; i<=2; i++)
            for(int j=1; j<=6; j++)
                gameFrame.bin[i][j]=this->bin[i][j];
        return gameFrame;
    }
    void print_gameFrame()
    {
        cout<<"\t\t";
        for(int i=6; i>=1; i--)
            cout<<"<<"<<i<<">>"<<"\t";
        cout<<endl<<"\t\t";
        for(int i=6; i>=1; i--)
            cout<<"  "<<bin[1][i]<<"  "<<"\t";
        cout<<endl<<"\t"<<home_position[1]<<"(P1)";
        cout<<"\t\t\t\t\t\t          "<<home_position[2]<<"(P2)"<<endl<<"\t\t";
        for(int i=1; i<=6; i++)
            cout<<"  "<<bin[2][i]<<"  "<<"\t";
        cout<<endl<<"\t\t";
        for(int i=1; i<=6; i++)
            cout<<"<<"<<i<<">>"<<"\t";
        cout<<endl<<endl<<endl<<endl;
    }
    int game_terminate()
    {
        int rem_stone1=0,rem_stone2=0;
        for(int i=1; i<=6; i++)
            rem_stone1+=bin[1][i],rem_stone2+=bin[2][i];
        if(rem_stone1==0||rem_stone2==0)
            return 1; // game is terminated
        return 0;
    }
    int winner()
    {
        int collected_stone1=home_position[1],collected_stone2=home_position[2];
        for(int i=1; i<=6; i++)
            collected_stone1+=bin[1][i],collected_stone2+=bin[2][i];
        if(collected_stone1!=home_position[1] || collected_stone2!=home_position[2])
        {
            for(int i=1; i<=6; i++)
                bin[1][i]=0,bin[2][i]=0;
            home_position[1]=collected_stone1,home_position[2]=collected_stone2;
        }
        if(collected_stone1>collected_stone2)
            return 1;
        else if(collected_stone1<collected_stone2)
            return 2;
        else
            return 0;
    }
    int play(int p,int b) //p means which player(1 or 2) and b means which bin(1 to 6)
    {
        int stone=bin[p][b];
        bin[p][b]=0;
        int current_bin=b+1,whose_move=p,ret=p; //current bin means from which bin the stone will be started to distribute, whose_move means the player who is distributed the stone, ret means who will get the next move and ret is initially set to current player but the initialization is not important
        while(stone!=0)
        {
            if(current_bin<=6)
            {
                bin[p][current_bin]++,stone--;
                if(stone==0&&bin[p][current_bin]==1&&p==whose_move) //this means that the player who is in the role of distributed the stone ended the distribution by giving the last stone to his one of empty bin that means he capture the all stone from his bin and the opposite's bin
                {
                    home_position[p]+=(bin[p][current_bin]+bin[(p%2==0)?1:2][7-current_bin]);
                    captureStone+=(bin[p][current_bin]+bin[(p%2==0)?1:2][7-current_bin]);
                    bin[p][current_bin]=0,bin[(p%2==0)?1:2][7-current_bin]=0;
                }
                current_bin++;
            }
            else
            {
                if(p==whose_move)
                {
                    home_position[p]++,stone--;
                    if(stone==0)
                    {
                        extraMove++;
                        return ret; // the current player gain a additional move for giving the last stone in his storage
                    }
                }
                current_bin=1, p=(p%2==0)?1:2; // set the player's side and the bin number for the next distribution of stone
            }
        }
        return (ret%2==0)?1:2;
    }
};
pair<int,int> MIN(int player,Mancala gameFrame,int depth,int alpha,int beta,int hp1,int hp2,int w1,int w2,int w3,int w4);
pair<int,int> MAX(int player,Mancala gameFrame,int depth,int alpha,int beta,int hp1,int hp2,int w1,int w2,int w3,int w4);
int h1(int p,Mancala game_frame)
{
    pair<int,int> storage=game_frame.get_storage();
    if(p==1)
        return storage.first-storage.second;
    else
        return storage.second-storage.first;
}
int h2(int p,Mancala game_frame,int w1,int w2)
{
    pair<int,int> storage=game_frame.get_storage(), tStone=game_frame.get_totalStone();
    if(p==1)
        return w1*(storage.first-storage.second)+w2*(tStone.first-tStone.second);
    else
        return w1*(storage.second-storage.first)+w2*(tStone.second-tStone.first);
}
int h3(int p,Mancala game_frame,int w1,int w2,int w3)
{
    pair<int,int> storage=game_frame.get_storage(), tStone=game_frame.get_totalStone();
    if(p==1)
        return w1*(storage.first-storage.second)+w2*(tStone.first-tStone.second)+w3*game_frame.get_extraMove();
    else
        return w1*(storage.second-storage.first)+w2*(tStone.second-tStone.first)+w3*game_frame.get_extraMove();
}
int h4(int p,Mancala game_frame,int w1,int w2,int w3,int w4)
{
    pair<int,int> storage=game_frame.get_storage(), tStone=game_frame.get_totalStone();
    if(p==1)
        return w1*(storage.first-storage.second)+w2*(tStone.first-tStone.second)+w3*game_frame.get_extraMove()+w4*game_frame.get_captureStone();
    else
        return w1*(storage.second-storage.first)+w2*(tStone.second-tStone.first)+w3*game_frame.get_extraMove()+w4*game_frame.get_captureStone();
}
int heuristics_value(int player,Mancala gameFrame,int hp1,int hp2,int w1,int w2,int w3,int w4)
{
    if(player==1)
    {
        if(hp1==1)
            return h1(player,gameFrame);
        else if(hp1==2)
            return h2(player,gameFrame,w1,w2);
        else if(hp1==3)
            return h3(player,gameFrame,w1,w2,w3);
        return h4(player,gameFrame,w1,w2,w3,w4);
    }
    else
    {
        if(hp2==1)
            return h1(player,gameFrame);
        else if(hp2==2)
            return h2(player,gameFrame,w1,w2);
        else if(hp2==3)
            return h3(player,gameFrame,w1,w2,w3);
        return h4(player,gameFrame,w1,w2,w3,w4);
    }
}
pair<int,int> MIN(int player,Mancala gameFrame,int depth,int alpha,int beta,int hp1,int hp2,int w1,int w2,int w3,int w4)
{
    if(gameFrame.game_terminate()||depth==0)
        return make_pair(heuristics_value(player,gameFrame,hp1,hp2,w1,w2,w3,w4), 0);
    pair<int,int> alpha_beta=make_pair(INT_MAX, 0);
    for(int i=1; i<=6; i++)
    {
        Mancala tmp=gameFrame.get_gameFrame();
        if(tmp.get_StoneFrombin(player,i)!=0)
        {
            int p=tmp.play(player,i);
            pair<int,int> abp;//alpha beta pair
            if(p==player)
                abp=MIN(p,tmp,depth-1,alpha,beta,hp1,hp2,w1,w2,w3,w4);
            else
                abp=MAX(p,tmp,depth-1,alpha,beta,hp1,hp2,w1,w2,w3,w4);
            if(alpha_beta.first>abp.first)
                alpha_beta.first=abp.first, alpha_beta.second=i;
            if(alpha_beta.first<=alpha)
                return alpha_beta;
            beta=min(beta,alpha_beta.first);
        }
    }
    return alpha_beta;
}
pair<int,int> MAX(int player,Mancala gameFrame,int depth,int alpha,int beta,int hp1,int hp2,int w1,int w2,int w3,int w4)
{
    if(gameFrame.game_terminate()||depth==0)
        return make_pair(heuristics_value(player,gameFrame,hp1,hp2,w1,w2,w3,w4), 0);
    pair<int,int> alpha_beta=make_pair(INT_MIN, 0);
    for(int i=1; i<=6; i++)
    {
        Mancala tmp=gameFrame.get_gameFrame();
        if(tmp.get_StoneFrombin(player,i)!=0)
        {
            int p=tmp.play(player,i); // p means who get the next move
            pair<int,int> abp;//alpha beta pair
            if(p==player)
                abp=MAX(p,tmp,depth-1,alpha,beta,hp1,hp2,w1,w2,w3,w4);
            else
                abp=MIN(p,tmp,depth-1,alpha,beta,hp1,hp2,w1,w2,w3,w4);
            if(alpha_beta.first<abp.first)
                alpha_beta.first=abp.first, alpha_beta.second=i;
            if(alpha_beta.first>=beta)
                return alpha_beta;
            alpha=max(alpha,alpha_beta.first);
        }
    }
    return alpha_beta;
}
int Minimax(int player,Mancala gameFrame,int depth,int hp1,int hp2,int w1,int w2,int w3,int w4)
{
    pair<int,int> alpha_beta=MAX(player,gameFrame,depth,INT_MIN,INT_MAX,hp1,hp2,w1,w2,w3,w4);
    return alpha_beta.second;
}
int getWinner(Mancala gameFrame)
{
    int w=gameFrame.winner();
    gameFrame.print_gameFrame();
    if(w==1)
        cout<<"Player 1 is the winner"<<endl<<endl<<endl;
    else if(w==2)
        cout<<"Player 2 is the winner"<<endl<<endl<<endl;
    else
        cout<<"Draw!"<<endl<<endl<<endl;
    return w;
}

int main()
{
    cout<<"It is a two player game."<<endl<<endl<<"It can be played between : "<<endl<<endl<<"1. Player 1(Computer) vs Player 2(Computer)"<<endl<<endl<<"2. Player 1(Computer) vs Player 2(Human)"<<endl<<endl<<"3. Player 1(Human) vs Player 2(Computer)"<<endl<<endl<<"4. Player 1 (Human) vs Player 2 (Human)"<<endl<<endl<<"Enter the index 1-4 for selecting the playing method"<<endl<<endl;
    int method,playerType[2],d;
    cin>>method;
    if(method==1)
        playerType[1]=1,playerType[2]=1; // 1 for computer and 2 for human
    else if(method==2)
        playerType[1]=1,playerType[2]=2;
    else if(method==3)
        playerType[1]=2,playerType[2]=1;
    else
        playerType[1]=2,playerType[2]=2;
    cout<<endl<<endl<<"Enter a integer that represents the depth limit for cutoff test:"<<endl<<endl;
    cin>>d;
    cout<<endl<<endl;
    cout<<"The available four heuristics is:"<<endl<<endl<<"heuristic-1: The evaluation function is\n(stones_in_my_storage – stones_in_opponents_storage)"<<endl<<endl<<"heuristic-2: The evaluation function is\nW1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –stones_on_opponents_side)"<<endl<<endl<<"heuristic-3: The evaluation function is\nW1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –stones_on_opponents_side) + W3 * (additional_move_earned)"<<endl<<endl<<"heuristic-4: The evaluation function is\nW1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –stones_on_opponents_side) + W3 * (additional_move_earned) + W4 * (stones_captured)"<<endl<<endl<<endl<<endl;
    cout<<"Choose the heuristic for player1:"<<endl<<endl;
    int hp1,hp2;
    cin>>hp1;
    cout<<endl<<endl<<"Choose the heuristic for player2:"<<endl<<endl;
    cin>>hp2;
    cout<<endl<<endl;
    cout<<"Enter the 4 constant W1,W2,W3,W4 used for heuristic."<<endl<<endl;
    int w1,w2,w3,w4;
    cout<<"W1 : ", cin>>w1, cout<<endl <<"W2 : ", cin>>w2, cout<<endl <<"W3 : ", cin>>w3, cout<<endl <<"W4 : ", cin>>w4, cout<<endl;
    Mancala gameFrame;
    cout<<"The initial game frame looks like : "<<endl<<endl;
    gameFrame.print_gameFrame();
    int player=1;
    while(1)
    {
        if(playerType[player]==1) // computer
        {
            int bin=Minimax(player,gameFrame,d,hp1,hp2,w1,w2,w3,w4);
            if(bin==0)
            {
                getWinner(gameFrame);
                return 0;
            }
            cout<< "Player " <<player <<" moves the stone from the bin "<< bin <<" :" <<endl<<endl;
            player=gameFrame.play(player,bin);
            gameFrame.print_gameFrame();
        }
        else if(playerType[player]==2) // human
        {
            cout<<"Choose the bin to distribute the stone from that bin ( Player "<<player<<" )"<<endl<<endl;
            int bin;
            cin>>bin;
            cout<<endl<< "Player " <<player <<" moves the stone from the bin "<< bin <<endl<<endl;
            player=gameFrame.play(player,bin);
            gameFrame.print_gameFrame();
            if(gameFrame.game_terminate())
            {
                getWinner(gameFrame);
                return 0;
            }
        }
    }
    return 0;
}

/*
int main()
{
    cout<<"The available four heuristics is:"<<endl<<endl<<"heuristic-1: The evaluation function is\n(stones_in_my_storage – stones_in_opponents_storage)"<<endl<<endl<<"heuristic-2: The evaluation function is\nW1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –stones_on_opponents_side)"<<endl<<endl<<"heuristic-3: The evaluation function is\nW1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –stones_on_opponents_side) + W3 * (additional_move_earned)"<<endl<<endl<<"heuristic-4: The evaluation function is\nW1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –stones_on_opponents_side) + W3 * (additional_move_earned) + W4 * (stones_captured)"<<endl<<endl<<endl<<endl;
    int d,hp1,hp2,w1,w2,w3,w4;
    srand(time(0));
    for(int i=1; i<=3; i++)
    {
        for(int j=i+1; j<=4; j++)
        {
            int avg1=0,avg2=0;
            for(int k=1; k<=2; k++)
            {
                if(k==1)
                    hp1=i,hp2=j;
                else
                    hp1=j,hp2=i;
                int p1win=0,p2win=0;
                for(int i=1; i<=100; i++)
                {
                    Mancala gameFrame;
                    int player=1;
                    d=rand()%7,w1=rand()%97,w2=rand()%97,w3=rand()%97,w4=rand()%97;
                    int gameEnd=0;
                    while(1)
                    {
                        int bin=Minimax(player,gameFrame,d,hp1,hp2,w1,w2,w3,w4);
                        if(bin==0)
                        {
                            int w=gameFrame.winner();
                            if(w==1)
                                p1win++;
                            else if(w==2)
                                p2win++;
                            gameEnd=1;
                        }
                        player=gameFrame.play(player,bin);
                        if(gameEnd==1)
                        {
                            break;
                        }
                    }
                }
                cout<<"Heuristics "<<hp1<<" vs Heuristics "<<hp2<<" : ";
                cout<<"\t"<<p1win<<"\t"<<p2win<<endl;
                if(k==1)
                    avg1+=p1win,avg2+=p2win;
                else
                    avg1+=p2win,avg2+=p1win;
            }
            cout<<endl<<"Finally, "<<"Heuristics "<<i<<" vs Heuristics "<<j<<" : "<<avg1<<"\t"<<avg2<<endl<<endl<<endl<<endl<<endl;
        }
    }
    return 0;
}
*/
