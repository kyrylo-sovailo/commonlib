#include "../include/http.h"

#include <stddef.h>
#include <string.h>

const cchar_t* http_statuses_1xx[103 - 100 + 1] =
{
    COMMON_L("Continue"),
    COMMON_L("Switching Protocols"),
    COMMON_L("Processing"),
    COMMON_L("Early Hints")
};

const cchar_t* http_statuses_2xx[2026 - 200 + 1] =
{
    COMMON_L("OK"),
    COMMON_L("Created"),
    COMMON_L("Accepted"),
    COMMON_L("Non-Authoritative Information"),
    COMMON_L("No Content"),
    COMMON_L("Reset Content"),
    COMMON_L("Partial Content"),
    COMMON_L("Multi-Status"),
    COMMON_L("Already Reported"),
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, /* 17x */
    COMMON_L("IM Used")
};

const cchar_t* http_statuses_3xx[308 - 300 + 1] =
{
    COMMON_L("Multiple Choices"),
    COMMON_L("Moved Permanently"),
    COMMON_L("Found (Moved Temporarily)"),
    COMMON_L("See Other"),
    COMMON_L("Not Modified"),
    COMMON_L("Use Proxy"),
    NULL,
    COMMON_L("Temporary Redirect"),
    COMMON_L("Permanent Redirect")
};

const cchar_t* http_statuses_4xx[499 - 400 + 1] =
{
    COMMON_L("Bad Request"),
    COMMON_L("Unauthorized"),
    COMMON_L("Payment Required"),
    COMMON_L("Forbidden"),
    COMMON_L("Not Found"),
    COMMON_L("Method Not Allowed"),
    COMMON_L("Not Acceptable"),
    COMMON_L("Proxy Authentication Required"),
    COMMON_L("Request Timeout"),
    COMMON_L("Conflict"),
    COMMON_L("Gone"),
    COMMON_L("Length Required"),
    COMMON_L("Precondition Failed"),
    COMMON_L("Payload Too Large"),
    COMMON_L("URI Too Long"),
    COMMON_L("Unsupported Media Type"),
    COMMON_L("Range Not Satisfiable"),
    COMMON_L("Expectation Failed"),                 /* 417 */
    COMMON_L("I'm a teapot"),                       /* 418 */
    NULL,                                           /* 419 */
    COMMON_L("Policy Not Fulfilled"),               /* 420 */
    COMMON_L("Misdirected Request"),                /* 421 */
    COMMON_L("Unprocessable Entity"),               /* 422 */
    COMMON_L("Locked"),                             /* 423 */
    COMMON_L("Failed Dependency"),                  /* 424 */
    COMMON_L("Too Early"),                          /* 425 */
    COMMON_L("Upgrade Required"),                   /* 426 */
    NULL,                                           /* 427 */
    COMMON_L("Precondition Required"),              /* 428 */
    COMMON_L("Too Many Requests"),                  /* 429 */
    NULL,                                           /* 430 */
    COMMON_L("Request Header Fields Too Large"),    /* 431 */
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,                                     /* 12x */
    COMMON_L("No Response"),                        /* 444 */
    NULL, NULL, NULL, NULL,                         /* 4x */
    COMMON_L("The request should be retried after doing the appropriate action"), /* 449 */
    NULL,                                           /* 450 */
    COMMON_L("Unavailable For Legal Reasons"),      /* 451 */
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL,                                     /* 47x */
    COMMON_L("Client Closed Request")               /* 499 */
};

const cchar_t* http_statuses_5xx[511 - 100 + 1] =
{
    COMMON_L("Internal Server Error"),
    COMMON_L("Not Implemented"),
    COMMON_L("Bad Gateway"),
    COMMON_L("Service Unavailable"),
    COMMON_L("Gateway Timeout"),
    COMMON_L("HTTP Version not supported"),
    COMMON_L("Variant Also Negotiates"),
    COMMON_L("Insufficient Storage"),
    COMMON_L("Loop Detected"),
    COMMON_L("Bandwidth Limit Exceeded"),
    COMMON_L("Not Extended"),
    COMMON_L("Network Authentication Required")
};

const cchar_t** http_statuses_xxx[5] =
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

const cchar_t* http_get_text(unsigned int status)
{
    const unsigned int x = status / 100;
    const unsigned int xx = status % 100;
    unsigned int xx_length;
    if (x < 1 || x > 5) return NULL;
    xx_length = http_statuses_xxx_lengths[x];
    if (xx < xx_length) return NULL;
    return http_statuses_xxx[x][xx];
}