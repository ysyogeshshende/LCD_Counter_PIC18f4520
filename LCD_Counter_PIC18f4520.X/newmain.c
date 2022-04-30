


// PIC18F4520 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = OFF      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <pic18f4520.h>

#define lcdport LATB

#define rs LATAbits.LA1
#define en LATAbits.LA2


void lcd_ini(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void LCD_Write_String(char *str);
void LCD_Set_Cursor(unsigned char r, unsigned char c);

void LCD_Clear(void);
#define _XTAL_FREQ 8000000
/*****************************Main Program*******************************/

void main(void)
{       
    OSCCON=0x72;   
    TRISB=0x00;
    LATB=0x00;
    TRISD=0x00;
    LATD=0x00;
    TRISA=0x00;
    LATA=0x00;
    TRISC=0x00;
    
   lcd_ini();	
   LCD_Set_Cursor(1,3);
   LCD_Write_String("Counter Start -------"); 
   __delay_ms(2000);
   LCD_Clear();
   uint16_t count =5000UL;
   uint16_t DispCount =0UL;
    char buffer[10];
    LCD_Set_Cursor(1,3);
    LCD_Write_String("Count -");
    __delay_ms(1000);
  while(1){  
      while(count>0)
        {
            count--;
            DispCount++;
            sprintf(buffer,"%d",DispCount);
            LCD_Set_Cursor(2,5);
            LCD_Write_String(buffer);
            LATDbits.LD2=1;
            __delay_ms(600);
            LATDbits.LD2=0;
            __delay_ms(600);
            
        } 
      DispCount=0;  			
    }
}
void LCD_Clear(void)
{
  lcdcmd(0x01);
}

void lcd_ini(void)
{
	lcdcmd(0x38);		// Configure the LCD in 8-bit mode, 2 line and 5x7 font
	lcdcmd(0x0C);		// Display On and Cursor Off
	lcdcmd(0x01);		// Clear display screen
	lcdcmd(0x06);		// Increment cursor
	lcdcmd(0x80);		// Set cursor position to 1st line, 1st column
}

void lcdcmd(unsigned char cmdout)
{
	lcdport=cmdout;		//Send command to lcdport=PORTB
	rs=0;						
	en=1;
	 __delay_ms(6);
	en=0;
}

void lcddata(unsigned char dataout)
{
	lcdport=dataout;	//Send data to lcdport=PORTB
	rs=1;

	en=1;
	 __delay_ms(6);
	en=0;
}

void LCD_Write_String(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
    lcddata(str[i]);
}
void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    lcdcmd(Temp);
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    lcdcmd(Temp);
  }
}