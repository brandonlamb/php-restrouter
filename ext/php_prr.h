
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_PRR_H
#define PHP_PRR_H 1

#define ZEPHIR_RELEASE 1

#include "kernel/globals.h"

#define PHP_PRR_NAME        "prr"
#define PHP_PRR_VERSION     "0.0.1"
#define PHP_PRR_EXTNAME     "prr"
#define PHP_PRR_AUTHOR      ""
#define PHP_PRR_ZEPVERSION  "0.5.4a"
#define PHP_PRR_DESCRIPTION ""



ZEND_BEGIN_MODULE_GLOBALS(prr)

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(prr)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(prr)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(prr_globals_id, zend_prr_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (prr_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_prr_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(prr_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(prr_globals)
#endif

#define zephir_globals_def prr_globals
#define zend_zephir_globals_def zend_prr_globals

extern zend_module_entry prr_module_entry;
#define phpext_prr_ptr &prr_module_entry

#endif
