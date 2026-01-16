#pragma once
#include <string>
#include <htmlTag.hpp>

class HtmlPage
{
private:
	HtmlTag head;
	HtmlTag body;	
public:
	std::string encord() const {return head.encord() + body.encord();}
	void setHead(const HtmlTag&  head) noexcept{this->head = head;}
	void setHead(const HtmlTag&& head) noexcept{this->head = std::move(head);}
	void setBody(const HtmlTag&  body) noexcept{this->body = body;}
	void setBody(const HtmlTag&& body) noexcept{this->body = std::move(body);}
};
