#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
double tsure=0,oky=0;
struct ogrList1{
    char ogrNum[15];
    char ad[30];
    char soyad[30];
    char ogrSira[15];
    char ogrTuru[2];
};

struct ogrList2{
    int ogrNum;
    char ad[50];
    char soyad[50];
    int ogrSira;
    int ogrTuru;
};

void degistir(){
    clock_t basla;
    basla=clock();
    struct ogrList1 liste[500];
    FILE *dosyaOku,*dosyaYaz;
    dosyaOku = fopen("ornek_ogrenci_kayit_bilgileri.txt","r+");
    dosyaYaz = fopen("tekrarsizKayitlar.txt","w");

    int sayac=0;
    while(!feof(dosyaOku)){
        fscanf(dosyaOku,"%s %s %s %s %s",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        sayac++;
    }
    /**Listeyi integer degerlikleri olanlar icin revize etme**/

    int i;
    if (oky==0){
    for(i=1; i<sayac-1; i++){
        if(strcmp(liste[i].ogrTuru,"I")==0){
            strcpy(liste[i].ogrTuru,"1");
            if(strcmp(liste[i].ogrNum,"-")==0){
                strcpy(liste[i].ogrNum,"0");}}
        else{
            strcpy(liste[i].ogrTuru,"2");
            if(strcmp(liste[i].ogrNum,"-")==0){
                strcpy(liste[i].ogrNum,"0");
            }
        }
    } }
    printf("Tekrar eden kayitlar\n");
    /**tekrar eden kayýtlarý silme**/
    fscanf(dosyaOku,"%d %s %s %d %d",liste[1].ogrNum,liste[1].ad,liste[1].soyad,liste[1].ogrSira,liste[1].ogrTuru);
    for(i=1; i<sayac-1; i++){
        if((strcmp(liste[i-1].ad,liste[i].ad)==0) && (strcmp(liste[i-1].soyad,liste[i].soyad)==0 )){
            printf("%15s %15s %10s\n",liste[i].ad,liste[i].soyad,liste[i].ogrTuru);}
        else{
            fprintf(dosyaYaz,"%10s %15s %15s %10s %10s\n",liste[i].ogrNum,liste[i].ad,liste[i].soyad,liste[i].ogrSira,liste[i].ogrTuru);
        }
    }printf("2 den fazla tekrar eden kayit yoktur!\n");
    fclose(dosyaOku);
    fclose(dosyaYaz);

    clock_t bitir;
    bitir=clock();
    double sure = (double)(bitir - basla)/CLOCKS_PER_SEC ;
    printf("Degistir Fonk Suresi %.3f saniye",sure);
    tsure+=sure;
}

void NumaraAta(){
    clock_t basla;
    basla=clock();
    struct ogrList2 liste[500];
    FILE *dosyaOku,*birinciOgr,*ikinciOgr;
    dosyaOku = fopen("tekrarsizKayitlar.txt","r+");
    birinciOgr= fopen("birinciOgretim.txt","w");
    ikinciOgr = fopen("ikinciOgretim.txt","w");

    int sayac=0;
    while(!feof(dosyaOku)){
        fscanf(dosyaOku,"%d %s %s %d %d",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        sayac++;}
    /**Numaralylary syralama**/
    int i,j;
    int tNum;
    char tAd[30];
    char tSoyad[30];
    int tSira;
    int tTur;

    for(i=0; i<sayac-1; i++){
        for(j=i+1; j<sayac-1; j++){
            if(liste[i].ogrNum!=0){
                if(liste[i].ogrNum<=liste[j].ogrNum){
                    tNum=liste[i].ogrNum;
                    strcpy(tAd,liste[i].ad);
                    strcpy(tSoyad,liste[i].soyad);
                    tSira=liste[i].ogrSira;
                    tTur=liste[i].ogrTuru;
                    liste[i].ogrNum=liste[j].ogrNum;
                    strcpy(liste[i].ad,liste[j].ad);
                    strcpy(liste[i].soyad,liste[j].soyad);
                    liste[i].ogrSira=liste[j].ogrSira;
                    liste[i].ogrTuru=liste[j].ogrTuru;
                    liste[j].ogrNum=tNum;
                    strcpy(liste[j].ad,tAd);
                    strcpy(liste[j].soyad,tSoyad);
                    liste[j].ogrSira=tSira;
                    liste[j].ogrTuru=tTur;
                }
            }
        }
    }
    /**Tum listeyi syra numarasyna gore syralama**/
    for(i=0; i<sayac-1; i++){
        for(j=i+1; j<sayac-1; j++){
            if(liste[i].ogrSira>=liste[j].ogrSira){
                tNum=liste[i].ogrNum;
                strcpy(tAd,liste[i].ad);
                strcpy(tSoyad,liste[i].soyad);
                tSira=liste[i].ogrSira;
                tTur=liste[i].ogrTuru;
                liste[i].ogrNum=liste[j].ogrNum;
                strcpy(liste[i].ad,liste[j].ad);
                strcpy(liste[i].soyad,liste[j].soyad);
                liste[i].ogrSira=liste[j].ogrSira;
                liste[i].ogrTuru=liste[j].ogrTuru;
                liste[j].ogrNum=tNum;
                strcpy(liste[j].ad,tAd);
                strcpy(liste[j].soyad,tSoyad);
                liste[j].ogrSira=tSira;
                liste[j].ogrTuru=tTur;
            }
        }
    }
    /**Numara Atama**/
    int t=1;
    for(i=0; i<sayac-1; i++){
        if(liste[i].ogrNum==0){
            if(liste[i].ogrTuru==1){
                liste[i].ogrNum= 1701000 + liste[i].ogrSira;}
            else{
                liste[i].ogrNum=1702000+t;
                t++;}
        }
    }
    /**tum kayitlari birinci ogretim ve ikinci ogretime ayyrma**/
    for(i=0; i<sayac-1; i++){
        if(liste[i].ogrTuru==1){
            fprintf(birinciOgr,"%10d %15s %15s %10d %10d\n",liste[i].ogrNum,liste[i].ad,liste[i].soyad,liste[i].ogrSira,liste[i].ogrTuru);
        }
        else{
            fprintf(ikinciOgr,"%10d %15s %15s %10d %10d\n",liste[i].ogrNum,liste[i].ad,liste[i].soyad,liste[i].ogrSira,liste[i].ogrTuru);
        }
    } printf("\nKayit siralari guncellenmistir.\n");

    clock_t bitir;
    bitir=clock();
    double sure = (double)(bitir - basla)/CLOCKS_PER_SEC ;

    printf("NumaraAta Fonk Suresi %.3f saniye",sure);
    tsure+=sure;
    fclose(dosyaOku);
    fclose(birinciOgr);
    fclose(ikinciOgr);
}

void dagilim(){

    clock_t basla;
    basla=clock();

    struct ogrList2 liste[500];
    FILE *dosyaOku,*birinciOgr,*ikinciOgr,*sinif,*der;
    birinciOgr= fopen("birinciOgretim.txt","r+");
    ikinciOgr = fopen("ikinciOgretim.txt","r+");
    der=fopen("tekrarsizKayitlar.txt","r+");
    int sayac=0,sayac2=0,sayac3=0;
    while(!feof(birinciOgr)){
        fscanf(birinciOgr,"%d %s %s %d %d",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        sayac++;}
     while(!feof(der)){
        fscanf(der,"%d %s %s %d %d",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        sayac3++;}
    int ssay; hata2:
    printf("\nSinif sayisini girin: ");
    scanf("%d",&ssay);
    int kap[ssay],skap=0,i=0,gecici=0,j=0,bsayi=0;
    printf("\nBir Ogr = %d  Ikinci Ogr = %d \n",sayac,sayac3-sayac);
    if (sayac >= sayac3-sayac) {
        printf("Sinif Kapasite Toplami %d'den Kucuk Olamaz.!\n",sayac); bsayi=sayac;}
    else {
        printf("Sinif Kapasite Toplami %d'den Kucuk Olamaz.!\n",sayac3-sayac);bsayi=sayac3-sayac;}

    for(i=0; i<ssay; i++){
        printf("%d. Sinif Kapasitesini Giriniz : ",i+1);
        scanf("%d",&kap[i]);
        skap+=kap[i];}
    printf("%d",i);
    if ( bsayi > skap ){
            char sin;
        printf(" Sinif Yetersiz! --->> Yeni Sinif Eklemek Ister Misiniz ? [E - H] : ");
        scanf("%s",&sin);
        if (sin == 'E' || sin == 'e'){
            int mevcut = bsayi-skap;
            kap[i+1]=mevcut;
            printf("%d. Sinif Kapasitesi = %d \n",i+1,kap[i+1]);
            skap +=mevcut;
        }
        else goto hata2;
    }
    /**Dizi kucukten buyuge syralanyr**/
    for(i=0; i<ssay-1; i++){
        for(j=i+1; j<ssay; j++){
            if(kap[i] > kap[j]){
                gecici = kap[i]; // Dizi[i] yi kaybetmemek için gecicide tutuyoruz
                kap[i] = kap[j]; //dizi[i] yi dizi[i] den daha küçük olan dizi[j] kaydediyoruz
                kap[j] = gecici; // Dizi[j] ye ise dizi[i] de?erini kaydediyoruz. Bu de?eri gecicide saklamy?tyk
            }
        }
    }
    int sec=0; hata3:
    printf("Esit Dagilim icin [1] - En Az Dagilim icin [2]' ye basiniz : ");
    scanf("%d",&sec);
    int edd[ssay];
    int k,ort=0,kalan=0;
    sayac-=1;// dosyadan 1 tane kayyt fazla dondugu ycyn
    kalan=sayac;
    FILE *atama[ssay*2];
    char dizi[20];
    int xd=1;
    for (i=1; i<=ssay; i++){
        sprintf(dizi,"%s%d%s%c","sinif",i,"ogr1.txt",'\0'); atama[2*i-2]=fopen(dizi,"w");
        sprintf(dizi,"%s%d%s%c","sinif",i,"ogr2.txt",'\0'); atama[2*i-1]=fopen(dizi,"w");}

    if (sec == 1 && skap >= sayac && skap >= sayac3-sayac ){ /** Eþit Dagilim **/
    for(i=0; i<ssay; i++){
        ort=kalan/(ssay-i);
        if(ort>kap[i]){
            edd[i]=kap[i];
            kalan=sayac-kap[i];
        }
        else{
        kap[i]=ort;}}
    printf("Birinci ogretim ve Ikinci ogretim esit dagilim BASARILI ! \n \n");
    printf("\n");
    int x=0;
    for (i=1; i<=ssay; i++){
            x++;
        for (xd=1; xd<=kap[i-1]; xd++){
            fscanf(birinciOgr,"%d %s %s %d %d \n",&liste[x].ogrNum,&liste[x].ad,&liste[x].soyad,&liste[x].ogrSira,&liste[x].ogrTuru);
            fprintf(atama[2*i-2],"%d %s %s %d %d \n",liste[x].ogrNum,liste[x].ad,liste[x].soyad,liste[x].ogrSira,liste[x].ogrTuru);
            x++;
            if (x==sayac) xd=kap[i-1]+2;}
        }
        git:
     while(!feof(ikinciOgr)){
        fscanf(ikinciOgr,"%d %s %s %d %d",&liste[sayac2].ogrNum,&liste[sayac2].ad,&liste[sayac2].soyad,&liste[sayac2].ogrSira,&liste[sayac2].ogrTuru);
        sayac2++;}printf("\n");
        x=0;
        for (i=1; i<=ssay; i++){
            x++;
        for (xd=1; xd<=kap[i-1]; xd++){
            fscanf(ikinciOgr,"%d %s %s %d %d \n",&liste[x].ogrNum,&liste[x].ad,&liste[x].soyad,&liste[x].ogrSira,&liste[x].ogrTuru);
            fprintf(atama[2*i-1],"%d %s %s %d %d \n",liste[x].ogrNum,liste[x].ad,liste[x].soyad,liste[x].ogrSira,liste[x].ogrTuru);
            x++;
            if (x==sayac2) xd=kap[i-1]+2;}
        }
    }
      /** En Az Dagilim **/
    else if (sec == 2 && skap >= sayac && skap >= sayac3-sayac){
        int y=1,u=1;
        for(i=1; i<=ssay; i++){
            u++; if(u >= sayac) break;
            for (y=1; y<=kap[ssay-1]; y++){
                fscanf(birinciOgr,"%d %s %s %d %d \n",&liste[u].ogrNum,&liste[u].ad,&liste[u].soyad,&liste[u].ogrSira,&liste[u].ogrTuru);
                fprintf(atama[2*i-2],"%d %s %s %d %d \n",liste[u].ogrNum,liste[u].ad,liste[u].soyad,liste[u].ogrSira,liste[u].ogrTuru);
                u++;
                if (u == sayac) y=kap[i-1]+u;
            }
        }
        while(!feof(ikinciOgr)){
        fscanf(ikinciOgr,"%d %s %s %d %d",&liste[sayac2].ogrNum,&liste[sayac2].ad,&liste[sayac2].soyad,&liste[sayac2].ogrSira,&liste[sayac2].ogrTuru);
        sayac2++;}

        u=0;
        for(i=1; i<=ssay; i++){
            u++;    if(u >= sayac2) break;
            for (y=1; y<=kap[ssay-1]; y++){
                fscanf(ikinciOgr,"%d %s %s %d %d \n",&liste[u].ogrNum,&liste[u].ad,&liste[u].soyad,&liste[u].ogrSira,&liste[u].ogrTuru);
                fprintf(atama[2*i-1],"%d %s %s %d %d \n",liste[u].ogrNum,liste[u].ad,liste[u].soyad,liste[u].ogrSira,liste[u].ogrTuru);
                u++;
                if (u==sayac2) y=kap[i-1]+u;}
        } printf("Birinci ogretim ve Ikinci ogretim esit dagilim BASARILI ! \n \n");
    }
    else {printf("Hatali Secim! \n \n"); goto hata3;}
    fclose(birinciOgr);
    fclose(ikinciOgr);
    clock_t bitir;
    bitir=clock();
    double sure = (double)(bitir - basla)/CLOCKS_PER_SEC ;
    printf("Dagilim Fonk Suresi %.3f saniye ",sure);
    tsure+=sure;
}

void kayitEkle(){
    clock_t basla;
    basla=clock();
    struct ogrList2 liste[500];
    FILE *dosyaOku,*dosyaYaz,*gercek,*dosyaBir,*dosyaIki;
    gercek = fopen("ornek_ogrenci_kayit_bilgileri.txt","r+");
    dosyaOku = fopen("tekrarsizKayitlar.txt","r+");
    dosyaBir = fopen("birinciOgretim.txt","r+");
    dosyaIki = fopen("ikinciOgretim.txt","r+");

    int sayac=0,sayac2=0,sayac3=0,sayac4=0;
     while(!feof(dosyaOku)){
        fscanf(dosyaOku,"%s %s %s %s %s",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        sayac++;}
      while(!feof(gercek)){
        fscanf(gercek,"%s %s %s %s %s",&liste[sayac4].ogrNum,&liste[sayac4].ad,&liste[sayac4].soyad,&liste[sayac4].ogrSira,&liste[sayac4].ogrTuru);
        sayac4++;}
     while(!feof(dosyaBir)){
        fscanf(dosyaBir,"%d %s %s %d %d",&liste[sayac2].ogrNum,&liste[sayac2].ad,&liste[sayac2].soyad,&liste[sayac2].ogrSira,&liste[sayac2].ogrTuru);
        sayac2++;}
    while(!feof(dosyaIki)){
        fscanf(dosyaIki,"%d %s %s %d %d",&liste[sayac3].ogrNum,&liste[sayac3].ad,&liste[sayac3].soyad,&liste[sayac3].ogrSira,&liste[sayac3].ogrTuru);
        sayac3++; }

    sayac2=sayac2-2;
    sayac3=sayac3-2;
    char secim;  int tur;
    printf("\n \n Yeni kayit eklemek ister misiniz ? [E / H] : ");
    scanf("%s",&secim);
        sayac=sayac+1;
    if (secim == 'E' || secim == 'e'){
        hata1:
        printf("Ogrenci Numarasi Giriniz : (7 Haneli): ");
        scanf("%d",&liste[sayac].ogrNum);
        if (liste[sayac].ogrNum >= 1001001 && liste[sayac].ogrNum <= 9999999 ){
            tur = (liste[sayac].ogrNum/1000)%10;
            liste[sayac].ogrTuru=tur;
                if(tur == 0 || tur>=3) {printf("HATA! OGRENIM TURU '1' - '2' OLABILIR. GIRILEN DEGER: %d \n",tur); goto hata1; }
        fflush(stdin);
        printf("Ogrenci Adini Giriniz : ");
        scanf("%s",&liste[sayac].ad);
        fflush(stdin);
        printf("Ogrenci Soyadini Giriniz : ");
        scanf("%s",&liste[sayac].soyad);
        printf("Ogrenci Ogrenim Turunuz : %d \n",tur);
        int sira = liste[sayac].ogrNum %1000;
        liste[sayac].ogrSira=sira;
        printf("Ogrenci Siraniz : %d \n",sira);
        printf("\nKayit Basariyla Eklendi...\n");
        //fprintf(dosyaOku,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,liste[sayac].ogrSira,liste[sayac].ogrTuru);
        }

        else {
                int turu;
                printf("Ogrenci Adini Giriniz : ");
                scanf("%s",&liste[sayac].ad);
                fflush(stdin);
                printf("Ogrenci Soyadini Giriniz : ");
                scanf("%s",&liste[sayac].soyad); hata:
                printf("Ogrenim turunu giriniz : ");
                scanf("%d",&turu);
                if(turu == 0 || turu>=3) {printf("HATA! OGRENIM TURU '1' - '2' OLABILIR. GIRILEN DEGER: %d \n",turu); goto hata;}
                printf("\nKayit Basariyla Eklendi...\n");

                if (turu == 1){
                int abc = liste[sayac2].ogrSira+1;
                liste[sayac].ogrNum= 1701001 + liste[sayac2].ogrSira;
                printf("%d ",liste[sayac].ogrNum );
                fscanf(dosyaBir,"%d",&liste[sayac].ogrNum);

               fprintf(dosyaBir,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,abc,turu);
               fprintf(dosyaOku,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,abc,turu);
                }

                else{ /**TURU==2**/

                    int abcd = liste[sayac3].ogrSira+1; //391
                    liste[sayac].ogrNum= 1702000 + liste[sayac3].ogrSira;
                    printf("%d ",liste[sayac].ogrNum );
                    fscanf(dosyaIki,"%d",&liste[sayac].ogrNum);
                    fprintf(dosyaIki,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,abcd,turu);
                    fprintf(dosyaOku,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,abcd,turu);

                    }
                }
            }

        if (tur==1){

           int i=0, dk=0;
            int qwer=sayac2+1;
            for (i=0; i<=sayac2; i++)
            {
                qwer--;
                if(liste[sayac].ogrNum == liste[qwer].ogrNum)
                {
                    dk++;
                    liste[sayac].ogrNum= 1701001 + liste[sayac2].ogrSira;
                    printf("%d ",liste[sayac].ogrNum );
                    fscanf(dosyaBir,"%d",&liste[sayac].ogrNum);
                    fprintf(dosyaBir,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,qwer,tur);
                    fprintf(dosyaOku,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,qwer,tur);
                    fprintf(gercek,"\n%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,qwer,tur);
                }
            }

        if (dk==0){
        fscanf(dosyaBir,"%10d %15s %15s %10d %10d",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        fprintf(dosyaBir,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,liste[sayac].ogrSira,liste[sayac].ogrTuru);
        fprintf(gercek,"\n%d %s %s %d %d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,liste[sayac].ogrSira,liste[sayac].ogrTuru);
        fscanf(gercek,"%d %s %s %d %d",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
        degistir();
        NumaraAta();
        oky++;}
        }
       else if (tur == 2){

                int i=0,dk=0;
                int qwer=sayac3+1;
                for (i=0; i<=sayac3; i++){
                    qwer--;
                    if (liste[sayac].ogrNum == liste[qwer].ogrNum){
                        dk++;
                        liste[sayac].ogrNum= 1702000 + liste[sayac2].ogrSira;
                        printf("%d ",liste[sayac].ogrNum );
                        fscanf(dosyaIki,"%d",&liste[sayac].ogrNum);
                        fprintf(dosyaIki,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,qwer,tur);
                        fprintf(dosyaOku,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,qwer,tur);
                        fprintf(gercek,"\n%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,qwer,tur);
                    }  }
        if (dk==0){
        fprintf(dosyaIki,"%10d %15s %15s %10d %10d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,liste[sayac].ogrSira,liste[sayac].ogrTuru);
        fprintf(gercek,"\n%d %s %s %d %d",liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,liste[sayac].ogrSira,liste[sayac].ogrTuru);
        fscanf(gercek,"%d %s %s %d %d",&liste[sayac].ogrNum,&liste[sayac].ad,&liste[sayac].soyad,&liste[sayac].ogrSira,&liste[sayac].ogrTuru);
                degistir();
                NumaraAta();
                oky++;
                }
            }
        clock_t bitir;
        bitir=clock();
        double sure = (double)(bitir - basla)/CLOCKS_PER_SEC ;
        printf("Dagilim Fonk Suresi %.3f saniye ",sure);
        tsure+=sure;

}

int main(){
    degistir();
    NumaraAta();
    dagilim();
    kayitEkle();
    printf("\nToplam Calisma Suresi : %.3f",tsure);
    return 0;
}
