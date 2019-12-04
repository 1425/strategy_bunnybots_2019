#include<iostream>
#include<array>
#include<vector>
#include<sstream>
#include<map>
#include<cassert>
#include<set>
#include<algorithm>
#include<fstream>

using namespace std;

//start generic code

#define nyi { cout<<"nyi "<<__LINE__<<"\n"; exit(44); }

#define PRINT(X) { cout<<""#X<<":"<<(X)<<"\n"; }

#define INST(A,B) A B;
#define STRUCT(ITEMS) struct T{ ITEMS(INST) };

#define SHOW_INNER(A,B) o<<""#B<<":"<<a.B<<" ";

#define SHOW(ITEMS) std::ostream& operator<<(std::ostream& o,T const& a){\
	o<<""<<"(";\
	ITEMS(SHOW_INNER)\
	return o<<")";\
}

#define RAND_INNER(A,B) rand((const A*)nullptr),

#define ITEMS_INNER(A,B) ""#B,
#define ITEMS(X)\
	vector<string> items(const T*){\
		return vector<string>{X(ITEMS_INNER)};\
	}

template<typename T,size_t N>
std::ostream& operator<<(std::ostream& o,std::array<T,N> const& a){
	o<<"[ ";
	for(auto elem:a){
		o<<elem<<" ";
	}
	return o<<"]";
}

template<typename T>
vector<T> range(T min,T lim){
	vector<T> r;
	for(T i=min;i<lim;i++){
		r|=i;
	}
	return r;
}

template<typename T>
vector<T> range(T lim){
	vector<T> r;
	for(T i=0;i<lim;i++){
		r|=i;
	}
	return r;
}

template<typename T,size_t N>
std::array<std::pair<size_t,T>,N> enumerate(std::array<T,N> const& a){
	std::array<pair<size_t,T>,N> r;
	for(auto i:range(N)){
		r[i]=std::make_pair(i,a[i]);
	}
	return r;
}

template<typename T>
std::vector<std::pair<size_t,T>> enumerate(std::vector<T> const& a){
	return mapf(
		[=](auto i){ return make_pair(i,a[i]); },
		range(a.size())
	);
}

template<typename Count,typename T>
std::vector<std::pair<Count,T>> enumerate_from(Count start,std::vector<T> const& a){
	return mapf(
		[=](auto i){ return make_pair(Count(start+i),a[i]); },
		range(a.size())
	);
}

template<typename Func,typename T>
auto mapf(Func f,std::vector<T> const& a){
	using Out=decltype(f(a[0]));
	vector<Out> r;
	for(auto elem:a){
		r|=f(elem);
	}
	return r;
}

template<typename Func,typename T,size_t N>
auto mapf(Func f,std::array<T,N> const& a){
	std::array<decltype(f(a[0])),N> r;
	for(auto [i,elem]:enumerate(a)){
		r[i]=f(elem);
	}
	return r;
}

template<typename T>
vector<T> to_vec(set<T> const& a){
	return vector<T>{a.begin(),a.end()};
}

template<typename Func,typename T>
auto mapf(Func f,set<T> const& a){
	return mapf(f,to_vec(a));
}

template<typename K,typename V>
vector<pair<K,V>> to_vec(std::map<K,V> const& a){
	vector<pair<K,V>> r;
	for(auto [k,v]:a) r|=make_pair(k,v);
	return r;
}

template<typename Func,typename K,typename V>
auto mapf(Func f,std::map<K,V> const& m){
	return mapf(f,to_vec(m));
}

template<typename T>
std::ostream& operator<<(std::ostream& o,std::vector<T> const& a){
	o<<"[ ";
	for(auto elem:a) o<<elem<<" ";
	return o<<"]";
}

template<typename T,typename T2>
std::vector<T>& operator|=(std::vector<T>& a,T2 t){
	a.push_back(t);
	return a;
}

template<typename A,typename B>
std::ostream& operator<<(std::ostream& o,std::pair<A,B> const& a){
	return o<<"("<<a.first<<","<<a.second<<")";
}

template<typename K,typename V>
std::ostream& operator<<(std::ostream& o,std::map<K,V> const& a){
	o<<"{ ";
	for(auto elem:a) o<<elem;
	return o<<"}";
}

