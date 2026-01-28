#include <htmlTag.hpp>

namespace html_class{
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                  Constractor and Destoractor
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	HtmlTag::HtmlTag(std::string text):
	_isTag   (false),
	_tag     (),
	_dataLen (),
	_children(){

		//count char to need escape
		std::size_t copiedLen = 0;
		for (char c : text){
			if(HtmlTag::_htmlEscapeFlag[(unsigned char) c]) [[unlikely]] {
				copiedLen += this->_htmlEscapeFlag[(unsigned char) c];
			}
		}

		if (!copiedLen) [[likely]]{
			// if don't escape
			this->_option = std::move(text);
		} else {
			//reserve new text size
			this->_option.reserve(text.size() + copiedLen);
			
			for (char c : text){
				if(const char* replaceText = HtmlTag::_htmlEscapeStr[(unsigned char) c]) [[unlikely]]
					this->_option.append(replaceText);
				else
					this->_option.push_back(c);
			}
		}
		
		//update len
		this->_dataLen = _option.length();
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                  Member functions
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void HtmlTag::chained_encord_raw_text(std::string& buff) const noexcept{
		if(this->_isTag){
			buff += '<'; 
			buff += this->_tag;
			buff += this->_option;
			buff += '>';

			for(const auto& elem: this->_children){
				elem.chained_encord_raw_text(buff);
			}

			buff += "</";
			buff += this->_tag;
			buff += '>';
		}else{
			buff += this->_option;
		}
	}

	std::string HtmlTag::encord_raw_text() const{
		std::string rawText;
		rawText.reserve(this->_dataLen);

		if(this->_isTag){
			rawText += '<'; 
			rawText += this->_tag;
			rawText += this->_option;
			rawText += '>';

			for(const auto& elem: this->_children){
				elem.chained_encord_raw_text(rawText);
			}

			rawText += "</";
			rawText += this->_tag;
			rawText += '>';
		}else{
			rawText += this->_option;
		}

		
		return rawText;
	}
} 
