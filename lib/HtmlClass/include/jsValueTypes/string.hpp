#pragma once
#include <jsValue.hpp>
#include <jsValueTypes/int.hpp>
#include <jsValueTypes/double.hpp>




// string class
class JsString: public JsValue{
	protected:
	std::string data;
	void calcStaticValue() noexcept{
		if(!this->isStatic)
			return;

		this->staticValue = "";
		for(auto& c : this->data){
			if(c == '`')
				staticValue += "\\`";
			else
				staticValue += c;
		}
		//end back slash escape
		if(staticValue[staticValue.length() - 1] == '\\')
			staticValue += "\\\\";

		this->staticValue = "String.raw`"+this->staticValue+"`";
	};
	
	public:
	JsString(const JsValue& v):JsValue(v),data(){};
	JsString(JsValue&& v):JsValue(std::move(v)),data(){};
	JsString(const JsString& o):JsValue(o),data(o.data){};
	JsString(JsString&& o):JsValue(std::move(o)),data(std::move(o.data)){};
	JsString(std::string& s):data(s){this->isStatic = true;this->calcStaticValue();};
	JsString(std::string&& s):data(std::move(s)){this->isStatic = true;this->calcStaticValue();};
	JsString(ExprNode* l,ExprNode* r,NodeType t):JsValue(l,r,t),data(){};

	JsString& operator=(const JsString& s) noexcept;
	JsString& operator=(JsString&& s) noexcept;
	JsString operator+(const JsString& s) const noexcept;
	JsInt operator+(const JsInt& i) const noexcept{return JsInt(JsValue::getNode(this),JsValue::getNode(&i),NodeType::NODE_ADD);};
	JsInt operator-(const JsInt& i) const noexcept{return JsInt(JsValue::getNode(this),JsValue::getNode(&i),NodeType::NODE_SUB);};
	JsInt operator*(const JsInt& i) const noexcept{return JsInt(JsValue::getNode(this),JsValue::getNode(&i),NodeType::NODE_MUL);};
	JsInt operator/(const JsInt& i) const noexcept{return JsInt(JsValue::getNode(this),JsValue::getNode(&i),NodeType::NODE_DIV);};
	JsInt operator%(const JsInt& i) const noexcept{return JsInt(JsValue::getNode(this),JsValue::getNode(&i),NodeType::NODE_REM);};
	JsDouble operator+(const JsDouble& d) const noexcept{return JsDouble(JsValue::getNode(this),JsValue::getNode(&d),NodeType::NODE_ADD);};
	JsDouble operator-(const JsDouble& d) const noexcept{return JsDouble(JsValue::getNode(this),JsValue::getNode(&d),NodeType::NODE_SUB);};
	JsDouble operator*(const JsDouble& d) const noexcept{return JsDouble(JsValue::getNode(this),JsValue::getNode(&d),NodeType::NODE_MUL);};
	JsDouble operator/(const JsDouble& d) const noexcept{return JsDouble(JsValue::getNode(this),JsValue::getNode(&d),NodeType::NODE_DIV);};
	JsDouble operator%(const JsDouble& d) const noexcept{return JsDouble(JsValue::getNode(this),JsValue::getNode(&d),NodeType::NODE_REM);};

	// java script functions
	static JsString fromCharCode(std::vector<JsInt>& args){};
};





JsString& JsString::operator=(const JsString& s)  noexcept{
	//copy
	if(s.isStatic){
		this->setNode(s.node);
		this->isStatic = s.isStatic;
		this->data = s.data;
		this->staticValue = s.staticValue;
	}else{
		JsValue::deleteNode(this->node);
		this->node = JsValue::createSingleNode(&s,NodeType::NODE_SET);
	}
}

JsString& JsString::operator=(JsString&& s) noexcept{
	//copy
	if(s.isStatic){
		this->setNode(s.node);
	}else{
		JsValue::deleteNode(this->node);
		this->node = JsValue::createSingleNode(&s,NodeType::NODE_SET);
		s.node = nullptr;
	}

	//move
	this->data = std::move(s.data);
	this->isStatic = std::move(s.isStatic);
	this->staticValue = std::move(s.staticValue);
}

// Add operators

JsString JsString::operator+(const JsString& s) const noexcept{
	JsString ret(*this);

	if(this->isStatic & s.isStatic){
		ret.data += s.data;
		ret.calcStaticValue();
	}
	else{
		ret = JsString(getNode(this),getNode(&s),NodeType::NODE_ADD);
	}

	return ret;
}