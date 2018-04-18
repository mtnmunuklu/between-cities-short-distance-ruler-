#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
char sehir[81][81];
int **GRAF;
int kodu[81];
int dosyaSatir=0;//sehirkod.txt dosyasýndaki satýrsayisini tutar
int dosyaSatir2=0;
char ekygecilendugumler[81][81];
char  *ziyaretEdilenler;
class Dosyalama{
public:
void dosyaAcSehirKod(char name[20])
{
    char adi[81];
    FILE *dosya;
    char *pch;
    int sayac=0;
    if((dosya=fopen(name,"r"))== NULL)
    {
        puts("Dosyasi acilmadi. !\n");
        puts("Dosya ismini kontrol ediniz.!\n");
    }
    else
    {
        while(fscanf(dosya,"%s",adi)!=EOF)
        {

            if(dosyaSatir>=1)
            {
                pch=strtok(adi,"-");
                while(pch!=NULL)
                {
                    if(sayac%2==0)
                    {
                        //  printf ("%s\n",pch);
                        strcpy(sehir[dosyaSatir-1],pch);
                    }
                    else
                    {
                        //  printf("%d\n",atoi(pch));
                        kodu[dosyaSatir-1]=atoi(pch);
                    }
                    sayac++;
                    pch = strtok (NULL, "-");
                }
            }
            dosyaSatir++;
        }
        dosyaSatir--;
    }
    fclose(dosya);
}
void dosyaACSehirMesafe(char name2[20])
{
    char adi2[81];
    FILE *dosya2;
    char *pch2;
    int tut;
    if((dosya2=fopen(name2,"r"))== NULL)
    {
        puts("Dosyasi acilmadi. !\n");
        puts("Dosya ismini kontrol ediniz.!\n");
    }
    else
    {
        for(int i=0; i<dosyaSatir; i++)
        {
            dosyaSatir2=0;
            //  printf("%d.----------\n",i);
            while(fscanf(dosya2,"%s",adi2)!=EOF)
            {

                if(dosyaSatir2>=1)
                {
                    pch2=strtok(adi2,"-");
                    if(strcmp(pch2,sehir[i])==0)
                    {
                        // printf ("%s\n",pch2);
                        pch2=strtok(NULL,"-");
                        // printf ("%s\n",pch2);
                        for(int i=0; i<dosyaSatir; i++)
                        {
                            if(strcmp(sehir[i],pch2)==0)
                            {
                                tut=i;
                            }
                        }
                        pch2=strtok(NULL,"-");
                        GRAF[i][tut]=atoi(pch2);
                        // printf ("%d\n",atoi(pch2));
                    }
                }
                dosyaSatir2++;

            }
            fseek(dosya2,0,SEEK_SET);
        }
    }
    fclose(dosya2);
}

};
int dugum=0;
int *enkisayolmaliyet;
class EnKisaYol{
public:
void Dijkstra(int bas,int sorgu)
{
    char *tmp;
    int i, j, baslangic, enkucuk;
    //Butun dugmlere balangicta sonsýz atar
    int t=0;
    while(t<dosyaSatir)
    {
        enkisayolmaliyet[t] = 10000;
        t++;
    }
    //Butun dugumlere baslangýcta sonsuz atar

    baslangic = bas; //baslangicta secilen dugum
    enkisayolmaliyet[baslangic] = 0;//secilen dugum icin en kisa yol 0 olarak kabul edilir
   i=0;
    do{
        enkucuk = 10000;
        int j=0;
        do
        {
            int dugumMesafe=GRAF[baslangic][j];
            if (ziyaretEdilenler[j]!=0 && dugumMesafe> -1)//ziyaret edilenlerde deðil ve baslangic dugumu tarafindan ulasilamaz degilse
            {
                if (dugumMesafe + enkisayolmaliyet[baslangic]<enkisayolmaliyet[j]) //en kisa yol ,baslangic dugumu tarafindan ulasilabilen dugume ait maliyet ile  baslangic dugumune  ait maliyetten buyukse
                {

                    enkisayolmaliyet[j] = dugumMesafe + enkisayolmaliyet[baslangic];//en kisa yola maliyetinene baslangic dugumu tarafindan ulasilabilen dugume ait maliyet ile baslangic dugumune ait maliyeti ekle
                    strcpy(ekygecilendugumler[j], ekygecilendugumler[baslangic]);//eky gecilen dugumler dizisinin sonuna  baslangic dugumunu ekler
                    tmp = ekygecilendugumler[j];
                    while (*tmp != NULL)
                        ++tmp;                             //Dijkstra algoritması http://www.zafercomert.com/IcerikDetay.aspx?zcms=70
                    strcpy(tmp,sehir[baslangic]);          //sitesindeki kodlardan yararlanılarak yazıldı.
                    strcat(tmp,"-");
                }
            }
            j++;
        }
        while(j<dosyaSatir);
        // dugumlere ait en kisa yol maliyetleri listelenir
        if(sorgu==1){
        printf("%d.dugum   : ",dugum);
        for(int i=0; i<dosyaSatir; i++)
        {
            printf("%8d",enkisayolmaliyet[i]);
        }
        //dugumlere ait en kisa yol maliyetleri listelenir
        printf("\n");
        dugum++;
        }

        // ziyaret edilmemisler arasindan en kucugunu bulmamizi saðlar
        int say=0;
        do{
            if (ziyaretEdilenler[say]!= 0 && enkisayolmaliyet[say] < enkucuk) //dugum ziyaret edilenlerde deðilse
            {
                    enkucuk = enkisayolmaliyet[say];
                    baslangic = say; //balangic dugumu 1 arttýrýlýr
            }
         say++;
        }while(say<dosyaSatir);
        //ziyaret edilen dugumler belirlenir.
       ziyaretEdilenler[baslangic]=0;
        i++;
    }while(i<dosyaSatir);
}
};
int main()
{
    char name[20];
    char name2[20];
    int sorgu;
    int bas;
    int bitis;
    printf("Sehir ve Kodlarinin oldugu dosya ismini giriniz:");
    scanf("%s",name);
    class Dosyalama dosya;
    class EnKisaYol yol;
    dosya.dosyaAcSehirKod(name);
    //Dinamik Graf
    GRAF= (int**)malloc(dosyaSatir*sizeof(int));
    for(int i = 0; i <dosyaSatir; i++)
        GRAF[i] = (int*) malloc(dosyaSatir*sizeof(int));

    enkisayolmaliyet= (int*)malloc(dosyaSatir*sizeof(int));
    ziyaretEdilenler=(char *)malloc(dosyaSatir*sizeof(char));
    int a=0;
    do{
        ziyaretEdilenler[a]=-1;
        a++;
    }while(a<dosyaSatir);
    for(int i=0; i<dosyaSatir; i++)
    {
        for(int j=0; j<dosyaSatir; j++)
        {
            GRAF[i][j]=-1;
        }
    }
    printf("Shirler ve Mesafelerin oldugu dosya ismini giriniz:");
    scanf("%s",name2);
    dosya.dosyaACSehirMesafe(name2);
   // printf("\nKomsuluk Matrisi\n\n");

   int i=0;
    do
    {
        int j=0;
        do
        {
            printf("%5d", GRAF[i][j]);
            j++;
        }
        while(j<dosyaSatir);
        printf("\n\n\n");
        i++;
    }
    while(i<dosyaSatir);

    printf("   -----------Sehirler(Dugumler)---------------\n\n");
    for(int i=0; i<dosyaSatir; i++)
    {
        printf("\t%9s     :    %c  (%d.dugum)\n",sehir[i],'A'+i,i);
    }
    printf("\nBir sehirden diger sehirlere olan/iki sehir arasindaki  en kisa yol icin(1/0) giriniz:");scanf("%d",&sorgu);

    if(sorgu==1){
    printf("\nLutfen baslangic dugumunu giriniz(Sayi olarak):");
    scanf("%d",&bas);

    //hangi sutunun hangi koda ait olduðunu gosterir.
    printf("\nGraf Tablosu\n\n");
    printf("Dugumler   ");
    int sehirlerno=0;
    do
    {
        printf("%7c ",'A'+sehirlerno);
        sehirlerno++;
    }
    while(sehirlerno<dosyaSatir);
    printf("\n\n");


    yol.Dijkstra(bas,sorgu);

    printf("\n\n    -------------Sehirler Arasi Enkisa Yol-------------\n\n");
    printf("\tSehirler\tMaliyet\t\tEnkisa Yol\n");
    for (int i = 0; i < dosyaSatir; i++)
    {
        printf("\t%9s     :   %d\t",sehir[i],enkisayolmaliyet[i]);
        printf("\tyol : ");
        printf("%s\t",ekygecilendugumler[i]);
        printf("\n");
    }
    }
  else if(sorgu==0){
     printf("\nLutfen baslangic dugumunu giriniz(Sayi olarak):");
     scanf("%d",&bas);
     printf("\nLutfen bitis dugumunu giriniz(Sayi olarak):");
     scanf("%d",&bitis);

     yol.Dijkstra(bas,sorgu);
     printf("\n\n    -------------Sehirler Arasi Enkisa Yol-------------\n\n");
    printf("\tSehirler\tMaliyet\t\tEnkisa Yol\n");
     printf("\t%9s     :   %d\t",sehir[bitis],enkisayolmaliyet[bitis]);
        printf("\tYol : ");
        printf("%s\t",ekygecilendugumler[bitis]);
        printf("\n");
  }
  getch();
}


