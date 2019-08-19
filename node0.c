#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to 4 0 ... 3 */
  };

 
extern int TRACE;
extern int YES;
extern int NO;
extern float clocktime;

// link costs for node 0
int cvo[4] = {0,1,3,7};

struct distance_table 
{
  int costs[4][4];
} dt0;

// structure to hold the minimum costs for node 0
 struct rtpkt  node0;
/* students to write the following two routines, and maybe some others */



//function to initialise the distance table and the min costs for node 0
void rtinit0() 
{ 
  printf("\n\n Function rinit0 is called at t=%f.\n",clocktime); 
  int i,j;
  for(i =0; i<4;i++)
{
  for(j =0; j<4;j++)
{
  dt0.costs[i][j] = 999;
}
}

  dt0.costs[0][0] =0;
  dt0.costs[1][1] =1;
  dt0.costs[2][2] =3;
  dt0.costs[3][3] =7;
  
  node0.sourceid = 0; 
  node0.destid = 1;
  node0.mincost[0] = 0;
  node0.mincost[1] = 1;
  node0.mincost[2] = 3;
  node0.mincost[3] = 7; 
 
  for (i =1; i<4;i++)
	{
	if (i != node0.sourceid)
	{
	  node0.destid = i;
	  tolayer2(node0);
	} 
	}  

}


//function to update the distance table and the min costs for node 0
void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
	printf("\n\n Function rupdate0 is called at t=%f.\n",clocktime);
	printf(" The source node to Node %d is Node %d.\n\n",rcvdpkt->destid,rcvdpkt->sourceid);
	
	int mincost_recalc,dtbl_recalc,i,source =rcvdpkt->sourceid;
	
	for (i = 0;i<4;i++){
		if (cvo[source] + rcvdpkt->mincost[i] < dt0.costs[i][source])
		{
			dt0.costs[i][source] = cvo[source] + rcvdpkt->mincost[i]; 
			dtbl_recalc =1;
		}
		if ( cvo[source] + rcvdpkt->mincost[i]<node0.mincost[i])
		{
			mincost_recalc =1;
			node0.mincost[i] =cvo[source] + rcvdpkt->mincost[i];
		}
	}
//checking if there is any change to the distance tables
	if (dtbl_recalc == 1)
	{
		printf(" The distance table of node %d has been recalculated.\n\n", rcvdpkt->destid);
	}

	printdt0(&dt0);
//sending the updated min costs to the other tables	
	if(dtbl_recalc ==1 ||mincost_recalc == 1){
		for (i =0; i<4;i++)
	   {
		  if(node0.sourceid !=i){
	         printf(" Sending messages to Node %d from Node %d.\n", i, node0.sourceid);	 
		     node0.destid = i; 
		     tolayer2(node0);}
		  } 
	   }
}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


