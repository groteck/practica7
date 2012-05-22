#include <stdlib.h>
#include "ami.h"
#include "ami_bmp.h"
#include <math.h>
#define coor(i, j, width) ((width)*(j)+(i))
//Funcion que calcula el valor resultante de la aplicación de la máscara en una posición
//dada. Canal es el canal de entrada, máscara sera la máscara a aplicar, width y height
//son las dimensiones de la imagen, Y sera la fíla y X la columna en que se encuentra
//el pixel al que queremos aplicar la máscara.
float masc_posi(float *canal_input,float m[3][3],int width,int height,int j,int i){
     int h, v, dh, dv;
     float suma = 0;

     for (dh = -1; dh <= 1; dh++) {
          for (dv = -1; dv <= 1; dv++) {
               h = i + dh;
               // Si nos salimos de la imagen, cogemos el píxel más
               // cercano:
               if (h < 0) {
                    h = 0;
               }
               if (h >= width) {
                    h = width -1;
               }

               v = j + dv;
               if (v < 0) {
                    v = 0;
               }
               if (v >= height) {
                    v = height -1;
               }

               suma += m[dh + 1][dv + 1] * canal_input[coor(h, v, width)];
          }
     }

     return suma;
};

//Funcion para calcular la aplicación de la máscara a un canal
void aan_mascara_canal(float *canal_input, float *canal_output, int width, int height,
    float m[3][3]){
  int i,j;

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      (canal_output)[(i*width)+j]= masc_posi(canal_input,m,width,height,i,j);
    };
  };
};

void calculo_gradiente_canal(float *canal_input,float *canal_output,float h[3][3],float v[3][3],int width,int height){
  int i;
  float *canalh,*canalv;

  canalh = (float*)malloc((width*height)*sizeof(float));
  canalv = (float*)malloc((width*height)*sizeof(float));

  aan_mascara_canal(canal_input,canalh,width,height,h);
  aan_mascara_canal(canal_input,canalv,width,height,v);

  for(i=0;i<width*height;i++){
    canal_output[i]= hypotf(canalh[i],canalv[i]);
  }
  free(canalh);
  free(canalv);
}

void ecuacion_propagacion(float *canal,int width,int height,float dt,float *F,int k){
  int i,j;
  float *gradiente,raiz;

  float masc_horizontal[3][3]= {{-(2.-sqrt(2.))/4.,0.,(2.-sqrt(2.))/4.},{-2.*(sqrt(2.)-1.)/4,0.,2.*(sqrt(2.)-1.)/4.},{-(2.-sqrt(2.))/4.,0.,(2.-sqrt(2.))/4.}};
  float masc_vertical[3][3]  = {{-(2.-sqrt(2.))/4.,-2.*(sqrt(2.)-1.)/4.,-(2.-sqrt(2.))/4.},{0.,0.,0.},{(2.-sqrt(2.))/4.,2.*(sqrt(2.)-1.)/4.,(2.-sqrt(2.))/4.}};

  gradiente = (float*)malloc((width*height)*sizeof(float));

  calculo_gradiente_canal(canal,gradiente,masc_horizontal,masc_vertical,width,height);

  for(j=0;j<width;j++){
    for(i=0;i<height;i++){
      int posicion = (width*i)+j;
      canal[posicion]=canal[posicion]+((F[posicion])*(dt*gradiente[posicion]));
    }
  }
  free(gradiente);

}

void aan_ecuacion_propagacion_frentes(float *red_input, float *green_input, float
    *blue_input, float *red_output, float *green_output, float *blue_output, int width, int
    height, float dt, int Niter, float *F){
  int i,j;
  unsigned char *rojo,*verde,*azul;
  char name[200];

  rojo = (unsigned char *)malloc((width*height)*sizeof(unsigned char));
  verde = (unsigned char *)malloc((width*height)*sizeof(unsigned char));
  azul = (unsigned char *)malloc((width*height)*sizeof(unsigned char));

  for(i=0;i<(width*height);i++){
    red_output[i] = (unsigned char)red_input[i];
    verde[i]      = (unsigned char)green_input[i];
    azul[i]       = (unsigned char)blue_input[i];
  }

  for(i=0;i<Niter;i++){
    ecuacion_propagacion(red_output,width,height,dt,F,i);
    for(j=0;j<(width*height);j++){
      if (red_output[j] < 0){
        red_output[j]=0;
      }
      else{
        if (red_output[j]>255){
          red_output[j]=255;
        }
      }
      rojo[j] = (unsigned char)red_output[j];

    }
    sprintf(name,"/home/groteck/Imágenes/practica7/resultado/imagen_%d.bmp",100000+i);
    ami_write_bmp(name,rojo,verde,azul,width,height);
  }
  free(rojo);
  free(verde);
  free(azul);
};

