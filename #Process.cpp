/*
	
	评委老师只需要选择以下两种方式对对应的题目进行验证(两种方式效果相同,推荐直接使用方法1)
		1、更改“#define SOLVE_PROBLEM_NO_ 0”(第28行)的问题编号
			默认值为	0	程序不做任何处理
			更改为	1	按照第1题的要求，同时在屏幕和outputA.txt中，输出50个最重要的供应商编号
			更改为	2	按照第2题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
			更改为	3	按照第3题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
			更改为	4	按照第4题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
		2、在不做上述更改的前提下，选择打开对应的运行模式开关(41~44行)
			将需要的开关设为	true
			将其他的开关设为	false	即可

	设置好运行模式就可以运行该程序验证数据了(该程序就会自动根据运行选项打开默认的辅助开关进行对应的运算)


	p.s.
		由于在竞赛过程中的绝大多数数据分析都是通过该程序完成的
		所以有20~30%的代码是对数据的分析过程，其中的思想在论文中有所体现
		但其依然可能会增加代码阅读的困难，还望评委老师见谅	Orz


*/



//==================方式1====(推荐)===================//
#define SOLVE_PROBLEM_NO_ 0
////可以更改为：
// #define SOLVE_PROBLEM_NO_ 1		//按照第1题的要求，同时在屏幕和outputA.txt中，输出50个最重要的供应商编号
// #define SOLVE_PROBLEM_NO_ 2		//按照第2题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
// #define SOLVE_PROBLEM_NO_ 3		//按照第3题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
// #define SOLVE_PROBLEM_NO_ 4		//按照第4题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据



//===================方式2====(亦可)==================//
//封装好的运行模式选择(推荐一次只打开一个开关)
//将需要的开关设为	true
//将其他的开关设为	false	即可
bool problem_No_1=false;		//按照第1题的要求，同时在屏幕和outputA.txt中，输出50个最重要的供应商编号
bool problem_No_2=false;		//按照第2题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
bool problem_No_3=false;		//按照第3题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据
bool problem_No_4=false;		//按照第4题的要求，在outputA.txt中输出表A的填写数据，在outputB.txt中输出表B的填写数据




/*=======================================下方就是代码全貌了============================================================*/



//可选辅助运算选项♥
bool solving_problem1_num_list=false;		//⭐输出第一问供应商S的重要性排名
bool solving_problem1_type=false;		//在输出排名的情况下配合输出材料类型
bool solving_problem1_score=false;		//⭐在不输出排名的情况下输出score列表，结合MatLab生成直观图线
bool solving_problem1_pro=false;		//在不输出排名的情况下输出pro列表
bool solving_problem1=true;			//输出第一题答案相关数据(常为true影响可忽略不计)

bool solving_problem2 = false;			//⭐输出第二问以及之后的A文件答案，在第四题中作为平滑处理的开关
bool solving_problem3 = false;			//⭐按照第三问的方式计算答案
bool trust_is_related = true;			//信任度是否和供应商评分有关(可证明应常为true)
bool finding_line=false;			//输出划线的合理估计位置
int line__ = solving_problem3?42:34;		//根据对合理估计位置的计算和matlab对于排序后score绘制的图线设置划分排名位置

bool solving_problem4 = false;			//⭐按照第四问计算答案，【自带改参】，且含一个额外参数自动求解problem4
int anss4 = 28200;				//求解最大产能的结果

bool outputA_in_file=true;			//⭐是否在文件中输出表A(默认为屏幕命令窗口输出)
bool outputB_in_file=true;			//⭐是否输出文件B(默认不输出)
bool using_pre_pro4=true;			//⭐第四问时是否预处理订单数据


