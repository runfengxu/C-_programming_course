#include"MyVector.h"


//the following code is meant for testing all the functions

int main(){


  cout<< "These are the testing results of all the functions:\n"<<endl;
  MyVector v;
  double a[2]={1,2};
  v=a;
  cout<<"v: "<<v;//test output
  cout<<"v[0]: "<<v[0]<<"\tv[1]: "<<v[1]<<endl;//test [] operator
  cout<<"module of v: "<<v.mod()<<endl<<endl;//test mod()

  MyVector u;
  double b[2]={5,3};
  u=b;
  cout<<"u: "<<u<<endl;




  MyVector w;

    cout<<"v*u: "<<w.dot(u,v)<<endl<<endl;//test dot()

  w=v+u;
  cout<<"v+u(operator): "<<w<<"v+u(member): "<<w.add(u,v)<<endl;//test + and add()

  w=v-u;
  cout<<"v-u(operator): "<<w<<"v-u(member): "<<w.sub(v,u)<<endl;//test - and sub()


  w=v*5;
  cout<<"v*5(operator): "<<w<<"v*5(member): "<<w.mult(v,5)<<endl;//test * and mult()

  w=v/5;
  cout<<"v/5(operator): "<<w<<"v/5(member): "<<w.div(v,5)<<endl;// test / and div()

  cout<<"magnitude of v/5: "<<w.mag(w)<<endl<<endl;//test mag()

  MyVector z;
  z=v;
  cout<<"z: "<<z<<endl;
  cout<<"set mag of z as 10: "<<z.setMag(z,10)<<endl;//test setmag()
  cout<<"normalize z: "<<z.normalize(z)<<endl;//test normalize()
  z=v;
  cout<<"rotate z by pi: "<<z.rotate(z,pi)<<endl;//test rotate()

  cout<<"angle between u and v: "<<z.angleBetween(v,u)<<endl<<endl;//test angleBetween()
  cout<<"distance between u and v: "<<z.dist(v,u)<<endl<<endl;//test dist()
  z.random(5);
  cout<<"random vector, each component is (-scale,scale): "<<z<<endl;//test random()


}
