//
//  main.c
//
// Zeynep Palabıyık


#define GL_SILENCE_DEPRECATION
#include <stdlib.h>
#include <curl/curl.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Zeynep Palabıyık
int windowWidth = 900;
int windowHeight = 8000;
int sekil1[50][2];
int sekil2[50][2];
int sekil3[50][2];

// Veriyi saklamak için bir karakter dizisi tanımlayın
char receivedData[10000]; // İhtiyaca göre boyutu ayarlayabilirsiniz
//boyutlar ve bellek adreslemesiyle ilgili işlemlerde kullanılmaktadır.
size_t veriisle(void *verip, size_t boyut, size_t byte, void *ekveri) {
    // HTTP istekleri sırasında gelen verileri işlemek için çağrılır.Bu işlev, veriyi alır ve receivedData karakter dizisine ekler
//    boyut: Her bir öğe (byte) boyutunu belirten bir tamsayı.
//byte: Alınan verinin öğe (byte) sayısını belirten bir tamsayı.
    size_t toplamboyut = boyut * byte;
    strncat(receivedData, (char *)verip,toplamboyut);
//   verip Alınan verinin bir işaretçisi (pointer). Bu, aldığınız verinin başlangıcıdır.
    return toplamboyut;
}

void kenarsayisi(int knrs[3])
{
    int yedek[100][2];
    int k = 0,a=0;
//    koordinat sayısı
    int kordinat = 0;
    char *p = receivedData;
    int satirs;
    printf("kacinci satir?");
    scanf("%d",&satirs);
    
//        koordinatları ayırma sayıları matrise aktarma
    if(satirs==1)
    {
        for (int i = 0; receivedData[i]; i++) {
            if (receivedData[i] == '(') {
                kordinat = 1;
//                koordinat 1 else iflein içine girmeyi sağlar.ife girmediyse else ife de giremez.
                p = &receivedData[i + 1];
            } else if (receivedData[i] == ',' && kordinat) {
                receivedData[i] = '\0';
                yedek[k][0] = atoi(p);
                p = &receivedData[i + 1];
            } else if (receivedData[i] == ')' && kordinat) {
                kordinat = 0;
                receivedData[i] = '\0';
                yedek[k][1] = atoi(p);
                k++;
//                toplam koordinat sayısı
            }
            if (receivedData[i] == '\n')
            {
                break;
            }
        }
    }
    else{
        int n=1;
            for (int i = 0; receivedData[i]; i++) {
                if (receivedData[i] == '\n')
                {
                    n++;
                    
                }
                if(n==satirs)
                {
                    
                    while (receivedData[i+1]!='\n') {
     
                        if (receivedData[i+1] == '(') {
                            kordinat = 1;

                            p = &receivedData[i + 2];
//                            iden sonrakinin adresini pye batar
                         
                        } else if (receivedData[i+1] == ',' && kordinat) {
                            receivedData[i+1] = '\0';
                            yedek[k][0] = atoi(p);
                           
                            p = &receivedData[i + 2];
                            
                        } else if (receivedData[i+1] == ')' && kordinat) {
                            kordinat = 0;
                            receivedData[i+1] = '\0';
                            yedek[k][1] = atoi(p);
                            k++;
                        }
                        i++;
                        
                    }
    
            }
        }
    
       }
    
  
    int b = 0;
    for (int i = 0; i < k; i++) {
        int kenarsayi = 0;
//kenar sayısını bulduran döngü
        for (int a = i + 1; a < k; a++) {
            kenarsayi++;
            if (yedek[i][0] == yedek[a][0] && yedek[i][1] == yedek[a][1]) {
                knrs[b] = kenarsayi;
                b++;
                break;
//                for döngüsünde koordinatların aynı olma durumunu kıyaslar.
            }
        }
    }
//aşağıda koordinatları grupluyor.
    if (knrs[0] != 0) {
        int c=0;
        for (int w = 0; w < knrs[0]; w++) {
            sekil1[c][0] = yedek[w][0];
            sekil1[c][1] = yedek[w][1];
            c++;
        }
    }
    if (knrs[1] != 0) {
        int e = 0;
        for (int d = knrs[0] + 1; d < knrs[1] + knrs[0] + 1; d++) {
            sekil2[e][0] = yedek[d][0];
            sekil2[e][1] = yedek[d][1];
            e++;
        }
    }
    if (knrs[2] != 0) {
        int g = 0;
        for (int f = knrs[0] + knrs[1] + 2; f < knrs[0] + knrs[2] + knrs[1] + 3; f++) {
            sekil3[g][0] = yedek[f][0];
            sekil3[g][1] = yedek[f][1];
            g++;
        }
    }
}