//调试开关
bool outer_program = false;			//外部程序交互开关
bool debuging = false;				//部分调试代码开关
bool debug_input_ask = false;			//调试输入订货量数据
bool debug_input_get = false;			//调试输入供货量数据
bool debug_pro_1 = false;			//调试第一次处理
bool debug_output1 = false;			//输出score倒数数据
bool debug_por15 = false;			//在粗处理后输出debug数据
bool debuging_pre_pro = false;			//输出预处理后的订单数据然后直接结束程序

bool prove_cycle_bill=false;			//查看周期稳定在24周的证据



//通过计算得出的辅助列表
bool using_trust = true;			//有无计算信用分对供应商评分的影响
double power_trust = 1;				//信用分对供应商评分的重要程度
bool using_sumup = true;			//有无计算订单总数对供应商评分的重要程度
double power_sumup1 = 100;			//反映惩罚系数对供应商评分的重要程度
double power_sumup2 = 150;			//反映少宽容系数对供应商评分的重要程度
double tanxingxishu = 1.12;			//根据剩余生产力计算推的的生产弹性系数
double tanxingxishu2 = 1.50;			//根据剩余生产力计算推的的生产弹性系数(单点)



//(非)绝对排序模式
#define SCORE 1					//综合结果
#define TRUST 2					//绝对信任
#define SUMUP 3					//绝对到货
const int MODEL=SCORE;



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
typedef pair<double,double> pll;
#define fi first
#define se second
typedef vector<double> vll;
typedef vector<pii> vpii;
#define it_ iterator
#define r_it_ reverse_iterator


//常用代码块
#define putt(x) cerr<<#x<<" = "<<(x)<<endl;
#define MAX 100007
const double MOD = 1000000007;	//模数,常用的还有 998244353;
const double eps = 1e-8;		//保留6位小数的精度,保留k位小数时一般取1e-(k+2);


//题中常量
#define MAX_S 403				//供货商上限
#define MAX_W 241				//周序号上限


//供应商抽象数据结构————参数列表
//亦是整合星期资料抽象出的数据结构，与供应商结构类似
typedef struct _supplier_
{
	int num;
	char ask_material_type;				//材料类型
	char get_material_type;				//材料类型
	double bill_data[25]		={};		//一周的订单数
	double ask_data[MAX_W]		={};		//表中订货量数据
	double get_data[MAX_W]		={};		//表中供货量数据
	double ask_pre[MAX_W]		={};		//订货量前缀和
	double get_pre[MAX_W]		={};		//供货量前缀和
	double pro[MAX_W]		={};		//产能和
	double ask_sum			=0.;		//订货量总和
	double get_sum			=0.;		//供货量总和
	double pro_sum			=0.;		//产能总和
	double owe_val			=0.;		//缺省值
	double score			=0.;		//供应商评分
	double score2			=0.;		//供应商评分结果(目前是废案)
	double delta			=0.;		//未完成订单缺省材料的总和
	double bill			=0.;		//订单数
	double trust			=0.;		//征信度
}supplier_,week_;


supplier_ data[MAX_S];
//data[i]:关于S_i供应商的数据

//对于各周的数据综合数据
week_ tot;
//下面单周局部数据求和用数组
double week_ask_sum[MAX_W];
double week_get_sum[MAX_W];
//(因这两行是代码构造早期就开始使用所以并未合并入上方结构体)


//处理答案时用的辅助数组
pll anss_A[24][MAX_S];
//fi:ask订单量	se:pro转化为的生产产能


//填写表B的封装内容
namespace finish_table_B
{
	//运算选项
	bool output_in_flie=true;	//以文件形式输出

	//调试开关
	bool output_avg = false;	//输出转运公司统计数据


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
		ofstream outputB;
		input_dam.open("dam.txt");
		input_plan.open("outputA.txt");
		outputB.open("outputB.txt");
		if(!input_dam||!input_plan||!outputB)
			return -1;
		// if(output_in_flie)
		// 	freopen("outputB.txt","w",stdout);

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
		// 		outputB<<it<<"\t";
		// 		sum+=it;
		// 	}
		// 	outputB<<" ( ";
		// 	outputB<<sum;
		// 	outputB<<" )";
		// 	outputB<<endl;
		// 	outputB<<endl;
		// 	outputB<<endl;
		// 	// outputB<<"\t";
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
					outputB<<(j==1&&k==1?"":"\t")<<tsp[k].order_detail[j][i];
				}
			}
			outputB<<endl;
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
}



