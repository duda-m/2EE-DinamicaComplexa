#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


//-------------------PARAMETERS-----------------------------------

//variables
float x_init, y_init, z_init, x_old, y_old, z_old, x_new, y_new, z_new, dt, t, k1x, k1y, k1z, k2x, k2y, k2z, k3x, k3y, k3z, k4x, k4y, k4z;

//for iteration
int iter, iter_max, t_max, j = 0;

//Langford constants
float a = 0.95, b = 0.7, c = 0.6, d = 3.5, e = 0.25, gama = 0.1;

//creating an array to store our data
char name[200];

//creating a file
FILE *fp;



//---------------------FUNCTIONS-----------------------------------

float f1(float x, float y, float z){
  return ((z - b)*x - d*y);
}
float f2(float x, float y, float z){
  return (d*x + (z - b)*y);
}
float f3(float x, float y, float z){
  return (c + a*z - z*z*z/3.0 - (x*x + y*y)*(1 + e*z) + gama*z*x*x*x);
}

//---------------------FUNCTIONS-----------------------------------


int main(){


    //initial values
    x_init = -2.0;
    y_init = 3.0;
    z_init = -2.0;

    t = 0.0;
    dt = 0.01;  //time steps
    t_max = 100;
    iter_max = (float) t_max/dt;

    //naming the file
    sprintf(name,"LangfordAttractor.txt");

    //open the .txt file
    fp = fopen(name, "w");

    //closing the file
    fclose(fp);

    x_old = x_init;
    y_old = y_init;
    z_old = z_init;

    //writing in the end of the file
    fp = fopen(name, "a");

    //writing data in the file
    fprintf(fp, "%f \t %f \t %f \t %f\n", t, x_old, y_old, z_old);

    //closing the file
    fclose(fp);

/*-----------------------------------------This part is important to make the graph in gnuplot-----------------------------------*/
    //condition to start the calculations and data storage
    while(j != 1)
    {
        printf("Digite 1 para iniciar.\n");
        scanf("%d", &j);
    }
/*-----------------------------------------This part is important to make the graph in gnuplot-----------------------------------*/

    for(iter = 0; iter < iter_max; iter++){


        k1x = f1(x_old, y_old, z_old)*dt;
        k1y = f2(x_old, y_old, z_old)*dt;
        k1z = f3(x_old, y_old, z_old)*dt;

        k2x = f1(x_old + k1x/2.0, y_old + k1y/2.0, z_old + k1z/2.0)*dt;
        k2y = f2(x_old + k1x/2.0, y_old + k1y/2.0, z_old + k1z/2.0)*dt;
        k2z = f3(x_old + k1x/2.0, y_old + k1y/2.0, z_old + k1z/2.0)*dt;

        k3x = f1(x_old + k2x/2.0, y_old + k2y/2.0, z_old + k2z/2.0)*dt;
        k3y = f2(x_old + k2x/2.0, y_old + k2y/2.0, z_old + k2z/2.0)*dt;
        k3z = f3(x_old + k2x/2.0, y_old + k2y/2.0, z_old + k2z/2.0)*dt;

        k4x = f1(x_old + k3x, y_old + k3y, z_old + k3z)*dt;
        k4y = f2(x_old + k3x, y_old + k3y, z_old + k3z)*dt;
        k4z = f3(x_old + k3x, y_old + k3y, z_old + k3z)*dt;

        x_new = x_old + (k1x + 2.0*(k2x + k3x) + k4x)/6.0;
        y_new = y_old + (k1y + 2.0*(k2y + k3y) + k4y)/6.0;
        z_new = z_old + (k1z + 2.0*(k2z + k3z) + k4z)/6.0;

        //incrementing t
        t = t + dt;

        //opening the file and writing the data indicated by fprintf
        fp = fopen(name, "a");

        //data that will be stored in the file
        fprintf(fp, "%f \t %f \t %f \t %f\n", t, x_old, y_old, z_old);

        //closing the file to avoid bugs
        fclose(fp);

        //microseconds sleep --> 1 seconds = 1000000 microseconds
        usleep(10000);

        x_old = x_new;
        y_old = y_new;
        z_old = z_new;
    }

    return 0;
}

