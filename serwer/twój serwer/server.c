#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h> 

#include "listuj.h"

char myhostname[1024];

struct sockaddr_in soc;

int main() 
{

int i;
char file[26];
char ip [16];

  int sdServerSocket, sdConnection, retval;
  socklen_t sin_size;
  struct sockaddr_in incoming;
  struct hostent *heLocalHost;

  sin_size = sizeof(struct sockaddr_in);

  sdServerSocket = socket(PF_INET, SOCK_STREAM, 0);
  gethostname(myhostname, 1023);
  heLocalHost = gethostbyname(myhostname);

  struct stat st = {0};
  struct dirent *de;

  soc.sin_family = AF_INET;
  soc.sin_port = htons(5009);
  soc.sin_addr = *(struct in_addr*) 
  heLocalHost->h_addr;
  memset(&(soc.sin_zero),0,8);
  char nazwa [20];

  char ok = 'k';
  char nope = 'n';

  char name [15];

  char signal;

  char buffor [1024];

  char rozmiar [10];

FILE *pic;
DIR *dir;
DIR *di;
FILE *f;
FILE *g;
//tworzenie plików
  if (stat("./serv", &st) == -1) 
  {
    mkdir("./serv", 0777);
    if (stat("./serv/pom", &st) == -1) 
    {
        mkdir("./serv/pom", 0777);
    }
  }
//tworzednie plików

  printf("slucham na %s : %d\n",
  inet_ntoa(soc.sin_addr),
  ntohs(soc.sin_port));

  retval = bind(sdServerSocket, (struct sockaddr*) &soc, sizeof(struct sockaddr));
  if (retval < 0) 
  {
    printf("bind nie powiodl sie\n");
    return 1;
  }

  listen(sdServerSocket, 10);

  while ((sdConnection = accept(sdServerSocket, (struct sockaddr*) &incoming, &sin_size)) > 0) 
  {
    printf("Polaczenie z %s:%d\n",
    inet_ntoa(incoming.sin_addr),
    ntohs(incoming.sin_port));

if(fork == 0 ){
    if (recv(sdConnection, &signal, sizeof(signal), 0) != sizeof(signal))
    {
        printf("pierwszy recv nie powiodl sie. \n");
        close(sdConnection);
        continue;
    }
    memset(nazwa, 0 , sizeof(nazwa));
    memset(name, 0, sizeof(name));
    memset(buffor, 0, sizeof(buffor));

    switch(signal){
//wysłanie pliku na serwer
    case 'a':

//wyślij nazwę
    if (recv(sdConnection, &name, sizeof(name), 0) <= 0)
    {
        printf("recv 2.1 sie nie powiodl %s \n", name);
        close(sdConnection);
        send(sdConnection, &nope, sizeof(char), 0);
    }
    else
    {
printf("%s \n", name);
//tworzenie pliku pomocniczego
        sprintf(nazwa, "./serv/pom/%s", name);
            pic = fopen(nazwa, "r");
        if (pic == NULL)
        {
            pic = fopen(nazwa, "a+");
        }
        else
        {
            int o = strcmp(fgets(ip, 16, pic), inet_ntoa(incoming.sin_addr));
            if (o ==1)
            {
                char d = 'd';
                send(sdConnection, &d, sizeof(char), 0);
                close(sdConnection);
            }
        }
        fprintf(pic, "%s", inet_ntoa(incoming.sin_addr));
        fclose(pic);
//tworzenie po prostu pliku
        sprintf(nazwa, "./serv/%s", name);
            pic = fopen(nazwa, "w+");
        if (pic == NULL)
        {
            pic = fopen(nazwa, "a+");
        }

        
//wysyłamy potwierdzenie
            send(sdConnection, &ok, sizeof(char), 0);
    }
//rozmiar
memset(rozmiar, 0, sizeof(rozmiar));
recv(sdConnection, &rozmiar, sizeof(rozmiar), 0);
send(sdConnection, &ok, sizeof(char), 0);
char *ptr;
long roz;
roz = strtol(rozmiar, &ptr, 10);
//wyślij plik
    while(roz > 0)
    {
         if (recv(sdConnection, &buffor, sizeof(buffor), 0) == 0)
         {
             printf("recv 2.3 sie nie powiodl \n");
            send(sdConnection, &nope, sizeof(char), 0);

         }
         else
        {
            fprintf(pic, "%s", buffor);
            roz = roz - 1024;
            send(sdConnection, &ok, sizeof(char), 0);
        }
    memset(buffor, 0, sizeof(buffor));
    }
roz = 0;
//!= sizeof(buffor)
close(sdConnection);
fclose(pic);
printf("ok \n");
//do listy
 di = opendir("./serv/pom");
 f = fopen("./serv/pom/list", "w");
while ((de = readdir(di)) != NULL) 
{
    char *name;
    name = de->d_name;
    size_t len = strlen(name);
        if((strcmp( name + len - 4,".txt") == 0))

        {
            sprintf(file, "./serv/pom/%s", name);
            g = fopen( file, "r");
            fgets( ip, 16, g);
            fclose(g);
            fprintf(f, "%s %s\n", name, ip);

        }
}
    fclose(f);
	closedir(di);	
printf("Done! \n");
        close(sdConnection);
    break;
// wylistowanie plików
    case 'b': 
        pic = fopen("./serv/pom/list", "r");
                fseek(pic, 0L, SEEK_END);
                long int size = ftell(pic);
                fseek(pic, 0L, SEEK_SET);
 
        while(size > 0)
        {
            int przeczytano = fread(&buffor, 1, 1024, pic);
            int wyslano = send(sdConnection, &buffor, przeczytano, 0);
            size = size - przeczytano;
            if (przeczytano != wyslano)
            {
                printf("error break \n");
                break;
            }
            
        }
        fclose(pic);
        close(sdConnection);
        break;

// odczyt plików z serwera

    case 'c': 
    if (recv(sdConnection, &nazwa, sizeof(nazwa) , 0) <= sizeof(nazwa))
    {           
        dir = opendir("./serv");
        while ((de = readdir(dir)) != NULL) 
        {   
            char *name;
            name = de->d_name;
            int fool = strcmp(name,nazwa);
            if (fool == 0)
            {
                sprintf(nazwa, "./serv/%s", name);
                pic = fopen(nazwa, "r");
                fseek(pic, 0L, SEEK_END);
                long int size = ftell(pic);
                fseek(pic, 0L, SEEK_SET);
                while(size>0)
                {
                    int przeczytano = fread(buffor, 1, 1024, pic);
                    printf("przeczytano: %d \nsizeof(pic): %ld \n", przeczytano, size);
                    int wyslano = send(sdConnection, buffor, przeczytano, 0);
                    size = size - przeczytano;
                        printf("przeczytano %d \nwysłaono %d \n", przeczytano, wyslano);
                    if (przeczytano != wyslano)
                    {
                        printf("error break \n");
                        break;
                    }
                }
            fclose(pic);
            printf("Wysłano plik \n");
            close(sdConnection);
            break;
            }
        }
    }
    else 
    {
        printf("drugi recv nie powiodl sie. \n");
        close(sdConnection);
        continue;
    }
    close(sdConnection);
    break;

    default: 
        close(sdConnection);
        break;
}

close(sdConnection);
}
}

return 0;
}
