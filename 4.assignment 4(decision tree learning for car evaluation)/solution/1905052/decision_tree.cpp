#include<bits/stdc++.h>
using namespace std;

vector<vector<string>>training_data;
vector<vector<string>>testing_data;
string dec1,dec2,dec3,dec4;

struct vertex
{
    string name;
    string attribute;
    int leaf;
    string decision;
    vector<vertex*> children;
    vertex(string n,string a,int l,string d)
    {
        name=n;
        attribute=a;
        leaf=l;
        decision=d;
    }
};

void insert1(vertex* parent,vertex* newNode)
{
    parent->children.push_back(newNode);
}

void depthFirstTraversal(vertex* root)
{
    if (root == nullptr)
        return;
    for (vertex* child : root->children)
    {
        depthFirstTraversal(child);
    }
}

string testing(vertex* root,vector<string>vv);
double entropy(double q,int check)
{
    if(check==0)
        return 0.0;
    double result;
    result=(q*log2(q));
    result*=(-1);
    return result;
}

double parent_gain(vector<vector<string>>training_data1)
{
    int unacc=0,acc=0,good=0,vgood=0;
    for(int i=0; i<training_data1.size(); i++)
    {
        if(training_data1[i][6]=="unacc")
            unacc++;
        else if(training_data1[i][6]=="acc")
            acc++;
        else if(training_data1[i][6]=="good")
            good++;
        else if(training_data1[i][6]=="vgood")
            vgood++;
    }
    int sum1=unacc+acc+good+vgood;
    double tmp1=entropy((unacc*1.0)/sum1,unacc)+entropy((acc*1.0)/sum1,acc)+entropy((good*1.0)/sum1,good)+entropy((vgood*1.0)/sum1,vgood);
    return tmp1;
}

double child_gain(string str1,string str2,string str3,string str4,int j,int attr,vector<vector<string>>training_data1)
{
    int unacc1=0,acc1=0,good1=0,vgood1=0;
    int unacc2=0,acc2=0,good2=0,vgood2=0;
    int unacc3=0,acc3=0,good3=0,vgood3=0;
    int unacc4=0,acc4=0,good4=0,vgood4=0;
    int f1=0,f2=0,f3=0,f4=0;

    for(int i=0; i<training_data1.size(); i++)
    {
        if(training_data1[i][j]==str1)
        {
            f1++;
            if(training_data1[i][6]=="unacc")
                unacc1++;
            else if(training_data1[i][6]=="acc")
                acc1++;
            else if(training_data1[i][6]=="good")
                good1++;
            else if(training_data1[i][6]=="vgood")
                vgood1++;
        }
        else if(training_data1[i][j]==str2)
        {
            f2++;
            if(training_data1[i][6]=="unacc")
                unacc2++;
            else if(training_data1[i][6]=="acc")
                acc2++;
            else if(training_data1[i][6]=="good")
                good2++;
            else if(training_data1[i][6]=="vgood")
                vgood2++;
        }
        else if(training_data1[i][j]==str3)
        {
            f3++;
            if(training_data1[i][6]=="unacc")
                unacc3++;
            else if(training_data1[i][6]=="acc")
                acc3++;
            else if(training_data1[i][6]=="good")
                good3++;
            else if(training_data1[i][6]=="vgood")
                vgood3++;
        }
        else if(attr==4&&training_data1[i][j]==str4)
        {
            f4++;
            if(training_data1[i][6]=="unacc")
                unacc4++;
            else if(training_data1[i][6]=="acc")
                acc4++;
            else if(training_data1[i][6]=="good")
                good4++;
            else if(training_data1[i][6]=="vgood")
                vgood4++;
        }
    }
    int sum1;
    double e1,e2,e3,e4;
    sum1=unacc1+acc1+good1+vgood1;
    e1=entropy((unacc1*1.0)/sum1,unacc1)+entropy((acc1*1.0)/sum1,acc1)+entropy((good1*1.0)/sum1,good1)+entropy((vgood1*1.0)/sum1,vgood1);
    sum1=unacc2+acc2+good2+vgood2;
    e2=entropy((unacc2*1.0)/sum1,unacc2)+entropy((acc2*1.0)/sum1,acc2)+entropy((good2*1.0)/sum1,good2)+entropy((vgood2*1.0)/sum1,vgood2);
    sum1=unacc3+acc3+good3+vgood3;
    e3=entropy((unacc3*1.0)/sum1,unacc3)+entropy((acc3*1.0)/sum1,acc3)+entropy((good3*1.0)/sum1,good3)+entropy((vgood3*1.0)/sum1,vgood3);
    sum1=unacc4+acc4+good4+vgood4;
    if(attr==4)
        e4=entropy((unacc4*1.0)/sum1,unacc4)+entropy((acc4*1.0)/sum1,acc4)+entropy((good4*1.0)/sum1,good4)+entropy((vgood4*1.0)/sum1,vgood4);
    int f=f1+f2+f3+f4;

    double g1=((f1*e1*1.0)/f) + ((f2*e2*1.0)/f) + ((f3*e3*1.0)/f) ;
    if(attr==4)
        g1+=((f4*e4*1.0)/f);

    return g1;
}

