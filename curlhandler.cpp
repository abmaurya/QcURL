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

std::string CurlHandler::SendData(CurlOptions curlOp)
{
    try
    {
        // Our request to be sent.
        curlpp::Easy myRequest;

        //Set Redirection
        myRequest.setOpt<FollowLocation>(curlOp.Redirection);

        myRequest.setOpt<Verbose>(curlOp.Verbose);

        //Adding Custom User-Agent, if given
        myRequest.setOpt<UserAgent>(curlOp.CustomAgent);

        if(curlOp.Post)
        {
            myRequest.setOpt<Post>(curlOp.Post);
            myRequest.setOpt<PostFields>(curlOp.PostData);
        }
        //Set the port
        if(curlOp.Url.find("http") == std::string::npos)
        {
            myRequest.setOpt<Port>(curlOp.PortNumber);
        }
        // Set the URL.
        myRequest.setOpt<Url>(curlOp.Url);
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