void display() {
//
    glClear(GL_COLOR_BUFFER_BIT);
//    ekranı temizler.
    glMatrixMode(GL_MODELVIEW);
//    koordiant sistemi için gerekli matrisi seçer.
    glLoadIdentity();
//    mevcut matrisi sıfırlar.
    int knrs[3] = {0};
    kenarsayisi(knrs);
    double alan[3];
   
    
    // İlk şekil çizimi
    glColor3f(1.0, 0.0, 0.0); // Kırmızı renk
    glBegin(GL_POLYGON);
//    bir çokgen oluşturulacağını belirler.
    //SEKİL 1
    for (int i = 0; i < knrs[0]; i++) {
        glVertex2i(sekil1[i][0], sekil1[i][1]);
//        çizim yatpırır.
        int x[knrs[0]];
        int y[knrs[0]];
              
              for (int i = 0; i < knrs[0]; i++) {
                      x[i] = sekil1[i][0];
                      y[i] = sekil1[i][1];
                  }
              int minX = x[0], minY = y[0], maxX = x[0], maxY = y[0];

              
              for (int i = 1; i < knrs[0]; i++) {
                      if (x[i] < minX) minX = x[i];
                      if (x[i] > maxX) maxX = x[i];
                      if (y[i] < minY) minY = y[i];
                      if (y[i] > maxY) maxY = y[i];
                  }
              // Dikdörtgenin uzunluğu ve yüksekliği hesaplanıyor
                 int genislik = maxX - minX;
                 int yukseklik = maxY - minY;
              // Dikdörtgenin alanı hesaplanıyor
                alan[0] = genislik * yukseklik;
    }
    
    double ziyaretsayisi=0;
    double toplam=0;
    double balan=0;// bolge alani
            for(int i=0;i<knrs[0];i++)
            {
                int ebob=0;
                
                if(i==knrs[0]-1)
                {
                    int sayi1=fabs(sekil1[i][1]-sekil1[0][1]);
                    int sayi2=fabs(sekil1[i][0]-sekil1[0][0]);
                    ziyaretsayisi=(fabs(sekil1[i][1]-sekil1[0][1])+fabs(sekil1[i][0]-sekil1[0][0])-1);
                                   
                    if(sayi1==0 || sayi2==0)
                     {
                         ebob=0;
                         ziyaretsayisi=0;
                     }
                    else {
                    
                        while (sayi1 != sayi2) {
                            if (sayi1 > sayi2)
                                sayi1=sayi1 - sayi2;
                            else
                                sayi2=sayi2 - sayi1;
                            
                        }
                        ebob=sayi1-1;
                    }
                    
                                    
                        balan=fabs(((sekil1[i][1]-sekil1[0][1])*fabs(sekil1[i][0]-sekil1[0][0]))/2)-(ziyaretsayisi-ebob)/2;
                        int x=(fabs((sekil1[i][1]-sekil1[0][1])*fabs(sekil1[i][0]-sekil1[0][0]))/2);
                        toplam=toplam+balan;
                    break;
                }
                
                
                else
                {
//                    x ve ylerin farkı (x1-x2)=n,(y1-y2)=m
                    int sayi1=fabs(sekil1[i][1]-sekil1[i+1][1]);
                    int sayi2=fabs(sekil1[i][0]-sekil1[i+1][0]);
                    ziyaretsayisi=(fabs(sekil1[i][1]-sekil1[i+1][1])+fabs(sekil1[i][0]-sekil1[i+1][0])-1);
//                    n+m-1 iki koordinat noktalarından geçen çizgini ziyaret ettiği birim kare sayısı
//                    ziyaret sayısındaki 1e1lik geçen birim karelerin kaç kere geçtiğini bulmak için ebob
                                       if(sayi1==0 || sayi2==0)
                                        {
                                            ebob=0;
                                            ziyaretsayisi=0;
//                                            n ya da mnin 0 olduğu durumlarda (eğimin sıfır olması) olması gerekn değerler
                                        }
                                       else {
                                           while (sayi1 != sayi2) {
                                               if (sayi1 > sayi2)
                                                   sayi1=sayi1 - sayi2;
                                               else
                                                   sayi2=sayi2 - sayi1;
                                               
                                           }
                                           ebob=sayi1-1;
                                       }
                                   
//                                    bölge bölge hesaplanan alanı en sonda for döngüyüsüyle toplama
                    balan=fabs(((sekil1[i][1]-sekil1[i+1][1])*fabs(sekil1[i][0]-sekil1[i+1][0]))/2)-(ziyaretsayisi-ebob)/2;
                                    toplam=toplam+balan;
                   
                                }
                
                    
                }
    
    if(knrs[0]!=0){
           
           
            printf("1. seklin birim kare sayisi : %.2lf\n", alan[0] - toplam);
         
                    
        }

    glEnd();

    
    
    
    
    // İkinci şekil çizimi
    glColor3f(0.0, 1.0, 0.0); // Yeşil renk
    glBegin(GL_POLYGON);
    for (int i = 0; i < knrs[1]; i++) {//knrs 3 olmali
        glVertex2i(sekil2[i][0], sekil2[i][1]);
        
        
        int x[knrs[1]];
        int y[knrs[1]];
        
              
              for (int i = 0; i < knrs[1]; i++) {
                      x[i] = sekil2[i][0];
                      y[i] = sekil2[i][1];
                  }
              int minX = x[0], minY = y[0], maxX = x[0], maxY = y[0];

              
              for (int i = 1; i < knrs[1]; i++) {
                      if (x[i] < minX) minX = x[i];
                      if (x[i] > maxX) maxX = x[i];
                      if (y[i] < minY) minY = y[i];
                      if (y[i] > maxY) maxY = y[i];
                  }
              
              // Dikdörtgenin uzunluğu ve yüksekliği hesaplanıyor
                 int genislik = maxX - minX;
                 int yukseklik = maxY - minY;
              // Dikdörtgenin alanı hesaplanıyor
                alan[1] = genislik * yukseklik;
        
    }
  
    
    double ziyaretsayisi1=0;
    double toplam1=0;
    double balan1=0;// bolge alani
            for(int i=0;i<knrs[1];i++)
            {
                int ebob=0;
                
                if(i==knrs[1]-1)
                {
                    int sayi1=fabs(sekil2[i][1]-sekil2[0][1]);
                    int sayi2=fabs(sekil2[i][0]-sekil2[0][0]);
                    ziyaretsayisi1=(fabs(sekil2[i][1]-sekil2[0][1])+fabs(sekil2[i][0]-sekil2[0][0])-1);
                    if(sayi1==0 || sayi2==0)
                     {
                         ebob=0;
                         ziyaretsayisi1=0;
                     }
                    else {
                     
                        while (sayi1 != sayi2) {
                            if (sayi1 > sayi2)
                                sayi1=sayi1 - sayi2;
                            else
                                sayi2=sayi2 - sayi1;
                            
                        }
                        ebob=sayi1-1;
                    }
                    
                
                                    balan1=fabs(((sekil2[i][1]-sekil2[0][1])*fabs(sekil2[i][0]-sekil2[0][0]))/2)-(ziyaretsayisi1-ebob)/2;
                                    toplam1=toplam1+balan1;
                    break;
                }
                else
                {
                    int sayi1=fabs(sekil2[i][1]-sekil2[i+1][1]);
                    int sayi2=fabs(sekil2[i][0]-sekil2[i+1][0]);
                    ziyaretsayisi1=(fabs(sekil2[i][1]-sekil2[i+1][1])+fabs(sekil2[i][0]-sekil2[i+1][0])-1);
                    
                                       if(sayi1==0 || sayi2==0)
                                        {
                                            ebob=0;
                                            ziyaretsayisi1=0;
                                        }
                                       else {
                                           while (sayi1 != sayi2) {
                                               if (sayi1 > sayi2)
                                                   sayi1=sayi1 - sayi2;
                                               else
                                                   sayi2=sayi2 - sayi1;
                                               
                                           }
                                           ebob=sayi1-1;
                                       }
                                
                                    
                    balan1=fabs(((sekil2[i][1]-sekil2[i+1][1])*fabs(sekil2[i][0]-sekil2[i+1][0]))/2)-(ziyaretsayisi1-ebob)/2;
                    toplam1=toplam1+balan1;
                    
                                }
                
                    
                }
    if(knrs[1]!=0){
          
           printf("2. seklin birim kare sayisi : %.2lf\n",alan[1]-toplam1);
          
       }
    glEnd();

    
    
    
    
        double toplam2=0;
    
    // Üçüncü şekil çizimi
    glColor3f(0.0, 0.0, 1.0); // Mavi renk
    glBegin(GL_POLYGON);
    for (int i = 0; i < knrs[2]; i++) {
        glVertex2i(sekil3[i][0], sekil3[i][1]);
        
        int x[knrs[2]];
        int y[knrs[2]];
              
              for (int i = 0; i < knrs[2]; i++) {
                      x[i] = sekil3[i][0];
                      y[i] = sekil3[i][1];
                  }
              int minX = x[0], minY = y[0], maxX = x[0], maxY = y[0];

              
              for (int i = 1; i < knrs[2]; i++) {
                      if (x[i] < minX) minX = x[i];
                      if (x[i] > maxX) maxX = x[i];
                      if (y[i] < minY) minY = y[i];
                      if (y[i] > maxY) maxY = y[i];
                  }
              
              // Dikdörtgenin uzunluğu ve yüksekliği hesaplanıyor
                 int genislik = maxX - minX;
                 int yukseklik = maxY - minY;
              // Dikdörtgenin alanı hesaplanıyor
               alan[2] = genislik * yukseklik;
        
        double ziyaretsayisi2=0;
        toplam2=0;
        double balan2=0;// bolge alani
                for(int i=0;i<knrs[2];i++)
                {
                    int ebob=0;
                    
                    if(i==knrs[2]-1)
                    {
                        int sayi1=fabs(sekil3[i][1]-sekil3[0][1]);
                        int sayi2=fabs(sekil3[i][0]-sekil3[0][0]);
                      ziyaretsayisi2=(fabs(sekil3[i][1]-sekil3[0][1])+fabs(sekil3[i][0]-sekil3[0][0])-1);
         
                        if(sayi1==0 || sayi2==0)
                         {
                             ebob=0;
                             ziyaretsayisi2=0;
                         }
                        else {
                       
                            while (sayi1 != sayi2) {
                            
                                if (sayi1 > sayi2)
                                    sayi1=sayi1 - sayi2;
                                else
                                    sayi2=sayi2 - sayi1;
                                
                            }
                            ebob=sayi1-1;
                        }
                        
                                        
                        balan2=fabs(((sekil3[i][1]-sekil3[0][1])*fabs(sekil3[i][0]-sekil3[0][0]))/2)-(ziyaretsayisi2-ebob)/2;
                        toplam2=toplam2+balan2;
                        break;
                    }
                    else
                    {
                        int sayi1=fabs(sekil3[i][1]-sekil3[i+1][1]);
                        int sayi2=fabs(sekil3[i][0]-sekil3[i+1][0]);
                        ziyaretsayisi2=(fabs(sekil3[i][1]-sekil3[i+1][1])+fabs(sekil3[i][0]-sekil3[i+1][0])-1);
                        
                        if(sayi1==0 || sayi2==0)
                        {
                            ebob=0;
                            ziyaretsayisi2=0;
                        }
                        else{
                                              
                                               while (sayi1 != sayi2) {
                                                
                                                   if (sayi1 > sayi2)
                                                       sayi1=sayi1 - sayi2;
                                                   else
                                                       sayi2=sayi2 - sayi1;
                                                   
                                               }
                                               ebob=sayi1-1;
                                           }
                                    
                        balan2=fabs(((sekil3[i][1]-sekil3[i+1][1])*fabs(sekil3[i][0]-sekil3[i+1][0]))/2)-(ziyaretsayisi2-ebob)/2;
                        toplam2=toplam2+balan2;
                                    }
                    
                        
                    }
        
           }
           glEnd();
    if(knrs[2]!=0){
             
            
               printf("3. seklin birim kare sayisi : %.2lf\n",alan[2]-toplam2);
             
           }
           
           
    // Yatay çizgiler
       glColor3f(0.5, 0.5, 0.5); // Siyah renk
       for (int y = -windowHeight / 2; y <= windowHeight / 2; y += 1) {
//y ekseni
           glBegin(GL_LINES);
           glVertex2i(-windowWidth / 2, y);
           glVertex2i(windowWidth / 2, y);
           glEnd();
       }

       // Dikey çizgiler
       for (int x = -windowWidth / 2; x <= windowWidth / 2; x += 1) {
           //xekseni
           glBegin(GL_LINES);
           glVertex2i(x, -windowHeight / 2);
           glVertex2i(x, windowHeight / 2);
           glEnd();
       }
    glFlush();
//   verileri pencereye hemen çizmeye zorlar.
}


