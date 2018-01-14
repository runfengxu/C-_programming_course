#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<fstream>
#define N 100
#define k 1.0

using namespace std;

//compute d(energy)
int dEnergy(int a[N][N],int m,int n)
{
  int d;
  if((m>0) && (m<N-1) &&( n>0) && (n<N-1)
    d=2*a[m][n]*(a[m+1][n]+a[m-1][n]+a[m][n+1]+a[m][n-1]);

  if((m==0) && (n>0) && (n<N-1)
    d=2*a[0][n]*(a[1][n]+a[N-1][n]+a[0][n+1]+a[0][n-1]);

  if((m==N-1) && (n>0) && (n<N-1)
    d=2*a[N-1][n]*(a[0][n]+a[N-2][n]+a[N-1][n+1]+a[N-1][n-1]);

  if((m>0) && (m<N-1) && (n==0))
    d=2*a[m][0]*(a[m+1][0]+a[m-1][0]+a[m][1]+a[m][N-1]);

  if((m>0) && (m<N-1) && (n==N-1)
    d=2*a[m][N-1]*(a[m+1][N-1]+a[m-1][N-1]+a[m][0]+a[m][N-2]);

  if((m==0) && (n==0))
    d=2*a[0][0]*(a[1][0]+a[N-1][0]+a[0][1]+a[0][N-1]);

  if((m==0) && (n==N-1))
    d=2*a[0][N-1]*(a[1][N-1]+a[N-1][N-1]+a[0][0]+a[0][N-2]);

  if((m==N-1) && (n==0)
    d=2*a[N-1][0]*(a[0][0]+a[N-2][0]+a[N-1][1]+a[N-1][N-1]);

  if((m==N-1) && (n==N-1))
    d=2*a[N-1][N-1]*(a[0][N-1]+a[N-2][N-1]+a[N-1][0]+a[N-1][N-2]);

  return d;
}

int main(){
  int a[N][N];
  int i,j;
  double T;


  ofstream low;//"low" is the result when temperature is lower than critical temperature.
  ofstream critical;//"critical" is the result when temperature is critical.
  ofstream high;//"high" is the result when temperature is higher than critical tempersture.
  ofstream T//"T" is the result of relation between total s at equibrilium state and temperature.;
  low.open("low.txt");
  critical.open("critical.txt");
  high.open("high.txt");
  T.open("T.txt");

  low<<"relation between time and total_s under the Tc\n"<<"time\ttotal_s"<<endl;
  critical<<"relation between time and total_s at the Tc\n"<<"time\ttotal_s"<<endl;
  high<<"relation between time and total_s beyond the Tc\n"<<"time\ttotal_s"<<endl;
  T<<"relation between temperature and final total_s \n"<<"Temperature\tfinal total_s"<<endl;




//S
int s_total[40];
for(i=0;i<40;i++){
  s_total[i]=10000;
}

//S FOR STABLE SYSTEM
int s_total_aver[40];
for(i=0;i<40;i++){
  s_total_aver[i]=0;
}

//GENERATE POINT FOR 10^7 TIMES
int m,n,dE;
int count=0;
double q;


srand(time(NULL));


for(T=1.0;T<=4.9;T+=0.1){
  //initiate a matrix of points(all spin up)
  for(i=0;i<=N-1;i++){
    for(j=0;j<=N-1;j++){
        a[i][j]=1;
    }
  }

  for(int r=1;r<=10000000;r++){
    //randomly SET POINT ,GENERATE S
    m=rand()%N;
    n=rand()%N;
    dE=dEnergy(a,m,n);

    if(dE>0){
      q=(double)rand()/RAND_MAX;
      if(q<exp((double)((0-dE)/(k*T)))){
        a[m][n]=-a[m][n];
        s_total[count]+=2*a[m][n];
      }
    }
    else{
      a[m][n]=-a[m][n];
      s_total[count]+=2*a[m][n];
    }
//OUTPUT

    if(r%1000==0 && count==0){
      low<<r<<"\t"<<s_total[count]<<endl;
    }


    if(r%1000==0 && count==15){
      critical<<r<<"\t"<<s_total[count]<<endl;
    }


    if(r%1000==0 && count==39){
      high<<r<<"\t"<<s_total[count]<<endl;
    }

    if(r>9900000){
      s_total_aver[count]+=s_total[count];
    }
  }


  T<<T<<"\t"<<s_total_aver[count]/100000<<endl;

  count++;


  }

low.close();
critical.close();
high.close();
T.close();
}
