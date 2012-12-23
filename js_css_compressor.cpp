#include "js_css_compressor.h"



zend_object_handlers jsCssCompressor_object_handlers;

struct jsCssCompressor_object {
    zend_object std;
    Compressor *jsCssCompressor;
};




void jsCssCompressor_free_storage(void *object TSRMLS_DC)
{
	jsCssCompressor_object *obj = (jsCssCompressor_object *)object;
    delete obj->jsCssCompressor;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value jsCssCompressor_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    jsCssCompressor_object *obj = (jsCssCompressor_object *)emalloc(sizeof(jsCssCompressor_object));
    memset(obj, 0, sizeof(jsCssCompressor_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    zend_hash_copy(obj->std.properties, &type->default_properties,
        (copy_ctor_func_t)zval_add_ref, (void *)&tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(obj, NULL, jsCssCompressor_free_storage, NULL TSRMLS_CC);
    retval.handlers = &jsCssCompressor_object_handlers;

    return retval;
}



zend_class_entry *jsCssCompressor_ce;

PHP_METHOD(Compressor, __construct)
{
	Compressor *jsCssCompressor = NULL;
	jsCssCompressor = new Compressor();
	jsCssCompressor_object *obj = (jsCssCompressor_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	obj->jsCssCompressor = jsCssCompressor;
}

PHP_METHOD(Compressor, addCss)
{
	char *c_path;
	int c_path_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &c_path, &c_path_len) == FAILURE)
	{
	    RETURN_NULL();
	}

	string path(c_path, c_path_len);


	Compressor *jsCssCompressor;
	jsCssCompressor_object *obj = (jsCssCompressor_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	jsCssCompressor = obj->jsCssCompressor;

	if (jsCssCompressor != NULL)
	{
		jsCssCompressor->addCss(path);
	}
}

PHP_METHOD(Compressor, addJs)
{
	char *c_path;
	int c_path_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &c_path, &c_path_len) == FAILURE)
	{
	    RETURN_NULL();
	}

	string path(c_path, c_path_len);

	Compressor *jsCssCompressor;
	jsCssCompressor_object *obj = (jsCssCompressor_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	jsCssCompressor = obj->jsCssCompressor;

	if (jsCssCompressor != NULL)
	{
		jsCssCompressor->addJs(path);
	}
}

PHP_METHOD(Compressor, getCss)
{
	Compressor *jsCssCompressor;
	jsCssCompressor_object *obj = (jsCssCompressor_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	jsCssCompressor = obj->jsCssCompressor;
	if (jsCssCompressor != NULL)
	{
		RETURN_STRING(jsCssCompressor->getCss().c_str(), 1);
	}
	RETURN_NULL();
}

PHP_METHOD(Compressor, getJs)
{
	Compressor *jsCssCompressor;
	jsCssCompressor_object *obj = (jsCssCompressor_object *)zend_object_store_get_object(getThis() TSRMLS_CC);
	jsCssCompressor = obj->jsCssCompressor;
	if (jsCssCompressor != NULL)
	{
		RETURN_STRING(jsCssCompressor->getJs().c_str(), 1);
	}
	RETURN_NULL();
}

function_entry jsCssCompressor_methods[] = {
    PHP_ME(Compressor, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Compressor, addCss, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Compressor, addJs, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Compressor, getCss, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Compressor, getJs, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(jsCssCompressor)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "jsCssCompressor", jsCssCompressor_methods);
    jsCssCompressor_ce = zend_register_internal_class(&ce TSRMLS_CC);
    jsCssCompressor_ce->create_object = jsCssCompressor_create_handler;
    memcpy(&jsCssCompressor_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    jsCssCompressor_object_handlers.clone_obj = NULL;
    return SUCCESS;
}







zend_module_entry jsCssCompressor_module_entry =
{
	#if ZEND_MODULE_API_NO >= 20010901
		STANDARD_MODULE_HEADER,
	#endif
		PHP_JS_CSS_COMPRESSOR_EXTNAME,
		NULL,                  /* Functions */
		PHP_MINIT(jsCssCompressor),
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
	ZEND_GET_MODULE(jsCssCompressor)
}
#endif