//pencere boyutunu düzenleme
void pencereduzen(int w, int h) {
    glViewport(0, 0, w, h); // Görüntüleme penceresinin boyutunu yeniden ayarlar
    glMatrixMode(GL_PROJECTION);//dönüşüm matrisini belirler. projeksiyon kısmını belirtir
    glLoadIdentity();//mevcüt dönüşüm matrisini sıfırlar. varsayılan birim matrisi oluşturur.

    // Şekli ortala (merkezleme)
    float merkezx = windowWidth / 40.0;
    float merkezy = windowHeight / 500.0;
    glOrtho(merkezx - (w / 5), merkezx + (w / 1), merkezy - (h / 1),merkezy + (h / 5), -1, 1);
//(left,right,bottom,top,derinilik(nearval,farval)
    // pencereyi oranlar
    float olcek = 15.0;
    glScalef(olcek, -olcek, 30.0); // Y koordinatlarını tersine çevir
    glMatrixMode(GL_MODELVIEW);
//    model koordinat ssisteminde koordinat sistemine dönüştürür.
}




int main(int argc, char** argv) {
    CURL *curl;
    CURLcode res;
//    curl tanımları
    curl_global_init(CURL_GLOBAL_DEFAULT);
//    curl kütüphanesini başlatır.
    curl = curl_easy_init();
//curl işaretçisini başlatır.başarılıysa bu işlem yeni bir curl işlemini temsil eder
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt");
//url yerleştirilir.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, veriisle);
//        işlencek fonk belirtir.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, receivedData);
//nereye yazılacağı
        res = curl_easy_perform(curl);
//res işlemin durumu saklar
        if (res == CURLE_OK) {
            printf("Başarılı(mainde)!\n");
            printf("Alınan Veri:\n%s  (mainde)\n", receivedData);
        } else {
            fprintf(stderr, "İstek başarısız: %s\n", curl_easy_strerror(res));
//            başarsızsa hata nedenini gösterir.
        }

        curl_easy_cleanup(curl);
//        curl işaretçisini ve kullanılan kaynakları temizler.bellek sızımı ve gereksiz kaynak kullanımını engellemek için kullanılır.
    }

    // OpenGL başlatma
    glutInit(&argc, argv);
//    glut kütüphanesini başlatır. paramtreler gluta komut satırları argümanlarını iletmek için kullanılır.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutsingle tek bir pencere için çift tampon oluşturur. rgb ayarlar.
    glutInitWindowSize(windowWidth, windowHeight);
//    genişlik ve yüksekliği belirler
    glutCreateWindow("PROJE 1");
//başlık adı
    glutDisplayFunc(display);
//    pencereye çizdirir
    glutReshapeFunc(pencereduzen);
//boyut
    glutMainLoop();
//olayları işler
    return 0;
}
        
