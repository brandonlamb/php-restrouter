<?php

namespace Prr;

use ArrayAccess;
use Countable;
use Iterator;

class RouteCollection implements ArrayAccess, Countable, Iterator
{
    /**
     * @var array
     */
    protected $storage = [];

    /**
     * @see Iterator
     * @var int
     */
    protected $position = 0;

    /**
     * Add a route to collection
     *
     * @param Route $route
     * @param mixed $offset
     * @return $this
     */
    public function add(Route $route, $offset = null)
    {
        if (null === $offset) {
            $this->storage[] = $route;
        } else {
            $this->storage[$offset] = $route;
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
     * @param array|RouteCollection $routes
     * @return $this
     * @throws \InvalidArgumentException
     */
    public function addRoutes($routes)
    {
        if (!is_array($routes) && !($routes instanceof Traversable) && !($routes instanceof self)) {
            throw new \InvalidArgumentException('Routes should be an array or an instance of Traversable');
        }

        foreach ($routes as $route) {
            if (is_array($route)) {
                $this->add(new Route(
                    !isset($route['url']) ?: $route['url'],
                    ['controller' => !isset($route['controller']) ?: $route['controller']],
                    !isset($route['methods']) ? [] : (array) $route['methods'],
                    !isset($route['name']) ?: $route['name']
                ));
            } else {
                $this->add($route);
            }
        }

        return $this;
    }

    /**
     * Add a route to collection
     *
     * @see ArrayAccess
     * @param mixed $offset
     * @param mixed $value
     */
    public function offsetSet($offset, $value)
    {
        $this->add($value, $offset);
    }

    /**
     * Get a route from collection
     *
     * @see ArrayAccess
     * @param mixed $offset
     * @return mixed
     * @throws \InvalidArgumentException
     */
    public function offsetGet($offset)
    {
        if (isset($this->storage[$offset])) {
            return $this->storage[$offset];
        }
        throw new \InvalidArgumentException($offset . ' does not exist.');
    }

    /**
     * Remove a route from collection
     *
     * @see ArrayAccess
     * @param mixed $offset
     */
    public function offsetUnset($offset)
    {
        unset($this->storage[$offset]);
    }

    /**
     * Check if route exists in collection
     *
     * @see ArrayAccess
     * @param mixed $offset
     * @return bool
     */
    public function offsetExists($offset)
    {
        return isset($this->storage[$offset]);
    }

    /**
     * Return number of routes
     *
     * @see Countable
     * @return int
     */
    public function count()
    {
        return count($this->storage);
    }

    /**
     * Return current array position
     *
     * @see Iterator
     * @return mixed
     */
    public function current()
    {
        if ($this->offsetExists($this->position)) {
            return $this->storage[$this->position];
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
        return $this->position;
    }

    /**
     * Increment position
     *
     * @see Iterator
     */
    public function next()
    {
        ++$this->position;
    }

    /**
     * Rewind array position
     *
     * @see Iterator
     */
    public function rewind()
    {
        $this->position = 0;
    }

    /**
     * Rewind array position
     *
     * @see Iterator
     * @return bool
     */
    public function valid()
    {
        return $this->offsetExists($this->position);
    }
}
