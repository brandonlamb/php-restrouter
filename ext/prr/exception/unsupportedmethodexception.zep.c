
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Prr_Exception_UnsupportedMethodException) {

	ZEPHIR_REGISTER_CLASS_EX(Prr\\Exception, UnsupportedMethodException, prr, exception_unsupportedmethodexception, prr_exception_ce, NULL, 0);

	return SUCCESS;

}

