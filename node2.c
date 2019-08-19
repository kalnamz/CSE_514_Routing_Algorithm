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
} dt2;

// link costs for node 2
int cv2[4] = {3,1,0,2};
/* students to write the following two routines, and maybe some others */
// structure to store the min costs
struct rtpkt  node2;

//function to initialise the distance table and the min costs for node 2
void rtinit2() 
{
	printf("\n Function rinit2 is called at t=%f.\n",clocktime);	
	 int i,j;
	  for(i =0; i<4;i++)
	{
	  for(j =0; j<4;j++)
	{
	  dt2.costs[i][j] = 999;
	}
	}
	   for(j =0; j<4;j++)
	{
	  dt2.costs[2][j] = 0;
	}

	  dt2.costs[2][2] =0;
	  dt2.costs[1][1] =1;
	  dt2.costs[0][0] =3;
	  dt2.costs[3][3] =2;
	  
	  node2.sourceid = 2; 
	  node2.destid = 1;
	  node2.mincost[0] = 3;
	  node2.mincost[1] = 1;
	  node2.mincost[2] = 0;
	  node2.mincost[3] = 2;

	  for (i =0; i<4;i++)
	{

	 if( i != node2.sourceid)
	{
	 node2.destid = i; 
	 tolayer2(node2);
	} 
	}
}

//function to update the distance table and the min costs for node 2
void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
	printf("\n\n Function rupdate2 is called at t=%f.\n",clocktime); 
	printf("\n\n The source node to node %d is node %d.\n\n",rcvdpkt->destid,rcvdpkt->sourceid);
	
	int dtbl_recalc,mincost_recalc,i,source =rcvdpkt->sourceid;
	
	for (i = 0;i<4;i++){
		if (cv2[source] + rcvdpkt->mincost[i] < dt2.costs[i][source])
		{
			dtbl_recalc =1;
			dt2.costs[i][source] = cv2[source] + rcvdpkt->mincost[i]; 
		}
		
		if ( cv2[source] + rcvdpkt->mincost[i]<node2.mincost[i])
		{
		   node2.mincost[i] =cv2[source] + rcvdpkt->mincost[i];
		   mincost_recalc =1;
		}
	}
//checking if there is any change to the distance tables
	if (dtbl_recalc == 1)
	{
	  printf("\nThe distance table of node %d has been recalculated.\n", rcvdpkt->destid);
	} 
	  printdt2(&dt2);
//sending the updated min costs to the other tables		  
	if(dtbl_recalc == 1 || mincost_recalc ==1){
		for (i =0; i<4;i++)
		{
			if(node2.sourceid !=i){
			    printf("Sending messages to Node %d from Node %d.\n", i, node2.sourceid);
				node2.destid = i; 
				tolayer2(node2);
		     } 
		}
	   
	}
}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}








