------ - MAIN--------
#pragma warning(disable :4996)
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "fanon.h"
#include "motoron.h"
#include "pumpon.h"
#include "rgbon.h"
#define FAN 22
void sig_handler(int signo);
int main(void)
{
	sginal(SIGINT, (void*)sig_handler);

	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi : %s\n",
			strerror(errno));
		return 1;
	}
	pinMode(FAN, OUTPUT);

	for (;;)
	{
		printf("here - FAN on\n");
		digitalWrite(FAN, 1);
		delay(5000);

		fannon_lib();
		motoron_lib();
		pumpon_lib();
		rgbon_lib();
	}
	return 0;
}
void sig_handler(int signo)
{
	printf("process stop\n");
	digitalWrite(FAN, 0);
	exit(0);
}

------FAN--------
#pragma warning(disable :4996)
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>

#define FAN 22
void sig_handler(int signo);
int fannon_lib(void)
{
	sginal(SIGINT, (void*)sig_handler);

	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi : %s\n",
			strerror(errno));
		return 1;
	}
	pinMode(FAN, OUTPUT);


	{
		printf("here - FAN on\n");
		digitalWrite(FAN, 1);
		delay(5000);
	}
	return 0;
}
void sig_handler(int signo)
{
	printf("process stop\n");
	digitalWrite(FAN, 0);
	exit(0);
}

--------MOTOR--------
#pragma warning(disable :4996)
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTORCONTROL 23
void sig_handler(int signo);

int wiringPicheck(void)
{
	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi : %s\n",
			strerror(errno));
		exit(1);
	}
}
int motoron_lib(void)
{
	if (wiringPicheck()) printf("Fail\n");

	signal(SIGINT, (void*)sig_handler);

	pinMode(MOTORCONTROL, OUTPUT);

	softPwmCreate(MOTORCONTROL, 0, 100);

	int i;
	int delaytime = 3000;

	while (1)
	{
		printf("here\n");
		softPwmWrite(MOTORCONTROL, 5);
		delay(delaytime);

		softPwmWrite(MOTORCONTROL, 0);
		delay(delaytime);
	}
	return 0;
}
void Bplusinmodeset(void)
{
	pinMode(MOTORCONTROL, OUTPUT);
}
void sig_handler(int signo)
{
	printf("process stop\n");
	digitalWrite(MOTORCONTROL, 0);
	exit(0);
}

------ - pump--------
#pragma warning(disable :4996)
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>

#define PUMP 21
void sig_handler(int signo);
int pumpon_lib(void)
{
	signal(SIGINT, (void*)sig_handler);

	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi : %s\n",
			strerror(errno));
		return 1;
	}

	pinMode(PUMP, OUTPUT);


	{
		printf("here - pump on\n");
		digitalWrite(PUMP, 1);
		delay(2000);//2second

		digitalWrite(PUMP, 0);
		delay(2000);
	}
	return 0;
}
void sig_handler(int signo)
{
	printf("process stop\n");
	digitalWrite(PUMP, 0);
	exit(0);
}


------------LED----------------
#pragma warning(disable :4996)
#include <signal.h> 
#include <unistd.h>
#include <stdio.h> 
#include <string.h> 
#include <errno.h>
#include <stdlib.h> 

#include <wiringPi.h>

#define RGBLEDPOWER  24 

#define RED	8 //27
#define GREEN	7 //28
#define BLUE	9 //29

void sig_handler(int signo);

int rgbon_lib(void)
{
	signal(SIGINT, (void*)sig_handler);

	if (wiringPiSetup() == -1)
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1;
	}

	pinMode(RGBLEDPOWER, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);

	int i;

	for (i = 0; i < 10; i++)
	{

		digitalWrite(RGBLEDPOWER, 1);

		digitalWrite(RED, 1);
		digitalWrite(BLUE, 0);
		digitalWrite(GREEN, 0);

		delay(3000); //3second

		digitalWrite(RED, 0);
		digitalWrite(BLUE, 1);
		digitalWrite(GREEN, 0);

		delay(1000); //1second

		digitalWrite(RED, 0);
		digitalWrite(BLUE, 0);
		digitalWrite(GREEN, 1);

		delay(1000);
	}
	digitalWrite(GREEN, 0);
	return 0;
}

void sig_handler(int signo)
{
	printf("process stop\n");

	digitalWrite(RED, 0);
	digitalWrite(GREEN, 0);
	digitalWrite(BLUE, 0);
	digitalWrite(RGBLEDPOWER, 0); //Off

	exit(0);
}