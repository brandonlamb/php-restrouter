<?php

include './debug.php';
define('START_TIME', microtime(true));

$config = yaml_parse_file('routes2.yml');
d($config);

