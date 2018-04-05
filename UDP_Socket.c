#include "rl_net.h"
#include "Board_LED.h"                  // ::Board Support:LED
#include <stdio.h>
#include <string.h>
#include "cmsis_os.h"                   /* CMSIS RTOS definitions             */                    
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_Buttons.h"
#include "Board_ADC.h"


extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

uint8_t ip_addr[NET_ADDR_IP4_LEN];
uint8_t mask[NET_ADDR_IP4_LEN];
uint8_t gateway[NET_ADDR_IP4_LEN];
uint8_t pri_dns[NET_ADDR_IP4_LEN];
uint8_t sec_dns[NET_ADDR_IP4_LEN];

int32_t udp_sock;                       // UDP socket handle
char AskBattery = 0xAA;
char AskPresence = 0xBB;
char AskPlaces = 0xCC;

short tensions;
char presence1, presence2;

int i;

// Send UDP data to destination client 192.168.0.8
void send_udp_data_8 (char data, char nbr_data) {
 
  if (udp_sock > 0) {
		
    NET_ADDR addr = { NET_ADDR_IP4, 2000, 192, 168, 0, 8 };
 
    uint8_t *sendbuf;
 
    sendbuf = netUDP_GetBuffer (nbr_data);
    *sendbuf = data;
	
    netUDP_Send (udp_sock, &addr, sendbuf, nbr_data);
    
  }
}

// Send UDP data to destination client 192.168.0.7
void send_udp_data_7 (char data, char nbr_data) {
 
  if (udp_sock > 0) {
		
    NET_ADDR addr = { NET_ADDR_IP4, 2000, 192, 168, 0, 7 };
 
    uint8_t *sendbuf;
 
    sendbuf = netUDP_GetBuffer (nbr_data);
    *sendbuf = data;
 
    netUDP_Send (udp_sock, &addr, sendbuf, nbr_data);
    
  }
}

// Notify the user application about UDP socket events.
uint32_t udp_cb_func (int32_t socket, const  NET_ADDR *addr, const uint8_t *buf, uint32_t len) {
 
  char chaineT[15];
	
  switch(buf[0]) 
		{
			case 0xAA : LED_On(1);																				//Envoie de la tension
									tensions=buf[1];
									tensions=tensions<<8;
									tensions=tensions + buf[2];	
									tensions = tensions*100/4096;
									sprintf(chaineT, "valeur = %d", tensions);
									GLCD_DrawString(0,30,chaineT);
			break;
			
			case 0xBB : LED_On(2);																				//Envoie des places dispos
			
									if((buf[1] & 0x0F) ==0x01){
									GLCD_SetForegroundColor (GLCD_COLOR_RED);
									GLCD_DrawChar(20,50,'O');
									presence1 = 'O'; }
									
									else if ((buf[1] & 0x0F)==0x00){
									GLCD_SetForegroundColor (GLCD_COLOR_GREEN);
									GLCD_DrawChar(20,50,'L');
									presence1 = 'L'; }
									
									if((buf[1] & 0xF0) ==0x10){
									GLCD_SetForegroundColor (GLCD_COLOR_RED);
									GLCD_DrawChar(60,50,'O');
									presence2 = 'O'; }
									
									else if ((buf[1] & 0xF0)==0x00){
									GLCD_SetForegroundColor (GLCD_COLOR_GREEN);
									GLCD_DrawChar(60,50,'L');
									presence2 = 'L';}
									
			case 0xCC : LED_On(3);																				//Envoie de la tension
									
		}
  return 0;
}

char lcd_text[20+1];
char P2=0;


void netCGI_ProcessData (uint8_t code, const char *data, uint32_t len) {
  char var[40];
	
	if (code != 0) {
    // Les autres codes sont ignor�s
    return;
  }
	
  if (len == 0) {
    // Si pas de donn�e � traiter
    return;
  }
		
  do {
    // Appel de la fonction d'analyse de la trame "POST"
    data = netCGI_GetEnvVar (data, var, sizeof (var));	// var contient la donn�e � g�rer
    if (var[0] != 0) {
      // si il y a une donn�e � g�rer
			
		if (strncmp(var,"lcd1=",5)==0)		//test si c'est egal
		{
		strcpy(lcd_text,&var[5]);					//prends le texte utile et le met dans lcd_text
		GLCD_DrawString(0,0,lcd_text); 		//affiche sur l'ecran
		
		}
			if (strncmp(var,"led0=",5)==0)	
			{
				if (strncmp(&var[4],"1",1)==0) P2=1;	//on allume si la valeur est 1
				else P2=0;														//sinon on l'eteint
			}
    
		}
  } while (data);			// Tant qu'il a a des donn�es � traiter
}
 

uint32_t netCGI_Script (const char *env, char *buf, uint32_t buf_len, uint32_t *pcgi) {
  uint32_t len = 0;

  switch (env[0]) {
    
    case 'a':
			 send_udp_data_7(AskPresence,1);
       len = sprintf (buf, &env[2], presence1, presence2);     
       break;
		
		case 'b':																//Etat de charge de la batterie
			send_udp_data_8(AskBattery,1);
			len = sprintf(buf, &env[2], tensions);
			break;
			
//		case 'd':
//       len = sprintf (buf, &env[2], lcd_text);     
//       break;
    }
  return (len);
}  




int main (void)
	{
	LED_Initialize     ();
  ADC_Initialize     ();
  GLCD_Initialize         ();
  GLCD_SetBackgroundColor (GLCD_COLOR_WHITE);
  GLCD_SetForegroundColor (GLCD_COLOR_BLUE);
  GLCD_ClearScreen        ();
  GLCD_SetFont            (&GLCD_Font_16x24);
  GLCD_DrawString         (0, 0, "Etat de la batterie :");
	Buttons_Initialize ();
	
	netInitialize     ();		
 
  // Initialize UDP socket and open port 2000
  udp_sock = netUDP_GetSocket (udp_cb_func);
  if (udp_sock > 0)
		{
    netUDP_Open (udp_sock, 2000);
			while(1)
			{
				if(Buttons_GetState()==1){ send_udp_data_8(AskBattery,1); //Demande d'�tat de la batterie
																	 osDelay(100);
																	 send_udp_data_7(AskPresence,1); //Demande d'�tat de la batterie
																	 osDelay(100);
																	 send_udp_data_7(AskPlaces,1);	 //Demande combien de places
																	}
			}
		}
	}
