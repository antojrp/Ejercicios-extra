# include <iostream>
# include <cmath>
# include <fstream>
using namespace std;

const int N=6;
const float g=9.81;
const float E=20.8;

void condiciones_iniciales(double& Pphi, double& Ppsi, double& phi, double& psi, int i)
{
  double phip;
  phi=0;
  psi=0+0.01*i;

  phip=sqrt(E-2*g*(1-cos(phi))-g*(1-cos(psi)));

  Pphi=2*phip;
  Ppsi=phip*cos(phi-psi);
}

double phi_punto(double Pphi, double Ppsi, double phi, double psi)
{
    return (Pphi-Ppsi*cos(phi-psi))/(1+pow(sin(phi-psi),2));
}

double psi_punto(double Pphi, double Ppsi, double phi, double psi)
{
    return (-Pphi*cos(phi-psi)+2*Ppsi)/(1+pow(sin(phi-psi),2));
}

double Pphi_punto(double phi, double psi, double h1, double h2)
{
    return -2*g*sin(phi)-h1+h2*sin(2*(phi-psi));
}

double Ppsi_punto(double phi, double psi, double h1, double h2)
{
    return -g*sin(psi)+h1-h2*sin(2*(phi-psi));
}

double h1(double Pphi, double Ppsi, double phi, double psi)
{
  return (Pphi*Ppsi*sin(phi-psi))/(1+pow(sin(phi-psi),2));
}

double h2(double Pphi, double Ppsi, double phi, double psi)
{
  return (Pphi*Pphi+2*Ppsi*Ppsi-2*Pphi*Ppsi*cos(phi-psi))/(2*pow(1+pow(sin(phi-psi),2),2));
}


void Runge_Kutta(double& Pphi, double& Ppsi, double& phi, double& psi, double h)
{
    double k1[4], k2[4], k3[4], k4[4];
    
    // Calculo k1
    k1[0]=h*phi_punto(Pphi,Ppsi,phi,psi);
    k1[1]=h*psi_punto(Pphi,Ppsi,phi,psi);
    k1[2]=h*Pphi_punto(phi,psi,h1(Pphi,Ppsi,phi,psi),h2(Pphi,Ppsi,phi,psi));
    k1[3]=h*Ppsi_punto(phi,psi,h1(Pphi,Ppsi,phi,psi),h2(Pphi,Ppsi,phi,psi));  

    // Calculo k2
    k2[0]=h*phi_punto(Pphi+k1[2]/2,Ppsi+k1[3]/2,phi+k1[0]/2,psi+k1[1]/2);
    k2[1]=h*psi_punto(Pphi+k1[2]/2,Ppsi+k1[3]/2,phi+k1[0]/2,psi+k1[1]/2);
    k2[2]=h*Pphi_punto(phi+k1[0]/2,psi+k1[1]/2,h1(Pphi+k1[2]/2,Ppsi+k1[3]/2,phi+k1[0]/2,psi+k1[1]/2),h2(Pphi+k1[2]/2,Ppsi+k1[3]/2,phi+k1[0]/2,psi+k1[1]/2));
    k2[3]=h*Ppsi_punto(phi+k1[0]/2,psi+k1[1]/2,h1(Pphi+k1[2]/2,Ppsi+k1[3]/2,phi+k1[0]/2,psi+k1[1]/2),h2(Pphi+k1[2]/2,Ppsi+k1[3]/2,phi+k1[0]/2,psi+k1[1]/2));   

    // Calculo k3
    k3[0]=h*phi_punto(Pphi+k2[2]/2,Ppsi+k2[3]/2,phi+k2[0]/2,psi+k2[1]/2);
    k3[1]=h*psi_punto(Pphi+k2[2]/2,Ppsi+k2[3]/2,phi+k2[0]/2,psi+k2[1]/2);
    k3[2]=h*Pphi_punto(phi+k2[0]/2,psi+k2[1]/2,h1(Pphi+k2[2]/2,Ppsi+k2[3]/2,phi+k2[0]/2,psi+k2[1]/2),h2(Pphi+k2[2]/2,Ppsi+k2[3]/2,phi+k2[0]/2,psi+k2[1]/2));
    k3[3]=h*Ppsi_punto(phi+k2[0]/2,psi+k2[1]/2,h1(Pphi+k2[2]/2,Ppsi+k2[3]/2,phi+k2[0]/2,psi+k2[1]/2),h2(Pphi+k2[2]/2,Ppsi+k2[3]/2,phi+k2[0]/2,psi+k2[1]/2));

    // Calculo k4
    k4[0]=h*phi_punto(Pphi+k3[2],Ppsi+k3[3],phi+k3[0],psi+k3[1]);
    k4[1]=h*psi_punto(Pphi+k3[2],Ppsi+k3[3],phi+k3[0],psi+k3[1]);
    k4[2]=h*Pphi_punto(phi+k3[0],psi+k3[1],h1(Pphi+k3[2],Ppsi+k3[3],phi+k3[0],psi+k3[1]),h2(Pphi+k3[2],Ppsi+k3[3],phi+k3[0],psi+k3[1]));
    k4[3]=h*Ppsi_punto(phi+k3[0],psi+k3[1],h1(Pphi+k3[2],Ppsi+k3[3],phi+k3[0],psi+k3[1]),h2(Pphi+k3[2],Ppsi+k3[3],phi+k3[0],psi+k3[1]));   

    // Calculo posición
    
    phi=phi+1.0/6.0*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
    psi=psi+1.0/6.0*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
    Pphi=Pphi+1.0/6.0*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
    Ppsi=Ppsi+1.0/6.0*(k1[3]+2*k2[3]+2*k3[3]+k4[3]);

  /*  if(phi>2*M_PI)
    {
      phi=phi-2*M_PI;
    }

    if(psi>2*M_PI)
    {
      psi=psi-2*M_PI;
    }*/
}