//程序主函数开始位置
int main(int argc,char*argv[])
{
	//打开问题开关,选择运行模式

	switch(SOLVE_PROBLEM_NO_)
	{
		case 1:problem_No_1=true;break;
		case 2:problem_No_2=true;break;
		case 3:problem_No_3=true;break;
		case 4:problem_No_4=true;break;
		default:
			cerr<<"Option error! ! Please choose again . . ."<<endl;
			cerr<<"选项错误 ！ ！ 请您重新选择 . . ."<<endl;
			return -1;
	}




	//根据运行选项打开默认的辅助开关
	if(problem_No_1)
	{
		solving_problem1_num_list=true;
	}
	if(problem_No_2)
	{
		solving_problem2 = true;
		outputA_in_file=true;
		outputB_in_file=true;
	}
	if(problem_No_3)
	{
		solving_problem2 = true;
		solving_problem3 = true;
		outputA_in_file=true;
		outputB_in_file=true;
	}
	if(problem_No_4)
	{
		solving_problem2 = true;
		solving_problem4 = true;
		outputA_in_file=true;
		outputB_in_file=true;
	}





	//读写同步优化
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	if(outer_program)
	{
		// putt(argc);		//检测附加参数个数
		//为了查找以及验证所选系数为最优方案时添加的代码片段
		//同时，考虑到运行环境的不同这里处理两种较为通用的情况
		if(argc==4||argc==3)
		{
			//预处理参数列表时会用到的字符串转数字的匿名函数
			auto todig=[](char str[])
			{
				double val=0;
				for(int i=0,ii=strlen(str);i<ii;i++)
				{
					if(str[i]<'0'||str[i]>'9')
						return -1.;
					val=val*10+str[i]-'0';
				}
				return val;
			};
			power_trust=todig(argv[1-(argc==3)]);
			power_sumup1=todig(argv[2-(argc==3)]);
			power_sumup2=todig(argv[3-(argc==3)]);
			// cerr<<power_trust<<endl;		//调试语句
			// cerr<<power_sumup<<endl;		//调试语句
		}


		//求解第四问的最大产能问题
		//同时，考虑到运行环境的不同这里处理两种较为通用的情况
		if(argc==2||argc==1)
		{
			//预处理参数列表时会用到的字符串转数字的匿名函数
			auto todig=[](char str[])
			{
				int val=0;
				for(int i=0,ii=strlen(str);i<ii;i++)
				{
					if(str[i]<'0'||str[i]>'9')
						return -1;
					val=val*10+str[i]-'0';
				}
				return val;
			};
			anss4 = todig(argv[1-(argc==1)]);				//求解最大产能的结果
			// putt(todig(argv[1-(argc==1)]));
			// putt(argv[1-(argc==1)]);
			if(anss4>0)
			{
				//启用解决第四题的运行模式
				cerr<<"U R Doing p4"<<endl;
				putt(anss4);

				solving_problem4 = true;	//按照第四问计算答案，含一个额外参数自动求解problem4
			}
		}		
	}


	if(solving_problem4)
	{
		//修改运行模式接口参数
		solving_problem1_num_list=false;			//输出供应商S的重要性排名
		solving_problem1_score=false;				//在不输出排名的情况下输出score列表
		solving_problem1_pro=false;					//在不输出排名的情况下输出pro列表
		solving_problem1=false;						//输出第一题答案相关数据

		solving_problem3 = false;					//按照第三问计算答案
		line__ = 402 ;								//设置划分排名位置

		//修改预设参数
		power_trust=1;
		power_sumup1=100;
		power_sumup2=150;

	}



//====================================input输入部分
	ifstream input_ask,input_get;
	input_ask.open("ask.txt");
	input_get.open("get.txt");
	if(!input_ask||!input_get)
		return -1;
	if(outputA_in_file)
		freopen("outputA.txt","w",stdout);
	string str;
	char ch;
	for(int i=1;i<MAX_S;i++)
	{
		data[i].num=i;
		//ask_data从"ask.txt"文件中过滤无效数据
		input_ask>>str>>ch;
		if(debug_input_ask)cout<<ch<<endl;
		data[i].ask_material_type=ch;
		//get_data从"get.txt"文件中过滤无效数据
		input_get>>str>>ch;
		if(debug_input_get)cout<<ch<<endl;
		data[i].get_material_type=ch;

		//data整合两个文件的数据到供应商信息结构体数组中
		for(int j=1;j<MAX_W;j++)
		{
			//ask_data从"ask.txt"文件中输入数据
			input_ask>>data[i].ask_data[j];
			if(debug_input_ask)cout<<data[i].ask_data[j]<<"\t";
			//get_data从"get.txt"文件中输入数据
			input_get>>data[i].get_data[j];
			if(debug_input_get)cout<<data[i].get_data[j]<<"\t";
		}
		if(debug_input_ask||debug_input_get)cout<<endl;
		// stop_screen();
	}
	//关闭文件通讯
	input_ask.close();
	input_get.close();







//====================================pro1对数据进行粗处理

	if(!solving_problem4||using_pre_pro4)
	{
		//减少极端数据对整体的影响
		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<MAX_W;j++)
			{
				//针对问题2需要特殊处理出产量最大的供应商
				if(!trust_is_related)
				{
					data[i].ask_data[j]=data[i].get_data[j];
					continue;
				}
				if(data[i].ask_data[j])
				{
					//对订单进行合理性处理
					//（超）完美订单
					if(data[i].ask_data[j]<=data[i].get_data[j])
						continue;
					//较好订单
					if(data[i].get_data[j]/data[i].ask_data[j]>.81)
					{
						data[i].ask_data[j]=data[i].get_data[j];
						continue;
					}
					//订单不合理
					if(data[i].get_data[j]/data[i].ask_data[j]<=.1||data[i].get_data[j]<=10)
					{
						data[i].ask_data[j]=data[i].get_data[j];
						continue;
					}
					//误差修正式，与get成正比
					auto wuchaxiuzheng=[&](double get){return 1.-1./log2(get);};
					data[i].ask_data[j]-=(data[i].ask_data[j]-data[i].get_data[j])*(wuchaxiuzheng(data[i].get_data[j]));
					// cerr<<data[i].get_data[j]<<" - "<<wuchaxiuzheng(data[i].get_data[j])<<" - "<<data[i].get_data[j]/data[i].ask_data[j]<<endl;		//调试用
				}
			}
		}
	}
	else
	{
		anss4*=tanxingxishu;
	}

	//调试输出预处理/合理化的订单数据
	auto shuchudata=[&]()
	{
		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<MAX_W;j++)
			{
				cout<<(j==1?"":"\t")<<data[i].ask_data[j];
			}
			cout<<endl;
		}
	};
	if(debuging_pre_pro)
	{
		shuchudata();
		return 0;
	}


	auto zhuanhuabi=[](char ch)		//转化比
	{
		double ret;
		switch(ch)
		{
			case 'A':ret=(0.6);break;
			case 'B':ret=(0.66);break;
			case 'C':ret=(0.72);break;
			default:cerr<<"bad"<<endl;return -1.;
		}
		return ret;
	};


	auto zhuanhuaxishu=[](char ch)		//转化系数
	{
		double ret;
		switch(ch)
		{
			case 'A':ret=(120*0.6);break;
			case 'B':ret=(110*0.66);break;
			case 'C':ret=(100*0.72);break;
			default:cerr<<"bad"<<endl;return -1.;
		}
		return 1./ret;
	};



	for(int i=1;i<MAX_S;i++)
	{

		for(int j=1;j<MAX_W;j++)
		{
			//week_ask_sum
			week_ask_sum[j]+=data[i].ask_data[j]*zhuanhuaxishu(data[i].get_material_type);
			week_get_sum[j]+=data[i].get_data[j]*zhuanhuaxishu(data[i].get_material_type);

			//ask_data
			data[i].ask_pre[j]=data[i].ask_pre[j-1]+data[i].ask_data[j];
			data[i].ask_sum+=data[i].ask_data[j];
			//get_data
			data[i].get_pre[j]=data[i].get_pre[j-1]+data[i].get_data[j];
			data[i].get_sum+=data[i].get_data[j];

			if(data[i].ask_pre[j]>data[i].get_pre[j])
			{
				data[i].owe_val+=data[i].ask_pre[j]-data[i].get_pre[j];
			}

			//delta,bill-> 4 trust计算信用分的前置数据
			if(data[i].ask_data[j]>data[i].get_data[j])
			{
				data[i].delta+=data[i].ask_data[j]-data[i].get_data[j];
			}
			if(data[i].ask_data[j]>0)
			{
				data[i].bill++;
				//根据权值
				data[i].trust+=min(1.,1.*data[i].get_data[j]/data[i].ask_data[j])*(data[i].ask_data[j]);
			}

		}


		// //trust计算供应商信用分
		data[i].trust/=data[i].ask_sum;//订单加权
		data[i].trust-=1./(pow(data[i].bill+041,1.5));
		// data[i].trust/=data[i].bill;//订单平等，上方权值（已废弃）
		// cerr<<data[i].trust<<endl;

		// if(data[i].delta>=0)
		// 	data[i].trust*=pow(1.-data[i].delta/max(data[i].get_sum,data[i].ask_sum),1000);
		if(solving_problem4)
			data[i].trust=data[i].get_sum/data[i].ask_sum;
		else
			data[i].trust=pow(data[i].trust,power_trust);



		if(debug_pro_1)
		{
			//ask_data
			printf("ask - S%03d - %c - sum = %6.lf\n",i,data[i].ask_material_type,data[i].ask_sum);
			//get_data
			printf("get - S%03d - %c - sum = %6.lf\n",i,data[i].get_material_type,data[i].get_sum);
			printf("owe_val = %9.lf\n",data[i].owe_val);
			puts("");
		}


	}




