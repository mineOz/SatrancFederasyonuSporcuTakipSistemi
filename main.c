#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOS_KAYIT 0
#define MAX_KAYIT 9000

typedef struct {

    int lisansNo;
    char tcKimlik[12];
    char adSoyad[31];
    int plaka;
    int ukdPuani;

}sporcu;
typedef struct {

    int turnuvaNo;
    char turnuvaAdi[41];
    char tarih[12];
    char sehir[16];

}turnuva;
typedef struct {

    int turnuvaNo;
    int turNO;
    int bLisans;
    int sLisans;
    int sonuc;
    float bUkd;
    float sUkd;

}mac;

sporcu oyuncuOku(int lisansNo,FILE *sporcuDos);
turnuva turnuvaOku(int turnuvaNo,FILE *turnuvaDos);
void oyuncuYaz(sporcu bir_sporcu,int lisansNo,FILE *sporcuDos);
void oyuncuEkle();
void menuSecim();
void dosya_yarat();
void oyuncuilGuncelle();
void bitenTurnuvaAktar();
void birOyuncuListele();
void birIldekiOyuncular();
void illerdekiOyuncuSayisi();
void ukd10listele();
void birTurnuvaBilgi();
void birOyuncuBilgiVeTurnuva();
int sayiAl(int altSinir,int ustSinir);
void siralama(int v1[][2],int i);
void siralama1(int v1[][2],int i);
void yerDegistirme(int *sayi, int *sayi2);
void beyazSiyahComp();

int main(){

    menuSecim();
    return 0;

    }


