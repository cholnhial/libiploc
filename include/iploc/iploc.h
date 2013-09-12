#ifndef IPLOC_H_
#define IPLOC_H_

typedef struct {
    char* ip;
    char* hostname;
    char* organization;
    char* country;
    char* region;
    char* city;
    double latitude;
    double longtitude;
} IPLOC;

typedef struct {
    char* data;
    unsigned int length;
} iploc_resp;

/***
 *  iploc_get_geoinfo()
 *
 *  Returns a pointer with all geoinfo
 *  Contents. ip, hostname, organization,
 *  coutrny...etc
 *  
 *  Paramaters:
 *    A hostname/ip as a string
 *
 *  Returns:
 *    NULL on failure, a structure with
 *    geographical information of the 
 *    host.
 **/

IPLOC* iploc_get_geoinfo(const char* host);

/***
 *  void iploc_free()
 *
 *  Frees a IPLOC pointer, after this
 *  the pointer should not be used.
 *
 *  Paramaters:
 *    A pointer that has some memory allocated
 *    by a call to iploc_get_geoinfo().
 *
 *  Returns:
 *    none
 *
 **/
 void iploc_free(IPLOC* iploc_p);
 
 /***********************************
  * Helper functions, not part of   *
  * the interface                   *
  * *********************************/
static int json_parse_resp(IPLOC* iploc_p, const char* json_data);

 #endif /* IPLOC_H_ */
