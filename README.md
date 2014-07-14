php-restrouter
==============

PHP REST Router

# Example 1

```yaml
---
- url: "/users"
  controller: "UserController::getAction"
  methods: [GET, POST]

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

// Add another route to the router
$router->add(
    '/posts/[i:postId]/comments',
    ['controller' => '\\v1\\Controller\\Posts\\Collection\\CommentsController'],
    ['GET']
);

$route = $router->match('/posts/1001/comments', 'GET');
```
