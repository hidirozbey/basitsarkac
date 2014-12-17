#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void salinim(double,double,double,double,double,double);

int main(){
	
	int i;
	double t_salinim_suresi;
	double delta_t;
	double L;
	double g;
	double baslangic_acisi;
	double m;
	
	
	printf("sirasiyla sarkacin ip uzunlugu(L-metre) \n baslangic acisi (Q-derece) \n sarkacin bulundugu ortamdaki yer cekimi ivmesi(g-m/sn^2) \n salinim suresi(t-sn) \n"
	" olcum yapilacak hassasiyetteki zaman araligi(delta t-sn) degerlerini giriniz \n kutleyi kg cinsinden giriniz\n ");
	scanf("%lf %lf %lf %lf %lf %lf",&L,&baslangic_acisi,&g,&t_salinim_suresi,&delta_t,&m);
	
	salinim(L,baslangic_acisi,g,t_salinim_suresi,delta_t,m);
	
    
	}
	
	
	void salinim(double const L,double const baslangic_acisi,double const g,double const t_salinim_suresi,double delta_t,double const m) {
		
		FILE*fptr_w_t;
		FILE*fptr_Q_t;
		
		fptr_w_t=fopen("sarkac1.txt","w");
		fptr_Q_t=fopen("sarkac2.txt","w");
		int i;
		double w;	// acisal hiz
		double Q;	// asagida aci radyal cinse cevrilicek
		double anlik_aci;
		double enerji;
		
		
		Q=M_PI*baslangic_acisi/180.0;// radyal cinsten
    	
    	double Eo=m*g*L*(1-cos(Q));	//baslangictaki toplam enerji
    	
    	w=sqrt((2*g/L)*(1-cos(Q)));// Q=0 iken w max degerini alir . Q max degerindeki tüm potansiyel enerji, Q=0 degerinde kinetik enerjiye aktarilacaktir.// bu formul sonucunda Q max degeri radyal olarak yerine konulur.
		anlik_aci=0;				// baslangici kinetik enerjinini max oldugu yerden alacagim.
	
	
	for( i=0 ; i <= (t_salinim_suresi)/delta_t ; i++){							//   (a-b)/delta_t kadar dongu olcak
		w = w - ( g / L ) * sin( anlik_aci + w * delta_t  ) * delta_t;			//   cikarilan formuller sonucu islemler w'ya bagli iterasyon bagintisi
		anlik_aci = anlik_aci + w * delta_t;									
		enerji=0.5*m*w*w*L*L+m*g*L*(1-cos(anlik_aci));  // mgh + 1/2 m v^2 formulunun acisal hiz ve l  türünden yazilmis hali//18.12.2014 mekanik dersindeki defterden tum sonuclari bulabilirsiniz
		
		printf(" w = %lf rad/sn  Q = %lf rad    t=%lf sn  enerji=%lf joule   yuzde hata= %lf \n",w,anlik_aci,delta_t*i,enerji,100*fabs(1-(Eo/enerji)));//fabs=mutlak deger
		
			fprintf(fptr_w_t,"%lf   %lf\n",delta_t*i,w);				// t ye karsilik w degerleri
			fprintf(fptr_Q_t,"%lf   %lf\n",delta_t*i,anlik_aci);		//t ye karsilik Q degerleri
			
	}
	
	
	fclose(fptr_w_t);
	fclose(fptr_Q_t);// acilan her dosya kapatilmak zorunda
		
	}
	

