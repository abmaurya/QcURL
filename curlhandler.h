#ifndef CURLHANDLER_H
#define CURLHANDLER_H

#include<string>

class CurlHandler
{
public:
    CurlHandler();
    ~CurlHandler();
    std::string SendData(bool redirection, bool verbose, std::string url, long portNumber, std::string customAgent = "");
};

#endif // CURLHANDLER_H
