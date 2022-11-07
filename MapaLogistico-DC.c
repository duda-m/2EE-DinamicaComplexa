#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int i, j, t_max;
float x_init = 0.01;
float x_old, x_new, dt, t, r, s;
char texto[200];

//opening the file fp
FILE*fp;

int main(){

    //sprintf(texto, "LogisticMapTeste.txt");
    sprintf(texto,"LogisticMap_x_init_%f.txt", x_init);

    //variable that opens the file; w --> create an empty file for writing
    fp = fopen(texto, "w");

    //closing the txt file
    fclose(fp);

    for(r = 0.0; r < 4.0; r += 0.0001)
    {
        s = 0.0;

        x_old = x_init;

        //procurando o x estavel
        for(i = 0; i <= 300; i++)
        {
            x_new = r*x_old*(1.0 - x_old);

            x_old = x_new;
        }

        //salvando os valores de x ponto
        for(j = 0; j < 50; j++)
        {
            x_new = r*x_old*(1.0 - x_old);

            x_old = x_new;

            fp = fopen(texto, "a");

            fprintf(fp, "%f \t %.4f\n", r, x_new);

            fclose(fp);
        }
    }

    return 0;

}
