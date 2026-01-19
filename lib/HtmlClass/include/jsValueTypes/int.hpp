#pragma once
#include <jsValue.hpp>

// int class
class JsInt:public JsValue{
	protected:
	int data;
	void calcStaticValue() noexcept{
		if(!this->isStatic)
			return;
		this->staticValue = std::to_string(this->data);
	};

	public:
	JsInt(const JsValue& v):JsValue(v),data(){};
	JsInt(JsValue&& v):JsValue(std::move(v)),data(){};
	JsInt(const JsInt& o):JsValue(o),data(o.data){};
	JsInt(JsInt&& o):JsValue(o),data(o.data){};
	JsInt(int& i):data(i){this->isStatic = true;this->calcStaticValue();};
	JsInt(int&& i):data(std::move(i)){this->isStatic = true;this->calcStaticValue();};
	JsInt(ExprNode* l,ExprNode* r,NodeType t):JsValue(l,r,t),data(){};
};
