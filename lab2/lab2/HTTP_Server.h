#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

extern char HTTP_200HEADER[];
extern char HTTP_404HEADER[];

void sendGETresponse(int fdSocket, char strFilePath[], char strResponse[]);

#endif