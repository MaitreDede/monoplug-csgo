/*
 * TeamSpeak 3 server sample
 *
 * Copyright (c) 2007-2009 TeamSpeak-Systems
 */

#ifdef WINDOWS
#include <Windows.h>
#else
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#endif
#include <stdio.h>

#include <public_definitions.h>
#include <public_errors.h>
#include <serverlib_publicdefinitions.h>
#include <serverlib.h>

/*
 * Callback when client has connected.
 *
 * Parameter:
 *   serverID  - Virtual server ID
 *   clientID  - ID of connected client
 *   channelID - ID of channel the client joined
 */
void onClientConnected(anyID serverID, anyID clientID, anyID channelID, unsigned int* removeClientError) {
	printf("Client %u joined channel %u on virtual server %u\n", clientID, channelID, serverID);
}

/*
 * Callback when client has disconnected.
 *
 * Parameter:
 *   serverID  - Virtual server ID
 *   clientID  - ID of disconnected client
 *   channelID - ID of channel the client left
 */
void onClientDisconnected(anyID serverID, anyID clientID, anyID channelID) {
	printf("Client %u left channel %u on virtual server %u\n", clientID, channelID, serverID);
}

/*
 * Callback when client has moved.
 *
 * Parameter:
 *   serverID     - Virtual server ID
 *   clientID     - ID of moved client
 *   oldChannelID - ID of old channel the client left
 *   newChannelID - ID of new channel the client joined
 */
void onClientMoved(anyID serverID, anyID clientID, anyID oldChannelID, anyID newChannelID) {
	printf("Client %u moved from channel %u to channel %u on virtual server %u\n", clientID, oldChannelID, newChannelID, serverID);
}

/*
 * Callback when channel has been created.
 *
 * Parameter:
 *   serverID        - Virtual server ID
 *   invokerClientID - ID of the client who created the channel
 *   channelID       - ID of the created channel
 */
void onChannelCreated(anyID serverID, anyID invokerClientID, anyID channelID) {
	printf("Channel %u created by %u on virtual server %u\n", channelID, invokerClientID, serverID);
}

/*
 * Callback when channel has been edited.
 *
 * Parameter:
 *   serverID        - Virtual server ID
 *   invokerClientID - ID of the client who edited the channel
 *   channelID       - ID of the edited channel
 */
void onChannelEdited(anyID serverID, anyID invokerClientID, anyID channelID) {
	printf("Channel %u edited by %u on virtual server %u\n", channelID, invokerClientID, serverID);
}

/*
 * Callback when channel has been deleted.
 *
 * Parameter:
 *   serverID        - Virtual server ID
 *   invokerClientID - ID of the client who deleted the channel
 *   channelID       - ID of the deleted channel
 */
void onChannelDeleted(anyID serverID, anyID invokerClientID, anyID channelID) {
	printf("Channel %u deleted by %u on virtual server %u\n", channelID, invokerClientID, serverID);
}

/*
 * Callback for user-defined logging.
 *
 * Parameter:
 *   logMessage        - Log message text
 *   logLevel          - Severity of log message
 *   logChannel        - Custom text to categorize the message channel
 *   logID             - Virtual server ID giving the virtual server source of the log event
 *   logTime           - String with the date and time the log entry occured
 *   completeLogString - Verbose log message including all previous parameters for convinience
 */
void onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, anyID logID, const char* logTime, const char* completeLogString) {
	/* Your custom error display here... */
	/* printf("LOG: %s\n", completeLogString); */
	if(logLevel == LogLevel_CRITICAL) {
		exit(1);  /* Your custom handling of critical errors */
	}
}

/*
 * Callback triggered when the specified client starts talking.
 *
 * Parameters:
 *   serverID - ID of the virtual server sending the callback
 *   clientID - ID of the client which started talking
 */
void onClientStartTalkingEvent(anyID serverID, anyID clientID) {
	printf("onClientStartTalkingEvent serverID=%u, clientID=%u\n", serverID, clientID);
}

