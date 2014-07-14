
extern zend_class_entry *prr_route_ce;

ZEPHIR_INIT_CLASS(Prr_Route);

PHP_METHOD(Prr_Route, __construct);
PHP_METHOD(Prr_Route, getUrl);
PHP_METHOD(Prr_Route, setUrl);
PHP_METHOD(Prr_Route, getTarget);
PHP_METHOD(Prr_Route, setTarget);
PHP_METHOD(Prr_Route, getMethods);
PHP_METHOD(Prr_Route, setMethods);
PHP_METHOD(Prr_Route, getName);
PHP_METHOD(Prr_Route, setName);
PHP_METHOD(Prr_Route, setFilters);
PHP_METHOD(Prr_Route, getRegex);
PHP_METHOD(Prr_Route, substituteFilter);
PHP_METHOD(Prr_Route, getParameters);
PHP_METHOD(Prr_Route, setParameters);

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, methods)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_seturl, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_settarget, 0, 0, 1)
	ZEND_ARG_INFO(0, target)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_setmethods, 0, 0, 1)
	ZEND_ARG_INFO(0, methods)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_setname, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_setfilters, 0, 0, 1)
	ZEND_ARG_INFO(0, filters)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_substitutefilter, 0, 0, 1)
	ZEND_ARG_INFO(0, matches)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_route_setparameters, 0, 0, 1)
	ZEND_ARG_INFO(0, parameters)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(prr_route_method_entry) {
	PHP_ME(Prr_Route, __construct, arginfo_prr_route___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Prr_Route, getUrl, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, setUrl, arginfo_prr_route_seturl, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, getTarget, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, setTarget, arginfo_prr_route_settarget, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, getMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, setMethods, arginfo_prr_route_setmethods, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, setName, arginfo_prr_route_setname, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, setFilters, arginfo_prr_route_setfilters, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, getRegex, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, substituteFilter, arginfo_prr_route_substitutefilter, ZEND_ACC_PROTECTED)
	PHP_ME(Prr_Route, getParameters, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Route, setParameters, arginfo_prr_route_setparameters, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
