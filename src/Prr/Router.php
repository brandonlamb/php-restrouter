<?php
namespace Prr;

class Router
{
	/**
	 * Collection of routes
	 *
	 * @var RouteCollection
	 */
	protected $routes;

	/**
	 * Collection of named routes
	 *
	 * @var array
	 */
	protected $namedRoutes;

    /**
     * The base REQUEST_URI. Gets prepended to all route url's.
     *
     * @var string
     */
    protected $basePath;

    /**
     * The last matched route
     *
     * @var Route
     */
    protected $matchedRoute;

    /**
     * Flag for removing extra slashes from url
     *
     * @var bool
     */
    protected $removeExtraSlashes = true;

    /**
     * Named match types for convenience in defining routes
     *
     * @var array
     */
    protected $matchTypes = [
    	// Integer
		'i'  => '[0-9]++',

		// Alphanumeric
		'a'  => '[0-9A-Za-z]++',

		// Hexadecimal
		'h'  => '[0-9A-Fa-f]++',

		'year' => '[1-9]\d{0,3}++',
		'date' => '\d{4}-\d{2}-\d{2}++',
		'*'  => '.+?',
		'**' => '.++',
		''   => '[^/\.]++'
	];

	/**
	 * Constructor
	 *
	 * @param RouteCollection $routes
	 * @param string $basePath
	 * @param array $matchTypes
	 */
	public function __construct(RouteCollection $routes = null, RouteCollection $namedRoutes = null, $basePath = '', array $matchTypes = [])
	{
		if ($routes instanceof RouteCollection) {
			$this->routes = $routes;
		} else {
			$this->routes = new RouteCollection;
		}

		if ($namedRoutes instanceof RouteCollection) {
			$this->namedRoutes = $namedRoutes;
		} else {
			$this->namedRoutes = new RouteCollection;
		}

		$this->setBasePath($basePath);
		!empty($matchTypes) && $this->addMatchTypes($matchTypes);
	}

    /**
     * Set the base _url - gets prepended to all route _url's.
     *
     * @param $basePath
     * @return $this
     */
    public function setBasePath($basePath)
    {
        $this->basePath = trim(rtrim($basePath, '/'));
        return $this;
    }

	/**
	 * Add named match types. It uses array_merge so keys can be overwritten.
	 *
	 * @param array $matchTypes The key is the name and the value is the regex.
	 * @return $this
	 */
	public function addMatchTypes(array $matchTypes)
	{
		$this->matchTypes = array_merge($this->matchTypes, $matchTypes);
		return $this;
	}

	/**
	 * Map a route to a target
	 *
	 * @param string $url The route regex, custom regex must start with an @. You can use multiple pre-set regex filters, like [i:id]
	 * @param array $target The target where this route should point to. Can be anything.
	 * @param array $methods One of 5 HTTP Methods, or a pipe-separated list of multiple HTTP Methods (GET|POST|PATCH|PUT|DELETE)
	 * @param string $name Optional name of this route. Supply if you want to reverse route this url in your application.
	 * @return $this
	 */
	public function add($url, array $target, array $methods = null, $name = null)
	{
		$route = new Route($url, $target, $methods, $name);

		// Add route to collection
		$this->routes->add($route);

		// If a name was passed, add to named routes
		if ($name) {
			if (isset($this->namedRoutes[$name])) {
				throw new \Exception("Can not redeclare route '{$name}'");
			} else {
				$this->namedRoutes[$name] = $route;
			}
		}

		return $this;
	}

	/**
	 * Add multiple routes at once from array in the following format:
	 *
	 *   $routes = [
	 *      new Route($route, $target, $methods, $name),
	 *      new Route($route, $target, $methods, $name)
	 *   ];
	 *
	 * @param mixed $routes, Can pass array, Traversable or RouteCollection
	 * @return $this
	 * @throws \InvalidArgumentException
	 */
	public function addRoutes($routes)
	{
		$this->routes->addRoutes($routes);
		return $this;
	}

	/**
	 * Set whether to remove extra slashes
	 *
	 * @param boolean $value
	 * @return $this
	 */
	public function removeExtraSlashes($value)
	{
		$this->removeExtraSlashes = (bool) $value;
		return $this;
	}

	/**
	 * Set the matched route
	 *
	 * @param Route $route
	 * @return $this
	 */
	public function setMatchedRoute(Route $route)
	{
		$this->matchedRoute = $route;
		return $this;
	}

	/**
	 * Get the matched route
	 *
	 * @return Route
	 */
	public function getMatchedRoute()
	{
		if (!$this->matchedRoute) {
			throw new \RuntimeException('No route was matched');
		}
		return $this->matchedRoute;
	}

