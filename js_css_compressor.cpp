#include "js_css_compressor.h"

PHP_MINIT_FUNCTION(js_css_compressor)
{
    return SUCCESS;
}

zend_module_entry js_css_compressor_module_entry =
{
	#if ZEND_MODULE_API_NO >= 20010901
		STANDARD_MODULE_HEADER,
	#endif
		PHP_JS_CSS_COMPRESSOR_EXTNAME,
		NULL,                  /* Functions */
		PHP_MINIT(js_css_compressor),
		NULL,                  /* MSHUTDOWN */
		NULL,                  /* RINIT */
		NULL,                  /* RSHUTDOWN */
		NULL,                  /* MINFO */
	#if ZEND_MODULE_API_NO >= 20010901
		PHP_JS_CSS_COMPRESSOR_EXTVER,
	#endif
		STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_JS_CSS_COMPRESSOR
extern "C"
{
	ZEND_GET_MODULE(js_css_compressor)
}
#endif
