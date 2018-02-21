/*------------------------------------------------------------------------------
 * Serveur Web embarqué - Script CGI
 * GE2 parcours IT2R - IUT de Cachan
 *------------------------------------------------------------------------------
 * Name:    HTTP_Server_CGI.c
 * Purpose: Serveur web HTTP
 * Modif: le 31/01/2016 pour la Team IT2R
 *----------------------------------------------------------------------------*/
 
#include <stdio.h>
#include <string.h>
#include "rl_net.h"
#include "Board_GLCD.h"
#include "Board_ADC.h"                  // ::Board Support:A/D Converter

uint8_t ip_addr[NET_ADDR_IP4_LEN];
uint8_t mask[NET_ADDR_IP4_LEN];
uint8_t gateway[NET_ADDR_IP4_LEN];
uint8_t pri_dns[NET_ADDR_IP4_LEN];
uint8_t sec_dns[NET_ADDR_IP4_LEN];

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

char lcd_text[20+1];
char P2=0;

// Fonction de gestions des requetes de type POST.
// \param[in]     code          type de données à gérer :
//                              - 0 = www-url-encoded form data,
//                              - sinon = autre (hors programme)
// \param[in]     data          pointeur sur donnee POST
// \param[in]     len           longueur donnee POST.
void netCGI_ProcessData (uint8_t code, const char *data, uint32_t len) {
  char var[40];
	
	if (code != 0) {
    // Les autres codes sont ignorés
    return;
  }
	
  if (len == 0) {
    // Si pas de donnée à traiter
    return;
  }
		
  do {
    // Appel de la fonction d'analyse de la trame "POST"
    data = netCGI_GetEnvVar (data, var, sizeof (var));	// var contient la donnée à gérer
    if (var[0] != 0) {
      // si il y a une donnée à gérer
			
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
  } while (data);			// Tant qu'il a a des données à traiter
}
 
// Fonction de génération des lignes CGI à mettre à jour
// \param[in]     env           environment string.
// \param[out]    buf           output data buffer.
// \return        number of bytes written to output buffer.
uint32_t netCGI_Script (const char *env, char *buf, uint32_t buf_len, uint32_t *pcgi) {
  uint32_t len = 0;
	uint32_t adv;

  switch (env[0]) {
    
    case 'a':
      // Mise a jour du champ du script CGI
       len = sprintf (buf, &env[2], lcd_text);     
       break;
		
		case 'b':	
		//	ADC_StartConversion();
		//	while(ADC_ConversionDone() !=0);
			
			//adv = ADC_GetValue();
			
			len = sprintf(buf, &env[2], buf[1], buf[2]);
			break;
			
		case 'd':
       len = sprintf (buf, &env[2], lcd_text);     
       break;
    }
  return (len);
} 