void checking(string str1,string str2,string str3,string str4,int j,int attr,vector<vector<string>>training_data1)
{
    int unacc1=0,acc1=0,good1=0,vgood1=0, unacc2=0,acc2=0,good2=0,vgood2=0, unacc3=0,acc3=0,good3=0,vgood3=0, unacc4=0,acc4=0,good4=0,vgood4=0;
    int f1=0,f2=0,f3=0,f4=0;

    for(int i=0; i<training_data1.size(); i++)
    {
        if(training_data1[i][j]==str1)
        {
            f1++;
            if(training_data1[i][6]=="unacc")
                unacc1++;
            else if(training_data1[i][6]=="acc")
                acc1++;
            else if(training_data1[i][6]=="good")
                good1++;
            else if(training_data1[i][6]=="vgood")
                vgood1++;
        }
        else if(training_data1[i][j]==str2)
        {
            f2++;
            if(training_data1[i][6]=="unacc")
                unacc2++;
            else if(training_data1[i][6]=="acc")
                acc2++;
            else if(training_data1[i][6]=="good")
                good2++;
            else if(training_data1[i][6]=="vgood")
                vgood2++;
        }
        else if(training_data1[i][j]==str3)
        {
            f3++;
            if(training_data1[i][6]=="unacc")
                unacc3++;
            else if(training_data1[i][6]=="acc")
                acc3++;
            else if(training_data1[i][6]=="good")
                good3++;
            else if(training_data1[i][6]=="vgood")
                vgood3++;
        }
        else if(attr==4&&training_data1[i][j]==str4)
        {
            f4++;
            if(training_data1[i][6]=="unacc")
                unacc4++;
            else if(training_data1[i][6]=="acc")
                acc4++;
            else if(training_data1[i][6]=="good")
                good4++;
            else if(training_data1[i][6]=="vgood")
                vgood4++;
        }
    }

    dec1="null",dec2="null",dec3="null",dec4="null";
    int sum1=unacc1+acc1+good1+vgood1;
    if(sum1==unacc1)
        dec1="unacc";
    else if(sum1==acc1)
        dec1="acc";
    else if(sum1==good1)
        dec1="good";
    else if(sum1==vgood1)
        dec1="vgood";

    sum1=unacc2+acc2+good2+vgood2;
    if(sum1==unacc2)
        dec2="unacc";
    else if(sum1==acc2)
        dec2="acc";
    else if(sum1==good2)
        dec2="good";
    else if(sum1==vgood2)
        dec2="vgood";

    sum1=unacc3+acc3+good3+vgood3;
    if(sum1==unacc3)
        dec3="unacc";
    else if(sum1==acc3)
        dec3="acc";
    else if(sum1==good3)
        dec3="good";
    else if(sum1==vgood3)
        dec3="vgood";

    if(attr==4)
    {
        sum1=unacc4+acc4+good4+vgood4;
        if(sum1==unacc4)
            dec4="unacc";
        else if(sum1==acc4)
            dec4="acc";
        else if(sum1==good4)
            dec4="good";
        else if(sum1==vgood4)
            dec4="vgood";
    }
}

