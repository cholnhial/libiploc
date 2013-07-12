
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <json/json.h>

#include <iploc/iploc.h>

#define MAX_URL_SIZE 2048
#define DATA_BUF_SIZE 1024
#define URLTEMPLATE "http://dazzlepod.com/ip/%s.json"

static size_t http_callback(char* ptr,
                            size_t count, 
                            size_t blocksize,
                            void* userdata)
{
    iploc_resp* response = userdata;
    size_t size = count * blocksize;
    memcpy(response->data + response->length, ptr, size);
    response->length += size;

    return size;
}

IPLOC* iploc_get_geoinfo(const char* host)
{   
    IPLOC* iploc_p = (IPLOC*) malloc(sizeof(IPLOC));
    if (!iploc_p) {
        return NULL;
    }
    
    /* Response stuff */
    iploc_resp* resp = (iploc_resp*) malloc(sizeof(iploc_resp));
    if (!resp) {
        free(iploc_p);
        return NULL;
    }
    resp->data = (char*) malloc(DATA_BUF_SIZE);
    if (!resp->data) {
        free(iploc_p);
        free(resp);
        return NULL;
    }
    resp->length = 0;

    char* url = (char*) malloc(MAX_URL_SIZE);
    if (!url) {
        free(resp->data);
        free(resp);
        free(iploc_p);
        return NULL;
    }

    /* Create a complete url */
    sprintf(url, URLTEMPLATE, host);
  
    /* Initialize curl */
     if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
        free(resp->data);
        free(resp);
        free(url);
        free(iploc_p);
        return NULL;
    }
    
    CURL *curl_hndl = curl_easy_init();
    if (!curl_hndl) {
        free(resp->data);
        free(resp);
        free(url);
        free(iploc_p);
        return NULL;
    }

    curl_easy_setopt(curl_hndl, CURLOPT_URL, url);
    curl_easy_setopt(curl_hndl, CURLOPT_WRITEFUNCTION, http_callback);
    curl_easy_setopt(curl_hndl, CURLOPT_WRITEDATA, resp);
    
    int res = curl_easy_perform(curl_hndl);
    if (res != CURLE_OK) {
        free(resp->data);
        free(resp);
        free(url);
        free(iploc_p);
        curl_easy_cleanup(curl_hndl);
        return NULL;
    }
    
    #ifdef DEBUG
        printf("%s\n", resp->data);
    #endif

    if (json_parse_resp(iploc_p, resp->data) == -1) {
        free(resp->data);
        free(resp);
        free(url);
        free(iploc_p);
        curl_easy_cleanup(curl_hndl);
        return NULL;
    }
    
    /* clean up */
     free(resp->data);
     free(resp);
     free(url);
     curl_easy_cleanup(curl_hndl);

    return iploc_p;
  
}

void iploc_free(IPLOC* iploc_p)
{
    free(iploc_p->ip);
    free(iploc_p->isp);
    free(iploc_p->country);
    free(iploc_p->region);
    free(iploc_p->city);
    free(iploc_p->organization);
    free(iploc_p->hostname);

    free(iploc_p);
}
/**********************************
 *  Helper functions definitions  *
 *                                *
 *  *******************************/

static int json_parse_resp(IPLOC* iploc_p, const char* json_data)
{
    if (!iploc_p && !json_data) {
        return -1;
    }

    json_object* jobj;
    json_object* jobj_extract;

    jobj = json_tokener_parse(json_data);
    if (!jobj) {
        return -1;
    } 

    /** check if error, might be wrong hostname/ip **/
    jobj_extract = json_object_object_get(jobj, "error");
    if (json_object_get_string(jobj_extract)) {
        return -1;
    }

    /* Get all the geoinfo data */
    jobj_extract = json_object_object_get(jobj, "country");
    iploc_p->country = strdup(json_object_get_string(jobj_extract));    
    jobj_extract = json_object_object_get(jobj, "city");
    iploc_p->city = strdup(json_object_get_string(jobj_extract));
    jobj_extract = json_object_object_get(jobj, "isp");
    iploc_p->isp = strdup(json_object_get_string(jobj_extract));
    jobj_extract = json_object_object_get(jobj, "organization");
    iploc_p->organization = strdup(json_object_get_string(jobj_extract));
    jobj_extract = json_object_object_get(jobj, "latitude");
    iploc_p->latitude = json_object_get_double(jobj_extract);
    jobj_extract = json_object_object_get(jobj, "ip");
    iploc_p->ip = strdup(json_object_get_string(jobj_extract));
    jobj_extract = json_object_object_get(jobj, "region");
    iploc_p->region = strdup(json_object_get_string(jobj_extract));
    jobj_extract = json_object_object_get(jobj, "hostname");
    iploc_p->hostname  = strdup(json_object_get_string(jobj_extract));
    jobj_extract = json_object_object_get(jobj, "longitude");
    iploc_p->longtitude = json_object_get_double(jobj_extract);
    
    
    return 0;
}
