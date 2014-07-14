
namespace Prr;

class Route
{
    /**
     * URL of this Route
     *
     * @var string
     */
    protected url;

    /**
     * Accepted HTTP methods for this route
     *
     * @var array
     */
    protected methods;

    /**
     * Target for this route, can be anything.
     *
     * @var array
     */
    protected target;

    /**
     * The name of this route, used for reversed routing
     *
     * @var string
     */
    protected name = "";

    /**
     * Custom parameter filters for this route
     *
     * @var array
     */
    protected filters;

    /**
     * Array containing parameters passed through request URL
     *
     * @var array
     */
    protected parameters;

    /**
     * Constructor
     *
     * @param string url
     * @param array target
     * @param array methods
     * @param string name
     */
    public function __construct(string! url, var target = null, var methods = null, string! name = null)
    {
        let this->url = url;

        if typeof methods != "array" {
            let methods = ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS", "HEAD"];
        }
        this->setMethods(methods);

        if typeof target != "array" {
            let target = [];
        }
        this->setTarget(target);

        if typeof name != "null" {
            this->setName(name);
        }

        let this->filters = [];
        let this->parameters = [];
    }

    /**
     * Get the route url
     *
     * @return string
     */
    public function getUrl() -> string
    {
        return this->url;
    }

    /**
     * Set the route url
     *
     * @param string $url
     * @return \Prr\Route
     */
    public function setUrl(string! url) -> <\Prr\Route>
    {
        let this->url = trim(url);

        // make sure that the URL is suffixed with a forward slash
        // if substr(url, -1) !== "/") {
        //     let url .= "/";
        // }

        return this;
    }

    /**
     * Get the target
     *
     * @return array
     */
    public function getTarget() -> array
    {
        return this->target;
    }

    /**
     * Set the target
     *
     * @param array $target
     * @return \Prr\Route
     */
    public function setTarget(var target) -> <\Prr\Route>
    {
        if typeof target != "array" {
            throw new \InvalidArgumentException("target must be array");
        }
        let this->target = target;
        return this;
    }

    /**
     * Get route methods
     *
     * @return array
     */
    public function getMethods() -> array
    {
        return this->methods;
    }

    /**
     * Set the route methods
     *
     * @param array
     * @return \Prr\Route
     */
    public function setMethods(var methods) -> <\Prr\Route>
    {
        if typeof methods != "array" {
            throw new \InvalidArgumentException("methods must be array");
        }
        let this->methods = methods;
        return this;
    }

    /**
     * Get the route name
     *
     * @return string
     */
    public function getName() -> string
    {
        return this->name;
    }

    /**
     * Set the route name
     *
     * @param string
     * @return \Prr\Route
     */
    public function setName(string! name) -> <\Prr\Route>
    {
        let this->name = trim(name);
        return this;
    }

    /**
     * Set the route filters
     *
     * @param array $filters
     * @return \Prr\Route;
     */
    public function setFilters(var filters) -> <\Prr\Route>
    {
        if typeof filters != "array" {
            throw new \InvalidArgumentException("filters must be array");
        }
        let this->filters = filters;
        return this;
    }

    /**
     * Get regular expression for this route
     *
     * @return string
     */
    public function getRegex() -> string
    {
       return preg_replace_callback("/:(\\w+)/", [this, "substituteFilter"], this->url);
    }

    /**
     * Substitute filters in the regular expression
     *
     * @param array $matches
     * @return string
     */
    protected function substituteFilter(var matches) -> string
    {
        if typeof matches == "array" {
            if isset matches[1] && isset this->filters[matches[1]] {
                return this->filters[matches[1]];
            }
        }
        return "([\\w-]+)";
    }

    /**
     * Get route parameters
     *
     * @return array
     */
    public function getParameters() -> array
    {
        return this->parameters;
    }

    /**
     * Set route parameters
     *
     * @param array $parameters
     * @return \Prr\Route
     */
    public function setParameters(var parameters) -> <\Prr\Route>
    {
        if typeof parameters != "array" {
            throw new \InvalidArgumentException("parameters must be array");
        }
        let this->parameters = parameters;
        return this;
    }
}
