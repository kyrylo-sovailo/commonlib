#ifndef HTTP_H
#define HTTP_H

extern const char *http_statuses_1xx[103-100+1];
extern const char *http_statuses_2xx[2026-200+1];
extern const char *http_statuses_3xx[308-300+1];
extern const char *http_statuses_4xx[499-400+1];
extern const char *http_statuses_5xx[511-100+1];
extern const char **http_statuses_xxx[5];
extern const unsigned int http_statuses_xxx_lengths[5];

const char *http_get_text(unsigned int status);

#endif