//====================================pro1.5过程中分析数据的代码块
	if(debug_por15)
	{
		double maxx=0;
		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<MAX_W;j++)
			{
				maxx=max(maxx,data[i].ask_data[j]);
				maxx=max(maxx,data[i].get_data[j]);
			}
			cerr<<i<<" - "<<data[i].trust<<endl;
		}

		//得到表中单点数据最大值结果是36972
		//经过简单计算可以证明对本题输入数据的运算过程不会超过double数据范围
		cerr<<maxx<<endl;
	}












//====================================anss_4为第四问设计的代码块

	//知道一家供应商S这一周W的get上限估计值之后，将get/trust即可

	if(solving_problem4)//尝试用三分法线性解问题4
	{
		// data[i].ask_data[j];
		// data[i].get_data[j];

		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<=min(24,48);j++)
			//输出答案时用24，分析或验证数据可以更改为48
			//整合数据发现周期为24周
			{
				vector<ll>a;
				for(int k=j;k<MAX_W;k+=48)
					a.push_back(data[i].get_data[k]);
				sort(a.begin(),a.end());
				auto fangcha=[&](double x)
				{
					double ret=0.;
					for(auto it:a)
						ret+=(it-x)*(it-x);
					return ret;
				};
				double val=(a.front()+a.back())/2,l=a.front(),r=a.back(),delta=0.;
				while(r-l>eps)
				{
					double midl=l+(r-l)/3;
					double midr=r-(r-l)/3;
					double fl=fangcha(l);
					double fr=fangcha(r);
					double fml=fangcha(midl);
					double fmr=fangcha(midr);
					double minn=min(min(fl,fr),min(fml,fmr));
					// putt(l);
					// putt(r);
					if(minn==fl||minn==fml)
					{
						r=midr;
						continue;
					}
					if(minn==fmr||minn==fr)
					{
						l=midl;
						continue;
					}
				}
				if(!solving_problem2)
					cout<<(j==1?"":"\t")<<(long long)(data[i].get_data[j]/data[i].trust*tanxingxishu);


				// cout<<(j==1?"":"\t")<<(long long)(val/data[i].trust);
				// cout<<(j==1?"":"\t")<<(long long)(data[i].get_data[j]*data[i].trust);
				// cerr<<(j==1?"":"\t")<<(long long)val;
				// cerr<<j<<endl;
			}
			// cerr<<endl<<endl;
			if(!solving_problem2)
				cout<<endl;
		}

		goto p4_next;
	}















