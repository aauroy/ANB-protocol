/**************************************
 * File		: anbMessages.h
 * Brief 	: structures & fonctions inhérentes aux messages
 * Author : 0b1
 **************************************/

/* TODO

	 - vérifier l'effet du paquet libstandard 
	 - mettre les includes qui vont bien
*/
#ifndef _ANB_MESSAGES_H
#define _ANB_MESSAGES_H

/* types de messages */
#define ID_MSG   0
#define ID_ACK 	 1
#define ID_TOKEN 2
#define ID_DATA  3

/* adresse broadcast */
#define _BDCAST_ADDR 255

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
unsigned char  getTxID 	 (anbMessage* msg);
unsigned char  getType 	 (anbMessage* msg);
unsigned char  getSize 	 (anbMessage* msg);
char* getPayload 				 (anbMessage* msg);

anbMessage createIDMessage 		(unsigned char txID);
anbMessage createACKMessage 	(unsigned char txID, unsigned char rxID);
anbMessage createTOKENMessage (unsigned char txID, unsigned char rxID, 
															 char* payload);
anbMessage createDATAMessage  (unsigned char txID, unsigned char rxID, 
															 char* payload);

char*				serializeMessage 	 (anbMessage* msg); 
anbMessage* unserializeMessage (anbMessage* msg);
#endif
