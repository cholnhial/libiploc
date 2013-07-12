#include <stdio.h>
#include <stdlib.h>
#include <iploc/iploc.h>

void show_ip_info(const IPLOC* iploc_p)
{
    printf("IP: %s\n", iploc_p->ip);
    printf("Hostname: %s\n", iploc_p->hostname);
    printf("ISP: %s\n", iploc_p->isp);
    printf("Organization: %s\n", iploc_p->organization);
    printf("Country: %s\n", iploc_p->country);
    printf("Region: %s\n", iploc_p->region);
    printf("City: %s\n", iploc_p->city);
    printf("Latitude: %.4f\n", iploc_p->latitude);
    printf("Longtitude: %.4f\n", iploc_p->longtitude);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Usage: %s <hostname/ip>\n", argv[0]);
        
        exit(EXIT_FAILURE);
    }

    IPLOC* ipinfo = iploc_get_geoinfo(argv[1]);
    
    if (!ipinfo) {
        printf("Unable to lookup host\n");
        exit(EXIT_FAILURE);
    }

    show_ip_info(ipinfo);
    
    return 0;
}
