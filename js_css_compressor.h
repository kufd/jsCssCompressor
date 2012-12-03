#ifndef PHP_JS_CSS_COMPRESSOR_H
#define PHP_JS_CSS_COMPRESSOR_H

#define PHP_JS_CSS_COMPRESSOR_EXTNAME  "js_css_compressor"
#define PHP_JS_CSS_COMPRESSOR_EXTVER   "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C"
{
	#include "php.h"
}

extern zend_module_entry js_css_compressor_module_entry;
#define phpext_js_css_compressor_ptr &js_css_compressor_module_entry;

#endif /* PHP_JS_CSS_COMPRESSOR_H */