//====================================pro2赋予供应商评分
	for(int i=1;i<MAX_S;i++)
	{
		for(int j=1;j<MAX_W;j++)
		{
			//供应商评分(应该要分两个if，ask和get的关系)
			auto ff_4score=[&](supplier_&s,int&x)
			//s:supplier;x:week;
			{
				if(s.ask_data[x]==0)
					return 0.;
				double&ask=s.ask_data[x];
				double&get=s.get_data[x];
				double Dask_week = week_ask_sum[x];
				double temp1 = zhuanhuaxishu(s.get_material_type=='B'?'A':'B');
				double temp2 = zhuanhuaxishu(s.get_material_type);
				double Dask = ask / zhuanhuabi(s.get_material_type) , Dget = get / zhuanhuabi(s.get_material_type) ;
				double C1 = (Dget-Dask) * sqrt(power_sumup1) * Dask / sqrt(temp1) ;		//计算惩罚系数
				double C2 = (Dask-Dget) * sqrt(power_sumup2) * Dask / sqrt(temp2) ;		//计算少宽容系数
				double ret;
				// //奖惩机制，计算供应商得分
				if(ask==get)
					return get*1e5;
				else if(ask<get)
					ret=1./(abs(ask-get)*(C1))*(s.ask_sum-s.delta)*Dask_week;
				else
					ret=-abs(ask-get)*(C2)/Dask_week/(s.ask_sum-s.delta);
				if(!using_sumup)ret=1./s.bill;
				if(using_trust)ret*=s.trust;
				return ret;
			};
			data[i].score+=ff_4score(data[i],j);
		}
		data[i].score+=4.1;
		// if(data[i].score<1)
		// 	cerr<<data[i].score<<endl;
		// if(solving_problem3)
		{
			auto judge_type=[](char ch)
			{
				if(ch=='A')return solving_problem3?		0.66/0.60	:	100/72.		;
				if(ch=='B')return solving_problem3?		0.66/0.66	:	100/72.6	;
				if(ch=='C')return solving_problem3?		0.66/0.72	:	100/72.		;
				return -1.;
			};
			data[i].score=pow(data[i].score,judge_type(data[i].get_material_type));
		}
		data[i].score=log2(data[i].score);
		// data[i].score=1-1./data[i].score;
	}




