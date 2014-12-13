#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
	
	int i;
	double t_salinim_suresi;
	double delta_t;
	double w;
	double L;
	double g;
	double Q;
	double anlik_aci;
	double baslangic_acisi;
	double toplam_Enerji;
	double enerji;
	
	

	
	printf("sirasiyla sarkacin ip uzunlugu(L-metre) \n baslangic acisi (Q-derece) \n sarkacin bulundugu ortamdaki yer cekimi ivmesi(g-m/sn^2) \n salinim suresi(t-sn) \n"
	" olcum yapilacak hassasiyetteki zaman araligi(delta t-sn) degerlerini giriniz \n ");
	scanf("%lf %lf %lf %lf %lf",&L,&baslangic_acisi,&g,&t_salinim_suresi,&delta_t);
	
	
    Q=M_PI*baslangic_acisi/180.0;// radyal cinsten
    
    w=sqrt((2*g/L)*(1-cos(Q)));// Q=0 icin w max degeri; baslangici Q=0 dan alicaz
	anlik_aci=0;
	
	for( i=0 ; i <= (t_salinim_suresi)/delta_t ; i++){
		w = w - ( g / L ) * sin( anlik_aci + w * delta_t  ) * delta_t;
		anlik_aci = anlik_aci + w * delta_t;
		
		printf(" w = %lf  Q = %lf   \n",w,anlik_aci);
	}
	
	
	return 0;
	
}