//ends are inclusive.
template<int MIN,int MAX>
struct Int_limited{
	int t;

	operator int()const{
		return t;
	}

	Int_limited& operator+=(int i){
		t+=i;
		return *this;
	}
};

template<int MIN,int MAX>
Int_limited<MIN,MAX> rand(const Int_limited<MIN,MAX>*){
	return Int_limited<MIN,MAX>{MIN+rand()%(MAX-MIN+1)};
}

template<int MIN,int MAX>
Int_limited<MIN,MAX> parse(const Int_limited<MIN,MAX>*,string const& s){
	return Int_limited<MIN,MAX>{stoi(s)};
}

bool parse(const bool*,string s){
	if(s=="0") return 0;
	if(s=="1") return 1;
	nyi
}

unsigned parse(const unsigned*,string s){
	return stoi(s);
}

template<typename T>
void print_lines(T t){
	for(auto elem:t){
		cout<<elem<<"\n";
	}
}

template<typename T>
vector<T> take(size_t lim,vector<T> const& v){
	vector<T> r;
	for(auto i:range(std::min(lim,v.size()))){
		r|=v[i];
	}
	return r;
}

template<typename T>
vector<T> take(size_t lim,set<T> s){
	return take(lim,to_vec(s));
}

template<typename T>
T min(vector<T> const& a){
	assert(a.size());
	T r=a[0];
	for(auto elem:a){
		r=min(r,elem);
	}
	return r;
}

template<typename T>
T max(vector<T> const& a){
	assert(a.size());
	T r=a[0];
	for(auto elem:a){
		r=max(r,elem);
	}
	return r;
}

template<typename T,size_t N>
T max(std::array<T,N> const& a){
	assert(N);
	T r=a[0];
	for(auto elem:a){
		r=max(r,elem);
	}
	return r;
}

#define MAP(A,B) mapf([](auto x){ return (A)(x); },(B))

template<typename A,typename B>
bool operator!=(std::pair<A,B> const& a,std::pair<A,B> const& b){
	nyi
}

template<typename Func,typename T>
auto group(Func f,vector<T> const& a){
	using K=decltype(f(a[0]));
	map<K,vector<T>> r;
	for(auto elem:a){
		r[f(elem)]|=elem;
	}
	return r;
}

template<typename Func,typename K,typename V>
auto map_values(Func f,map<K,V> const& in){
	using V2=decltype(f(in.begin()->second));
	map<K,V2> r;
	for(auto [k,v]:in){
		r[k]=f(v);
	}
	return r;
}

template<typename T>
bool all_equal(vector<T> const& a){
	if(a.empty()) return 1;
	for(auto elem:a){
		if(elem!=a[0]) return 0;
	}
	return 1;
}

template<typename T>
T sum(vector<T> v){
	T r{};
	for(auto elem:v)r+=elem;
	return r;
}

template<typename T,size_t N>
T sum(std::array<T,N> const& a){
	T r{};
	for(auto elem:a)r+=elem;
	return r;
}

template<typename T>
auto mean(vector<T> v){
	assert(v.size());
	return sum(v)/v.size();
}

template<typename T>
set<T> to_set(vector<T> v){
	return set<T>(v.begin(),v.end());
}

template<typename T>
multiset<T> to_multiset(vector<T> v){
	return multiset<T>{v.begin(),v.end()};
}

template<typename T>
vector<T> sorted(vector<T> a){
	sort(begin(a),end(a));
	return a;
}

template<typename T>
vector<T> reversed(vector<T> a){
	reverse(begin(a),end(a));
	return a;
}

template<typename T>
vector<pair<size_t,T>> count(vector<T> v){
	auto m=to_multiset(v);
	return reversed(sorted(mapf(
		[=](auto x){
			return make_pair(m.count(x),x);
		},
		to_set(v)
	)));
}

vector<string> lines(string s){
	stringstream ss;
	ss<<s;
	vector<string> r;
	while(ss.good()){
		string line;
		getline(ss,line);
		r|=line;
	}
	return r;
}

vector<string> split(string s,char target){
	vector<string> r;
	std::stringstream ss;
	for(auto c:s){
		if(c==target){
			r|=ss.str();
			ss.str("");
		}else{
			ss<<c;
		}
	}
	if(ss.str().size()){
		r|=ss.str();
	}
	return r;
}

