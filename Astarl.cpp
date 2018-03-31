#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef pair<lli, lli> ii;
typedef vector<lli> vi;
typedef vector<ii> vii;
#define INF 1000000000

vector< pair<lli,lli> > m;	//for storing the coordinates


lli heuristic(lli v, lli t)
{
	return (lli) (sqrt( (m[v].first - m[t].first)*(m[v].first - m[t].first) + (m[v].second - m[t].second)*(m[v].second - m[t].second) ));
}

int main(void) 
{
	//freopen("03","r",stdin);
	//freopen("A.out","w",stdout);
	lli V, E, u, v, w;
	vector<vii> AdjList;

	scanf("%lld %lld", &V, &E);

	//getting the coordinates
	for(lli i=0; i<V; i++)
	{
		lli x,y;
		cin >> x >> y;
		m.push_back(make_pair(x,y));
	}
	vector< pair<lli,lli> >::iterator it;

	AdjList.assign(V, vii()); // assign blank vectors of pair<lli, lli>s to AdjList
	for (lli i = 0; i < E; i++)
	{
	    scanf("%lld %lld %lld", &u, &v, &w);
	    u--; v--;
	    AdjList[u].push_back(ii(v, w));                              // directed graph
	}
	
	lli q;
	cin >> q;
	while(q--)
	{
		lli s,t;
		cin >> s >> t;
		s--; t--;
		  // Dijkstra routine
		vi dist(V, INF); dist[s] = heuristic(s,t);                // INF = 1B to avoid overflow
		vi distr(V, INF); distr[s] = 0;
		vi vis(V,-1); 
		priority_queue< ii, vector<ii>, greater<ii> > pq;
		pq.push(ii(heuristic(s,t),s));
		while (!pq.empty()) 
		{                                             // main loop
		    ii front = pq.top(); pq.pop();     // greedy: pick shortest unvisited vertex
		    lli d = front.first, u = front.second;
		    lli flag = 0;
		    vis[u] = 1;
		    if (d > dist[u]) continue;   
		    if(u == t)
		    	break;
		    for (lli j = 0; j < (lli)AdjList[u].size(); j++) 
		    {
		    	ii v = AdjList[u][j];
		    	                       // all outgoing edges from u
			    
			    if(vis[v.first] != 1){
				if (distr[u] + v.second < distr[v.first] )
				{
				   dist[v.first] = distr[u] + v.second + heuristic(v.first, t);
			       distr[v.first] = distr[u] + v.second;
				   pq.push(ii(dist[v.first], v.first));
				   vis[v.first] = 0;
				}}
			}
		}
		if(distr[t] == INF)
			cout << "-1\n";
		else
			cout << distr[t]  << "\n";
		//lli vis(0);
		/*for(lli i=0; i<distr.size(); i++)
		{
			if(distr[i] != INF)
				vis++;
		}
		cout << "visited number of nodes : " << vis << "\n";*/
	}
	return 0;
}