void Hamiltoniano(double phi[N], double psi[N], double Pphi[N], double Ppsi[N], double E[N])
{
  for(int k=0; k<N; k++)
  {
   E[k]=(Pphi[k]*Pphi[k]+2*Ppsi[k]*Ppsi[k]-2*Pphi[k]*Ppsi[k]*cos(phi[k]-psi[k]))/(2*(1+pow(sin(phi[k]-psi[k]),2)))+2*g*(1-cos(phi[k]))+g*(1-cos(psi[k]));
  }
}

void crear_fichero(string nombre)
{
  ofstream salida(nombre);
  salida << "";
  salida.close();
}

void escribir_posiciones(double phi[N], double psi[N])
{
  double x1,y1,x2,y2;
  ofstream salida("pendulo.dat", ios::app);
  for(int i=0; i<N; i++)
  {
    x1=sin(phi[i]);
    y1=-cos(phi[i]);
    x2=sin(phi[i])+sin(psi[i]);
    y2=-cos(phi[i])-cos(psi[i]);
    salida << x1 << ", " << y1 << "\n";
    salida << x2 << ", " << y2 << "\n";
  }

  salida << "\n\n";
  salida.close();
}

void escribir_tayectorias(double phi[N], double psi[N])
{
  double x2,y2;
  ofstream salida("trayectorias.dat", ios::app);
  for(int i=0; i<N; i++)
  {
    x2=sin(phi[i])+sin(psi[i]);
    y2=-cos(phi[i])-cos(psi[i]);
    salida << x2 << ", " << y2 << "\n";
  }

  salida << "\n\n";
  salida.close();
}

void escribir_mapa(double phi[N], double psi[N], double Pphi[N], double Ppsi[N])
{
  double x1,y1,x2,y2,phip,psip;
  ofstream salida("mapa.dat", ios::app);
  for(int i=0; i<N; i++)
  {
    phip=(Pphi[i]-Ppsi[i]*cos(phi[i]-psi[i]))/(1+pow(sin(phi[i]-psi[i]),2));
    psip=(-Pphi[i]*cos(phi[i]-psi[i])+2*Ppsi[i])/(1+pow(sin(phi[i]-psi[i]),2));
    salida << psi[i] << ", " << phip << "\n";
  }

  salida << "\n\n";
  salida.close();
}

void Lyapunov(double Lya[N], double phi[N], double psi[N], double Pphi[N], double Ppsi[N], double h, double delta0[N])
{
  double psip, psip0, delta;
  psip0=(-Pphi[0]*cos(phi[0]-psi[0])+2*Ppsi[0])/(1+pow(sin(phi[0]-psi[0]),2));
  for(int i=1; i<N; i++)
  {
    psip=(-Pphi[i]*cos(phi[i]-psi[i])+2*Ppsi[i])/(1+pow(sin(phi[i]-psi[i]),2));
    delta=sqrt(pow((psi[0]-psi[i]),2)+pow(10*h*(psip-psip0),2));
    Lya[i]=Lya[i]+log(delta/delta0[i]);
  }

}

void escribir_energia(double E[N])
{
  ofstream salida("Energia.dat", ios::app);
  for(int k=0; k<N; k++)
  {
      salida << E[k] << " ";
  }
  salida << "\n";
  salida.close();
}

void escribir_Lyapunov(double Lya[N], double h, int i)
{

    ofstream salida("Lyapunov.dat", ios::app);
    for(int k=1; k<N; k++)
    {
        salida << Lya[k]/(10*h*(i/10)) << " ";
    }
    salida << "\n";
    salida.close();

}

int main()
{
    double Pphi[N],Ppsi[N],phi[N],psi[N],E[N],delta0[N],Lya[N],psip0,psip,h,t;
    h=0.001;
    t=0;
    crear_fichero("pendulo.dat");
    crear_fichero("trayectorias.dat");
    crear_fichero("mapa.dat");
    crear_fichero("Energia.dat");
    crear_fichero("Lyapunov.dat");
    for(int i=0; i<N; i++)
    {
      condiciones_iniciales(Pphi[i],Ppsi[i],phi[i],psi[i],i);
    }

    psip0=(-Pphi[0]*cos(phi[0]-psi[0])+2*Ppsi[0])/(1+pow(sin(phi[0]-psi[0]),2));
    for(int i=1; i<N; i++)
    {
      psip=(-Pphi[i]*cos(phi[i]-psi[i])+2*Ppsi[i])/(1+pow(sin(phi[i]-psi[i]),2));
      delta0[i]=sqrt(pow((psi[0]-psi[i]),2)+pow(10*h*(psip-psip0),2));
      Lya[i]=0;
    }

    for(int i=0; i<15000; i++)
    {
        if(i%10==0)
        {
        escribir_posiciones(phi,psi);
        escribir_tayectorias(phi,psi);
        escribir_mapa(phi,psi,Pphi,Ppsi);
        Hamiltoniano(phi,psi,Pphi,Ppsi,E);
        escribir_energia(E);
        if(i!=0)
        {
          Lyapunov(Lya,phi,psi,Pphi,Ppsi,h,delta0);
          escribir_Lyapunov(Lya,h,i);
        }

        }
        for(int i=0; i<N; i++)
        {
        Runge_Kutta(Pphi[i],Ppsi[i],phi[i],psi[i],h);
        }
    }
}