class Node
{
    string rv , attribute , decision;
    vector<Node>vect;
    int isleaf=0 , buy=0 , maint=0 , door=0 , person=0 , lug=0 , safe=0;

    vector<vector<string>> vec;

public:
    void set_buy(int s)
    {
        buy=s;
    }
    int get_buy()
    {
        return buy;
    }
    void set_maint(int s)
    {
        maint=s;
    }
    int get_maint()
    {
        return maint;
    }
    void set_door(int s)
    {
        door=s;
    }
    int get_door()
    {
        return door;
    }
    void set_person(int s)
    {
        person=s;
    }
    int get_person()
    {
        return person;
    }
    void set_lug(int s)
    {
        lug=s;
    }
    int get_lug()
    {
        return lug;
    }
    void set_safe(int s)
    {
        safe=s;
    }
    int get_safe()
    {
        return safe;
    }
    void set_rv(string rv)
    {
        this->rv=rv;
    }
    string get_rv()
    {
        return rv;
    }
    void set_attribute(string attribute)
    {
        this->attribute=attribute;
    }
    string get_attribute()
    {
        return attribute;
    }
    void add_child(Node node)
    {
        vect.push_back(node);
    }
    vector<Node> get_children()
    {
        return vect;
    }
    void set_isleaf(int l)
    {
        isleaf=l;
    }
    int get_leaf()
    {
        return isleaf;
    }
    void set_decision(string dec)
    {
        decision=dec;
    }
    string get_decision()
    {
        return decision;
    }
    void set_data(vector<vector<string>> vec)
    {
        this->vec = vec;
    }
    vector<vector<string>> get_data()
    {
        return vec;
    }
};