	/**
	 * Reversed routing
	 *
	 * Generate the URL for a named route. Replace regexes with supplied parameters
	 *
	 * @param string $routeName The name of the route.
	 * @param array $params Associative array of parameters to replace placeholders with.
	 * @return string The URL of the route with named parameters in place.
	 */
	public function generate($routeName, array $params = [])
	{
		// Check if named route exists
		if (!isset($this->namedRoutes[$routeName])) {
			throw new \Exception("Route '{$routeName}' does not exist.");
		}

		// Replace named parameters
		$route = $this->namedRoutes[$routeName];

		// prepend base path to route url again
		$url = $this->basePath . $route->getUrl();

		// On a match, results in an array with 0 = [key:name], 1 = /, 2 = key, 3 = name
		#if (preg_match_all('`(/|\.|)\[([^:\]]*+)(?::([^:\]]*+))?\](\?|)`', $route->getUrl(), $matches, PREG_SET_ORDER)) {
		$matches = $this->getUrlMatches($route->getUrl());
		if (!empty($matches)) {
			foreach($matches as $match) {
				list($block, $pre, $type, $param, $optional) = $match;

				if ($pre) {
					$block = substr($block, 1);
				}

				if (isset($params[$param])) {
					$url = str_replace($block, $params[$param], $url);
				} elseif ($optional) {
					$url = str_replace($pre . $block, '', $url);
				}
			}
		}

		return $url;
	}

	/**
	 * Attempt to match a route against configured route collection
	 *
	 * @param string $requestUrl
	 * @param string $method
	 * @return Route|boolean
	 */
	public function match($requestUrl, $method)
	{
		$this->removeExtraSlashes && $requestUrl = rtrim($requestUrl, '/');
		$method = strtoupper(trim($method));
		$params = [];
		$match = false;

		foreach ($this->routes as $route) {
	        // compare server request method with route's allowed http methods
	        if (!in_array($method, $route->getMethods())) {
	            continue;
	        }

	        $routeUrl = $route->getUrl();

	        // Check for a wildcard (matches all)
			if ($routeUrl === '*') {
				$match = true;
			} elseif (isset($routeUrl[0]) && $routeUrl[0] === '@') {
				$pattern = '`' . substr($routeUrl, 1) . '`u';
				$match = preg_match($pattern, $requestUrl, $params);
			} else {
				$url = null;
				$regex = false;
				$j = 0;
				$n = isset($routeUrl[0]) ? $routeUrl[0] : null;
				$i = 0;

				// Find the longest non-regex substring and match it against the URI
				while (true) {
					if (!isset($routeUrl[$i])) {
						break;
					} elseif (false === $regex) {
						$c = $n;
						$regex = $c === '[' || $c === '(' || $c === '.';
						if (false === $regex && false !== isset($routeUrl[$i+1])) {
							$n = $routeUrl[$i + 1];
							$regex = $n === '?' || $n === '+' || $n === '*' || $n === '{';
						}
						if (false === $regex && $c !== '/' && (!isset($requestUrl[$j]) || $c !== $requestUrl[$j])) {
							continue 2;
						}
						$j++;
					}
					$url .= $routeUrl[$i++];
				}

				$regex = $this->compileRoute($url);
				$match = preg_match($regex, $requestUrl, $params);
			}

	        // Build array of key:value parameters
			if ($match == true || $match > 0) {
				if ($params) {
					foreach ($params as $key => $value) {
						if (is_numeric($key)) {
							unset($params[$key]);
						}
					}
				}


				$route->setParameters($params);
				$route->setTarget(array_merge($route->getTarget(), ['method' => $method]));

				return $this->setMatchedRoute($route)->getMatchedRoute();
			}
		}

		return false;
	}

	/**
	 * Get array of matches for route url
	 *
	 * @param string $url
	 * @return array
	 */
	protected function getUrlMatches($url)
	{
		preg_match_all('`(/|\.|)\[([^:\]]*+)(?::([^:\]]*+))?\](\?|)`', $url, $matches, PREG_SET_ORDER);
		return $matches;
	}

	/**
	 * Compile the regex for a given route (EXPENSIVE)
	 *
	 * @param string $url
	 * @return string
	 */
	protected function compileRoute($url)
	{
		$matches = $this->getUrlMatches($url);
		if (!empty($matches)) {
			$matchTypes = $this->matchTypes;
			foreach($matches as $match) {
				list($block, $pre, $type, $param, $optional) = $match;

				if (isset($matchTypes[$type])) {
					$type = $matchTypes[$type];
				}
				if ($pre === '.') {
					$pre = '\.';
				}

				$pattern = '(?:'
					. ($pre !== '' ? $pre : null)
					. '(' . ($param !== '' ? "?<" . $param . ">" : null) . $type . '))'
					. ($optional !== '' ? '?' : null);

				$url = str_replace($block, $pattern, $url);
			}
		}

		return '`^' . $url . '$`u';
	}
}
