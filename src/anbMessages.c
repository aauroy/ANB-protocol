/**************************************
 * File			:	anbMessages.c
 * Brief		: Implémentation des fonctions liées aux messages
 * Author		: 0b1
 **************************************/

#include "anbMessages.h"

/************************************************
 * Création de messages
 ************************************************/
// Note; doit-on passer en dynamique ???
//       si l'o
anbMessage createIDMessage 		(unsigned char txID)
{
	anbMessage msg; 
	setTxID (&msg, txID);
	setRxID (&msg, _BDCAST_ADDR);
	setType (&msg, ID_MSG);
	setSize (&msg, 0);
	setPayload (&msg, NULL); 

	return msg; 
}

anbMessage createACKMessage 	(unsigned char txID, unsigned char rxID)
{
	anbMessage msg; 
	setTxID (&msg, txID);
	setRxID (&msg, rxID);
	setType (&msg, ACK_MSG);
	setSize (&msg, 0);
	setPayload (&msg, NULL); 

	return msg; 
}

anbMessage createTOKENMessage (unsigned char txID, unsigned char rxID, 
															 char* payload, unsigned char payloadSize)
{
	anbMessage msg; 
	setTxID (&msg, txID);
	setRxID (&msg, rxID);
	setType (&msg, TOKEN_MSG);
	setSize (&msg, payloadSize);
	setPayload (&msg, payload); 

	return msg; 
}

anbMessage createDATAMessage  (unsigned char txID, unsigned char rxID, 
															 char* payload, unsigned char payloadSize)
{
	anbMessage msg; 
	setTxID (&msg, txID);
	setRxID (&msg, rxID);
	setType (&msg, DATA_MSG);
	setSize (&msg, payloadSize);
	setPayload (&msg, payload);

	return msg; 
}


/************************************************
 * Sérialisation / Déssérialisation
 ************************************************/
char*				serializeMessage 	 (anbMessage* msg)
{
	char tempCar = 0; 
	char *msgBuffer = (char *) malloc ((int) (_HDR_SIZE + getSize (msg))); 
	
	tempCar = getTxID (msg); 
	memcpy (msgBuffer, &tempCar, _CHAR_SIZE); 
	tempCar = getRxID (msg); 
	memcpy (msgBuffer + _CHAR_SIZE, &tempCar, _CHAR_SIZE);
 	tempCar = getType (msg); 
	memcpy (msgBuffer + (2 * _CHAR_SIZE), &tempCar, _CHAR_SIZE);
	tempCar = getSize (msg); 
	memcpy (msgBuffer + (3 * _CHAR_SIZE), &tempCar, _CHAR_SIZE); 

	if (tempCar != 0)
	{
		memcpy (msgBuffer + (4 * _CHAR_SIZE), getPayload (msg), (int) getSize (msg));  
	}	
	return msgBuffer; 
}

anbMessage unserializeMessage (char* msgBuffer)
{
	anbMessage msg;
	char *visitor = msgBuffer; 
	
	setTxID (&msg, (unsigned char) *visitor);
	++visitor;	
	setRxID (&msg, (unsigned char) *visitor);
	++visitor;	
	setType (&msg, (unsigned char) *visitor);
	++visitor;	
	setSize (&msg, (unsigned char) *visitor); 

	if (getSize (&msg) != 0)
	{
		createPayload (&msg, getSize (&msg)); 
		++visitor; 
		setPayload (&msg, visitor); 	
	}
	return msg; 
}


/************************************************
 * Gestion de la mémoire
 ************************************************/
void createPayload (anbMessage* msg, unsigned char payloadSize)
{
	msg->m_payload = (char *) malloc ((unsigned int) payloadSize); 
	memset (msg->m_payload, 0, (unsigned int) payloadSize); 
	return; 
}

void destroyMessage (anbMessage* msg)
{
	if (getSize (msg) != 0)
		free (msg->m_payload);
	return;
}


/************************************************
 * Setters & getters
 ************************************************/
void setTxID 		(anbMessage* msg, unsigned char tx)
{
	msg->m_txID = tx;
	return;
}

void setRxID 		(anbMessage* msg, unsigned char rx)
{
	msg->m_rxID = rx; 
	return; 
}

void setType 		(anbMessage* msg, unsigned char type)
{
	msg->m_type = type; 
	return;
}

void setSize 		(anbMessage* msg, unsigned char size)
{
	msg->m_size = size; 
}

void setPayload (anbMessage* msg, char* payload)
{
	msg->m_payload = payload; 
	return; 
}

unsigned char  getTxID 	 (anbMessage* msg)
{
	return msg->m_txID;
}

unsigned char  getRxID 	 (anbMessage* msg)
{
	return msg->m_rxID;
}

unsigned char  getType 	 (anbMessage* msg)
{
	return msg->m_type; 
}

unsigned char  getSize 	 (anbMessage* msg)
{
	return msg->m_size; 
}

char* getPayload 				 (anbMessage* msg)
{
	return msg->m_payload; 
}