//====================================sort->anss为计算不同类型的答案设计排序规则
p4_next://解决第四题的标签

	auto cmp=[](supplier_&s)
	{

		switch(MODEL)
		{
			//综合结果
			case SCORE:
				return (double)s.score;
			//绝对信任
			case TRUST:
				return (double)s.trust;

			//绝对到货
			case SUMUP:
				return (double)s.get_sum;
		}

	};

	sort(data+1,data+MAX_S,[&](supplier_ a,supplier_ b){return cmp(a)>cmp(b);});




//====================================anss_1为第一问设计的代码块
	if(solving_problem1)
		for(int i=1;i<MAX_S;i++)
		{
			//(i==1?"\t":"")
			if(solving_problem1_num_list)
			{
				cerr<<(data[i].num)<<endl;
				cout<<(data[i].num)<<endl;
			}
			if(solving_problem1_type)cout<<" - "<<data[i].get_material_type<<" - ";
			if(solving_problem1_score)cout<<(i==1?"":"\t")<<(data[i].score);
			// if(solving_problem1_num_list)cerr<<endl;
			// cout<<(1./data[i].score)<<"\t";
			if(problem_No_1&&i==50)break;
			if(i==400)break;
		}
	if(solving_problem1_pro)
	{
		for(int i=1;i<MAX_S;i++)
		{
			data[i].pro_sum+=data[i].get_sum*zhuanhuabi(data[i].get_material_type);
			// cout<<(i==1?"":"\t")<<(data[i].pro_sum);
			cout<<(i==1?"":"\t")<<(data[i].delta);
		}
		cout<<endl;
	}






	if(debug_output1)
	{
		for(int i=1;i<MAX_S;i++)
		{
				cout<<(1./data[i].score)<<"\t";
			if(i==400)break;
		}
	}





	if(!solving_problem4)
	{

		int line_=0;//分割线
		double had=56400.;//遍历时的当下存货量
		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<MAX_W;j++)
			{
				data[i].pro[j]=data[i].get_data[j]/zhuanhuabi(data[i].get_material_type);
				had+=data[i].pro[j];
			}
			//计算需要的供应商数量
			if(had/MAX_W>(solving_problem4?anss4:28200.)/tanxingxishu)
			{
				if(finding_line)
					cerr<<i<<endl;	//	第二题中 i=270	第三题中 i=267
				line_=i;
				// return 0;
				break;
			}
		}

		//选取取消合作关系的供应商并且取消相关订单
		if(line__)line_=line__;
		for(int i=line_;++i<MAX_S;)
		{
			for(int j=1;j<MAX_W;j++)
				data[i].ask_data[j]=data[i].get_data[j]=0;
		}

	}





