
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Prr_Route) {

	ZEPHIR_REGISTER_CLASS(Prr, Route, prr, route, prr_route_method_entry, 0);

	/**
	 * URL of this Route
	 *
	 * @var string
	 */
	zend_declare_property_null(prr_route_ce, SL("url"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Accepted HTTP methods for this route
	 *
	 * @var array
	 */
	zend_declare_property_null(prr_route_ce, SL("methods"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Target for this route, can be anything.
	 *
	 * @var array
	 */
	zend_declare_property_null(prr_route_ce, SL("target"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The name of this route, used for reversed routing
	 *
	 * @var string
	 */
	zend_declare_property_string(prr_route_ce, SL("name"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Custom parameter filters for this route
	 *
	 * @var array
	 */
	zend_declare_property_null(prr_route_ce, SL("filters"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Array containing parameters passed through request URL
	 *
	 * @var array
	 */
	zend_declare_property_null(prr_route_ce, SL("parameters"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor
 *
 * @param string url
 * @param array target
 * @param array methods
 * @param string name
 */
PHP_METHOD(Prr_Route, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *url_param = NULL, *target = NULL, *methods = NULL, *name_param = NULL, *_0 = NULL, *_1;
	zval *url = NULL, *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &url_param, &target, &methods, &name_param);

	if (unlikely(Z_TYPE_P(url_param) != IS_STRING && Z_TYPE_P(url_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'url' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(url_param) == IS_STRING)) {
		url = url_param;
	} else {
		ZEPHIR_INIT_VAR(url);
		ZVAL_EMPTY_STRING(url);
	}
	if (!target) {
		ZEPHIR_CPY_WRT(target, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(target);
	}
	if (!methods) {
		ZEPHIR_CPY_WRT(methods, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(methods);
	}
	if (!name_param) {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	} else {
	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(name_param) == IS_STRING)) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}
	}


	zephir_update_property_this(this_ptr, SL("url"), url TSRMLS_CC);
	if (Z_TYPE_P(methods) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(methods);
		array_init_size(methods, 11);
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "GET", 1);
		zephir_array_fast_append(methods, _0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "POST", 1);
		zephir_array_fast_append(methods, _0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "PUT", 1);
		zephir_array_fast_append(methods, _0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "DELETE", 1);
		zephir_array_fast_append(methods, _0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "PATCH", 1);
		zephir_array_fast_append(methods, _0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "OPTIONS", 1);
		zephir_array_fast_append(methods, _0);
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "HEAD", 1);
		zephir_array_fast_append(methods, _0);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setmethods", NULL, methods);
	zephir_check_call_status();
	if (Z_TYPE_P(target) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(target);
		array_init(target);
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "settarget", NULL, target);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(_0);
	zephir_gettype(_0, name TSRMLS_CC);
	if (!ZEPHIR_IS_STRING(_0, "null")) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setname", NULL, name);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("filters"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("parameters"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get the route url
 *
 * @return string
 */
PHP_METHOD(Prr_Route, getUrl) {


	RETURN_MEMBER(this_ptr, "url");

}

/**
 * Set the route url
 *
 * @param string $url
 * @return \Prr\Route
 */
PHP_METHOD(Prr_Route, setUrl) {

	zval *url_param = NULL, *_0;
	zval *url = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &url_param);

	if (unlikely(Z_TYPE_P(url_param) != IS_STRING && Z_TYPE_P(url_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'url' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(url_param) == IS_STRING)) {
		url = url_param;
	} else {
		ZEPHIR_INIT_VAR(url);
		ZVAL_EMPTY_STRING(url);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_trim(_0, url, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("url"), _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Get the target
 *
 * @return array
 */
PHP_METHOD(Prr_Route, getTarget) {


	RETURN_MEMBER(this_ptr, "target");

}

/**
 * Set the target
 *
 * @param array $target
 * @return \Prr\Route
 */
PHP_METHOD(Prr_Route, setTarget) {

	zval *target;

	zephir_fetch_params(0, 1, 0, &target);



	if (Z_TYPE_P(target) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "target must be array", "prr/route.zep", 125);
		return;
	}
	zephir_update_property_this(this_ptr, SL("target"), target TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Get route methods
 *
 * @return array
 */
PHP_METHOD(Prr_Route, getMethods) {


	RETURN_MEMBER(this_ptr, "methods");

}

/**
 * Set the route methods
 *
 * @param array
 * @return \Prr\Route
 */
PHP_METHOD(Prr_Route, setMethods) {

	zval *methods;

	zephir_fetch_params(0, 1, 0, &methods);



	if (Z_TYPE_P(methods) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "methods must be array", "prr/route.zep", 150);
		return;
	}
	zephir_update_property_this(this_ptr, SL("methods"), methods TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Get the route name
 *
 * @return string
 */
PHP_METHOD(Prr_Route, getName) {


	RETURN_MEMBER(this_ptr, "name");

}

/**
 * Set the route name
 *
 * @param string
 * @return \Prr\Route
 */
PHP_METHOD(Prr_Route, setName) {

	zval *name_param = NULL, *_0;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (unlikely(Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(name_param) == IS_STRING)) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_fast_trim(_0, name, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("name"), _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set the route filters
 *
 * @param array $filters
 * @return \Prr\Route;
 */
PHP_METHOD(Prr_Route, setFilters) {

	zval *filters;

	zephir_fetch_params(0, 1, 0, &filters);



	if (Z_TYPE_P(filters) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "filters must be array", "prr/route.zep", 187);
		return;
	}
	zephir_update_property_this(this_ptr, SL("filters"), filters TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Get regular expression for this route
 *
 * @return string
 */
PHP_METHOD(Prr_Route, getRegex) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	zval *_1, *_2;
	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 3);
	zephir_array_fast_append(_0, this_ptr);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "substituteFilter", 1);
	zephir_array_fast_append(_0, _1);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("url"), PH_NOISY_CC);
	ZEPHIR_INIT_BNVAR(_1);
	ZVAL_STRING(_1, "/:(\\w+)/", 0);
	ZEPHIR_RETURN_CALL_FUNCTION("preg_replace_callback", &_3, _1, _0, _2);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Substitute filters in the regular expression
 *
 * @param array $matches
 * @return string
 */
PHP_METHOD(Prr_Route, substituteFilter) {

	zend_bool _0;
	zval *matches, *_1, *_2, *_3, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &matches);



	if (Z_TYPE_P(matches) == IS_ARRAY) {
		_0 = zephir_array_isset_long(matches, 1);
		if (_0) {
			_1 = zephir_fetch_nproperty_this(this_ptr, SL("filters"), PH_NOISY_CC);
			zephir_array_fetch_long(&_2, matches, 1, PH_READONLY, "prr/route.zep", 212 TSRMLS_CC);
			_0 = zephir_array_isset(_1, _2);
		}
		if (_0) {
			_3 = zephir_fetch_nproperty_this(this_ptr, SL("filters"), PH_NOISY_CC);
			ZEPHIR_OBS_VAR(_5);
			zephir_array_fetch_long(&_5, matches, 1, PH_NOISY, "prr/route.zep", 213 TSRMLS_CC);
			zephir_array_fetch(&_4, _3, _5, PH_NOISY | PH_READONLY, "prr/route.zep", 213 TSRMLS_CC);
			RETURN_CTOR(_4);
		}
	}
	RETURN_MM_STRING("([\\w-]+)", 1);

}

/**
 * Get route parameters
 *
 * @return array
 */
PHP_METHOD(Prr_Route, getParameters) {


	RETURN_MEMBER(this_ptr, "parameters");

}

/**
 * Set route parameters
 *
 * @param array $parameters
 * @return \Prr\Route
 */
PHP_METHOD(Prr_Route, setParameters) {

	zval *parameters;

	zephir_fetch_params(0, 1, 0, &parameters);



	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "parameters must be array", "prr/route.zep", 238);
		return;
	}
	zephir_update_property_this(this_ptr, SL("parameters"), parameters TSRMLS_CC);
	RETURN_THISW();

}

