#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>


#define L 2000.0
#define N 40.0
#define pm 4.0
#define vm 90.0
using namespace std;

void copia(double *u_viejo, double *u_nuevo);
void inicial(double *u_i, double *ej_x, double delta_x);
void paso(double *u_f, double *u_p, double delta_t, double paso);
void normalizacion(double *u_i, double *u_f);

int main()
{
	
	double *u_inicial, *u_pasado, *u_presente, *u_futuro, *eje_x;
	double h = 50;
	double delta_t = 0.004;
	double T = 2.8;
	eje_x = new double[L + 1];
	u_inicial = new double[L + 1];
	u_futuro = new double[L + 1];
	u_presente = new double[L + 1];
	u_pasado = new double[L];

	cout << "Juan Pablo Montoya nacio en Bogota, Colombia el 20 de septiemnbre de 1975. Compitio en la Formula 1 desde 2001 hasta 2006" << endl;

	inicial(u_inicial, eje_x, h);
	copia(u_inicial, u_presente);
	
	normalizacion(u_inicial,u_inicial);
	double t = 0.0;
	while (t < T)
	{
		paso(u_futuro, u_presente, delta_t, h);
		copia(u_futuro, u_presente);
		t = t + delta_t;
	}
	ofstream file;
	file.open("final.txt");
	int g;
	for (g = 0; g < L + 1; g++)
	{

		if (file.is_open())
		{
			file << eje_x[g] << " " << u_presente[g] << "\n";


		}

	}
	file.close();
}
void copia(double *u_viejo, double *u_nuevo)
{
	int i;
	for (i = 0; i < L + 1; i++)
	{
		u_nuevo[i] = u_viejo[i];

	}
}
void inicial(double *u_i, double *ej_x, double delta_x)
{
	int i, k, z;
	int j = 0;
	double x;

	for (i = -1000; i < 1; i++)
	{
		ej_x[j] = i;
		j = j + 1;
	}

	for (k = 1; k < 1001; k++)
	{

		ej_x[j] = k;
		j = j + 1;

	}

	
	for (z = 0; z < L + 1; z++)
	{
		if (z < N / 4.0)
		{
			u_i[z] = 0.0;
		}
		else if (z > N / 4.0 && z < ((N / 2) - 1))
		{
			u_i[z] = pm;
		}
		else if (z == (N / 2))
		{
			u_i[z] = pm / 2.0;
		}
		else
		{
			u_i[z] = 0.0;
		}
	}

	ofstream archivo;
	archivo.open("inicial.txt");
	int g;
	for (g = 0; g < L + 1; g++)
	{

		if (archivo.is_open())
		{
			archivo << ej_x[g] << " " << u_i[g] << "\n";


		}

	}
	archivo.close();
}

void paso(double *u_f, double *u_p, double delta_t, double paso)
{
	int p;

	for (p = 1; p < L; p++)
	{
		u_f[p] = u_p[p] - vm * ((1 - ((2 * u_p[p])/pm))*(delta_t / (paso*2.0)))*(u_p[p + 1] - u_p[p-1]);
	}

}
void normalizacion(double *u_i,double *u_f) 
{
	ofstream primero;
	primero.open("inicialnorm.txt");
	int i, j;
	for (i=0;i<L+1;i++)
	{
		primero << u_i[i] / (*std::max_element(u_i, u_i + 2001)) << "\n";
	}
	primero.close();

	ofstream segundo;
	segundo.open("finalnorm.txt");
	for (j = 0; j < L + 1; j++)
	{
		segundo << u_f[j] / (*std::max_element(u_f, u_f + 2001)) << "\n";
	}
	segundo.close();

}
