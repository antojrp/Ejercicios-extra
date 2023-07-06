# include <iostream>
# include <stdlib.h>
# include <fstream>
# include <math.h>
# include <time.h>
# include "gsl_rng.h"

const int MAX=100;
const int IMG=4;
gsl_rng *tau;

using namespace std;

void leer_datos(int a[][MAX][IMG], string nombre, int N, int k)
{
  string line;
  ifstream entrada(nombre);


  if (entrada)
  {  
    for(int i=N-1; i>=0; i--)
    {
        for(int j=0; j<N ; j++)
        {
            entrada >> a[i][j][k];
        }
    } 
  }
  else
  {
    cout << "No se pudo abrir el fichero \n"; 
  }
  entrada.close();
}

void generar_datos(int s[][MAX], int N)
{
    double valor;
    for(int j=0; j<N; j++)
    {
        for(int i=0; i<N; i++)
        {
            valor=gsl_rng_uniform(tau);
            if(valor<0.5)
            {
                s[i][j]=0;
            }
            else
            {
                s[i][j]=1;
            }
        }
    }
}

void alterar_datos(int a[][MAX][IMG], int s[][MAX], int p, int N, int k)
{
    int n,m;


    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            s[i][j]=a[i][j][k];
        }
    }
    for(int i=0; i<(p*N*N/100); i++)
    {
        n=gsl_rng_uniform_int(tau,N);
        m=gsl_rng_uniform_int(tau,N);
        s[n][m]=(s[n][m]+1)%2; 
    }
    
}

void imagen(int a[][MAX][IMG],double img[IMG], int N)
{
    for(int k=0; k<IMG; k++)
    {
        img[k]=0;

        for(int i=0; i<N ; i++)
        {
            for(int j=0; j<N; j++)
            {
                img[k]=img[k]+a[i][j][k];
            }
        }
        img[k]=img[k]/(N*N);
    }
}

double pesos_sinapticos(int a[][MAX][IMG], double img[IMG], int N, int i, int j, int k, int l)
{
    double w=0;
    
    if(i==k && j==l )
    {
        return w;
    }
    else
    {
        for(int m=0; m < IMG; m++)
        {
            w=w+(a[i][j][m]-img[m])*(a[k][l][m]-img[m]);
        }
        return w/(N*N);
    }
        
      
}

double umbral(int a[][MAX][IMG], double img[IMG], int N, int i, int j)
{
    double umbral=0;
    umbral=0;
    for(int k=0; k < N; k++)
    {
        for(int l=0; l < N; l++)
        {
            umbral=umbral+pesos_sinapticos(a,img,N,i,j,k,l);
        }
    }
    return umbral*0.5;            

}

double variacion_energia(int s[][MAX], int a[][MAX][IMG], double img[],int n, int m, int N)
{
    double sum1=0, sum2=0, sum3=0;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(i!=n,j!=m)
            {
            sum1=sum1+pesos_sinapticos(a,img,N,n,m,i,j)*s[i][j];
            }
        }
    }

    return  pow(-1,s[n][m])*(-sum1+umbral(a,img,N,n,m));
}

void ising(int s[][MAX], int a[][MAX][IMG],double img[], double T, int N)
{
    int n,m;
    double p, e;
    
    n=rand()%N;
    m=rand()%N;

    p=exp(-variacion_energia(s,a,img,n,m,N)/T);

    if(p>1)
    {
        p=1;
    }

    e=gsl_rng_uniform(tau);

    if(e<p)
    {
        s[n][m]=(s[n][m]+1)%2;
    }
}

void solapamiento(double sol[IMG], int s[][MAX], int a[][MAX][IMG], double img[], int N)
{
    for(int m=0; m<IMG; m++)
    {
        sol[m] = 0;
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
               sol[m]=sol[m]+(a[i][j][m]-img[m])*(s[i][j]-img[m]); 
            }
        }
        sol[m]=sol[m]/(N*N*img[m]*(1-img[m]));
    }
}

void crear_fichero(string nombre)
{
    ofstream salida(nombre);
    salida << "";
    salida.close();
}

void escribir_datos(int s[][MAX], int N)
{
    ofstream salida("hopefield_data.dat", ios::app);
    for(int i=N-1; i>=0; i--)
    {
        for(int j=0; j<N-1; j++)
        {
            salida << s[i][j] << ",";
        }
        salida << s[i][N-1] <<"\n";
    }

    salida << "\n";
    salida.close();
}

void escribir_solapamiento(double sol[IMG])
{
    ofstream salida("solapamiento.dat", ios::app);
    for(int m=0; m<IMG; m++)
    {
        salida<<sol[m]<< "   ";
    }

    salida << "\n";
    salida.close();
}

int main()
{
    int N=MAX, p=0;
    int s[MAX][MAX],aux[MAX][MAX], a[MAX][MAX][IMG]; 
    double T=0.0001, img[IMG], sol[IMG];
    bool alterar = true;
    bool recuerda = false;

    extern gsl_rng *tau;
    int semilla = time(NULL);
//    int semilla = 4567890;
//    int semilla = 35364545;
    tau = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(tau,semilla);

    crear_fichero("hopefield_data.dat");
    crear_fichero("solapamiento.dat");
    if(recuerda)
    {
        for(int k=0; k<IMG; k++)
        {
            generar_datos(aux,N);

            for(int i=0; i<N; i++)
            {
                for(int j=0; j<N; j++)
                {
                    a[i][j][k]=aux[i][j];
                }
            }

        }
    }
    else
    {
        for(int k=0; k<IMG; k++)
        {
            leer_datos(a,"imagen_"+to_string(k)+".txt",N,k);
        }
    }
    if(alterar)
    {
        alterar_datos(a, s, p, N, 3);
    }
    else
    {
        generar_datos(s,N);
    }
    imagen(a, img, N);
    escribir_datos(s, N);
    for(int i=0; i<N*N*100+1; i++)
    {
        ising(s,a,img,T,N);
        if(i%(N*N)==0)
        {
            escribir_datos(s,N);
            solapamiento(sol,s,a,img,N);
            escribir_solapamiento(sol);
        }
    }
}