sporcu oyuncuOku(int lisansNo,FILE *sporcuDos){//Anahtar olan lisans numarasina göre sporcu dosyasindaki verilerin okunmasini saglar.

        sporcu bir_sporcu;

        fseek(sporcuDos,(lisansNo-1000)*sizeof(sporcu),SEEK_SET);
        fread(&bir_sporcu,sizeof(sporcu),1,sporcuDos);

        return bir_sporcu;

}
turnuva turnuvaOku(int turnuvaNo,FILE *turnuvaDos){//Anahtar olan turnuva numarasina gore turnuva dosyasindaki verilerin okunmasini saglar.

    turnuva bir_turnuva;

    fseek(turnuvaDos,(turnuvaNo-1)*sizeof(turnuva),SEEK_SET);
    fread(&bir_turnuva,sizeof(turnuva),1,turnuvaDos);

    return bir_turnuva;

}
void oyuncuYaz(sporcu bir_sporcu,int lisansNo,FILE *sporcuDos){//Sporcu dosyasindaki verilerin yazilmasini saglar.

        fseek(sporcuDos,(lisansNo-1000)*sizeof(sporcu),SEEK_SET);
        fwrite(&bir_sporcu,sizeof(sporcu),1,sporcuDos);

}
void menuSecim(){ //Kullaniciya menu goruntuler

    int secim;

    do{


    printf("\n1)Biten bir turnuvaya iliskin bilgilerin sisteme aktarilmasi");
    printf("\n2)Bir oyuncunun bilgilerinin listelenmesi");
    printf("\n3)Bir oyuncunun bilgilerinin ve katildigi turnuvalarda oynadigi maclarin listelenmesi");
    printf("\n4)Bir ildeki tum oyuncularin listelenmesi");
    printf("\n5)UKD puani en yuksek 10 oyuncunun listelenmesi");
    printf("\n6)Illerdeki oyuncu sayilarinin listelenmesi");
    printf("\n7)Bir turnuvanin bilgilerinin ve turnuvada oynanan maclarin listelenmesi");
    printf("\n8)Tum maclardaki beyaz-siyah karsilastirmasi");
    printf("\n9)Yeni bir oyuncunun eklenmesi");
    printf("\n10)Bir oyuncunun ilinin guncellenmesi");
    printf("\n11)Cikis icin.");

    printf("\n\nSecim yapin:");

    secim=sayiAl(1,11);



    switch(secim)
            {
            case 1:
                bitenTurnuvaAktar();
            break;

            case 2:
                //birOyuncuListele(sporcuDos);
                birOyuncuListele();
                break;
            case 3:
                birOyuncuBilgiVeTurnuva();
                break;
            case 4:
                birIldekiOyuncular();
                break;
            case 5:
                ukd10listele();
                break;
            case 6:
                illerdekiOyuncuSayisi();
                break;
            case 7:
                birTurnuvaBilgi();
                break;
            case 8:beyazSiyahComp();
                break;
            case 9:
                oyuncuEkle();
                break;
            case 10:
                oyuncuilGuncelle();
                break;
            }
    }while(secim!=11);

}
void oyuncuEkle(){ //Kullanicidan istenen bilgileri alarak dosyaya oyuncu ekler

        FILE *sporcuDos;
        int lisans;
        sporcu bir_sporcu;

     if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");
        }
    }


    printf("\nEklemek istediginiz oyuncunun lisans numarasini giriniz:");
    lisans=sayiAl(1000,9999);

    bir_sporcu=oyuncuOku(lisans,sporcuDos);

    if(bir_sporcu.lisansNo==BOS_KAYIT){

            bir_sporcu.lisansNo=lisans;
            printf("\nOyuncunun tc kimlik numarisini giriniz:");
            fflush(stdin);
            gets(bir_sporcu.tcKimlik);
            printf("\nOyunucun ad ve soy adini giriniz:");
            fflush(stdin);
            gets(bir_sporcu.adSoyad);
            printf("\nOyucunun ilini girinz:");
            scanf("%d",&bir_sporcu.plaka);
            printf("\nOyuncunun ukd puanini giriniz:");
            scanf("%d",&bir_sporcu.ukdPuani);

            oyuncuYaz(bir_sporcu,lisans,sporcuDos);

            /*fseek(sporcuDos,(lisans-1000)*sizeof(sporcu),SEEK_SET);
            fwrite(&bir_sporcu,sizeof(sporcu),1,sporcuDos);*/

    }
    else{
            printf("\nOyuncu ekleme basarisiz.");
    }
    fclose(sporcuDos);

}
void dosya_yarat(){ //Dosya olusturmada kullanilir
    FILE *sporcuDos;
    sporcu bos_kayit;
    int i;

    bos_kayit.lisansNo=BOS_KAYIT;
    bos_kayit.ukdPuani=BOS_KAYIT;

    if((sporcuDos=fopen("sporcular.dat","wb"))==NULL)
        printf("Bos kayitlar iceren sporcuDos yaratilamadi.\n");
    else {
        for(i=1;i<=MAX_KAYIT;i++)
            fwrite(&bos_kayit,sizeof(sporcu),1,sporcuDos);

    }
}
void oyuncuilGuncelle(){ // lisans numarasi alinan oyuncunun ilinin guncellenmesi yapilir

        FILE *sporcuDos;
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");

        }
    }
    sporcu bir_sporcu;
    int lisans;

    printf("Ilini guncellemek istediginiz oyuncunun lisans numarasini giriniz:");
    lisans=sayiAl(1000,9999);

    bir_sporcu=oyuncuOku(lisans,sporcuDos);

    if(bir_sporcu.lisansNo==0){
        printf("\nBu lisans numarasina sahip bir oyuncu yok.");
    }
    else{

        printf("Yeni il plaka kodunu giriniz:");
        bir_sporcu.plaka=sayiAl(1,81);

        oyuncuYaz(bir_sporcu,lisans,sporcuDos);

       /* fseek(sporcuDos,(lisans-1000)*sizeof(sporcu),SEEK_SET);
        fwrite(&bir_sporcu,sizeof(sporcu),1,sporcuDos);*/

    }
    fclose(sporcuDos);
}
void bitenTurnuvaAktar(){ // bir oyuncunun bilgilerini ve katildigi turnuvalardaki maclari listeler

        FILE *sporcuDos;
        FILE *turnuvaDos;
        FILE *macDos;
        FILE *dosya4;
        FILE *dosya5;
        turnuva bir_turnuva;
        int son_kayit,ortalamaUKD,macSonucu,beyazLisans,siyahLisans;
        sporcu beyaz_sporcu,siyah_sporcu;
        mac bir_mac;
        float beyazPUAN,beyazDegisim;
        float siyahPUAN,siyahDegisim;

     if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");
        }
    }
    if((turnuvaDos=fopen("turnuvalar.dat","rb+"))==NULL) {
        turnuvaDos=fopen("turnuvalar.dat","wb");
        if((turnuvaDos=fopen("turnuvalar.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");
            }
        }
     if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
        macDos=fopen("tum_maclar.txt","w");
        if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
            printf("dosyasi acilamadi.\n");

        }
    }
    if((dosya4=fopen("turnuva_genel.txt","r+"))==NULL){
        dosya4=fopen("turnuva_genel.txt","w");
        if((dosya4=fopen("turnuva_genel.txt","r+"))==NULL)
            printf("dosyasi acilamadi.\n");
    }

    if((dosya5=fopen("turnuva_maclar.txt","r+"))==NULL){
        dosya5=fopen("turnuva_maclar.txt","w");
        if((dosya5=fopen("turnuva_maclar.txt","r+"))==NULL)
            printf("dosyasi acilamadi.\n");
    }



    son_kayit=(ftell(turnuvaDos)/sizeof(turnuva))+1; //Son kayitin konumu hesaplaniyor

    bir_turnuva=turnuvaOku(son_kayit,turnuvaDos);

    fscanf(dosya4,"%[^\n]\n",&bir_turnuva.turnuvaAdi);
    fscanf(dosya4,"%[^\n]\n",&bir_turnuva.tarih);
    fscanf(dosya4,"%[^\n]\n",&bir_turnuva.sehir);

    bir_turnuva.turnuvaNo=son_kayit;

    fscanf(dosya4,"%d",&ortalamaUKD);

    bir_turnuva=turnuvaOku(bir_turnuva.turnuvaNo,turnuvaDos);

         while(!feof(dosya5)){

                fscanf(dosya5,"%d %d %d %d %f %f"
                                                ,&bir_mac.turNO,&bir_mac.bLisans,&bir_mac.sLisans
                                                ,&bir_mac.sonuc,&bir_mac.bUkd,&bir_mac.sUkd);
                beyazLisans=bir_mac.bLisans;
                siyahLisans=bir_mac.sLisans;

            beyaz_sporcu=oyuncuOku(beyazLisans,sporcuDos);
            siyah_sporcu=oyuncuOku(siyahLisans,sporcuDos);

            if(siyah_sporcu.ukdPuani<1000)
                siyah_sporcu.ukdPuani=ortalamaUKD;
            if(beyaz_sporcu.ukdPuani<1000)
                beyaz_sporcu.ukdPuani=ortalamaUKD;

            beyaz_sporcu.ukdPuani+=(float)bir_mac.bUkd;
            siyah_sporcu.ukdPuani+=(float)bir_mac.sUkd;

        switch(bir_mac.sonuc){

           case 1:
                    beyazDegisim=bir_mac.bUkd+beyazDegisim;
                    beyazPUAN=beyazPUAN+1;
                break;

           case 2:
               siyahDegisim=bir_mac.sUkd+siyahDegisim;
               siyahPUAN=siyahPUAN+1;

                break;

           case 0:  beyazPUAN+=0.5;
                    siyahPUAN+=0.5;

                break;

        }

            if(beyaz_sporcu.ukdPuani<1000)
                beyaz_sporcu.ukdPuani=0;
            if(siyah_sporcu.ukdPuani<1000)
                siyah_sporcu.ukdPuani=0;

            oyuncuYaz(beyaz_sporcu,beyazLisans,sporcuDos);
            oyuncuYaz(siyah_sporcu,siyahLisans,sporcuDos);

        fseek(macDos,0L,SEEK_END);

        fprintf(macDos,"%d %d %d %d %d %.2f %.2f\n"
                   ,bir_turnuva.turnuvaNo,bir_mac.turNO,bir_mac.bLisans
                   ,bir_mac.sLisans,bir_mac.sonuc,bir_mac.bUkd,bir_mac.sUkd);

    }

    printf("Turnuva bilgileri basarili bir sekilde sisteme akrarilmistir.");

    fclose(sporcuDos);
    fclose(turnuvaDos);
    fclose(macDos);
    fclose(dosya4);
    fclose(dosya5);

    }
