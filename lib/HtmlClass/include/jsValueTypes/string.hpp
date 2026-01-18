#pragma once
#include <jsValue.hpp>
#include <jsValueTypes/int.hpp>

// string class
class JsString: JsValue{
	private:
	std::string data;

	public:
	JsString(const JsString& o):JsValue(o),data(o.data){};
	JsString(JsString&& o):JsValue(o),data(o.data){};
	JsString(std::string& s):data(s){this->isStatic = true;};
	JsString(std::string&& s):data(s){this->isStatic = true;};
	JsString(ExprNode* l,ExprNode* r,NodeType t):JsValue(l,r,t),data(){};

	JsString& operator=(const JsString& s) noexcept;
	JsString& operator=(JsString&& s) noexcept;
	JsString operator+(const JsString& s) const noexcept;
	JsString operator+(JsString&& s) const noexcept;

	// java script functions
		static JsValue fromCharCode(std::vector<JsInt> args);
};





JsString& JsString::operator=(const JsString& s) noexcept{
	//copy
	if(!this->isStatic)
		this->node = JsValue::copyNode(*s.node);
		
	this->isStatic = s.isStatic;
	this->data = s.data;
}

JsString& JsString::operator=(JsString&& s) noexcept{

}

JsString JsString::operator+(const JsString& s) const noexcept{
	JsString ret(*this);

	if(this->isStatic & s.isStatic){
		ret.data += s.data;
	}
	else{
		ExprNode* left_Node;
		ExprNode* right_Node;

		//make node
		if(this->isStatic)
			left_Node = new ExprNode(ExprNode{
				.refCount = 0,
				.left = new std::string("\"" + this->data + "\""),
				.right = nullptr,
				.type = NodeType::NODE_VALUE
			});
		else
			left_Node = this->node;
			
		//make node
		if(s.isStatic)
			right_Node = new ExprNode(ExprNode{
				.refCount = 0,
				.left = new std::string("\"" + s.data + "\""),
				.right = nullptr,
				.type = NodeType::NODE_VALUE
			});
		else
			right_Node = s.node;

		ret = JsString(left_Node,right_Node,NodeType::NODE_ADD);
	}

	return ret;
}

JsString JsString::operator+(JsString&& s) const noexcept{

}