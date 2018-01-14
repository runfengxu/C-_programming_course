#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#define pi 3.1415926
#define k 0.01 //Boltzmann constance
#define L 0.698252 //the size of ground state
#define s 0.01 //each step length
#define D 100.0 //boundary
#define Tmax 200 //temperature range

//function to show the info
void usage(char *program)
{
    fprintf(stderr,"\nProgram Usage:\n%s\n",program);
    fprintf(stderr,"\t[ -n 1000000 ]   number of steps per run, default 1000000\n");
    fprintf(stderr,"\t[ -o output.txt ]   the output file, default:output.txt\n");
    fprintf(stderr,"\t[ -h ]   display this information");
    fprintf(stderr,"\n");
    exit(1);
}


//function to get my args
void getMyargs(int argc,char **argv,int *nstep,char **filename)
{
    char ch;
    while((ch=getopt(argc,argv,"n:o:h"))!= -1)
    {
        switch(ch)
        {
            case 'n': *nstep=atoi(optarg);break;
            case 'o': *filename=optarg;break;
            case 'h': usage(argv[0]);
            case '?': usage(argv[0]);
        }
    }
}



//function to get the step
void getStep(float *step,float stmp)
{
    float theta=(rand()/(float)RAND_MAX)*2*pi;
    step[0]=stmp*cos(theta);
    step[1]=stmp*sin(theta);

}


//function to walk
float runStep(float *site,float *step,float Dtmp,int Ttmp)
{

    float d1,d2,e1,e2,p;
    d1=sqrt((site[0])*(site[0])+(site[1])*(site[1]));
    d2=sqrt((site[0]+step[0])*(site[0]+step[0])+(site[1]+step[1])*(site[1]+step[1]));
    e1=-0.5*cos(0.5*pi*d1)-cos(1.5*pi*d1);
    e2=-0.5*cos(0.5*pi*d2)-cos(1.5*pi*d2);

    if(d2<=2*Dtmp)//only walk inside the boundary
    {
      if(e2>e1)//delta>0,walk in a certain probability
      {
        float p=rand()*1/(float)RAND_MAX;
        if(p<=exp((e1-e2)/(k*Ttmp)))//decide the probability
        {
          site[0]+=step[0];
          site[1]+=step[1];
        }
      }
      else//delta<0,must walk
      {
        site[0]+=step[0];
        site[1]+=step[1];
      }
    }


    float dis=sqrt((site[0])*(site[0])+(site[1])*(site[1]));
    return dis;
}


//function to output
void output(FILE *fp,int Tem,float prob)
{
    fprintf(fp,"%10d %10.4f\n",Tem,prob);
}





//problem: the amount of k and the dimension of E


int main(int argc,char *argv[])
{
    int nstep=1000000;
    char *filename="output.txt";
    getMyargs(argc,argv,&nstep,&filename);

    FILE *fp=fopen(filename,"w");

    srand(time(NULL));
    for(int T=1;T<=Tmax;T++)//walk at a series of Temperature(from 1 to Tmax)
    {
    //initial state before each run
    float site[]={0.0,0.0};
    float dis=0;

    //walking at a temperature
    int i;
    float count=0,pro=0;
    for(i=1;i<nstep;++i)//n walks
    {
        float step[2];
        getStep(step,s);
        dis=runStep(site,step,D,T);
        if(dis<=L)//count times on the ground states
          count++;
    }
    pro=count/(float)nstep; //calculate the probability at T
    output(fp,T,pro);//output T and probabilty
    }

    fclose(fp);
    return 0;
}
