#include <math.h>
#include <stdio.h>
#include <stdlib.h>
const float pi = 3.1415926535;

int main ()
{
  printf("\n");
  printf("=====================================================================================================\n\n");
  
  printf("Bem vindo ao gerador de elipses\n\n");
  
  printf("=====================================================================================================\n\n");

  float borda = 1, a = 1.0, b = 1.0, ang = 0.0, formula, H, V;
  int h = -50, v = 50, continuar;


  do 
  {
    // Detecção dos parâmetros da elipse:

    printf("Semieixo horizontal: "); 
    scanf("%f", &a);
    printf("\n");
    
    printf("Semieixo vertical: "); 
    scanf("%f", &b);
    printf("\n");
    
    printf("Rotação em graus: "); 
    scanf("%f", &ang);
    printf("\n");
    ang = (ang - floor(ang/360)); // Retirando as rotações redundantes
    ang = (ang/180)*pi; // Transformando de graus para radianos

    printf("Erro de borda: "); 
    scanf("%f", &borda);
    printf("\n");
    borda = borda/10;

    // Todos os parâmetros da elipse foram informados.
    printf("=====================================================================================================\n\n");
    // Desenho da elipse:

      for(v = 25; v >= -25; v--) // Movimento vertical
      {

        for (h = -50; h <= 50; h++) // Movimento horizontal
        {

          H = 1.0*h*cos(1.0*ang) + 1.0*v*sin(1.0*ang);
          V = -1.0*h*sin(1.0*ang) + 1.0*v*cos(1.0*ang);

          formula = pow((H/a),2) + pow((V/b),2);

          if (formula <= 1)
            printf("·");
          else
            if (formula <= (1 + borda))
              printf("#");
            else
              printf(" ");

          if (h == 50)
            printf("\n");
        }

      }

    // Fim do desenho da elipse.
    printf("\n\n=====================================================================================================\n\n");

    printf("Insira 1 se quiser continuar: ");
    scanf("%i", &continuar);
    printf("\n\n");
  }
  while (continuar == 1);



  printf("\n");
  return 0;
}