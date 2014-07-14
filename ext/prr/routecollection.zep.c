
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
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/hash.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Prr_RouteCollection) {

	ZEPHIR_REGISTER_CLASS(Prr, RouteCollection, prr, routecollection, prr_routecollection_method_entry, 0);

	/**
	 * @var array
	 */
	zend_declare_property_null(prr_routecollection_ce, SL("storage"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(prr_routecollection_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(prr_routecollection_ce TSRMLS_CC, 1, spl_ce_Countable);
	zend_class_implements(prr_routecollection_ce TSRMLS_CC, 1, zend_ce_iterator);
	return SUCCESS;

}

/**
 * Constructor
 */
PHP_METHOD(Prr_RouteCollection, __construct) {

	zval *_0;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_property_this(this_ptr, SL("storage"), _0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Add a route to collection
 *
 * @param Route route
 * @param mixed offset
 * @return \Prr\RouteCollection
 */
PHP_METHOD(Prr_RouteCollection, add) {

	zval *route, *offset = NULL;

	zephir_fetch_params(0, 1, 1, &route, &offset);

	if (!offset) {
		offset = ZEPHIR_GLOBAL(global_null);
	}


	if (!(zephir_instance_of_ev(route, prr_route_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'route' must be an instance of 'Prr\\Route'", "", 0);
		return;
	}
	if (Z_TYPE_P(offset) == IS_NULL) {
		zephir_update_property_array_append(this_ptr, SL("storage"), route TSRMLS_CC);
	} else {
		zephir_update_property_array(this_ptr, SL("storage"), offset, route TSRMLS_CC);
	}
	RETURN_THISW();

}

/**
 * Add multiple routes at once from array in the following format:
 *
 *   routes = [
 *      new Route(route, $target, $methods, $name),
 *      new Route(route, $target, $methods, $name)
 *   ];
 *
 * @param array|RouteCollection routes
 * @return \Prr\RouteCollection
 */
PHP_METHOD(Prr_RouteCollection, addRoutes) {

	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1, *_6;
	HashPosition _0, _5;
	zval *routes, *route = NULL, **_2, *_4 = NULL, **_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &routes);



	if (Z_TYPE_P(routes) == IS_ARRAY) {
		zephir_is_iterable(routes, &_1, &_0, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HVALUE(route, _2);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "addroute", &_3, route);
			zephir_check_call_status();
		}
	}
	if (Z_TYPE_P(routes) == IS_OBJECT) {
		if (zephir_instance_of_ev(routes, prr_routecollection_ce TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&_4, routes, "all",  NULL);
			zephir_check_call_status();
			zephir_is_iterable(_4, &_6, &_5, 0, 0);
			for (
			  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
			  ; zephir_hash_move_forward_ex(_6, &_5)
			) {
				ZEPHIR_GET_HVALUE(route, _7);
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "addroute", &_3, route);
				zephir_check_call_status();
			}
		}
	}
	RETURN_THIS();

}

/**
 * Add a route via array or Route object
 *
 * @param Route|array route
 * @return \Prr\RouteCollection
 */
PHP_METHOD(Prr_RouteCollection, addRoute) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_2;
	zval *route, *_0, *_1 = NULL, *_3 = NULL, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &route);



	if (Z_TYPE_P(route) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, prr_route_ce);
		ZEPHIR_INIT_VAR(_1);
		if (!(zephir_array_isset_string(route, SS("url")))) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_NULL(_1);
		} else {
			ZEPHIR_OBS_NVAR(_1);
			zephir_array_fetch_string(&_1, route, SL("url"), PH_NOISY TSRMLS_CC);
		}
		ZEPHIR_INIT_VAR(_2);
		array_init_size(_2, 2);
		ZEPHIR_INIT_VAR(_3);
		if (!(zephir_array_isset_string(route, SS("controller")))) {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_NULL(_3);
		} else {
			ZEPHIR_OBS_NVAR(_3);
			zephir_array_fetch_string(&_3, route, SL("controller"), PH_NOISY TSRMLS_CC);
		}
		zephir_array_update_string(&_2, SL("controller"), &_3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_3);
		if (!(zephir_array_isset_string(route, SS("methods")))) {
			ZEPHIR_INIT_NVAR(_3);
			array_init(_3);
		} else {
			ZEPHIR_OBS_NVAR(_3);
			zephir_array_fetch_string(&_3, route, SL("methods"), PH_NOISY TSRMLS_CC);
		}
		ZEPHIR_INIT_VAR(_4);
		if (!(zephir_array_isset_string(route, SS("name")))) {
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_NULL(_4);
		} else {
			ZEPHIR_OBS_NVAR(_4);
			zephir_array_fetch_string(&_4, route, SL("name"), PH_NOISY TSRMLS_CC);
		}
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1, _2, _3, _4);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, _0);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		if (zephir_instance_of_ev(route, prr_route_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "add", NULL, route);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "route must be array or Route", "prr/routecollection.zep", 93);
	return;

}