vector<string> split(string s){
	return split(s,' ');
}

template<typename T>
vector<T> skip(size_t start,vector<T> const& a){
	if(start>a.size()){
		return {};
	}
	return vector<T>{a.begin()+start,a.end()};
}

template<typename T>
vector<T> tail(vector<T> v){
	return skip(1,v);
}

template<typename A,typename B>
vector<pair<A,B>> zip(vector<A> const& a,vector<B> const& b){
	vector<pair<A,B>> r;
	for(auto i:range(min(a.size(),b.size()))){
		r|=make_pair(a[i],b[i]);
	}
	return r;
}

template<typename T>
void diff(vector<T> const& a,std::vector<T> const& b){
	if(a.size()!=b.size())nyi
	for(auto [i,p]:enumerate(zip(a,b))){
		auto [a1,b1]=p;
		if(a1!=b1){
			cout<<i<<":\n";
			diff(a1,b1);
			cout<<"\n";
		}
	}
}

string tag(string t,string body){
	auto sp=split(t);
	assert(sp.size());
	stringstream ss;
	ss<<"<"<<t<<">"<<body<<"</"<<sp[0]<<">";
	return ss.str();
}

template<typename T>
string as_string(T t){
	stringstream ss;
	ss<<t;
	return ss.str();
}

