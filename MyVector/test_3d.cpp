#include"MyVector.h"


//the following code is meant for testing all the functions

int main(){


  cout<< "These are the testing results of all the functions: "<<endl;
  
  //change dimension to 3D 
  MyVector::nDim(3);
  MyVector s;
  MyVector t;
  
  
  double s_temp[3]={1.0,2.0,3.0};
  double t_temp[3]={2.0,4.0,6.0};
  s=s_temp;
  t=t_temp;
  cout<<"\ns(3D vec):"<<s<<endl;
  cout<<"t(3D vec):"<<t<<endl;

  MyVector r;
  r = r.cross(s,t);//testing cross()
  cout<<"s crossX t:"<<r<<endl;



}