void birOyuncuListele(){ //TC no alinarak oyuncu bilgilerine ulasilir ve listelenir

        FILE *sporcuDos;
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");

        }
    }


    sporcu bir_sporcu;
    char oyuncuTc[12];
    int lisans,i,sonuc;

    printf("\nOyunucunun tc kimlik numarasini giriniz:");
    fflush(stdin);
    gets(oyuncuTc);

    rewind(sporcuDos);

    for(i=1;i<MAX_KAYIT;i++){

        fread(&bir_sporcu,sizeof(sporcu),1,sporcuDos);


        if( (strcmp(oyuncuTc,bir_sporcu.tcKimlik))== 0){ // TC kimlik no karsilastirilmasi yapiliyor

            lisans=bir_sporcu.lisansNo;

            printf("\nLisans No  Tc kimlik no        Ad soyad            Il plaka            Ukd\n");
            printf("--------  --------------     ------------------    --------           ------");

            bir_sporcu=oyuncuOku(lisans,sporcuDos);

            printf("\n%6d %15s %23s %10d %17d\n\n"
                   ,bir_sporcu.lisansNo,bir_sporcu.tcKimlik,bir_sporcu.adSoyad,bir_sporcu.plaka,bir_sporcu.ukdPuani);

            break;
            }

        }
        fclose(sporcuDos);
    }
