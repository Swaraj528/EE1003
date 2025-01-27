#include<stdio.h>
//Functions specific to our question
//f(x)
double func(double x){
	return 3*x*x-5*x+2;
}
//manually found derivative of f(x)
double deriv(double x){
	return 6*x-5;
}
//This function generates points on the known function to plot
void makePlotArray(double xo, double yo, int n, double x[n], double y[n], double h, double(*func)(double)){
	x[n/2] = xo; y[n/2] = yo;
  //Plotting backwards
	for(int i = n/2+1; i < n; i++){
		x[i] = x[i-1]-h;
		y[i] = func(x[i]);
	}
  //Plotting forwards
	for(int i = n/2-1; i > -1; i--){
		x[i] = x[i+1] + h;
		y[i] = func(x[i]);
	}
}
//The Newton-Raphson algorithm
void NewtonRootFind(double xo, int iters, double (*func)(double), double (*deriv)(double), double root[1]){
  double xn = xo;
	for(int i = 0; i<iters; i++){
    double old = xn;
    //Update equation
    xn = xn - func(xn)/deriv(xn);
    //Checking for convergence and breaking once achieved
    if(xn - old < 1e-6 && xn - old > - 1e-6){
      printf("iterations = %d, found root = %lf\n", i, xn);
     break;
    }
  }
  root[0] = xn;
}
