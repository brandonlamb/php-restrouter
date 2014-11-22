
namespace Prr;

use Prr\Exception\UnsupportedMethodException;

class Router
{
	/**
	 * Collection of routes
	 *
	 * @var RouteCollection
	 */
	protected routes;

	/**
	 * Collection of named routes
	 *
	 * @var array
	 */
	protected namedRoutes;

    /**
     * The base REQUEST_URI. Gets prepended to all route url"s.
     *
     * @var string
     */
    protected basePath;

    /**
     * The last matched route
     *
     * @var Route
     */
    protected matchedRoute;

    /**
     * Flag for removing extra slashes from url
     *
     * @var bool
     */
    protected removeExtraSlashes = true;

    /**
     * Named match types for convenience in defining routes
     *
     * @var array
     */
    protected matchTypes;

    /**
     * Default consumes array
     *
     * @var array
     */
    protected defaultConsumes;

    /**
     * Default produces array
     *
     * @var array
     */
    protected defaultProduces;

    /**
     * Array of media type route consumes
     *
     * @var array
     */
    protected consumes;

    /**
     * Array of media types route produces
     *
     * @var array
     */
    protected produces;

    /**
     * Controller name
     *
     * @var string
     */
    protected controller;

    /**
     * Action name
     *
     * @var string
     */
    protected action;

    /**
     * Array containing parameters passed through request URL
     *
     * @var array
     */
    protected params;

	/**
	 * Constructor
	 *
	 * @param RouteCollection routes
	 * @param string basePath
	 * @param array matchTypes
	 */
	public function __construct(<\Prr\RouteCollection> routes = null, <\Prr\RouteCollection> namedRoutes = null, string! basePath = "", var matchTypes = [])
	{
		let this->matchTypes = [
	    	// Integer
			"i": "[0-9]++",

			// Alphanumeric
			"a": "[0-9A-Za-z]++",

			// Hexadecimal
			"h": "[0-9A-Fa-f]++",

			"year": "[1-9]\\d{0,3}++",
			"date": "\\d{4}-\\d{2}-\\d{2}++",
			"*": ".+?",
			"**": ".++",
			"" : "[^/\\.]++"
		];

		if typeof routes == "object" && (routes instanceof RouteCollection) {
			let this->routes = routes;
		} else {
			let this->routes = new \Prr\RouteCollection();
		}

		if typeof namedRoutes == "object" && (namedRoutes instanceof RouteCollection) {
			let this->namedRoutes = namedRoutes;
		} else {
			let this->namedRoutes = new RouteCollection;
		}

		if !empty matchTypes {
			this->addMatchTypes(matchTypes);
		}

		this->setBasePath(basePath);

		let this->defaultConsumes = [];
		let this->defaultProduces = [];
		let this->params = [];
	}

    /**
     * Set the base _url - gets prepended to all route _url"s.
     *
     * @param basePath
     * @return \Prr\Router
     */
    public function setBasePath(string! basePath) -> <\Prr\Router>
    {
        let this->basePath = trim(rtrim(basePath, "/"));
        return this;
    }

	/**
	 * Add named match types. It uses array_merge so keys can be overwritten.
	 *
	 * @param array matchTypes The key is the name and the value is the regex.
	 * @return \Prr\Router
	 */
	public function addMatchTypes(var matchTypes) -> <\Prr\Router>
	{
		if typeof matchTypes != "array" {
			throw new \InvalidArgumentException("matchTypes must be array");
		}
		let this->matchTypes = array_merge(this->matchTypes, matchTypes);
		return this;
	}

	/**
	 * Clear routes from route collection
	 *
	 * @return \Prr\Router
	 */
	public function clear() -> <\Prr\Router>
	{
		this->routes->clear();
		this->namedRoutes->clear();
		return this;
	}

