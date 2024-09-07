/*
  *   蔵本モデルの数値シミュレーション
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 500 //関数の定義のためにここに必要
double rand_cauchy( double mu, double gamma);
double Uniform(void);
double order(double theta[N+1]);//複素秩序変数の絶対値を計算する関数
double arg(double theta[N+1]);//複素秩序変数の偏角を計算する関数

int main(void){
    //fileの準備
    FILE *fp_gif,*fp_order;
    char name_txt[256],name_gif[256],name_order[256];
    sprintf(name_gif,"gif.txt");
    if((fp_gif = fopen(name_gif,"w"))==NULL){
        printf("file open error\n");
    }
    sprintf(name_order,"order.txt");
    if((fp_order = fopen(name_order,"w"))==NULL){
        printf("file open error\n");
    }

    int i,j,k;
    double pi = atan(1.0)*4.0;
    double theta[N+1],thetanew[N+1];
    double omega[N+1];//固有各振動数
    double K=10.0;//相関の強さを表す定数と刻み幅
    double t = 0.0,dt = 0.0010,trec=0.0,T = 5.0,dtrec=T/100.0;
    double R,Theta;
    double omega0 = 4.0,gamma = 1.0;
    srand((unsigned) time(NULL));
    //初期条件の設定
    for(i=1;i<=N;i++){
        theta[i]=2.0*pi*Uniform();
        thetanew[i]=theta[i];
        omega[i] = rand_cauchy(omega0,gamma);
    }
    R = order(theta);
    Theta = arg(theta);
    //file output
    fprintf(fp_order,"%lf %lf %lf\n",t,R,Theta);
    for(i=1;i<=N;i++){
        fprintf(fp_gif,"%lf %lf\n",cos(theta[i]),sin(theta[i]));
    }
    fprintf(fp_gif,"\n\n");

    //時間発展の計算
    while(t<=T){
        R = order(theta);
        Theta = arg(theta);
        for(i=1;i<=N;i++){
            thetanew[i] += omega[i]*dt;
            thetanew[i] += -K*R*sin(theta[i]-Theta)*dt;
        }
        for(i=1;i<=N;i++){
            theta[i]=thetanew[i];
        }

        //fileへの出力
        if(fabs(t-trec)<0.5*dt){
            R = order(theta);
            Theta = arg(theta);
            fprintf(fp_order,"%lf %lf %lf\n",t,R,Theta);
            for(i=1;i<=N;i++){
                fprintf(fp_gif,"%lf %lf\n",cos(theta[i]),sin(theta[i]));
            }
            fprintf(fp_gif,"\n\n");
            trec += dtrec;
            printf("t = %lf:%lf\n",t,R);
        }
        t+=dt;
    }
    fclose(fp_gif);
    fclose(fp_order);
    return 0;
}


double order(double theta[N+1]){
    double X=0.0,Y=0.0;
    for(int i=1;i<=N;i++){
        X += cos(theta[i])/(double)N;
        Y += sin(theta[i])/(double)N;
    }
    return sqrt(X*X+Y*Y);
}

double arg(double theta[N+1]){
    double X=0,Y=0;
    for(int i=1;i<=N;i++){
        X += cos(theta[i])/(double)N;
        Y += sin(theta[i])/(double)N;
    }
    return atan2(Y,X);
}


double Uniform(void){
    return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}

double rand_cauchy( double mu, double gamma){
    return mu + gamma*tan(M_PI*( Uniform()-0.5 ));
}
