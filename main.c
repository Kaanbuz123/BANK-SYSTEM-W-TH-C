#include <stdio.h>
#include <stdlib.h> // system("cls") için
#include <string.h> // strcmp() fonksiyonu için
#include <renkler.h> // renkler.h kütüphanen olduðunu varsayýyorum
#include <windows.h> // Sleep() ve konsol iþlemleri için

// <-- YENÝ EKLENDÝ: Platforma özel bekleme (sleep) fonksiyonu -->
#ifdef _WIN32
// Windows için milisaniye cinsinden bekleme fonksiyonu
void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}

#endif

// 1. ADIM: Ýki sistem için ortak Veri Yapýsý
struct Kullanici {
    char isim[50];
    char sifre[50];
    char gmail[50];
    double bakiye; // ATM sistemi bu deðiþkeni kullanacak
};


// <-- YENÝ EKLENDÝ: Yükleniyor Ekraný Fonksiyonu -->

/**
 * @brief Belirtilen saniye boyunca "Yükleniyor..." animasyonu gösterir.
 * @param saniye Animasyonun kaç saniye süreceði.
 * @param mesaj Ekranda gösterilecek mesaj (örn: "Yükleniyor").
 */
void yukleniyorEkraniGoster(int saniye, const char* mesaj) {
    // Animasyonun her adýmý 0.4 saniye sürecek.
    int toplamAdim = (saniye * 1000) / 400;
    HANDLE konsol = GetStdHandle(STD_OUTPUT_HANDLE); // Renk için konsolu al

    for (int i = 0; i < toplamAdim; i++) {
        // stdout tamponunu hemen yazmaya zorla yani ("Bekleme odasýnda (stdout tamponunda)
        //ne kadar yazý birikmiþ olursa olsun isterse tek bir harf olsun bekleme yapma onu HEMEN ÞÝMDÝ ekrana zorla yaz."
        fflush(stdout);


        int noktaSayisi = i % 4; // 0, 1, 2, 3, 0, 1, 2, 3...

        // Satýr baþýna dön ve mesajý yazdýr
        printf("\r"); // Satýr baþýna dön
        SetConsoleTextAttribute(konsol, 14); // Sarý renk

        printf("%s", mesaj); // "ATM'ye yönlendiriliyor"

        if (noktaSayisi == 0) {
            printf("    ");
        } else if (noktaSayisi == 1) {
            printf(".   ");
        } else if (noktaSayisi == 2) {
            printf("..  ");
        } else {
            printf("..."); // yükleniyor ekranýnda "." lar tekrarlansýn diye bunlar gülüm
        }

        SetConsoleTextAttribute(konsol, 7); // Rengi normale döndür

        // 400 milisaniye (0.4 saniye) bekle
        sleep_ms(400);
    }

    // Animasyon bittiðinde satýrý temizle ve yeni satýra geç
    printf("\r%s... Tamamlandi! \n\n", mesaj);
    sleep_ms(500); // Kullanýcýnýn mesajý okumasý için kýsa bir bekleme
    SetConsoleTextAttribute(konsol, 7); // Rengi normale döndür
}
// BUNU YAZAN TOSUN OKUYANA KOSUN

// 2. ADIM: ATM Sistemini Fonksiyona Dönüþtürme
void atmMenusu(struct Kullanici* aktifKullanici)
{
    HANDLE konsol = GetStdHandle(STD_OUTPUT_HANDLE);
    int islem;
    double tutar;

    printf(RENK_FG_MAGENTA"KAAN BABANK'A HOSGELDINZ\n"RENK_RESET);
    printf("Sayin %s, hesabiniz acilmistir.\n", aktifKullanici->isim);

    printf("Guncel Bakiyeniz: %.2f TL\n\n", aktifKullanici->bakiye);

    while (1)
    {
        printf("\nLutfen Yapmak Istediginiz Islemi Tuslayiniz\n");
        printf("--------SECENEKLER--------\n");
        printf(RENK_FG_SARI"PARA CEKMEK ICIN: 1 \n"RENK_RESET);
        printf(RENK_FG_SARI"PARA YATIRMAK ICIN: 2 \n"RENK_RESET);
        printf(RENK_FG_SARI"BAKIYE SORGULAMA ICIN: 3 \n"RENK_RESET);
        printf(RENK_FG_SARI"CIKIS (KART IADESI) ICIN: 4 \n"RENK_RESET);
        printf("--------TUSLAYINIZ--------\n");
        printf("Islem Secin: ");

        if (scanf("%d", &islem) != 1) {
            printf(RENK_FG_KIRMIZI"\nGECERSIZ GIRIS! Lutfen sadece sayi giriniz.\n"RENK_RESET);
            while(getchar() != '\n');
            continue;
        }

        switch(islem){
        case 1: // PARA CEKME
            printf(RENK_FG_YESIL"Mevcut Bakiyeniz: %.2f TL\n"RENK_RESET, aktifKullanici->bakiye);
            printf("Ne kadar para cekeceksiniz : ");
            scanf("%lf", &tutar);

            if(tutar <= 0) {
                printf(RENK_FG_KIRMIZI"Gecersiz tutar girdiniz!\n"RENK_RESET);
            } else if(tutar > aktifKullanici->bakiye){
                printf(RENK_FG_KIRMIZI"Yetersiz Bakiye! Bakiyeniz: %.2f TL\n"RENK_RESET, aktifKullanici->bakiye);
            } else {

                // <-- YENÝ YÜKLEME EKRANI (Para Çekme) -->
                yukleniyorEkraniGoster(2, "Para hazirlaniyor");

                aktifKullanici->bakiye -= tutar;
                printf(RENK_FG_YESIL"%.2f TL Cekildi. Yeni bakiyeniz: %.2f TL\n"RENK_RESET, tutar, aktifKullanici->bakiye);
            }
            break;

        case 2: // PARA YATIRMA
            printf(RENK_FG_YESIL RENK_BG_PARLAK_KIRMIZI"Mevcut Bakiyeniz: %.2f TL\n"RENK_RESET, aktifKullanici->bakiye);
            printf("Ne kadar para yatiracaksiniz : ");
            scanf("%lf", &tutar);

            if(tutar > 0){

                // <-- YENÝ YÜKLEME EKRANI (Para Yatýrma) -->
                yukleniyorEkraniGoster(2, "Para sayiliyor ve hesaba geciriliyor");

                aktifKullanici->bakiye += tutar;
                printf(RENK_FG_YESIL RENK_BG_PARLAK_KIRMIZI"Para yatirildi. Guncel bakiyeniz: %.2f TL\n"RENK_RESET, aktifKullanici->bakiye);
            } else {
                printf(RENK_BG_PARLAK_CYAN"0'dan buyuk bir tutar girin. Guncel bakiyeniz: %.2f TL\n"RENK_RESET, aktifKullanici->bakiye);
            }
            break;

        case 3: // BAKÝYE SORGULAMA

            // <-- YENÝ YÜKLEME EKRANI (Bakiye Sorgulama) -->
            yukleniyorEkraniGoster(1, "Bakiye bilgisi aliniyor");

            printf(RENK_FG_YESIL RENK_BG_PARLAK_KIRMIZI"\nGuncel bakiyeniz: %.2f TL\n"RENK_RESET, aktifKullanici->bakiye);
            break;

        case 4: // KART ÝADESÝ (ÇIKIÞ)

            // <-- YENÝ YÜKLEME EKRANI (Çýkýþ) -->
            yukleniyorEkraniGoster(2, "Oturum sonlandiriliyor ve kartiniz hazirlaniyor");

            printf("Kartiniz iade edildi. Bizi tercih ettiginiz icin tesekkur ederiz!\n");
            return;

        default: // GEÇERSÝZ ÝÞLEM
            printf(RENK_FG_KIRMIZI"\nGecersiz islem secildi! Lutfen 1 ile 4 arasinda bir secenek tuslayiniz.\n"RENK_RESET);
        }
    }
}