//====================================anss_A为填写表A设计的代码块

	//整合240周的数据到前24周的内存位置
	auto ff_4sumpro=[&]()
	{
		for(int j=1;j<MAX_W;j++)
		{
			for(int i=1;i<MAX_S;i++)
			{
				if(j>24)
				{
					data[i].pro[(j-1)%24+1]+=data[i].pro[j];
					data[i].ask_data[(j-1)%24+1]+=data[i].ask_data[j];
					data[i].get_data[(j-1)%24+1]+=data[i].get_data[j];
				}
				if(data[i].get_data[j]>0)
					data[i].bill_data[(j-1)%24+1]++;
			}
		}

		//此处发现以周期稳定在24周
		if(prove_cycle_bill)
			for(int j=1;j<24;j++)
				for(int i=1;i<MAX_S;i++)
					if(data[i].bill_data[j]!=0)
					{
						char stri[10],strj[10];
						sprintf(stri,"%03d ]",i);
						sprintf(strj,"[ %3d ]",j);
						cerr<<"[ S-"<<stri<<" bill of week%24 = "<<strj<<" : "<<data[i].bill_data[j]<<endl;
					}


		tot.pro_sum=0;
		for(int j=1;j<=24;j++)
		{
			tot.ask_data[j]=tot.get_data[j]=tot.pro[j]=0;
			for(int i=1;i<MAX_S;i++)
			{
				data[i].pro[j]/=10;
				data[i].ask_data[j]/=10;
				data[i].get_data[j]/=10;
				data[i].bill_data[j]/=10;
				tot.pro[j]+=data[i].pro[j];
				tot.ask_data[j]+=data[i].ask_data[j];
				tot.get_data[j]+=data[i].get_data[j];
			}
			tot.pro_sum+=tot.pro[j];
		}
	};
	ff_4sumpro();
	





	//恢复数据的编号有序性
	sort(data+1,data+MAX_S,[&](supplier_ a,supplier_ b){return (a.num)<(b.num);});



