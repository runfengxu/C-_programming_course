#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<unistd.h>
#define pi 3.1415926


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
void getStep(float *step)
{
    float theta=(rand()/(float)RAND_MAX)*2*pi;
    float p=rand()*1/(float)RAND_MAX;
    float q=rand()*1/(float)RAND_MAX;
    //walk or not
    if(p<=0.8)
    {
        //whole or half
        if(q<=0.5)
        {
            step[0]=cos(theta);
            step[1]=sin(theta);
        }
        else
        {
            step[0]=0.5*cos(theta);
            step[1]=0.5*sin(theta);
        }
    }
    else
    {
        step[0]=0;
        step[1]=0;
    }
}


//function to walk
float runStep(float *site,float *step)
{
    site[0]+=step[0];
    site[1]+=step[1];
    float dis=sqrt((site[0])*(site[0])+(site[1])*(site[1]));
    return dis;
}


//function to output
void output(FILE *fp,int istep,float dist)
{
    fprintf(fp,"%10d %10.2f\n",istep,dist);
}


int main(int argc,char *argv[])
{
    int nstep=1000000;
    char *filename="output.txt";
    getMyargs(argc,argv,&nstep,&filename);

    
    //initial state
    float site[]={0.0,0.0};
    float dis=0;
    FILE *fp=fopen(filename,"w");
    output(fp,0,dis);

    //walking
    int i;
    srand(time(NULL));
    for(i=1;i<nstep;++i)
    {
        float step[2];
        getStep(step);
        dis=runStep(site,step);
        if(i%100 ==0)
          output(fp,i,dis);

    }

    fclose(fp);
    return 0;
}
