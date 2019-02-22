#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "lcd16x2.h"
#include "i2c.h"
#include <stdio.h>

#define HMC5833L_DEVICE_ADDRESS				0x1E
#define HMC5833L_CFG_A_REGISTER				0x00
#define HMC5833L_CFG_B_REGISTER				0x01
#define HMC5833L_MODE_REGISTER				0x02
#define HMC5833L_DO_REGISTER_START		0x03

void HMC5883_Init(void);
void HMC5883_GetHeadings(void);

int16_t rawX, rawY, rawZ;
char buf[8];

GPIO_InitTypeDef GPIO_InitStruct;
void delay(int a);


uint8_t Pusula_Acisi;
char Kible_Acilari[11][2]={"Adana","161","Adiyaman","170","Afyon","149","Agri","185","Amasya","164","Ankara","155","Antalya","146","Artvin","179","Aydin","140","Balikesir","143","Bilecik","149"};

//Türkiye Cumhuriyeti Istiklal Marsi  
const int buzzer = 7; // buzzer pin7 ve GND'ye bagli
//kullanilacak notalar
int a, ad, b, c, cd, d, dd, e, f, fd, g, gd, a2, ad2, b2, c2, cd2, d2, dd2, e2, f2, fd2, g2, gd2, a3;
void setup()  
{ 
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
////////////////////// 
// c  = do
// cd = do diyez
// d  = re
// dd = re diyez
// e  = mi
// f  = fa
// fd = fa diyez
// g  = sol
// gd = sol diyez
// a  = la
// ad = la diyez
// b  = si
///////////////////////
//notalara karsilik gelen frekans degerleri
a=440;
ad=466;
b=494;
c=523;
cd=554;
d=587;
dd=622;
e=659;
f = 698;
fd = 740;
g = 784;
gd = 830;
a2 = 880;
ad2 = 932;
b2 = 988;
c2 = 1046;
cd2 = 1108;
d2 = 1174;
dd2 = 1244;
e2 = 1318;
f2 = 1396;
fd2 = 1480;
g2 = 1568;
gd2 = 1660;
a3 = 1760;
} 
void dongu()
{ 
//Korkma Sönmez Bu Safak 
    tone(buzzer, c);
    delay(800);
    tone(buzzer, f);
    delay(800);
    tone(buzzer, g);
    delay(800);
    tone(buzzer, gd);
    delay(800);
    tone(buzzer, e);
    delay(400);
    tone(buzzer, g);
    delay(200);       
    tone(buzzer, f);
    delay(1600);       
    noTone(buzzer);
    delay(300);
//Larda Yüzden Al Sancak
    tone(buzzer, f);
    delay(800);       
    tone(buzzer, ad2);
    delay(800);       
    tone(buzzer, c2);
    delay(800);       
    tone(buzzer, cd2);
    delay(800);
    tone(buzzer, a2);
    delay(400);
    tone(buzzer, c2);
    delay(200);
    tone(buzzer, ad2);
    delay(1600);       
//Sönmeden Yurdumun Üstünde Tüten En Son Ocak O Be
    tone(buzzer, c2);
    delay(200);       
    tone(buzzer, ad2);
    delay(200);       
    tone(buzzer, c2);
    delay(200);       
    tone(buzzer, g);
    delay(400);       
    noTone(buzzer);
    delay(100); 
    tone(buzzer, g);
    delay(400);       
    tone(buzzer, ad);
    delay(200);
    tone(buzzer, gd);
    delay(400);  
    tone(buzzer, e);
    delay(200);
    tone(buzzer, f);
    delay(400);  
    tone(buzzer, g);
    delay(200);
    tone(buzzer, gd);
    delay(400);       
    tone(buzzer, ad);
    delay(200);       
    tone(buzzer, c2);
    delay(400);       
    tone(buzzer, cd2);
    delay(200);       
    tone(buzzer, dd2);
    delay(400);       
    tone(buzzer, f2);
    delay(200);       
    tone(buzzer, dd2);
    delay(400);    
//Nim Milletimin
    tone(buzzer, dd);
    delay(200);
    tone(buzzer, d);
    delay(200);
    tone(buzzer, dd);
    delay(200);
    tone(buzzer, c2);
    delay(800);
    tone(buzzer, ad);
    delay(800);
    tone(buzzer, gd);
    delay(1600);
// Yildizidir Parlayacak O benim
    tone(buzzer, c);
    delay(200);
    tone(buzzer, b);
    delay(200);
    tone(buzzer, c);
    delay(200);
    tone(buzzer, g);
    delay(800);
    tone(buzzer, c);
    delay(800);
    tone(buzzer, c2);
    delay(800);
    tone(buzzer, ad);
    delay(200);
    tone(buzzer, gd);
    delay(200);
    tone(buzzer, g);
    delay(400);
    tone(buzzer, gd);
    delay(200);
    tone(buzzer, f);
    delay(800);
//Dir O Benim Milletimindir Ancak
    tone(buzzer, f2);
    delay(800);
    tone(buzzer, dd2);
    delay(200);
    tone(buzzer, cd2);
    delay(400);
    tone(buzzer, c2);
    delay(200);
    tone(buzzer, ad);
    delay(400);
    tone(buzzer, gd);
    delay(200);
    tone(buzzer, g);
    delay(400);
    tone(buzzer, f);
    delay(200);
    tone(buzzer, c2);
    delay(400);
    tone(buzzer, c);
    delay(800);
    tone(buzzer, f);
    delay(1600);
/////////////ikinci kit'a
//Çatma Kurban Olayim
    tone(buzzer, c);
    delay(800);
    tone(buzzer, f);
    delay(800);
    tone(buzzer, g);
    delay(800);
    tone(buzzer, gd);
    delay(800);
    tone(buzzer, e);
    delay(400);
    tone(buzzer, g);
    delay(200);       
    tone(buzzer, f);
    delay(1600);       
    noTone(buzzer);
    delay(300);
//Çehreni Ey Nazli Hilal
    tone(buzzer, f);
    delay(800);       
    tone(buzzer, ad2);
    delay(800);       
    tone(buzzer, c2);
    delay(800);       
    tone(buzzer, cd2);
    delay(400);
    tone(buzzer, ad2);
    delay(400);
    tone(buzzer, a2);
    delay(400);
    tone(buzzer, c2);
    delay(400);
    tone(buzzer, ad2);
    delay(800);       
//Kahraman Irkima Bir Gül Ne Bu Siddet Bu Celal Sana
    tone(buzzer, c2);
    delay(200);       
    tone(buzzer, ad2);
    delay(200);       
    tone(buzzer, c2);
    delay(200);       
    tone(buzzer, g);
    delay(400);       
    noTone(buzzer);
    delay(100); 
    tone(buzzer, g);
    delay(400);       
    tone(buzzer, ad);
    delay(200);
    tone(buzzer, gd);
    delay(400);  
    tone(buzzer, e);
    delay(200);
    tone(buzzer, f);
    delay(400);  
    tone(buzzer, g);
    delay(200);
    tone(buzzer, gd);
    delay(400);       
    tone(buzzer, ad);
    delay(200);       
    tone(buzzer, c2);
    delay(400);       
    tone(buzzer, cd2);
    delay(200);       
    tone(buzzer, dd2);
    delay(400);       
    tone(buzzer, f2);
    delay(200);       
    tone(buzzer, dd2);
    delay(400);    
//Olmaz Dökülen
    tone(buzzer, dd);
    delay(200);
    tone(buzzer, d);
    delay(200);
    tone(buzzer, dd);
    delay(200);
    tone(buzzer, c2);
    delay(800);
    tone(buzzer, ad);
    delay(800);
    tone(buzzer, gd);
    delay(1600);
//Kanlarimiz Sonra Helal Hakkidir
    tone(buzzer, c);
    delay(200);
    tone(buzzer, b);
    delay(200);
    tone(buzzer, c);
    delay(200);
    tone(buzzer, g);
    delay(800);
    tone(buzzer, c);
    delay(800);
    tone(buzzer, c2);
    delay(800);
    tone(buzzer, ad);
    delay(200);
    tone(buzzer, gd);
    delay(200);
    tone(buzzer, g);
    delay(400);
    tone(buzzer, gd);
    delay(200);
    tone(buzzer, f);
    delay(800);
//Hakk'a Tapan Milletimin Istiklal
    tone(buzzer, f2);
    delay(800);
    tone(buzzer, dd2);
    delay(200);
    tone(buzzer, cd2);
    delay(400);
    tone(buzzer, c2);
    delay(200);
    tone(buzzer, ad);
    delay(400);
    tone(buzzer, gd);
    delay(200);
    tone(buzzer, g);
    delay(400);
    tone(buzzer, f);
    delay(200);
    tone(buzzer, c2);
    delay(400);
    tone(buzzer, c);
    delay(800);
    tone(buzzer, f);
    delay(1600);
//Söz    : Mehmet Akif Ersoy
//Beste  : Osman Zeki Üngör
    noTone(buzzer);
    delay(300);
    for(;;){} //tekrar yok
}