void birIldekiOyuncular(){ // istenilen plaka kodundaki tum oyuncularin bilgileri listelenir

    FILE *sporcuDos;
    sporcu bir_sporcu;
    int plaka,i,gecici;


    if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");}
            }



    printf("\nGormek istediginiz ilin plaka kodunu giriniz(1,81):");
    plaka=sayiAl(1,81);


    rewind(sporcuDos);

        printf("Lisans No  Tc kimlik no           Ad soyad            Il plaka           Ukd\n");
        printf("--------   -------------          ----------------    --------           ----\n");

    for(i=1;i<MAX_KAYIT;i++){

        fread(&bir_sporcu,sizeof(sporcu),1,sporcuDos);

        if(plaka==bir_sporcu.plaka){

        printf("%6d %17s %22s %10d %18d\n"
               ,bir_sporcu.lisansNo,bir_sporcu.tcKimlik,bir_sporcu.adSoyad,bir_sporcu.plaka,bir_sporcu.ukdPuani);
        }


    }

    fclose(sporcuDos);

}
void illerdekiOyuncuSayisi(){ //Plaka kodlarinin sahip oldugu oyuncu sayilari plakalar sirali sekilde listelenir

        FILE *sporcuDos;
        sporcu bir_sporcu;
        int sayac[82][2]={0}; // 0- oyuncu sayisi
                            //   1- il plaka kodu
        int i;

     if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");


        }
    }


    rewind(sporcuDos);

    for(i=1;i<MAX_KAYIT;i++){

        fread(&bir_sporcu,sizeof(sporcu),1,sporcuDos);

        if(bir_sporcu.lisansNo!=0){

            sayac[bir_sporcu.plaka][0]++;
            sayac[bir_sporcu.plaka][1]=bir_sporcu.plaka;
        }
    }

    siralama(sayac,82);

            printf("\nIl plaka Kodu Oyuncu Sayisi");
            printf("\n------------- -------------");

    for(i=1;i<82;i++){

        if(sayac[i][0]!=0){


            printf("\n%5d \t%10d",sayac[i][1],sayac[i][0]);
        }
    }

    fclose(sporcuDos);
}
void ukd10listele(){//UKD puani yuksek 10 oyuncunun ve 10.ile ayni oyuncularin puanlari sıralanarak listelenir

        FILE *sporcuDos;
        sporcu bir_sporcu;

        int sayac[MAX_KAYIT][2]={0}; // 0-UKD puanlari
                                        //1-lisans numaralari oyuncu verilerine daha kolay ulasilmasi
                                        // amaciyla tutuluyor

        int i,j=10;

    if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");


        }
    }


    rewind(sporcuDos);

    for(i=1;i<MAX_KAYIT;i++){

        fread(&bir_sporcu,sizeof(sporcu),1,sporcuDos);

        if(bir_sporcu.lisansNo!=0){

            sayac[i][0]=bir_sporcu.ukdPuani;
            sayac[i][1]=bir_sporcu.lisansNo;
        }

    }
        siralama1(sayac,MAX_KAYIT);


        printf("Lisans No  Tc kimlik no        Ad soyad             Il plaka       Ukd\n");
        printf("--------   --------------      ----------------     --------       ----");

        for(i=0;i<10;i++){

            bir_sporcu=oyuncuOku(sayac[i][1],sporcuDos);


            if(sayac[i][1]!=0){

                    printf("\n%6d %16s %17s %12d %14d\n"
                    ,bir_sporcu.lisansNo,bir_sporcu.tcKimlik,bir_sporcu.adSoyad,bir_sporcu.plaka,bir_sporcu.ukdPuani);

                    while(sayac[i][0]==sayac[j][0]){
                    bir_sporcu=oyuncuOku(sayac[j][1],sporcuDos);


                    printf("\n%6d %16s %17s %12d %14d\n"
                    ,bir_sporcu.lisansNo,bir_sporcu.tcKimlik,bir_sporcu.adSoyad,bir_sporcu.plaka,bir_sporcu.ukdPuani);

                     j++;

                    }
            }

        }
    fclose(sporcuDos);
}
void birTurnuvaBilgi(){ //Turnuva no alinarak o turnuvaya iliskin bilgiler listelenir

        FILE *sporcuDos;
        FILE *macDos;
        FILE *turnuvaDos;

        turnuva bir_turnuva;
        mac bir_mac;
        sporcu beyaz_sporcu;
        sporcu siyah_sporcu;
        int turnuvaNo,gecici_beyaz,gecici_siyah;
        float sonucBeyaz=0,sonucSiyah=0;

         if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            dosya_yarat();
            if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
                printf("dosyasi acilamadi.\n");
                }
            }

        if((turnuvaDos=fopen("turnuvalar.dat","rb+"))==NULL) {
            turnuvaDos=fopen("turnuvalar.dat","wb");
            if((turnuvaDos=fopen("turnuvalar.dat","rb+"))==NULL) {
                printf("dosyasi acilamadi.\n");
                }
            }
        if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
            macDos=fopen("tum_maclar.txt","w");
            if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
                printf("dosyasi acilamadi.\n");

                }
            }


        printf("\nGormek istediginiz turnuvanin no'sunu giriniz:");
        scanf("%d",&turnuvaNo);

        bir_turnuva=turnuvaOku(turnuvaNo,turnuvaDos);

        if(bir_turnuva.turnuvaNo==turnuvaNo){

        printf("\nTurnuva No Turnuva Adi   Tarih          Sehir");
        printf("\n---------- ----------- ---------        ------");

        printf("\n%d %15s %20s %8s\n"
               ,bir_turnuva.turnuvaNo,bir_turnuva.turnuvaAdi,bir_turnuva.tarih,bir_turnuva.sehir);

        rewind(macDos);

        fscanf(macDos,"%d %d %d %d %d %f %f"
               ,&bir_mac.turnuvaNo,&bir_mac.turNO,&bir_mac.bLisans,&bir_mac.sLisans,&bir_mac.sonuc
               ,&bir_mac.bUkd,&bir_mac.sUkd);

        rewind(sporcuDos);

        while(!feof(macDos)){

            if(bir_mac.turnuvaNo==turnuvaNo){

                if(bir_mac.sonuc==1){sonucBeyaz=1;sonucSiyah=0;}
                    else if(bir_mac.sonuc==2){sonucSiyah=1;sonucBeyaz=0;}
                    else if(bir_mac.sonuc==0){sonucBeyaz=0.5;sonucSiyah=0.5;}

                gecici_beyaz=bir_mac.bLisans;
                gecici_siyah=bir_mac.sLisans;

                beyaz_sporcu=oyuncuOku(gecici_beyaz,sporcuDos);

                siyah_sporcu=oyuncuOku(bir_mac.sLisans,sporcuDos);

                printf("\n\tBeyaz Oynayanlar \t\t\tSiyah Oynayanlar");
                printf("\nTur No  Ad soyad       Ukd   Mac Puani - Mac puani  Ad soy ad      Ukd");
                printf("\n-----  -----------     ----  --------    --------   -----------    -----");
                printf("\n%d %16s %8d   %.2f     -   %.2f %15s %7d\n"
                       ,bir_mac.turNO,beyaz_sporcu.adSoyad,beyaz_sporcu.ukdPuani
                       ,sonucBeyaz,sonucSiyah,siyah_sporcu.adSoyad,siyah_sporcu.ukdPuani);

            }


            fscanf(macDos,"%d %d %d %d %d %f %f"
               ,&bir_mac.turnuvaNo,&bir_mac.turNO,&bir_mac.bLisans,&bir_mac.sLisans,&bir_mac.sonuc
               ,&bir_mac.bUkd,&bir_mac.sUkd);
            }
        }
        else printf("\n Girilen turnuvasina ait bilgiler yoktur.\n");

    fclose(turnuvaDos);
    fclose(macDos);
    fclose(sporcuDos);

}
void birOyuncuBilgiVeTurnuva(){ //lisans no alinarak oyuncu bilgileri ve katildigi turnuvalarda oynadigi maclar listelenir

    FILE *sporcuDos;
    FILE *turnuvaDos;
    FILE *macDos;
    sporcu bir_sporcu;
    turnuva bir_turnuva;
    mac bir_mac;
    sporcu iki_sporcu;
    int lisansNo,i;
    float toplamPuan=0,sonuc=0;
    float ukdDegisimi=0;

     if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
        dosya_yarat();
        if((sporcuDos=fopen("sporcular.dat","rb+"))==NULL) {
            printf("dosyasi acilamadi.\n");
        }
    }
    if((turnuvaDos=fopen("turnuvalar.dat","r+"))==NULL) {
        turnuvaDos=fopen("turnuvalar.dat","w");
        if((turnuvaDos=fopen("turnuvalar.dat","r+"))==NULL) {
            printf("dosyasi acilamadi.\n");

        }
    }
    if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
        macDos=fopen("tum_maclar.txt","w");
        if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
            printf("dosyasi acilamadi.\n");

        }
    }

    printf("\nGormek istediginiz oyuncunun lisans numarasini giriniz:");
    lisansNo=sayiAl(1000,9999);

    bir_sporcu=oyuncuOku(lisansNo,sporcuDos);

    if(bir_sporcu.lisansNo!=BOS_KAYIT){ //Bos kayit degilse

        printf("Lisans No  Tc kimlik no        Ad soyad             Il plaka       Ukd\n");
        printf("--------   --------------      ----------------     --------       ----");
        printf("\n%6d %17s %17s %13d %14d\n"
                    ,bir_sporcu.lisansNo,bir_sporcu.tcKimlik,bir_sporcu.adSoyad,bir_sporcu.plaka,bir_sporcu.ukdPuani);

        printf("\nKatildigi turnuvalar ve maclar :..\n");

        rewind(macDos);


        while(!feof(macDos)){

             fscanf(macDos,"%d %d %d %d %d %f %f"
                   ,&bir_mac.turnuvaNo,&bir_mac.turNO
                   ,&bir_mac.bLisans,&bir_mac.sLisans,&bir_mac.sonuc
                   ,&bir_mac.bUkd,&bir_mac.sUkd);

           /* bir_turnuva=turnuvaOku(bir_mac.turnuvaNo,turnuvaDos);*/

           fseek(turnuvaDos,(bir_mac.turnuvaNo-1)*sizeof(turnuva),SEEK_SET);
           fread(&bir_turnuva,sizeof(turnuva),1,turnuvaDos);

            if(bir_mac.bLisans == lisansNo || bir_mac.sLisans == lisansNo){


            printf("\nTurnuva adi,Tarihi, ve Sehri: %s - %s - %s\n",bir_turnuva.turnuvaAdi,bir_turnuva.tarih,bir_turnuva.sehir);
            printf("\nTur No   Rakip Ad Soyad  Rakip UKD  Mac Puani UKD degisim\n ");
            printf("------   --------------  --------   --------  -----------\n");

            while(bir_mac.turnuvaNo==bir_turnuva.turnuvaNo){

                    if(bir_mac.sonuc==1)sonuc=1;
                    else if(bir_mac.sonuc==2)sonuc=0;
                    else if(bir_mac.sonuc==0)sonuc=0.5;

                    toplamPuan+=sonuc;

                if(bir_sporcu.lisansNo==bir_mac.bLisans){

                    iki_sporcu=oyuncuOku(bir_mac.sLisans,sporcuDos);

                    /*fseek(sporcuDos,(bir_mac.slisans-1)*sizeof(sporcu),SEEK_Set*/

                    printf("%2d %20s %8d %10.2f %10.2f\n"
                           ,bir_mac.turNO,iki_sporcu.adSoyad,iki_sporcu.ukdPuani,sonuc,bir_mac.bUkd);
                    ukdDegisimi+=bir_mac.bUkd;


                }
                else if(bir_sporcu.lisansNo==bir_mac.sLisans){

                    iki_sporcu=oyuncuOku(bir_mac.bLisans,sporcuDos);

                    printf("%2d %20s %8d %10.2f %10.2f\n"
                           ,bir_mac.turNO,iki_sporcu.adSoyad,iki_sporcu.ukdPuani,sonuc,bir_mac.sUkd);

                    ukdDegisimi+=bir_mac.sUkd;


                    }


                    fscanf(macDos,"%d %d %d %d %d %f %f"
                   ,&bir_mac.turnuvaNo,&bir_mac.turNO
                   ,&bir_mac.bLisans,&bir_mac.sLisans,&bir_mac.sonuc
                   ,&bir_mac.bUkd,&bir_mac.sUkd);



                }





                    }

                        printf("\nToplam Mac Puani Degisimi: %.2f",toplamPuan);
                        printf("\nToplam UKD Degisimi: %.2f",ukdDegisimi);


                                sonuc=0;
                                toplamPuan=0;
                                ukdDegisimi=0;

                }

        }else printf("\nOyuncu Bulunamadi\n");


    fclose(sporcuDos);
    fclose(turnuvaDos);
    fclose(macDos);
    }
