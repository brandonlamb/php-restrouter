
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
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/hash.h"


ZEPHIR_INIT_CLASS(Prr_Router) {

	ZEPHIR_REGISTER_CLASS(Prr, Router, prr, router, prr_router_method_entry, 0);

	/**
	 * Collection of routes
	 *
	 * @var RouteCollection
	 */
	zend_declare_property_null(prr_router_ce, SL("routes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Collection of named routes
	 *
	 * @var array
	 */
	zend_declare_property_null(prr_router_ce, SL("namedRoutes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The base REQUEST_URI. Gets prepended to all route url"s.
	 *
	 * @var string
	 */
	zend_declare_property_null(prr_router_ce, SL("basePath"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The last matched route
	 *
	 * @var Route
	 */
	zend_declare_property_null(prr_router_ce, SL("matchedRoute"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Flag for removing extra slashes from url
	 *
	 * @var bool
	 */
	zend_declare_property_bool(prr_router_ce, SL("removeExtraSlashes"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Named match types for convenience in defining routes
	 *
	 * @var array
	 */
	zend_declare_property_null(prr_router_ce, SL("matchTypes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Constructor
 *
 * @param RouteCollection routes
 * @param string $basePath
 * @param array $matchTypes
 */
PHP_METHOD(Prr_Router, __construct) {

	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *_2;
	zend_bool _0, _1, _3, _6;
	zval *basePath = NULL;
	zval *routes = NULL, *namedRoutes = NULL, *basePath_param = NULL, *matchTypes = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 4, &routes, &namedRoutes, &basePath_param, &matchTypes);

	if (!routes) {
		routes = ZEPHIR_GLOBAL(global_null);
	}
	if (!namedRoutes) {
		namedRoutes = ZEPHIR_GLOBAL(global_null);
	}
	if (!basePath_param) {
		ZEPHIR_INIT_VAR(basePath);
		ZVAL_STRING(basePath, "", 1);
	} else {
	if (unlikely(Z_TYPE_P(basePath_param) != IS_STRING && Z_TYPE_P(basePath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'basePath' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(basePath_param) == IS_STRING)) {
		basePath = basePath_param;
	} else {
		ZEPHIR_INIT_VAR(basePath);
		ZVAL_EMPTY_STRING(basePath);
	}
	}
	if (!matchTypes) {
		ZEPHIR_INIT_VAR(matchTypes);
		array_init(matchTypes);
	}


	_0 = Z_TYPE_P(routes) != IS_NULL;
	if (_0) {
		_0 = !zephir_instance_of_ev(routes, prr_routecollection_ce TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'routes' must be an instance of 'Prr\\RouteCollection'", "", 0);
		return;
	}
	_1 = Z_TYPE_P(namedRoutes) != IS_NULL;
	if (_1) {
		_1 = !zephir_instance_of_ev(namedRoutes, prr_routecollection_ce TSRMLS_CC);
	}
	if (_1) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Parameter 'namedRoutes' must be an instance of 'Prr\\RouteCollection'", "", 0);
		return;
	}
	ZEPHIR_INIT_VAR(_2);
	array_init_size(_2, 11);
	add_assoc_stringl_ex(_2, SS("i"), SL("[0-9]++"), 1);
	add_assoc_stringl_ex(_2, SS("a"), SL("[0-9A-Za-z]++"), 1);
	add_assoc_stringl_ex(_2, SS("h"), SL("[0-9A-Fa-f]++"), 1);
	add_assoc_stringl_ex(_2, SS("year"), SL("[1-9]\\d{0,3}++"), 1);
	add_assoc_stringl_ex(_2, SS("date"), SL("\\d{4}-\\d{2}-\\d{2}++"), 1);
	add_assoc_stringl_ex(_2, SS("*"), SL(".+?"), 1);
	add_assoc_stringl_ex(_2, SS("**"), SL(".++"), 1);
	add_assoc_stringl_ex(_2, SS(""), SL("[^/\\.]++"), 1);
	zephir_update_property_this(this_ptr, SL("matchTypes"), _2 TSRMLS_CC);
	_3 = Z_TYPE_P(routes) == IS_OBJECT;
	if (_3) {
		_3 = (zephir_instance_of_ev(routes, prr_routecollection_ce TSRMLS_CC));
	}
	if (_3) {
		zephir_update_property_this(this_ptr, SL("routes"), routes TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_4);
		object_init_ex(_4, prr_routecollection_ce);
		ZEPHIR_CALL_METHOD(NULL, _4, "__construct", &_5);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("routes"), _4 TSRMLS_CC);
	}
	_6 = Z_TYPE_P(namedRoutes) == IS_OBJECT;
	if (_6) {
		_6 = (zephir_instance_of_ev(namedRoutes, prr_routecollection_ce TSRMLS_CC));
	}
	if (_6) {
		zephir_update_property_this(this_ptr, SL("namedRoutes"), namedRoutes TSRMLS_CC);
	} else {
		ZEPHIR_INIT_LNVAR(_4);
		object_init_ex(_4, prr_routecollection_ce);
		ZEPHIR_CALL_METHOD(NULL, _4, "__construct", &_5);
		zephir_check_call_status();
		zephir_update_property_this(this_ptr, SL("namedRoutes"), _4 TSRMLS_CC);
	}
	if (!(ZEPHIR_IS_EMPTY(matchTypes))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "addmatchtypes", NULL, matchTypes);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setbasepath", NULL, basePath);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Set the base _url - gets prepended to all route _url"s.
 *
 * @param $basePath
 * @return this
 */
PHP_METHOD(Prr_Router, setBasePath) {

	zval *basePath_param = NULL, *_0, *_1, _2;
	zval *basePath = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &basePath_param);

	if (unlikely(Z_TYPE_P(basePath_param) != IS_STRING && Z_TYPE_P(basePath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'basePath' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(basePath_param) == IS_STRING)) {
		basePath = basePath_param;
	} else {
		ZEPHIR_INIT_VAR(basePath);
		ZVAL_EMPTY_STRING(basePath);
	}


	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "/", 0);
	zephir_fast_trim(_1, basePath, &_2, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	zephir_fast_trim(_0, _1, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("basePath"), _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Add named match types. It uses array_merge so keys can be overwritten.
 *
 * @param array $matchTypes The key is the name and the value is the regex.
 * @return this
 */
PHP_METHOD(Prr_Router, addMatchTypes) {

	zval *matchTypes, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &matchTypes);



	if (Z_TYPE_P(matchTypes) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "matchTypes must be array", "prr/router.zep", 114);
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("matchTypes"), PH_NOISY_CC);
	zephir_fast_array_merge(_0, &(_1), &(matchTypes) TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("matchTypes"), _0 TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Map a route to a target
 *
 * @param string $url The route regex, custom regex must start with an @. You can use multiple pre-set regex filters, like [i:id]
 * @param array $target The target where this route should point to. Can be anything.
 * @param array $methods One of 5 HTTP Methods, or a pipe-separated list of multiple HTTP Methods (GET|POST|PATCH|PUT|DELETE)
 * @param string $name Optional name of this route. Supply if you want to reverse route this url in your application.
 * @return this
 */
PHP_METHOD(Prr_Router, add) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *url_param = NULL, *target, *methods = NULL, *name = NULL, *route, *_0, *_1, *_2, *_3;
	zval *url = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &url_param, &target, &methods, &name);

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
	if (!methods) {
		methods = ZEPHIR_GLOBAL(global_null);
	}
	if (!name) {
		name = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(route);
	object_init_ex(route, prr_route_ce);
	ZEPHIR_CALL_METHOD(NULL, route, "__construct", NULL, url, target, methods, name);
	zephir_check_call_status();
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("routes"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "add", NULL, route);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(name))) {
		_1 = zephir_fetch_nproperty_this(this_ptr, SL("namedRoutes"), PH_NOISY_CC);
		if (zephir_array_isset(_1, name)) {
			ZEPHIR_INIT_VAR(_2);
			object_init_ex(_2, zend_exception_get_default(TSRMLS_C));
			ZEPHIR_INIT_VAR(_3);
			ZEPHIR_CONCAT_SV(_3, "Can not redeclare route ", name);
			ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, _3);
			zephir_check_call_status();
			zephir_throw_exception_debug(_2, "prr/router.zep", 140 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		} else {
			zephir_update_property_array(this_ptr, SL("namedRoutes"), name, route TSRMLS_CC);
		}
	}
	RETURN_THIS();

}

/**
 * Add multiple routes at once from array in the following format:
 *
 *   routes = [
 *      new Route(route, $target, $methods, $name),
 *      new Route(route, $target, $methods, $name)
 *   ];
 *
 * @param mixed routes, Can pass array, Traversable or RouteCollection
 * @return this
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Prr_Router, addRoutes) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *routes, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &routes);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("routes"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "addroutes", NULL, routes);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Set whether to remove extra slashes
 *
 * @param boolean $value
 * @return this
 */
PHP_METHOD(Prr_Router, removeExtraSlashes) {

	zval *value_param = NULL;
	zend_bool value;

	zephir_fetch_params(0, 1, 0, &value_param);

	value = zephir_get_boolval(value_param);


	zephir_update_property_this(this_ptr, SL("removeExtraSlashes"), value ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Set the matched route
 *
 * @param Route route
 * @return this
 */
PHP_METHOD(Prr_Router, setMatchedRoute) {

	zval *route;

	zephir_fetch_params(0, 1, 0, &route);



	if (!(zephir_instance_of_ev(route, prr_route_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'route' must be an instance of 'Prr\\Route'", "", 0);
		return;
	}
	zephir_update_property_this(this_ptr, SL("matchedRoute"), route TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Get the matched route
 *
 * @return Route
 */
PHP_METHOD(Prr_Router, getMatchedRoute) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("matchedRoute"), PH_NOISY_CC);
	if (Z_TYPE_P(_0) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_RuntimeException, "No route was matched", "prr/router.zep", 199);
		return;
	}
	RETURN_MM_MEMBER(this_ptr, "matchedRoute");

}

/**
 * Reversed routing
 *
 * Generate the URL for a named route. Replace regexes with supplied parameters
 *
 * @param string routeName The name of the route.
 * @param array $params Associative array of parameters to replace placeholders with.
 * @return string The URL of the route with named parameters in place.
 */
PHP_METHOD(Prr_Router, generate) {

	zephir_nts_static zephir_fcall_cache_entry *_13 = NULL;
	HashTable *_9;
	HashPosition _8;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *routeName_param = NULL, *params = NULL, *route = NULL, *url = NULL, *match = NULL, *matches = NULL, *block = NULL, *pre = NULL, *type = NULL, *param = NULL, *optional = NULL, *_0, *_1 = NULL, *_3, *_4, *_5, *_6 = NULL, *_7 = NULL, **_10, _11 = zval_used_for_init, *_12 = NULL, *_14 = NULL;
	zval *routeName = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &routeName_param, &params);

	if (unlikely(Z_TYPE_P(routeName_param) != IS_STRING && Z_TYPE_P(routeName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'routeName' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(routeName_param) == IS_STRING)) {
		routeName = routeName_param;
	} else {
		ZEPHIR_INIT_VAR(routeName);
		ZVAL_EMPTY_STRING(routeName);
	}
	if (!params) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("namedRoutes"), PH_NOISY_CC);
	if (!(zephir_array_isset(_0, routeName))) {
		ZEPHIR_INIT_VAR(_1);
		object_init_ex(_1, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_SVS(_2, "Route ", routeName, " does not exist.");
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _2);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1, "prr/router.zep", 219 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("namedRoutes"), PH_NOISY_CC);
	zephir_array_fetch(&_4, _3, routeName, PH_NOISY | PH_READONLY TSRMLS_CC);
	ZEPHIR_CPY_WRT(route, _4);
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("basePath"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_6, route, "geturl",  NULL);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(url);
	ZEPHIR_CONCAT_VV(url, _5, _6);
	ZEPHIR_CALL_METHOD(&_7, route, "geturl",  NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&matches, this_ptr, "geturlmatches", NULL, _7);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(matches))) {
		zephir_is_iterable(matches, &_9, &_8, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_9, (void**) &_10, &_8) == SUCCESS
		  ; zephir_hash_move_forward_ex(_9, &_8)
		) {
			ZEPHIR_GET_HVALUE(match, _10);
			ZEPHIR_OBS_NVAR(block);
			zephir_array_isset_long_fetch(&block, match, 0, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(pre);
			zephir_array_isset_long_fetch(&pre, match, 1, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(type);
			zephir_array_isset_long_fetch(&type, match, 2, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(param);
			zephir_array_isset_long_fetch(&param, match, 3, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(optional);
			zephir_array_isset_long_fetch(&optional, match, 4, 0 TSRMLS_CC);
			if (zephir_is_true(pre)) {
				ZEPHIR_SINIT_NVAR(_11);
				ZVAL_LONG(&_11, 1);
				ZEPHIR_CALL_FUNCTION(&_12, "substr", &_13, block, &_11);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(block, _12);
			}
			if (zephir_array_isset(params, param)) {
				ZEPHIR_INIT_NVAR(_14);
				zephir_array_fetch(&_4, params, param, PH_NOISY | PH_READONLY TSRMLS_CC);
				zephir_fast_str_replace(_14, block, _4, url);
				ZEPHIR_CPY_WRT(url, _14);
			} else {
				if (zephir_is_true(optional)) {
					ZEPHIR_INIT_NVAR(_14);
					ZEPHIR_INIT_LNVAR(_1);
					ZEPHIR_CONCAT_VV(_1, pre, block);
					ZEPHIR_SINIT_NVAR(_11);
					ZVAL_STRING(&_11, "", 0);
					zephir_fast_str_replace(_14, _1, &_11, url);
					ZEPHIR_CPY_WRT(url, _14);
				}
			}
		}
	}
	RETURN_CCTOR(url);

}

/**
 * Attempt to match a route against configured route collection
 *
 * @param string $requestUrl
 * @param string $method
 * @return Route|boolean
 */
PHP_METHOD(Prr_Router, match) {

	zval *_18 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_11 = NULL, *_14 = NULL;
	HashTable *_6, *_16;
	HashPosition _5, _15;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool match = 0, _8;
	zval *requestUrl_param = NULL, *method_param = NULL, *route = NULL, *methods = NULL, *routeUrl = NULL, *pattern = NULL, *key = NULL, *value = NULL, *params, *_0, *_1 = NULL, _2 = zval_used_for_init, *_3, *_4 = NULL, **_7, *_9, *_10 = NULL, *_12 = NULL, *_13 = NULL, **_17;
	zval *requestUrl = NULL, *method = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &requestUrl_param, &method_param);

	if (unlikely(Z_TYPE_P(requestUrl_param) != IS_STRING && Z_TYPE_P(requestUrl_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'requestUrl' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(requestUrl_param) == IS_STRING)) {
		requestUrl = requestUrl_param;
	} else {
		ZEPHIR_INIT_VAR(requestUrl);
		ZVAL_EMPTY_STRING(requestUrl);
	}
	ZEPHIR_SEPARATE_PARAM(requestUrl);
	if (unlikely(Z_TYPE_P(method_param) != IS_STRING && Z_TYPE_P(method_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'method' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (unlikely(Z_TYPE_P(method_param) == IS_STRING)) {
		method = method_param;
	} else {
		ZEPHIR_INIT_VAR(method);
		ZVAL_EMPTY_STRING(method);
	}
	ZEPHIR_INIT_VAR(params);
	array_init(params);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("removeExtraSlashes"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_STRING(&_2, "/", 0);
		zephir_fast_trim(_1, requestUrl, &_2, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
		zephir_get_strval(requestUrl, _1);
	}
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("routes"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_4, _3, "all",  NULL);
	zephir_check_call_status();
	zephir_is_iterable(_4, &_6, &_5, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
	  ; zephir_hash_move_forward_ex(_6, &_5)
	) {
		ZEPHIR_GET_HVALUE(route, _7);
		ZEPHIR_CALL_METHOD(&methods, route, "getmethods",  NULL);
		zephir_check_call_status();
		if (!(zephir_fast_in_array(method, methods TSRMLS_CC))) {
			continue;
		}
		ZEPHIR_CALL_METHOD(&routeUrl, route, "geturl",  NULL);
		zephir_check_call_status();
		if (ZEPHIR_IS_STRING_IDENTICAL(routeUrl, "*")) {
			match = 1;
		} else {
			_8 = zephir_array_isset_long(routeUrl, 0);
			if (_8) {
				zephir_array_fetch_long(&_9, routeUrl, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
				_8 = ZEPHIR_IS_STRING_IDENTICAL(_9, "@");
			}
			if (_8) {
				ZEPHIR_SINIT_NVAR(_2);
				ZVAL_LONG(&_2, 1);
				ZEPHIR_CALL_FUNCTION(&_10, "substr", &_11, routeUrl, &_2);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(pattern);
				ZEPHIR_CONCAT_SVS(pattern, "`", _10, "`u");
				ZEPHIR_INIT_LNVAR(_12);
				Z_SET_ISREF_P(params);
				ZEPHIR_CALL_FUNCTION(&_13, "preg_match", &_14, pattern, requestUrl, params);
				Z_UNSET_ISREF_P(params);
				zephir_check_call_status();
				if (zephir_is_true(_13)) {
					ZEPHIR_INIT_NVAR(_12);
					ZVAL_BOOL(_12, 1);
				} else {
					ZEPHIR_INIT_NVAR(_12);
					ZVAL_BOOL(_12, 0);
				}
				match = zephir_is_true(_12);
			} else {
				ZEPHIR_CALL_METHOD(&pattern, this_ptr, "compileroute", NULL, routeUrl);
				zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_12);
				Z_SET_ISREF_P(params);
				ZEPHIR_CALL_FUNCTION(&_10, "preg_match", &_14, pattern, requestUrl, params);
				Z_UNSET_ISREF_P(params);
				zephir_check_call_status();
				if (zephir_is_true(_10)) {
					ZEPHIR_INIT_NVAR(_12);
					ZVAL_BOOL(_12, 1);
				} else {
					ZEPHIR_INIT_NVAR(_12);
					ZVAL_BOOL(_12, 0);
				}
				match = zephir_is_true(_12);
			}
		}
		if (match) {
			if (zephir_fast_count_int(params TSRMLS_CC)) {
				zephir_is_iterable(params, &_16, &_15, 0, 0);
				for (
				  ; zephir_hash_get_current_data_ex(_16, (void**) &_17, &_15) == SUCCESS
				  ; zephir_hash_move_forward_ex(_16, &_15)
				) {
					ZEPHIR_GET_HMKEY(key, _16, _15);
					ZEPHIR_GET_HVALUE(value, _17);
					if (zephir_is_numeric(key)) {
						zephir_array_unset(&params, key, PH_SEPARATE);
					}
				}
			}
			ZEPHIR_CALL_METHOD(NULL, route, "setparameters", NULL, params);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_CALL_METHOD(&_10, route, "gettarget",  NULL);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_18);
			array_init_size(_18, 2);
			zephir_array_update_string(&_18, SL("method"), &method, PH_COPY | PH_SEPARATE);
			zephir_fast_array_merge(_1, &(_10), &(_18) TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, route, "settarget", NULL, _1);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_13, this_ptr, "setmatchedroute", NULL, route);
			zephir_check_call_status();
			ZEPHIR_RETURN_CALL_METHOD(_13, "getmatchedroute", NULL);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Get array of matches for route url
 *
 * @param string $url
 * @return array
 */
PHP_METHOD(Prr_Router, getUrlMatches) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_2 = NULL;
	zval *url_param = NULL, *matches, *_0, *_1;
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
	ZEPHIR_INIT_VAR(matches);
	array_init(matches);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "`(/|\\.|)\\[([^:\\]]*+)(?::([^:\\]]*+))?\\](\\?|)`", 0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 2);
	Z_SET_ISREF_P(matches);
	ZEPHIR_CALL_FUNCTION(NULL, "preg_match_all", &_2, _0, url, matches, _1);
	zephir_check_temp_parameter(_0);
	Z_UNSET_ISREF_P(matches);
	zephir_check_call_status();
	RETURN_CCTOR(matches);

}

/**
 * Compile the regex for a given route (EXPENSIVE)
 *
 * @param string $url
 * @return string
 */
PHP_METHOD(Prr_Router, compileRoute) {

	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *url_param = NULL, *match = NULL, *matches = NULL, *matchTypes = NULL, *block = NULL, *pre = NULL, *type = NULL, *param = NULL, *optional = NULL, *pattern = NULL, *_0, **_3, *_4, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL;
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
	ZEPHIR_SEPARATE_PARAM(url);


	ZEPHIR_CALL_METHOD(&matches, this_ptr, "geturlmatches", NULL, url);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(matches))) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("matchTypes"), PH_NOISY_CC);
		ZEPHIR_CPY_WRT(matchTypes, _0);
		zephir_is_iterable(matches, &_2, &_1, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		  ; zephir_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HVALUE(match, _3);
			ZEPHIR_OBS_NVAR(block);
			zephir_array_isset_long_fetch(&block, match, 0, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(pre);
			zephir_array_isset_long_fetch(&pre, match, 1, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(type);
			zephir_array_isset_long_fetch(&type, match, 2, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(param);
			zephir_array_isset_long_fetch(&param, match, 3, 0 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(optional);
			zephir_array_isset_long_fetch(&optional, match, 4, 0 TSRMLS_CC);
			if (zephir_array_isset(matchTypes, type)) {
				zephir_array_fetch(&_4, matchTypes, type, PH_NOISY | PH_READONLY TSRMLS_CC);
				ZEPHIR_CPY_WRT(type, _4);
			}
			if (ZEPHIR_IS_STRING_IDENTICAL(pre, ".")) {
				ZEPHIR_INIT_NVAR(pre);
				ZVAL_STRING(pre, "\\.", 1);
			}
			ZEPHIR_INIT_LNVAR(_5);
			if (!ZEPHIR_IS_STRING_IDENTICAL(pre, "")) {
				ZEPHIR_CPY_WRT(_5, pre);
			} else {
				ZEPHIR_INIT_NVAR(_5);
				ZVAL_NULL(_5);
			}
			ZEPHIR_INIT_LNVAR(_6);
			if (!ZEPHIR_IS_STRING_IDENTICAL(param, "")) {
				ZEPHIR_INIT_NVAR(_6);
				ZEPHIR_CONCAT_SVS(_6, "?<", param, ">");
			} else {
				ZEPHIR_INIT_NVAR(_6);
				ZVAL_NULL(_6);
			}
			ZEPHIR_INIT_LNVAR(_7);
			if (!ZEPHIR_IS_STRING_IDENTICAL(optional, "")) {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_STRING(_7, "?", 1);
			} else {
				ZEPHIR_INIT_NVAR(_7);
				ZVAL_NULL(_7);
			}
			ZEPHIR_INIT_NVAR(pattern);
			ZEPHIR_CONCAT_SVSVVSV(pattern, "(?:", _5, "(", _6, type, "))", _7);
			ZEPHIR_INIT_NVAR(_8);
			zephir_fast_str_replace(_8, block, pattern, url);
			zephir_get_strval(url, _8);
		}
	}
	ZEPHIR_CONCAT_SVS(return_value, "`^", url, "$`u");
	RETURN_MM();

}

