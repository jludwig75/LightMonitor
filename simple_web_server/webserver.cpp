/*
   WebServer.cpp

   Copyright (C) 2003-2004 Ren� Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   Ren� Nyffenegger rene.nyffenegger@adp-gmbh.ch

   Thanks to Tom Lynn who pointed out an error in this source code.
*/

#include <ctime>
#include <process.h>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
//<process.h>


#include "webserver.h"
#include "UrlHelper.h"
#include "base64.h"

webserver::request_func webserver::request_func_=0;

unsigned webserver::Request(Socket* s) {
  std::string line = s->ReceiveLine();
  if (line.empty()) {
    return 1;
  }

  http_request req;

  size_t methodLength = 0;

  std::string firstLine = line.substr(0, line.length()-2);

  if (line.find("GET") == 0) {
    req.method_="GET";
	methodLength = 3;
  }
  else if (line.find("POST") == 0) {
    req.method_="POST";
	methodLength = 4;
  }

  std::string path;
  std::map<std::string, std::string> params;

  size_t posStartPath = line.find_first_not_of(" ", methodLength);

  SplitGetReq(line.substr(posStartPath), path, params);

  req.status_ = "202 OK";
  req.s_      = s;
  req.path_   = path;
  req.params_ = params;

  static const std::string authorization   = "Authorization: Basic ";
  static const std::string accept          = "Accept: "             ;
  static const std::string accept_language = "Accept-Language: "    ;
  static const std::string accept_encoding = "Accept-Encoding: "    ;
  static const std::string user_agent      = "User-Agent: "         ;
  static const std::string content_length  = "Content-Length: ";

  int contentLength = 0;

  while(1) {
    line=s->ReceiveLine();

    if (line.empty()) break;

    unsigned int pos_cr_lf = line.find_first_of("\x0a\x0d");
    if (pos_cr_lf == 0) break;

    line = line.substr(0,pos_cr_lf);

    if (line.substr(0, authorization.size()) == authorization) {
      req.authentication_given_ = true;
      std::string encoded = line.substr(authorization.size());
      std::string decoded = base64_decode(encoded);

      unsigned int pos_colon = decoded.find(":");

      req.username_ = decoded.substr(0, pos_colon);
      req.password_ = decoded.substr(pos_colon+1 );
    }
    else if (line.substr(0, accept.size()) == accept) {
      req.accept_ = line.substr(accept.size());
    }
    else if (line.substr(0, accept_language.size()) == accept_language) {
      req.accept_language_ = line.substr(accept_language.size());
    }
    else if (line.substr(0, accept_encoding.size()) == accept_encoding) {
      req.accept_encoding_ = line.substr(accept_encoding.size());
    }
    else if (line.substr(0, user_agent.size()) == user_agent) {
      req.user_agent_ = line.substr(user_agent.size());
    }
	else if (line.substr(0, content_length.size()) == content_length) {
		contentLength = atoi(line.substr(content_length.size()).c_str());
		printf("Content-Length: %d\n", contentLength);
	}
  }

  if (req.method_ == "POST" && contentLength > 0)
  {
	  line = "";
	  while (line.length() < (size_t)contentLength)
	  {
		  line += s->ReceiveBytes();
	  }
	  printf("Content body: \"%s\"\n", line.c_str());
	  line = req.method_ + " " + req.path_ + "?" + line;
	  SplitGetReq(line.substr(posStartPath), path, params);
	  req.params_ = params;
  }

  request_func_(&req);

  std::stringstream str_str;
  str_str << req.answer_.size();

  time_t ltime;
  time(&ltime);
  tm* gmt= gmtime(&ltime);

  static std::string const serverName = "RenesWebserver (Windows)";

  char* asctime_remove_nl = asctime(gmt);
  asctime_remove_nl[24] = 0;

  s->SendBytes("HTTP/1.1 ");

  if (! req.auth_realm_.empty() ) {
    s->SendLine("401 Unauthorized");
    s->SendBytes("WWW-Authenticate: Basic Realm=\"");
    s->SendBytes(req.auth_realm_);
    s->SendLine("\"");
  }
  else {
    s->SendLine(req.status_);
  }
  s->SendLine(std::string("Date: ") + asctime_remove_nl + " GMT");
  s->SendLine(std::string("Server: ") +serverName);
  s->SendLine("Connection: close");
  s->SendLine("Content-Type: text/html; charset=ISO-8859-1");
  s->SendLine("Content-Length: " + str_str.str());
  if (!req.responseHeaders_.empty())
  {
	  s->SendBytes(req.responseHeaders_.c_str());
  }
  s->SendLine("");
  s->SendLine(req.answer_);

  s->Close();

  delete s;

  return 0;
}

webserver::webserver(unsigned int port_to_listen, request_func r) : _in(port_to_listen, 5, NonBlockingSocket) {
  request_func_ = r;
}

void webserver::handle_client() {

    // TODO: This is naive, because we want handle_client to handle one request not an entire client session, but it will work for now.

    Socket* ptr_s = _in.Accept();
    if (ptr_s)
    {
        Request(ptr_s);
    }
}
