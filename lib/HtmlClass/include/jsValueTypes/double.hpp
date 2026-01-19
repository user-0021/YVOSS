#pragma once
#include <jsValue.hpp>

// double class
class JsDouble:public JsValue{
	protected:
	double data;
	void calcStaticValue() noexcept{
		if(!this->isStatic)
			return;
		this->staticValue = std::to_string(this->data);
	};

	public:
	JsDouble(const JsValue& v):JsValue(v),data(){};
	JsDouble(JsValue&& v):JsValue(std::move(v)),data(){};
	JsDouble(const JsDouble& o):JsValue(o),data(o.data){};
	JsDouble(JsDouble&& o):JsValue(o),data(o.data){};
	JsDouble(double& d):data(d){this->isStatic = true;this->calcStaticValue();};
	JsDouble(double&& d):data(std::move(d)){this->isStatic = true;this->calcStaticValue();};
	JsDouble(ExprNode* l,ExprNode* r,NodeType t):JsValue(l,r,t),data(){};
};

