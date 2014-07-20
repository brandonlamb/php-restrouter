<?php

// comment out to test with/without c-extension
dl('prr.so');
include './debug.php';
define('START_TIME', microtime(true));

#include '../vendor/autoload.php';

// Save
#$router = new Prr\Router;
#$router->addRoutes(yaml_parse_file('routes2.yml'));
#file_put_contents('router2.dat', serialize($router));

// Load
$router = unserialize(file_get_contents('router2.dat'));

$requestUrl = '/users/123/cbb2f436551daf3ba5fd7c96eeba0b55';
$match = $router->match($requestUrl, 'GET');

$result = $match instanceof \Prr\Route ? 'true' : 'false';
d($result);
