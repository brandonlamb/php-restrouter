php-restrouter
==============

PHP REST Router

Concepts

- It is not the duty of the router to "figure out" the request URL (/v1/blah)
- It is not the duty of the router to "figure out" the request method (get, post)
- It is not the duty of the router to "dispatch" (instantiate controller classes or call methods)
- It is not the duty of the router to "parse configs" (yaml, ini, etc)

Essentially the three classes responsible for routing simply loop over an array of routes and matching against a given string url and method. Routes are defined either by creating Route objects yourself or parse a yaml config yourself into the right array format.

On a successful match, the router simply passes back the route object. The route's "target" property can really contain anything (just an associative array), such as controller, method.

# Example 1

Create router using a yaml parsed config file to define routes.

```yaml
---
- url: "/users"
  controller: "UserController::getAction"
  methods: [GET, POST]
  name: users

- url: "/locations/[i:locationId]/counts/[i:countId]/instances/[i:instanceId]"
  controller: "\\v1\\Controller\\Collection\\CountsController"
  methods: [GET, POST, DELETE]
...
```

```php
$router = new Prr\Router;
$router->addRoutes(yaml_parse_file('examples/routes.yaml'));

$url = '/locations/101/counts/10000001/instances/123/';
$match = $router->match($url, 'GET');
```

# Example 2

Create a route collection outside of the router object and inject it.

```php
// Create instance of route collection
$collection = new Prr\RouteCollection;

// Create instance of a route
$route = new Prr\Route(
    '/users',
    ['controller' => 'UserController'],
    ['GET', 'POST']
);

// Add route to route collection
$collection[] = $route; // array access
$collection->add($route); // oop access

// Create instance of router and pass route collection
$router = (new Prr\Router)->addRoutes($collection);

// Add another route to the router using array syntax
$router->add(
    '/posts/[i:postId]/comments',
    ['controller' => '\\v1\\Controller\\Posts\\Collection\\CommentsController'],
    ['GET']
);

$route = $router->match('/posts/1001/comments', 'GET');
```

# Example 3

Dont create a route collection outside of the router object, one will be created internally.

```php
// Create instance of router
$router = new Prr\Router;

// Create instance of a route and add to router
$route = new Prr\Route(
    '/users',
    ['controller' => 'UserController'],
    ['GET', 'POST']
);
$router->add($route);

// Add another route to the router using array syntax
$router->add(
    '/posts/[i:postId]/comments',
    ['controller' => '\\v1\\Controller\\Posts\\Collection\\CommentsController'],
    ['GET']
);

$route = $router->match('/posts/1001/comments', 'GET');
```
