#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void salinim(double,double,double,double,double,double,double);

int main(){
	
	double L;							//ip uzunlugu
	double w;							//acisal hiz
	double baslangic_acisi;				
	double g;							//yercekimi ivmesi
	double t_salinim_suresi;
	double delta_t;						//birim zaman araligi
	double m;							// sarkaca bagli cismin kutlesi
	
	
	printf("sirasiyla sarkacin ip uzunlugu(L-metre) \n baslangic acisal hizini(w-rad/sn) \n baslangic acisi (Q-derece)  \n sarkacin bulundugu ortamdaki yer cekimi ivmesi(g-m/sn^2) \n salinim suresi(t-sn) \n"
	" olcum yapilacak hassasiyetteki zaman araligi(delta t-sn) degerlerini giriniz \n kutleyi kg cinsinden giriniz\n ");
	scanf("%lf %lf %lf %lf %lf %lf %lf",&L,&w,&baslangic_acisi,&g,&t_salinim_suresi,&delta_t,&m);
	
	salinim(L,w,baslangic_acisi,g,t_salinim_suresi,delta_t,m);
	
	}
	
	void salinim(double L,double w,double baslangic_acisi,double g,double  t_salinim_suresi,double delta_t,double  m) {
		
		FILE*fptr_w_t;
		FILE*fptr_Q_t;
		FILE*fptr_energy;
		FILE*fptr_acisal_momentum;
		FILE*fptr_Torq_t;
		
		fptr_w_t=fopen("sarkac1.txt","w");	// bu dosyanin bulundugu klasore tirnak icinde yazan isimde dosya aciniz. sonuclar oraya yazdirilacaktir
		fptr_Q_t=fopen("sarkac2.txt","w");
		fptr_energy=fopen("sarkac3.txt","w");
		fptr_acisal_momentum=fopen("sarkac4.txt","w");
		fptr_Torq_t=fopen("sarkac5.txt","w");
		
		double i;
		double Q;	// asagida aci radyal cinse cevrilicek
		double enerji;
		double Tork;		// acisal momentumun turevi torku verecektir. (L2-L1)/delta_t; 
		
		
		
		
		Q=M_PI*baslangic_acisi/180.0;// radyal cinsten
    	
    	
    	double Eo=(m*g*L*(1-cos(Q))) + (0.5*m*w*w*L*L);	//baslangictaki toplam enerji
    	double L1;
		double L2;	//acisal momentum L=rxp ==>> sonuc olarak L=m(rxv), v=wxr yon olarak r ye dik old. aradaki aci 90 derece old. direk L=m.v.r=m.w.r.r yazacagým islem printf'de
    	
	for( i=0 ; i <= (t_salinim_suresi)/delta_t ; i++){							//   (a-b)/delta_t kadar dongu olcak
		L1=m*w*L*L;
		Q = Q + w * delta_t;	
		w = w - ( g / L ) * sin( Q ) * delta_t;			//   cikarilan formuller sonucu islemler w'ya bagli iterasyon bagintisi
		L2=m*w*L*L;
		Tork=(L2-L1)/delta_t;			
		enerji=(m*g*L*(1-cos(Q))) + (0.5*m*w*w*L*L);
		
		printf(" w = %lf rad/sn  Q = %lf rad    t = %lf sn    L = %lf kg m^2/sn    Tork = %lf kg m^2/sn^2  enerji = %lf joule   yuzde hata = %lf \n",w,Q,delta_t*i,L1,Tork,enerji,100*fabs(1-(enerji/Eo)));//fabs=mutlak deger
		
			fprintf(fptr_w_t,"%lf   %lf\n",delta_t*i,w);				// t ye karsilik w degerleri
			fprintf(fptr_Q_t,"%lf   %lf\n",delta_t*i,Q);		//t ye karsilik Q degerleri
			fprintf(fptr_energy,"%lf   %lf\n",delta_t*i,enerji);
			fprintf(fptr_acisal_momentum,"%lf   %lf\n",delta_t*i,L1);
			fprintf(fptr_Torq_t,"%lf   %lf\n	",delta_t*i,Tork);
			
	}
	
	
	fclose(fptr_w_t);
	fclose(fptr_Q_t);// acilan her dosya kapatilmak zorunda
	fclose(fptr_energy);
	fclose(fptr_acisal_momentum);	
	fclose(fptr_Torq_t);
	}
	
	

