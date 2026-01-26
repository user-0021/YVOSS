#include <drogon/drogon.h>
#include <html_class.hpp>
#include <iostream>

#define HTTPS_CALLBACK [=](const drogon::HttpRequestPtr &req,std::function<void(const drogon::HttpResponsePtr &)> &&callback)

int main() {
	//bind web page

	//Set HTTP listener address and port
	drogon::app().addListener("0.0.0.0", 5555);
	//Load config file
	drogon::app().loadConfigFile("../config.json");

	//regist callback
	drogon::app().registerHandler(".*",HTTPS_CALLBACK{

		//api callback
		if (req->path().find("/api/") == 0) {
			auto resp = drogon::HttpResponse::newNotFoundResponse();
			callback(resp);
			return;
		}

		// webpage
		printf("%s\r\n",drogon::app().getHomePage().c_str());
		auto resp = drogon::HttpResponse::newFileResponse(drogon::app().getHomePage());
		callback(resp);
	});

	//drogon::app().loadConfigFile("../config.yaml");
	//Run HTTP framework,the method will block in the internal event loop
	drogon::app().run();
	return 0;
}
