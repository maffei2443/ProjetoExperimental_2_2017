/*
  Arquivos necessarios para servir de entrada:
    USA-roda-d.NY.co
    USA-road-d.NY.gr
    input

  Como rodar os experimentos?
  Tendo todos os arquivos acima no mesmo diretório
  no qual se localiza esse código rode, no dire-
  tório vigente, os comandos abaixo:

    g++ -std=c++14 experimentos.cpp -o experimentos
    ./experimentos < input_adjusted
  Após a execução do programa, tem-se diversos novos
  arquivos, quais sejam:
    <?>_t
    <?>_q
    <?>_pushed
    <?>_heuristicas
*/

#include <bits/stdc++.h>
// Obs : rodar com -o1000000000000000000 :)
using namespace std;
typedef pair<int,int> ii;
typedef vector<int>   vi;
typedef vector<long long> vll;
typedef vector<pair<int,int> > vii;
#define ll long long
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pq priority_queue
#define mii map<int,int>
#define sf1(x) scanf("%d",&x)
#define sf2(x,y) scanf("%d %d",&x,&y)
#define sf3(x,y,z) scanf("%d %d %d",&x,&y,&z)
#define log2(x) (31 - __builtin_clz(x))
#define lcm(x,y) (x*y) / __gcd(x,y)
int inf = (1e9) + 7;
int mod = 998244353;
int nodes = 1;
int per_node = 1;
FILE* fplog;
pair<int,double> d;


vector<pair<int,double> > graph[270000];
pair<double,double> coordinates[270000];

vector<pair<int,double> > bfs[4]; // 0 =
vector<pair<int,double> > ucs[4]; // 0 =
vector<pair<int,double> > gs[4]; // 0 =
vector<pair<int,double> > as[4]; // 0 = 5, 1 = 15, ...


int x, cat, sam;
double dist[4][50]; // De 10 em 10 colunas, troca a origem !!! SETADO APENAS UMA VEZ !!!
double best_dist[4][50]; // De 10 em 10 colunas, troca a origem !!! SETADO APENAS UMA VEZ !!!
int tempo[4][50]; // Trocado toda hora.
int push[4][50];
int heuristicas[4][50];
int from[5];
// Vetores de OBJETIVOS para cada categoria de distancia de cada origem.
int to[4][50];
// Vetor com os vertices de origem


void le_arqs(){
 ifstream c_file("USA-road-d.NY.co");
 ifstream g_file("USA-road-d.NY.gr");

 for (int i = 0; i < 264346; ++i)
 {
  string c;

  int k;
  double d1,d2;
  c_file >> c >> k >> d1 >> d2;
  k--;
  d1/= 1e6;
  d2/= 1e6;
  coordinates[k] = mp(d1,d2);
 }

 for (int i = 0; i < 733846; ++i){

  string c;
  int a,b;
  double w;
  g_file >> c >> a >> b >> w;

//cout << c << " " << a << " " << " " <<  b << " "<< w << '\n';
// getchar();
  a--;
  b--;
  w/=10;
  graph[a].pb(mp(b,w));
  graph[b].pb(mp(a,w));
 } 
 // cout << "Leu aruivos\n";
}