void dfs(Node nod,vertex* rt)
{
    vector<Node> nodes=nod.get_children();
    for(int i=0; i<nodes.size(); i++)
    {
        Node node=nodes[i];
        vector<vector<string>> v=node.get_data();
        if(v.size()==0)
        {
            node.set_isleaf(1);
            vector<vector<string>> vvv=nod.get_data();
            int unacc=0,acc=0,good=0,vgood=0;
            for(int j=0; j<vvv.size(); j++)
            {
                if(vvv[j][6]=="unacc")
                    unacc++;
                else if(vvv[j][6]=="acc")
                    acc++;
                else if(vvv[j][6]=="good")
                    good++;
                else if(vvv[j][6]=="vgood")
                    vgood++;
            }
            if(unacc>acc&&unacc>good&&unacc>vgood)
                node.set_decision("unacc");
            else if(acc>unacc&&acc>good&&acc>vgood)
                node.set_decision("acc");
            else if(good>unacc&&good>acc&&good>vgood)
                node.set_decision("good");
            else
                node.set_decision("vgood");
        }

        if(node.get_buy()==1&&node.get_maint()==1&&node.get_door()==1&&node.get_person()==1&&node.get_lug()==1&&node.get_safe()==1)
        {
            node.set_isleaf(1);
            int unacc=0,acc=0,good=0,vgood=0;
            for(int j=0; j<v.size(); j++)
            {
                if(v[j][6]=="unacc")
                    unacc++;
                else if(v[j][6]=="acc")
                    acc++;
                else if(v[j][6]=="good")
                    good++;
                else if(v[j][6]=="vgood")
                    vgood++;
            }
            if(unacc>acc&&unacc>good&&unacc>vgood)
                node.set_decision("unacc");
            else if(acc>unacc&&acc>good&&acc>vgood)
                node.set_decision("acc");
            else if(good>unacc&&good>acc&&good>vgood)
                node.set_decision("good");
            else
                node.set_decision("vgood");
        }

        vertex* newNode=new vertex(node.get_rv(),node.get_attribute(),node.get_leaf(),node.get_decision());
        insert1(rt,newNode);

        if(node.get_leaf()==1)
            continue;

        string name="null";
        double ans=0;
        double g1=parent_gain(v);

        if(node.get_buy()==0)
        {
            double c1=child_gain("vhigh","high","med","low",0,4,v);
            double cc1=g1-c1;
            ans=cc1;
            name="buying";
        }
        if(node.get_maint()==0)
        {
            double c2=child_gain("vhigh","high","med","low",1,4,v);
            double cc2=g1-c2;
            if(ans<cc2)
            {
                ans=cc2;
                name="maint";
            }
        }
        if(node.get_door()==0)
        {
            double c3=child_gain("2","3","4","5more",2,4,v);
            double cc3=g1-c3;
            if(ans<cc3)
            {
                ans=cc3;
                name="doors";
            }
        }
        if(node.get_person()==0)
        {
            double c4=child_gain("2","4","more","null",3,3,v);
            double cc4=g1-c4;
            if(ans<cc4)
            {
                ans=cc4;
                name="persons";
            }
        }
        if(node.get_lug()==0)
        {
            double c5=child_gain("small","med","big","null",4,3,v);
            double cc5=g1-c5;
            if(ans<cc5)
            {
                ans=cc5;
                name="lug_boot";
            }
        }
        if(node.get_safe()==0)
        {
            double c6=child_gain("low","med","high","null",5,3,v);
            double cc6=g1-c6;
            if(ans<cc6)
            {
                ans=cc6;
                name="safety";
            }
        }

        string attributes[] = {"buying", "maint", "doors", "persons", "lug_boot", "safety"};
        int attr_index=-1;
        for (const string &attr : attributes)
        {
            attr_index++;
            string attributes1[4];
            if(name==attr)
            {
                if(attr_index==0||attr_index==1)
                {
                    checking("vhigh", "high", "med", "low", attr_index, 4, v);
                    attributes1[0]="vhigh", attributes1[1]="high", attributes1[2]="med", attributes1[3]="low";
                }
                else if(attr_index==2)
                {
                    checking("2","3","4","5more",attr_index,4,v);
                    attributes1[0]="2", attributes1[1]="3", attributes1[2]="4", attributes1[3]="5more";
                }
                else if(attr_index==3)
                {
                    checking("2","4","more","null",attr_index,3,v);
                    attributes1[0]="2", attributes1[1]="4", attributes1[2]="more";
                }
                else if(attr_index==4)
                {
                    checking("small","med","big","null",attr_index,3,v);
                    attributes1[0]="small", attributes1[1]="med", attributes1[2]="big";
                }
                else if(attr_index==5)
                {
                    checking("low","med","high","null",attr_index,3,v);
                    attributes1[0]="low", attributes1[1]="med", attributes1[2]="high";
                }
                int k=-1;
                for (const string &attr1 : attributes1)
                {
                    k++;
                    Node tmp1;
                    tmp1.set_rv(attr);
                    tmp1.set_attribute(attr1);
                    tmp1.set_buy(node.get_buy());
                    tmp1.set_maint(node.get_maint());
                    tmp1.set_door(node.get_door());
                    tmp1.set_person(node.get_person());
                    tmp1.set_lug(node.get_lug());
                    tmp1.set_safe(node.get_safe());
                    if(attr_index==0)
                        tmp1.set_buy(1);
                    else if(attr_index==1)
                        tmp1.set_maint(1);
                    else if(attr_index==1)
                        tmp1.set_door(1);
                    else if(attr_index==1)
                        tmp1.set_person(1);
                    else if(attr_index==1)
                        tmp1.set_lug(1);
                    else if(attr_index==1)
                        tmp1.set_safe(1);
                    if(k==0&&dec1!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec1);
                    }
                    if(k==1&&dec2!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec2);
                    }
                    if(k==2&&dec3!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec3);
                    }
                    if(k==3&&dec4!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec4);
                    }

                    vector<vector<string>> v1;
                    int cntt=0;
                    for(int i=0; i<v.size(); i++)
                    {
                        if(v[i][attr_index]==attr1)
                            cntt++;
                    }
                    v1.resize(cntt);
                    int j=0;
                    for(int i=0; i<v.size(); i++)
                    {
                        if(v[i][attr_index]==attr1)
                        {
                            v1[j].push_back(v[i][0]), v1[j].push_back(v[i][1]), v1[j].push_back(v[i][2]), v1[j].push_back(v[i][3]);
                            v1[j].push_back(v[i][4]), v1[j].push_back(v[i][5]), v1[j].push_back(v[i][6]);
                            j++;
                        }
                    }
                    tmp1.set_data(v1);
                    node.add_child(tmp1);
                }
            }
        }

        dfs(node,newNode);
    }
}