// 3. ADIM: Kayýt Sistemi Ana Fonksiyon (int main)
int main()
{
    // <-- GÜNCELLENDÝ: konsol deðiþkeni en üste taþýndý -->
    HANDLE konsol = GetStdHandle(STD_OUTPUT_HANDLE);

    struct Kullanici kayitliKullanici;
    kayitliKullanici.bakiye = 2000.0;

    char gisim[50], gsifre[50];

    printf(RENK_BG_PARLAK_KIRMIZI"------KAYIT OLMA TABLOSU DENEME V2.------\n\n"RENK_RESET);

    printf("Tam Adinizi Giriniz =>");
    // SetConsoleTextAttribute(konsol, 14); // Bu satýrý kullanmak için 'konsol'u burada tanýmlamalýyýz
    scanf("%s", kayitliKullanici.isim);

    printf("Bir Sifre Belirleyiniz=>");
    scanf("%s", kayitliKullanici.sifre);

    printf("Gmailinizi Giriniz=>");
    scanf("%s", kayitliKullanici.gmail);
    // SetConsoleTextAttribute(konsol, 7);

    printf(RENK_BG_PARLAK_KIRMIZI"------Kayit Islemi Basarili (Baslangic Bakiye: %.2f TL)------\n\n"RENK_RESET, kayitliKullanici.bakiye);

    // <-- YENÝ YÜKLEME EKRANI (Kayýt Sonrasý) -->
    yukleniyorEkraniGoster(2, "Kayit verileri sunucuya isleniyor");


    getchar();
    printf("Giris ekranina gitmek icin Enter'a basin...");
    getchar();

    system("cls"); //konsolu temizlesin

    printf(RENK_BG_PARLAK_YESIL"-----GIRIS EKRANINA HOSGELDINIZ-----\n\n"RENK_RESET);

    printf("Isim=>");
    scanf("%s", gisim);

    printf("Sifre=>");
    scanf("%s", gsifre);


    if (strcmp(gisim, kayitliKullanici.isim) == 0 && strcmp(gisim, kayitliKullanici.sifre) == 0){ // <-- DÝKKAT: Burayý kontrol et!

        system("cls");

        printf(RENK_BG_PARLAK_YESIL RENK_FG_YESIL"Tebrikler Basari Ile Giris Yaptiniz.\n\n"RENK_RESET);

        // <-- YENÝ EKLENDÝ: 3 saniyelik yükleme ekranýný burada çaðýrýyoruz -->
        // (Bu zaten senin kodunda vardý, yerinde býraktým)
        yukleniyorEkraniGoster(3, "ATM'ye yonlendiriliyor");

        system("cls");


        atmMenusu(&kayitliKullanici);


        // 'atmMenusu' fonksiyonu bittiðinde kod buradan devam eder:
        printf("\nAna programdan cikiliyor. Iyi gunler dileriz, %s.\n", kayitliKullanici.isim);
        printf(RENK_FG_YESIL"Kalan son bakiyeniz: %.2f TL\n"RENK_RESET, kayitliKullanici.bakiye);


    }else{
        printf(RENK_FG_KIRMIZI"Kullanici Adi Veya Sifre Hatali!"RENK_RESET);
    }

    printf("\nProgrami kapatmak icin Enter'a basin...");
    getchar();
    getchar();

    return 0;
}
