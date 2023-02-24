/// stack

push(STACK s, x)
	top++
	IF top > stack_size
		overflow
	ELSE
		s[top] = x




pop(STACK s)
	IF top == 0
		underflow
	ELSE 
		RETURN s(top)
		top--

STACK s
visited[ ]
DFS(v)
         push( s, v )
         WHILE NOT isEmpty( s ) 
                  v ← pop(s)
                  IF NOT visited[v]
                           visit( v )
                           FOR each w in adjacency( v )
                                                  IF NOT visited[w]
                                                              push(s, w)


typedef struct DATA
{
	int a;
	int b;
}DATA;


DATA stack[10000] = {0};
int step = 0;


void Push(DATA a)
{
	stack[step++] = a;
}

void Pop()
{
	step--;
}

//////////////////////////////////////
BFS
BFS(G, v) // graph G, starting point of search v
    generate queue
    insert the statting point v to the queue
    indicate the point v as visited
    while queue is not empty
        t <- return the first element of queue
        for every line connected to t
            u <- neighboring point of t
            if u is no visited
            insert u into queue, nad inidcated as visited
            
//////////////////////////////////////////////////
DFS -lteration
stack s
visited[]
DFS9(v)
    push(s, v)
    while not is empty(s)
    v <- pop(s)
    if not visited[v]
        visit(v)
        for each w in adjacency(v)
            if not visisted[w]
                push(s, w)

///////////////////////////////////////////////////
DFS - recursion
DFS(g,v)
    visite[v] <= true
    for each all w in adjececy(G, v)
        if visited[w] is false
            DFS(g, w);
//////////////////////////////////////////////
DP
int dp(int i)
{
    int& ans = d[i];
    if (ans > 0) 
        return ans;
    ans = 1;
    for (int j = 1; j <= n; j++)
        if (G[i][j]) 
            ans = max(ans, dp(j)+1);
    return ans;
}

--------------------------------------------------------------
// floyd al, to get any two nodes (i & j) shorttest distance 
// init
d[i][i] = 0;
other d[i][j] = INF

for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            

/////////////////////////////////////////////////////////////////////////////////
// Kruskal, MST: minial spanning tree 
there are n nodes
there are m edges
u[i], v[i], w[i]
i is edje
r[i] is sorted edject info
int cmp(const int i, const int j)
{
    return w[i]<w[j];
}
int findRoot(int x)
{
    return p[x] == x ? x : p[x] = find(p[x]);
}
int kruskal()
{
    int ans = 0;
    for (i = 0; i < n; i++)
        p[i] = i;
    
    for (int i = 0; i < m; i++)
        r[i] = i;
    
    sort(r, r+m; cmp);
    
    for (int i = 0; i<m; i++)
    {
        int e = r[i];
        int x = find(u[e]);
        int y = find(v[e]);
        int (x != y)
        {
            ans += w[e];
            p[x] = y;
        }
    }
    
    return ans;
}

////////////////////////////////////////////////////////////////////////////////////////
// dijkstra 
// single source shourttest path
there are n nodes
memset(v, 0, sizeof(v));
for (int i = 0; i < n; i++)
    d[i] = (i==0 ? 0; INF);
for (int i = 0; i < n; i++)
{
    int x = 0;
    int m = INF;
    for (int y = 0; y < n; y++)
    {
        if (!v[y] && d[y] <=m)
            m = d[x=y];
    }
    
    v[x] = 1;
    
    for (int y = 0; y < n; y++)
    {
        d[y] = min(D[y], D[x] + W[x][y]);
    }    
}

//////////////////////////////////////
BFS
BFS(G, v) // graph G, starting point of search v
    generate queue
    insert the statting point v to the queue
    indicate the point v as visited
    while queue is not empty
        t <- return the first element of queue
        for every line connected to t
            u <- neighboring point of t
            if u is no visited
            insert u into queue, nad inidcated as visited
            
//////////////////////////////////////////////////
DFS -lteration
stack s
visited[]
DFS9(v)
    push(s, v)
    while not is empty(s)
    v <- pop(s)
    if not visited[v]
        visit(v)
        for each w in adjacency(v)
            if not visisted[w]
                push(s, w)

///////////////////////////////////////////////////
DFS - recursion
DFS(g,v)
    visite[v] <= true
    for each all w in adjececy(G, v)
        if visited[w] is false
            DFS(g, w);
//////////////////////////////////////////////
DP
int dp(int i)
{
    int& ans = d[i];
    if (ans > 0) 
        return ans;
    ans = 1;
    for (int j = 1; j <= n; j++)
        if (G[i][j]) 
            ans = max(ans, dp(j)+1);
    return ans;
}
                                
                                
