
namespace Prr;

use ArrayAccess;
use Countable;
use Iterator;

class RouteCollection implements ArrayAccess, Countable, Iterator
{
    /**
     * @var array
     */
    protected storage;

    /**
     * Constructor
     */
    public function __construct()
    {
        let this->storage = [];
    }

    /**
     * Clear routes
     *
     * @return \Prr\RouteCollection
     */
    public function clear() -> <\Prr\RouteCollection>
    {
        let this->storage = [];
        return this;
    }

    /**
     * Add a route to collection
     *
     * @param Route route
     * @param mixed offset
     * @return \Prr\RouteCollection
     */
    public function add(<\Prr\Route> route, var offset = null) -> <\Prr\RouteCollection>
    {
        if typeof offset == "null" {
            let this->storage[] = route;
        } else {
            let this->storage[offset] = route;
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
     * @param array|RouteCollection routes
     * @return \Prr\RouteCollection
     */
    public function addRoutes(var routes) -> <\Prr\RouteCollection>
    {
        var route;

        if typeof routes == "array" {
            for route in routes {
                this->addRoute(route);
            }
        }

        if typeof routes == "object" {
            if (routes instanceof \Prr\RouteCollection) {
                for route in routes->all() {
                    this->addRoute(route);
                }
            }
        }

        return this;
    }

    /**
     * Add a route via array or Route object
     *
     * @param Route|array route
     * @return \Prr\RouteCollection
     */
    protected function addRoute(var route) -> <\Prr\RouteCollection>
    {
        var url, name, methods;

        if typeof route == "object" {
            if route instanceof \Prr\Route {
                return this->add(route);
            }
        }

        if typeof route == "array" {
            if fetch url, route["url"] {
                unset route["url"];
            }

            if fetch name, route["name"] {
                unset route["name"];
            }

            if fetch methods, route["methods"] {
                unset route["methods"];
            }

            return this->add(new Route(url, route, methods, name));
        }

        throw new \InvalidArgumentException("route must be array or Route");
    }

    /**
     * Add a route to collection
     *
     * @see ArrayAccess
     * @param mixed offset
     * @param mixed $value
     */
    public function offsetSet(var offset, var value) -> void
    {
        this->add(value, offset);
    }

    /**
     * Get a route from collection
     *
     * @see ArrayAccess
     * @param mixed offset
     * @return mixed
     * @throws \InvalidArgumentException
     */
    public function offsetGet(var offset)
    {
        var value;
        if fetch value, this->storage[offset] {
            return value;
        }
        throw new \InvalidArgumentException(offset . " does not exist.");
    }

    /**
     * Remove a route from collection
     *
     * @see ArrayAccess
     * @param mixed offset
     */
    public function offsetUnset(var offset) -> void
    {
        unset this->storage[offset];
    }

    /**
     * Check if route exists in collection
     *
     * @see ArrayAccess
     * @param mixed offset
     * @return bool
     */
    public function offsetExists(var offset) -> boolean
    {
        return isset this->storage[offset];
    }

    /**
     * Return number of routes
     *
     * @see Countable
     * @return int
     */
    public function count() -> int
    {
        return sizeof(this->storage);
    }

    /**
     * Return current array position
     *
     * @see Iterator
     * @return mixed
     */
    public function current()
    {
        return current(this->storage);
    }

    /**
     * Return the current position
     *
     * @see Iterator
     * @return int
     */
    public function key()
    {
        return key(this->storage);
    }

    /**
     * Increment position
     *
     * @see Iterator
     */
    public function next()
    {
        return next(this->storage);
    }

    /**
     * Rewind array position
     *
     * @see Iterator
     */
    public function rewind() -> void
    {
        reset(this->storage);
    }

    /**
     * Rewind array position
     *
     * @see Iterator
     * @return boolean
     */
    public function valid() -> boolean
    {
        var key;
        let key = key(this->storage);
        return (key !== null && key !== false);
    }

    /**
     * Get the storage array of routes
     *
     * @return array
     */
    public function all() -> array
    {
        reset(this->storage);
        return this->storage;
    }
}
