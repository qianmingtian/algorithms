/*
 * @Author: 千铭天
 * @Date: 2019-11-22 15:43:43
 * @LastEditors: 
 * @LastEditTime: 2019-11-22 16:08:44
 * @Description:  
 */
#include <stdlib.h>
#define MAXVEX 32
#define INFINITY 65535
typedef struct
{
    int numVertexes;
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
} MGraph;
struct olsr_topo_list
{
    int T_dest_addr;
    int T_last_addr;
    int T_measure; //Todo
    int T_seq;
    double T_time;
};

void GreateMGraph(MGraph *G, int topo_flag, struct olsr_topo_list topo_list[3])
{

    G->numVertexes = topo_flag + 1;
    for (int i = 0; i < G->numVertexes - 1; i++) //Reading vertex information and establishing a vertex table
    {
        G->vexs[i] = topo_list[i].T_dest_addr;
    }
    G->vexs[topo_flag] = 2;
    for (int i = 0; i < G->numVertexes; i++)
    {
        for (int j = 0; j < G->numVertexes; j++)
            G->arc[i][j] = INFINITY;
    }
    for (int i = 0; i < topo_flag; i++)
    {
        for (int k = 0; k < G->numVertexes; k++)
        {
            if (topo_list[i].T_last_addr == G->vexs[k])
            {
                G->arc[i][k] = topo_list[i].T_measure;
                G->arc[k][i] = G->arc[i][k];
            }
        }
    }
}
int main()
{
    int topo_flag = 3;
    //MGraph *G = '\0';
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph)); //'\0';
    G->numVertexes = 0;
    struct olsr_topo_list topo_list[3];
    topo_list[0].T_dest_addr = 1;
    topo_list[1].T_dest_addr = 3;
    topo_list[2].T_dest_addr = 4;
    topo_list[0].T_last_addr = 2;
    topo_list[1].T_last_addr = 2;
    topo_list[2].T_last_addr = 1;
    topo_list[0].T_measure = 4;
    topo_list[1].T_measure = 3;
    topo_list[2].T_measure = 1;
    GreateMGraph(G, topo_flag, topo_list);
    return 0;
}
