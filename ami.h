#define ami_abs(x) ((x)>0?(x):(-(x)))
#define ami_max_vector(x,pos,max,dim) {int ml; pos=0; max=x[0]; \
          for(ml=1;ml<dim;ml++) if(x[ml]>max) {max=x[ml]; pos=ml;} \
        }
#define ami_min_vector(x,pos,min,dim) {int ml; pos=0; min=x[0]; \
          for(ml=1;ml<dim;ml++) if(x[ml]<min) {min=x[ml]; pos=ml;} \
        }
#define ami_media_vector(x,alh,dim) {int ml; alh=0; \
          for(ml=0;ml<dim;ml++) alh+=x[ml]; \
          alh=alh/dim; \
        }
#define ami_normalizar_vector(x,dim) {int ml; double alh=0; \
          for(ml=0;ml<dim;ml++) alh+=x[ml]*x[ml]; \
          if(alh>0){\
            alh=sqrt(alh); \
            for(ml=0;ml<dim;ml++) x[ml]/=alh;}\
        }
#define ami_norma_vector(x,norma,dim) {int ml; norma=0; \
          for(ml=0;ml<dim;ml++) norma+=x[ml]*x[ml]; \
          if(norma>0) norma=sqrt((double) norma); \
        }
#define ami_producto_vectorial(v,u,z) {\
          z[0]=v[1]*u[2]-u[1]*v[2];\
          z[1]=v[2]*u[0]-v[0]*u[2];\
          z[2]=v[0]*u[1]-u[0]*v[1];\
        }
#define ami_matriz_vector(A,x,v,Nfil,Ncol) {int ml,mk;\
          for(ml=0;ml<Nfil;ml++){ v[ml]=A[ml][0]*x[0]; \
            for(mk=1;mk<Ncol;mk++) v[ml]+=A[ml][mk]*x[mk];}\
        }
#define ami_matriz_traspuesta_vector(A,x,v,Nfil,Ncol) {int ml,mk;\
          for(ml=0;ml<Nfil;ml++){ v[ml]=A[0][ml]*x[0]; \
            for(mk=1;mk<Ncol;mk++) v[ml]+=A[mk][ml]*x[mk];}\
        }
#define ami_matriz_traspuesta(A,At,NfilA,NcolA) {int ml,mk;\
          for(ml=0;ml<NfilA;ml++){ \
            for(mk=0;mk<NcolA;mk++) At[mk][ml]=A[ml][mk];}\
        }
#define ami_matriz_copia(A,B,NfilA,NcolA) {int ml,mk;\
          for(ml=0;ml<NfilA;ml++){ \
            for(mk=0;mk<NcolA;mk++) B[ml][mk]=A[ml][mk];}\
        }
#define ami_escalar_matriz(l,A,B,NfilA,NcolA) {int ml,mk;\
          for(ml=0;ml<NfilA;ml++){ \
            for(mk=0;mk<NcolA;mk++) B[ml][mk]=l*A[ml][mk];}\
        }
#define ami_vector_copia(u,v,N) {int ml;\
          for(ml=0;ml<N;ml++){ \
            v[ml]=u[ml];}\
        }
#define ami_vector_vector(x,v,a,dim) {int ml; a=x[0]*v[0];\
          for(ml=1;ml<dim;ml++) a+=x[ml]*v[ml];\
        }
#define ami_vector_resta_vector(x,v,a,dim) {int ml; a=x[0]-v[0];\
          for(ml=1;ml<dim;ml++) a+=x[ml]-v[ml];\
        }
#define ami_vector_suma_vector(x,v,a,dim) {int ml; a=x[0]+v[0];\
          for(ml=1;ml<dim;ml++) a+=x[ml]+v[ml];\
        }
#define ami_escalar_vector(x,a,v,dim) {int ml; \
          for(ml=0;ml<dim;ml++) v[ml]=x[ml]*a;\
        }
#define ami_matriz_matriz(A,B,C,NfilA,NcolA,NcolB) {int ml,mk,mu;\
          for(mu=0;mu<NfilA;mu++) \
            for(mk=0;mk<NcolB;mk++){\
              C[mu][mk]=A[mu][0]*B[0][mk];\
              for(ml=1;ml<NcolA;ml++) C[mu][mk]+=A[mu][ml]*B[ml][mk];}\
        }
#define ami_matriz_traspuesta_matriz(A,B,C,NfilA,NcolA,NcolB) {int ml,mk,mu;\
          for(mu=0;mu<NfilA;mu++) \
            for(mk=0;mk<NcolB;mk++){\
              C[mu][mk]=A[0][mu]*B[0][mk];\
              for(ml=1;ml<NcolA;ml++) C[mu][mk]+=A[ml][mu]*B[ml][mk];}\
        }
#define ami_calloc2d(direccion,tipo,height,width) {int ml,mk; \
          direccion=(tipo **) malloc(sizeof(tipo *)*(height)); \
          direccion[0]=(tipo *)malloc(sizeof(tipo)*(width)*(height)); \
          for(ml=0;ml<(height);ml++) direccion[ml]=&(direccion[0][ml*(width)]); \
          for(ml=0;ml<height;ml++) for(mk=0;mk<width;mk++) direccion[ml][mk]=0; \
        }
#define ami_malloc2d(direccion,tipo,height,width) {int ml; \
          direccion=(tipo **) malloc(sizeof(tipo *)*(height)); \
          direccion[0]=(tipo *)malloc(sizeof(tipo)*(width)*(height)); \
          for(ml=0;ml<(height);ml++) direccion[ml]=&(direccion[0][ml*(width)]);\
        }