#define X(A) \
	template<typename T> auto A(T t){ return tag(""#A,as_string(t)); }\
	auto A##1(string s){ return tag(""#A,s); }
X(title)
X(head)
X(table)
X(tr)
X(td)
X(h1)
X(body)
X(html)
X(th)
X(small)
#undef X

struct As_string{
	template<typename T>
	string operator()(T)const;
};

struct Td{
	template<typename T>
	string operator()(T t)const{ return td(t); }
};

string join(vector<string> a){
	stringstream ss;
	for(auto elem:a) ss<<elem;
	return ss.str();
}

void write_file(string const& path,string const& contents){
	ofstream f(path);
	f<<contents;
}

template<typename T>
vector<T> operator+(vector<T> const& a,vector<T> const& b){
	vector<T> r{a.begin(),a.end()};
	for(auto elem:b){
		r|=elem;
	}
	return r;
}

template<typename T>
vector<double> to_doubles(vector<T> const& a){
	return mapf([](auto x){ return double(x); },a);
}

unsigned rand(const unsigned*){
	return rand()%10;
}

int rand(const int*){ return rand(); }
bool rand(const bool*){ return rand()%2; }

template<typename T>
vector<T> rand(const vector<T>*){
	vector<T> r;
	for(auto _:range(rand()%400)){
		(void)_;
		r|=rand((const T*)nullptr);
	}
	return r;
}

template<typename K,typename V>
map<K,V> without_key(K key,map<K,V> const& a){
	map<K,V> r;
	for(auto [k,v]:a){
		if(k!=key){
			r[k]=v;
		}
	}
	return r;
}

template<typename A,typename B>
vector<B> seconds(std::vector<std::pair<A,B>> const& a){
	return mapf([](auto p){ return p.second; },a);
}

template<typename K,typename V>
vector<V> at_keys(map<K,V> const& m,vector<K> keys){
	vector<V> r;
	for(auto k:keys){
		auto f=m.find(k);
		assert(f!=m.end());
		r|=f->second;
	}
	return r;
}

template<typename T>
set<T>& operator|=(std::set<T>& a,T t){
	a.insert(t);
	return a;
}

template<typename K,typename V>
set<K> keys(map<K,V> const& m){
	set<K> r;
	for(auto [k,v]:m){
		r|=k;
	}
	return r;
}

template<typename T>
T choose(vector<T> const& a){
	assert(a.size());
	return a[rand()%a.size()];
}

template<typename T>
T choose(set<T> const& a){
	return choose(to_vec(a));
}

//start program-specific code

using Team=string;//number and then optionally a char.

Team rand(const Team*){
	stringstream ss;
	ss<<1+(rand()%10);
	if(rand()%2){
		ss<<char('a'+(rand()%26));
	}
	return ss.str();
}

Team parse(const Team*,string s){
	return s;
}

using Match=Int_limited<1,150>;

using Cubes_scored=Int_limited<0,120>;
using Auto_bunnies=Int_limited<0,3>;
using Auto_tubs_touched=Int_limited<0,8>;

#define PICK_ITEM(A,B) auto B(T const& a){ return a.B; }
#define PICK_ITEMS(A,B) \
	vector<A> B(vector<T> const& a){ return MAP(B,a); }\
	template<size_t N> std::array<A,N> B(std::array<T,N> const& a){ return MAP(B,a); }

#define MATCH_DATA_ITEMS(X)\
	X(Team,team)\
	X(Match,match)\
	X(Auto_bunnies,auto_bunnies)\
	X(Auto_tubs_touched,auto_tubs_touched)\
	X(bool,auto_tub_lift)\
	X(unsigned,bunnies_placed)\
	X(unsigned,bunnies_ejected)\
	X(Cubes_scored,cubes_scored)

#define T Match_data
STRUCT(MATCH_DATA_ITEMS)
SHOW(MATCH_DATA_ITEMS)
ITEMS(MATCH_DATA_ITEMS)
MATCH_DATA_ITEMS(PICK_ITEM)
MATCH_DATA_ITEMS(PICK_ITEMS)

T rand(const T*){
	return T{
		MATCH_DATA_ITEMS(RAND_INNER)
	};
}

bool operator==(Match_data const& a,Match_data const& b){
	#define X(A,B) if(a.B!=b.B) return 0;
	MATCH_DATA_ITEMS(X)
	#undef X
	return 1;
}

bool operator!=(Match_data const& a,Match_data const& b){
	return !(a==b);
}
#undef T

using Scouting_data=vector<Match_data>;

#define ROBOT_CAPABILITIES_ITEMS(X)\
	X(double,auto_bunnies)\
	X(double,auto_tubs_touched)\
	X(double,auto_tub_lift)\
	X(double,cubes_scored)\
	X(double,bunnies_placed)\
	X(double,bunnies_ejected)

#define T Robot_capabilities
STRUCT(ROBOT_CAPABILITIES_ITEMS)
SHOW(ROBOT_CAPABILITIES_ITEMS)
ITEMS(ROBOT_CAPABILITIES_ITEMS)
ROBOT_CAPABILITIES_ITEMS(PICK_ITEM)
ROBOT_CAPABILITIES_ITEMS(PICK_ITEMS)

T& operator+=(T& a,T b){
	#define X(A,B) a.B+=b.B;
	ROBOT_CAPABILITIES_ITEMS(X)
	#undef X
	return a;
}

T operator/(T a,double b){
	#define X(A,B) a.B/=b;
	ROBOT_CAPABILITIES_ITEMS(X)
	#undef X
	return a;
}
#undef T

using Alliance_capabilities=std::array<Robot_capabilities,3>;

using Points=double;

#define AUX_DATA_ITEMS(X)\
	X(double,bunny_place_value)

#define T Aux_data
STRUCT(AUX_DATA_ITEMS)
SHOW(AUX_DATA_ITEMS)
#undef T

Points points(Robot_capabilities const& a,Aux_data const& aux_data){
	return 
		2*a.cubes_scored+
		5*a.auto_bunnies+
		5*a.auto_tubs_touched+
		15*a.auto_tub_lift+
		aux_data.bunny_place_value*a.bunnies_placed
	;
}

Points points(Alliance_capabilities const& a,Aux_data const& aux_data){
	return
		2*min(120.,sum(cubes_scored(a)))+
		5*std::max(
			max(auto_bunnies(a)),
			.8+sum(auto_bunnies(a))
		)+
		5*sum(auto_tubs_touched(a))+
		15*sum(auto_tub_lift(a))+
		aux_data.bunny_place_value*sum(bunnies_placed(a))
	;
}

static const int ALLIANCES=4;

using Picklist=std::vector<
	std::pair<
		std::pair<Points,Team>,
		std::vector<std::pair<Points,Team>>
	>
>;

Robot_capabilities capabilities(Scouting_data const& a){
	//check all from the same team...
	auto t=team(a);
	assert(all_equal(t));
	Robot_capabilities r;
	#define X(A,B) r.B=mean(to_doubles(B(a)));
	ROBOT_CAPABILITIES_ITEMS(X)
	#undef X
	return r;
}

std::map<Team,Robot_capabilities> to_capabilities(Scouting_data const& a){
	auto g=group([](auto x){ return x.team; },a);
	return map_values(capabilities,g);
}

Aux_data gen_aux_data(Scouting_data const& a){
	auto total_places=sum(bunnies_placed(a));
	auto total_ejected=sum(bunnies_ejected(a));
	if(total_ejected>total_places){
		PRINT(total_ejected);
		PRINT(total_places);
	}
	assert(total_ejected<=total_places);
	auto portion_staying=1-(0.0+total_ejected)/total_places;

	auto average_cubes=mean(to_doubles(cubes_scored(a)));
	return Aux_data{2*average_cubes*portion_staying};
}

template<typename T>
void explore_column(string name,vector<T> info){
	auto s=to_set(info);
	cout<<name<<" ("<<s.size()<<"):"<<min(info)<<" "<<max(info)<<" ";
	//<<take10(s)<<"\n";
	cout<<take(5,count(info))<<"\n";
}

void explore_data(Scouting_data const& a){
	cout<<"Data check\n";
	cout<<"Rows:"<<a.size()<<"\n";
	if(a.empty())nyi
	#define X(A,B) explore_column(""#B,B(a));
	MATCH_DATA_ITEMS(X)
	#undef X
}

void make_ex(std::ostream& o,Scouting_data const& s){
	#define X(A,B) o<<""#B<<",";
	MATCH_DATA_ITEMS(X)
	#undef X
	o<<"\n";

	for(auto a:s){
		#define X(A,B) o<<a.B<<",";
		MATCH_DATA_ITEMS(X)
		#undef X
		o<<"\n";
	}
}

Scouting_data parse(string const& s){
	auto l=lines(s);
	assert(l.size()>=1);
	auto header=l[0];

	auto expected_header=items((const Match_data*)nullptr);
	auto hf=split(header,',');
	assert(hf==expected_header);

	Scouting_data r;
	for(auto x:skip(1,l)){
		if(x.size()==0) continue;
		auto sp=split(x,',');
		//PRINT(sp);
		//PRINT(sp.size());
		//PRINT(expected_header.size());
		assert(sp.size()==expected_header.size());
		Match_data d;
		#define X(A,B) d.B=parse((const A*)nullptr,sp[0]); sp=tail(sp);
		MATCH_DATA_ITEMS(X)
		#undef X
		r|=d;
	}
	return r;
}

void diff(Match_data const& a,Match_data const& b){
	ostream& o=cout;
	#define X(A,B) if(a.B!=b.B) o<<""#B<<": \""<<a.B<<"\" \""<<b.B<<"\"\n";
	MATCH_DATA_ITEMS(X)
	#undef X
}

template<typename Func>
struct Map_result{
	#define X(A,B) decltype((*(Func*)0)(*(A*)0)) B;
	ROBOT_CAPABILITIES_ITEMS(X)
	#undef X
};

template<typename Func>
vector<string> to_vec(Map_result<Func> const& a){
	vector<string> r;
	#define X(A,B) r|=a.B;
	ROBOT_CAPABILITIES_ITEMS(X)
	#undef X
	return r;
}

template<typename Func>
auto mapf(Func f,Robot_capabilities const& a){
	Map_result<Func> r;
	#define X(A,B) r.B=f(a.B);
	ROBOT_CAPABILITIES_ITEMS(X)
	#undef X
	return r;
}

string to_html(Team picker,Picklist const& p){
	string header="Picklist for team "+picker;

	auto nice_cell=[](auto p)->string{
		return td(
			as_string(p.second)+
			"<br>"+tag("font color=grey",small(p.first))
		);
	};

	return html(
		head(title(header))+
		body(
			h1(header)+
			tag("table border",
				tr(
					tag("th colspan=2 rowspan=2","First Pick")+
					tag("th colspan=14","Second Pick")
				)+
				tr(join(mapf(
					[](auto x){ return th(x); },
					range(1,15)
				)))+
				join(mapf(
					[=](auto p)->string{
						auto [i,x]=p;
						return tr(
							th(i)+nice_cell(x.first)+
							join(mapf(
								nice_cell,
								take(14,x.second)
							))
						);
					},
					enumerate_from(1,take(7,p))
				))
			)
		)
	);
}

string to_html(map<Team,Robot_capabilities> const& m){
	return html(
		head(
			title("Robot capabilities")
		)+
		body(
			h1("Robot capabilities")+
			tag("table border",
				tr(
					join(mapf(
						td1,
						std::vector<std::string>{"Team"}+items((const Robot_capabilities*)nullptr)
					))
				)+
				join(mapf(
					[](auto p){
						return tr(
							td(p.first)
							+join(to_vec(mapf(Td{},p.second)))
						);
					},
					m
				))
			)
		)
	);
}

Picklist make_picklist(Team picker,map<Team,Robot_capabilities> const& cap,Aux_data const& aux){
	//static const int last_robot=3*ALLIANCES;
	//static const int picked_per_alliance=4;

	assert(cap.count(picker));
	auto f=cap.find(picker);
	assert(f!=cap.end());
	auto own_cap=f->second;

	auto other_robots=without_key(picker,cap);
	auto baseline_picks=reversed(sorted(
		mapf(
			[own_cap,aux](auto p)->pair<Points,Team>{
				auto pts=points(
					Alliance_capabilities{own_cap,p.second,Robot_capabilities{}},
					aux
				);
				return make_pair(pts,p.first);
			},
			other_robots
		)
	));
	PRINT(baseline_picks);

	auto baseline_teams=take(3,skip(10,seconds(baseline_picks)));
	auto baseline_caps=at_keys(cap,baseline_teams);//mapf([=](auto a){ return cap[a]; },baseline_teams);
	auto baseline_cap=mean(baseline_caps);
	PRINT(baseline_cap);

	PRINT(picker);

	auto first_picks=reversed(sorted(mapf(
		[own_cap,aux,baseline_cap](auto p){
			auto pts=points(
				Alliance_capabilities{own_cap,p.second,baseline_cap},
				aux
			);
			return make_pair(pts,p.first);
		},
		other_robots
	)));

	PRINT(first_picks);

	auto m=mapf(
		[=](auto p){
			auto first_pick_team=p.second;
			auto first_pick_cap=[=](){
				auto f=other_robots.find(p.second);
				assert(f!=other_robots.end());
				return f->second;
			}();

			auto rest=without_key(first_pick_team,other_robots);
			auto pts3=[=](Robot_capabilities third){
				return points(
					Alliance_capabilities{own_cap,first_pick_cap,third},
					aux
				);
			};
			return make_pair(
				//first_pick_team,
				p,
				reversed(sorted(mapf(
					[=](auto t3){ return make_pair(pts3(t3.second),t3.first); },
					rest
				)))
			);
		},
		first_picks
	);
	//PRINT(cap);
	//PRINT(aux);
	//print_lines(m);

	return m;
}

vector<string> args(int argc,char **argv){
	return mapf(
		[=](auto i){ return string{argv[i]}; },
		range(1,argc)
	);
}

int main(int argc,char **argv){
	auto a=args(argc,argv);
	Team picker="NONE";
	optional<string> input_file; //or random; and if random, then write out the example CSV.
	for(auto at=begin(a);at!=end(a);++at){
		if(*at=="--picker"){
			at++;
			assert(at!=end(a));
			picker=*at;
			continue;
		}
		if(*at=="--in"){
			at++;
			assert(at!=end(a));
			input_file=*at;
			continue;
		}
		cout<<"Unrecognized argument.\n";
		return 1;
	}
	auto s=rand((const Scouting_data*)nullptr);
	//s=take(1,s);
	stringstream ss;
	make_ex(ss,s);
	ofstream f("ex.csv");
	f<<ss.str();

	//PRINT(ss.str());
	auto p=parse(ss.str());
	if(p!=s){
		diff(p,s);
	}
	assert(p==s);

	//PRINT(s);
	//print_lines(s);
	explore_data(s);
	auto cap=to_capabilities(s);
	auto aux=gen_aux_data(s);
	PRINT(aux);

	//cout<<"\nRobot Capabilities\n";
	//print_lines(cap);

	write_file("robot_capabilities.html",to_html(cap));
	//Team picker="1425";
	if(picker=="NONE") picker=choose(keys(cap));
	{
		auto p=make_picklist(picker,cap,aux);
		//PRINT(p);
		write_file("picklist.html",to_html(picker,p));
	}
}
