//运算选项
bool output_in_flie=true;	//以文件形式输出

//调试开关
bool output_avg = false;	//输出转运公司统计数据


//扩展内存栈
#pragma comment(linker, "/STACK:102400000,102400000")
//O2代码编译优化
#pragma GCC optimize ("O2")
//万能头文件
#include<bits/stdc++.h>
//使用标准命名空间
using namespace std;


//常用标准数据类型
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define fi first
#define se second

typedef map<int,int> mii;
typedef map<ll,ll> mll;
typedef multiset<int> msii;
typedef multiset<ll> msll;
typedef set<int> sii;
typedef set<ll> sll;
typedef set<pii> spii;
typedef set<pll> spll;
typedef vector<int> vii;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
#define it_ iterator
#define r_it_ reverse_iterator




//常用代码块
#define putt(x) cerr<<#x<<" = "<<(x)<<endl;
#define MAX 100007
const double MOD = 1000000007;	//模数,常用的还有 998244353;
const double eps = 1e-8;	//保留6位小数的精度,保留k位小数时一般取1e-(k+2);


//系数列表
bool using_trust = true;
double power_trust = 10;
bool using_sumup = true;
double power_sumup1 = 100;
double power_sumup2 = 150;


//题中常量
#define MAX_S 403	//供货商上限
#define MAX_W 241	//周序号上限
#define MAX_T 9		//转运公司上限



struct transport_
{
	int num;
	double dam[MAX_W];
	double dam_avg[50];
	double tot_avg;
	int bill[50];
	int tot_bill;
	int order[25];
	int order_detail[25][MAX_S];
}tsp[MAX_T];

vector<vpll>plan(25);


int main()
{
	//读写同步优化
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
//====================================input
	ifstream input_dam,input_plan;
	input_dam.open("dam.txt");
	input_plan.open("outputA.txt");
	if(!input_dam||!input_plan)
		return -1;
	if(output_in_flie)
		freopen("outputB.txt","w",stdout);

	for(int i=1;i<MAX_T;i++)
	{
		string str;
		input_dam>>str;
		for(int j=1;j<MAX_W;j++)
			input_dam>>tsp[i].dam[j];
	}


	for(int i=1;i<MAX_S;i++)
	{
		int val;
		for(int j=1;j<=24;j++)
		{
			input_plan>>val;
			if(val)plan[j].push_back({i,val});
		}
	}
	
	//调试模块：前结合MatLab绘制图线用于测评表A的正确性（已失效）
	// for(int j=1;j<=24;j++)
	// {
	// 	ll sum=0;
	// 	for(auto it:plan[j])
	// 	{
	// 		cout<<it<<"\t";
	// 		sum+=it;
	// 	}
	// 	cout<<" ( ";
	// 	cout<<sum;
	// 	cout<<" )";
	// 	cout<<endl;
	// 	cout<<endl;
	// 	cout<<endl;
	// 	// cout<<"\t";
	// }


//====================================pro1
	for(int i=1;i<MAX_T;i++)
	{
		tsp[i].num=i;
		for(int j=1;j<MAX_W;j++)
		{
			int jj=(j-1)%48+1;
			tsp[i].dam_avg[jj]+=tsp[i].dam[j];
			if(tsp[i].dam[j]!=0.)tsp[i].bill[jj]++;
		}
		for(int j=1;j<=48;j++)
		{
			tsp[i].tot_avg+=tsp[i].dam[j];
			tsp[i].tot_bill+=tsp[i].bill[j];
		}
		tsp[i].tot_avg/=tsp[i].tot_bill;
		for(int j=1;j<=48;j++)
		{
			if(tsp[i].bill[j])tsp[i].dam_avg[j]/=tsp[i].bill[j];
			else tsp[i].dam_avg[j]=(tsp[i].dam_avg[j-1]+tsp[i].tot_avg)/2;
			if(output_avg){cerr<<i<<" , "<<j<<" - ";putt(tsp[i].dam_avg[j]);}
		}
	}





//====================================pro2
	for(int j=1;j<=24;j++)
	{
		sort(tsp+1,tsp+MAX_T,[&](transport_ a,transport_ b){return a.dam_avg[j]<b.dam_avg[j];});
		sort(plan[j].begin(),plan[j].end(),[&](pll a,pll b){return a.se>b.se;});
		double had=0;
		for(auto it:plan[j])
		{
			for(int i=1;i<4;i++)
			{
				if(tsp[i].order[j]+it.se<=6000)
				{
					tsp[i].order[j]+=it.se;
					tsp[i].order_detail[j][it.fi]+=it.se;
					it.se=0;
					break;
				}
			}
			if(it.se==0)continue;
			// cerr<<it.se<<endl;
			//优先考虑放在当前周排名前四的转运公司
			for(int i=1;it.se&&i<=4;i++)
			{
				if(tsp[i].order[j]+it.se<=6000)
				{
					tsp[i].order[j]+=it.se;
					tsp[i].order_detail[j][it.fi]+=it.se;
					it.se=0;
					break;
				}
				if(tsp[i].order[j]<6000)
				{
					it.se-=6000-tsp[i].order[j];
					tsp[i].order_detail[j][it.fi]+=6000-tsp[i].order[j];
					tsp[i].order[j]=6000;
				}
			}
			//如果订单还有剩余的材料需要转运则给额外的转运公司下订单
			//虽然根据数据分析这一点可以判定其不会成立
			if(it.se!=0)
			{
				for(int i=1;i<MAX_T;i++)
				{
					if(tsp[i].order[j]+it.se<=6000)
					{
						tsp[i].order[j]+=it.se;
						tsp[i].order_detail[j][it.fi]+=it.se;
						it.se=0;
						break;
					}
				}
				for(int i=1;it.se&&i<MAX_T;i++)
				{
					if(tsp[i].order[j]+it.se<=6000)
					{
						tsp[i].order[j]+=it.se;
						tsp[i].order_detail[j][it.fi]+=it.se;
						it.se=0;
						break;
					}
					if(tsp[i].order[j]<6000)
					{
						it.se-=6000-tsp[i].order[j];
						tsp[i].order_detail[j][it.fi]+=6000-tsp[i].order[j];
						tsp[i].order[j]=6000;
					}
				}
			}
		}
		
	}




//====================================anss_2B
	sort(tsp+1,tsp+MAX_T,[&](transport_ a,transport_ b){return a.num<b.num;});
	for(int i=1;i<MAX_S;i++)
	{
		for(int j=1;j<=24;j++)
		{
			for(int k=1;k<MAX_T;k++)
			{
				cout<<(j==1&&k==1?"":"\t")<<tsp[k].order_detail[j][i];
			}
		}
		cout<<endl;
	}




	return 0;
}
/*

	1-1、通过表2,补上其中0处的数据
		一年为周期48周->平均值
	1-2、通过表A的计划，分配转运材料
	2、在出结果时排转运公司优先级
	3、一家公司的供货大于六千就要分给下一次序的转运公司

*/
