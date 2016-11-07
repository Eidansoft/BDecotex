<?php
require_once (dirname(__FILE__)."/../view/ViewException.php.inc");
/**
 * Description of ControllerException
 *
 * @author alex
 */
class ControllerException extends ViewException {
    public function __construct($code, $httpCode = 500, $otherInfo = null) {
        parent::__construct($code, $httpCode, $otherInfo);
    }
}

?>