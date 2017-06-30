// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h>    
#include<winsock2.h>
#include<ws2tcpip.h>
#include<iostream>

#pragma comment (lib,"ws2_32.lib")
int main(int argc, char *argv[])
{
	WSADATA Ws;
	//Init Windows Socket
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
		return 0;
	}
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	struct hostent *host;
	int portnumber, nbytes;

	if ((host = gethostbyname("127.0.0.1")) == NULL)
	{
		fprintf(stderr, "Gethostname error\n");
		exit(1);
	}

	if ((portnumber = atoi("9995"))<0)
	{
		fprintf(stderr, "Usage:%s hostname portnumber\a\n", argv[0]);
		exit(1);
	}

	/* �ͻ�����ʼ���� sockfd������ */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "Socket Error:%s\a\n", strerror(errno));
		exit(1);
	}

	/* �ͻ�����������˵�����    */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);

	/* �ͻ���������������     */
	if (connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr, "Connect Error:%s\a\n", strerror(errno));
		exit(1);
	}

	while (true)
	{
		char MESSAGE[] = "hello server..\n";
		//bufferevent_write(buf_ev,MESSAGE,strlen(MESSAGE)); 
		// 
		if (-1 == (::send(sockfd, MESSAGE, strlen(MESSAGE), 0)))
		{
			printf("the net has a error occured..");
			break;
		}

		if ((nbytes = recv(sockfd, buffer, 1024, 0)) == -1)
		{
			fprintf(stderr, "read error:%s\n", strerror(errno));
			exit(1);
		}

		buffer[nbytes] = '\0';
		printf("I have received:%s\n", buffer);
		memset(buffer, 0, 1024);

		Sleep(2);

	}
	/* ����ͨѶ   */
	closesocket(sockfd);
	

	system("pause");

	return 0;
}