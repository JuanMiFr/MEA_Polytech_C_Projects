/*
 * main.c
 *
 *  Created on: 27 déc. 2023
 *      Author: test
 */
#include <stdio.h>
#include <string.h>

typedef struct
{
	unsigned char id;
	unsigned char humidity;
	unsigned short int temperature;
	unsigned short int pressure;
} wdata_t;
char b64 [64]={
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9','+','/',
};

void struct_to_table(wdata_t* wdata, unsigned char* t)
		{
			t[0]=(wdata->id);
			t[1]=(wdata->humidity);
			unsigned char msb=0;
			unsigned char lsb=0;
			unsigned short int number=0;
			number=(wdata->temperature);
			lsb=(char)number;
			msb=(char)(number>>8);
			t[2]=msb;
			t[3]=lsb;
			number=wdata->pressure;
			lsb=(char)number;
			msb=(char)(number>>8);
			t[4]=msb;
			t[5]=lsb;
		}
void table_to_struct(wdata_t* wdata, unsigned char* t)
		{
			(wdata->id)=t[0];
			(wdata->humidity)=t[1];
			unsigned char msb=0;
			unsigned char lsb=0;
			unsigned short int number=0;
			lsb=t[2];
			msb=t[3];
			number=(256*msb)+lsb;
			(wdata->temperature)=number;
			msb=t[4];
			lsb=t[5];
			number=(256*msb)+lsb;
			(wdata->pressure)=number;
		}

void b64_encode (wdata_t* wdata,unsigned char* msg)
		{
			unsigned char t[6];
			struct_to_table(wdata,t);
			unsigned int tab[2];
			tab[0]=0;
			tab[1]=0;
			int n=2;
				for (int j=0;j<3;j++)
					{
						tab[0]+=(unsigned int)(t[j]<<n*8);
						n--;
					}
			n=2;
				for (int k=3;k<6;k++)
					{
						tab[1]+=(unsigned int)(t[k]<<n*8);
						n--;
					}
				/*
				msg[0]=(char)(tab[0]>>18);
				msg[1]=(char)(tab[0]>>12);
				msg[2]=(char)(tab[0]>>6);
				msg[3]=(char)(tab[0]&63);
				msg[4]=(char)(tab[1]>>18);// manera sin boucle
				msg[5]=(char)(tab[1]>>12);
				msg[6]=(char)(tab[1]>>6);
				msg[7]=(char)(tab[1]&63);
				*/
				n=3;
				for (int i=0;i<2;i++)
				{
					if(i==0)
					{
					for (int p=0;p<4;p++)
						{
							if (p==3)
								{
									msg[p]=tab[i]&63;
									p++;
								}
							if(p!=3)
							{
								msg[p]=tab[i]>>6*n;
								n--;
							}
						}
					}else
					{
						n=3;
						for (int t=4;t<8;t++)
						{
							if (t==7)
							{
								msg[t]=tab[i]&63;
							}
							if (t!=7)
							{
								msg[t]=tab[i]>>6*n;
								n--;
							}
						}
					}
				}
		}

unsigned char b64_val(unsigned char c)
{
	for (int i=0;i<64;i++)
	{
		if (b64[i]==c)
		{
			return (char)i;

		}
	}
}

void msg_codé (unsigned char* msg)
{
	printf("|");
	int jeje=0;
	for (int i=0;i<8;i++)
	{
		jeje=(int)b64_val(msg[i]);
//		msg[i]=(char)b64_val(msg[i]);//no sé que hice
		printf("%c",b64[jeje]);
	}
	printf("|    fin du message codé");
}

void b64_decode(unsigned char* msg, wdata_t* wdata)
{
	//char tab[8];
	//	for (int i=0;i<8;i++)
	//{
	//	tab[i]=(int)b64_val(msg[i]);
	//}
		int t[2];
		t[0]=0;
		t[1]=0;
		t[0]+=msg[0]<<18;
		t[0]+=msg[1]<<12;
		t[0]+=msg[2]<<6;
		t[0]+=msg[3];
		t[1]+=msg[4]<<18;
		t[1]+=msg[5]<<12;
		t[1]+=msg[6]<<6;
		t[1]+=msg[7];

		unsigned char tchar[6];

		for (int j=0;j<3;j++)
						{
							tchar[0]=(char)(t[j]>>n*8);
							n--;
						}
				n=2;
					for (int k=3;k<6;k++)
						{
							tchar[1]=(char)(t[k]>>n*8);
							n--;
						}
			table_to_struct(t,wdata);

		unsigned char t[6];

int main (void)
{
	wdata_t hola;
	hola.id=1;
	hola.humidity=65;
	hola.temperature=19600;
	hola.pressure=1050;
	unsigned char t[6];
	struct_to_table(&hola,t);
	for (int i=0;i<6;i++)
		{
			printf("%d\n",t[i]);
		}
	unsigned int number=(unsigned int)(t[4]<<8);
	number|=(unsigned int)t[5];
	printf("%d",number);
	unsigned char msg[8];
	b64_encode (&hola,msg);
	printf("\n");
	for (int i=0;i<8;i++)
		{
			printf("%d",msg[i]);
		}
	char jeje=b64_val('a');
	printf("\n %d",jeje);
	msg_codé (msg);
	return 0;
}