int main(){
  unsigned char *ro_ch,*ve_ch,*az_ch;
  float *red_input,*red_output,*blue_input,*blue_output,*green_input,*green_output,*F;
  char fentrada[200];
  int i,niter,tam,h,w,option;
  float dt;
  printf("---------------MENU-----------------.\n");
  printf("Introduzca la direccion del archivo\n");
  scanf("%s",fentrada);
  printf("introduzca dt \n");
  scanf("%f",&dt);
  printf("Introduzca numero de iteraciones\n");
  scanf("%d",&niter);
  printf("\nPor favor elija una opción para el cálculo de la velocidad\n   1-) Velocidad inversa a la magnitud de un canal\n   2-) Velocidad inversa a la magnitud del gradiente\n   3-) Otro valor para continuar\n");
  scanf("%d",&option);

  ami_read_bmp(fentrada,&ro_ch,&ve_ch,&az_ch, &w,&h);
  tam=w*h;
  F=(float*)malloc(tam*sizeof(float));
  red_input=(float*)malloc(tam*sizeof(float));
  blue_input=(float*)malloc(tam*sizeof(float));
  green_input=(float*)malloc(tam*sizeof(float));
  red_output=(float*)malloc(tam*sizeof(float));
  blue_output=(float*)malloc(tam*sizeof(float));
  green_output=(float*)malloc(tam*sizeof(float));
  for(i=0;i<tam;i++){
    red_input[i]=ro_ch[i];
    blue_input[i]=az_ch[i];
    green_input[i]=ve_ch[i];
  }
  switch(option){
    case 1:{
             float k;
             printf("\nIntroduzca un valor para el parámetro K\n");
             scanf("%f",&k);
             for(i=0;i<tam;i++){
               F[i]= k * (255-green_input[i]);
             }
             break;
           }
    case 2:{
             float m,k;
             float *gradiente;
             float masc_horizontal[3][3]= {{-(2.-sqrt(2.))/4.,0.,(2.-sqrt(2.))/4.},{-2.*(sqrt(2.)-1.)/4,0.,2.*(sqrt(2.)-1.)/4.},{-(2.-sqrt(2.))/4.,0.,(2.-sqrt(2.))/4.}};
             float masc_vertical[3][3]  = {{-(2.-sqrt(2.))/4.,-2.*(sqrt(2.)-1.)/4.,-(2.-sqrt(2.))/4.},{0.,0.,0.},{(2.-sqrt(2.))/4.,2.*(sqrt(2.)-1.)/4.,(2.-sqrt(2.))/4.}};
             float min;

             gradiente=(float*)malloc((tam)*sizeof(float));
             printf("\nIntroduzca un valor para el parámetro K\n");
             scanf("%f",&k);
             printf("\nIntroduzca un valor para el parámetro M\n");
             scanf("%f",&m);

             calculo_gradiente_canal(green_input,gradiente,masc_horizontal,masc_vertical,w,h);
             for(i=0;i<tam;i++){
               if((gradiente[i]/m) <1  ){
                 min= gradiente[i]/m;
               }
               else min = 1;
               F[i]=k*(1-min);
             }
             break;
           }
    default:{
              for(i=0;i<tam;i++){
                F[i] = green_input[i];
              }
              break;
            }
  }
  aan_ecuacion_propagacion_frentes(red_input,green_input,blue_input,red_output,green_output,blue_output,w,h,dt,niter,F);
  free(red_input);
  free(blue_input);
  free(green_input);
  free(red_output);
  free(blue_output);
  free(green_output);
  free(ro_ch);
  free(az_ch);
  free(ve_ch);
  free(F);
  printf("FINISH");
  return 0;
}