int sayiAl(int altSinir,int ustSinir){ //Kontrol islemi yapilmasini saglar

    int sayi;

    scanf("%d",&sayi);

    while(sayi<altSinir || sayi>ustSinir){

        printf("\nTekrar giriniz:");
        scanf("%d",&sayi);

    }
    return sayi;
}
void siralama(int v1[][2],int i){ //Kucukten buyuge siralama islemi yapiliyor

    int gecis_say=0,yer_degisti,b;

 do{
        gecis_say++;
        yer_degisti=0;
        for(b=0;b<i-gecis_say;b++){

            if(v1[b][1]>v1[b+1][1] ) {

                    yerDegistirme(&v1[b][0],&v1[b+1][0]);
                    yerDegistirme(&v1[b][1],&v1[b+1][1]);

                    yer_degisti=1;
            }

        }
    }while(yer_degisti==1);
}
void siralama1(int v1[][2],int i){ //Buyukten kucuge siralama islemi yapiliyor

    int gecis_say=0,yer_degisti,b;

 do{
        gecis_say++;
        yer_degisti=0;
        for(b=0;b<i-gecis_say;b++){

            if(v1[b][0]<v1[b+1][0] ) {

                    yerDegistirme(&v1[b][0],&v1[b+1][0]);
                    yerDegistirme(&v1[b][1],&v1[b+1][1]);

                    yer_degisti=1;
            }

        }
    }while(yer_degisti==1);
}
void yerDegistirme(int *sayi, int *sayi2){ //siralama fonksiyonlarinda yer degistirmeyi saglar

            int tut;

            tut=*sayi;
            *sayi=*sayi2;
            *sayi2=tut;
}
void beyazSiyahComp(){ //Beyaz ve Siyah oyuncularin UKD degisimlerinin ve mac puanlarýnýn karsilastirilmasi yapiliyor

    mac bir_mac;
    FILE *macDos;
    float beyazPuan=0;
    float siyahPuan=0;
    float beyazUkd=0;
    float siyahUkd=0;

    if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
            macDos=fopen("tum_maclar.txt","w");
            if((macDos=fopen("tum_maclar.txt","r+"))==NULL) {
                printf("dosyasi acilamadi.\n");

                }
            }


    printf("                      Beyaz Oynayanlar      Siyah Oynayanlar\n");
    printf("                      ----------------      ----------------\n");

    fscanf(macDos,"%d %d %d %d %d %f %f"
           ,&bir_mac.turnuvaNo,&bir_mac.turNO,&bir_mac.bLisans,&bir_mac.bLisans,&bir_mac.sonuc,&bir_mac.bUkd,&bir_mac.sUkd);

    while(!feof(macDos)){ //Mac dosyasinin sonuna kadar beyaz ve siyah oyuncularin mac puanlari hesaplaniyor

        if(bir_mac.sonuc==1)
            beyazPuan+=1;
        else if(bir_mac.sonuc==2)
            siyahPuan+=1;
        else if(bir_mac.sonuc==0){
            beyazPuan+=0.5;
            siyahPuan+=0.5;
        }
        beyazUkd+=bir_mac.bUkd;
        siyahUkd+=bir_mac.sUkd;

        fscanf(macDos,"%d %d %d %d %d %f %f"
               ,&bir_mac.turnuvaNo,&bir_mac.turNO,&bir_mac.bLisans,&bir_mac.bLisans,&bir_mac.sonuc,&bir_mac.bUkd,&bir_mac.sUkd);

    }

    printf("Toplam Mac Puani:%11.2f %25.2f",beyazPuan,siyahPuan);
    printf("\nToplam UKD Degisimi:%8.2f %25.2f",beyazUkd,siyahUkd);

}
int macPuani(int sonuc){     //Galibiyet için 1,beraberlik icin 0.5 puan döndürülerek maç puan hesabi yapiliyor

    switch(sonuc){

        case 1: return 1; break;
        case 2: return 1; break;
        case 0: return 0.5; break;

    }

}
