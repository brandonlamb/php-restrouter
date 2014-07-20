<?php

define('START_TIME', microtime(true));

$_SERVER['REQUEST_METHOD'] = 'GET';
$_SERVER['REQUEST_URI'] = '/users/';

include './examples/debug.php';
include './vendor/autoload.php';

#include 'test-1.php';
#include 'test-2.php';
#include '../PHP-Router/vendor/autoload.php';

$collection = new Prr\RouteCollection;

/*
$route = new Prr\Route(
    '/users/',
    ['controller' => 'UserController::getAction'],
    ['GET', 'POST']
);
$route->setUrl('/users/bob');
#d($route);
*/

#$collection[] = $route;
#$collection->add($route);
#$collection->add($route);

$router = (new Prr\Router)->addRoutes($collection);

/*
$router->add(
    '/locations/[i:locationId]/counts/[i:countId]/instances/[i:instanceId]',
    ['controller' => '\\v1\\Controller\\Instance\\CountsController'],
    ['GET']
);
#$router->setBasePath('/api/');
*/

/*
$url = $router->generate(
    'counts',
    [
        'locationId' => 101,
        'countId' => 10000001,
        'instanceId' => 123,
    ]
);
d($url);
*/

/*
$url = '/locations/[i:locationId]/counts/[i:countId]/instances/[i:instanceId]';
$url = '/v1/counts/[i:countId]/[i:instanceId]';
$url = '/v1/counts/[i:countId]/(?:<instanceId>[0-9]++)';
$url = '/v1/counts/[i:countId]/[(?<instanceId>[0-9]++)]';
$url = '@/(?[A-Za-z]{2}_[A-Za-z]{2})$';
d($router->compileRoute($url));
*/

/*
$router->addRoutes([
    [
        'url' => '/locations/[i:locationId]/counts/[i:countId]/instances/[i:instanceId]',
        'controller' => '\\v1\\Controller\\Instance\\CountsController',
        'methods' => ['GET']
    ]
]);
*/
$router->addRoutes(yaml_parse_file('examples/routes.yaml'));
#d($router);



$requestUrl = '/locations/101/counts/10000001/instances/123/';
#$regex = '`^/locations(?:/(?P<locationId>[0-9]++))/counts(?:/(?P<countId>[0-9]++))/instances(?:/(?P<instanceId>[0-9]++))$`u';
#$regex = '`^/locations(?:/(?<locationId>[0-9]++))/counts(?:/(?<countId>[0-9]++))/instances(?:/(?<instanceId>[0-9]++))$`u';
#$match = preg_match($regex, $requestUrl, $params);
#d($match, $params);

$match = $router->match($requestUrl, 'GET');
d($match);

#d($router);

d();



/*
use PHPRouter\RouteCollection;
use PHPRouter\Router;
use PHPRouter\Route;

$collection = new RouteCollection();
$collection->attach(new Route('/users/', array(
    '_controller' => 'someController::users_create',
    'methods' => ['GET']
)));

$collection->attach(new Route('/', array(
    '_controller' => 'someController::indexAction',
    'methods' => 'GET'
)));

print_r($collection);exit;

$router = new Router($collection);
#$router->setBasePath('/PHP-Router');
$route = $router->matchCurrentRequest();

var_dump($route);
exit;
*/





$storage = new SplObjectStorage();

$obj1 = new Test(['methods' => ['GET', 'POST']]);
$obj2 = new Test(['methods' => 'GET']);

$storage->attach($obj1);
$storage->attach($obj2);
$storage->attach($obj1);

#$storage->attach(new Test(['test1' => 'one']));
#$storage->attach(new Test(['test2' => 'two']));
#$storage->attach(new Test(['test2' => 'two']));

print_r($storage);
echo "\n\n";
