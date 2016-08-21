<?php

/**
 * Assertions extracted from PHPUnit framework due an issue with YAML
 * dependency I couldn't resolve.
 *
 * @author alex
 */
class CommonAssertions {
    
    /**
     * Asserts that two variables have the same type and value.
     * Used on objects, it asserts that two variables reference
     * the same object.
     *
     * @param mixed  $expected
     * @param mixed  $actual
     * @param string $message
     */
    public static function assertSame($expected, $actual, $message = '')
    {
        if ($expected !== $actual){
            throw new Exception($message);
        }
    }
    
    /**
     * Asserts that a string matches a given format string.
     *
     * @param string $format
     * @param string $string
     * @param string $message
     *
     */
    public static function assertStringMatchesFormat($format, $string, $message = '')
    {
        if (!is_string($format)) {
            throw new Exception("Param 'format' must be an String");
        }

        if (!is_string($string)) {
            throw new Exception("Param 'string' must be an String");
        }

        if (1 != preg_match("/" . $format . "/", $string)){
            throw new Exception($message);
        }
    }
}