/*
 * Callback triggered when the specified client stops talking.
 *
 * Parameters:
 *   serverID - ID of the virtual server sending the callback
 *   clientID - ID of the client which stopped talking
 */
void onClientStopTalkingEvent(anyID serverID, anyID clientID) {
	printf("onClientStopTalkingEvent serverID=%u, clientID=%u\n", serverID, clientID);
}

/*
 * Callback triggered when a license error occurs.
 *
 * Parameters:
 *   serverID  - ID of the virtual server on which the license error occured. This virtual server will be automatically
 *               shutdown. If the parameter is zero, all virtual servers are affected and have been shutdown.
 *   errorCode - Code of the occured error. Use ts3server_getGlobalErrorMessage() to convert to a message string
 */
void onAccountingErrorEvent(anyID serverID, unsigned int errorCode) {
	char* errorMessage;
	if(ts3server_getGlobalErrorMessage(errorCode, &errorMessage) == ERROR_ok) {
		printf("onAccountingErrorEvent serverID=%u, errorCode=%u: %s\n", serverID, errorCode, errorMessage);
		ts3server_freeMemory(errorMessage);
	}

	/* If serverID is zero, the whole server is affected, you might want to destroy the serverlib here to clean up resources.
	 * If serverID is not zero, the specified virtual server is already stopped but other virtual servers continue running. */
	if(serverID == 0) {
		if(ts3server_destroyServerLib() != ERROR_ok) {
			printf("Error destroying server lib\n");
		}
	}

	/* Your custom handling here. In a real application, you wouldn't stop the whole process because the TS3 server part went down.
	 * The whole idea of this callback is to let you gracefully handle the TS3 server failing to start and to continue your application. */
	exit(1);
}

/*
 * Read server key from file
 */
int readKeyPairFromFile(const char *fileName, char *keyPair) {
	FILE *file;

	file = fopen(fileName, "r");
	if(file == NULL) {
		printf("Could not open file '%s' for reading keypair\n", fileName);
		return -1;
	}

	fgets(keyPair, BUFSIZ, file);
	if(ferror(file) != 0) {
		fclose (file);
		printf("Error reading keypair from file '%s'.\n", fileName);
		return -1;
	}
	fclose (file);

	printf("Read keypair '%s' from file '%s'.\n", keyPair, fileName);
	return 0;
}

/*
 * Write server key to file
 */
int writeKeyPairToFile(const char *fileName, const char* keyPair) {
	FILE *file;

	file = fopen(fileName, "w");
	if(file == NULL) {
		printf("Could not open file '%s' for writing keypair\n", fileName);
		return -1;
	}

	fputs(keyPair, file);
	if(ferror(file) != 0) {
		fclose (file);
		printf("Error writing keypair to file '%s'.\n", fileName);
		return -1;
	}
	fclose (file);

	printf("Wrote keypair '%s' to file '%s'.\n", keyPair, fileName);
	return 0;
}

