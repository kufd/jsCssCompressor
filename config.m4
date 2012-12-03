PHP_ARG_ENABLE(js_css_compressor,
    [Whether to enable the "js_css_compressor" extension],
    [  --enable-js_css_compressor      Enable "js_css_compressor" extension support])

if test $PHP_JS_CSS_COMPRESSOR != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(JS_CSS_COMPRESSOR_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, JS_CSS_COMPRESSOR_SHARED_LIBADD)
    PHP_NEW_EXTENSION(js_css_compressor, js_css_compressor.cpp compressor.class.cpp, $ext_shared)
fi