int main(void)
{
	
	// Enable clock for GPIOC
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  // Configure PC13 as push-pull output
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

	DelayInit();
	//*lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	// Initialize HMC5883L
	HMC5883_Init();
	Pusula_Acisi=HMC5883_GetHeadings();
	if(Pusula_Acisi=="149"){
		setup();
		dongu();
		// Turn on LED on PC9
  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
	
	/**while (1)
	{
		HMC5883_GetHeadings();
		
		lcd16x2_clrscr();
		lcd16x2_puts("X,Y,Z =\n");
		sprintf(buf, "%d,", rawX);
		lcd16x2_puts(buf);
		sprintf(buf, "%d,", rawY);
		lcd16x2_puts(buf);
		sprintf(buf, "%d", rawZ);
		lcd16x2_puts(buf);
		
		DelayMs(250);
	}**/
}

void HMC5883_Init()
{
	// Initialize I2C
	i2c_init();
	
	// Set HMC5883L to default configuration (from datasheet) 
	i2c_write_with_reg(HMC5833L_DEVICE_ADDRESS, HMC5833L_CFG_A_REGISTER, 0x70);
	i2c_write_with_reg(HMC5833L_DEVICE_ADDRESS, HMC5833L_CFG_B_REGISTER, 0xA0);
	// Set HMC5883L to continuous measurement mode
	i2c_write_with_reg(HMC5833L_DEVICE_ADDRESS, HMC5833L_MODE_REGISTER, 0x00);
}

void HMC5883_GetHeadings()
{
	// Raw value from data output register 
	// (X MSB, X LSB, Z MSB, Z LSB, Y MSB, Y LSB)
	uint8_t rawValue[6];
	i2c_read_multi_with_reg(HMC5833L_DEVICE_ADDRESS, 0x03, 6, rawValue);
	
	// Store MSB and LSB of raw X value
	rawX = rawValue[0] << 8;
	rawX |= rawValue[1];
	
	// Store MSB and LSB of raw Z value
	rawZ = rawValue[2] << 8;
	rawZ |= rawValue[3];
	
	// Store MSB and LSB of raw Y	value
	rawY = rawValue[4] << 8;
	rawY |= rawValue[5];
	
	return rawZ;
}
