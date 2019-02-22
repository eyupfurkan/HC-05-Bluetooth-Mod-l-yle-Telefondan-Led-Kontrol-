#include "stm32f10x_usart.h"//USART kütüphanesi
#include "stm32f10x_rcc.h"//RCC kütüphanesi
#include "stm32f10x_gpio.h"//GPIO kütüphanesi
#include "misc.h"//CMSIS fonksiyon özellikleri kütüphanesi
  
int i;//Global tamsayi cinsinden i
  
			GPIO_InitTypeDef GPIO_InitStructure;//GPIO yerine isimlendirme
  	  USART_InitTypeDef USART_InitStructure;//USART yerine isimlendirme

void NVIC_Configuration(void);//usart1'i kesmeyi aktif etme fonksiyonu oldugunu bildirme
void USART1_IRQHandler(void);//Usart kesme fonksiyonu  oldugunu bildirme
int main(void)//Bluetooth HC-05 modülüyle Telefondan Led Kontrolü Ana Fonksiyonu
	//Telefondan 1 gönderdigimizde led yancak.
//Telefondan 0 gönderdigimizde led söncek.
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	//Register clock control ile yollari açma.

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;//GPIO Pin 0. pin olarak ayarlaniyor.
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//GPIO Hiz 50 MHz olarak ayarlaniyor.
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;//Led çikisi push pull olarak ayarlaniyor.
  GPIO_Init(GPIOA, &GPIO_InitStructure);// Simdi ayarlanan degerler A Portuna aktariliyor.
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//GPIO Pin 9. pin olarak ayarlaniyor.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx oldugu için alternatif push pull olarak ayarlaniyor.
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//GPIO Hiz 50 MHz olarak ayarlaniyor.
  GPIO_Init(GPIOA, &GPIO_InitStructure);//Simdi ayarlanan degerler A Portuna aktariliyor.
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//GPIO Pin 10. pin olarak ayarlaniyor.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//Gerilim degeri gelecegi için Reseave(Alici) olarak ayarlandi.
  GPIO_Init(GPIOA, &GPIO_InitStructure);//Simdi ayarlanan degerler A Portuna aktariliyor.
	
  
  USART_InitStructure.USART_BaudRate = 38400;  //Baund rate bluetooth'u alirken gördüm. 38400'dür.    
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //Kelime uzunlugu 8 BitAction = 1 bayt
  USART_InitStructure.USART_StopBits = USART_StopBits_1; // Baglanti sonlaninca kullanilacak pin - stop 1 biti 
  USART_InitStructure.USART_Parity = USART_Parity_No;// Pariti biti yok.
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //yok. Usart ile usart arasinda haberlesme için.
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //Rx Tx islemi yapilacagi için.
  USART_Init(USART1, &USART_InitStructure); // usart 1'i aktif ediyor. Usart özellikleri yükleniyor ve yeni özelliklere göre baslatiliyor.
  USART_Cmd(USART1, ENABLE);// Aktif etme.
	
    NVIC_Configuration();//usart1'i kesmeyi aktif etme fonksiyonu çagriliyor.
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//Usart1 kesmelerini açma . Sadece Rx ve Tx için.
    while(1)
    {
  
    }//Program sürekli çalismasi için.
}
  
void USART1_IRQHandler(void)//Usart kesme fonksiyonu
{
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET) //Kesme Bayraklari aktifse.
    {
        i = USART_ReceiveData(USART1);//Usart1'den okunan deger i'ye atanir.
        if(i == '1'){//i 1'se yani Telefondan 1 geldiyse islemi yap.
            GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);  //A portunun 0. pinindeki ledi yak.      
        }
        else if(i == '0'){//i 0'sa yani Telefondan 0 geldiyse islemi yap.
            GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET); //A portunun 0. pinindeki ledi söndür.     
        }
    }
}
void NVIC_Configuration(void)//usart1'i kesmeyi aktif etme.
{
  NVIC_InitTypeDef NVIC_InitStructure;//NVIC yerine isimlendirme
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//Kesme kanalini aktif ediyor.
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //Kullanilmiyor.
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //Kullanilmiyor.
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Aktif etme.
  NVIC_Init(&NVIC_InitStructure); // Özellikleri atama.
}
  