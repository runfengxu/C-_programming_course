#include"MyVector.h"


bool MyVector::_bDim = true;
int MyVector::_nDim = 2;


//重载
void MyVector::nDim(int n){
  if(_bDim){
    _nDim = n;
    _bDim = false;
  }
  else{
    cerr << "Cannot reset the dimension\n" <<endl;
  }
};


int MyVector::nDim(){
  return _nDim;
};

MyVector::MyVector():_data(_nDim, 0.0){
  _bDim = false;
}


double& MyVector::operator[](int i){
	return _data[i];
}

double MyVector::operator[](int i) const{
	return _data[i];
}

MyVector MyVector::operator+(const MyVector &v)const {
	MyVector tmp;
	for(int i=0;i<_nDim;i++){
		tmp._data[i]=_data[i]+v._data[i];
	}
	return tmp;
}

MyVector MyVector::operator-(const MyVector &v)const {
	MyVector tmp;
	for(int i=0;i<_nDim;i++){
		tmp._data[i]=_data[i]-v._data[i];
	}
	return tmp;
}

MyVector MyVector::operator*(double u) const {
	MyVector tmp;
	for(int i=0;i<_nDim;i++){
		tmp._data[i]=_data[i]*u;
	}
	return tmp;
}

MyVector MyVector::operator/(double u) const {
	if(u==0.0){
		cout<<"Could not be divided by zero"<<endl;
		exit(1);
	}
	else{
		MyVector tmp;
		for(int i=0;i<_nDim;i++){
			tmp._data[i]=_data[i]/u;
		}
		return tmp;
	}
}

void MyVector::operator=(const double* a){
	if(a==NULL){
		cout<<"Nothing Input"<<endl;
		exit(1);
	}
	else{
		for(int i=0;i<_nDim;i++){
			_data[i]=a[i];
		}
	}
}

void MyVector::operator=(const MyVector& v){
	for(int i=0;i<_nDim;i++){
		_data[i]=v._data[i];
	}
}

MyVector& MyVector::operator+=(const MyVector& v){
	for(int i=0;i<_nDim;i++){
		_data[i]+=v._data[i];
	}
	return *this;
}

MyVector& MyVector::operator-=(const MyVector& v){
	for(int i=0;i<_nDim;i++){
		_data[i]-=v._data[i];
	}
	return *this;
}

MyVector& MyVector::operator*=(double u){
	for(int i=0;i<_nDim;i++){
		_data[i] *= u;
	}
	return *this;
}

double MyVector::mod() const{
	double tmp=0.0;
	for (int i =0;i<_nDim;i++){
		tmp+=_data[i]*_data[i];
	}
	return sqrt(tmp);
}

MyVector operator*(double u, const MyVector& v) {
	MyVector tmp;
	for(int i=0;i<v.nDim();i++){
		tmp._data[i] = v._data[i] * u;
	}
	return tmp;
}

ostream& operator<<(ostream& os, const MyVector& v) {
	os<<"( ";
        for(int i=0;i<v.nDim()-1;i++){
		os<<v._data[i]<<", ";
	}
	os<<v._data[v.nDim()-1]<<" )"<<endl;
        return os;
}


MyVector MyVector::add(const MyVector& u, const MyVector& v){
	MyVector tmp;
	for(int i=0;i<_nDim;i++){
		tmp._data[i]=u._data[i]+v._data[i];
	}
	return tmp;
}

MyVector MyVector::sub(const MyVector& u, const MyVector& v){
	MyVector tmp;
	for(int i=0;i<_nDim;i++){
		tmp._data[i]=u._data[i]-v._data[i];
	}
	return tmp;
}

MyVector MyVector::mult(const MyVector& v, double u){
  MyVector tmp;
  for(int i=0;i<_nDim;i++){
    tmp._data[i]=u*v._data[i];
  }
  return tmp;
}

MyVector MyVector::div(const MyVector& v, double u){
  if(u==0.0){
    cout<<"Could not be divided by zero"<<endl;
    exit(1);
  }
  else{
    MyVector tmp;
    for(int i=0;i<_nDim;i++){
    tmp._data[i]=v._data[i]/u;
  }
  return tmp;
  }
}

double MyVector::dot(const MyVector& u, const MyVector& v){
	double tmp=0.0;
	for(int i=0;i<_nDim;i++){
		tmp+=u._data[i]*v._data[i];
	}
	return tmp;
}

MyVector MyVector::cross(const MyVector& u, const MyVector& v){
	if(u._nDim==3 && v._nDim==3){
		MyVector tmp;
		tmp._data[0]=u._data[1]*v._data[2]-u._data[2]*v._data[1];
		tmp._data[1]=u._data[2]*v._data[0]-u._data[0]*v._data[2];
		tmp._data[2]=u._data[0]*v._data[1]-u._data[1]*v._data[0];
		return tmp;
	}
	else{
		cout<<"Vectors must be 3D"<<endl;
		exit(1);
	}
}

double MyVector::mag(const MyVector& v){
	double tmp=0.0;
	for(int i=0;i<_nDim;i++){
		tmp+=v._data[i]*v._data[i];
	}
	return sqrt(tmp);
}

MyVector& MyVector::setMag(MyVector& v, double L){
	double r=L/mag(v);
	for(int i=0;i<_nDim;i++){
		v._data[i]=r*v._data[i];
	}
	return v;
}

MyVector& MyVector::normalize(MyVector& v){
	double r=1.0/mag(v);
	for(int i=0;i<_nDim;i++){
		v._data[i]=r*v._data[i];
	}
	return v;
}

MyVector& MyVector::rotate(MyVector& v,double delta){
  if(v._nDim==2){
    double theta=acos(fabs(v._data[0]/mag(v)));
    if(v._data[0]<=0 && v._data[1]>0){
      theta=pi-theta;
    }
    if(v._data[0]<0 && v._data[1]<=0){
      theta=pi+theta;
    }
    if(v._data[0]>=0 && v._data[1]<0){
      theta=2*pi-theta;
    }
    v._data[0]=mag(v)*cos(theta+delta);
    v._data[1]=mag(v)*sin(theta+delta);
    return v;
  }
}

double MyVector::angleBetween(const MyVector& u, const MyVector& v){
	double cos=dot(u,v)/mag(u)/mag(v);
	return acos(cos);
}

double MyVector::dist(const MyVector& u, const MyVector& v){
	double tmp=0.0;
	for(int i=0;i<_nDim;i++){
		tmp+=(u._data[i]-v._data[i])*(u._data[i]-v._data[i]);
	}
	return sqrt(tmp);
}

//输入范围，生成有限大小的向量
void MyVector::random(double scale){
  srand(time(NULL));
  for(int i=0;i<_nDim;i++){
		_data[i]=2*((rand()/double(RAND_MAX))-0.5)*scale;
	}
}


