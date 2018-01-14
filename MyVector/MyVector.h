#ifndef MYVECTOR_H
#define MYVECTOR_H

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<cmath>
#include<time.h>
#define pi 3.1415926

using namespace std;

class MyVector{

private:
  static int _nDim;
  static bool _bDim;
  vector<double> _data;


public:
  //设维数，初始化
  static void nDim(int);
  static int nDim();
  MyVector();
    double& operator[](int);
	double  operator[](int) const;
        //overloading operators
	MyVector operator+(const MyVector&) const;
	MyVector operator-(const MyVector&) const;
	MyVector operator*(double) const;
	MyVector operator/(double) const;

	void operator=(const double*);
	void operator=(const MyVector&);

	MyVector& operator+=(const MyVector&);
	MyVector& operator-=(const MyVector&);
	MyVector& operator*=(double);
  
	double mod() const;//calculate the module

	friend MyVector operator*(double, const MyVector&);
	friend ostream& operator<<(ostream&, const MyVector&);


	MyVector add(const MyVector& u, const MyVector& v);
	MyVector sub(const MyVector& u, const MyVector& v);
	MyVector mult(const MyVector& v, double u);
        MyVector div(const MyVector& v, double u);
	double dot(const MyVector& u, const MyVector& v);
	MyVector cross(const MyVector& u, const MyVector& v);
	double mag(const MyVector& v);
	MyVector& setMag(MyVector& v, double L);
	MyVector& normalize(MyVector& v);
	MyVector& rotate(MyVector& v, double delta);

	double angleBetween(const MyVector& u, const MyVector& v);
	double dist(const MyVector& u, const MyVector& v);

	void random(double scale);

};

#endif