	/**
	 * Map a route to a target
	 *
	 * @param string url The route regex, custom regex must start with an @. You can use multiple pre-set regex filters, like [i:id]
	 * @param array target The target where this route should point to. Can be anything.
	 * @param array methods One of 5 HTTP Methods, or a pipe-separated list of multiple HTTP Methods (GET|POST|PATCH|PUT|DELETE)
	 * @param string name Optional name of this route. Supply if you want to reverse route this url in your application.
	 * @return \Prr\Router
	 */
	public function add(string! url, var target, var methods = null, var name = null) -> <\Prr\Router>
	{
		var route;
		let route = new Route(url, target, methods, name);

		// Add route to collection
		this->routes->add(route);

		// If a name was passed, add to named routes
		if !empty name {
			if isset this->namedRoutes[name] {
				throw new \Exception("Can not redeclare route " . name);
			} else {
				let this->namedRoutes[name] = route;
			}
		}

		return this;
	}

	/**
	 * Add multiple routes at once from array in the following format:
	 *
	 *   routes = [
	 *      new Route(route, $target, $methods, $name),
	 *      new Route(route, $target, $methods, $name)
	 *   ];
	 *
	 * @param mixed routes, Can pass array, Traversable or RouteCollection
	 * @return \Prr\Router
	 * @throws \InvalidArgumentException
	 */
	public function addRoutes(var routes) -> <\Prr\Router>
	{
		this->routes->addRoutes(routes);
		return this;
	}

	/**
	 * Set whether to remove extra slashes
	 *
	 * @param boolean value
	 * @return \Prr\Router
	 */
	public function removeExtraSlashes(boolean value) -> <\Prr\Router>
	{
		let this->removeExtraSlashes = value;
		return this;
	}

	/**
	 * Set the matched route
	 *
	 * @param Route route
	 * @return \Prr\Router
	 */
	public function setMatchedRoute(<\Prr\Route> route) -> <\Prr\Router>
	{
		let this->matchedRoute = route;
		return this;
	}

	/**
	 * Get the matched route
	 *
	 * @return Route
	 */
	public function getMatchedRoute() -> <\Prr\Route>
	{
		if typeof this->matchedRoute != "object" {
			throw new \RuntimeException("No route was matched");
		}
		return this->matchedRoute;
	}

	/**
	 * Get controller class name
	 *
	 * @return string
	 */
	public function getController() -> string
	{
		return this->controller;
	}

	/**
	 * Get action name
	 *
	 * @return string
	 */
	public function getAction() -> string
	{
		return this->action;
	}

    /**
     * Get consumes array
     *
     * @return array
     */
    public function getConsumes() -> array
    {
        return this->consumes;
    }

    /**
     * Get produces array
     *
     * @return array
     */
    public function getProduces() -> array
    {
        return this->produces;
    }

    /**
     * Set the default consumes array
     *
     * @param array consumes
     * @return \Prr\Router
     */
    public function setDefaultConsumes(var consumes) -> <\Prr\Router>
    {
    	if typeof consumes != "array" {
    		throw new \InvalidArgumentException("consumes must be array");
    	}
    	let this->consumes = consumes;
    	return this;
    }

    /**
     * Set the default produces array
     *
     * @param array produces
     * @return \Prr\Router
     */
    public function setDefaultProduces(var produces) -> <\Prr\Router>
    {
    	if typeof produces != "array" {
    		throw new \InvalidArgumentException("consumes must be array");
    	}
    	let this->produces = produces;
    	return this;
    }

    /**
     * Get route parameters
     *
     * @return array
     */
    public function getParams() -> array
    {
        return this->params;
    }

	/**
	 * Reversed routing
	 *
	 * Generate the URL for a named route. Replace regexes with supplied parameters
	 *
	 * @param string routeName The name of the route.
	 * @param array $params Associative array of parameters to replace placeholders with.
	 * @return string The URL of the route with named parameters in place.
	 */
	public function generate(string! routeName, var params = []) -> string
	{
		var route, url, match, matches, block, pre, type, param, optional;

		// Check if named route exists
		if !isset this->namedRoutes[routeName] {
			throw new \Exception("Route " . routeName . " does not exist.");
		}

		// Replace named parameters
		let route = <\Prr\Route> this->namedRoutes[routeName];

		// prepend base path to route url again
		let url = this->basePath . route->getUrl();

		// On a match, results in an array with 0 = [key:name], 1 = /, 2 = key, 3 = name
		let matches = this->getUrlMatches(route->getUrl());

		if !empty matches {
			for match in matches {
				fetch block, match[0];
				fetch pre, match[1];
				fetch type, match[2];
				fetch param, match[3];
				fetch optional, match[4];

				if pre {
					let block = substr(block, 1);
				}

				if isset params[param] {
					let url = str_replace(block, params[param], url);
				} else {
					if optional {
						let url = str_replace(pre . block, "", url);
					}
				}
			}
		}

		return url;
	}

