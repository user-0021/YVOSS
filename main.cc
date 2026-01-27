#include <drogon/drogon.h>
#include <iostream>

#define HTTPS_CALLBACK [=](const drogon::HttpRequestPtr &req,drogon::AdviceCallback &&acb,drogon::AdviceChainCallback&& accb)

int main() {
	//bind web page

	//Set HTTP listener address and port
	drogon::app().addListener("0.0.0.0", 5555);
	//Load config file
	drogon::app().loadConfigFile("../config.json");

	static const char* homePageRoute = "a";

	//set route  fot React
	drogon::app().registerPreRoutingAdvice(HTTPS_CALLBACK{
		//request path
		const std::string &path = req->path();
		LOG_DEBUG << "CallPreRouting to " << path;

		//api callback
		if (path.compare(0, 5, "/api/") == 0) {
			LOG_DEBUG << "ROOT to API ";
			accb(); 
			return;
    }

		//static resource
		size_t last_slash = path.find_last_of('/');
    size_t last_dot = path.find_last_of('.');
		if (last_dot != std::string::npos && (last_slash == std::string::npos || last_dot > last_slash)) {
			LOG_DEBUG << "ROOT to static";
			accb();
			return;
    }

		// webpage
		LOG_DEBUG << "ROOT to homePage [" << drogon::app().getDocumentRoot()+drogon::app().getHomePage() <<"]";
		auto resp = drogon::HttpResponse::newFileResponse(drogon::app().getDocumentRoot()+drogon::app().getHomePage());
    resp->setStatusCode(drogon::k200OK);
    acb(resp);
	});

	//drogon::app().loadConfigFile("../config.yaml");
	//Run HTTP framework,the method will block in the internal event loop
	drogon::app().run();
	return 0;
}
