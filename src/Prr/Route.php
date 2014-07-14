<?php
namespace Prr;

class Route
{
    /**
     * URL of this Route
     *
     * @var string
     */
    protected $url;

    /**
     * Accepted HTTP methods for this route
     *
     * @var array
     */
    protected $methods = ['GET', 'POST', 'PUT', 'DELETE', 'PATCH', 'OPTIONS', 'HEAD'];

    /**
     * Target for this route, can be anything.
     *
     * @var array
     */
    protected $target = [];

    /**
     * The name of this route, used for reversed routing
     *
     * @var string
     */
    protected $name;

    /**
     * Custom parameter filters for this route
     *
     * @var array
     */
    protected $filters = [];

    /**
     * Array containing parameters passed through request URL
     *
     * @var array
     */
    protected $parameters = [];

    /**
     * Constructor
     *
     * @param string $url
     * @param array $target
     * @param array $methods
     * @param string $name
     */
    public function __construct($url, array $target = null, array $methods = null, $name = null)
    {
        $this->url = $url;
        $methods !== null && $this->setMethods($methods);
        $target !== null && $this->setTarget($target);
        $name !== null && $this->setName($name);
    }

    /**
     * Get the route url
     *
     * @return string
     */
    public function getUrl()
    {
        return $this->url;
    }

    /**
     * Set the route url
     *
     * @param string $url
     * @return $this
     */
    public function setUrl($url)
    {
        $this->url = trim($url);

        // make sure that the URL is suffixed with a forward slash
        #substr($this->url, -1) !== '/' && $this->url .= '/';

        return $this;
    }

    /**
     * Get the target
     *
     * @return array
     */
    public function getTarget()
    {
        return $this->target;
    }

    /**
     * Set the target
     *
     * @param array $target
     * @return $this
     */
    public function setTarget(array $target)
    {
        $this->target = $target;
        return $this;
    }

    /**
     * Get route methods
     *
     * @return array
     */
    public function getMethods()
    {
        return $this->methods;
    }

    /**
     * Set the route methods
     *
     * @param array
     * @return $this
     */
    public function setMethods(array $methods)
    {
        $this->methods = $methods;
        return $this;
    }

    /**
     * Get the route name
     *
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * Set the route name
     *
     * @param string
     * @return $this
     */
    public function setName($name)
    {
        $this->name = trim($name);
        return $this;
    }

    /**
     * Set the route filters
     *
     * @param array $filters
     * @return $this;
     */
    public function setFilters(array $filters)
    {
        $this->filters = $filters;
        return $this;
    }

    /**
     * Get regular expression for this route
     *
     * @return string
     */
    public function getRegex()
    {
       return preg_replace_callback("/:(\w+)/", [$this, 'substituteFilter'], $this->url);
    }

    /**
     * Substitute filters in the regular expression
     *
     * @param array $matches
     * @return string
     */
    protected function substituteFilter(array $matches)
    {
        if (isset($matches[1]) && isset($this->filters[$matches[1]])) {
            return $this->filters[$matches[1]];
        }
        return "([\w-]+)";
    }

    /**
     * Get route parameters
     *
     * @return array
     */
    public function getParameters()
    {
        return $this->parameters;
    }

    /**
     * Set route parameters
     *
     * @param array $parameters
     * @return $this
     */
    public function setParameters(array $parameters)
    {
        $this->parameters = $parameters;
        return $this;
    }
}
