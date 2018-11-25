// Calculates first and second minimum distance from stop when user inputs starting point
#include <iostream>
#include <cstdlib>
#include <cstdio>      
#include <conio.h>
#include <cmath>

using namespace std;

  int main()
  {
	double a[13][2]={{22.4162, 39.6388},
			 {22.4198, 39.6391},
			 {22.4223, 39.6379},
			 {22.4249, 39.6355},
			 {22.4271, 39.6333},
			 {22.4244, 39.6370},
			 {22.4205, 39.6391},
			 {22.4184, 39.6397},
			 {22.4167, 39.6398},
			 {22.4204, 39.6376},
			 {22.4219, 39.6327},
			 {22.4227, 39.6302},
			 {22.4184, 39.6427}};

		double lat1,long1,smallest,secondsmallest;
		double PI = 4.0*atan(1.0);
		const double earth=6378.137;  //The IUGG value for the equatorial radius of the Earth
		double dist[13];
		int foo=0,input;

	do{
		puts("1. Start point\n2. End point");
		cin >> input;
		switch(input)
		{
			case 1:
//---------------------------------------Calculate r-----------------------------------------------
		puts("Coordinates of route's start point: ");
		cin >> lat1 >> long1 ;
		
       
		for (int i=0;i<13;i++)
		{ 

			double dlat1=lat1*(PI/180);

			double dlong1=long1*(PI/180);
			double dlat2=a[i][0]*(PI/180);
			double dlong2=a[i][1]*(PI/180);

			double dLong=dlong1-dlong2;
			double dLat=dlat1-dlat2;

			double aHarv= pow(sin(dLat/2.0),2.0)+cos(dlat1)*cos(dlat2)*pow(sin(dLong/2),2);
			double cHarv=2*atan2(sqrt(aHarv),sqrt(1.0-aHarv));
			dist[i]=(earth*cHarv)/(0.00092*60); //se lepta

			//cout <<"\nH Distance in point of " << id[i] << "stop from start point is: \n" << dist[i] << endl;
		}   

	   //Main distance calculation from starting point 
		if (dist[0] < dist[1]){
			smallest = dist[0];
			secondsmallest = dist[1];} 
		else{
			smallest = dist[1];
			secondsmallest = dist[0];}

		for(int i = 2; i < 12; i++){
			if (dist[i] < smallest){
				secondsmallest = smallest;
				smallest = dist[i];} 
			else if (dist[i] < secondsmallest){
				secondsmallest = dist[i];}
		}

		for(int i = 0; i < 13; i++){
			if (dist[i] == smallest){
				cout <<"\nStop with smallest distance: r1= "<< i << endl;}
			if (dist[i] == secondsmallest){
			cout <<"\nStop with 2nd smallest distance: r2= "<< i << endl;}
		}
		cout <<"\nSmallest distance: "<< smallest <<"\nand 2nd smallest distance: "<< secondsmallest << "\n" << endl;
		break;
		

			
			case 2:
//------------------------------------------------Calculate s--------------------------------------------------	
		puts("\nCoordinates of route's end point: ");
		cin >> lat1 >> long1;

		for (int i=0;i<13;i++)
		{ 
			double dlat1=lat1*(PI/180);

			double dlong1=long1*(PI/180);
			double dlat2=a[i][0]*(PI/180);
			double dlong2=a[i][1]*(PI/180);

			double dLong=dlong1-dlong2;
			double dLat=dlat1-dlat2;

			double aHarv= pow(sin(dLat/2.0),2.0)+cos(dlat1)*cos(dlat2)*pow(sin(dLong/2),2);
			double cHarv=2*atan2(sqrt(aHarv),sqrt(1.0-aHarv));
			dist[i]=(earth*cHarv)/(0.00092*60); //se lepta

			//cout <<"\nDistance in minutes of " << id[i] << "stop from start point is: \n" << dist[i] << endl;
		}    
   
			//Main distance calculation from ending point
			if (dist[0] < dist[1]){
				smallest = dist[0];
				secondsmallest = dist[1];} 
			else{
				smallest = dist[1];
				secondsmallest = dist[0];}

			for(int i = 2; i < 12; i++){
				if (dist[i] < smallest){
				secondsmallest = smallest;
				smallest = dist[i];} 
				else if (dist[i] < secondsmallest){
				secondsmallest = dist[i];}
     }

	 for(int i = 0; i < 13; i++){
		 if (dist[i] == smallest){
			cout <<"\nStop with smallest distance: s1= "<< i << endl;}
			if (dist[i] == secondsmallest){
			cout <<"\nStop with 2nd smallest distance:s2= "<< i << endl;}
	 }
	 cout <<"\nSmallest distance: "<< smallest <<"\n and 2nd smallest distance: "<< secondsmallest <<"\n" << endl;
	 break;
	 
//----------------------------------Error--------------------------------------
		default:
		puts("Invalid option, try again\n");
		break;
	}

	 foo++;
}while(foo<2);

    system("PAUSE");
    return 0;
}