	/**
	 * Attempt to match a route against configured route collection
	 *
	 * @param string $requestUrl
	 * @param string $method
	 * @return boolean
	 */
	public function match(string! requestUrl, string! method) -> boolean
	{
		boolean match = false, unsupportedMethod = false;
		var route, methods, routeUrl, pattern, key, value, target, controller, action;
		var consumes, produces, params = [];

		if this->removeExtraSlashes {
			let requestUrl = rtrim(requestUrl, "/");
		}

		for route in this->routes->all() {
	        // compare server request method with route"s allowed http methods
			let methods = route->getMethods();
	        if !in_array(method, methods) {
	        	let unsupportedMethod = true;
	            continue;
	        }

	        let routeUrl = route->getUrl();

	        // Check for a wildcard (matches all)
			if (routeUrl === "*") {
				let match = true;
			} else {
				if isset routeUrl[0] && routeUrl[0] === "@" {
					let pattern = "`" . substr(routeUrl, 1) . "`u";
					let match = preg_match(pattern, requestUrl, params) ? true : false;
				} else {
					let pattern = this->compileRoute(routeUrl);
					let match = preg_match(pattern, requestUrl, params) ? true : false;
				}
			}

	        // Build array of key:value parameters
			if match {
				if count(params) {
					for key, value in params {
						if is_numeric(key) {
							unset params[key];
						}
					}
				}

				let this->params = params;

				// Fetch target data from route
				let target = route->getTarget();

				if fetch controller, target["controller"] {
					if memstr(controller, "::") {
						let controller = explode("::", controller);
						let this->controller = controller[0];
						let this->action = controller[1];
					} else {
						let this->controller = controller;
					}
				}

				if fetch action, target["action"] {
					let this->action = action;
				}

				if fetch consumes, target["consumes"] {
					let this->consumes = consumes;
				} else {
					let this->consumes = this->defaultConsumes;
				}

				if fetch produces, target["produces"] {
					let this->produces = produces;
				} else {
					let this->produces = this->defaultProduces;
				}

				route->setTarget(array_merge(route->getTarget(), ["method": method]));

				this->setMatchedRoute(route);

				return true;
			}
		}

		// We throw an exception if a route was matched by URL but did not support the method passed
		if unsupportedMethod {
			throw new UnsupportedMethodException("Route matched to URL, but method not supported");
		}

		return false;
	}

	/**
	 * Get array of matches for route url
	 *
	 * @param string $url
	 * @return array
	 */
	protected function getUrlMatches(string! url) -> array
	{
		var matches = [];
		//preg_match_all("`(/|\\.|)\\[([^:\\]]*+)(?::([^:\\]]*+))?\\](\\?|)`", url, matches, PREG_SET_ORDER);
		preg_match_all("`(/|\.|)\{([^:\}]*+)(?::([^:\}]*+))?\}(\\?|)`", url, matches, PREG_SET_ORDER);
		return matches;
	}

	/**
	 * Compile the regex for a given route (EXPENSIVE)
	 *
	 * @param string $url
	 * @return string
	 */
	protected function compileRoute(string! url) -> string
	{
		var match, matches, matchTypes, block, pre, type, param, optional, pattern;

		let matches = this->getUrlMatches(url);

		if !empty matches {
			let matchTypes = this->matchTypes;

			for match in matches {
				fetch block, match[0];
				fetch pre, match[1];
				fetch type, match[2];
				fetch param, match[3];
				fetch optional, match[4];

				if isset matchTypes[type] {
					let type = matchTypes[type];
				}
				if pre === "." {
					let pre = "\\.";
				}

				let pattern = "(?:"
					. (pre !== "" ? pre : null)
					. "(" . (param !== "" ? "?<" . param . ">" : null) . type . "))"
					. (optional !== "" ? "?" : null);

				let url = str_replace(block, pattern, url);
			}
		}

		return "`^" . url . "$`u";
	}
}