//====================================anss_A♥填写表A并且结束程序
	if(solving_problem2)
	{

		//总结数据+局部平滑处理
		for(int j=1;j<=24;j++)
		{
			tot.ask_data[j]=0;
			for(int i=1;i<MAX_S;i++)
			{
				data[i].ask_data[j]=data[i].get_data[j]/zhuanhuabi(data[i].get_material_type);
				tot.ask_data[j]+=data[i].ask_data[j];
			}
			double temp=min((solving_problem4?anss4:28200.)/tot.ask_data[j],tanxingxishu2);
			for(int i=1;i<MAX_S;i++)
			{
				data[i].ask_data[j]=data[i].ask_data[j]*temp*zhuanhuabi(data[i].get_material_type)*data[i].bill_data[j];
			}
		}

		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<=24;j++)
				cout<<(j==1?"":"\t")<<(long long)(data[i].ask_data[j]);
			cout<<endl;
		}
		
		cerr<<"Done table A !"<<endl;
		cerr<<"已完成表A的填写 ！"<<endl<<endl;

		if(outputB_in_file)finish_table_B::main();

		cerr<<"Done table B !"<<endl;
		cerr<<"已完成表B的填写 ！"<<endl<<endl;

		return 0;
	}



//后面就是在正解出来之前的处理了


//====================================for_4为第四问做的订购合理性评估做铺垫(平滑处理)
	for(int j=1;j<=24;j++)
	{
		for(int i=1;i<MAX_S;i++)
		{
			if(data[i].ask_data[j]>0)
			{
				anss_A[j][i].fi=data[i].ask_data[j];
				anss_A[j][i].se=data[i].pro[j];
			}
		}
	}

	//平滑处理
	for(int j=1;j<=24;j++)
	{
		tot.pro[j]=0;
		for(int i=1;i<MAX_S;i++)
		{
			if(data[i].ask_data[j]>0)
			{
				data[i].pro[j]=sqrt(data[i].pro[j]/data[i].trust);
				tot.pro[j]+=data[i].pro[j];
			}
		}
		double temp=(solving_problem4?anss4:28200.)/tot.pro[j];
		for(int i=1;i<MAX_S;i++)
		{
			if(data[i].pro[j]>0)
			{
				data[i].pro[j]*=temp;
				data[i].ask_data[j]=data[i].pro[j]*zhuanhuabi(data[i].get_material_type);
			}
		}
	}



//====================================for_4第四问的订购合理性评估
	if(solving_problem4&&debuging)
	{
		double t1_maxx=-1e10,t2_maxx=-1e10;
		for(int j=1;j<=24;j++)
		{
			for(int i=1;i<MAX_S;i++)
			{
				if(anss_A[j][i].fi>0)
				{
					double t1=abs(1.*data[i].ask_data[j]/(1.*anss_A[j][i].fi));
					t1_maxx=max(t1_maxx,t1);
				}
				if(anss_A[j][i].se>0)
				{
					double t2=abs(1.*data[i].pro[j]/(1.*anss_A[j][i].se));
					t2_maxx=max(t2_maxx,t2);
				}
			}
		}
		putt(t1_maxx);
		putt(t2_maxx);
		return 0;
	}



//====================================anss_A2B填写表A以及之后为填写表B设计打基础的代码块
	if(solving_problem2)
		for(int i=1;i<MAX_S;i++)
		{
			for(int j=1;j<=24;j++)
			{
				cout<<(j==1?"":"\t")<<(long long)(data[i].ask_data[j]);
			}
			cout<<endl;
		}


	return 0;

}
/*
	Done .
*/