double distance(int u, int v){
 double r = 6371;
    double deltaLat = ((3.1415926535/ 180.0)) * (coordinates[v].ss - coordinates[u].ss);
    double deltaLon = ((3.1415926535/ 180.0)) * (coordinates[v].ff - coordinates[u].ff);


    double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos((3.1415926535/ 180.0) * (coordinates[u].ss)) * cos((3.1415926535/ 180.0) *(coordinates[v].ss))
            * sin(deltaLon / 2) * sin(deltaLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
 return  r * c * 1000; // convert to meters
}



pair<int,double> AS(int from, int to, int& pushed, int& heuristica){
  // cout << "AS\n";
 fprintf(fplog, "AS :: %d -> %d\n",from,to );
 auto start = chrono::high_resolution_clock::now();

 priority_queue< pair< pair< double,int>, double >, vector< pair< pair< double,int>, double > >, greater<pair< pair< double,int>, double >>> q;
 q.push(mp(mp(0.0,from),0.0));
 int cont = 0;
 heuristica = 0;
 vector<double> bp(270000,1e20);
 while(q.size())
 {
  auto u = q.top(); q.pop();
  cont++;
  // printf(" %lf %d\n",u.ff.ff, u.ff.ss );

  if(u.ff.ss == to)
  {
   auto end = chrono::high_resolution_clock::now();
   auto elapsed = end - start;
   fprintf(fplog, "analisados == %d\n", cont);
   fprintf(fplog, "enfileirados == %d\n", pushed);   
   fprintf(fplog, "Calculos de heuristica :: %d\n", heuristica);
   // getchar();
   return mp(elapsed.count(),u.ss);
  }

  for(auto v: graph[u.ff.ss]){
   heuristica++;
   if(bp[v.ff] > u.ss + v.ss){
    q.push(mp(mp(distance(v.ff,to) + u.ss + v.ss,v.ff) , u.ss + v.ss));
    pushed++;
    bp[v.ff] = u.ss + v.ss;
   }
  }
 }
}

pair<int,double> BFS(int from, int to, int& pushed){

 fprintf(fplog, "BFS :: %d -> %d\n",from, to );
 auto start = chrono::high_resolution_clock::now();
 int enq[270000];
 memset(enq,0,sizeof(enq));
 queue<pair<int,double>> q;
 q.push(mp(from,0.0));
 enq[from] = 1;

 int cont = 0;
 while(q.size()){

  auto u = q.front(); q.pop();
  cont++;
  if(u.ff == to)
  {
   auto end = chrono::high_resolution_clock::now();
   auto elapsed = end - start;
   fprintf(fplog, "analisados == %d\n", cont);
   fprintf(fplog, "enfileirados == %d\n", pushed);   
   // getchar();
   return mp(elapsed.count(),u.ss);
  }

  for(auto v: graph[u.ff]){
   cont++;
   if(!enq[v.ff]) {
    q.push(mp(v.ff,v.ss + u.ss));
    pushed++;
    enq[v.ff] = 1;
   }
  }
 }
}

pair<int,double> GS(int from, int to, int& pushed){
// cout << "Ignorar....\n";
 fprintf(fplog,"GS :: %d -> %d\n", from, to);
 auto start = chrono::high_resolution_clock::now();
 // cout << "tempo correto\n";
 priority_queue< pair< pair< double,int>, double >, vector< pair< pair< double,int>, double > >, greater<pair< pair< double,int>, double >>> q;
 q.push(mp(mp(0.0,from),0.0));
 int cont = 0;
 int enq[270000];
 memset(enq,0,sizeof(enq));
 while(q.size())
 {
  auto u = q.top(); q.pop();
  cont++;
  // printf(" %lf %d\n",u.ff.ff, u.ff.ss );

  if(u.ff.ss == to)
  {
   auto end = chrono::high_resolution_clock::now();
   auto elapsed = end - start;
   fprintf(fplog, "analisados == %d\n", cont);
   fprintf(fplog, "enfileirados == %d\n", pushed);   
   // getchar();
   return mp(elapsed.count(),u.ss);
  }

  for(auto v: graph[u.ff.ss]){
   cont++;
   if(!enq[v.ff]){
    q.push(mp(mp(distance(v.ff,to),v.ff), u.ss + v.ss));
    pushed++;
    enq[v.ff] = 1;
   }
  }
 }
}

pair<int,double> UCS(int from, int to, int& pushed, int& heuristica){
 fprintf(fplog, "UCS :: %d -> %d\n", from, to);
 auto start = chrono::high_resolution_clock::now();
 vector<double> bp(270000,1e20);
 int enq[270000];
 
 priority_queue<pair<double,int>, vector<pair<double,int>>,greater<pair<double,int> > > q;
 bp[from] = 0; 
 q.push(mp(0.0,from));
 enq[from] = 1;
 int cont = 0;
 heuristica = 0;
 while(q.size()){

  auto u = q.top(); q.pop();
  cont++;
  if(u.ss == to)
  {
   auto end = chrono::high_resolution_clock::now();
   auto elapsed = end - start;
   fprintf(fplog, "analisados == %d\n", cont);
   fprintf(fplog, "enfileirados == %d\n", pushed);
   return mp(elapsed.count(),u.ff);
  }

  for(auto v: graph[u.ss]){
   heuristica++;
   if(bp[v.ff] > u.ff + v.ss){
    q.push(mp(v.ss + u.ff,v.ff));
    pushed++;
    bp[v.ff] = v.ss + u.ff;
   }
  }
 }
}



void computeAS( pair<int, double> (*fe) (int, int, int&, int&)){
  // cout << "compute1\n";
 for(int i = 0; i < 4; i++){  // Calcular primeiro usando o A*, para preencher a tabela de distancias
    int c = 0;
    int f = 0;
    for(int k = 0; k < 50; k++){
      int pushed = 1;
      int heuristica = 0;
      d = fe(from[f], to[i][k], pushed, heuristica);
      tempo[i][k] = d.ff;
      best_dist[i][k] = d.ss;
      dist[i][k] = d.ss;
      push[i][k] = pushed;
      heuristicas[i][k] = heuristica;
      c++;
      c %= 10;
      if(c == 0)
      	f++;
    }

 }
}

void compute1( pair<int, double> (*fe) (int, int, int&, int&)){
  // cout << "compute1\n";
 for(int i = 0; i < 4; i++){  // Calcular primeiro usando o A*, para preencher a tabela de distancias
   	int c=0;
   	int f = 0;
    for(int k = 0; k < 50; k++){
      int pushed = 1;
      int heuristica = 0;
      d = fe(from[f], to[i][k], pushed, heuristica);
      tempo[i][k] = d.ff;
      best_dist[i][k] = d.ss;
      dist[i][k] = d.ss;
      push[i][k] = pushed;
      c++;
      c %= 10;
      if(c == 0)
      	f++;
    }
  }
}


void compute2( pair<int, double> (*fe) (int, int, int&)){
 for(int i = 0; i < 4; i++){  // Calcular primeiro usando o A*, para preencher a tabela de distancias
    int c = 0;
    int f = 0;
    for(int k = 0; k < 50; k++){
      int pushed = 1;
      int heuristica = 0;
      // cout << "Compute2" << endl;
      d = fe(from[f], to[i][k], pushed);
      tempo[i][k] = d.ff;
      dist[i][k] = d.ss;
      push[i][k] = pushed;
      c++;
      c %= 10;
      if(c == 0)
      	f++;
    }
 }
}

void writeAS(const char * name){
  string t(name);
  string q(name);
  string pushed(name);
  string h(name);
  t += "_t";
  q += "_q";
  pushed += "_pushed";
  h += "_heuristicas";
  FILE *fp = fopen(t.c_str(), "w+");
  FILE *fp2 = fopen(q.c_str(), "w+");
  FILE *fp3 = fopen(pushed.c_str(), "w+");
  FILE *fp4 = fopen(h.c_str(), "w+");
 // Cabeçalho de controle
 fprintf(fp, "%d %d %d\n\n", cat, x, sam);
 fprintf(fp2, "%d %d %d\n\n", cat, x, sam);
 fprintf(fp3, "%d %d %d\n\n", cat, x, sam);
 fprintf(fp4, "%d %d %d\n\n", cat, x, sam);

  // for(int e = 0; e < cat; e++){      // 0 <= i < e
  for(int m = 0; m < 4; m++){           // linha == categoria
     for(int i = 0 ; i < 50; i++){   // A cada 'sam', muda de origem!
       // fprintf(fp2, "1.0"); // Qualidade otima por conta da heuristica admissivel e consistente.
       fprintf(fp, "%d", tempo[m][i]);
       fprintf(fp2, "%.16lf", ( best_dist[m][i] / dist[m][i] ));
       fprintf(fp3, "%d", push[m][i]);
       fprintf(fp4, "%d", heuristicas[m][i]);

      if(i + 1 != 50){
        fprintf(fp, ", ");
        fprintf(fp2, ", ");
        fprintf(fp3, ", ");
        fprintf(fp4, ", ");
      }       
     }
     fprintf(fp, "\n\n");
     fprintf(fp2, "\n\n");
     fprintf(fp3, "\n\n");
     fprintf(fp4, "\n\n");
  }
 // }
 fclose(fp);
 fclose(fp2);
 fclose(fp3);
 fclose(fp4);
}
void write1(const char * name){
  string t(name);
  string q(name);
  string pushed(name);
  t += "_t";
  q += "_q";
  pushed += "_pushed";
  FILE *fp = fopen(t.c_str(), "w+");
  FILE *fp2 = fopen(q.c_str(), "w+");
  FILE *fp3 = fopen(pushed.c_str(), "w+");
 // Cabeçalho de controle
 fprintf(fp, "%d %d %d\n\n", cat, x, sam);
 fprintf(fp2, "%d %d %d\n\n", cat, x, sam);
 fprintf(fp3, "%d %d %d\n\n", cat, x, sam);

  // for(int e = 0; e < cat; e++){      // 0 <= i < e
  for(int m = 0; m < 4; m++){           // linha == categoria
     for(int i = 0 ; i < 50; i++){   // A cada 'sam', muda de origem!
       fprintf(fp, "%d", tempo[m][i]);
       fprintf(fp2, "%.16lf", ( best_dist[m][i] / dist[m][i] ));
       fprintf(fp3, "%d", push[m][i]);
      if(i + 1 != 50){
        fprintf(fp, ", ");
        fprintf(fp2, ", ");
        fprintf(fp3, ", ");
      }       
     }
     fprintf(fp, "\n\n");
     fprintf(fp2, "\n\n");
     fprintf(fp3, "\n\n");
  }
 // }
 fclose(fp);
 fclose(fp2);
 fclose(fp3);
}

int main(){

 le_arqs();
 cin >> x;  // Numero de origens.
 cin >> cat;// Categoriaas de distancia
 cin >> sam;  // Tamanho da "amostra" (destinos por cidade)
 printf("%d %d %d\n", x, cat, sam);
 // Vetores de minimas distancias.

 for(int k = 0; k < 5; k++)  cin >> from[k%5];  // Ler os destinos.

 for(int i = 0; i < cat; i++)  // Numero de categorias
   for(int l = 0; l < x*sam; l++){// Colunas :/
      cin >> to[i][l];
      cout << to[i][l];
      if(((l+1) % 10) == 0){
        cout << "\n";
        if((l+1)%50 == 0)
          cout << "\n";
      }
      else
        cout << ", ";
    }
 cout << "Carregou tabela\n"   ;
 cout << "Carregou tabela\n"   ;
 fplog = fopen("log_calculos", "w+");
 
 computeAS(UCS);
 cout << "\nRodou UCS 1\n";
 writeAS("UCS");
 cout << "\nRodou UCS 2\n";


 computeAS(AS);
cout << "\nRodou AS 1\n";
 writeAS("AS");
cout << "\nRodou AS 2\n";

 compute2(BFS);
cout << "\nRodou BFS 1\n";
 writeAS("BFS");
cout << "\nRodou BFS 2\n";

cout << "Tah de frescura??" << endl;
 compute2(GS);
cout << "\nRodou GS 1\n";
 write1("GS");
cout << "\nRodou GS 2\n";
cout << "BOOM" << endl;
fclose(fplog);
//*/
  return 0;
}