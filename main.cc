#include <drogon/drogon.h>
#include <html_class.hpp>
#include <iostream>

#define HTTPS_CALLBACK() [=](const drogon::HttpRequestPtr &req,std::function<void(const drogon::HttpResponsePtr &)> &&callback)

int main() {


	htmlPage mainPage;
	mainPage.setHead(
		htmlTag("head",""
		)
	);
	mainPage.setBody(
		htmlTag("body","option1=1",
			htmlTag("h1","option1=2",
				htmlVal("hello")
			)+
			htmlTag("h2","option1=2",
				htmlVal("world")
			)+
			HTML_TAG_FOREACH_BEGIN(int i = 0;i < 10;i++){
				return 	htmlTag("h2","option1=2",
									htmlVal("world" + std::to_string(i))
								);
			}
			HTML_TAG_FOREACH_END
		)
	);

	//bind web page
	drogon::app()
		.registerHandler("/",
			HTTPS_CALLBACK(){
				auto resp = drogon::HttpResponse::newHttpResponse();
				resp->setStatusCode(drogon::k200OK);
				resp->setContentTypeCode(drogon::CT_TEXT_HTML);
				resp->setBody(
					mainPage.encord()
				);

				callback(resp);
			});

	//Set HTTP listener address and port
	drogon::app().addListener("0.0.0.0", 5555);
	//Load config file
	//drogon::app().loadConfigFile("../config.json");
	//drogon::app().loadConfigFile("../config.yaml");
	//Run HTTP framework,the method will block in the internal event loop
	drogon::app().run();
	return 0;
}
