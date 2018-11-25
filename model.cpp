#include <ilcplex/ilocplex.h>
ILOSTLBEGIN
int main (){
int i,j,k,k1,k2,m,r,s; 
const int imax=13;
const int kmax=5;
const int jmax=13;
puts("Type start stop and end stop of route: ");
     cin >> r >> s;
double CX[imax][jmax][kmax];

//Initialize matrix C with 10 ^ 6
double C[imax][jmax][kmax];

//--------------------------------------------- FIND USABLE ROUTES -------------------------------------------------------
double K[kmax];
double I[imax];
double J[jmax];
for (i=0;i<imax;i++){
	for (j=0;j<jmax;j++){
		for (k=0;k<kmax;k++){
			C[i][j][k]=1000000;
			CX[i][j][k]=1000000;
		}
	}
}
//Declaration of table values between 2 consecutive stops of the 2 transport modes
C[0][1][0]=1;
C[1][2][0]=1;
C[2][3][0]=1;
C[3][4][0]=1;

C[5][6][1]=1;
C[6][7][1]=1;
C[7][8][1]=1;
C[8][0][1]=1;

C[0][1][2]=2;
C[1][9][2]=1;
C[9][3][2]=2;
C[3][10][2]=2;
C[10][11][2]=2;

C[7][12][3]=1;
C[12][8][3]=2;
C[8][0][3]=1;

//Following values have as upper limit the highest distance (552 m or 10 min) 
//of consecutive network stops and concern the 5th mode of walking (k=4)

//a)Between stops of the same trasport mode
C[0][1][4]=7;
C[1][2][4]=6;
C[2][3][4]=7;
C[3][4][4]=6;
C[5][6][4]=9;
C[6][7][4]=4;
C[6][8][4]=8;
C[7][8][4]=4;
C[8][0][4]=2;
C[1][9][4]=3;
C[9][3][4]=10;
C[3][10][4]=8;
C[10][11][4]=5;
C[7][12][4]=6;
C[12][8][4]=6;
C[8][0][4]=2;

C[1][0][4]=7;
C[2][1][4]=6;
C[3][2][4]=7;
C[4][3][4]=6;
C[6][5][4]=9;
C[7][6][4]=4;
C[8][7][4]=4;
C[0][8][4]=2;
C[9][1][4]=3;
C[3][9][4]=10;
C[10][3][4]=8;
C[11][10][4]=5;
C[12][7][4]=6;
C[8][12][4]=6;
C[0][8][4]=2;

//b)Between stops of different trasport modes
C[0][6][4]=9;
C[6][0][4]=9;
C[0][7][4]=5;
C[7][0][4]=5;
C[0][9][4]=9;
C[9][0][4]=9;
C[0][12][4]=9;
C[12][0][4]=9;
C[1][5][4]=10;
C[5][1][4]=10;
C[1][6][4]=1;
C[6][1][4]=1;
C[1][7][4]=3;
C[7][1][4]=3;
C[1][8][4]=6;
C[8][1][4]=6;
C[1][9][4]=3;
C[9][1][4]=3;
C[1][12][4]=7;
C[12][1][4]=7;
C[2][5][4]=5;
C[5][2][4]=5;
C[2][6][4]=4;
C[6][2][4]=4;
C[2][7][4]=9;
C[7][2][4]=9;
C[2][8][4]=6;
C[8][2][4]=6;
C[2][9][4]=4;
C[9][2][4]=4;
C[2][10][4]=10;
C[10][2][4]=10;
C[3][5][4]=3;
C[5][3][4]=3;
C[3][9][4]=10;
C[9][3][4]=10;
C[3][10][4]=8;
C[10][3][4]=8;
C[4][5][4]=9;
C[5][4][4]=9;
C[5][9][4]=8;
C[9][5][4]=8;
C[5][10][4]=9;
C[10][5][4]=9;
C[6][9][4]=3;
C[9][6][4]=3;
C[6][12][4]=8;
C[12][6][4]=8;
C[7][9][4]=6;
C[9][7][4]=6;
C[7][12][4]=6;
C[12][7][4]=6;
C[8][9][4]=9;
C[9][8][4]=9;
C[8][12][4]=6;
C[12][8][4]=6;
C[9][10][4]=10;
C[10][9][4]=10;

//---------------------------------------------- FIND USABLE ROUTES ----------------------------------------------------

//find transport modes (except walking) where start stops r and finish stops s belong
for (i=0;i<imax;i++){
	for (j=0;j<jmax;j++){
		for (k=0;k<kmax;k++){
			if(k!=kmax-1){
				if (C[r][j][k]!=1000000 || C[i][s][k]!=1000000){
					K[k]=k;					
				}
			}
		}
	}
}
for (k=0;k<kmax;k++){
	if(k!=kmax-1){
		if (K[k]!=k){
			K[k]=1000000;					
		}
	}
}
//find transport mode stops where only r,s belong
for (i=0;i<imax;i++){
	for (j=0;j<jmax;j++){
		for (k=0;k<kmax;k++){
			if(k!=kmax-1 && C[i][j][k]!=1000000){
				if (K[k]!=1000000){
					I[i]=i;
					J[j]=j;
				}
			}
		}
	}
}
for (i=0;i<imax;i++){
	if (I[i]!=i){
			I[i]=1000000;					
	}
}
for (j=0;j<jmax;j++){
	if (J[j]!=j){
			J[j]=1000000;					
	}
}
//for stops from i to j which don't belong in the above found, we do C = 10 ^ 6
for (i=0;i<imax;i++){
	for (j=0;j<jmax;j++){
		for (k=0;k<kmax;k++){
			if(k!=kmax-1){
				if (I[i]!=i || J[j]!=j){					
					C[i][j][k]=1000000;
				}	
			}
		}
	}
}
//------------------------------------------- END OF FIND USABLE ROUTES --------------------------------------------------------

IloEnv env;
	try {
		IloModel model (env);

typedef IloArray<IloNumVarArray> IloNumVarMatrix2x2;
typedef IloArray<IloNumVarMatrix2x2> IloNumVarMatrix3x3;

typedef IloArray<IloRangeArray> IloRangeMatrix2x2;
typedef IloArray<IloRangeMatrix2x2> IloRangeMatrix3x3;

IloCplex cplex(env);

//-----------------------------  Decision Variable X ---------------------------------------
IloNumVarMatrix3x3 Xijk(env,0);
for (i=0;i<imax;i++){
	IloNumVarMatrix2x2 Xjk(env,0);
	for (j=0;j<jmax;j++){
		IloNumVarArray Xk(env,0);
		for (k=0;k<kmax;k++){
//			if(C[i][j][k]!=1000000){
				char Journey[70];
				sprintf(Journey,"Xijk(i%d,j%d,k%d)",i,j,k);
				IloNumVar X(env,0,1,ILOINT,Journey);
				Xk.add(X);
			}
//		}
		Xjk.add(Xk);
	}
	Xijk.add(Xjk);
}

//-------------------------------------------- CONSTRAINTS -------------------------------------------------
//--------------------Constraint 1--------------------------------
IloRangeArray Ai(env,0);
	i=r; 
	IloExpr expr1(env,0);
		for (j=0;j<jmax;j++){
			for(k=0;k<kmax;k++){
//				if(C[i][j][k]!=1000000){
					expr1+=Xijk[i][j][k];
//				}
			}
		}
	
			int LB1=1,UB1=1;
			IloRange A(env,LB1,expr1,UB1);		
			model.add(A);
			Ai.add(A);
			expr1.end();
//----------------- Constraint 1.1 ----------------------
IloRangeArray AAj(env,0);
	j=r; 
	IloExpr expr3(env,0);
		for (i=0;i<imax;i++){
			for(k=0;k<kmax;k++){
//				if(C[i][j][k]!=1000000){
					expr3+=Xijk[i][j][k];
//				}
			}
		}	
			int LB3=0,UB3=0;
			IloRange AA(env,LB3,expr3,UB3);		
			model.add(AA);
			AAj.add(AA);
			expr3.end();

//----------------- Constraint 2 ----------------------
IloRangeArray Tj(env,0);
	j=s; 
	IloExpr expr2(env,0);
		for (i=0;i<imax;i++){
			for(k=0;k<kmax;k++){
//				if(C[i][j][k]!=1000000){
					expr2+=Xijk[i][j][k];
//				}
			}
		}	
			int LB2=1,UB2=1;
			IloRange T(env,LB2,expr2,UB2);		
			model.add(T);
			Tj.add(T);
			expr2.end();
//---------------- Constraint 2.2--------------------------------
IloRangeArray TTi(env,0);
	i=s; 
	IloExpr expr4(env,0);
		for (j=0;j<jmax;j++){
			for(k=0;k<kmax;k++){
//				if(C[i][j][k]!=1000000){
					expr4+=Xijk[i][j][k];
//				}
			}
		}
			int LB4=0,UB4=0;
			IloRange TT(env,LB4,expr4,UB4);		
			model.add(TT);
			TTi.add(TT);
			expr4.end();

//------------------ Constraint 3 ------------------------------
IloRangeMatrix2x2 Sum_Xij(env,0);
for (i=0;i<imax;i++){
	IloRangeArray Sum_Xj(env,0);
		for (j=0;j<jmax;j++){
			IloExpr expr(env,0);
			for(k=0;k<kmax;k++){
//				if(C[i][j][k]!=1000000){
					expr+=Xijk[i][j][k];
//				}
			}
			int LB=0,UB=1;		
			IloRange Sum_X(env,LB,expr,UB);
			model.add(Sum_X);
			Sum_Xj.add(Sum_X);
			expr.end();
		}
	Sum_Xij.add(Sum_Xj);
}

//------------------- Constraint 4 ---------------------------
IloRangeArray Sumdiaforas_Xj(env,0);
	for (j=0;j<jmax;j++){
		IloExpr expr(env,0);
		if (j!=r && j!=s){
			for (i=0;i<imax;i++){
				for(k1=0;k1<kmax;k1++){
//					if(C[i][j][k1]!=1000000){
						expr+=Xijk[i][j][k1];
//					}
				}
			}
			for (m=0;m<jmax;m++){
				for(k2=0;k2<kmax;k2++){
//					if(C[j][m][k2]!=1000000){
						expr-=Xijk[j][m][k2]; 
//					}
				}
			}
		}
			int LB=0,UB=0;			
			IloRange Sumdiaforas_X(env,LB,expr,UB);
			model.add(Sumdiaforas_X);
			Sumdiaforas_Xj.add(Sumdiaforas_X);
			expr.end();
	 }
//----------------- Objective function ---------------------------
IloExpr expr(env);

for (i=0;i<imax;i++){
	for (j=0;j<jmax;j++){
		for (k=0;k<kmax;k++){
//			if(C[i][j][k]!=1000000){
				expr+=Xijk[i][j][k]*C[i][j][k];
//			}
		}
	}
}
model.add(IloMinimize(env, expr));
expr.end();		

cplex.extract(model);
cplex.exportModel("onoma.lp");
cplex.solve();

//---------------------- Print Results -------------------------------
		if (!cplex.solve ()){
			env.error() << "Failed to optimize LP." << endl;
			throw(-1);
		}
		env.out()<<"Solution status = " <<cplex.getStatus()<<endl;
		env.out()<<"Solution value = " <<cplex.getObjValue()<<endl;

for (i=0;i<imax;i++){
	for (j=0;j<jmax;j++){
		for (k=0;k<kmax;k++){
//			if(C[i][j][k]!=1000000){
				int g = cplex.getValue(Xijk[i][j][k]); //anaktish timhs metabliths
//				if(g!=0) cout<<"Xijk"<<"("<<i<<","<<j<<","<<k<<")"<<"="<<g<<endl;
				if(g!=0){
					cout<<"Xijk"<<"("<<i<<","<<j<<","<<k<<")"<<"="<<g<<endl;
					CX[i][j][k]=g;
//			}
			}
		}
	}
}	
}
	catch ( IloException& e){
		cerr << "concert exception caught:" << e << endl;
	}
	catch (...){
		cerr << "Unknown exception caught" << endl;
	}
	env.end();

//-------------------------------- FIND ROUTES -----------------------------------------

	int d,ts,sumt,d1,d2;
	const int dmax=20;
	//ts=635;

	puts("Dwse wra enarksis : ");
     	cin >> ts;
     
	//double I[imax];
	double mint[imax];
	double D[dmax][kmax];
	double T[imax][dmax][kmax];
	double TT[imax][dmax][kmax];

	for (i=0;i<imax;i++){
		for (d=0;d<dmax;d++){
			for (k=0;k<kmax;k++){
//				I[i]=1000000;
				mint[i]=1000000;
				D[d][k]=1000000;
				T[i][d][k]=1000000;
				TT[i][d][k]=1000000;
			}
		}
	}
//-----------------Find start hours of every route of every transport mode (at the first stop of the transport mode) -------
	D[0][0]=700;
	D[1][0]=730;
	D[2][0]=830;
	D[3][0]=900;
	D[4][0]=920;

	D[5][1]=710;
	D[6][1]=730;
	D[7][1]=750;
	D[8][1]=850;
	D[9][1]=930;

	D[10][2]=705;
	D[11][2]=715;
	D[12][2]=815;
	D[13][2]=845;
	D[14][2]=900;

	D[15][3]=720;
	D[16][3]=740;
	D[17][3]=750;
	D[18][3]=850;
	D[19][3]=905;
//------------------------------ Calculate start hours from stops ------------------------------------------------
sumt=0;
for (d=0;d<dmax;d++){
	for (k=0;k<kmax-1;k++){
		for (i=0;i<imax;i++){
			for (j=0;j<jmax;j++){		
				if (C[i][j][k]!=1000000){
					sumt=sumt+C[i][j][k];
					T[i][d][k]=D[d][k]+sumt-C[i][j][k];
					}		
			}
		}
	sumt=0;
	}
}

for (i=0;i<imax;i++){
	for (d=0;d<dmax;d++){
		for (k=0;k<kmax-1;k++){
			if(T[i][d][k]<1000){
//				cout<<T[i][d][k]<<endl;
			}
		}
	}
}
//--------------------- Find start hour at start stop -------------------------------------------
int min=1000000;
for (d=0;d<dmax;d++){
	for (k=0;k<kmax-1;k++){
		for (j=0;j<jmax;j++){
			if (T[r][d][k]<1000000){
				if (CX[r][j][k]==1){
					if (T[r][d][k]>ts){
						if (T[r][d][k]-ts < min){
							min=T[r][d][k]-ts;
						}
					}
				}
			}
		}
	}
}
for (k=0;k<kmax-1;k++){
	for (d=0;d<dmax;d++){
		if (T[r][d][k]-ts == min){
			cout<<T[r][d][k]<<endl;
		}else{
			T[r][d][k]=1000000;
//			cout<<T[r][d][k]<<endl;
		}
	}
}
	system("pause");
	return 0;
} //End main
