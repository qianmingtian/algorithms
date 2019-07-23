#include "routing.h"
// #include <stddef.h>
#define USER_NUM 16
/* TODOLIST:
	1.USER_NUM引入（local_variable）

*/
int neighbor[USER_NUM] = {1, 2, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int neighbor_link_quality[USER_NUM] = {0, 4, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int two_hop_neighbor[USER_NUM][USER_NUM] = {
	{1, 0, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0}};
int two_hop_neighbor_link_quality[USER_NUM][USER_NUM] = {
	{0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0}};

typedef struct route_link
{
	ui8_t dest_addr;
	ui8_t next_addr;
	ui8_t source_addr;
	fi32_t link_quality;
	struct route_link *next;
} route_table;

struct routing
{
	ui8_t dest_addr;
	ui8_t next_addr;
	fi32_t max_quality;
	ui8_t result_symbol;
};

route_table *route_table_head = NULL; //TODO :全局变量初始化时

void generate_route_table(void)
{
	route_table *prev, *current, *clean_tmp;

	clean_tmp = NULL;

	//clean the previous table
	while (route_table_head != NULL)
	{
		clean_tmp = route_table_head->next;
		free(route_table_head);
		route_table_head = clean_tmp;
	}

	//generate or update the table
	for (int i = 1; i <= USER_NUM; i++)
	{
		if (neighbor[i - 1] != 0)
		{
			current = (route_table *)malloc(sizeof(route_table));
			if (route_table_head == NULL)
			{
				route_table_head = current;
			}
			else
			{
				prev->next = current;
			}
			//TODO : 本地变量存储发送节点的地址？接收函数同步本地信息未完成？
			//   local_variable.src;
			// current->source_addr =   ;
			current->dest_addr = i;
			current->next_addr = i;
			current->link_quality = neighbor_link_quality[i - 1];
			current->next = NULL;

			prev = current;

			//2-hop
			for (int j = 1; j <= USER_NUM; j++)
			{
				if (two_hop_neighbor[i - 1][j - 1] != 0)
				{
					current = (route_table *)malloc(sizeof(route_table));
					if (route_table_head == NULL)
					{
						route_table_head = current;
					}
					else
					{
						prev->next = current;
					}
					//TODO : 本地变量存储发送节点的地址？接收函数同步本地信息未完成？
					//   local_variable.src;
					// current->source_addr =   ;
					current->next_addr = i;
					current->dest_addr = j;
					current->link_quality = (fi32_t)(neighbor_link_quality[i - 1] * two_hop_neighbor_link_quality[i - 1][j - 1]) /
											(neighbor_link_quality[i - 1] + two_hop_neighbor_link_quality[i - 1][j - 1]);

					current->next = NULL;
					prev = current;
				}
			}
		}
	}
}

struct routing *lookup_routing(int dest_addr)
{
	struct routing *routing_result;
	route_table *current;

	//obtain current routing table
	current = route_table_head;
	routing_result = (struct routing *)malloc(sizeof(struct routing));
	routing_result->max_quality = 0;
	routing_result->result_symbol = 0;

	//search 1-hop and 2-hop routing table
	while (current != NULL)
	{
		if (dest_addr == current->dest_addr)
		{
			if (current->link_quality > routing_result->max_quality)
			{
				routing_result->dest_addr = current->dest_addr;
				routing_result->next_addr = current->next_addr;
				routing_result->max_quality = current->link_quality;
				routing_result->result_symbol = 1;
			}
		}
		current = current->next;
	}
	return routing_result;
}

int main()
{
	generate_route_table;
	lookup_routing(3);
	return 0;
}