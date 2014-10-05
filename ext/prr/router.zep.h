
extern zend_class_entry *prr_router_ce;

ZEPHIR_INIT_CLASS(Prr_Router);

PHP_METHOD(Prr_Router, __construct);
PHP_METHOD(Prr_Router, setBasePath);
PHP_METHOD(Prr_Router, addMatchTypes);
PHP_METHOD(Prr_Router, clear);
PHP_METHOD(Prr_Router, add);
PHP_METHOD(Prr_Router, addRoutes);
PHP_METHOD(Prr_Router, removeExtraSlashes);
PHP_METHOD(Prr_Router, setMatchedRoute);
PHP_METHOD(Prr_Router, getMatchedRoute);
PHP_METHOD(Prr_Router, getController);
PHP_METHOD(Prr_Router, getAction);
PHP_METHOD(Prr_Router, getConsumes);
PHP_METHOD(Prr_Router, getProduces);
PHP_METHOD(Prr_Router, setDefaultConsumes);
PHP_METHOD(Prr_Router, setDefaultProduces);
PHP_METHOD(Prr_Router, getParams);
PHP_METHOD(Prr_Router, generate);
PHP_METHOD(Prr_Router, match);
PHP_METHOD(Prr_Router, getUrlMatches);
PHP_METHOD(Prr_Router, compileRoute);

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, routes, Prr\\RouteCollection, 1)
	ZEND_ARG_OBJ_INFO(0, namedRoutes, Prr\\RouteCollection, 1)
	ZEND_ARG_INFO(0, basePath)
	ZEND_ARG_INFO(0, matchTypes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_setbasepath, 0, 0, 1)
	ZEND_ARG_INFO(0, basePath)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_addmatchtypes, 0, 0, 1)
	ZEND_ARG_INFO(0, matchTypes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_add, 0, 0, 2)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, target)
	ZEND_ARG_INFO(0, methods)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_addroutes, 0, 0, 1)
	ZEND_ARG_INFO(0, routes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_removeextraslashes, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_setmatchedroute, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, route, Prr\\Route, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_setdefaultconsumes, 0, 0, 1)
	ZEND_ARG_INFO(0, consumes)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_setdefaultproduces, 0, 0, 1)
	ZEND_ARG_INFO(0, produces)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_generate, 0, 0, 1)
	ZEND_ARG_INFO(0, routeName)
	ZEND_ARG_INFO(0, params)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_match, 0, 0, 2)
	ZEND_ARG_INFO(0, requestUrl)
	ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_geturlmatches, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_prr_router_compileroute, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(prr_router_method_entry) {
	PHP_ME(Prr_Router, __construct, arginfo_prr_router___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Prr_Router, setBasePath, arginfo_prr_router_setbasepath, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, addMatchTypes, arginfo_prr_router_addmatchtypes, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, clear, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, add, arginfo_prr_router_add, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, addRoutes, arginfo_prr_router_addroutes, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, removeExtraSlashes, arginfo_prr_router_removeextraslashes, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, setMatchedRoute, arginfo_prr_router_setmatchedroute, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getMatchedRoute, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getController, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getAction, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getConsumes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getProduces, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, setDefaultConsumes, arginfo_prr_router_setdefaultconsumes, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, setDefaultProduces, arginfo_prr_router_setdefaultproduces, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getParams, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, generate, arginfo_prr_router_generate, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, match, arginfo_prr_router_match, ZEND_ACC_PUBLIC)
	PHP_ME(Prr_Router, getUrlMatches, arginfo_prr_router_geturlmatches, ZEND_ACC_PROTECTED)
	PHP_ME(Prr_Router, compileRoute, arginfo_prr_router_compileroute, ZEND_ACC_PROTECTED)
  PHP_FE_END
};
