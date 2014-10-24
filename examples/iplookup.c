#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iploc/iploc.h>

#define INET6_ADDRSTRLEN 48
const char* TERM_LINE_FMT =   "\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%10s\e[0m"
					  		  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%10s\e[0m"
							  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%10s\e[0m"
							  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%10s\e[0m"
							  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%10s\e[0m"
							  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%10s\e[0m"
							  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%.4f\e[0m"
							  "	\e[0;32m\033[1m%s\033[0m\e[0m\e[0;33m%.4f\e[0m\n";

void show_ip_info(const IPLOC* iploc_p)
{
    printf("IP: %s\n", iploc_p->ip);
    printf("Hostname: %s\n", iploc_p->hostname);
    printf("Organization: %s\n", iploc_p->organization);
    printf("Country: %s\n", iploc_p->country);
    printf("Region: %s\n", iploc_p->region);
    printf("City: %s\n", iploc_p->city);
    printf("Latitude: %.4f\n", iploc_p->latitude);
    printf("Longtitude: %.4f\n", iploc_p->longtitude);
}

void show_ip_info_line(const IPLOC* iploc_p)
{	
    printf( 
    		TERM_LINE_FMT, 
    	 	"IP: ", 
        	iploc_p->ip,
        	"Hostname: ",
        	iploc_p->hostname,
        	"Organisation: ",
        	iploc_p->organization,
        	"Country: ",
        	iploc_p->country,
        	"Region: ",
        	iploc_p->region,
        	"City: ",
        	iploc_p->city,
        	"Latitude: ",
        	iploc_p->latitude,
        	"Longtitude: ",
        	iploc_p->longtitude
        	);

}

int main(int argc, char** argv)
{
    if (argc == 2) 
    {

        IPLOC* ipinfo = iploc_get_geoinfo(argv[1]);
    
         if (!ipinfo) {
            printf("Unable to lookup host\n");
            exit(EXIT_FAILURE);
         }

        show_ip_info(ipinfo);
    } 
    else 
    {
        char ip_address[INET6_ADDRSTRLEN];
        
        /* Read IP */
        fgets(ip_address, INET6_ADDRSTRLEN - 1, stdin);
        /* Remove newline if any */
        if(ip_address[strlen(ip_address) - 1] == '\n')
        {
            ip_address[strlen(ip_address) -1] = '\0';
        }

        /* Look up IP */
        IPLOC* ipinfo = iploc_get_geoinfo(ip_address);

        /* Display info in line*/
        if(ipinfo != NULL)
        {
            show_ip_info_line(ipinfo);

            /* Clean up */
            iploc_free(ipinfo);
        }
    }

    
    
    return 0;
}
