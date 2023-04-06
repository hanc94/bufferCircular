#include "mex.h"
//Operación módulo con signo
#define MOD(a,b) ((((a)%(b))+(b))%(b))
//Convolución usando buffer circular
void myConvCircularBuffer(double *x,double xn,double *y,int n){
//Índice con el inicio del buffer circular, variable estática
	static int xins=0;
	int i,p=10000;
	double xaux[10000];
//Entrada actual
	x[xins]=xn;
//Convolución usando direccionamiento circular
	for(i=0;i<p;i++){
		xaux[i]=x[n];
		
		
	}
//Actualización del índice del inicio del buffer ciruclar
	xins=MOD((xins-1),p);
}
/* Función pasarela */
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
//Variables locales
	int nx,n,e;
	double *x,*y;
/* Verifica que hayan dos argumentos de entrada */
	if(nrhs!=2) {
		mexErrMsgIdAndTxt("myConv:nrhs","Se requieren dos entradas.");
	}
/*Verifica que haya un argumento de salida*/
	if(nlhs!=1) {
		mexErrMsgIdAndTxt("myConv:nlhs","Se requiere una salida");
	}
/* Punteros a la señal de entrada y respuesta al impulso*/
	x = mxGetPr(prhs[0]);
	//h = mxGetPr(prhs[1]);
// Variable eco
	e = mxGetScalar(prhs[1]);	

/* Tamaños de la señal de entrada y respuesta al impulso (filas)*/
	nx = mxGetM(prhs[0]);
/*Línea de retardos del filtro*/
	double xd[nx];
	for(int i=0;i<nx;i++)
		xd[i]=x[i];
/* Crea la matriz de salida */
	plhs[0] = mxCreateDoubleMatrix((mwSize)nx,1,mxREAL);
/* Puntero a la matriz de salida */
	y = mxGetPr(plhs[0]);
/* Llama a la función convolución */
	for(n=0;n<nx;n++){
		myConvCircularBuffer(xd,x[n],y,n);
		//int N=100;
		//myConvCircularBuffer(xd,(0.1*e)*x[n+N],y);
	}
}
