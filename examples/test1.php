<?php

// comment out to test with/without c-extension
dl('prr.so');
include './debug.php';
define('START_TIME', microtime(true));

#include '../vendor/autoload.php';

if (apc_exists('routes4')) {
	$routes = apc_fetch('routes4');
} else {
	$routes = yaml_parse_file('routes2.yml');
	apc_store('routes4', $routes, 60);
}

$router = new Prr\Router;
$router->addRoutes($routes);

$requestUrl = '/users/123/e2ba087a22ca1863673172ec08945d0a';
$match = $router->match($requestUrl, 'GET');

$result = $match instanceof \Prr\Route ? 'true' : 'false';

echo "Request: $requestUrl\n";
echo "Controller: " . $router->getController() . "\n";
echo "Action: " . $router->getAction() . "\n";

echo "Params: ";
print_r($router->getParams());

echo "\nConsumes: ";
print_r($router->getConsumes());

echo "\nProduces: ";
print_r($router->getProduces());

d($match);
d($result);
