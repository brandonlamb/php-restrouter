php-restrouter
==============

PHP REST Router

# Example 1

```yaml
---
- url: "/users/"
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

