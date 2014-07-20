<?php

class Benchmark
{
	/**
	 * All of the benchmark starting times.
	 *
	 * @var array
	 */
	public static $marks = array();

	/**
	 * Enforce singleton; disallow instantiation
	 *
	 * @return void
	 */
	private function __construct() {}

	/**
	 * Enforce singleton; disallow cloning
	 *
	 * @return void
	 */
	private function __clone() {}

	/**
	 * Start a benchmark.
	 *
	 * After starting a benchmark, the elapsed time in milliseconds can be
	 * retrieved using the "check" method.
	 *
	 * @param  string $name,    key to use to save in marks
	 * @param  mixed  $content, optional content to display
	 * @return void
	 * @see	check
	 */
	public static function start($name, $content = null)
	{
		static::$marks[$name] = array(
			'start' => microtime(true),
			'stop' => null,
			'time' => 0,
			'memory' => 0,
			'peak' => 0,
			'content' => null !== $content ? $content : null,
		);
	}

	/**
	 * Stop a benchmark.
	 *
	 * After starting a benchmark, the elapsed time in milliseconds can be
	 * retrieved using the "check" method.
	 *
	 * @param  string $name,    key to use to save in marks
	 * @param  mixed  $content, optional content to display
	 * @return void
	 * @see	check
	 */
	public static function stop($name, $content = null)
	{
		// Set stop time
		static::$marks[$name]['stop'] = microtime(true);

		// Set time taken between start and stop times
#		$diff = number_format(static::$marks[$name]['stop'] - static::$marks[$name]['start'], 10);
		$diff = number_format((static::$marks[$name]['stop'] - static::$marks[$name]['start']) * 1000, 2) . 'ms';
		#$diff = number_format((static::$marks[$name]['stop'] - static::$marks[$name]['start']), 5) . ' seconds';
		static::$marks[$name]['time'] = $diff;

		// Get memory used
		static::$marks[$name]['memory'] = number_format(memory_get_usage() / 1024, 2) . 'KB';

		// Getpeak  memory used
		static::$marks[$name]['peak'] = number_format(memory_get_peak_usage() / 1024, 2) . 'KB';

		// Set content if any
		static::$marks[$name]['content'] = null !== $content ? $content : null;
	}

	public static function display()
	{
		foreach (static::$marks as $name => &$mark) {
			echo $name . "\t\t - time:" . $mark['time'] . ' / memory:' . $mark['memory'] . ' / peak:' . $mark['peak'] . "\n";
		}
	}
}
