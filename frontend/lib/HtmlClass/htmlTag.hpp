#pragma once
#include <vector>

class HtmlNode{
	protected:
		char* name;
		char* attributes;
		std::vector<HtmlNode> children;
		char* text;

	public:
		HtmlNode(char* name,char* attributes,std::vector<HtmlNode> children = {}){

		}

		
};