
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
     * @see Iterator
     * @var int
     */
    protected position = 0;

    /**
     * Constructor
     */
    public function __construct()
    {
        let this->storage = [];
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
     * @throws \InvalidArgumentException
     */
    public function addRoutes(var routes) -> <\Prr\RouteCollection>
    {
        var route;

        if typeof routes != "array" && !(routes instanceof \Prr\RouteCollection) {
            throw new \InvalidArgumentException("Routes should be an array or an instance of Traversable");
        }

        for route in routes {
            if typeof route == "array" {
                this->add(new Route(
                    !isset route["url"] ? null : route["url"],
                    ["controller": !isset route["controller"] ? null : route["controller"]],
                    !isset route["methods"] ? [] : route["methods"],
                    !isset route["name"] ? null : route["name"]
                ));
            } else {
                if route instanceof \Prr\Route {
                    this->add(route);
                }
            }
        }

        return this;
    }

    /**
     * Add a route to collection
     *
     * @see ArrayAccess
     * @param mixed offset
     * @param mixed $value
     */
    public function offsetSet(var offset, var value)
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
    public function offsetUnset(var offset)
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
    public function offsetExists(var offset)
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

        if this->offsetExists(this->position) {
            return this->storage[this->position];
        }
        return null;
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

        return this->position;
    }

    /**
     * Increment position
     *
     * @see Iterator
     */
    public function next()
    {
        return next(this->storage);
        let this->position++;
    }

    /**
     * Rewind array position
     *
     * @see Iterator
     */
    public function rewind() -> void
    {
        reset(this->storage);
        return;
        let this->position = 0;
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

        return this->offsetExists(this->position);
    }
}
