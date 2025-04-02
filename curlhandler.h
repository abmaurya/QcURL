#ifndef CURLHANDLER_H
#define CURLHANDLER_H

#include<string>

struct CurlOptions
{
    bool Redirection;
    bool Verbose;
    bool Post;
    long PortNumber;
    std::string Url;
    std::string PostData;
    std::string CustomAgent;
};

class CurlHandler
{
public:
    CurlHandler();
    ~CurlHandler();
    std::string SendData(CurlOptions curlOp);
};

#endif // CURLHANDLER_H