#define ami_malloc2d_punteros(direccion,puntero_simple,tipo,height,width) {int ml; \
          direccion=(tipo **) malloc(sizeof(tipo *)*(height)); \
          direccion[0]=(tipo *) puntero_simple; \
          for(ml=0;ml<(height);ml++) direccion[ml]=&(direccion[0][ml*(width)]);\
        }
#define ami_free2d(direccion) { free(direccion[0]); free(direccion); }
#define ami_free2d_punteros(direccion) { free(direccion); }
#define ami_calloc3d(direccion,tipo,depth,height,width) {int ml,mk,mu; \
          direccion=(tipo ***) malloc(sizeof(tipo **)*(depth)); \
          direccion[0]=(tipo **)malloc(sizeof(tipo *)*(depth)*(height)); \
          direccion[0][0]=(tipo *)malloc(sizeof(tipo)*(depth)*(height)*(width)); \
          for(mu=0;mu<depth;mu++){ \
            for(ml=0;ml<(height);ml++) \
              direccion[0][ml+mu*(height)]=&(direccion[0][0][ml*(width)+mu*(width)*(height)]); \
            direccion[mu]=&(direccion[0][mu*(height)]);}\
          for(mu=0;mu<depth;mu++) for(ml=0;ml<height;ml++) for(mk=0;mk<width;mk++) direccion[mu][ml][mk]=0; \
        }
#define ami_malloc3d(direccion,tipo,depth,height,width) {int ml,mk,mu; \
          direccion=(tipo ***) malloc(sizeof(tipo **)*(depth)); \
          direccion[0]=(tipo **)malloc(sizeof(tipo *)*(depth)*(height)); \
          direccion[0][0]=(tipo *)malloc(sizeof(tipo)*(depth)*(height)*(width)); \
          for(mu=0;mu<depth;mu++){ \
            for(ml=0;ml<(height);ml++) \
              direccion[0][ml+mu*(height)]=&(direccion[0][0][ml*(width)+mu*(width)*(height)]); \
            direccion[mu]=&(direccion[0][mu*(height)]);}\
        }
#define ami_malloc3d_punteros(direccion,puntero_simple,tipo,depth,height,width) {int ml,mk,mu; \
          direccion=(tipo ***) malloc(sizeof(tipo **)*(depth)); \
          direccion[0]=(tipo **)malloc(sizeof(tipo *)*(depth)*(height)); \
          direccion[0][0]=(tipo *) puntero_simple; \
          for(mu=0;mu<depth;mu++){ \
            for(ml=0;ml<(height);ml++) \
              direccion[0][ml+mu*(height)]=&(direccion[0][0][ml*(width)+mu*(width)*(height)]); \
            direccion[mu]=&(direccion[0][mu*(height)]);}\
        }
#define ami_free3d(direccion) { free(direccion[0][0]); free(direccion[0]); free(direccion); }
#define ami_free3d_punteros(direccion) { free(direccion[0]); free(direccion); }
#define ami_malloc1d(direccion,tipo,size) {direccion=(tipo *) malloc(sizeof(tipo)*(size));}
#define ami_calloc1d(direccion,tipo,size) {int ml; direccion=(tipo *) malloc(sizeof(tipo)*(size)); \
          for(ml=0;ml<size;ml++) direccion[ml]=0;\
        }
#define ami_printf2d(comentario,direccion,height,width) {int ml,mk;  \
          for(ml=0;ml<height;ml++){\
            for(mk=0;mk<width;mk++) \
              printf("%s[%d][%d]=%e ",comentario,ml,mk,(double) direccion[ml][mk]); \
            printf("\n"); }printf("\n");\
        }
#define ami_printf2d_int(comentario,direccion,height,width) {int ml,mk;  \
          for(ml=0;ml<height;ml++){\
            for(mk=0;mk<width;mk++) \
              printf("%s[%d][%d]=%d ",comentario,ml,mk,(int) direccion[ml][mk]); \
            printf("\n");}\
          printf("\n");\
        }
#define ami_printf1d(comentario,direccion,size){ int ml; \
          for(ml=0;ml<size;ml++) printf("%s[%d]=%e \n",comentario,ml,(double) direccion[ml]); \
          printf("\n");\
        }
#define ami_printf1d_int(comentario,direccion,size){ int ml; \
          for(ml=0;ml<size;ml++) printf("%s[%d]=%d ",comentario,ml,(int) direccion[ml]); \
          printf("\n");\
        }
#define ami_printf(comentario,valor) printf("%s=%e\n",comentario,(double) valor);
#define ami_printf_int(comentario,valor) printf("%s=%d\n",comentario,(int) valor);
#define ami_printf3d(comentario,direccion,depth,height,width) {int ml,mk,mu; \
          for(mu=0;mu<depth;mu++){ for(ml=0;ml<height;ml++){ for(mk=0;mk<width;mk++) \
              printf("%s[%d][%d][%d]=%e ",comentario,mu,ml,mk,(double) direccion[mu][ml][mk]); \
              printf("\n");} printf("\n");} \
        }
#define ami_printf3d_int(comentario,direccion,depth,height,width) {int ml,mk,mu; \
          for(mu=0;mu<depth;mu++){ for(ml=0;ml<height;ml++){ for(mk=0;mk<width;mk++) \
              printf("%s[%d][%d][%d]=%d ",comentario,mu,ml,mk,(int) direccion[mu][ml][mk]); \
              printf("\n");} printf("\n");} \
        }


