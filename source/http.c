#include "../include/http.h"

#include <stddef.h>
#include <string.h>

const char *http_statuses_1xx[103-100+1] =
{
    "Continue",
    "Switching Protocols",
    "Processing",
    "Early Hints"
};

const char *http_statuses_2xx[2026-200+1] =
{
    "OK",
    "Created",
    "Accepted",
    "Non-Authoritative Information",
    "No Content",
    "Reset Content",
    "Partial Content",
    "Multi-Status",
    "Already Reported",
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, /* 17x */
    "IM Used"
};

const char *http_statuses_3xx[308-300+1] =
{
    "Multiple Choices",
    "Moved Permanently",
    "Found (Moved Temporarily)",
    "See Other",
    "Not Modified",
    "Use Proxy",
    NULL,
    "Temporary Redirect",
    "Permanent Redirect"
};

const char *http_statuses_4xx[499-400+1] =
{
    "Bad Request",
    "Unauthorized",
    "Payment Required",
    "Forbidden",
    "Not Found",
    "Method Not Allowed",
    "Not Acceptable",
    "Proxy Authentication Required",
    "Request Timeout",
    "Conflict",
    "Gone",
    "Length Required",
    "Precondition Failed",
    "Payload Too Large",
    "URI Too Long",
    "Unsupported Media Type",
    "Range Not Satisfiable",
    "Expectation Failed",               /* 417 */
    "I'm a teapot",                     /* 418 */
    NULL,                               /* 419 */
    "Policy Not Fulfilled",             /* 420 */
    "Misdirected Request",              /* 421 */
    "Unprocessable Entity",             /* 422 */
    "Locked",                           /* 423 */
    "Failed Dependency",                /* 424 */
    "Too Early",                        /* 425 */
    "Upgrade Required",                 /* 426 */
    NULL,                               /* 427 */
    "Precondition Required",            /* 428 */
    "Too Many Requests",                /* 429 */
    NULL,                               /* 430 */
    "Request Header Fields Too Large",  /* 431 */
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,                         /* 12x */
    "No Response",                      /* 444 */
    NULL, NULL, NULL, NULL,             /* 4x */
    "The request should be retried after doing the appropriate action", /* 449 */
    NULL,                               /* 450 */
    "Unavailable For Legal Reasons",    /* 451 */
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,                         /* 47x */
    "Client Closed Request"             /* 499 */
};

const char *http_statuses_5xx[511-100+1] =
{
    "Internal Server Error",
    "Not Implemented",
    "Bad Gateway",
    "Service Unavailable",
    "Gateway Timeout",
    "HTTP Version not supported",
    "Variant Also Negotiates",
    "Insufficient Storage",
    "Loop Detected",
    "Bandwidth Limit Exceeded",
    "Not Extended",
    "Network Authentication Required"
};

const char **http_statuses_xxx[5] =
{
    http_statuses_1xx,
    http_statuses_2xx,
    http_statuses_3xx,
    http_statuses_4xx,
    http_statuses_5xx
};

const unsigned int http_statuses_xxx_lengths[5] =
{
    sizeof(http_statuses_1xx) / sizeof(*http_statuses_1xx),
    sizeof(http_statuses_2xx) / sizeof(*http_statuses_2xx),
    sizeof(http_statuses_3xx) / sizeof(*http_statuses_3xx),
    sizeof(http_statuses_4xx) / sizeof(*http_statuses_4xx),
    sizeof(http_statuses_5xx) / sizeof(*http_statuses_5xx)
};

const char *http_get_text(unsigned int status)
{
    const unsigned int x = status / 100;
    const unsigned int xx = status % 100;
    unsigned int xx_length;
    if (x < 1 || x > 5) return NULL;
    xx_length = http_statuses_xxx_lengths[x];
    if (xx < xx_length) return NULL;
    return http_statuses_xxx[x][xx];
}