/**************************************
 * File		: anbMessages.h
 * Brief 	: structures & fonctions inhérentes aux messages
 * Author : 0b1
 **************************************/
#include <stdlib.h>
#include <string.h>

/* TODO

	 - vérifier l'effet du paquet libstandard 
	 - mettre les includes qui vont bien
*/
#ifndef _ANB_MESSAGES_H
#define _ANB_MESSAGES_H

/* types de messages */
#define ID_MSG    0
#define ACK_MSG   1
#define TOKEN_MSG 2
#define DATA_MSG  3

/* adresse broadcast */
#define _BDCAST_ADDR 255

/* taille de l'entête */
#define _HDR_SIZE 4

/* tailles constantes */
#define _CHAR_SIZE 1
#define _INT_SIZE 4


/* définition de la structure de données */
typedef struct sAnbMessage
{
	unsigned char m_txID;
	unsigned char m_rxID; 
	unsigned char m_type;
	unsigned char m_size; 
	char *m_payload;
} anbMessage;

/* fonctions de gestion des messages */
void setTxID 		(anbMessage* msg, unsigned char tx);
void setRxID 		(anbMessage* msg, unsigned char rx);
void setType 		(anbMessage* msg, unsigned char type);
void setSize 		(anbMessage* msg, unsigned char size);
void setPayload (anbMessage* msg, char* payload);

unsigned char  getTxID 	 (anbMessage* msg);
unsigned char  getRxID 	 (anbMessage* msg);
unsigned char  getType 	 (anbMessage* msg);
unsigned char  getSize 	 (anbMessage* msg);
char* getPayload 				 (anbMessage* msg);

anbMessage createIDMessage 		(unsigned char txID);
anbMessage createACKMessage 	(unsigned char txID, unsigned char rxID);
anbMessage createTOKENMessage (unsigned char txID, unsigned char rxID, char* payload, 
															 unsigned char payloadSize);
anbMessage createDATAMessage  (unsigned char txID, unsigned char rxID, char* payload, 
															 unsigned char payloadSize);

char*				serializeMessage 	 (anbMessage* msg); 
anbMessage  unserializeMessage (char* msgBuffer);
void 				createPayload 		 (anbMessage* msg, unsigned char payloadSize);
void 				destroyMessage     (anbMessage* msg); 				
#endif