/**
 * Add a route to collection
 *
 * @see ArrayAccess
 * @param mixed offset
 * @param mixed $value
 */
PHP_METHOD(Prr_RouteCollection, offsetSet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *offset, *value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &offset, &value);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", NULL, value, offset);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Get a route from collection
 *
 * @see ArrayAccess
 * @param mixed offset
 * @return mixed
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Prr_RouteCollection, offsetGet) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *offset, *value, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &offset);



	ZEPHIR_OBS_VAR(value);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	if (zephir_array_isset_fetch(&value, _0, offset, 0 TSRMLS_CC)) {
		RETURN_CCTOR(value);
	}
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VS(_2, offset, " does not exist.");
	ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, _2);
	zephir_check_call_status();
	zephir_throw_exception_debug(_1, "prr/routecollection.zep", 122 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Remove a route from collection
 *
 * @see ArrayAccess
 * @param mixed offset
 */
PHP_METHOD(Prr_RouteCollection, offsetUnset) {

	zval *offset, *_0;

	zephir_fetch_params(0, 1, 0, &offset);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	zephir_array_unset(&_0, offset, PH_SEPARATE);

}

/**
 * Check if route exists in collection
 *
 * @see ArrayAccess
 * @param mixed offset
 * @return bool
 */
PHP_METHOD(Prr_RouteCollection, offsetExists) {

	zval *offset, *_0;

	zephir_fetch_params(0, 1, 0, &offset);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	RETURN_BOOL(zephir_array_isset(_0, offset));

}

/**
 * Return number of routes
 *
 * @see Countable
 * @return int
 */
PHP_METHOD(Prr_RouteCollection, count) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_FUNCTION("sizeof", &_1, _0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return current array position
 *
 * @see Iterator
 * @return mixed
 */
PHP_METHOD(Prr_RouteCollection, current) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_RETURN_CALL_FUNCTION("current", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the current position
 *
 * @see Iterator
 * @return int
 */
PHP_METHOD(Prr_RouteCollection, key) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_RETURN_CALL_FUNCTION("key", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Increment position
 *
 * @see Iterator
 */
PHP_METHOD(Prr_RouteCollection, next) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_RETURN_CALL_FUNCTION("next", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Rewind array position
 *
 * @see Iterator
 */
PHP_METHOD(Prr_RouteCollection, rewind) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(NULL, "reset", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Rewind array position
 *
 * @see Iterator
 * @return boolean
 */
PHP_METHOD(Prr_RouteCollection, valid) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *key = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(&key, "key", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	_2 = Z_TYPE_P(key) != IS_NULL;
	if (_2) {
		_2 = !ZEPHIR_IS_FALSE_IDENTICAL(key);
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Get the storage array of routes
 *
 * @return array
 */
PHP_METHOD(Prr_RouteCollection, all) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("storage"), PH_NOISY_CC);
	Z_SET_ISREF_P(_0);
	ZEPHIR_CALL_FUNCTION(NULL, "reset", &_1, _0);
	Z_UNSET_ISREF_P(_0);
	zephir_check_call_status();
	RETURN_MM_MEMBER(this_ptr, "storage");

}

