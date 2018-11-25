// Calculates best combination of 4 instances
#include <iostream>
#include <cstdlib>
#include <cstdio>      

using namespace std;
  int main()
 {
	  double tr[1],ts[1],apot[3];
	  int a,b,c,d;

		puts("Type tr");
		cin >> tr[0] >> tr[1];
		puts("Type ts");
		cin >> ts[0] >> ts[1];

		puts("\nType solution value");
		
		cin >>a>>b>>c>>d;

		apot[0]=a+tr[0]+ts[0];
		apot[1]=b+tr[0]+ts[1];
		apot[2]=c+tr[1]+ts[0];
		apot[3]=d+tr[1]+ts[1];

		for (int i=0;i<4;i++){
				cout << apot[i] <<endl;
		}

		double min=10000000;

		for (int i=0;i<4;i++){
				if(apot[i]<min){
					min=apot[i];
				}
		}

		for (int i=0;i<4;i++){
				if(min==apot[i]){
					cout << "an i=0 diadromi apo to 0 sto 0"<< endl;
					cout << "an i=1 diadromi apo to 0 sto 1"<< endl;
					cout << "an i=2 diadromi apo to 1 sto 0"<< endl;
					cout << "an i=3 diadromi apo to 1 sto 1"<< endl;
					cout << "\nOptimal route is i = " << i  << " with time :" << apot[i]<< endl;
				}

		}
system("PAUSE");
    return 0;
}