int main()
{
    double accuracy=0.0;
    double results[20];
    int rs=0;
    ifstream inputFile("input.txt");
    vector<string>vec;
    string line;
    while (getline(inputFile, line))
        vec.push_back(line);

    random_device rd;
    mt19937 generator(rd());
    double per=0.8;
    for(int ii=0; ii<20; ii++)
    {
        per-= 0.008;
        shuffle(vec.begin(), vec.end(), generator);

        int total_size= vec.size();
        int break_point= total_size * per;

        training_data.resize(break_point);
        testing_data.resize(total_size - break_point);
        for(int i=0; i<break_point; i++)
        {
            line=vec[i];
            istringstream iss(line);
            string att;
            while (getline(iss, att, ','))
                training_data[i].push_back(att);
        }

        for(int i=break_point,j=0; i<vec.size(); i++,j++)
        {
            line=vec[i];
            istringstream iss(line);
            string att;
            while (getline(iss, att, ','))
                testing_data[j].push_back(att);
        }

        Node root;
        root.set_rv("root");
        string attributes[] = {"buying", "maint", "doors", "persons", "lug_boot", "safety"};
        string name;
        double ans;
        int attr_index=-1;
        for (const string &attr : attributes)
        {
            attr_index++;
            double gain = parent_gain(training_data);
            double child_gain_value;
            if(attr_index==0||attr_index==1)
                child_gain_value = child_gain("vhigh", "high", "med", "low", attr_index, 4, training_data);
            else if(attr_index==2)
                child_gain_value = child_gain("2","3","4","5more",attr_index,4,training_data);
            else if(attr_index==3)
                child_gain_value = child_gain("2","4","more","null",attr_index,3,training_data);
            else if(attr_index==4)
                child_gain_value = child_gain("small","med","big","null",attr_index,3,training_data);
            else if(attr_index==5)
                child_gain_value = child_gain("low","med","high","null",attr_index,3,training_data);
            double cc = gain - child_gain_value;
            if (attr_index==0||cc > ans)
            {
                ans = cc;
                name = attr;
            }
        }

        attr_index=-1;
        for (const string &attr : attributes)
        {
            attr_index++;
            string attributes1[4];
            if(name==attr)
            {
                if(attr_index==0||attr_index==1)
                {
                    checking("vhigh", "high", "med", "low", attr_index, 4, training_data);
                    attributes1[0]="vhigh", attributes1[1]="high", attributes1[2]="med", attributes1[3]="low";
                }
                else if(attr_index==2)
                {
                    checking("2","3","4","5more",attr_index,4,training_data);
                    attributes1[0]="2", attributes1[1]="3", attributes1[2]="4", attributes1[3]="5more";
                }
                else if(attr_index==3)
                {
                    checking("2","4","more","null",attr_index,3,training_data);
                    attributes1[0]="2", attributes1[1]="4", attributes1[2]="more";
                }
                else if(attr_index==4)
                {
                    checking("small","med","big","null",attr_index,3,training_data);
                    attributes1[0]="small", attributes1[1]="med", attributes1[2]="big";
                }
                else if(attr_index==5)
                {
                    checking("low","med","high","null",attr_index,3,training_data);
                    attributes1[0]="low", attributes1[1]="med", attributes1[2]="high";
                }
                int k=-1;
                for (const string &attr1 : attributes1)
                {
                    k++;
                    Node tmp1;
                    tmp1.set_rv(attr);
                    tmp1.set_attribute(attr1);
                    if(attr_index==0)
                        tmp1.set_buy(1);
                    else if(attr_index==1)
                        tmp1.set_maint(1);
                    else if(attr_index==1)
                        tmp1.set_door(1);
                    else if(attr_index==1)
                        tmp1.set_person(1);
                    else if(attr_index==1)
                        tmp1.set_lug(1);
                    else if(attr_index==1)
                        tmp1.set_safe(1);
                    if(k==0&&dec1!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec1);
                    }
                    if(k==1&&dec2!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec2);
                    }
                    if(k==2&&dec3!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec3);
                    }
                    if(k==3&&dec4!="null")
                    {
                        tmp1.set_isleaf(1);
                        tmp1.set_decision(dec4);
                    }

                    vector<vector<string>> v1;
                    int cntt=0;
                    for(int i=0; i<training_data.size(); i++)
                    {
                        if(training_data[i][attr_index]==attr1)
                            cntt++;
                    }
                    v1.resize(cntt);
                    int j=0;
                    for(int i=0; i<training_data.size(); i++)
                    {
                        if(training_data[i][attr_index]==attr1)
                        {
                            v1[j].push_back(training_data[i][0]), v1[j].push_back(training_data[i][1]), v1[j].push_back(training_data[i][2]), v1[j].push_back(training_data[i][3]);
                            v1[j].push_back(training_data[i][4]), v1[j].push_back(training_data[i][5]), v1[j].push_back(training_data[i][6]);
                            j++;
                        }
                    }
                    tmp1.set_data(v1);

                    root.add_child(tmp1);
                }
            }
        }

        vertex* rt=new vertex("root","null",0,"null");
        dfs(root,rt);

        depthFirstTraversal(rt);

        int total=0,same=0;
        for(int i=0; i<testing_data.size(); i++)
        {
            vector<string> vv;
            for(int j=0; j<7; j++)
                vv.push_back(testing_data[i][j]);
            string res=testing(rt,vv);
            total++;
            if(res==vv[6])
                same++;
        }
        accuracy+=(same*1.0/total)*100;
        results[rs++]=(same*1.0/total)*100;
    }
    cout<<"Accuracy : "<<(accuracy*1.0)/20<<"%"<<endl;
    double mean=(accuracy*1.0)/20;
    double sd=0.0;
    for(int i=0;i<rs;i++)
    {
        sd+=pow(abs(results[i]-mean),2);
    }
    sd=(sd*1.0)/20;
    cout<<"Standard Deviation : "<<sqrt(sd)<<endl;
    return 0;
}

string testing(vertex* root,vector<string>vv)
{
    for (vertex* child : root->children)
    {
        if(child->name=="buying"&&child->attribute==vv[0])
        {
            if(child->leaf==1)
                return child->decision;
            return testing(child,vv);
        }
        else if(child->name=="maint"&&child->attribute==vv[1])
        {
            if(child->leaf==1)
                return child->decision;
            return testing(child,vv);
        }
        else if(child->name=="doors"&&child->attribute==vv[2])
        {
            if(child->leaf==1)
                return child->decision;
            return testing(child,vv);
        }
        else if(child->name=="persons"&&child->attribute==vv[3])
        {
            if(child->leaf==1)
                return child->decision;
            return testing(child,vv);
        }
        else if(child->name=="lug_boot"&&child->attribute==vv[4])
        {
            if(child->leaf==1)
                return child->decision;
            return testing(child,vv);
        }
        else if(child->name=="safety"&&child->attribute==vv[5])
        {
            if(child->leaf==1)
                return child->decision;
            return testing(child,vv);
        }
    }
}