int main() {
	char *version;
    anyID serverID;
	unsigned int error;
	char buffer[BUFSIZ] = { 0 };
	char filename[BUFSIZ];
	char port_str[20];
	char *keyPair;

	/* Create struct for callback function pointers */
	struct ServerLibFunctions funcs;

	/* Initialize all callbacks with NULL */
	memset(&funcs, 0, sizeof(struct ServerLibFunctions));

	/* Now assign the used callback function pointers */
	funcs.onClientConnected         = onClientConnected;
	funcs.onClientDisconnected      = onClientDisconnected;
	funcs.onClientMoved              = onClientMoved;
	funcs.onChannelCreated          = onChannelCreated;
	funcs.onChannelEdited           = onChannelEdited;
	funcs.onChannelDeleted          = onChannelDeleted;
	funcs.onUserLoggingMessageEvent = onUserLoggingMessageEvent;
	funcs.onClientStartTalkingEvent = onClientStartTalkingEvent;
	funcs.onClientStopTalkingEvent  = onClientStopTalkingEvent;
	funcs.onAccountingErrorEvent    = onAccountingErrorEvent;

	/* Initialize server lib with callbacks */
	ts3server_initServerLib(&funcs, LogType_FILE | LogType_CONSOLE | LogType_USERLOGGING, NULL);

	/* Query and print server lib version */
    if((error = ts3server_getServerLibVersion(&version)) != ERROR_ok) {
        printf("Error querying server lib version: %d\n", error);
        return 1;
    }
    printf("Server lib version: %s\n", version);
    ts3server_freeMemory(version);  /* Release dynamically allocated memory */

	/* Attempt to load keypair from file */
	/* Assemble filename: keypair_<port>.txt */
	strcpy(filename, "keypair_");
	sprintf(port_str, "%d", 9987);  // Default port
	strcat(filename, port_str);
	strcat(filename, ".txt");

	/* Try reading keyPair from file */
	if(readKeyPairFromFile(filename, buffer) == 0) {
		keyPair = buffer;  /* Id read from file */
	} else {
		keyPair = "";  /* No Id saved, start virtual server with empty keyPair string */
	}

    /* Create virtual server using default port 9987 with max 10 slots */

	/* Create the virtual server with specified port, name, keyPair and max clients */
	printf("Create virtual server using keypair '%s'\n", keyPair);
    if((error = ts3server_createVirtualServer(9987, "0.0.0.0", "TeamSpeak 3 SDK Testserver", keyPair, 10, &serverID)) != ERROR_ok) {
		char* errormsg;
		if(ts3server_getGlobalErrorMessage(error, &errormsg) == ERROR_ok) {
			printf("Error creating virtual server: %s (%d)\n", errormsg, error);
			ts3server_freeMemory(errormsg);
		}
        return 1;
    }

	/* If we didn't load the keyPair before, query it from virtual server and save to file */
	if(!*buffer) {
		if((error = ts3server_getVirtualServerKeyPair(serverID, &keyPair)) != ERROR_ok) {
			char* errormsg;
			if(ts3server_getGlobalErrorMessage(error, &errormsg) == ERROR_ok) {
				printf("Error querying keyPair: %s\n\n", errormsg);
				ts3server_freeMemory(errormsg);
			}
			return 0;
		}

		/* Save keyPair to file "keypair_<port>.txt"*/
		if(writeKeyPairToFile(filename, keyPair) != 0) {
			ts3server_freeMemory(keyPair);
			return 0;
		}
		ts3server_freeMemory(keyPair);
	}

    /* Set welcome message */
    if((error = ts3server_setVirtualServerVariableAsString(serverID, VIRTUALSERVER_WELCOMEMESSAGE, "Hello TeamSpeak 3")) != ERROR_ok) {
        printf("Error setting server welcomemessage: %d\n", error);
        return 1;
    }

    /* Set server password */
    if((error = ts3server_setVirtualServerVariableAsString(serverID, VIRTUALSERVER_PASSWORD, "secret")) != ERROR_ok) {
        printf("Error setting server password: %d\n", error);
        return 1;
    }

    /* Flush above two changes to server */
    if((error = ts3server_flushVirtualServerVariable(serverID)) != ERROR_ok) {
        printf("Error flushing server variables: %d\n", error);
        return 1;
    }

    /* Wait for user input */
    printf("\n--- Press Return to shutdown server and exit ---\n");
    getchar();

    /* Stop virtual server */
    if((error = ts3server_stopVirtualServer(serverID)) != ERROR_ok) {
        printf("Error stopping virtual server: %d\n", error);
        return 1;
    }

	/* Shutdown server lib */
    if((error = ts3server_destroyServerLib()) != ERROR_ok) {
        printf("Error destroying server lib: %d\n", error);
        return 1;
    }

	return 0;
}
