<?php

// comment out to test with/without c-extension
dl('prr.so');
include './debug.php';
define('START_TIME', microtime(true));

#include '../vendor/autoload.php';

if (apc_exists('routes3')) {
	$routes = apc_fetch('routes3');
} else {
	$routes = yaml_parse_file('routes2.yml');
	apc_store('routes3', $routes, 60);
}

$router = new Prr\Router;
$router->addRoutes($routes);

#$requestUrl = '/users/123/cbb2f436551daf3ba5fd7c96eeba0b55';
$requestUrl = '/users/123/c6452bb8801efc9031f8a7e7251c8244';
$match = $router->match($requestUrl, 'GET');

$result = $match instanceof \Prr\Route ? 'true' : 'false';
d($match);
d($result);
