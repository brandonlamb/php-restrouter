
extern zend_class_entry *prr_routecollection_ce;

ZEPHIR_INIT_CLASS(Prr_RouteCollection);

PHP_METHOD(Prr_RouteCollection, __construct);
PHP_METHOD(Prr_RouteCollection, add);
PHP_METHOD(Prr_RouteCollection, addRoutes);
PHP_METHOD(Prr_RouteCollection, addRoute);
PHP_METHOD(Prr_RouteCollection, offsetSet);
PHP_METHOD(Prr_RouteCollection, offsetGet);
PHP_METHOD(Prr_RouteCollection, offsetUnset);
PHP_METHOD(Prr_RouteCollection, offsetExists);
PHP_METHOD(Prr_RouteCollection, count);
PHP_METHOD(Prr_RouteCollection, current);
PHP_METHOD(Prr_RouteCollection, key);
PHP_METHOD(Prr_RouteCollection, next);
PHP_METHOD(Prr_RouteCollection, rewind);
PHP_METHOD(Prr_RouteCollection, valid);
PHP_METHOD(Prr_RouteCollection, all);

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_add, 0, 0, 1)
	ZEND_ARG_INFO(0, route)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_addroutes, 0, 0, 1)
	ZEND_ARG_INFO(0, routes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_addroute, 0, 0, 1)
	ZEND_ARG_INFO(0, route)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_routecollection_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(prr_routecollection_method_entry) {
	PHP_ME(Prr_RouteCollection, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Prr_RouteCollection, add, arginfo_prr_routecollection_add, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, addRoutes, arginfo_prr_routecollection_addroutes, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, addRoute, arginfo_prr_routecollection_addroute, ZEND_ACC_PROTECTED)
	PHP_ME(Prr_RouteCollection, offsetSet, arginfo_prr_routecollection_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, offsetGet, arginfo_prr_routecollection_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, offsetUnset, arginfo_prr_routecollection_offsetunset, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, offsetExists, arginfo_prr_routecollection_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, count, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, current, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, key, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, next, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, rewind, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, valid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_RouteCollection, all, NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
