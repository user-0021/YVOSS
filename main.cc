#include <drogon/drogon.h>
#include <iostream>
#include <html_class.hpp>

#define HTTPS_CALLBACK [=](const drogon::HttpRequestPtr &req,std::function<void (const drogon::HttpResponsePtr &)> &&callback)
#define PREROUTING_CALLBACK [=](const drogon::HttpRequestPtr &req,drogon::AdviceCallback &&acb,drogon::AdviceChainCallback&& accb)

using namespace html_class;

int main() {
	//bind web page
	auto tmp = HtmlTag("h","data",
		HtmlTag("Hello")+
		HTML_TAG_FOREACH_BEGIN(int i = 0;i < 10;i++){
			return HtmlTag("OK! \"' <" + std::to_string(i) + ">\n");
		}
		HTML_TAG_FOREACH_END
	);

	//Set HTTP listener address and port
	//Load config file
	drogon::app().loadConfigFile("../config.json");

	static const std::string homePagePath = drogon::app().getDocumentRoot() + drogon::app().getHomePage();
	static const char* homePagePath_c = homePagePath.c_str();

	drogon::app().registerHandler("/test",HTTPS_CALLBACK{
		auto resp = drogon::HttpResponse::newHttpResponse();
		resp->setStatusCode(drogon::k200OK);
		resp->setContentTypeCode(drogon::CT_TEXT_HTML);
		resp->setBody(
			tmp.encord_raw_text()
		);

		callback(resp);
	});

	//set route  fot React
	//drogon::app().registerPreRoutingAdvice(PREROUTING_CALLBACK{
	//	//request path
	//	const std::string &path = req->path();
	//	LOG_DEBUG << "CallPreRouting to " << path;

	//	//api callback
	//	if (path.compare(0, 5, "/api/") == 0) {
	//		LOG_DEBUG << "ROOT to API ";
	//		accb(); 
	//		return;
  //  }

	//	//static resource
	//	size_t last_slash = path.find_last_of('/');
  //  size_t last_dot = path.find_last_of('.');
	//	if (last_dot != std::string::npos && (last_slash == std::string::npos || last_dot > last_slash)) {
	//		LOG_DEBUG << "ROOT to static";
	//		accb();
	//		return;
  //  }

	//	// webpage
	//	LOG_DEBUG << "ROOT to homePage [" << homePagePath_c <<"]";
	//	auto resp = drogon::HttpResponse::newFileResponse(homePagePath_c);
  //  resp->setStatusCode(drogon::k200OK);
  //  acb(resp);
	//});

	drogon::app().addListener("0.0.0.0", 5555);
	//drogon::app().loadConfigFile("../config.yaml");
	//Run HTTP framework,the method will block in the internal event loop
	drogon::app().run();
	return 0;
}
