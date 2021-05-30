#include <iostream>
using namespace std;
class Graph
{
public:
    Graph(int n);
    ~Graph();
    void print()const;
    int**& getMatrix();
    int getVertexCnt() const{return n_;}
private:
    int**	matrix_;
    int		n_;
};

int**&
Graph::getMatrix()
{
    return matrix_;
}
void
Graph::print()const
{
    cout << "[adjacency matrix]" << endl;
    int i, j;
    for (i = 0; i < n_; i++) {
        for (j = 0; j < n_; j++)
            cout << matrix_[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

Graph::Graph(int n): n_(n), matrix_(new int*[n])
{
    int i, j;
    for (i = 0; i < n; i++) {
        matrix_[i] = new int[n];
        for (j = 0; j < n; j++)
            matrix_[i][j] = 0;
    }
}

Graph::~Graph()
{
    for (int i = 0; i < n_; i++)
        delete[] matrix_[i];
    delete[]matrix_;
}

int minKeyIndex(char status[],int key[],int u)
{
    int minkey=INT16_MAX;
    int index;
    for(int i=0;i<u;i++)
    {
        if(status[i]=='q' && key[i]<minkey)
        {
            index=i;
            minkey=key[i];
        }
    }
    return index;
}

Graph*
primsMST(Graph* graph)
{
    int n=graph->getVertexCnt();
    char* status=new char[n];
    int* parent=new int[n];
    int* key=new int[n];

    for (int i = 0; i < n; ++i) {
        status[i]='q';
        key[i]=INT16_MAX;
    }
    parent[0]=-1;
    key[0]=0;
    for (int i = 0; i < n-1; i++)
    {
        int u=minKeyIndex(status,key,n);
        status[u]='t';
        for(int j=0;j<n;j++)
        {
            if(graph->getMatrix()[u][j] &&
                status[j]=='q' && graph->getMatrix()[u][j]<key[j])
            {
                parent[j]=u;
                key[j]=graph->getMatrix()[u][j];
            }
        }
    }

    Graph* graph1=new Graph(n);
    int**& matrix=graph1->getMatrix();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==parent[j])
            {
                matrix[i][j]=key[j];
                matrix[j][i]=key[j];
            }
        }
    }
    return graph1;
}
int minDistance(char status[],int distance[],int u)
{
    int minDis=INT16_MAX;
    int index;
    for(int i=0;i<u;i++)
    {
        if(status[i] == 'q' && distance[i]<=minDis)
        {
            index=i;
            minDis=distance[i];
        }
    }
    return index;
}

Graph*
dijkstrasSSSP(Graph* graph)
{
    int n=graph->getVertexCnt();
    char* status=new char[n];
    int* pred=new int [n];
    int* distance=new int[n];
    for(int i=0;i<n;i++)
    {
        status[i]='q';
        distance[i]=INT16_MAX;
    }
    pred[0]=-1;
    distance[0]=0;

    for(int i=0;i<n-1;i++)
    {
        int u=minDistance(status,distance,n);
        status[u]='t';
        for(int j=0;j<n;j++)
        {
            if(graph->getMatrix()[u][j] && status[j]=='q' && distance[u]<INT16_MAX &&
                    distance[j]>distance[u]+graph->getMatrix()[u][j])
            {
                pred[j]=u;
                distance[j]=distance[u]+graph->getMatrix()[u][j];
            }
        }
    }
    Graph* graph1=new Graph(n);
    int**& matrix=graph1->getMatrix();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(pred[j]==i)
            {
                matrix[i][j]=distance[j];
            }
        }
    }
    return graph1;
}


Graph*
createPrimsInstance() {
    int n = 6;
    Graph* result = new Graph(n);
    int**& matrix = result->getMatrix();
    matrix[0][1] = 4; matrix[0][3] = 3; matrix[0][4] = 1;
    matrix[1][0] = 4; matrix[1][2] = 3; matrix[1][5] = 4;
    matrix[2][1] = 3; matrix[2][3] = 2;
    matrix[3][0] = 3; matrix[3][2] = 2; matrix[3][4] = 4;
    matrix[4][0] = 1; matrix[4][3] = 4; matrix[4][5] = 2;
    matrix[5][1] = 4; matrix[5][4] = 2;
    return result;
}

Graph*
createDijkstrasInstance() {
    int n = 6;
    Graph* result = new Graph(n);
    int**& matrix = result->getMatrix();
    matrix[0][1] = 9; matrix[0][3] = 8; matrix[0][4] = 1;
    matrix[1][2] = 4;
    matrix[3][2] = 1;
    matrix[4][3] = 5; matrix[4][5] = 2;
    matrix[5][1] = 3;
    return result;
}

int main()
{
    Graph* primsInstance = createPrimsInstance();
    cout << "***** PRIMS INSTANCE *****" << endl;
    primsInstance->print();
    cout << "- - - PRIMS MST - - -" << endl;
    Graph* MST = primsMST(primsInstance);
    MST->print();

    Graph* dijkstrasInstance = createDijkstrasInstance();
    cout << endl << "***** DIJKSTRAS INSTANCE ******" << endl;
    dijkstrasInstance->print();
    cout << "- - - DIJKSTRAS SSSP - - -" << endl;
    Graph* SSSP = dijkstrasSSSP(dijkstrasInstance);
    SSSP->print();

    return 0;
}

