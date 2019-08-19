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

struct distance_table 
{
  int costs[4][4];
} dt3;

// the link costs for node 3
int cv3[4] = {7,999,2,0};

/* students to write the following two routines, and maybe some others */
struct rtpkt  node3;

//function to initialise the distance table and the min costs for node 3
void rtinit3() 
{
	
  printf("\n\n Function rinit3 is called at t=%f.\n",clocktime);	
  int i,j;
  for(i =0; i<4;i++)
{
  for(j =0; j<4;j++)
 {
  dt3.costs[i][j] = 999;
 }
} 

  dt3.costs[1][1] = 999;
  dt3.costs[0][0] = 7;
  dt3.costs[2][2] = 2;
  dt3.costs[3][3] = 0;
  
  node3.sourceid = 3; 
  node3.destid = 0;
  node3.mincost[0] = 7;
  node3.mincost[1] = 999;
  node3.mincost[2] = 2;
  node3.mincost[3] = 0;

 for (i =0; i<4;i++)
 {
  if (i != node3.sourceid && i!=1)
  {
   node3.destid = i; 
   tolayer2(node3);
  }  
 }
}

//function to update the distance table and the min costs for node 3
void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt; 
{
	printf("\nFunction rupdate3 is called at t=%f.\n",clocktime);
	printf(" The source node to node %d is node %d.\n\n",rcvdpkt->destid,rcvdpkt->sourceid);
	
	int dtbl_recalc, mincost_recalc,i,source =rcvdpkt->sourceid;
	
	for (i = 0;i<4;i++){
	   if (cv3[source] + rcvdpkt->mincost[i] < dt3.costs[i][source])
	   {
	      dt3.costs[i][source] = cv3[source] + rcvdpkt->mincost[i];
	      dtbl_recalc =1;
	   }
	  if ( cv3[source] + rcvdpkt->mincost[i]<node3.mincost[i])
	  {
	      node3.mincost[i] =cv3[source] + rcvdpkt->mincost[i];
	      mincost_recalc =1;
	  }
	}
//checking if there is any change to the distance tables
	if (dtbl_recalc == 1)
	  {
	    printf(" The distance table of node %d has been recalculated.\n\n", rcvdpkt->destid);
   	  }
// printing the distance table
	  printdt3(&dt3);

//sending the updated min costs to the other tables	  
	if(dtbl_recalc == 1 || mincost_recalc == 1){
	
		for (i =0; i<4;i++)
		{
			if(node3.sourceid !=i && i!=1){
				printf("\n Sending messages to Node %d from Node %d.\n", i, node3.sourceid);
				node3.destid = i; 
				tolayer2(node3);
			}
		} 
		   
	}

}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}








