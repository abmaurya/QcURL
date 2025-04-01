#include "curlhandler.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <QDebug>

using namespace curlpp::options;

CurlHandler::CurlHandler()
{
    curlpp::initialize();
}

CurlHandler::~CurlHandler()
{
    curlpp::terminate();
}

std::string CurlHandler::SendData(bool redirection, bool verbose, std::string url, long portNumber, std::string customAgent)
{
    try
    {
        // Our request to be sent.
        curlpp::Easy myRequest;

        //Set Redirection
        myRequest.setOpt<FollowLocation>(redirection);

        myRequest.setOpt<Verbose>(verbose);

        //Adding Custom User-Agent, if given
        myRequest.setOpt<UserAgent>(customAgent);

        //Set the port
        myRequest.setOpt<Port>(portNumber);
        // Set the URL.
        myRequest.setOpt<Url>(url);

        std::stringstream ss;
        // Send request and get a result in stringstream.
        //NOTE: Accessing the ostream operator (<<) from
        ss<<myRequest;
        return ss.str();
    }

    catch(curlpp::RuntimeError & e)
    {
        qDebug() << e.what();
    }

    catch(curlpp::LogicError & e)
    {
        qDebug() << e.what();
    }
    return "";
}
