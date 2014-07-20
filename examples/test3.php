<?php

// comment out to test with/without c-extension
dl('prr.so');
include './debug.php';
define('START_TIME', microtime(true));

include '../vendor/autoload.php';

$router = new Prr\Router;

for ($i = 0; $i < 20; ++$i) {
	$router->add(
	    '/users/',
	    ['controller' => 'UserController::getAction'],
	    ['GET', 'POST']
	);
}

$router->add(
	"/locations/[i:locationId]/counts/[i:countId]/instances/[i:instanceId]",
	['controller' => 'UserController::getAction'],
    ['GET', 'POST', 'DELETE']
);

$requestUrl = '/locations/101/counts/10000001/instances/123/';
$match = $router->match($requestUrl, 'GET');

$result = $match instanceof \Prr\Route ? 'true' : 'false';
d($result);
