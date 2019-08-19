#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };


extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

//link costs for node 1
int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;

//structure to hold the minimum costs cost node 1
 struct rtpkt  node1;
/* students to write the following two routines, and maybe some others */

//function to initialise the distance table and the min costs for node 1
rtinit1() 
{
	printf("\n\n Function rinit1 is called at t=%f.\n",clocktime);
  int i,j;
  for(i =0; i<4;i++)
{
  for(j =0; j<4;j++)
{
  dt1.costs[i][j] = 999;
}
}
   

  dt1.costs[1][1] =0;
  dt1.costs[0][0] =1;
  dt1.costs[2][2] =1;
  dt1.costs[3][3] =999;
  
  
  node1.sourceid = 1;
  node1.destid = 0;
  node1.mincost[0] = 1;
  node1.mincost[1] = 0;
  node1.mincost[2] = 1;
  node1.mincost[3] = 999;

 for (i =0; i<3;i++)
{
if (i != node1.sourceid)
{
node1.destid = i; 
 tolayer2(node1);
} 
}
}

//function to update the distance table and the min costs for node 1
rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
	printf("\nFunction rupdate1 is called at t=%f\.n",clocktime);
	
	printf(" The source node to Node %d is Node %d.\n\n",rcvdpkt->destid,rcvdpkt->sourceid);
	
	int mincost_recalc,dtbl_recalc,i,source =rcvdpkt->sourceid;
	
	for (i = 0;i<4;i++){

		if (connectcosts1[source] + rcvdpkt->mincost[i] < dt1.costs[i][source])
		{
			dt1.costs[i][source] = connectcosts1[source] + rcvdpkt->mincost[i];
			dtbl_recalc =1;
		}

		if ( connectcosts1[source] + rcvdpkt->mincost[i]<node1.mincost[i])
		{
			node1.mincost[i] =connectcosts1[source] + rcvdpkt->mincost[i];
			mincost_recalc =1;
		}
	}
//checking if there is any change to the distance tables	
	if (dtbl_recalc == 1)
	{
		printf("\n The distance table of node %d has been recalculated.\n", rcvdpkt->destid);
	}
	
	printdt1(&dt1);
//sending the updated min costs to the other tables	
	if(dtbl_recalc ==1 ||mincost_recalc == 1){
		for (i =0; i<3;i++)
		{
			if(node1.sourceid !=i){
				printf(" Sending messages to Node %d from Node %d.\n", i, node1.sourceid);
				 node1.destid = i; 
				 tolayer2(node1);
			}
		} 
	   
	}			


}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}



